#include <iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int n=1000;
double g=0.4;

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

struct lista_l
{
    int w1;
    int w2;
    lista_l* next;
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


void generuj_macierz(wierzcholek T[], int **M)
{
    lista *current;
    for(int i=0; i<n; i++)
    {
        current=T[i].sasiad;
        while(current!=NULL)
        {
            M[i][current->nazwa-1]=1;
            current=current->next;
        }
    }
}

void generuj_luki(wierzcholek T[], lista_l **pier)
{
    lista_l *pierwszy=*pier;
    lista *current;
    for(int i=0; i<n; i++)
    {
        current=T[i].sasiad;
        while(current!=NULL)
        {
            lista_l *nowy= new lista_l;
            nowy->w1=i+1;
            nowy->w2=current->nazwa;
            if(pierwszy==NULL) nowy->next=NULL;
            else nowy->next=pierwszy;
            pierwszy=nowy;
            current=current->next;
        }
    }
    *pier=pierwszy;
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

void dfs(wierzcholek T[], int &odwiedzone, lista *stos, int &krok, int E[][2])
{
    if(stos==NULL)
    {
        if(odwiedzone==n) return;
        else
        {
            int i=0;
            for(i=0; i<n; i++) if(!T[i].visited) break;
            T[i].visited=1;
            odwiedzone++;
            E[i][0]=++krok;
            dfs(T,odwiedzone,T[i].sasiad,krok,E);
            E[i][1]=++krok;
        }
    }
    else
    {
        while(stos!=NULL)
        {
            if(!T[stos->nazwa-1].visited)
            {
                T[stos->nazwa-1].visited=1;
                odwiedzone++;
                E[stos->nazwa-1][0]=++krok;
                dfs(T,odwiedzone,stos,krok,E);
                E[stos->nazwa-1][1]=++krok;
            }
            else
            {
                stos=stos->next;
            }
        }
        return;
    }
    dfs(T,odwiedzone,0,krok,E);
}

int zlicz_luki_nast(wierzcholek T[], int E[][2])
{
    int luki=0;
    lista *current;
    for(int i=0; i<n; i++)
    {
        current=T[i].sasiad;
        while(current!=NULL)
        {
            if(E[current->nazwa][0]<E[i+1][0]&&E[i+1][0]<E[i+1][1]&&E[i+1][1]<E[current->nazwa][1])
                luki++;
            current=current->next;
        }
    }
    return luki;
}

int zlicz_luki_macierz(int **M, int E[][2])
{
    int luki=0;
    for(int i=0;i<n; i++)
    {
        for(int j=0; j<n; j++)
            if(M[i][j]==1)
            {
                if(E[j+1][0]<E[i+1][0]&&E[i+1][0]<E[i+1][1]&&E[i+1][1]<E[j+1][1])
                   luki++;
            }
    }
    return luki;
}

int zlicz_luki_l(lista_l *pierwszy, int E[][2])
{
   int luki=0;
   lista_l *current;
   current=pierwszy;
   while(current!=NULL)
   {
       if(E[current->w2][0]<E[current->w1][0]&&E[current->w1][0]<E[current->w1][1]&&E[current->w1][1]<E[current->w2][1])
        luki++;
       current=current->next;
   }
   return luki;
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

 void usun_luki(lista_l *pierwszy)
 {
     lista_l *current;
     while(pierwszy!=NULL)
     {
         current=pierwszy->next;
         delete pierwszy;
         pierwszy=current;
     }
 }

int main()
{
    srand(time(NULL));
    lista *stos=NULL;
    lista_l *pierwszy=NULL;
    int odwiedzone=0, krok=0;
    int E[n][2];
    wierzcholek *T = new wierzcholek[n];
    int **M=new int *[n];
    for(int i=0; i<n; i++)
    {
        M[i]= new int [n];
        for(int j=0; j<n; j++)
        M[i][j]=0;
    }
    for(int i=0; i<n; i++)
    {
        T[i].sasiad=NULL;
        T[i].dl=0;
        T[i].visited=0;
    }
    generuj_nast(T,g);
    dfs(T,odwiedzone,stos,krok,E);
    generuj_macierz(T,M);
    generuj_luki(T,&pierwszy);
    cout<<"ilosc lukow dla macierzy "<<zlicz_luki_macierz(M,E);
    cout<<endl<<"ilosc lukow dla listy nast "<<zlicz_luki_nast(T,E);
    cout<<endl<<"ilosc lukow dla listy lukow "<<zlicz_luki_l(pierwszy,E);
    usun_nast(T);
    usun_luki(pierwszy);
    delete []T;
    for(int i=0; i<n; i++)
        delete []M[i];
    delete []M;
    M=NULL;
    return 0;
}
