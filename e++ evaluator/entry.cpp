/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry()
{
    this->key = "";
    this->val = new UnlimitedRational();
    this->left = nullptr;
    this->right = nullptr;
}

SymEntry::SymEntry(string k, UnlimitedRational* v)
{
    this->key = k;
    this->val = v;
    this->left = nullptr;
    this->right = nullptr;
}

SymEntry::~SymEntry()
{
    if(this->left == nullptr && this->right == nullptr)
    {
    }
    else if(this->left != nullptr && this->right == nullptr)
    {
        delete this->left;
    }
    else if(this->right != nullptr && this->left == nullptr)
    {
        delete this->right;
    }
    else
    {
        delete this->right;
        delete this->left;
    }
}