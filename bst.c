
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define NODE 0
#define PARENT 1


extern int BinarySearch_Floor(void* arr, int elem_size, int elem_num, void* target, cmpfunc_p cmpfunc);
extern int BinarySearch_Ceil(void* arr, int elem_size, int elem_num, void* target, cmpfunc_p cmpfunc);

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


static Node_p Node_Init(void* key, void* value);
static Node_p _bst_insert(BST_p bst, Node_p root, void* key, void* value);
static void* _bst_search(BST_p bst, Node_p root, void* key);
static void _bst_preorder_traversal(BST_p bst, Node_p root, operation_p func);
static void _bst_inorder_traversal(BST_p bst, Node_p root, operation_p func);
static void _bst_postorder_traversal(BST_p bst, Node_p root, operation_p func);
/* static Node_p* _bst_node_search(BST_p bst, Node_p root, Node_p parent, void* key); */
static Node_p _remove_min_recursive(BST_p bst, Node_p root);
static Node_p _remove_max_recursive(BST_p bst, Node_p root);
static Node_p _bst_remove_key(BST_p bst, Node_p root, void* key);

/**************************************
 *                                    *
 * Public functions                   *
 *                                    *
 **************************************/

/*
 * Binary Search functions
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
 * Binary Search Tree functions
 */
BST_p BST_Init(int key_size, int value_size, cmpfunc_p key_cmpfunc, cmpfunc_p value_cmpfunc, operation_p free_node_func){
    assert(key_size > 0 && value_size > 0 && \
           key_cmpfunc != NULL);
    BST_p new_bst = malloc(sizeof(BST_t));
    assert(new_bst != NULL);
    new_bst->root = NULL;
    new_bst->num_node = 0;


    new_bst->key_size = key_size;
    new_bst->value_size = value_size;

    new_bst->key_cmpfunc = key_cmpfunc;
    new_bst->value_cmpfunc = value_cmpfunc;
    new_bst->free_node_func = free_node_func;

    return new_bst;
}

void BST_Delete(BST_p bst){
    operation_p free_func = bst->free_node_func == NULL ? free : bst->free_node_func;
    BST_PostOrder_Traversal(bst, free_func);
    bst->num_node = 0;
    free(bst);
}

void BST_Insert(BST_p bst, void* key, void* value){
    bst->root = _bst_insert(bst, bst->root, key, value);
}

void* BST_Search(BST_p bst, void* key){
    return _bst_search(bst, bst->root, key);
}

void BST_PreOrder_Traversal(BST_p bst, operation_p func){
    _bst_preorder_traversal(bst, bst->root, func);
}

void BST_InOrder_Traversal(BST_p bst, operation_p func){
    _bst_inorder_traversal(bst, bst->root, func);
}

void BST_PostOrder_Traversal(BST_p bst, operation_p func){
    _bst_postorder_traversal(bst, bst->root, func);
}

/* void BST_BreadthFirst_Traversal(BST_p bst, operation_p func){ */
/*     void* stack = malloc(bst->elem_num * bst->elem_size); */
/*     assert(stack != NULL); */

/* } */

void* BST_Find_MinimumKey(BST_p bst){
    if(bst->root == NULL)
        return NULL;
    Node_p node = bst->root;
    while(node->left_child != NULL)
        node = node->left_child;
    return node->key;
}

void* BST_Find_MaximumKey(BST_p bst){
    if(bst->root == NULL)
        return NULL;
    Node_p node = bst->root;
    while(node->right_child != NULL)
        node = node->right_child;
    return node->key;
}

void BST_Remove_Max(BST_p bst){
    if(bst->root == NULL)
        return ;
    Node_p node = bst->root;
    Node_p parent_node = NULL;
    if(bst->num_node == 1){
        bst->root = NULL;
        bst->num_node --;
        return;
    }

    while(node->right_child != NULL){
        parent_node = node;
        node = node->right_child;
    }
    if(parent_node == NULL)
        bst->root = node->left_child;

    else
        parent_node->right_child = node->left_child;

    bst->num_node --;

}

void BST_Remove_Min(BST_p bst){
    if(bst->root == NULL)
        return ;
    Node_p node = bst->root;
    Node_p parent_node = NULL;
    if(bst->num_node == 1){
        bst->root = NULL;
        bst->num_node --;
        return;
    }

    while(node->left_child != NULL){
        parent_node = node;
        node = node->left_child;
    }

    if(parent_node == NULL)
        bst->root = node->right_child;
    else
        parent_node->left_child = node->right_child;

    bst->num_node --;
}

void BST_Remove_Key(BST_p bst, void* key){
    bst->root =  _bst_remove_key(bst, bst->root, key);
}

bool BST_IsEmpty(BST_p bst){
    return bst->num_node == 0;
}

