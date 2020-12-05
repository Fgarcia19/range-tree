#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include "funciones.cpp"
using namespace std;
double t0, t1;
#define N 10000

int main()
{
    time(NULL);
    vector<pair<int,int>> v;
    vector<pair<int,int>> a;

    vector<int> v1;
    vector<int> v2;

    srand(time(NULL));

    for (int i=0;i<N;i++)
    {
      v.push_back({rand()%1000000000,rand()%1000000000});
      a.push_back(v.back());
    }
    sort(v.begin(),v.end(),compare);

    int vx[N];
    int vy[N];
    for (int i=0;i<N;i++)
    {
      vx[i]=v[i].first;
      vy[i]=v[i].second;      
    }
    range_tree rg(vy,vx,false);
    Node * root = rg.create_range_tree(vx,0,N-1,0);
    rg.root=root;
    int fx,tx,fy,ty;
    t0=clock();
    auto r1=rg.find(151792716, 889831815,900558361,996327726);
    t1=clock();
    double t_arbol=(double(t1-t0)/CLOCKS_PER_SEC);
    double t2=clock();
    auto b=find(a,151792716, 889831815,900558361,996327726);
    double t3=clock();
    double t_fuerza=(double(t3-t2)/CLOCKS_PER_SEC);
    cout<<"COMPROBAR"<<endl;
    if(comprobar(r1,b))
      cout<<"Respuestas iguales"<<endl;
    else cout<<"Respuestas distintas"<<endl;
    cout<<"ARBOL: "<<t_arbol * 1000 <<endl;
    cout<<"BRUTA: "<<t_fuerza * 1000 <<endl;
    return 0;
}
