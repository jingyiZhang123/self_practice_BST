#ifndef BST_H
#define BST_H

#include <stdbool.h>
typedef int (*cmpfunc_p)(void*, void*);
typedef void (*operation_p)(void*);

// Binary Search APIs
extern int BinarySearch_Floor(void* arr, int elem_size, int elem_num, void* target, cmpfunc_p cmpfunc);
extern int BinarySearch_Ceil(void* arr, int elem_size, int elem_num, void* target, cmpfunc_p cmpfunc);



// Binary Search Tree APIs
typedef struct Node Node_t;
typedef Node_t* Node_p;

struct Node{
    void* key;
    void* value;

    Node_p left_child;
    Node_p right_child;

};


typedef struct BST BST_t;
typedef BST_t* BST_p;

struct BST{
    Node_p root;
    int num_node;

    int key_size;
    int value_size;

    cmpfunc_p key_cmpfunc;
    cmpfunc_p value_cmpfunc;

    operation_p free_node_func;
};

extern BST_p BST_Init(int key_size, int value_size, cmpfunc_p key_cmpfunc, cmpfunc_p value_cmpfunc, operation_p free_node_func);
extern bool BST_IsEmpty(BST_p bst);
extern int BST_Size(BST_p bst);
extern void BST_Insert(BST_p bst, void* key, void* value);
extern void* BST_Search(BST_p bst, void* key);
extern void BST_PreOrder_Traversal(BST_p bst, operation_p func);
extern void BST_InOrder_Traversal(BST_p bst, operation_p func);
extern void BST_PostOrder_Traversal(BST_p bst, operation_p func);
extern void BST_Delete(BST_p bst);
extern void* BST_Find_MinimumKey(BST_p bst);
extern void* BST_Find_MaximumKey(BST_p bst);
extern void BST_Remove_Max(BST_p bst);
extern void BST_Remove_Min(BST_p bst);
extern void BST_Remove_Key(BST_p bst, void* key);


#endif
