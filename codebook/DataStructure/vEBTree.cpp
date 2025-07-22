using u64 = uint64_t;
constexpr int lsb(u64 x)
{ return x ? __builtin_ctzll(x) : 1 << 30; }
constexpr int msb(u64 x)
{ return x ? 63-__builtin_clzll(x) : -1; }
template<int N, class T=void>
struct veb{
  static const int M=N>>1;
  veb<M> ch[1<<N-M];
  veb<N-M> aux;
  int mn,mx;
  veb():mn(1<<30),mx(-1){}
  constexpr int mask(int x){return x&((1<<M)-1);}
  bool empty(){return mx==-1;}
  int min(){return mn;}
  int max(){return mx;}
  bool have(int x){
    return x==mn?true:ch[x>>M].have(mask(x));
  }
  void insert_in(int x){
    if(empty()) return mn=mx=x,void();
    if(x<mn) swap(x,mn);
    if(x>mx) mx=x;
    if(ch[x>>M].empty()) aux.insert_in(x>>M);
    ch[x>>M].insert_in(mask(x));
  }
  void erase_in(int x){
    if(mn==mx) return mn=1<<30,mx=-1,void();
    if(x==mn) mn=x=(aux.min()<<M)^ch[aux.min()].min();
    ch[x>>M].erase_in(mask(x));
    if(ch[x>>M].empty()) aux.erase_in(x>>M);
    if(x==mx){
      if(aux.empty()) mx=mn;
      else mx=(aux.max()<<M)^ch[aux.max()].max();
    }
  }
  void insert(int x){
    if(!have(x)) insert_in(x);
  }
  void erase(int x){
    if(have(x)) erase_in(x);
  }
  int next(int x){// >=x
    if(x>mx) return 1<<30;
    if(x<=mn) return mn;
    if(mask(x)<=ch[x>>M].max())
      return ((x>>M)<<M)^ch[x>>M].next(mask(x));
    int y=aux.next((x>>M)+1);
    return (y<<M)^ch[y].min();
  }
  int prev(int x){// <x
    if(x<=mn) return -1;
    if(x>mx) return mx;
    if(x<=(aux.min()<<M)+ch[aux.min()].min())
      return mn;
    if(mask(x)>ch[x>>M].min())
      return ((x>>M)<<M)^ch[x>>M].prev(mask(x));
    int y=aux.prev(x>>M);
    return (y<<M)^ch[y].max();
  }
};
template<int N>
struct veb<N,typename enable_if<N<=6>::type>{
  u64 a;
  veb():a(0){}
  void insert_in(int x){a|=1ull<<x;}
  void insert(int x){a|=1ull<<x;}
  void erase_in(int x){a&=~(1ull<<x);}
  void erase(int x){a&=~(1ull<<x);}
  bool have(int x){return a>>x&1;}
  bool empty(){return a==0;}
  int min(){return lsb(a);}
  int max(){return msb(a);}
  int next(int x){return lsb(a&~((1ull<<x)-1));}
  int prev(int x){return msb(a&((1ull<<x)-1));}
};