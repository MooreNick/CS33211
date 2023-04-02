#include "table.h"

int main() {

    // most of this is same as producer.c, we do not need to intialize things as we did in producer.c

    int shared = shm_open("/Shared_memory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shared == -1)
        printf("error on shm_open()");

    struct table *consumer;
    consumer = mmap(0, sizeof(struct table), PROT_READ|PROT_WRITE, MAP_SHARED, shared, 0);
    if (consumer == MAP_FAILED)
        printf("error on mmap()");

    int rep = 0;
    while(rep < NUMBER_OF_REPS) {
        while(consumer->shared_buffer[0] == 0 && consumer->shared_buffer[1] == 0); // if table is still full of 0, then producer hasn't finished, busy wait

        // printf("consumer before crit");
        sleep(1);
        sem_wait(&consumer->filled_spots);

        for (int i = 0; i < MAX_TABLE_SIZE; ++i) {
            printf("consumer removed %d\n", consumer->shared_buffer[i]); // print the removed number
            consumer->shared_buffer[i] = 0; // 'reset' the removed number
        }
   
        ++rep;
        sem_post(&consumer->empty_spots);
    }
    

    return 0;


}
