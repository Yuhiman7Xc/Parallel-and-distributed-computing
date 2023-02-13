#include <bits/stdc++.h>
#include <ctime>

using namespace std;

void matrixAdd(int **a,int **b,int **c,int n){
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            c[i][j] = a[i][j] + b[i][j];
}

void matrixSub(int **a,int **b,int **c,int n){
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            c[i][j] = a[i][j] - b[i][j];
}

// 用strassen算法计算矩阵a与b的乘积，储存在矩阵c中
// 输入：矩阵a，b，c，矩阵维数n
void matrixMulti(int **a,int **b,int **c,int n){
    //解决最小子问题
    if(n==2){
        c[0][0] = a[0][0]*b[0][0]+a[0][1]*b[1][0];
        c[0][1] = a[0][0]*b[0][1]+a[0][1]*b[1][1];
        c[1][0] = a[1][0]*b[0][0]+a[1][1]*b[1][0];
        c[1][1] = a[1][0]*b[0][1]+a[1][1]*b[1][1];
        return;
    }else{
        //各个中间量矩阵，大小均为n/2
        //a，b，c的四个分块
        int** a11;
        int** a12;
        int** a21;
        int** a22;
        
        int** b11;
        int** b12;
        int** b21;
        int** b22;
        
        int** c11;
        int** c12;
        int** c21;
        int** c22;
        //strassen算法的7个分块
        int** p1;
        int** p2;
        int** p3;
        int** p4;
        int** p5;
        int** p6;
        int** p7;
        //计算h过程的中间量
        int** as;
        int** bs;
        
        //为中间量矩阵动态分配内存空间
        a11 = new int *[n/2];
        a12 = new int *[n/2];
        a21 = new int *[n/2];
        a22 = new int *[n/2];
        
        b11 = new int *[n/2];
        b12 = new int *[n/2];
        b21 = new int *[n/2];
        b22 = new int *[n/2];
        
        c11 = new int *[n/2];
        c12 = new int *[n/2];
        c21 = new int *[n/2];
        c22 = new int *[n/2];
        
        p1 = new int *[n/2];
        p2 = new int *[n/2];
        p3 = new int *[n/2];
        p4 = new int *[n/2];
        p5 = new int *[n/2];
        p6 = new int *[n/2];
        p7 = new int *[n/2];
        
        as = new int *[n/2];
        bs = new int *[n/2];
        for(int i = 0;i < n/2;i++){
            a11[i] = new int [n/2];
            a12[i] = new int [n/2];
            a21[i] = new int [n/2];
            a22[i] = new int [n/2];
            
            b11[i] = new int [n/2];
            b12[i] = new int [n/2];
            b21[i] = new int [n/2];
            b22[i] = new int [n/2];
            
            c11[i] = new int [n/2];
            c12[i] = new int [n/2];
            c21[i] = new int [n/2];
            c22[i] = new int [n/2];
            
            p1[i] = new int [n/2];
            p2[i] = new int [n/2];
            p3[i] = new int [n/2];
            p4[i] = new int [n/2];
            p5[i] = new int [n/2];
            p6[i] = new int [n/2];
            p7[i] = new int [n/2];
            
            as[i] = new int [n/2];
            bs[i] = new int [n/2];
        }
        
        //分割输入矩阵a和b
        for(int i = 0;i < n/2;i++){
            for(int j = 0; j < n/2;j++){
                a11[i][j] = a[i][j];
                a12[i][j] = a[i][j+n/2];
                a21[i][j] = a[i+n/2][j];
                a22[i][j] = a[i+n/2][j+n/2];
                
                b11[i][j] = b[i][j];
                b12[i][j] = b[i][j+n/2];
                b21[i][j] = b[i+n/2][j];
                b22[i][j] = b[i+n/2][j+n/2];
            }
        }
        
        //计算p1～p7
        matrixAdd(a11, a22, as, n/2);
        matrixAdd(b11, b22, bs, n/2);
        matrixMulti(as, bs, p1, n/2);
        
        matrixAdd(a21, a22, as, n/2);
        matrixMulti(as, b11, p2, n/2);
        
        matrixSub(b12, b22, bs, n/2);
        matrixMulti(a11, bs, p3, n/2);
        
        matrixSub(b21, b11, bs, n/2);
        matrixMulti(a22, bs, p4, n/2);
        
        matrixAdd(a11, a12, as, n/2);
        matrixMulti(as, b22, p5, n/2);
        
        matrixSub(a21, a11, as, n/2);
        matrixAdd(b11, b12, bs, n/2);
        matrixMulti(as, bs, p6, n/2);
        
        matrixSub(a12, a22, as, n/2);
        matrixAdd(b21, b22, bs, n/2);
        matrixMulti(as, bs, p7, n/2);
        
        //计算c的各个分块
        matrixAdd(p1, p4, as, n/2);
        matrixSub(p7, p5, bs, n/2);
        matrixAdd(as, bs, c11, n/2);
        
        matrixAdd(p3, p5, c12, n/2);
        
        matrixAdd(p2, p4, c21, n/2);
        
        matrixAdd(p1, p3, as, n/2);
        matrixSub(p6, p2, bs, n/2);
        matrixAdd(as, bs, c22, n/2);
        
        //将小矩阵组合为大矩阵c
        for(int i = 0;i < n/2;i++)
            for(int j = 0;j < n/2;j++){
                c[i][j] = c11[i][j];
                c[i+n/2][j] = c21[i][j];
                c[i][j+n/2] = c12[i][j];
                c[i+n/2][j+n/2] = c22[i][j];
            }
        
        //回收分配的内存空间
        for(int i = 0;i < n/2;i++){
            delete[] a11[i];
            delete[] a12[i];
            delete[] a21[i];
            delete[] a22[i];
            
            delete[] b11[i];
            delete[] b12[i];
            delete[] b21[i];
            delete[] b22[i];
            
            delete[] c11[i];
            delete[] c12[i];
            delete[] c21[i];
            delete[] c22[i];
            
            delete[] p1[i];
            delete[] p2[i];
            delete[] p3[i];
            delete[] p4[i];
            delete[] p5[i];
            delete[] p6[i];
            delete[] p7[i];
            
            delete[] as[i];
            delete[] bs[i];
        }
        delete[] a11;
        delete[] a12;
        delete[] a21;
        delete[] a22;
        
        delete[] b11;
        delete[] b12;
        delete[] b21;
        delete[] b22;
        
        delete[] c11;
        delete[] c12;
        delete[] c21;
        delete[] c22;
        
        delete[] p1;
        delete[] p2;
        delete[] p3;
        delete[] p4;
        delete[] p5;
        delete[] p6;
        delete[] p7;
        
        delete[] as;
        delete[] bs;
    }
}

