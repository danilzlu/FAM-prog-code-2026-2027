# Занятие 2

Примеры кода со второго занятия.

Некоторые программы намеренно содержат ошибки. Известные проблемы
таких программ перечислены в начале файла в разделе `ISSUES`.

## Примеры

### `clock-3.01.c`, `clock-3.02.c`

Два варианта решения задачи «Часы 3», полученные на семинарах
в разных группах.

### `digits-02.c`

Пример решения задачи «Цифры 2».

Программа подсчитывает количество цифр целого числа.
Содержит известную ошибку на граничном случае `number == 0`.

### `year.c`

Пример решения задачи про високосный год.

## goto и jmp

Вообще говоря, все операторы управления потоком в Си транслируются в асемблерный код, использующий `jmp`. Смотрите примеры на Godbolt (возможно нестабильное соединение из некоторых локаций):

* [GOTO](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:___c,selection:(endColumn:2,endLineNumber:16,positionColumn:2,positionLineNumber:16,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:'int+f(int+x)%0A%7B%0A++++int+y+%3D+10%3B%0A%0A++++if+(x+%3E+0)%0A++++++++goto+positive%3B%0A%0A++++y+%3D+20%3B%0A++++goto+finish%3B%0A%0Apositive:%0A++++y+%3D+30%3B%0A%0Afinish:%0A++++return+y%3B%0A%7D'),l:'5',n:'0',o:'C+source+%231',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:cg161,filters:(b:'0',binary:'1',binaryObject:'1',commentOnly:'0',debugCalls:'1',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'0',trim:'1',verboseDemangling:'0'),flagsViewOpen:'1',fontScale:14,fontUsePx:'0',j:1,lang:___c,libs:!(),options:'-O0',overrides:!(),selection:(endColumn:12,endLineNumber:16,positionColumn:12,positionLineNumber:16,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'+x86-64+gcc+16.1+(Editor+%231)',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4) появляется `jmp`;
* [IF](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:___c,selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:'int+f(int+x)%0A%7B%0A++++int+y+%3D+10%3B%0A%0A++++if+(x+%3E+0)+%7B%0A++++++++y+%3D+20%3B%0A++++%7D%0A%0A++++return+y%3B%0A%7D'),l:'5',n:'0',o:'C+source+%231',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:cg161,filters:(b:'0',binary:'1',binaryObject:'1',commentOnly:'0',debugCalls:'1',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'0',trim:'1',verboseDemangling:'0'),flagsViewOpen:'1',fontScale:14,fontUsePx:'0',j:1,lang:___c,libs:!(),options:'-O0',overrides:!(),selection:(endColumn:9,endLineNumber:7,positionColumn:9,positionLineNumber:7,selectionStartColumn:9,selectionStartLineNumber:7,startColumn:9,startLineNumber:7),source:1),l:'5',n:'0',o:'+x86-64+gcc+16.1+(Editor+%231)',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4) вместо `jmp` появляется `jle`;
* [WHILE](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:___c,selection:(endColumn:2,endLineNumber:11,positionColumn:2,positionLineNumber:11,selectionStartColumn:2,selectionStartLineNumber:11,startColumn:2,startLineNumber:11),source:'int+f(int+x)%0A%7B%0A++++int+y+%3D+0%3B%0A%0A++++while+(x+%3E+0)+%7B%0A++++++++y+%3D+y+%2B+x%3B%0A++++++++x+%3D+x+-+1%3B%0A++++%7D%0A%0A++++return+y%3B%0A%7D'),l:'5',n:'0',o:'C+source+%231',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:cg161,filters:(b:'0',binary:'1',binaryObject:'1',commentOnly:'0',debugCalls:'1',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'0',trim:'1',verboseDemangling:'0'),flagsViewOpen:'1',fontScale:14,fontUsePx:'0',j:1,lang:___c,libs:!(),options:'-O0',overrides:!(),selection:(endColumn:10,endLineNumber:13,positionColumn:10,positionLineNumber:13,selectionStartColumn:10,selectionStartLineNumber:13,startColumn:10,startLineNumber:13),source:1),l:'5',n:'0',o:'+x86-64+gcc+16.1+(Editor+%231)',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4) появляются `jmp` и `jg`.