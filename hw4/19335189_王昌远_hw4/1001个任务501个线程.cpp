#include <pthread.h>
#include <unistd.h>
#include<iostream>
#include<vector>
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
class C{
	public:
		A *a;
		A *b;
		C(A* a, A* b){
			this -> a = a;
			this -> b = b;
			}
	        ~C(){}
			
};
vector<int> cum(1000, 0);
int num = 0;
int sum = 0;
void f(A *b){
	int t = 0;
	for(int i = 0; i < 1000; i ++){
			t = t +((*(b->a))[0][i]) * ((*(b->b))[i][0]);
			}
	cum[*(b->i)] = t;
	
	}	
void* f1(void *a){
        C * b = (C*) a;
	int t = 0;
	for(int i = 0; i < 500; i ++){
			f(b -> a);
			f(b -> b);
			}


	num ++;
	}	
void* SUM(void * a){
	while(num != 500){}
	for(int i = 0; i  < 1000;  i++){
		sum += cum[i];
		}
		}	
int main(){
	vector<int> ori1(1000,1);
	vector<vector<int> > a(1000,ori1);
	vector<int> ori2(1,1);
	vector<vector<int> > b(1000,ori2);
	pthread_t thread[1000];
	vector<vector<int> > a1(1,ori1);
	vector<vector<int> > a2(1,ori1);
		
	for(int i = 0; i < 500 ;i = i + 1){

	a1[0] = a[2 * i];
	a2[0] = a[2 * i + 1];
	A *aa1 = new A(a1,b, 2*i);
	A *aa2 = new A(a2,b, 2*i+ 1);
	C *bb = new C(aa1,aa2);
	pthread_create(&thread[i], NULL,f1, (void*)bb);
		}
	pthread_t th;
	pthread_create(&th, NULL, SUM, NULL);
	pthread_join(th,NULL);
	cout << sum;
	}
		
		
	




