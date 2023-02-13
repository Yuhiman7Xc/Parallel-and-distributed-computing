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
int num = 0;
vector<int> cum(1000, 0);
int sum = 0;
void* f(void *a){
        A * b = (A*) a;
	int t = 0;
	for(int i = 0; i < 1000; i ++){
			t = t +((*(b->a))[0][i]) * ((*(b->b))[i][0]);
			}
	cum[*(b->i)] = t;
        num ++;
	
	}	
void* SUM(void * a){
	while(num != 1000){}
	for(int i = 0; i  < 1000;  i++){
		sum += cum[i];
		}
		}	
int main(){
	pthread_t thread[1000];
	vector<int> ori1(1000,1);
	vector<vector<int> > a(1000,ori1);
	vector<int> ori2(1,1);
	vector<vector<int> > b(1000,ori2);
	//subproblems
	vector<vector<int> > a1(1,ori1);
	for(int i = 0; i < 1000 ;i ++){
		a1[0] = a[i];
		A *aa = new A(a1,b, i);
		//assignment
		pthread_create(&thread[i], NULL,f, (void*)aa);
		}
	pthread_t th;
	pthread_create(&th, NULL, SUM, NULL);
	pthread_join(th,NULL);
	cout << sum;
	}
		
		
	




