#include <iostream>
#include <cassert>
using namespace std;

//题10：输入一个整数，求出整数的二进制中1的个数
int number_of_1(int num)
{
    int count = 0;
    while (num) {
        count++;
        num = num & (num-1);
    }

    return count;
}
//题40：一个整型数组里除了两个数字之外，其它数字都出现了2遍，找出这两个数字
void find_num_appear_once(int a[], int n)
{
    assert(a && n >0);
    int xor_value = 0 ,i;
    for (i = 0; i < n; i++) {
        xor_value ^= a[i];
    }

    int first_1_bit_position = 0;
    if (xor_value & 0x1 == 0) {
        first_1_bit_position++;
        xor_value >>= 1;
    }

    int num1 = 0, num2 = 0;
    for (i = 0; i< n; i++) {
        if (a[i] & (0x1<<first_1_bit_position)) {
            num1 ^= a[i];
        } else {
            num2 ^= a[i];
        }
    }

    printf("two numbers are %d and %d\n", num1, num2);
}
int main() 
{
    printf("num of 1 in -1 is %d\n", number_of_1(-1)); // -1 FF FF FF FF
    int a[] = {1,2,3,4,5,6,7,7,5,4,3,2};
    find_num_appear_once(a, sizeof(a)/sizeof(int));
    return 0;
}

