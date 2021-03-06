// VectorSum_Collective.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "mpi.h"
#define MAXSIZE 100

int main(int argc, char *argv[])
{
	int myid, numprocs;
	int data[MAXSIZE], i, offset, low, high, portion = 0, total_sum;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	if (0 == myid) {
		/* fill the array */
		for (int i = 0; i < MAXSIZE; i++)
		{
			data[i] = i;
		}
	}
	/* broadcast data */
	MPI_Bcast(data, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD);

	/* add portion of data */
	offset = MAXSIZE / numprocs; /* must be an integer */
	low = myid * offset;
	high = low + offset;
	for (i = low; i<high; i++) {
		portion += data[i];
	}
	printf("I got %d from %d\n", portion, myid);
	/* compute global sum */
	MPI_Reduce(&portion, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (0 == myid) {
		printf("The sum is %d.\n", total_sum);
	}
	MPI_Finalize();
	return 0;
}

