
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int IntCompare(void* a, void* b){
    return *(int*)a - *(int*)b;
}

int main(int argc, char *argv[])
{
    int arr[20] = {2,2,4,4,6,6,6,8,10,10,12,12,14,14,16,16,18,18,20,20};
    int target = 5;
    int result_f = BinarySearch_Floor(arr, sizeof(int), 20, &target, IntCompare);
    int result_c = BinarySearch_Ceil(arr, sizeof(int), 20, &target, IntCompare);

    printf("target:%d\nfound: arr[%d - %d]\n", target,result_f, result_c);
    return 0;
}
