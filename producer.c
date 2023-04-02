#include "table.h"

int main(int argc, char* argv[]) {
    srand(time(NULL)); // random seed for project
    //srand(2); // fixed seed for debugging

    // create a shared memory location (if it doesn't exit "O_CREAT") give read and write access "O_RDWR"

    int shared = shm_open("/Shared_memory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shared == -1)
        printf("error on shm_open()");

    if (ftruncate(shared, sizeof(struct table)) == -1) // make sure resizing will not cause error
        printf("error on ftruncate()");
    else
        ftruncate(shared, sizeof(struct table)); // resize shared memory

    struct table *producer;

    producer = mmap(0, sizeof(struct table), PROT_READ|PROT_WRITE, MAP_SHARED, shared, 0); // get pointer to shared memory

    if (producer == MAP_FAILED)
        printf("error on mmap()");


    // Initialize semaphores and initial value of 0 for table

    sem_init(&producer->empty_spots, 1, MAX_TABLE_SIZE);
    sem_init(&producer->filled_spots, 1, 0);

    for (int i = 0; i < MAX_TABLE_SIZE; ++i) {
        producer->shared_buffer[i] = 0;
    }
    

    int rep = 0;
    while (rep < NUMBER_OF_REPS) { // num of reps is 5 in .h
        
        while (producer->shared_buffer[0] != 0 && producer->shared_buffer[1] != 0); // if table isn't zero, consumer isn't done consuming, busy wait

        // printf("prod before crit");
        sleep(1);
        sem_wait(&producer->empty_spots);

        int item;
        for (int i = 0; i < MAX_TABLE_SIZE; ++i) {
            item = rand() % 100 + 1; // get item
            if (item == 0) { // making sure it isn't zero
                item = 1;
            }
            producer->shared_buffer[i] = item;
            printf("producer produced %d\n", item);
        }
        ++rep;

        sem_post(&producer->filled_spots);

    }
    

    return 0;
}
