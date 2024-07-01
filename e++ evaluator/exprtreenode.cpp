/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode()
{
    this->type = "VAR";
    this->evaluated_value = new UnlimitedRational();
    this->val = new UnlimitedRational();
    this->id = ":=";
    this->left = nullptr;
    this->right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v)
{
    UnlimitedInt* one = new UnlimitedInt(1);
    UnlimitedRational* ptr = new UnlimitedRational(v,one);
    this->type = "VAL";
    this->val = ptr;
    UnlimitedInt* num = new UnlimitedInt(ptr->get_p_str());
    UnlimitedInt* den = new UnlimitedInt(ptr->get_q_str());
    this->evaluated_value = new UnlimitedRational(num,den);
    this->id = "==";
    this->left = nullptr;
    this->right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v)
{
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
    this->val = new UnlimitedRational();
    this->evaluated_value = v;
    this->id = t;
    this->left = nullptr;
    this->right = nullptr;
}

ExprTreeNode::~ExprTreeNode()
{
    if(this->left != nullptr)
    {
        delete this->left;
    }
    if(this->right != nullptr)
    {
        delete this->right;
    }
    if(this->type == "VAR" && this->id != ":=")
    {
        delete this->val;
    }
    else
    {
        delete this->val;
        delete this->evaluated_value;
    }
}
