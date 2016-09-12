#ifndef __common__
#define __common__

#include <sys/time.h>
#include <unistd.h>

void Spin(int time){
    // begin time
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    double time_begin = tv.tv_sec * 1e6 + tv.tv_usec;

    // while get time
    double time_lapse = 0;
    double time_now;
    while(time_lapse < (time * 1e6)){
        gettimeofday(&tv, &tz);
        time_now = tv.tv_sec * 1e6 + tv.tv_usec;
        time_lapse = time_now - time_begin;
    }

    return;

}

#endif
