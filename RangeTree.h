#include "quicksort-doble.cpp"
#include <vector>

using namespace std;

class range_tree;

struct Node {
  int x, pos;
  int lvl;
  bool leaf;
     Node * m_pSon[2];
     Node* prev;
     Node* next;
     Node* parent;
     Node * ytree;
     std::pair<int,int> coord;
     Node(int n)
     {
        x = n;
        leaf=false;
        m_pSon[0]=nullptr;
        m_pSon[1]=nullptr;
        prev=nullptr;
        next=nullptr;
     }
};


class range_tree
{
  private:
    int size;
    Node* tail;
    bool is_y;
    int *vy;
    int *vx;
  public:
    Node* root;
    range_tree(int vyy[],int vxx[],bool t)
    {
      is_y=t;
      tail=nullptr;
      vy = vyy;
      vx = vxx;
    }
    Node * create_range_tree(int v[],int l, int h,int lvl)
    {
      if(l==h)
      {
        Node * padre = new Node(v[l]);
        padre->m_pSon[0] = new Node(v[l]);
        padre->m_pSon[0]->coord={vx[l],vy[l]};
        padre->m_pSon[0]->pos=l;
        padre->pos=l;
        padre->m_pSon[0]->parent=padre;
        padre->m_pSon[0]->lvl=lvl;
        padre->m_pSon[0]->leaf=true;
        if (!tail)
          tail = padre->m_pSon[0];
        else {
          tail->next = padre->m_pSon[0];
          padre->m_pSon[0]->prev = tail;
          tail = tail->next;
        }
        if(!is_y)
        {
          quickSort(vy,l,h,vx);
          range_tree p(vy,vx,true);
          padre->ytree=p.create_range_tree(vy,l,h,0);
        }
        padre->lvl=lvl-1;
        return padre;
      } 
      if( l+1==h)
      {
        Node * padre = new Node((v[l] + v[h])/2);     
        padre->m_pSon[0] = new Node(v[l]);
        padre->m_pSon[0]->pos=l;
        padre->m_pSon[1] = new Node(v[h]);
        padre->m_pSon[1]->pos=h;
        padre->m_pSon[0]->parent=padre;
        padre->m_pSon[1]->parent=padre;
        padre->m_pSon[0]->leaf=true;
        padre->m_pSon[1]->leaf=true;
        padre->m_pSon[0]->lvl=lvl;
        padre->m_pSon[1]->lvl=lvl;
        padre->m_pSon[0]->coord={vx[l],vy[l]};
        padre->m_pSon[1]->coord={vx[h],vy[h]};
        if (!tail) {
          tail = padre->m_pSon[0];
      }
      else {
        tail->next = padre->m_pSon[0];
        padre->m_pSon[0]->prev = tail;
        tail = tail->next;
        }
        tail->next = padre->m_pSon[1];
        padre->m_pSon[1]->prev = tail;
        tail = tail->next;
        if(!is_y)
        {
          quickSort(vy,l,h,vx);
          range_tree p(vy,vx,true);
          padre->ytree=p.create_range_tree(vy,l,h,0);
        }  
        padre->lvl=lvl-1;
        return padre;
    }
    int m = (l + h)/2;
    Node * pl = create_range_tree(v,l, m,lvl+1);
    Node * pr = create_range_tree(v,m+1, h,lvl+1);
    Node * padre = new Node((pl->x + pr->x)/2);
    padre->lvl=lvl;
    pl->parent=padre;
    pr->parent=padre;
    padre->m_pSon[0] = pl; 
    padre->m_pSon[1] = pr;
    if(!is_y)
    {
      quickSort(vy,l,h,vx);
      range_tree p(vy,vx,true);
      padre->ytree=p.create_range_tree(vy,l,h,0);
    }
    return padre;
  }

  void print(Node * r)
  {
    if(!r) return;
    print(r->m_pSon[0]);
    if(!r->m_pSon[0] && !r->m_pSon[1])
          cout<<r->x<<" ";
    print(r->m_pSon[1]);
  }

  void printf(Node *ptr, int level) 
  {
    if (ptr) {
      printf(ptr->m_pSon[0],level+1);
      for (int k = 0; k < level; k++) {
        std::cout << "    ";
      }
      cout<<ptr->coord.first<<" "<<ptr->coord.second<<endl;
      printf(ptr->m_pSon[1],level+1);
    }
  }

  void ver_list(Node* r)
  {
    auto aux=r;
    while(aux->m_pSon[0]!=nullptr)
    {
      aux=aux->m_pSon[0];
    }
    while(aux!=nullptr)
    {
      cout<<aux->x<<" ";
      aux=aux->next;
    }
  }

  vector<std::pair<int,int>> find(int x_from,int x_to,int y_from, int y_to)
  {
    auto from_x=find(this->root,x_from);
    auto to_x=find(this->root,x_to);
    auto parent=find_parent(from_x,to_x);
    auto y=find(parent->ytree,y_from);
    vector<std::pair<int,int>>r;
    while (true)
    {
      if(y==nullptr) break;
      if( y->coord.second>y_to) break;
      if( x_from <=y->coord.first &&  y_from <=y->coord.second && y->coord.first<=x_to)
      {
        r.push_back({y->coord.first,y->coord.second});
      }
      y=y->next;
    }
    return r;
  }
  
  Node * find_parent(Node* a,Node* b)
  { 
    if(a==b) return a->parent; 
    while(a->lvl>b->lvl){
      a=a->parent;
    }
    while(a->lvl<b->lvl){
      b=b->parent;
    }  
    while(a!=b){
      a=a->parent;
      b=b->parent;
    }
    return a;
  }

  Node* find(Node* r,int value)
  {
    auto aux=r;
    while(!aux->leaf)
    {
      if(aux->x<value)
      {
        if(!aux->m_pSon[1])
        {
          aux=aux->m_pSon[0];
          break;
        }
        aux=aux->m_pSon[1];
      }
      else
        aux=aux->m_pSon[0];
    }
    while(aux->prev!=nullptr)
    {
      if(aux->prev->x>value)
        aux=aux->prev;
      else break;
    }
      while(true)
      {
        if(aux->prev==nullptr) break;
        if(aux->prev->x==value)
          aux=aux->prev;
        else break;
      }
    return aux;
  }

};
