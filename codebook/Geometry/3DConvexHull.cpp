struct CH3D {
  struct face{int a, b, c; bool ok;} F[8 * N];
  double dblcmp(Pt &p,face &f)
  {return cross3(P[f.a], P[f.b], P[f.c]) * (p - P[f.a]);}
  int g[N][N], num, n;
  Pt P[N];
  void deal(int p,int a,int b) {
    int f = g[a][b];
    face add;
    if (F[f].ok) {
      if (dblcmp(P[p],F[f]) > eps) dfs(p,f);
      else
        add.a = b, add.b = a, add.c = p, add.ok = 1, g[p][b] = g[a][p] = g[b][a] = num, F[num++]=add;
    }
  } 
  void dfs(int p, int now) {
    F[now].ok = 0;
    deal(p, F[now].b, F[now].a), deal(p, F[now].c, F[now].b), deal(p, F[now].a, F[now].c);
  }
  bool same(int s,int t){
    Pt &a = P[F[s].a];
    Pt &b = P[F[s].b];
    Pt &c = P[F[s].c];
    return fabs(volume(a, b, c, P[F[t].a])) < eps && fabs(volume(a, b, c, P[F[t].b])) < eps && fabs(volume(a, b, c, P[F[t].c])) < eps;
  }
  void init(int _n){n = _n, num = 0;}
  void solve() {
    face add;
    num = 0;
    if(n < 4) return;
    if([&](){
        for (int i = 1; i < n; ++i)
        if (abs(P[0] - P[i]) > eps) 
        return swap(P[1], P[i]), 0;
        return 1;
        }() || [&](){
        for (int i = 2; i < n; ++i)
        if (abs(cross3(P[i], P[0], P[1])) > eps) 
        return swap(P[2], P[i]), 0;
        return 1;
        }() || [&](){
        for (int i = 3; i < n; ++i)
        if (fabs(((P[0] - P[1]) ^ (P[1] - P[2])) * (P[0] - P[i])) > eps)
        return swap(P[3], P[i]), 0;
        return 1;
        }())return;
    for (int i = 0; i < 4; ++i) {
      add.a = (i + 1) % 4, add.b = (i + 2) % 4, add.c = (i + 3) % 4, add.ok = true;
      if (dblcmp(P[i],add) > 0) swap(add.b, add.c);
      g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
      F[num++] = add;
    }
    for (int i = 4; i < n; ++i)
      for (int j = 0; j < num; ++j)
        if (F[j].ok && dblcmp(P[i],F[j]) > eps) {
          dfs(i, j);
          break;
        }
    for (int tmp = num, i = (num = 0); i < tmp; ++i)
      if (F[i].ok) F[num++] = F[i];
  }
  double get_area() {
    double res = 0.0;
    if (n == 3)
      return abs(cross3(P[0], P[1], P[2])) / 2.0;
    for (int i = 0; i < num; ++i)
      res += area(P[F[i].a], P[F[i].b], P[F[i].c]);
    return res / 2.0;
  }
  double get_volume() {
    double res = 0.0;
    for (int i = 0; i < num; ++i)
      res += volume(Pt(0, 0, 0), P[F[i].a], P[F[i].b], P[F[i].c]);
    return fabs(res / 6.0);
  } 
  int triangle() {return num;}
  int polygon() {
    int res = 0;
    for (int i = 0, flag = 1; i < num; ++i, res += flag, flag = 1)
      for (int j = 0; j < i && flag; ++j)
        flag &= !same(i,j);
    return res;
  }
  Pt getcent(){
    Pt ans(0, 0, 0), temp = P[F[0].a]; 
    double v = 0.0, t2; 
    for (int i = 0; i < num; ++i)
      if (F[i].ok == true) {
        Pt p1 = P[F[i].a], p2 = P[F[i].b], p3 = P[F[i].c]; 
        t2 = volume(temp, p1, p2, p3) / 6.0;
        if (t2>0)
          ans.x += (p1.x + p2.x + p3.x + temp.x) * t2, ans.y += (p1.y + p2.y + p3.y + temp.y) * t2, ans.z += (p1.z + p2.z + p3.z + temp.z) * t2, v += t2; 
      } 
    ans.x /= (4 * v), ans.y /= (4 * v), ans.z /= (4 * v); 
    return ans; 
  } 
  double pointmindis(Pt p) {            
    double rt = 99999999; 
    for(int i = 0; i < num; ++i)
      if(F[i].ok == true) { 
        Pt p1 = P[F[i].a], p2 = P[F[i].b], p3 = P[F[i].c];                    
        double a = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y); 
        double b = (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z); 
        double c = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x); 
        double d = 0 - (a * p1.x + b * p1.y + c * p1.z); 
        double temp = fabs(a * p.x + b * p.y + c * p.z + d) / sqrt(a * a + b * b + c * c);                    
        rt = min(rt, temp);
      } 
    return rt; 
  }
};