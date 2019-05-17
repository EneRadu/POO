#include <iostream>
#include <string.h>
#include <vector>
#include <stdexcept>
using namespace std;

struct data{
    int zi,luna,an;
};

class Detinator{
protected:
    char nume[100];
    int index;
    int is_cont_e;
    int is_cont_n;
public:
    Detinator(){
        index=0;
    }
    Detinator(int i){
        index=i;
    }
    ~Detinator(){}
    void set_index(int i){
        index=i;
    }
    int get_index(){
        return index;
    }
    int get_cont_e(){
        return is_cont_e;
    }
    int get_cont_n(){
        return is_cont_n;
    }
    void citire();
    virtual void afisare(){
        cout<<endl;
        cout<<"Numele: "<<endl;
        cout<<nume<<endl;
        //cout<<"Indexul: "<<endl;
        //cout<<index<<endl;
        cout<<"Tipuri de conturi: economic/normal "<<endl;
        cout<<is_cont_e<<" "<<is_cont_n<<endl;
    }
    Detinator & operator = (Detinator b);
};

void Detinator::citire(){
    cout<<"Introduceti numele: "<<endl;
    cin>>this->nume;
    cout<<"Ce tipuri de conturi? (0/1) pt economic, (0/1) pt normal: "<<endl;
    cin>>this->is_cont_e>>this->is_cont_n;
}

Detinator & Detinator::operator = (Detinator b){
    strcpy(this->nume,b.nume);
    this->index=b.index;
    this->is_cont_e=b.is_cont_e;
    this->is_cont_n=b.is_cont_n;
}

class Cont_economii:public Detinator{
protected:
    int index;
    data deschidere;
    int sold;
    int rata;
    int istoric[1001];
    int istoric_nr;
public:
    Cont_economii(){
        istoric_nr=1;
    }
    Cont_economii(int i){
        index=i;
    }
    ~Cont_economii(){}
    void set_index(int i){
        index=i;
    }
    int get_index(){
        return index;
    }
    void citire();
    void afisare(){
        cout<<endl;
        cout<<"Sold curent: "<<endl;
        cout<<sold<<endl;
        cout<<"Data deschiderii: "<<endl;
        cout<<deschidere.zi<<" "<<deschidere.luna<<" "<<deschidere.an<<endl;
        cout<<"Rata: "<<endl;
        cout<<rata<<endl;
        cout<<endl;
        cout<<"Istoricul contului: "<<endl;
        for(int i=0;i<istoric_nr;i++)
            cout<<istoric[i]<<" ";
        cout<<endl;
    }
    void extragere(int i){
        sold=sold-i;
        istoric[istoric_nr++]=sold;
    }
    void adaugare(int i){
        sold=sold+i;
        istoric[istoric_nr++]=sold;
    }
    Cont_economii & operator = (Cont_economii b);
};

void Cont_economii::citire(){
    cout<<"Data deschiderii: "<<endl;
    cin>>this->deschidere.zi>>this->deschidere.luna>>this->deschidere.an;
    cout<<"Soldul: "<<endl;
    cin>>this->sold;
    this->istoric[0]=sold;
    cout<<"Rata dorita: 3/6/12 "<<endl;
    cin>>this->rata;
}

Cont_economii & Cont_economii::operator = (Cont_economii b){
    this->index=b.index;
    this->deschidere=b.deschidere;
    this->sold=b.sold;
    this->rata=b.rata;
    this->istoric_nr=b.istoric_nr;
    for(int i=0;i<this->istoric_nr;i++)
        this->istoric[i]=b.istoric[i];
}

class Cont_normal:public Detinator{
protected:
    int index;
    data deschidere;
    int sold;
    int nr_gratuite;
public:
    Cont_normal(){
        nr_gratuite=10;
    }
    Cont_normal(int i){
        index=i;
    }
    ~Cont_normal(){}
    void set_index(int i){
        index=i;
    }
    int get_index(){
        return index;
    }
    void citire();
    void afisare(){
        cout<<endl;
        cout<<"Sold curent: "<<endl;
        cout<<sold<<endl;
        cout<<"Data deschiderii: "<<endl;
        cout<<deschidere.zi<<" "<<deschidere.luna<<" "<<deschidere.an<<endl;
        cout<<"Nr tranzactiilor gratuite ramase: "<<endl;
        cout<<nr_gratuite<<endl;
    }
    void extragere(int i){
        if(nr_gratuite!=0){
            nr_gratuite--;
            sold=sold-i;
        }
        else
            sold=sold-i-5;
    }
    void adaugare(int i){
        sold=sold+i;
    }
    Cont_normal & operator = (Cont_normal b);
};

void Cont_normal::citire(){
    cout<<"Data deschiderii: "<<endl;
    cin>>this->deschidere.zi>>this->deschidere.luna>>this->deschidere.an;
    cout<<"Soldul: "<<endl;
    cin>>this->sold;
}

Cont_normal & Cont_normal::operator = (Cont_normal b){
    this->index=b.index;
    this->deschidere=b.deschidere;
    this->sold=b.sold;
    this->nr_gratuite=b.nr_gratuite;
}

template <class T1,class T2>
class Conturi{
protected:
    vector <T1> cont_economii;
    vector <T2> cont_normal;
    int nr_index;
public:
    Conturi(){
        nr_index=0;
    }
    Conturi(int i){
        nr_index=i;
    }
    ~Conturi(){}
    void set_index(int i){
        nr_index=i;
    }
    int get_index(){
        return nr_index;
    }
    void push_eco(T1 const&);
    void push_nor(T2 const&);
    void pop_eco();
    void pop_nor();
    friend int main();
    friend class Cont_economii;
    friend class Cont_normal;
    Conturi & operator += (int i);
};

