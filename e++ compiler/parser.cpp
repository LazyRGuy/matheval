/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    this->symtable = new SymbolTable();
    this->expr_trees.clear();
    this->last_deleted = -2;
}

bool isdigit(string s)
{
    if(s[0] == '-')
    {
        return true;
    }
    else if(s[0] < 48 || s[0] > 57)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Parser::parse(vector<string> expression){
    if(expression[0] == "del")
    {
        this->symtable->remove(expression[2]);
        ExprTreeNode* root = new ExprTreeNode();
        root->right = new ExprTreeNode(expression[2],0);
        root->left = new ExprTreeNode("DEL",0);
        root->left->type = "DEL";
        this->expr_trees.push_back(root);
        return;
    }
    ExprTreeNode* root = new ExprTreeNode();
    root->left = new ExprTreeNode(expression[0],0);
    if(expression.size() == 3)
    {
        if(isdigit(expression[2]) == true)
        {
            root->right = new ExprTreeNode("VAL",stoi(expression[2]));
        }
        else
        {
            root->right = new ExprTreeNode(expression[2],0);
        }
    }
    else
    {
        vector<string> stk;
        vector<ExprTreeNode*> pointers;
        int j = 0;
        int n = expression.size();
        int k = 0;
        for(int i = 2; i < n;i++)
        {
            if(expression[i] != ")")
            {
                stk.push_back(expression[i]);
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
                ExprTreeNode* rot = new ExprTreeNode(op,0);
                if(righti == ":=")
                {
                    rot->right = pointers[k-1];
                    pointers.pop_back();
                    k--;
                }
                else
                {
                    if(isdigit(righti))
                    {
                        rot->right = new ExprTreeNode("VAL",stoi(righti));
                    }
                    else
                    {
                        rot->right = new ExprTreeNode(righti,0);
                    }
                }
                if(lefti == ":=")
                {
                    rot->left = pointers[k-1];
                    pointers.pop_back();
                    k--;
                }
                else
                {
                    if(isdigit(lefti))
                    {
                        rot->left = new ExprTreeNode("VAL",stoi(lefti));
                    }
                    else
                    {
                        rot->left = new ExprTreeNode(lefti,0);
                    }
                }
                stk.push_back(":=");
                pointers.push_back(rot);
                j = j-3;
                k++;
            }
        }
        root->right = pointers[0];
    }
    if(expression[0] == "ret")
    {
        root->left->type = "RET";
        this->expr_trees.push_back(root);
        return;
    }
    this->expr_trees.push_back(root);
    this->symtable->insert(root->left->id);
    return;
}

Parser::~Parser(){
    delete this->symtable;
    int n = this->expr_trees.size();
    for(int i = 0; i < n;i++)
    {
        ExprTreeNode* root = this->expr_trees[n-1-i];
        this->expr_trees.pop_back();
        delete root;
    }
}