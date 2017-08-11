
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int IntCompare(void* a, void* b){
    return *(int*)a - *(int*)b;
}


void NodePrint(void* node){
    printf("%d -> %d\n", *(int*)(((Node_p)node)->key), *(int*)(((Node_p)node)->value));
}

void BinarySearch_Test(){
    int arr[20] = {2,2,4,4,6,6,6,8,10,10,12,12,14,14,16,16,18,18,20,20};
    for (int i=0; i < 20; i++)
        printf("%d ", arr[i]);
    printf("\n\n");
    int target = 8;
    int result_f = BinarySearch_Floor(arr, sizeof(int), 20, &target, IntCompare);
    int result_c = BinarySearch_Ceil(arr, sizeof(int), 20, &target, IntCompare);
    printf("target:%d\nfound: arr[%d - %d]\n\n", target,result_f, result_c);

    target = 6;
    result_f = BinarySearch_Floor(arr, sizeof(int), 20, &target, IntCompare);
    result_c = BinarySearch_Ceil(arr, sizeof(int), 20, &target, IntCompare);
    printf("target:%d\nfound: arr[%d - %d]\n\n", target,result_f, result_c);

    target = 21;
    result_f = BinarySearch_Floor(arr, sizeof(int), 20, &target, IntCompare);
    result_c = BinarySearch_Ceil(arr, sizeof(int), 20, &target, IntCompare);
    printf("target:%d\nfound: arr[%d - %d]\n\n", target,result_f, result_c);

    target = 1;
    result_f = BinarySearch_Floor(arr, sizeof(int), 20, &target, IntCompare);
    result_c = BinarySearch_Ceil(arr, sizeof(int), 20, &target, IntCompare);
    printf("target:%d\nfound: arr[%d - %d]\n\n", target,result_f, result_c);

}

void BST_Test(){
    BST_p bst = BST_Init(sizeof(int), sizeof(int), IntCompare, IntCompare, NULL);
    int keys[10];
    int values[10];

    for (int i=0; i < 10; i++) {
        keys[i] = rand()%100;
        values[i] = i*10;
    }
    for (int i=0; i < 10; i++) {
        BST_Insert(bst, &keys[i], &values[i]);
    }

    int* found = (int*)BST_Search(bst, &keys[0]);
    if(found != NULL)
        printf("key:%d value-> %d\n", keys[0], *found);
    else
        printf("NOT FOUND! %d\n", keys[0]);

    found = (int*)BST_Search(bst, &keys[4]);
    if(found != NULL)
        printf("key:%d value-> %d\n", keys[4], *found);
    else
        printf("NOT FOUND! %d\n", keys[4]);

    found = (int*)BST_Search(bst, &keys[9]);
    if(found != NULL)
        printf("key:%d value-> %d\n", keys[9], *found);
    else
        printf("NOT FOUND! %d\n", keys[9]);

    int temp = 120;
    found = (int*)BST_Search(bst, &temp);
    if(found != NULL)
        printf("key:%d value-> %d\n", temp, *found);
    else
        printf("NOT FOUND! %d\n", temp);


    printf("--------------------------\n");
    BST_PreOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    BST_PostOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");


    int* min_addr = (int*)BST_Find_MinimumKey(bst);
    printf("minvalue is %d\n", *min_addr);
    int* max_addr = (int*)BST_Find_MaximumKey(bst);
    printf("maxvalue is %d\n", *max_addr);

    printf("--------------------------\n");
    BST_Remove_Max(bst);
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    BST_Remove_Max(bst);
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    BST_Remove_Max(bst);
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    BST_Remove_Max(bst);
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    printf("--------------------------\n");
    BST_Remove_Min(bst);
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    BST_Remove_Min(bst);
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    BST_Remove_Min(bst);
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    BST_Remove_Min(bst);
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    BST_Remove_Max(bst);
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    BST_Remove_Min(bst);
    BST_InOrder_Traversal(bst, NodePrint);
    printf("--------------------------\n");
    /* extern void BST_Remove_Min(BST_p bst); */


    BST_Delete(bst);
}

void BST_Test2(){
    BST_p bst = BST_Init(sizeof(int), sizeof(int), IntCompare, IntCompare, NULL);
    int keys[10];
    int values[10];

    for (int i=0; i < 10; i++) {
        keys[i] = rand()%20;
        values[i] = i*10;
    }
    for (int i=0; i < 10; i++) {
        BST_Insert(bst, &keys[i], &values[i]);
    }

    for (int i=0; i < 10; i++) {
        printf("--------------------------\n");
        BST_Remove_Key(bst, &keys[rand()%10]);
        BST_InOrder_Traversal(bst, NodePrint);
        printf("--------------------------\n");
    }


    BST_Delete(bst);
}


int main(int argc, char *argv[])
{
    BinarySearch_Test();
    BST_Test();
    BST_Test2();

    return 0;
}
