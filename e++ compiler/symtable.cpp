/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
SymbolTable::SymbolTable(){
    this->size = 0;
    this->root = NULL;
}

int h(SymNode* node)
{
    if(node == NULL)
    {
        return -1;
    }
    return node->height;
}

SymNode* Left(SymNode* root, SymNode* ptr)
{
    SymNode* temp = ptr->right;
    temp->par = ptr->par;
    ptr->right = temp->left;
    if(ptr->right != NULL)
    {
        ptr->right->par = ptr;
    }
    temp->left = ptr;
    if(temp->par == NULL)
    {
        root = temp;
    }
    else
    {
        if(ptr->par->left == ptr)
        {
            ptr->par->left = temp;
        }
        else
        {
            ptr->par->right = temp;
        }
    }
    ptr->par = temp;
    ptr->height = 1 + std::max(h(ptr->right),h(ptr->left));
    temp->height = 1 + std::max(h(temp->right),h(temp->left));
    return root;
}

SymNode* Right(SymNode* root,SymNode* ptr)
{
    SymNode* temp = ptr->left;
    temp->par = ptr->par;
    ptr->left = temp->right;
    if(ptr->left != NULL)
    {
        ptr->left->par = ptr;
    }
    temp->right = ptr;
    if(temp->par == NULL)
    {
        root = temp;
    }
    else
    {
        if(ptr->par->left == ptr)
        {
            ptr->par->left = temp;
        }
        else
        {
            ptr->par->right = temp;
        }
    }
    ptr->par = temp;
    ptr->height = 1 + std::max(h(ptr->right),h(ptr->left));
    temp->height = 1 + std::max(h(temp->right),h(temp->left));
    return root;
}

void SymbolTable::insert(string k){
    if (search(k)!=-2){
        return;
    }
    if(root == NULL)
    {
        SymNode* ins = new SymNode(k);
        root = ins;
        this->size++;
        return;
    }
    SymNode* parent = NULL;
    SymNode* ptr = root;
    while(ptr != NULL)
    {
        if(ptr->key > k)
        {
            parent = ptr;
            ptr = ptr->left;
        }
        else
        {
            parent = ptr;
            ptr = ptr->right;
        }
    }
    SymNode* ins = new SymNode(k);
    if(parent->key > k)
    {
        parent->left = ins;
        ins->par = parent;
    }
    else
    {
        parent->right = ins;
        ins->par = parent;
    }
    this->size++;
    while(parent != NULL)
    {
        parent->height = 1 + std::max(h(parent->left),h(parent->right));
        if(h(parent->left) > 1 + h(parent->right))
        {
            if(h(parent->left->right) > h(parent->left->left))
            {
                this->root = Left(this->root,parent->left);
            }
            this->root = Right(this->root,parent);
        }
        else if(h(parent->right) > 1 + h(parent->left))
        {
            if(h(parent->right->right) < h(parent->right->left))
            {
                this->root=Right(this->root,parent->right);
            }
            this->root = Left(this->root,parent);
        }
        parent = parent->par;
    }
    return;
}

SymNode* swup(SymNode* root,SymNode* ptr,SymNode* ch)
{
    if(ptr->par == NULL)
    {
        root = ch;
    }
    else if(ptr->par->left == ptr)
    {
        ptr->par->left = ch;
    }
    else
    {
        ptr->par->right = ch;
    }
    if(ch != NULL)
    {
        ch->par = ptr->par;
    }
    return root;
}

int get_height(SymNode *node)
{
    if (!node)
        return -1;
    return node->height;
}

int get_balance(SymNode *node)
{
    return get_height(node->right) - get_height(node->left);
}

void SymbolTable::remove(string k){
    if(search(k) == -2)
    {
        return;
    }
    SymNode* ptr = this->root;
    while(ptr != NULL)
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
            break;
        }
    }
    if(ptr == NULL)
    {
        return;
    }
    SymNode* parent = ptr->par;
    if(ptr->left == NULL && ptr->right == NULL)
    {
        if(ptr->par == NULL)
        {
            delete ptr;
            root = NULL;
            size--;
            return;
        }
        else if(ptr->par->key > k)
        {
            ptr->par->left = NULL;
            delete ptr;
        }
        else
        {
            ptr->par->right = NULL;
            delete ptr;
        }
    }
    else if(ptr->left != NULL && ptr->right == NULL)
    {
        this->root = swup(this->root,ptr,ptr->left);
        ptr->left = NULL;
        delete ptr;
    }
    else if(ptr->right != NULL && ptr->left == NULL)
    {
        this->root = swup(this->root,ptr,ptr->right);
        ptr->right = NULL;
        delete ptr;
    }
    else
    {
        SymNode* mini = ptr->right;
        while(mini->left != NULL)
        {
            mini = mini->left;
        }
        if(mini->par != ptr)
        {
            parent = mini->par;
            this->root = swup(this->root,mini,mini->right);
            mini->right = ptr->right;
            mini->right->par = mini;
        }
        else
        {
            parent = mini;
        }
        this->root = swup(this->root,ptr,mini);
        mini->left = ptr->left;
        mini->left->par = mini;
        ptr->left = NULL;
        ptr->right = NULL;
        delete ptr;
    }
    while(parent != NULL)
    {
        parent->height = 1 + std::max(h(parent->left),h(parent->right));
        if(h(parent->left) > 1 + h(parent->right))
        {
            if(h(parent->left->right) > h(parent->left->left))
            {
                this->root = Left(this->root,parent->left);
            }
            this->root = Right(this->root,parent);
        }
        else if(h(parent->right) > 1 + h(parent->left))
        {
            if(h(parent->right->right) < h(parent->right->left))
            {
                this->root = Right(this->root,parent->right);
            }
            this->root = Left(this->root,parent);
        }
        parent = parent->par;
    }
    size--;
    return;
}

int SymbolTable::search(string k){
    SymNode* ptr = this->root;
    while(ptr != NULL)
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
            return ptr->address;
        }
    }
    return -2;
}
void SymbolTable::assign_address(string k,int idx){
    SymNode* ptr = this->root;
    while(ptr != NULL)
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
            ptr->address = idx;
            return;
        }
    }
    return;
}

int SymbolTable::get_size(){
    return  this->size;
}

SymNode* SymbolTable::get_root(){
    return this->root;
}

SymbolTable::~SymbolTable(){
    if(this->root != NULL)
    {
        delete this->root;
    }
}
