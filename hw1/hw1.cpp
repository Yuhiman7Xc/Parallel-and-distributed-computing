#include<windows.h>
#include<iostream>
#include<vector>
#include<time.h>
using namespace std;

const int num_of_cpus = 10;  //  cores
int M=0,N;
vector<int> value;
long long int sum = 0;
bool mutex = 0;

struct ThreadParam {
    int begin;
    int end;
    ThreadParam(int _begin, int _end):begin(_begin),end(_end){}
};

DWORD WINAPI ThreadFunc(LPVOID param){
    ThreadParam* p = static_cast<ThreadParam*>(param);
    long long int local_sum=0;
    for(int i = p->begin; i < p->end; i++){//�����
        //f(i);   //�̺߳���
        
        local_sum +=value[i];
    }
    
    if(!mutex){
        mutex = true;
        sum += local_sum;
        mutex = false;
    }

    delete p;
    return 0;
}

int main(){
    long long int number;   
    cout << "������������"; //���8��0
    cin >> number;
    for(int i = 0; i < number; i++){//number���������
        value.push_back(i+1);
    }
    N=number;

    clock_t start, finish;
    double duration;

    start = clock();
    HANDLE Threads[num_of_cpus];
    for(int i = 0; i < num_of_cpus; i++){
        ThreadParam* p = new ThreadParam(M+i*N/num_of_cpus, M+i*N/num_of_cpus+N/num_of_cpus);
        //��ÿ��CPU��������
        Threads[i] = CreateThread(NULL,0,ThreadFunc,p,0,NULL);
        //�����߳�
    }
    WaitForMultipleObjects(num_of_cpus,Threads,true,INFINITE);
    finish = clock();

    duration = (double)(finish - start)/(CLOCKS_PER_SEC*num_of_cpus);
    cout << sum << endl;
    cout << "������ʱ:" << duration << "��" << endl;

    long long int sum2 = 0;
    start = clock();
    for(int i = 0; i < number; i++){
        sum2 += value[i];
    }
    finish = clock();

    duration = (double)(finish - start)/CLOCKS_PER_SEC;
    cout << sum2 << endl;
    cout << "������ʱ:" << duration << "��" <<endl;

    return 0;
}