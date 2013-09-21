#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

//等概率产生整数1-m
int random_m(int m) 
{
    srand(time(NULL));
    return rand() % m + 1;
}
// m >= n 情况下使用random_m编写函数random_n，等概率随机产生1-n
int random_n_v1(int m, int n)
{
    int v;
    do {
        v = random_m(m)
    } while ( v > n)
    
    return v;
}
// m < n && m*m >= n
int random_n_v2(int m, int n)
{
    int v;
    int t = (m * m)/n * n;

    do {
        v = random_m(m) + (random_m(m)-1)*m
    } while (v > t);
    return v % n + 1;
}

//已知随机函数rand_01()，以p的概率产生0，以1-p的概率产生1，现在要求设计一个新的随机函数newRand()，使其以1/n的等概率产生1~n之间的任意一个数
int rand_01()
{
    if (rand() % 3 == 0) {
        return 0;
    } else {
        return 1;
    }
}
int rand_01_in_same_probablity()
{
    int v1 = rand_01();
    int v2 = rand_01();
    if (v1 == 0 && v2 == 1)
        return 0;
    else if(v1 == 1 && v2 == 0)
        return 1;
    else
        return rand_01_in_same_probablity();
}
int new_rand_1_to_n(int n)
{
    int k = 1 + log(n)/log(2);
    int result = 0, i;
    for (i = 0; i < k;i++) {
        if (rand_01_in_same_probablity() == 1)
            result |= 1<<i;
    }
    if (result == 0 || result > n) return new_rand_1_to_n(n);
    return result;
}
//均匀洗牌算法
//n-1位置，每个数出现的概率是1/n, n-2位置,每个数出现概率1/(n-1) * (1-1/n) = 1/n
void shuffle(int a[], int n)
{
    int i ,tmp;
    for (i = n-1; i >= 0; i--) {
        int r = rand() % (i+1);
        temp = a[i];
        a[i] = a[r];
        a[r]= temp;
    }
}

//程序的输入包含两个整数m和n，其中m<n。输出是0~n-1范围内m个随机整数的有序列表，不允许重复。
void generate(int m, int n)
{
    int i;
    int t = m;
    for (i = 0; i < n ; i++) {
        int r = rand() % (n-i);
        if (r < t) {
            printf("%d\n", i);
            t--;
        }
    }
}
int main() 
{
    return 0;
}

