/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymbolTable::SymbolTable()
{
    this->size = 0;
    this->root = nullptr;
}

SymbolTable::~SymbolTable()
{
    if(this->root != nullptr)
    {
        delete this->root;
    }
}

void SymbolTable::insert(string k, UnlimitedRational* v)
{
    if(root == nullptr)
    {
        SymEntry* ins = new SymEntry(k,v);
        root = ins;
        this->size++;
        return;
    }
    SymEntry* parent = nullptr;
    SymEntry* ptr = root;
    while(ptr != nullptr)
    {
        if(ptr->key > k)
        {
            parent = ptr;
            ptr = ptr->left;
        }
        else if(ptr->key < k)
        {
            parent = ptr;
            ptr = ptr->right;
        }
        else
        {
            ptr->val = v;
            return;
        }
    }
    SymEntry* ins = new SymEntry(k,v);
    if(parent->key > k)
    {
        parent->left = ins;
    }
    else
    {
        parent->right = ins;
    }
    this->size++;
    return;
}

void SymbolTable::remove(string k)
{
    if(root == nullptr)
    {
        return;
    }
    SymEntry* parent = nullptr;
    SymEntry* ptr = root;
    while(ptr != nullptr)
    {
        if(ptr->key > k)
        {
            parent = ptr;
            ptr = ptr->left;
        }
        else if(ptr->key < k)
        {
            parent = ptr;
            ptr = ptr->right;
        }
        else
        {
            if(parent->right->key == k)
            {
                delete parent->right;
                parent->right = nullptr;
                return;
            }
            else
            {
                break;
            }
        }
    }
    if(ptr == nullptr)
    {
        return;
    }
    if(ptr->left == nullptr && ptr->right == nullptr)
    {
        if(parent == nullptr)
        {
            delete ptr;
            root = nullptr;
            return;
        }
        if(parent->key > k)
        {
            parent->left = nullptr;
            delete ptr;
            return;
        }
        else
        {
            parent->right = nullptr;
            delete ptr;
            return;
        }
    }
    else if(ptr->left != nullptr)
    {
        SymEntry* mini = ptr->left;
        SymEntry* pmin = ptr;
        while(mini->right != nullptr)
        {
            pmin = mini;
            mini = mini->right;
        }
        ptr->key = mini->key;
        delete ptr->val;
        ptr->val = mini->val;
        if(pmin == ptr)
        {
            pmin->left = mini->left;
            return;
        }
        else
        {
            pmin->right = mini->left;
            return;
        }
    }
    else
    {
        SymEntry* mini = ptr->right;
        SymEntry* pmin = ptr;
        while(mini->left != nullptr)
        {
            pmin = mini;
            mini = mini->left;
        }
        ptr->key = mini->key;
        delete ptr->val;
        ptr->val = mini->val;
        if(pmin == ptr)
        {
            pmin->right = mini->right;
            return;
        }
        else
        {
            pmin->left = mini->right;
            return;
        }
    }
}

UnlimitedRational* SymbolTable::search(string k)
{
    SymEntry* ptr = root;
    while(ptr != nullptr)
    {
        if(ptr->key > k)
        {
            ptr = ptr->left;
        }
        else if(ptr->key < k)
        {
            ptr = ptr->right;
        }
        else
        {
            return ptr->val;
        }
    }
    return new UnlimitedRational();
}

int SymbolTable::get_size()
{
    return this->size;
}

SymEntry* SymbolTable::get_root()
{
    return this->root;
}
