#include <iostream>

using namespace std;


class Graf
{

protected:
    int n;
public:
    Graf()
    {
        n=0;
    }
    Graf (int n1)
    {
        n=n1;
    }
    Graf (const Graf &b)
    {
        this->n=b.n;
    }
    ~Graf() {}
    int get_n()
    {
        return this->n;
    }
    Graf & operator = (Graf b);
    virtual void afisare()
    {
        cout<<"nr de noduri din graf este: "<<endl;
        cout<<n;
    }
    friend istream & operator >> (istream &in, Graf &g);
    friend ostream & operator << (ostream &out, Graf &g);
    friend class Matrice;
    friend class Graf_complet;
    friend class Graf_antisimetric;
};

class Matrice:public Graf
{
protected:
    int mat[101][101];
public:
    Matrice ()
    {
        n=0;
    }
    Matrice (int **mat)
    {
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                mat[i][j]=0;
    }
    Matrice (const Matrice &b)
    {
        this->n=b.n;
        for(int i=1; i<=b.n; i++)
            for(int j=1; j<=b.n; j++)
                if(b.mat[i][j]==1)
                {
                    this->mat[i][j]=1;
                }
    }
    ~Matrice() {}
    int getval(int i,int j);
    void setval(int i,int j,int val);
    Matrice & operator = (Matrice b);
    friend istream & operator >> (istream &in, Matrice &m);
    friend ostream & operator << (ostream &out, const Matrice &m);
    friend class Graf_antisimetric;
    friend class Graf;
    friend class Graf_complet;
    friend class Graf_turneu;
};

class Graf_complet:public Graf
{
protected:
    int nr_muchii;
public:

    Graf_complet ()
    {
        nr_muchii=0;
    }
    Graf_complet (int nr)
    {
        nr_muchii=nr;
    }
    Graf_complet (const Graf &b)
    {
        this->nr_muchii=b.n;
    }
    ~Graf_complet() {}
    void afisare()
    {
        cout<<"nr de noduri din graf_complet este: "<<endl;
        cout<<nr_muchii;
    }
    Graf_complet & operator = (Graf_complet b);
    friend istream & operator >> (istream &in, Graf_complet &g);
    friend ostream & operator << (ostream &out, Graf_complet &g);
};

class Graf_antisimetric:public Graf
{
protected:
    Matrice m;
public:

    Graf_antisimetric ()
    {
        n=0;
    }

    Graf_antisimetric (Matrice m)
    {
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                m.mat[i][j]=0;
    }
    Graf_antisimetric (const Graf_antisimetric &b)
    {
        this->n=b.n;
        for(int i=1; i<=b.n; i++)
            for(int j=1; j<=b.n; j++)
                if(b.m.mat[i][j]==1)
                {
                    this->m.mat[i][j]=1;
                }
    }
    ~Graf_antisimetric(){}
    void afisare()
    {
        cout<<"arcele grafului_antisimetric sunt: "<<endl;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
            {
                if(m.getval(i,j)==1)
                    cout<<"arc de la "<<i<<" la "<<j<<endl;
            }
    }
    Graf_antisimetric & operator = (Graf_antisimetric b);
    friend istream & operator >> (istream &in, Graf_antisimetric &m);
    friend ostream & operator << (ostream &out, Graf_antisimetric &m);
    friend class Matrice;

};

class Graf_turneu:public Graf_antisimetric,public Graf_complet
{
protected:
    Matrice g_m;
    int g_nr_noduri;
    int complet,antisimetric,turneu;
public:
    int is_complet();
    int is_antisimetric();
    int is_turneu();
    void afisare()
    {
        cout<<"arcele grafului_turneu sunt: "<<endl;
        for(int i=1; i<=g_nr_noduri; i++)
            for(int j=1; j<=g_nr_noduri; j++)
            {
                if(g_m.getval(i,j)==1)
                    cout<<"arc de la "<<i<<" la "<<j<<endl;
            }
    }
    ~Graf_turneu(){}
    void set_valori();
    void afis_valori();
    friend Matrice;
    friend class Graf;
    friend class Graf_antisimetric;
    friend class Graf_complet;
    Graf_turneu & operator = (Graf_turneu &b);
    friend istream & operator >> (istream &in, Graf_turneu &m);
    friend ostream & operator << (ostream &our, Graf_turneu &m);

};
////////
istream & operator >> (istream &in, Matrice &m)
{
    int n,nr,x,y;
    cout<<"cate noduri are graful pus in matrice: "<<endl;
    in>>m.n;
    cout<<"cate arce are graful pus in matrice: "<<endl;
    in>>nr;
    for(int i=1; i<=nr; i++)
    {
        cout<<"arc de la x la y: "<<endl;
        in>>x>>y;
        m.mat[x][y]=1;
    }
    return in;
}

ostream & operator << (ostream &out, const Matrice &m)
{
    cout<<"arcele grafului sunt: "<<endl;
    for(int i=1; i<=m.n; i++)
        for(int j=1; j<=m.n; j++)
        {
            if(m.mat[i][j]==1)
                cout<<"arc de la "<<i<<" la "<<j<<endl;
        }
    return out;
}

Matrice & Matrice::operator = (Matrice b)
{
    this->n=b.n;
    for(int i=1; i<=b.n; i++)
        for(int j=1; j<=b.n; j++)
            if(b.mat[i][j]==1)
            {
                this->mat[i][j]=1;
            }
    return *this;
}

