#include <iostream>
#include <cassert>
using namespace std;
//selection sort
void selection_sort(int a[], int n)
{
    int i,j;
    for (i = 0; i < n; i++) {
        int min = i;
        for (j = i; j < n; j++) {
            if (a[min] > a[j])
                min = j;
        }
        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}
//insert sort
void insert_sort(int a[], int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++) {
        temp = a[i];
        for (j = i-1; j >=0; j--) {
            if (a[j] > temp)
                a[j+1] = a[j];
            else 
                break;
        }
        a[j+1] = temp;
    }
}
//bubble sort
void bubble_sort(int a[], int n)
{
    int i,j,temp;
    for (i = 1; i <= n; i++) {
        for (j = 0; j < n-i; j++) {
            if (a[j] > a[j+1]) {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
//quick sort
int partition(int a[], int start, int end)
{
    int guard = a[start];
    while (start < end) {
        while (start < end && a[end] >= guard) end--;
        if (start < end) a[start++] = a[end];
        while (start < end && a[start] <= guard) start++;
        if (start < end) a[end--] = a[start];
    }
    a[start] = guard;

    return start;
}
void quicksort(int a[], int start, int end)
{
    if(start >= end) return;
    int guard = partition(a, start, end);
    quicksort(a, start, guard-1);
    quicksort(a, guard+1, end);
}

//merge sort
void mergesort(int a[], int start, int end)
{
    if (start >= end ) return ;
    int mid = (start + end) / 2;
    mergesort(a, start, mid);
    mergesort(a, mid+1, end);

    int b[end-start+1];
    int i = start, j = mid + 1, k=0;
    while (k <= end-start) {
        if (i <= mid && j <=end ) {
            b[k++] = (a[i] <=  a[j]) ? a[i++] : a[j++];
        } else if (i <= mid) {
            b[k++] = a[i++];
        } else if (j <= end) {
            b[k++] = a[j++];
        }
    }

    for (k = 0; k <= end-start; k++) {
        a[start+k] = b[k];
    }
}
//merge sort without recursion
void merge(int a[], int b[], int start, int mid, int end)
{
    int i = start, j= mid+1, k=0;
    while (k <= end-start) {
        if (i <= mid && j <= end) {
            b[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
        } else if (i <= mid) {
            b[k++] = a[i++];
        } else if (j <= end) {
            b[k++] = a[j++];
        }
    }

    for (k = 0; k <= end-start; k++) {
        a[start+k] = b[k];
    }
}
void mergesort_v2(int a[], int n)
{
    int step, start;
    int b[n];
    for (step = 1; step < n; step *= 2) {
        start = 0;
        while (start + 2*step < n) {
            merge(a, b, start, start+step-1, start+step*2-1);
            start += 2*step;
        }

        if (start + step < n) {
            merge(a, b, start, start+step-1, n-1);
        }
    }
}

//heap sort
void heap_fixdown(int a[], int n, int pos)
{
    int change,temp;
    while (2*pos + 1 < n) {
        change = 2 * pos +1;
        if (change+1 < n && a[change] < a[change+1])
            change++;
        if (a[change] <= a[pos]) 
            break;
        temp = a[change];
        a[change] = a[pos];
        a[pos] = temp;
        pos = change;

    }
}
void heap_fixdown_v2(int a[], int n, int pos)
{
    int change,temp;
    while (2*pos + 1 < n) {
        change = 2 * pos +1;
        if (change+1 < n && a[change] > a[change+1])
            change++;
        if (a[change] >= a[pos]) 
            break;
        temp = a[change];
        a[change] = a[pos];
        a[pos] = temp;
        pos = change;

    }
}
void heap_sort(int a[], int n)
{
    int i,temp;
    for (i = n/2; i >= 0; i--) {
        heap_fixdown(a, n, i);
    }

    for (i = n-1 ; i >= 1; i--) {
       temp = a[i];
       a[i] = a[0];
       a[0] = temp;

       heap_fixdown(a, i, 0);
    }
}
//TEST
void print_array(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void do_sort()
{
    int a[] = {1,2,9,10 ,12,7,5,7,6};
    printf("before sort :");
    int len = sizeof(a)/sizeof(int);

    print_array(a, len);
    /*quicksort(a, 0, len - 1);
    printf("after quicksort:");
    print_array(a, len);
    */
    /*
    mergesort(a, 0, len-1);
    printf("after mergesort:");
    */
    /*
    selection_sort(a, len);
    printf("after selectionsort:");
    */
    /*
    insert_sort(a,len);
    printf("after selectionsort:");
    */
    /*
    bubble_sort(a,len);
    printf("after bubblesort:");
    */
    /*
    heap_sort(a,len);
    */
    mergesort_v2(a,len);
    printf("after mergesort_v2:");
    print_array(a, len);
    
}

//题14：输入一个数组，实现一个函数完成调整数组中元素位置，使所有奇数位于数组前半部分，偶数位于数组后半部分
void record_odd_even(int a[], int n)
{
    int start = 0, end = n-1;
    while (start < end) {
        while(start < end && a[start] % 2) 
            start++;
        while(start < end && a[end] % 2 == 0) 
            end--;
        if (start < end) {
            int temp = a[start];
            a[start] = a[end];
            a[end] = temp;
        }
    }
}
//题29：数组中有一个数字出现的次数超过数组长度的一半，找出这个数字
int more_than_half_num(int a[], int n)
{
    assert(a && n > 0);
    int middle = n >> 1;
    int pos = partition(a, 0, n-1);
    while (pos != middle) {
        if (pos > middle) {
            pos = partition(a, 0, pos-1);
        } else {
            pos = partition(a, pos+1, n-1);
        }
    }

    return a[middle];
}
//题30：给定一个有n个元素的数组，找出其中最小的k个数
void find_min_k_v1(int a[], int n, int output[], int k)
{
   assert(a && n > 0 && k > 0);
   int start = 0, end = n-1;
   int pos = partition(a, start, end);
   while (pos != k-1) {
       if (pos > k-1) {
           pos = partition(a,0, pos-1);
       }else {
           pos = partition(a, pos+1, n-1);
       }
   }
   int i;
   for (i = 0; i < k;i++) {
       output[i] = a[i];
   }
}

void find_min_k_v2(int a[], int n, int output[], int k)
{
    int i,j;
    for (i = 0; i < k; i++)
        output[i] = a[i];
    
    for (j = k/2; j >=0 ;j--)
        heap_fixdown(output,k,j);

    for (; i < n; i++) {
        if (a[i] < output[0]) {
            output[0] = a[i];
            heap_fixdown(output, k, 0);
        }
    }
    
}
//题26：在数组中如果前面一个数字大于后面一个数字，则这两个数字构成一个逆序对。输入一个数组，求出数组中逆序对的个数
int get_inverse_pairs(int a[], int copy[], int start ,int end)
{
    if (start >= end) return 0;
    int mid = (start + end) / 2;
    int left_count = get_inverse_pairs(a, copy, start, mid);
    int right_count = get_inverse_pairs(a, copy, mid+1, end);

    int i = start, j = mid + 1, k = 0, count = 0;
    while (k <= end-start) {
        if (i > mid) {
            copy[k+start] = a[j++];
        } else if (j > end) {
            copy[k+start] = a[i++];
        } else if (a[i] > a[j]) {
            count += mid-i+1;
            copy[k+start] = a[j++];
        } else {
            copy[k+start] = a[i++];
        }

        k++;
    }

    for(i = start; i <= end; i++) {
        a[i] = copy[i];
    }
    return left_count + right_count + count;
}
int main() 
{
    //do_sort();
    /*
    int a[] = {1,2,3,4,4,4,8,9,11,2,3};
    record_odd_even(a, sizeof(a)/sizeof(int));
    print_array(a, sizeof(a)/sizeof(int));
    */
    /*
    int a[] = {1,2,2,2,1,2,8,2,2,2,3};
    printf("more than half num is %d\n", more_than_half_num(a, sizeof(a)/sizeof(int)));
    */
    /*
    int a[] = {1,6,9,3,4,12,2,3,7,10};
    int k = 4;
    int output[k];
    find_min_k_v2(a, sizeof(a)/sizeof(int), output, k);
    print_array(output, k);
    */
    int a[] = {7, 5, 6, 4};
    int copy[4];
    printf("pairs is %d\n", get_inverse_pairs(a, copy, 0, sizeof(a)/sizeof(int) - 1));
    print_array(a, sizeof(a)/sizeof(int));
    return 0;
}

