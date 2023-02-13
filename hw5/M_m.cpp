#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <omp.h>
#include <time.h>
using namespace std;

omp_lock_t mylock;
int sum = 0;

int main(int argc, char *argv[])
{
    vector<vector<double> > m;  //假设m存放的是存进来的矩阵 x*y
    vector<double> v;           //v为向量 y*1
    vector<double> ans;         //存放结果 x*1

    int m_x = m.size();        //矩阵宽度
    int m_y = m[0].size();     //矩阵长度
    int v_l = v.size();        //向量长度

    #pragma omp parallel for num_threads(4) private(i)
    for(int i = 0; i < m_x; i++){
        omp_set_lock(&mylock);
        for(int j = 0; j < m_y; j++){
            for(int k = 0; k < v_l; k++){
                sum += m[i][j]*v[k];
            }
        }
        ans.push_back(sum);
        sum = 0;
        omp_unset_lock(&mylock);
    }
}