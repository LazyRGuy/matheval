/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

UnlimitedInt::UnlimitedInt()
{
    this->size = 1;
    this->sign = 0;
    this->unlimited_int = new int[1];
    this->unlimited_int[0] = 0;
    this->capacity = 1;
}

UnlimitedInt::UnlimitedInt(string s)
{
    if(s[0] == '0')
    {
        this->size = 1;
        this->sign = 0;
        this->unlimited_int = new int[1];
        this->unlimited_int[0] = 0;
        this->capacity = 1;
    }
    else
    {
        if(s[0] == '-')
        {
            this->size = s.size()-1;
            this->sign = -1;
        }
        else
        {
            this->size = s.size();
            this->sign = 1;
        }
        this->capacity = this->size;
        this->unlimited_int = new int[this->size];
        for(int i = 0; i < this->size;i++)
        {
            this->unlimited_int[this->size-1-i] = s[s.size()-1-i] - '0';
        }
    }
}

UnlimitedInt::UnlimitedInt(int i)
{
    std::string s = std::to_string(i);
    if(s[0] == '0')
    {
        this->size = 1;
        this->sign = 0;
        this->unlimited_int = new int[1];
        this->unlimited_int[0] = 0;
        this->capacity = 1;
    }
    else
    {
        if(s[0] == '-')
        {
            this->size = s.size()-1;
            this->sign = -1;
        }
        else
        {
            this->size = s.size();
            this->sign = 1;
        }
        this->capacity = this->size;
        this->unlimited_int = new int[this->size];
        for(int i = 0; i < this->size;i++)
        {
            this->unlimited_int[this->size-1-i] = s[s.size()-1-i] - '0';
        }
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz)
{
    int* temp = new int[sz];
    for(int i = 0; i < sz;i++)
    {
        temp[i] = ulimited_int[i];
    }
    this->unlimited_int = temp;
    this->capacity = cap;
    this->sign = sgn;
    this->size = sz;
}

UnlimitedInt::~UnlimitedInt()
{
    delete[] this->unlimited_int;
}

int UnlimitedInt::get_size()
{
    return this->size;
}

int* UnlimitedInt::get_array()
{
    return this->unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return this->sign;
}

int UnlimitedInt::get_capacity()
{
    return this->capacity;
}

string UnlimitedInt::to_string()
{
     string ans;
    if (this->sign == -1)
    {
        ans = "-";
    }
    else
    {
        ans = "";
    }
    for (int i = 0; i < this->size; i++)
    {
        char ad = unlimited_int[i] + '0';
        ans = ans + ad;
    }
    return ans;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2)
{
    int sgn;
    int sz;
    if(i1->sign == 0)
    {
        UnlimitedInt* i3 = new UnlimitedInt(i2->to_string());
        return i3;
    }
    if(i2->sign == 0)
    {
        UnlimitedInt* i3 = new UnlimitedInt(i1->to_string());
        return i3;
    }
    if(i2->sign != i1->sign)
    {
        UnlimitedInt* copy = new UnlimitedInt(i2->unlimited_int,i2->size,i1->sign,i2->size);
        UnlimitedInt* ans = UnlimitedInt::sub(i1,copy);
        delete copy;
        return ans;
    }
    else
    {
        sgn = i1->sign;
    }
    int br = 0;
    if(i1->size < i2->size)
    {
        UnlimitedInt* temp = i1;
        i1 = i2;
        i2 = temp;
        br = 1;
    }
    int* added = new int[i1->size+1];
    added[0] = 0;
    for(int i = 0; i < i1->size; i++)
    {
        if(i >= i2->size)
        {
            added[i1->size-i] = i1->unlimited_int[i1->size-1-i];
        }
        else
        {
            added[i1->size-i] = i1->unlimited_int[i1->size-1-i] + i2->unlimited_int[i2->size-1-i];
        }
    }
    for(int i = i1->size;i > 0;i--)
    {
        added[i-1] += added[i]/10;
        added[i] = added[i]%10;
    }
    if(added[0] != 0)
    {
        sz = i1->size+1;
        UnlimitedInt* ans = new UnlimitedInt(added,sz,sgn,sz);
        delete[] added;
        if(br == 1)
        {
            UnlimitedInt* themp = i1;
            i1 = i2;
            i2 = themp;
        }
        return ans;
    }
    else
    {
        int *tp = new int[i1->size];
        for(int i = 0;i < i1->size;i++)
        {
            tp[i] = added[i+1];
        }
        sz = i1->size;
        delete[] added;
        UnlimitedInt* ans = new UnlimitedInt(tp,sz,sgn,sz);
        delete[] tp;
        if(br == 1)
        {
            UnlimitedInt* themp = i1;
            i1 = i2;
            i2 = themp;
        }
        return ans;
    }
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1,UnlimitedInt* i2)
{
    int sgn;
    int sz;
    if(i1->sign == 0)
    {
        UnlimitedInt* i3 = new UnlimitedInt(i2->to_string());
        i3->sign = i3->sign*(-1);
        return i3;
    }
    if(i2->sign == 0)
    {
        UnlimitedInt* i3 = new UnlimitedInt(i1->to_string());
        return i3;
    }
    if(i2->sign != i1->sign)
    {
        UnlimitedInt* copy = new UnlimitedInt(i2->unlimited_int,i2->size,i1->sign,i2->size);
        UnlimitedInt* ans = UnlimitedInt::add(i1,copy);
        delete copy;
        return ans;
    }
    else
    {
        sgn = i1->sign;
    }
    int br = 0;
    if(i1->size < i2->size)
    {
        UnlimitedInt* temp = i1;
        i1 = i2;
        i2 = temp;
        sgn = sgn*(-1);
        br = 1;
    }
    int* added = new int[i1->size];
    for(int i = 0; i < i1->size;i++)
    {
        if(i >= i2->size)
        {
            added[i1->size-1-i] = i1->unlimited_int[i1->size-1-i];
        }
        else
        {
            added[i1->size-1-i] = i1->unlimited_int[i1->size-1-i] - i2->unlimited_int[i2->size-1-i];
        }
    }
    int cnt = 0;
    for(int i = i1->size-1;i >= 0;i--)
    {
        if(i!= 0 && added[i] < 0)
        {
            added[i] += 10;
            added[i-1] -= 1;
            if(added[i] == 0)
            {
                cnt += 1;
            }
            else
            {
                cnt = 0;
            }
        }
        else if(i == 0 && added[i] < 0)
        {
            added[i] = added[i]*(-1);
            sgn = sgn*(-1);
        }
        else if(added[i] == 0)
        {
            cnt += 1;
        }
        else
        {
            cnt = 0;
        }
    }
    if(cnt != 0)
    {
        if(i1->size == cnt)
        {
            delete[] added;
            if(br == 1)
            {
                UnlimitedInt* themp = i1;
                i1 = i2;
                i2 = themp;
            }
            return new UnlimitedInt();
        }
        int* tp = new int[i1->size-cnt];
        for(int i = 0; i < i1->size-cnt;i++)
        {
            tp[i] = added[i+cnt];
        }
        sz = i1->size-cnt;
        delete[] added;
        UnlimitedInt* ans = new UnlimitedInt(tp,sz,sgn,sz);
        delete[] tp;
        if(br == 1)
        {
            UnlimitedInt* themp = i1;
            i1 = i2;
            i2 = themp;
        }
        return ans;
    }
    else
    {
        sz = i1->size;
        UnlimitedInt* ans = new UnlimitedInt(added,sz,sgn,sz);
        delete[] added;
        if(br == 1)
        {
            UnlimitedInt* themp = i1;
            i1 = i2;
            i2 = themp;
        }
        return ans;
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2)
{
    if(i1->sign == 0 || i2->sign == 0)
    {
        UnlimitedInt* zero = new UnlimitedInt();
        return zero;
    }
    int sgn;
    int sz;
    if(i1->sign != i2->sign)
    {
        sgn = -1;
    }
    else
    {
        sgn = 1;
    }
    sz=i1->size+i2->size;
    int* ans =new int[sz];
    for (int i = 0; i < sz; i++)
    {
        ans[i] = 0;
    }
    for (int i = i1->size-1;i>=0; i--)
    {
        for (int j = i2->size-1; j >=0; j--)
        {
            ans[i+j+1] += i1->unlimited_int[i]*i2->unlimited_int[j];
        }
    }
    for (int i=sz-1;i>0;i--)
    {
        ans[i-1] += ans[i]/10;
        ans[i] = ans[i]%10;
    }
    if(ans[0] == 0)
    {
        int * tp = new int[sz-1];
        for(int i = 0; i < sz-1;i++)
        {
            tp[i] = ans[i+1];
        }
        delete[] ans;
        UnlimitedInt* final = new UnlimitedInt(tp,sz-1,sgn,sz-1);
        delete[] tp;
        return final;
    }
    else
    {
        UnlimitedInt* final = new UnlimitedInt(ans,sz,sgn,sz);
        delete[] ans;
        return final;
    }
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2)
{
    if(i2->sign == 0)
    {
        UnlimitedInt* zero = new UnlimitedInt();
        return zero;
    }
    if(i1->sign == 0)
    {
        UnlimitedInt* zero = new UnlimitedInt();
        return zero;
    }
    int sgn;
    if(i1->sign != i2->sign)
    {
        sgn = -1;
    }
    else
    {
        sgn = 1;
    }
    if(i1->size < i2->size)
    {
        if(sgn == 1)
        {
            return new UnlimitedInt(0);
        }
        else
        {
            return new UnlimitedInt(-1);
        }
    }
    int* subu = new int[i2->size];
    UnlimitedInt* dup = new UnlimitedInt(i2->to_string());
    dup->sign = 1;
    for(int i = 0; i < i2->size;i++)
    {
        subu[i] = i1->unlimited_int[i];
    }
    UnlimitedInt* itr = new UnlimitedInt(subu,i2->size,1,i2->size);
    delete[] subu;
    string ans = "";
    int br = 0;
    for(int i = i2->size-1;i < i1->size;i++)
    {
        int cnt = 0;
        UnlimitedInt* tempi = UnlimitedInt::sub(itr,dup);
        while(tempi->sign != -1)
        {
            delete itr;
            itr = tempi;
            tempi = UnlimitedInt::sub(itr,dup);
            cnt++;
            br = 1;
        }
        delete tempi;
        if(br == 1)
        {
        char tp = cnt + '0';
        ans = ans + tp;
        }
        if(i != i1->size-1)
        {
            subu = new int[itr->size+1];
            for(int i = 0; i < itr->size;i++)
            {
                subu[i] = itr->unlimited_int[i];
            }
            subu[itr->size] = i1->unlimited_int[i+1];
            int sz = itr->size+1;
            delete itr;
            itr = new UnlimitedInt(subu,sz,1,sz);
            delete[] subu;
        }
    }
    if(sgn == -1)
    {
        if(itr->sign == 0)
        {
            UnlimitedInt* tempu = new UnlimitedInt(ans);
            tempu->sign = sgn;
            delete itr;
            delete dup;
            return tempu;
        }
        else
        {
            UnlimitedInt* tempie = new UnlimitedInt(ans);
            UnlimitedInt* one = new UnlimitedInt(1);
            UnlimitedInt* tmpu = UnlimitedInt::add(tempie,one);
            delete tempie;
            delete one;
            delete dup;
            delete itr;
            return tmpu;
        }
    }
    else
    {
        delete itr;
        delete dup;
        return new UnlimitedInt(ans);
    }
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2)
{
    UnlimitedInt* q = UnlimitedInt::div(i1,i2);
    UnlimitedInt* p = UnlimitedInt::mul(i2,q);
    UnlimitedInt* r = UnlimitedInt::sub(i1,p);
    delete q;
    delete p;
    return r;
}