/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
    this->memory_size = 0;
    this->output_file = "";
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    this->output_file = out_file;
    this->memory_size = mem_limit;
    for(int i = 0; i < mem_limit;i++)
    {
        this->least_mem_loc.push_heap(i);
    }
}


vector<string> myal(ExprTreeNode* ptr,SymbolTable* symtable)
{
    vector<string> res;
    if(ptr->left == NULL && ptr->right == NULL)
    {
        if(ptr->type == "VAR")
        {
            res.push_back("PUSH mem[" + to_string(symtable->search(ptr->id)) + "]");
        }
        else
        {
            res.push_back("PUSH " + to_string(ptr->num));
        }
        return res;
    }
    if(ptr->right != NULL)
    {
        vector<string> righti = myal(ptr->right,symtable);
        int urmum = righti.size();
        for(int i = 0; i < urmum ;i++)
        {
            res.push_back(righti[i]);
        }
    }
    if(ptr->left != NULL)
    {
        vector<string> lefti = myal(ptr->left,symtable);
        int valo = lefti.size();
        for(int i = 0; i < valo ;i++)
        {
            res.push_back(lefti[i]);
        }
    }
    res.push_back(ptr->type);
    return res;
}

void EPPCompiler::compile(vector<vector<string>> code){
    int sz = code.size();
    int dell = -2;
    vector<string> res;
    for(int i = 0; i < sz;i++)
    {
        if(code[i][0] == "del")
        {
            dell = targ.symtable->search(code[i][2]);
            this->targ.last_deleted = dell;
            targ.parse(code[i]);
            this->least_mem_loc.push_heap(dell);
            res.push_back("DEL = mem[" + to_string(dell) + "]");
        }
        else
        {
            int ads = -2;
            if(code[i][0] == "ret")
            {
                targ.parse(code[i]);
            }
            else
            {
                targ.parse(code[i]);
                if(this->targ.symtable->search(code[i][0]) == -1)
                {    
                    ads = this->least_mem_loc.get_min();
                    this->least_mem_loc.pop();
                    this->targ.symtable->assign_address(code[i][0],ads);
                }
            }
            vector<string> kelly = EPPCompiler::generate_targ_commands();
            int yummy = kelly.size();
            for(int i = 0; i < yummy;i++)
            {
                res.push_back(kelly[i]);
            }
            if(code[i][0] == "ret")
            {
                break;
            }
        }
    }
    EPPCompiler::write_to_file(res);
}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* ptr = targ.expr_trees.back()->right;
    if(targ.expr_trees.back()->left->type == "DEL")
    {
        vector<string> cmd;
        cmd.push_back("DEL = mem[" + to_string(this->targ.last_deleted) + "]");
        return cmd;
    }
    vector<string> res;
    vector<string> kelly = myal(ptr,targ.symtable);
    int yummy = kelly.size();
    for(int i = 0; i < yummy;i++)
    {
        res.push_back(kelly[i]);
    }
    if(targ.expr_trees.back()->left->type == "RET")
    {
        res.push_back("RET = POP");
    }
    else
    {
        res.push_back("mem[" + to_string(targ.symtable->search(targ.expr_trees.back()->left->id)) + "] = POP");
    }
    return res;
}

void EPPCompiler::write_to_file(vector<string> commands){
    fstream file_handle;
    file_handle.open(output_file, std::ios::out);
    int boom = commands.size();
    for (int i = 0; i < boom; i++){
        file_handle << commands[i] <<"\n";
    }
    file_handle.close();
}

EPPCompiler::~EPPCompiler(){
}
