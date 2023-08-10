template <typename T>
struct P {
  T x, y;
  P (T _x, T _y) : x(_x), y(_y) {}
  P operator + (P<T> o) {return P<T>(x + o.x, y + o.y);}
  P operator - (P<T> o) {return P<T>(x - o.x, y - o.y);}
  P operator * (T k) {return P<T>(x * k, y * k);}
  P operator / (T k) {return P<T>(x / k, y / k);}
  T operator * (P<T> o) {return x * o.x + y * o.y;}
  T operator ^ (P<T> o) {return x * o.y - y * o.x;}
};
using Pt = P<double>;