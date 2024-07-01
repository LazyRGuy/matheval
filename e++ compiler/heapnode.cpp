/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    this->val = -1;
    this->par = NULL;
    this->left = NULL;
    this->right = NULL;
}

HeapNode::HeapNode(int _val){
    this->val = _val;
    this->par = NULL;
    this->left = NULL;
    this->right = NULL;
}

HeapNode::~HeapNode(){
    if(this->left != NULL)
    {
        delete this->left;
    }
    if(this->right != NULL)
    {
        delete this->right;
    }
}