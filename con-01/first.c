#include <stdio.h>

const int secs_in_hour = 3600;
const int secs_in_min = 60;

int main(void) {
    int hours, mins, secs;
    int time;

    scanf("%d:%d:%d %d", &hours, &mins, &secs, &time);


    int secs2 = (secs + time) % 60;
    time = time / 60;
    int mins2 = (mins + time + (secs + time) / 60) % 60;
    time = time / 60;
    int hours2 = (hours + time) % 24;
    

    printf("%d:%d:%d\n", hours2, mins2, secs2);

    return 0;
}