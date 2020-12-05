#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <ctime>
// #include "RangeTree.h"
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
    //   // v1.push_back(rand()%100);
    //   // v2.push_back(rand()%100);
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
      // vx[i]=v1[i];
      // vy[i]=v2[i]; 
      // cout<<vx[i]<<" "<<vy[i]<<endl;
    }
    for (int i = 0; i < N; i++) {
      cout << "y: " << vy[i] << " x: " << vx[i] << endl;
    }
    range_tree rg(vy,vx,false);
    Node * root = rg.create_range_tree(vx,0,N-1,0);
    rg.root=root;
    // print(root);
    // rg.printf(root,0);
    // rg.ver_list();
    int fx,tx,fy,ty;
    // cin>>fx>>tx>>fy>>ty;
    // rg.find1(fx, tx,fy,ty);

    t0=clock();
    auto r1=rg.find(151792716, 889831815,900558361,996327726);
    t1=clock();
    cout<<t0<<endl;
    cout<<t1<<endl;

    double t_arbol=(double(t1-t0)/CLOCKS_PER_SEC);
    cout<<"Fuerza bruta"<<endl;
    double t2=clock();
    auto b=find(a,151792716, 889831815,900558361,996327726);

    // for(auto i:b)
    // {
    //   cout<<i.first<<" - "<<i.second<<endl;
    // }
    double t3=clock();
        cout<<t2<<endl;
    cout<<t3<<endl;

    double t_fuerza=(double(t3-t2)/CLOCKS_PER_SEC);

    cout<<"COMPROBAR"<<endl;
    cout<<r1.size()<<" "<<b.size()<<endl;
    cout<<comprobar(r1,b)<<endl;

    cout<<"ARBOL: "<<t_arbol * 1000 <<endl;
    cout<<"BRUTA: "<<t_fuerza * 1000 <<endl;


  

    return 0;
}

// 2595 4132
// 5235 2406
// 6407 6500
