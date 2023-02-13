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
vector<int> cum(1000, 0);
int sum = 0;
int num = 0;
void* f(void *a){
        A * b = (A*) a;
	int t = 0,t1 = 0;
	for(int i = 0; i < 1000; i ++){
			t = t +((*(b->a))[0][i]) * ((*(b->b))[i][0]);
			}
	for(int i = 0; i < 1000; i ++){
			t1 = t1 +((*(b->a))[1][i]) * ((*(b->b))[i][0]);
			}
	cum[2*(*(b->i))] = t;
	cum[2*(*(b->i)) + 1] = t1;
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
	pthread_t thread[500];
	vector<vector<int> > a1(2,ori1);	
	for(int i = 0; i < 500 ;i ++){

	a1[0] = a[2*i];
	a1[1] = a[2*i + 1];
	A *aa = new A(a1,b, i);
	pthread_create(&thread[i], NULL,f, (void*)aa);
		}
	pthread_t th;
	pthread_create(&th, NULL, SUM, NULL);
	pthread_join(th,NULL);
	cout << sum;
	}
		
		
	




