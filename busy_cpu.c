#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>
#include <sys/time.h>

int main(int argc, char **argv){
    int rank, size, time;

    if( argc < 2 ){
        printf("usage: ./busy_cpu T\nT: time in seconds to keep CPU busy\n");
        exit(-1);
    }

    time = atoi(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // variable to measure execution time
    struct timeval time_start;
    struct timeval time_end;

    // get the start time
    gettimeofday(&time_start, NULL);

    int current = 0;

    // do while current time < end time
    while( current < time ){
        // get the current time
        gettimeofday(&time_end, NULL);
        current = (double) (time_end.tv_sec - time_start.tv_sec) + (double) (time_end.tv_usec - time_start.tv_usec) / 1000000.0;
    }

    system("echo $(hostname)");

    MPI_Finalize();

    return 0;
}
