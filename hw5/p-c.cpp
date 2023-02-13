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