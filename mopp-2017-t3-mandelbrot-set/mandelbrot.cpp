#include <complex>
#include <iostream>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <assert.h>
#include <stdio.h>

using namespace std;

int max_row, max_column, max_n, cpus;
char **mat;

void *calculate (void * arg)
{
        int id_deref= (intptr_t) arg;
        
        // divide the problem set into "cpus" partitions
        for(int r = id_deref * max_row/cpus; r < (id_deref + 1) * max_row / cpus; ++r)
        {
                for(int c = 0; c < max_column; ++c)
                {
                        complex<float> z= 0;
                        int n = 0;
                        while(abs(z) < 2.0 && ++n < max_n)
                                z = z*z + complex<float>(
                                        (float)c * 2 / max_column - 1.5,
                                        (float)r * 2 / max_row - 1
                                );
                        mat[r][c]=(n == max_n ? '#' : '.');     //assign # to r,c position if absolute val of z is still in bounds after max_n iterations
                }
        }

}


int main(){
        int id = 0, i=0;                //declaring ID var for thread later used
	cpus = get_nprocs();            //get the number of cpus
        cin >> max_row;                 //input row size
        cin >> max_column;              //input column size
        cin >> max_n;                   //input total iterations

        if (getenv("MAX_CPUS")) 
        {
                 cpus = atoi(getenv("MAX_CPUS"));
        }
        // Sanity-check
        assert(cpus > 0 && cpus <= 64);
        fprintf(stderr, "Running on %d CPUs\n", cpus);

        pthread_t thread[cpus];         //declare total threads.

        // Allocating memory to 2D array
        mat = (char**)malloc(sizeof(char*)*max_row);
        for (i=0; i<max_row;i++)
                mat[i]=(char*)malloc(sizeof(char)*max_column);

        // Create threads and use thread id (0 to cpus) as argument in calculate func.
        for (i = 0; i < cpus; i++)
        {
                pthread_create(&thread[i], NULL, calculate, (void*)(intptr_t) id); // we cannot conver int to void* without warning due to size mismatch. So use intptr_t.
                id++;
        }

        // Thread join
        for (i = 0; i < cpus; i++) 
        {
                pthread_join(thread[i], NULL);
        }

        // Print the result
        for(int r = 0; r < max_row; ++r){
                for(int c = 0; c < max_column; ++c)
                        std::cout << mat[r][c];
                cout << '\n';
        }
}
