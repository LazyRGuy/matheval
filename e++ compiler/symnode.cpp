/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

// Write your code below this line

SymNode::SymNode()
{
    this->key = "";
    this->height = 0;
    this->address = -1;
    this->par = NULL;
    this->left = NULL;
    this->right = NULL;
}

SymNode::SymNode(string k)
{
    this->key = k;
    this->height = 0;
    this->address = -1;
    this->par = NULL;
    this->left = NULL;
    this->right = NULL;
}

int ho(SymNode *node)
{
    if (node == NULL)
    {
        return -1;
    }
    return node->height;
}

SymNode *SymNode::LeftLeftRotation()
{
    return NULL;
}

SymNode *SymNode::RightRightRotation()
{return NULL;
}

SymNode *SymNode::LeftRightRotation()
{
    return NULL;
}

SymNode *SymNode::RightLeftRotation()
{
    return NULL;
}

SymNode::~SymNode()
{
    if (this->left != NULL)
    {
        delete this->left;
    }
    if (this->right != NULL)
    {
        delete this->right;
    }
}