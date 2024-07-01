/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){
    this->size = 0;
    this->root = NULL;
}

void MinHeap::push_heap(int num){
    if(this->size == 0)
    {
        HeapNode* naya = new HeapNode(num);
        this->root = naya;
        this->size++;
        return;
    }
    int dp = this->size+1;
    int* arr = new int[31];
    int i = 0;
    while(dp != 0)
    {
        int rem = dp%2;
        arr[i] = rem;
        dp = dp/2;
        i++;
    }
    i-=2;
    HeapNode* ptr = root;
    HeapNode* parent = NULL;
    while(i != -1)
    {
        parent = ptr;
        if(parent->val > num)
        {
            int thu = num;
            num = parent->val;
            parent->val = thu;
        }
        if(arr[i] == 0)
        {
            ptr = ptr->left;
        }
        else
        {
            ptr = ptr->right;
        }
        i--;
    }
    if(arr[0] == 1)
    {
        parent->right = new HeapNode(num);
        ptr = parent->right;
    }
    else
    {
        parent->left = new HeapNode(num);
        ptr = parent->left;
    }
    delete[] arr;
    size++;
}

int MinHeap::get_min(){
    return root->val;
}

void MinHeap::pop(){
    if(size == 1)
    {
        delete root;
        root = NULL;
        size--;
        return;
    }
    int dp = this->size;
    int* arr = new int[31];
    int i = 0;
    while(dp != 0)
    {
        int rem = dp%2;
        arr[i] = rem;
        dp = dp/2;
        i++;
    }
    i-=2;
    HeapNode* ptr = root;
    HeapNode* parent = NULL;
    while(i != -1)
    {
        parent = ptr;
        if(arr[i] == 0)
        {
            ptr = ptr->left;
        }
        else
        {
            ptr = ptr->right;
        }
        i--;
    }
    ptr = root;
    if(arr[0] == 1)
    {
        root->val = parent->right->val;
        delete parent->right;
        parent->right = NULL;
    }
    else
    {
        root->val = parent->left->val;
        delete parent->left;
        parent->left = NULL;
    }
    while((ptr->right != NULL && ptr->val > ptr->right->val) && (ptr->left != NULL && ptr->val > ptr->left->val))
    {
        int temp = ptr->val;
        if(ptr->right->val < ptr->left->val)
        {
            ptr->val= ptr->right->val;
            ptr->right->val = temp;
            ptr = ptr->right;
        }
        else
        {
            ptr->val= ptr->left->val;
            ptr->left->val = temp;
            ptr = ptr->left;
        }
    }
    if(ptr->left != NULL && ptr->right == NULL)
    {
        if(ptr->left->val < ptr->val)
        {
            int temp = ptr->val;
            ptr->val= ptr->left->val;
            ptr->left->val = temp;
        }
    }
    delete[] arr;
    this->size--;
    return;
}

MinHeap::~MinHeap(){
    if(root != NULL)
    {
        delete root;
    }
}