# 1:

```c++
/*
static.cpp
*/
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

int a[20] = {0};

void dummy(){
    sleep(0.1);
}

int main(){
    int number = 1000;    //循环次数
    
    //int thread_count = strol(argv[1],null,10);
    double start,end,t;
    start = omp_get_wtime();
    #pragma omp parallel for num_threads(2) schedule(static,4)
    for(int i = 0; i < number; i++){
        a[i] = i;
        int my_rank = omp_get_thread_num();
        //printf("i = %d , This is thread %d of 4 . \n",i,my_rank);
        dummy();
    }
    end = omp_get_wtime();
    t = end - start;
    printf("static took me %lf sconds",t);
    return 0;
}
```

```c++
/*
dynamic.cpp
*/
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

int a[20] = {0};

void dummy(){
    sleep(0.1);
}

int main(){
    int number = 1000;    //循环次数
    
    //int thread_count = strol(argv[1],null,10);
    double start,end,t;
    start = omp_get_wtime();
    #pragma omp parallel for num_threads(2) schedule(dynamic,4)
    for(int i = 0; i < number; i++){
        a[i] = i;
        int my_rank = omp_get_thread_num();
        //printf("i = %d , This is thread %d of 4 . \n",i,my_rank);
        dummy();
    }
    end = omp_get_wtime();
    t = end - start;
    printf("static took me %lf sconds",t);
    return 0;
}
```

```c++
/*
guided.cpp
*/
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

int a[20] = {0};

void dummy(){
    sleep(0.1);
}

int main(){
    int number = 1000;    //循环次数
    
    //int thread_count = strol(argv[1],null,10);
    double start,end,t;
    start = omp_get_wtime();
    #pragma omp parallel for num_threads(2) schedule(guided,1)
    for(int i = 0; i < number; i++){
        a[i] = i;
        int my_rank = omp_get_thread_num();
        //printf("i = %d , This is thread %d of 4 . \n",i,my_rank);
        dummy();
    }
    end = omp_get_wtime();
    t = end - start;
    printf("static took me %lf sconds",t);
    return 0;
}
```



# 2:

```c++
/*
单个生产者单个消费者
*/
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;

vector<int> item;
omp_lock_t mylock;
const int number = 8;
int num = 0;

void producer(){
    for(int i = 0; i < number; i++){
        omp_set_lock(&mylock);
        item.push_back(num);
        printf("item %d was produced.\n",num);
        num ++;
        omp_unset_lock(&mylock);
        sleep(1);
    }
}

void consumer(){
    for(int i = 0; i < number; i++){
        sleep(1);
        if(item.size() != 0){ 
            omp_set_lock(&mylock);
            printf("item %d was comsumed.\n",item[item.size()-1]);
            item.pop_back();
            omp_unset_lock(&mylock);
        }
        else printf("there is no item.\n");
    }
}

int main(){
    #pragma omp parallel sections
    {
        #pragma omp section
        producer();
        #pragma omp section
        consumer();
    }
    return 0;
}
```

```c++
/*
2个生产者2个消费者
*/
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;

vector<int> item;
omp_lock_t mylock;
const int number = 8;
int num = 0;

void producer(){
    for(int i = 0; i < number; i++){
        omp_set_lock(&mylock);
        item.push_back(num);
        printf("item %d was produced.\n",num);
        num ++;
        omp_unset_lock(&mylock);
        sleep(1);
    }
}

void consumer(){
    for(int i = 0; i < number; i++){
        sleep(1);
        if(item.size() != 0){ 
            omp_set_lock(&mylock);
            printf("item %d was comsumed.\n",item[item.size()-1]);
            item.pop_back();
            omp_unset_lock(&mylock);
        }
        else printf("there is no item.\n");
    }
}

int main(){
    #pragma omp parallel sections
    {
        #pragma omp section
        producer();
        #pragma omp section
        consumer();
        #pragma omp section
        producer();
        #pragma omp section
        consumer();
    }
    return 0;
}
```





