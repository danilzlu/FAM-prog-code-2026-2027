#!/usr/bin/env python3
"""Deterministic end-to-end fixtures for the avlset assignment. Python 3.9+."""
from bisect import bisect_left, bisect_right, insort
from pathlib import Path
import random

ROOT = Path(__file__).resolve().parent / 'tests'
ROOT.mkdir(exist_ok=True)

class Oracle:
    def __init__(self): self.a=[]
    def run(self, line):
        p=line.split(); op=p[0]; x=int(p[1]); a=self.a
        i=bisect_left(a,x)
        if op=='INSERT':
            if i==len(a) or a[i]!=x: a.insert(i,x)
        elif op=='DELETE':
            if i<len(a) and a[i]==x: a.pop(i)
        elif op=='EXISTS': return 'true' if i<len(a) and a[i]==x else 'false'
        elif op=='NEXT':
            j=bisect_right(a,x); return str(a[j]) if j<len(a) else 'none'
        elif op=='PREV': return str(a[i-1]) if i else 'none'
        elif op=='KTH': return str(a[x]) if 0<=x<len(a) else 'none'
        elif op=='RANK': return str(i)
        elif op in ('RANGE_COUNT','RANGE_SUM','DELETE_RANGE'):
            y=int(p[2]); lo=bisect_left(a,x); hi=bisect_right(a,y) if x<=y else lo
            if op=='RANGE_COUNT': return str(hi-lo)
            if op=='RANGE_SUM': return str(sum(a[lo:hi]))
            del a[lo:hi]
        else: raise ValueError(op)
        return None

def write(name,level,commands,stress=False):
    o=Oracle(); out=[]
    for line in commands:
        v=o.run(line)
        if v is not None: out.append(v)
    stem=f'L{level}_{"stress_" if stress else ""}{name}'
    (ROOT/(stem+'.in')).write_text('\n'.join(commands)+'\n',encoding='ascii')
    (ROOT/(stem+'.expected')).write_text('\n'.join(out)+('\n' if out else ''),encoding='ascii')
    print(f'{stem}: {len(commands)} commands, {len(out)} answers')

def random_ops(level,n,seed,span=100000):
    rng=random.Random(seed); cmds=[]
    ops=['INSERT']*4+['DELETE']*2+['EXISTS']*2+['NEXT','PREV']
    if level>=8: ops+=['KTH','RANK','RANGE_COUNT']*2
    if level>=9: ops+=['RANGE_SUM']*2
    if level>=10: ops+=['DELETE_RANGE']
    for _ in range(n):
        op=rng.choice(ops); x=rng.randint(-span,span)
        if op=='KTH': cmds.append(f'KTH {rng.randint(0,n)}')
        elif op in ('RANGE_COUNT','RANGE_SUM','DELETE_RANGE'):
            y=x+rng.randint(-span//10,span//10)
            cmds.append(f'{op} {x} {y}')
        else: cmds.append(f'{op} {x}')
    return cmds

write('basic',4,['EXISTS 1','NEXT 1','PREV 1','INSERT 5','INSERT 5','INSERT -2','INSERT 2147483647','INSERT -2147483648','EXISTS 5','NEXT 5','PREV -2','DELETE 5','DELETE 5','EXISTS 5','NEXT 2147483647','PREV -2147483648'])
write('delete_cases',4,['INSERT 10','INSERT 5','INSERT 15','INSERT 2','INSERT 7','INSERT 12','INSERT 20','DELETE 10','EXISTS 10','NEXT 7','PREV 12','DELETE 2','DELETE 20','DELETE 15','NEXT 12','PREV 7'])
write('rotations',6,['INSERT 30','INSERT 20','INSERT 10','INSERT 40','INSERT 50','INSERT 25','INSERT 27','INSERT 26','DELETE 10','DELETE 20','DELETE 30','EXISTS 25','NEXT 26','PREV 26'])
write('order_statistics',8,['KTH 0','RANK 0','RANGE_COUNT 2 1','INSERT 10','INSERT 5','INSERT 20','INSERT 15','KTH 0','KTH 2','KTH 4','RANK 15','RANK 16','RANGE_COUNT 5 15','RANGE_COUNT 16 19','RANGE_COUNT -2147483648 2147483647','DELETE 10','KTH 2','RANK 20'])
write('sums',9,['RANGE_SUM -10 10','INSERT 2147483647','INSERT -2147483648','INSERT -5','INSERT 7','RANGE_SUM -2147483648 2147483647','RANGE_SUM 0 2147483647','RANGE_SUM 8 6','DELETE -5','RANGE_SUM -2147483648 0','RANGE_COUNT -2147483648 2147483647'])
write('bulk_delete',10,['INSERT '+str(i) for i in range(-20,21)]+['DELETE_RANGE -5 5','RANGE_COUNT -20 20','RANGE_SUM -20 20','EXISTS 0','KTH 15','DELETE_RANGE 10 -10','RANK 10','DELETE_RANGE -2147483648 2147483647','KTH 0','RANGE_SUM -100 100','INSERT 3','EXISTS 3'])
for lvl,n in [(4,25000),(6,50000),(8,45000),(9,40000),(10,30000)]:
    write('random',lvl,random_ops(lvl,n,1000+lvl),stress=True)
write('sorted_insert',6,[f'INSERT {i}' for i in range(50000)]+[f'EXISTS {i}' for i in range(0,50000,17)]+[f'DELETE {i}' for i in range(0,50000,2)]+['NEXT 0','PREV 49999'],stress=True)
write('rank_heavy',8,[f'INSERT {i*2}' for i in range(30000)]+[f'RANK {i}' for i in range(30000)]+[f'RANGE_COUNT {i} {i+500}' for i in range(0,30000,3)],stress=True)
write('sum_heavy',9,[f'INSERT {i-15000}' for i in range(30000)]+[f'RANGE_SUM {-15000+i} {15000-i}' for i in range(15000)]+['RANGE_SUM -15000 15000'],stress=True)
write('bulk_heavy',10,[f'INSERT {i}' for i in range(60000)]+[f'DELETE_RANGE {i} {i+999}' for i in range(0,60000,1000)]+['RANGE_COUNT 0 60000','RANGE_SUM 0 60000','KTH 0'],stress=True)
