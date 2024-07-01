/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
UnlimitedRational::UnlimitedRational()
{
    this->p = new UnlimitedInt();
    this->q = new UnlimitedInt(1);
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den)
{
    this->p = num;
    this->q = den;
}

UnlimitedRational::~UnlimitedRational()
{
    delete this->p;
    delete this->q;
}

UnlimitedInt* UnlimitedRational::get_p()
{
    return this->p;
}

UnlimitedInt* UnlimitedRational::get_q()
{
    return this->q;
}

string UnlimitedRational::get_p_str()
{
    return this->p->to_string();
}

string UnlimitedRational::get_q_str()
{
    return this->q->to_string();
}

string UnlimitedRational::get_frac_str()
{
    return this->p->to_string() + '/' + this->q->to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2)
{
    if(i2->q->get_sign() == 0 || i1->q->get_sign() == 0)
    {
        UnlimitedInt* zero = new UnlimitedInt();
        UnlimitedInt* zehro = new UnlimitedInt();
        UnlimitedRational* ans = new UnlimitedRational(zero,zehro);
        return ans;
    }
    UnlimitedInt* aq = UnlimitedInt::mul(i1->q,i2->q);
    UnlimitedInt* ap = UnlimitedInt::mul(i1->p,i2->q);
    UnlimitedInt* dell = ap;
    UnlimitedInt* bp = UnlimitedInt::mul(i1->q,i2->p);
    ap = UnlimitedInt::add(ap,bp);
    UnlimitedInt* dp = new UnlimitedInt(ap->UnlimitedInt::to_string());
    UnlimitedInt* dq = new UnlimitedInt(aq->UnlimitedInt::to_string());
    delete bp;
    delete dell;
    UnlimitedInt* temp;
    while(aq->get_sign() != 0)
    {
        temp = aq;
        aq = UnlimitedInt::mod(ap,aq);
        UnlimitedInt* tp = ap;
        ap = temp;
        delete tp;
    }
    UnlimitedInt* md = ap;
    ap = UnlimitedInt::div(dp,md);
    dell = aq;
    aq = UnlimitedInt::div(dq,md);
    delete dp;
    delete dell;
    delete md;
    delete dq;
    UnlimitedRational* ans = new UnlimitedRational(ap,aq);
    return ans;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedInt* minus = new UnlimitedInt(-1);
    UnlimitedInt* del = new UnlimitedInt(i2->p->UnlimitedInt::to_string());
    UnlimitedInt* dell = del;
    del = UnlimitedInt::mul(minus,del);
    delete minus;
    delete dell;
    UnlimitedInt* cq = new UnlimitedInt(i2->q->UnlimitedInt::to_string());
    UnlimitedRational* rat = new UnlimitedRational(del,cq);
    UnlimitedRational* mine = UnlimitedRational::add(i1,rat);
    delete rat;
    return mine;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1,UnlimitedRational* i2)
{
    if(i2->q->get_sign() == 0 || i1->q->get_sign() == 0)
    {
        UnlimitedInt* zero = new UnlimitedInt();
        UnlimitedInt* zehro = new UnlimitedInt();
        UnlimitedRational* ans = new UnlimitedRational(zero,zehro);
        return ans;
    }
    UnlimitedInt* ap = UnlimitedInt::mul(i1->p,i2->p);
    UnlimitedInt* aq = UnlimitedInt::mul(i2->q,i1->q);
    UnlimitedInt* dp = new UnlimitedInt(ap->UnlimitedInt::to_string());
    UnlimitedInt* dq = new UnlimitedInt(aq->UnlimitedInt::to_string());
    UnlimitedInt* temp;
    while(aq->get_sign() != 0)
    {
        temp = aq;
        aq = UnlimitedInt::mod(ap,aq);
        UnlimitedInt* tp = ap;
        ap = temp;
        delete tp;
    }
    UnlimitedInt* md = ap;
    ap = UnlimitedInt::div(dp,md);
    UnlimitedInt* dell = aq;
    aq = UnlimitedInt::div(dq,md);
    delete dp;
    delete dell;
    delete md;
    delete dq;
    UnlimitedRational* ans = new UnlimitedRational(ap,aq);
    return ans;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1,UnlimitedRational* i2)
{
    if(i2->p->get_sign() == 0 || i1->q->get_sign() == 0)
    {
        UnlimitedInt* zero = new UnlimitedInt();
        UnlimitedInt* zehro = new UnlimitedInt();
        UnlimitedRational* ans = new UnlimitedRational(zero,zehro);
        return ans;
    }
    UnlimitedInt* ap = UnlimitedInt::mul(i1->p,i2->q);
    UnlimitedInt* aq = UnlimitedInt::mul(i2->p,i1->q);
    UnlimitedInt* dp = new UnlimitedInt(ap->UnlimitedInt::to_string());
    UnlimitedInt* dq = new UnlimitedInt(aq->UnlimitedInt::to_string());
    UnlimitedInt* temp;
    while(aq->get_sign() != 0)
    {
        temp = aq;
        aq = UnlimitedInt::mod(ap,aq);
        UnlimitedInt* tp = ap;
        ap = temp;
        delete tp;
    }
    UnlimitedInt* md = ap;
    ap = UnlimitedInt::div(dp,md);
    UnlimitedInt* dell = aq;
    aq = UnlimitedInt::div(dq,md);
    delete dp;
    delete dell;
    delete md;
    delete dq;
    UnlimitedRational* ans = new UnlimitedRational(ap,aq);
    return ans;
}