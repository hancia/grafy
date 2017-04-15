#include <iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int n=10;

struct lista
{
    int nazwa;
    lista* next;
};
struct wierzcholek
{
    int nazwa;
    int dl;
    lista *sasiad;
};

void generuj_nast(wierzcholek T[])
{
    int a,b;
    lista *current, *prev;
    for(int i=0; i<n; i++)
    {
        T[i].nazwa=i+1;
        for(int m=n; m>=1; m--)
        {
            if(m!=i+1)
            {
                lista *nowy= new lista;
                nowy->nazwa=m;
                if(T[i].dl==0) nowy->next=NULL;
                else nowy->next=T[i].sasiad;
                T[i].sasiad=nowy;
                T[i].dl++;
            }
        }
        a=rand()%T[i].dl;
        for(int m=0; m<a; m++)
        {
            current=T[i].sasiad;
            b=rand()%T[i].dl;
            for(int j=0; j<b; j++)
            {
                prev=current;
                current=current->next;
            }
            if(current==T[i].sasiad)
            T[i].sasiad=current->next;
            else
            prev->next=current->next;
            T[i].dl--;
            delete current;
        }
    }
}

void wyswietl_nast(wierzcholek T[])
{
    for(int i=0; i<n; i++)
    {
        lista *obecny=T[i].sasiad;
        cout<<endl<<"wierzcholek "<<T[i].nazwa<<" i lista jego sasiadow: ";
        while(obecny!=NULL)
        {
            cout<<obecny->nazwa<<" ";
            delete obecny;
            obecny=obecny->next;
        }
    }
}

void wpisz_nast(wierzcholek T[])
 {
    int a;
    cout<<"wpisz recznie bo nie dziala: "<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"wierzcholek "<<i<<endl;
        T[i].nazwa=i;
        cout<<" ilosc sasiadow: ";
        cin>>a;
        for(int m=1; m<a; m++)
        {
            if(m!=i+1)
            {
                lista *nowy= new lista;
                nowy->nazwa=m;
                if(T[i].sasiad==NULL) nowy->next=NULL;
                else nowy->next=T[i].sasiad;
                T[i].sasiad=nowy;
                T[i].dl++;
            }
        }
    }
 }

 void usun_nast(wierzcholek T[])
 {
     lista *current,*current2;
     for(int i=0; i<n; i++)
     {
         current=T[i].sasiad;
         while(current!=NULL)
         {
             current2=current->next;
             delete current;
             current=current2;
         }
     }
 }
int main()
{
    srand(time(NULL));
    wierzcholek *T = new wierzcholek[n];
    for(int i=0; i<n; i++)
    {
        T[i].sasiad=NULL;
        T[i].dl=0;
    }
    generuj_nast(T);
    wyswietl_nast(T);
    usun_nast(T);
    return 0;
}
