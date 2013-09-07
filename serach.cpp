#include <iostream>
#include <cassert>
using namespace std;

int binary_serach(int a[], int start, int end, int num)
{
    int mid;
    while (start <= end) {
        mid = (start + end) / 2;
        if (a[mid] > num) {
            end = mid - 1;
        } else if(a[mid] < num) {
            start = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}
//题3: 二维数组中的查找：二维数组中，每行都按从左到右递增的顺序排序，每一列都按从上到下递增的顺序排。
//现在输入一个二维数组和一个整数，判断数组中是否含有整数
bool find_num(int **a, int cols, int rows, int num)
{
    assert(a && cols > 0 && rows > 0);
    int row = 0, col = cols-1;

    while ( row < rows && col >= 0) {
        if (a[row][col] > num) {
            col--;
        } else if(a[row][col] < num){
            row++;
        } else {
            return true;
        }
    }

    return false;
}
int main() 
{
    return 0;
}