int Matrice::getval(int i,int j)
{
    return this->mat[i][j];
}

void Matrice::setval(int i,int j,int val)
{
    this->mat[i][j]=val;
}
///////////////
istream & operator >> (istream &in, Graf &g)
{
    cout<<"nr de noduri din graf: "<<endl;
    in>>g.n;
    return in;
}

ostream & operator << (ostream &out, Graf &g)
{
    cout<<"nr de noduri din graf este: "<<endl;
    out<<g.n;
    return out;
}

Graf & Graf::operator = (Graf b)
{
    this->n=b.n;
}
////////////////
istream & operator >> (istream &in, Graf_complet &g)
{
    cout<<"nr de noduri din graf_complet: "<<endl;
    in>>g.nr_muchii;
    return in;
}

ostream & operator << (ostream &out, Graf_complet &g)
{
    cout<<"nr de noduri din graf_complet este: "<<endl;
    out<<g.nr_muchii;
    return out;
}

Graf_complet & Graf_complet::operator = (Graf_complet b)
{
    this->nr_muchii=b.nr_muchii;
}
////////////////
istream & operator >> (istream &in, Graf_antisimetric &m)
{
    int n,nr,x,y;
    cout<<"cate noduri are graful_antisimetric pus in matrice: "<<endl;
    in>>m.n;
    cout<<"cate arce are graful_antisimetric pus in matrice: "<<endl;
    in>>nr;
    for(int i=1; i<=nr; i++)
    {
        cout<<"arc de la x la y: "<<endl;
        in>>x>>y;
        m.m.setval(x,y,1);
    }

    return in;
}

ostream & operator << (ostream &out, Graf_antisimetric &m)
{
    cout<<"arcele grafului_antisimetric sunt: "<<endl;
    for(int i=1; i<=m.n; i++)
        for(int j=1; j<=m.n; j++)
        {
            if(m.m.getval(i,j)==1)
                cout<<"arc de la "<<i<<" la "<<j<<endl;
        }
    return out;
}

Graf_antisimetric & Graf_antisimetric::operator = (Graf_antisimetric b)
{
    this->n=b.n;
    for(int i=1; i<=b.n; i++)
        for(int j=1; j<=b.n; j++)
            if(b.m.mat[i][j]==1)
            {
                this->m.mat[i][j]=1;
            }
    return *this;
}
////////////////
int Graf_turneu::is_complet()
{
    int i,j;
    for(j=1; j<=this->g_nr_noduri; j++)
    {
        int ok=0;
        for(int i=1; i<=this->g_nr_noduri; i++)
            if(this->g_m.getval(i,j)==1)
                ok=1;
        if(ok==0)
            return 0;
    }
    return 1;
}

int Graf_turneu::is_antisimetric()
{
    int i,j;
    for(i=1; i<=this->g_nr_noduri; i++)
        for(j=1; j<=this->g_nr_noduri; j++)
            if(this->g_m.getval(i,j)==1 && this->g_m.getval(j,i)==1)
                return 0;
    return 1;
}

int Graf_turneu::is_turneu()
{
    if(Graf_turneu::is_complet()==1 && Graf_turneu::is_antisimetric()==1)
        return 1;
    return 0;
}

void Graf_turneu::set_valori()
{
    this->complet=Graf_turneu::is_complet();
    this->antisimetric=Graf_turneu::is_antisimetric();
    this->turneu=Graf_turneu::is_turneu();
}

void Graf_turneu::afis_valori()
{
    set_valori();
    cout<<"este complet: "<<endl<<this->complet<<endl<<"este antisimetric: "<<endl<<this->antisimetric<<endl<<"este turneu: "<<endl<<this->turneu<<endl;
}

istream & operator >> (istream &in, Graf_turneu &m)
{
    int n,nr,x,y;
    cout<<"cate noduri are graful_turneu pus in matrice: "<<endl;
    in>>m.g_nr_noduri;
    cout<<"cate arce are graful_turneu pus in matrice: "<<endl;
    in>>nr;
    for(int i=1; i<=nr; i++)
    {
        cout<<"arc de la x la y: "<<endl;
        in>>x>>y;
        m.g_m.setval(x,y,1);
    }
    return in;
}

ostream & operator << (ostream &out, Graf_turneu &m)
{
    cout<<"arcele grafului_turneu sunt: "<<endl;
    for(int i=1; i<=m.g_nr_noduri; i++)
        for(int j=1; j<=m.g_nr_noduri; j++)
        {
            if(m.g_m.getval(i,j)==1)
                cout<<"arc de la "<<i<<" la "<<j<<endl;
        }
    return out;
}

Graf_turneu & Graf_turneu::operator = (Graf_turneu &b)
{
    this->g_nr_noduri=b.g_nr_noduri;
    for(int i=1; i<=b.g_nr_noduri; i++)
        for(int j=1; j<=b.g_nr_noduri; j++)
        {
            if(b.g_m.mat[i][j]==1)
            {
                this->g_m.setval(i,j,1);
            }
        }
    return *this;
}

int main()
{
    Graf_turneu gt1,gt2;
    Graf_antisimetric ga1,ga2;
    Graf_complet gc1,gc2;
    Graf g1,g2;
    cin>>gt1;
    gt1.afisare();

    return 0;
}
