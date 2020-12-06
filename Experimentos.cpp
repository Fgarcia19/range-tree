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
#define N_CONS 10000

int main()
{
    time(NULL);
    vector<pair<int,int>> v;
    vector<pair<int,int>> a;

    vector<int> v1;
    vector<int> v2;

    srand(time(NULL));
    //N es cantidad de elemento a insertar
    //N_CONS cantidad de consultas a realizar para la parte de experimentacion y calcular los tiempos
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
    //Valores from,to de x,y respectivamente para buscar
    fx = 151792716;
    tx = 889831815;
    fy = 900558361;
    ty = 996327726;
    double t_arbol = 0;
    double t_fuerza = 0;
    double t0, t1, t2, t3;
    vector<pair<int, int>> r1, b;
    for (int i = 0; i < N_CONS; i++) {
      t0=clock();
      //Para facilitar la creacion de N_CONS consultas distintas, si se desea hacer una unica puede ponerse a 1
      r1=rg.find(fx + i, tx + i, fy + i, ty + i);
      t1=clock();
      t_arbol += (double(t1-t0)/CLOCKS_PER_SEC);
      //cout << "tiempo arbol: " << (double(t1-t0)/CLOCKS_PER_SEC) * 1000 << endl;
      t2=clock();
      b=find(a, fx + i, tx + i, fy + i, ty + i);
      t3=clock();
      t_fuerza += (double(t3-t2)/CLOCKS_PER_SEC);
      //cout << "tiempo fuerza bruta: " << (double(t3-t2)/CLOCKS_PER_SEC) * 1000 << endl;
      cout<<"COMPROBAR"<<endl;
      if(comprobar(r1,b))
        cout<<"Respuestas iguales"<<endl;
      else cout<<"Respuestas distintas"<<endl;
    }
    cout<<"ARBOL: "<< t_arbol * 10 <<endl;
    cout<<"BRUTA: "<< t_fuerza  * 10 <<endl;
    return 0;
}
