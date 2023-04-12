/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

 /* This is an interactive version of cpi */
/*/
#include "mpi.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;


int main(int argc, char* argv[]) {

    int rank, value =7777, n;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    if (rank == 0)
    {
        cin >> value;
        MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0,  MPI_COMM_WORLD, &status);
        value++;
        if (rank < n - 1)
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }
    cout << "Process " << rank << " got " << value << endl;
    MPI_Finalize();

    return 0;
}
/**/

#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Задача 1: передача данных от процесса i к процессу j
    int i = 0, j = size - 1;
    if (rank == i) {
        std::string data = "some data to send";
        MPI_Send(data.c_str(), data.size() + 1, MPI_CHAR, j, 0, MPI_COMM_WORLD);
    }
    else if (rank == j) {
        char buffer[256];
        MPI_Recv(buffer, 256, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Received data: " << buffer << std::endl;
    }

    // Задача 2: передача различных данных каждому процессу с большим номером
    for (int j = rank + 1; j < size; j++) {
        std::string data = "data for process " + std::to_string(j);
        MPI_Send(data.c_str(), data.size() + 1, MPI_CHAR, j, 0, MPI_COMM_WORLD);
        std::cout << "Sent data: " << data << " from process " << rank << " to process " << j << std::endl;
    }

    for (int i = 0; i < rank; i++) {
        char buffer[256];
        MPI_Recv(buffer, 256, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Received data: " << buffer << " at process " << rank << std::endl;
    }

    MPI_Finalize();
    return 0;
}