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
    lista *sasiad;
};

void generuj_nast(wierzcholek T[])
{
    int a,b;
    for(int i=0; i<n; i++)
    {
        T[i].nazwa=i+1;
        a=rand()%n;
        for(int m=0; m<a; m++)
        {
            b=rand()%n+1;
            if(b!=i)
            {
                if(m==0)
                {
                   lista *nowy= new lista;
                    nowy->nazwa=b;
                    nowy->next=NULL;
                    T[i].sasiad=nowy;
                }
                else
                {
                    lista *nowy= new lista;
                    nowy->nazwa=b;
                    nowy->next=T[i].sasiad;
                    T[i].sasiad=nowy;
                }
            }
            else b--;
        }
    }
}

void wyswietl_nast(wierzcholek T[])
{
    for(int i=0; i<n; i++)
    {
        lista *obecny=T[i].sasiad;
        cout<<"wierzcholek "<<T[i].nazwa<<" i lista jego sasiadow: ";
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
        for(int m=0; m<a; m++)
        {
            if(m==0)
            {
               lista *nowy= new lista;
                nowy->nazwa=i;
                nowy->next=NULL;
                //T[i].sasiad.next=nowy;
                T[i].sasiad=nowy;
            }
            else
            {
                lista *nowy= new lista;
                nowy->nazwa=i;
                nowy->next=T[i].sasiad;
                //T[i].sasiad.next=nowy;
                T[i].sasiad=nowy;
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
    wierzcholek *T = new wierzcholek[n];
    generuj_nast(T);
    wyswietl_nast(T);
    usun_nast(T);
    return 0;
}
