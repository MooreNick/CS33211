# CS33211
Project 1 for Operating Systems
Producer/Consumer Problem

I solved this problem using semaphores in the C programming language. My submission includes two .c files and one .h file, all three of which are in this repository. My program was compiled and works connected to Kent State's wasp server via VS Code. I compliled the files using gcc producer.c -pthread -lrt -o producer and gcc consumer.c -pthread -lrt -o consumer. I then ran the files using ./producer & ./consumer and I the file ran as expected.

I used a second while loop in both files that busy wait if the 'other' process hasn't finished doing its' job yet. 

My .h file includes a couple of global variables and a defined structure for a table. The table has two semaphores and an integer array of size 2 for the produced/consumed items.
