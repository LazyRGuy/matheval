/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    this->left = NULL;
    this->right = NULL;
    this->id = ":=";
    this->num=0;
    this->type = ":=";
}

ExprTreeNode::ExprTreeNode(string t,int v){
    this->id = t;
    this->num = v;
    this->left = NULL;
    this ->right = NULL;
    this->type = "VAR";
    if(t == "+")
    {
        this->type = "ADD";
    }
    if(t == "-")
    {
        this->type = "SUB";
    }
    if(t == "*")
    {
        this->type = "MUL";
    }
    if(t == "/")
    {
        this->type = "DIV";
    }
    if(t == "VAL")
    {
        this->type = "VAL";
    }
}

ExprTreeNode::~ExprTreeNode(){
    if(this->left != NULL)
    {
        delete this->left;
    }
    if(this->right != NULL)
    {
        delete this->right;
    }
}

