
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

extern int BinarySearch_Floor(void* arr, int elem_size, int elem_num, void* target, cmpfunc_p cmpfunc);
extern int BinarySearch_Ceil(void* arr, int elem_size, int elem_num, void* target, cmpfunc_p cmpfunc);


/*
 * Public functions
 */
int BinarySearch_Floor(void* arr, int elem_size, int elem_num, void* target, cmpfunc_p cmpfunc){
    int start = 0;
    int end = elem_num - 1;
    int mid;
    while (start + 1 < end) {
        mid = start + (end - start)/2;
        int ret = cmpfunc((char*)arr + mid*elem_size, target);
        if(ret == 0)
            end = mid;
        else if (ret < 0)
            start = mid;
        else
            end = mid;
    }

    if(cmpfunc((char*)arr + start*elem_size, target) == 0)
        return start;

    if(cmpfunc((char*)arr + end*elem_size, target) == 0)
        return end;

    if(cmpfunc((char*)arr, target) > 0)
        return -1;

    if(cmpfunc((char*)arr + (elem_num-1)*elem_size, target) < 0)
        return elem_num-1;

    return start;
}


int BinarySearch_Ceil(void* arr, int elem_size, int elem_num, void* target, cmpfunc_p cmpfunc){
    int start = 0;
    int end = elem_num - 1;
    int mid;
    while (start + 1 < end) {
        mid = start + (end - start)/2;
        int ret = cmpfunc((char*)arr + mid*elem_size, target);
        if(ret == 0)
            start = mid;
        else if (ret < 0)
            start = mid;
        else
            end = mid;
    }

    if(cmpfunc((char*)arr + end*elem_size, target) == 0)
        return end;

    if(cmpfunc((char*)arr + start*elem_size, target) == 0)
        return start;

    if(cmpfunc((char*)arr, target) > 0)
        return 0;

    if(cmpfunc((char*)arr + (elem_num-1)*elem_size, target) < 0)
        return elem_num;

    return end;
}


/*
 * Private functions
 */
