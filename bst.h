#ifndef BST_H
#define BST_H

typedef int (*cmpfunc_p)(void*, void*);


extern int BinarySearch_Floor(void* arr, int elem_size, int elem_num, void* target, cmpfunc_p cmpfunc);
extern int BinarySearch_Ceil(void* arr, int elem_size, int elem_num, void* target, cmpfunc_p cmpfunc);


#endif
