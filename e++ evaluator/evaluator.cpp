/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

bool isop(string s)
{
    if(s == "+" || s== "-" || s== "*" || s == "/")
    {
        return true;
    }
    else
    {
        return false;
    }
}

Evaluator::Evaluator()
{
    this->symtable = new SymbolTable();
    this->expr_trees.clear();
}

Evaluator::~Evaluator()
{
    delete this->symtable;
    int sz = this->expr_trees.size();
    for(int i = sz-1; i >= 0;i--)
    {
        ExprTreeNode* tmp = this->expr_trees[i];
        this->expr_trees.pop_back();
        delete tmp;
    }
}

bool isdigit(string s){
    int n = s.size();
    if(s[0] == 45)
    {
        for(int i = 1; i <n ;i++)
        {
            if (s[i] < 48 || s[i] > 57)
            {
                return false;
            }
        }
    }
    else
    {
        for(int i = 0; i <n ;i++)
        {
            if (s[i] < 48 || s[i] > 57)
            {
                return false;
            }
        }
    }
    return true;
}

void Evaluator::parse(vector<string> code)
{
    ExprTreeNode* root = new ExprTreeNode();
    int n = code.size();
    int i = 0;
    if(code[1] == ":=")
    {
        root->left = new ExprTreeNode(code[0],new UnlimitedRational());
        i = 2;
        if(n == 3)
        {
            if(isdigit(code[2]))
            {
                UnlimitedInt* v = new UnlimitedInt(code[2]);
                root->right = new ExprTreeNode("VAL",v);
            }
            else
            {
                root->right = new ExprTreeNode(code[2],new UnlimitedRational());
                delete root->right->evaluated_value;
                root->right->evaluated_value = this->symtable->search(code[2]);
            }
            this->expr_trees.push_back(root);
            return;
        }
    }
    vector<string> stk;
    int j = 0;
    vector<ExprTreeNode*> pointers;
    while(i < n)
    {
        if(code[i] != ")")
        {
            stk.push_back(code[i]);
            j++;
        }
        else
        {
            string righti = stk[j-1];
            string op = stk[j-2];
            string lefti = stk[j-3];
            stk.pop_back();
            stk.pop_back();
            stk.pop_back();
            stk.pop_back();
            ExprTreeNode* rot = new ExprTreeNode(op,new UnlimitedRational());
            if(righti == ":=")
            {
                rot->right = pointers[pointers.size()-1];
                pointers.pop_back();
            }
            else
            {
                if(isdigit(righti))
                {
                    UnlimitedInt* v = new UnlimitedInt(righti);
                    rot->right = new ExprTreeNode("VAL",v);
                }
                else
                {
                    UnlimitedRational* thomp = new UnlimitedRational();
                    rot->right = new ExprTreeNode(righti,thomp);
                    delete rot->right->evaluated_value;
                    rot->right->evaluated_value = this->symtable->search(righti);
                }
            }
            if(lefti == ":=")
            {
                rot->left = pointers[pointers.size()-1];
                pointers.pop_back();
            }
            else
            {
                if(isdigit(lefti))
                {
                    UnlimitedInt* v = new UnlimitedInt(lefti);
                    rot->left = new ExprTreeNode("VAL",v);
                }
                else
                {
                    rot->left = new ExprTreeNode(lefti,new UnlimitedRational());
                    delete rot->left->evaluated_value;
                    rot->left->evaluated_value = this->symtable->search(lefti);
                }
            }
            stk.push_back(":=");
            pointers.push_back(rot);
            j--;
            j--;
            j--;
        }
        i++;
    }
    root->right = pointers[0];
    this->expr_trees.push_back(root);
    return;
}


void myval(ExprTreeNode* root)
{

    if(isop(root->id) == false)
    {
        return;
    }
    if(isop(root->right->id) == true)
    {
        myval(root->right);
    }
    if(isop(root->left->id) == true)
    {
        myval(root->left);
    }
    string op = root->id;
    delete root->evaluated_value;
    if(op == "+")
    {
        root->evaluated_value = UnlimitedRational::add(root->left->evaluated_value,root->right->evaluated_value);
    }
    else if(op == "-")
    {
        root->evaluated_value = UnlimitedRational::sub(root->left->evaluated_value,root->right->evaluated_value);
    }
    else if(op == "*")
    {
        root->evaluated_value = UnlimitedRational::mul(root->left->evaluated_value,root->right->evaluated_value);
    }
    else
    {
        root->evaluated_value = UnlimitedRational::div(root->left->evaluated_value,root->right->evaluated_value);
    }
    return;
}

void Evaluator::eval()
{
    ExprTreeNode* root = this->expr_trees[this->expr_trees.size()-1];
    myval(root->right);
    delete root->left->evaluated_value;
    root->left->evaluated_value = root->right->evaluated_value;
    this->symtable->insert(root->left->id,root->left->evaluated_value);
}