/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

 /* This is an interactive version of cpi */
#include "mpi.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;


int main(int argc, char* argv[]) {

    int rank, n;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    cout << "Hello from process" << rank << " of " << n << endl;
    MPI_Finalize();

    return 0;
}
