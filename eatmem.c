#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MILLI_TO_NANO 1000000;

int main()
{
    char* max_env = getenv("MAX_RAM");
    int max_ram = max_env ? atoi(max_env) : 300;

    char* sleep_env = getenv("SLEEP_MILLISECONDS");
    int sleep_millisecs = sleep_env ? atoi(sleep_env) : 50;

    struct timespec sleeptime;
    sleeptime.tv_sec = sleep_millisecs / 1000;
    sleeptime.tv_nsec = (sleep_millisecs % 1000) * MILLI_TO_NANO;
    
    printf("I will now consume %dMB of RAM, 1MB at a time.\n", max_ram);
    printf("I will sleep %d milliseconds between allocating each MB.\n", sleep_millisecs);
    printf("Set the MAX_RAM or SLEEP_MILLISECONDS env vars to change these values.\n");

    int count = 0;
    while(1)
    {
        void *m = malloc(1024*1024);
        memset(m,0,1024*1024);
        count++;
        printf("Used %dMB of RAM.\n", count);
        if (count >= max_ram) {
            break;
        }
        nanosleep(&sleeptime, NULL);
    }
    return 0;
}