int BST_Size(BST_p bst){
    return bst->num_node;
}

/**************************************
 *                                    *
 * Private functions                   *
 *                                    *
 **************************************/

Node_p Node_Init(void* key, void* value){
    Node_p new_node = malloc(sizeof(Node_t));
    assert(new_node != NULL);

    new_node->key = key;
    new_node->value = value;

    new_node->left_child = NULL;
    new_node->right_child = NULL;

    return new_node;
}

Node_p Node_Copy(Node_p node){
    Node_p new_node = malloc(sizeof(Node_t));
    assert(new_node != NULL);

    new_node->key = node->key;
    new_node->value = node->value;

    new_node->left_child = node->left_child;
    new_node->right_child = node->right_child;

    return new_node;
}

Node_p _bst_insert(BST_p bst, Node_p root, void* key, void* value){
    if(root == NULL){
        bst->num_node ++;
        return Node_Init(key, value);
    }

    if(bst->key_cmpfunc(root->key, key) == 0)
        root->value = value;
    else if(bst->key_cmpfunc(key, root->key) < 0)
        root->left_child = _bst_insert(bst, root->left_child, key, value);
    else
        root->right_child = _bst_insert(bst, root->right_child, key, value);
    return root;
}


Node_p* _bst_node_search(BST_p bst, Node_p root, Node_p parent, void* key){
    if(root == NULL)
        return NULL;
    if(bst->key_cmpfunc(root->key, key) == 0){
        Node_p* node_and_parent = malloc(sizeof(Node_p) * 2);
        assert(node_and_parent != NULL);
        node_and_parent[NODE] = root;
        node_and_parent[PARENT] = parent;
        return node_and_parent;
    }
    else if(bst->key_cmpfunc(key, root->key) < 0)
        return _bst_node_search(bst, root->left_child, root, key);
    else
        return _bst_node_search(bst, root->right_child, root, key);
}

void* _bst_search(BST_p bst, Node_p root, void* key){

    if(root == NULL)
        return NULL;
    if(bst->key_cmpfunc(root->key, key) == 0)
        return root->value;
    else if(bst->key_cmpfunc(key, root->key) < 0)
        return _bst_search(bst, root->left_child, key);
    else
        return _bst_search(bst, root->right_child, key);
}

void _bst_preorder_traversal(BST_p bst, Node_p root, operation_p func){
    if( root != NULL){
        func(root);
        _bst_preorder_traversal(bst, root->left_child, func);
        _bst_preorder_traversal(bst, root->right_child, func);
    }
}

void _bst_inorder_traversal(BST_p bst, Node_p root, operation_p func){
    if( root != NULL){
        _bst_inorder_traversal(bst, root->left_child, func);
        func(root);
        _bst_inorder_traversal(bst, root->right_child, func);
    }
}
void _bst_postorder_traversal(BST_p bst, Node_p root, operation_p func){
    if( root != NULL){
        _bst_postorder_traversal(bst, root->left_child, func);
        _bst_postorder_traversal(bst, root->right_child, func);
        func(root);
    }
}

Node_p _get_minimum_node(Node_p root){
    Node_p node = root;
    while(node->left_child)
        node = node->left_child;
    return node;
}

Node_p _remove_min_recursive(BST_p bst, Node_p root){
    if(root->left_child == NULL){
        Node_p right_node = root->right_child;
        free(root);
        bst->num_node --;
        return right_node;
    }
    root->left_child = _remove_min_recursive(bst, root->left_child);
    return root;
}

Node_p _remove_max_recursive(BST_p bst, Node_p root){
    if(root->right_child == NULL){
        Node_p left_node = root->left_child;
        free(root);
        bst->num_node --;
        return left_node;
    }
    root->right_child = _remove_max_recursive(bst, root->right_child);
    return root;
}

Node_p _bst_remove_key(BST_p bst, Node_p root, void* key){
    if(root == NULL)
        return NULL;
    if(bst->key_cmpfunc(key, root->key) < 0){
        root->left_child = _bst_remove_key(bst, root->left_child, key);
        return root;
    }
    else if(bst->key_cmpfunc(key, root->key) > 0){
        root->right_child = _bst_remove_key(bst, root->right_child, key);
        return root;
    }
    else{
        if(root->left_child == NULL){
            Node_p right_node = root->right_child;
            free(root);
            bst->num_node --;
            return right_node;
        }
        if(root->right_child == NULL){
            Node_p left_node = root->left_child;
            free(root);
            bst->num_node --;
            return left_node;
        }

        // root->left != NULL && root->right != NULL
        Node_p successor = Node_Copy(_get_minimum_node(root->right_child));
        bst->num_node ++;

        successor->right_child = _remove_min_recursive(bst, root->right_child);
        successor->left_child = root->left_child;

        free(root);
        bst->num_node --;
        return successor;
    }
}
