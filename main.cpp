#include <iostream>
#include<ctime>
#include<cstdlib>
#include <fstream>
using namespace std;
int n=5000;
double g=0.4;
//struktury dla listy nastepnikow
struct lista
{
    int nazwa;
    lista* next;
};
struct wierzcholek
{
    int nazwa;
    lista *sasiad;
    bool visited;
    int start, stop;
};

//struktura dla listy lukow
struct lista_l
{
    int w1;
    int w2;
    lista_l* next;
};


//generuje macierz
void generuj_macierz(int **M, double gestosc,int krawedzie)
{
    gestosc=gestosc*n*(n-1)/2;
    int a,b;
    while(krawedzie>=gestosc)
    {
        a=rand()%n;
        b=rand()%n;
        M[a][b]=0;
        krawedzie--;
    }
}

//generuje liste nastepnikow na podstawie macierzy
void generuj_nast(wierzcholek T[], int **M)
{
    for(int i=0; i<n; i++)
    {
        T[i].nazwa=i+1;
        for(int m=0; m<n; m++)
        {
            if(M[i][m]==1)
            {
                lista *nowy= new lista;
                nowy->nazwa=m+1;
                if(T[i].sasiad==NULL) nowy->next=NULL;
                else nowy->next=T[i].sasiad;
                T[i].sasiad=nowy;
            }
        }
    }
}


//generuje liste lukow na podstawie mqcierzy
lista_l* generuj_luki(lista_l *pierwszy, int **M)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        if(M[i][j]==1)
        {
            lista_l *nowy= new lista_l;
            nowy->w1=i+1;
            nowy->w2=j+1;
            if(pierwszy==NULL) nowy->next=NULL;
            else nowy->next=pierwszy;
            pierwszy=nowy;
        }
    }
    return pierwszy;
}
//wyswietla liste nastepnikow
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


//przechodzi przez liste nastepnikow dfs i oznacza etykiety
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
                dfs(T,odwiedzone,T[stos->nazwa-1].sasiad,krok,E);
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


//zlicza luki powrotne korzystajac z listy nastepnikow
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


//zlicza luki powrotne korzystajac z macierzy sasiedztwa
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


//zlicza luki powrotne korzystajac z listy lukow
int zlicz_luki_l(lista_l *pierwszy, int E[][2])
{
   int luki=0;
   /*for(int i=0; i<ilosc_l;i++)
   {
       if(E[L[i].w2][0]<E[L[i].w1][0]&&E[L[i].w1][0]<E[L[i].w1][1]&&E[L[i].w1][1]<E[L[i].w2][1])
        luki++;
   }*/
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

//usuwa liste nastepnikow
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

 //usuwa liste lukow
 void usun_luki(lista_l *pierwszy)
 {
     lista_l *current;
     while(pierwszy!=NULL)
     {
         current=pierwszy;
         pierwszy=pierwszy->next;
         delete current;
     }
 }

int main()
{
    srand(time(NULL));
    lista *stos=NULL;
    lista_l *pierwszy=NULL;
    int krawedzie=0;
    ofstream wynik;
    wynik.open("wyniki.txt", std::ofstream::app);
    int odwiedzone=0, krok=0;
    int E[n][2];
    wierzcholek *T = new wierzcholek[n];
    int **M=new int *[n];
    for(int i=0; i<n; i++)
    {
        M[i]= new int [n];
        for(int j=0; j<n; j++)
            if(i!=j)
            {
                M[i][j]=1;
                krawedzie++;
            }
            else
            M[i][j]=0;
    }
    for(int i=0; i<n; i++)
    {
        T[i].sasiad=NULL;
        T[i].visited=0;
    }
    generuj_macierz(M,g,krawedzie);
    generuj_nast(T,M);
    pierwszy=generuj_luki(pierwszy,M);


    clock_t start = clock();
    dfs(T,odwiedzone,stos,krok,E);
    cout<<"ilosc danych "<<n<<" gestosc "<<g<<endl<<"Czas tworzenia etykiet  "<<double(clock()-start)/CLOCKS_PER_SEC;

    cout<<endl<<"Czas zliczania lukow powrotnych dla roznych reprezentacji: "<<endl;
    double a1,a2,a3;
    start=clock();
    zlicz_luki_macierz(M,E);
    a1=double(clock()-start)/CLOCKS_PER_SEC;
    start=clock();
    zlicz_luki_nast(T,E);
    a2=double(clock()-start)/CLOCKS_PER_SEC;
    start=clock();
    zlicz_luki_l(pierwszy,E);
    a3=double(clock()-start)/CLOCKS_PER_SEC;
    cout<<"Macierz sasiedztwa "<<a1<<" Lista nastêpnikow "<<a2<<" Lista lukow "<<a3<<endl;
    usun_nast(T);
    delete []T;
    for(int i=0; i<n; i++)
        delete []M[i];
    delete []M;
    M=NULL;
    wynik.close();
    usun_luki(pierwszy);
    return 0;
}