template <class T1,class T2>
void Conturi<T1,T2>::push_eco (T1 const& cont) {
   cont_economii.push_back(cont);
}

template <class T1,class T2>
void Conturi<T1,T2>::push_nor (T2 const& cont) {
   cont_normal.push_back(cont);
}

template <class T1,class T2>
void Conturi<T1,T2>::pop_eco (){
    if(cont_economii.empty())
        throw out_of_range("no_space");
    cont_economii.pop_back();
}

template <class T1,class T2>
void Conturi<T1,T2>::pop_nor (){
    if(cont_normal.empty())
        throw out_of_range("no_space");
    cont_normal.pop_back();
}

template<class T1,class T2>
Conturi<T1,T2> & Conturi<T1,T2>::operator += (int i){
    this->nr_index++;
}

int main()
{
    int choice=-1;
    int nr_det;
    Conturi<Cont_economii,Cont_normal> banca;
    Detinator d[100];
    while(choice!=11){
        cout<<endl;
        cout<<"(1) Introducere de detinatori de conturi"<<endl;
        cout<<"(2) Adaugare bani in soldul unui cont de economii"<<endl;
        cout<<"(3) Adaugare bani in soldul unui cont normal"<<endl;
        cout<<"(4) Extragere bani din soldul unui cont de economii"<<endl;
        cout<<"(5) Extragere bani din soldul unui cont normal"<<endl;
        cout<<"(6) Afisare date despre un cont de economii"<<endl;
        cout<<"(7) Afisare date despre un cont normal"<<endl;
        cout<<"(8) Afisare date despre un detinator de cont"<<endl;
        cout<<"(9) Afisare nr detinatori totali"<<endl;
        cout<<"(10) Afisare nr conturi totale"<<endl;
        cout<<"(11) Iesire"<<endl;
        cout<<endl<<"Introduceti alegerea dorita "<<endl;
        cin>>choice;
        switch(choice){
            case 1:{

                cout<<endl<<"Introduceti nr de detinatori care doriti sa ii adaugati"<<endl;
                cin>>nr_det;
                for(int i=0;i<nr_det;i++){
                    cout<<endl<<"Introduceti datele pt detinatorul "<<i<<endl;
                    d[i].citire();
                    d[i].set_index(i);
                    if(d[i].get_cont_e()){
                        Cont_economii ce;
                        cout<<endl<<"Introduceti datele pt detinatorul "<<i<<" contul de economii"<<endl;
                        ce.citire();
                        ce.set_index(i);
                        banca.push_eco(ce);
                        banca.nr_index+=1;
                    }
                    if(d[i].get_cont_n()){
                        Cont_normal cn;
                        cout<<endl<<"Introduceti datele pt detinatorul "<<i<<" contul normal"<<endl;
                        cn.citire();
                        cn.set_index(i);
                        banca.push_nor(cn);
                        banca.nr_index+=1;
                    }
                }
                break;
            }
            case 2:{
                cout<<endl<<"Introduceti indexul"<<endl;
                int index;
                cin>>index;
                cout<<endl<<"Introduceti suma de bani de adaugat"<<endl;
                int suma;
                cin>>suma;
                for(int i=0;i<nr_det;i++)
                    if(banca.cont_economii[i].get_index()==index)
                        banca.cont_economii[i].adaugare(suma);
                break;
            }
            case 3:{
                cout<<endl<<"Introduceti indexul"<<endl;
                int index;
                cin>>index;
                cout<<endl<<"Introduceti suma de bani de adaugat"<<endl;
                int suma;
                cin>>suma;
                for(int i=0;i<nr_det;i++)
                    if(banca.cont_normal[i].get_index()==index)
                        banca.cont_normal[i].adaugare(suma);
                break;
            }
            case 4:{
                cout<<endl<<"Introduceti indexul"<<endl;
                int index;
                cin>>index;
                cout<<endl<<"Introduceti suma de bani de extras"<<endl;
                int suma;
                cin>>suma;
                for(int i=0;i<nr_det;i++)
                    if(banca.cont_economii[i].get_index()==index)
                        banca.cont_economii[i].extragere(suma);
                break;
            }
            case 5:{
                cout<<endl<<"Introduceti indexul"<<endl;
                int index;
                cin>>index;
                cout<<endl<<"Introduceti suma de bani de extras"<<endl;
                int suma;
                cin>>suma;
                for(int i=0;i<nr_det;i++)
                    if(banca.cont_normal[i].get_index()==index)
                        banca.cont_normal[i].extragere(suma);
                break;
            }
            case 6:{
                cout<<endl<<"Introduceti indexul"<<endl;
                int index;
                cin>>index;
                for(int i=0;i<nr_det;i++)
                    if(banca.cont_economii[i].get_index()==index)
                        banca.cont_economii[i].afisare();
                break;
            }
            case 7:{
                cout<<endl<<"Introduceti indexul"<<endl;
                int index;
                cin>>index;
                for(int i=0;i<nr_det;i++)
                    if(banca.cont_normal[i].get_index()==index)
                        banca.cont_normal[i].afisare();
                break;
            }
            case 8:{
                cout<<endl<<"Introduceti indexul"<<endl;
                int index;
                cin>>index;
                for(int i=0;i<nr_det;i++)
                    if(d[i].get_index()==index)
                        d[i].afisare();
                break;
            }
            case 9:{
                cout<<endl<<"Sunt "<<nr_det<<" detinatori"<<endl;
                break;
            }
            case 10:{
                cout<<endl<<"Sunt "<<banca.get_index()<<" conturi inregistrate la banca"<<endl;
                break;
            }
            case 11:{
                break;
            }
            default:{
                break;
            }
        }
    }
    return 0;
}
