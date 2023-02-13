#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

int a[20] = {0};

void dummy(){
    sleep(0.1);
}

int main(){
    int number = 12;    //循环次数
    
    //int thread_count = strol(argv[1],null,10);
    double start,end,t;
    start = omp_get_wtime();
    #pragma omp parallel for num_threads(4) schedule(dynamic,2)
    for(int i = 0; i < number; i++){
        a[i] = i;
        int my_rank = omp_get_thread_num();
        printf("i = %d , This is thread %d of 4 . \n",i,my_rank);
        dummy();
    }
    end = omp_get_wtime();
    t = end - start;
    //printf("static took me %lf sconds",t);
    return 0;
}