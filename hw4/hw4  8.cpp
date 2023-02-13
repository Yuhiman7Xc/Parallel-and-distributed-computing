#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

class Matirx{
	public:
		vector<vector<int> > *a;
		vector<vector<int> > *b;
		int* i;
		Matirx(vector<vector<int> > a1,vector<vector<int> > b1 ,int i1){
			a = new vector<vector<int> >(a1);
			b = new vector<vector<int> >(b1);
			i = new int(i1);
		}
		~Matirx(){}
};
vector<int> res(1000, 0);	//运算结果
void* f1(void *a){
    Matirx* b = (Matirx*) a;
	int t = 0;
	for(int i = 0; i < 1000; i ++){
		t = t +((*(b->a))[0][i]) * ((*(b->b))[i][0]);
	}
	res[*(b->i)] = t;
}	

int main(){
	vector<int> task1(1000,1);
	vector<vector<int> > a(1000,task1);	//矩阵a 1000*1000
	vector<int> task2(1,1);
	vector<vector<int> > b(1000,task2);	//矩阵b	1000*1
	pthread_t thread[8];				//8个线程

	clock_t start_t,end_t;
	double total_t;
	vector<vector<int> > a1(1,task1);	//记录矩阵a的每一行，临时变量1*1000
	start_t = clock();
	for(int i = 0; i < 1000 ;i ++){		//遍历矩阵a的1000行
		a1[0] = a[i];
		Matirx *A = new Matirx(a1,b, i);			//a1与b相乘
		pthread_create(&thread[i%8], NULL,f1, (void*)A);
	}
	for(int i = 0; i  < 8; i ++){
		pthread_join(thread[i], NULL);
	}
	end_t = clock();
	total_t = (end_t - start_t);
	cout << "time = " << (double)(total_t/CLOCKS_PER_SEC) << endl;
}
