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
//题8：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
//输入一个排好序的数组的一个旋转，输出旋转数组的最小元素。例如数组{3, 4, 5, 1, 2}为{1, 2, 3, 4, 5}的一个旋转，该数组的最小值为1
int find_min(int a[], int n)
{
    assert(a && n > 0);
    int mid, left = 0, right = n -1;
    while (a[left] >= a[right]) {
        if (right - left == 1) {
            return a[right];
        }
        mid = (left + right) / 2;
        //1 0 1 1 1 this situation
        if (a[left] == a[right] && a[left] == a[mid]) {
            int min =  a[left], i;
            for (i = left + 1 ; i <= right; i++) {
                if (a[i] < min) min = a[i];
            }
            return min;
        }

        if (a[mid] >= a[left])
            left = mid;
        else if (a[mid] <= a[right])
            right = mid;
    }
}
//题38：统计一个数字在排序数组中出现的次数
int get_first_k_position(int a[], int length, int start, int end, int k)
{
    if (end < start) return -1;
    int mid = (start + end) / 2;
    if (a[mid] == k) {
        if (mid == 0 ||
            (mid > 0 && a[mid-1] != k)) {
            return mid;
        } else {
            end = mid-1;
        }
    } else if (a[mid] > k) {
        end = mid - 1;
    } else {
        start = mid +1;
    }

    return get_first_k_position(a, length, start, end, k);
}
int get_last_k_position(int a[], int length, int start, int end, int k)
{
    if (end < start) return -1;
    int mid = (start + end) / 2;
    if (a[mid] == k) {
        if (mid == length-1 ||
            (mid < length-1  && a[mid+1] != k)) {
            return mid;
        } else {
            start = mid + 1;
        }
    } else if (a[mid] > k) {
        end = mid - 1;
    } else {
        start = mid +1;
    }

    return get_last_k_position(a, length,start, end, k);
}
int get_num_of_k(int a[], int n, int k)
{
    assert(a && n>0);
    int first = get_first_k_position(a, n,  0, n-1, k);
    int last = get_last_k_position(a, n, 0, n-1,k);
    if (first == -1 && last == -1) {
        return 0;
    } else {
        return last-first+1;
    }
}

//题41：输入一个已经按升序排序过的任意实数数组和一个数字，在数组中查找两个数，使得它们的和正好是输入的那个数字
void find_number_with_sum(int a[], int n, int sum) 
{
    assert(a);
    int start = 0, end = n-1;
    while (start < end) {
        int v = a[start] + a[end];
        if (v > sum) {
            end --;
        } else if (v < sum) {
            start++;
        } else {
            printf("two nums are %d and %d\n", a[start], a[end]);
            start++;
            end--;
        }
    }
}
//题41.2：输入一个正数n，输出所有和为n连续正数序列
void find_continous_sequence(int num)
{
    if (num < 3) return;
    int low = 1, high =2;
    int half = (num+1)/2;
    int sum = low + high;
    while (low <= half) {
        if (sum == num) {
            int i ;
            for (i = low; i <=high; i++)
                printf("%d ", i);
            printf("\n");

            sum -= low;
            low++;
        } else if (sum > num) {
            sum -= low;
            low++;
        } else {
            high++;
            sum += high;
        }
    }
}
//中位数：求两个有序数组合并后的中位数，两个数组等长
int find_median(int a[], int b[], int n)
{
    assert(a && b && n > 0);
    if (n == 1)
        return a[0] > b[0] ? b[0] : a[0];
    int middle = (n-1)/2; //n为偶数，取坐标小的，奇数，取中间

    if (a[middle] == b[middle]) {
        return a[middle];
    } else if (a[middle] > b[middle]) {
        return find_median(a, b+n-middle-1, middle+1);
    } else {
        return find_median(a+n-middle-1, b, middle+1);
    }
}
//中位数：求两个有序数组合并后的中位数，两个数组不等长
int find_median_random_length(int a[], int na, int b[], int nb)
{
    int ma = na / 2;
    int mb = nb / 2;
    int l = (ma > mb) ? mb : ma;

    if (na == 1) {
        if (nb % 2 == 0) {
            if (a[0] >= b[mb]) return b[mb];
            else if (a[0] <= b[mb-1]) return b[mb-1];
            else  return a[0];
        } else {
            return b[mb];
        }
    }

    if (nb == 1) {
        if (na % 2 == 0) {
            if (b[0] >= a[ma]) return a[ma];
            else if (b[0] <= a[ma-1]) return a[ma-1];
            else return b[0];
        }else {
            return a[ma];
        }
    }

    if (a[ma] == b[mb]) {
        return a[ma];
    } else if (a[ma] > b[mb]) {
        return find_median_random_length(a, na-l, b+mb, nb-l);
    } else {
        return find_median_random_length(a+ma, na-l, b, nb-l);
    }
}
int main() 
{
    /*题8
    int a[] = {1,0,1,1,1};
    printf("min=%d\n", find_min(a, sizeof(a)/sizeof(int)));
    */
    /*
    int a[] = {1,2,3,3,3,3,3,3,4,5,6,7};
    printf("num of 3 is %d\n", get_num_of_k(a, sizeof(a)/sizeof(int), 3));
    */
    /*
    int a[] = {1,3,4,5,7,11,13,17};
    find_number_with_sum(a, sizeof(a)/sizeof(int), 18);
    */
    /*
    find_continous_sequence(15);
    */
    int a[] = {1,3,4,5,10,12};
    int b[] = {2,6,8,10,13,15};
    printf("median is %d\n", find_median(a, b, sizeof(a)/sizeof(int)));
    return 0;
}