template <typename T>
void NormalMul(T **  MatrixA, T ** MatrixB, T ** MatrixResult, int size)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			MatrixResult[i][j] = 0;
			for(int k = 0; k < size; k++)
				MatrixResult[i][j] += MatrixA[i][k] * MatrixB[k][j];
		}
	}
}

// 测试数据:的300*300矩阵
int main(){
    int** a;
    int** b;
    int** c;
    int** d;
    int n = 300;
    a = new int *[n];
    b = new int *[n];
    c = new int *[n];
    d = new int *[n];
    for(int i = 0;i < n;i++){
        a[i] = new int [n];
        b[i] = new int [n];
        c[i] = new int [n];
        d[i] = new int [n];
    }
    int cnt = 0;
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++){
            a[i][j] = cnt;
            b[i][j] = cnt;
            cnt++;
        }

    long startTime_normal, endTime_normal;
	long startTime_strasse, endTime_strassen;
    
    cout << "Strassen算法开始时间：" << (startTime_strasse= clock()) << endl;
    matrixMulti(a, b, c, n);
    cout << "Strassen算法结束时间：" << (endTime_strassen = clock()) << endl;
    cout << "总时间:" << endTime_strassen-startTime_strasse << endl;

    cout << "朴素算法开始时间：" << (startTime_normal = clock()) << endl;
	NormalMul(a, b, d, n);
	cout << "朴素算法结束时间：" << (endTime_normal = clock()) << endl;
	cout << "总时间:" << endTime_normal-startTime_normal << endl;
    
    /*
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }
    */
}
