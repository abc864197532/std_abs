const double eps = 1e-8, PI = acos(-1);
int sign(double x)
{ return fabs(x) <= eps ? 0 : (x > 0 ? 1 : -1); }
double normalize(double x) {
  while (x < -eps) x += PI * 2;
  while (x > PI * 2 + eps) x -= PI * 2;
  return x; }
template <typename T> struct P {
  T x, y;
  P (T _x = 0, T _y = 0) : x(_x), y(_y) {}
  P<T> operator + (P<T> o) {
    return P<T>(x + o.x, y + o.y);}
  P<T> operator - (P<T> o) {
    return P<T>(x - o.x, y - o.y);}
  P<T> operator * (T k) {return P<T>(x * k, y * k);}
  P<T> operator / (T k) {return P<T>(x / k, y / k);}
  T operator * (P<T> o) {return x * o.x + y * o.y;}
  T operator ^ (P<T> o) {return x * o.y - y * o.x;}
};
using Pt = P<ll>;
struct Line { Pt a, b; };
struct Cir { Pt o; double r; };
ll abs2(Pt a) { return a * a; }
double abs(Pt a) { return sqrt(abs2(a)); }
int ori(Pt o, Pt a, Pt b)
{ return sign((o - a) ^ (o - b)); }
bool btw(Pt a, Pt b, Pt c) // c on segment ab?
{ return ori(a, b, c) == 0 &&
         sign((c - a) * (c - b)) <= 0; }
int pos(Pt a)
{ return sign(a.y) == 0 ? sign(a.x) < 0 : a.y < 0; }
bool cmp(Pt a, Pt b)
{ return pos(a) == pos(b) ? sign(a ^ b) > 0 :
         pos(a) < pos(b); }
bool same_vec(Pt a, Pt b, int d) // d = 1: check dir
{ return sign(a ^ b) == 0 && sign(a * b) > d * 2 - 2; }
bool same_vec(Line a, Line b, int d)
{ return same_vec(a.b - a.a, b.b - b.a); }
Pt perp(Pt a) { return Pt(-a.y, a.x); } // CCW 90 deg
// double part
double theta(Pt a)
{ return normalize(atan2(a.y, a.x)); }
Pt unit(Pt o) { return o / abs(o); }
Pt rot(Pt a, double o) // CCW
{ double c = cos(o), s = sin(o);
  return Pt(c * a.x - s * a.y, s * a.x + c * a.y); }
Pt proj_vec(Pt a, Pt b, Pt c) // vector ac proj to ab
{return (b - a) * ((c - a) * (b - a)) / (abs2(b - a));}
Pt proj_pt(Pt a, Pt b, Pt c) // point c proj to ab
{ return proj_vec(a, b, c) + a; }