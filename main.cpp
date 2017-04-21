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
    bool visited;
    int start, stop;
};

void generuj_nast(wierzcholek T[], double gestosc)
{
    int a,b,krawedzie=0;
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
                krawedzie++;
            }
        }
    }
    gestosc=gestosc*n*(n-1)/2;
    while(krawedzie>=gestosc)
    {
        a=rand()%n;
        if(T[a].sasiad!=NULL)
        {
            current=T[a].sasiad;
            b=rand()%T[a].dl;
            for(int j=0; j<b; j++)
            {
                prev=current;
                current=current->next;
            }
            if(current==T[a].sasiad)
            T[a].sasiad=current->next;
            else
            prev->next=current->next;
            T[a].dl--;
            delete current;
            krawedzie--;
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
            obecny=obecny->next;
        }
    }
}

void wpisz_nast(wierzcholek T[])
 {
    int a;
    cout<<"wpisz recznie: "<<endl;
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

void dfs(wierzcholek T[], int &odwiedzone, wierzcholek *stos, int &krok)
{
    if(stos==NULL)
    {
        if(odwiedzone==n) return;
        else
        {
            int i=0;
            for(i=0; i<n; i++) if(!T[i].visited) break;
            cout<<" odwiedzam "<<T[i].nazwa;
            T[i].visited=1;
            odwiedzone++;
            T[i].start=++krok;
            dfs(T,odwiedzone,&T[i],krok);
            T[i].stop=++krok;
        }
    }
    else
    {
        while(stos->sasiad!=NULL)
        {
            if(!T[stos->sasiad->nazwa-1].visited)
            {
                T[stos->sasiad->nazwa-1].visited=1;
                cout<<" odwiedzam "<<T[stos->sasiad->nazwa-1].nazwa;
                odwiedzone++;
                T[stos->sasiad->nazwa-1].start=++krok;
                dfs(T,odwiedzone,&T[stos->sasiad->nazwa-1],krok);
                T[stos->sasiad->nazwa-1].stop=++krok;
            }
            else
            {
                stos->sasiad=stos->sasiad->next;
            }
        }
        return;
    }
    dfs(T,odwiedzone,0,krok);
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
    wierzcholek *stos=NULL;
    int odwiedzone=0, krok=0;
    wierzcholek *T = new wierzcholek[n];
    for(int i=0; i<n; i++)
    {
        T[i].sasiad=NULL;
        T[i].dl=0;
        T[i].visited=0;
    }
    generuj_nast(T,0.2);
    wyswietl_nast(T);
    dfs(T,odwiedzone,stos,krok);
    cout<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"etykiety wierzcholka: "<<T[i].nazwa<<" "<<T[i].start<<" "<<T[i].stop<<endl;
    }
    usun_nast(T);
    return 0;
}
