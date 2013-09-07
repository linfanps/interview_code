#include <iostream>
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
int main() 
{
    do_sort();
    return 0;
}

