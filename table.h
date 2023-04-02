#ifndef OS_PROJECT_ONE_
#define OS_PROJECT_ONE_

#include <sys/mman.h>
#include <sys/stat.h>      
#include <fcntl.h> 
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MAX_TABLE_SIZE = 2;
int NUMBER_OF_REPS = 5;

struct table {
    int shared_buffer[2];
    sem_t empty_spots;
    sem_t filled_spots;
};

#endif
