#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <vector>
using namespace std;
class A{
	public:
		vector<vector<int> > *a;
		vector<vector<int> > *b;
		int* i;
		A(vector<vector<int> > a1,vector<vector<int> > b1 ,int i1){
			a = new vector<vector<int> >(a1);
			b = new vector<vector<int> >(b1);
			i = new int(i1);
		}
		~A(){}
};
vector<int> res(1000, 0);	//运算结果
void* f(void *a){
    A* b = (A*) a;
	int t = 0;
	for(int i = 0; i < 1000; i ++){
		t = t +((*(b->a))[0][i]) * ((*(b->b))[i][0]);
	}
	res[*(b->i)] = t;
}	

int main(){
	vector<int> ori1(1000,1);
	vector<vector<int> > a(1000,ori1);	//矩阵a 1000*1000
	vector<int> ori2(1,1);
	vector<vector<int> > b(1000,ori2);	//矩阵b	1000*1
	pthread_t thread[1000];				//1000个线程

	vector<vector<int> > a1(1,ori1);	//记录矩阵a的每一行，临时变量1*1000
	for(int i = 0; i < 1000 ;i ++){		//遍历矩阵a的1000行
		a1[0] = a[i];
		A *c = new A(a1,b, i);			//a1与b相乘
		pthread_create(&thread[i], NULL,f, (void*)c);
	}
	for(int i = 0; i  < 1000; i ++){
		pthread_join(thread[i], NULL);
	}
}
