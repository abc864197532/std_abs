#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define all(a) a.begin(), a.end()
#define sz(a) ((int)a.size())
#ifdef ABS
void db() {}
template <typename T>
ostream& operator << (ostream &o, vector <T> vec) {
    o << "{"; int f = 0;
    for (T i : vec) o << (f++ ? " " : "") << i;
    return o << "}"; }
template <typename T, typename ...U> void db(T i, U ...j) { cerr << i << " ", db(j...); }
#define ppr(c, x...) cerr << "\e[1;" << c << "m", db(__LINE__, "[" + string(#x) + "]", x), cerr << "\e[0m" << endl
#define bug(x...) ppr(32, x)
#define bugv(x...) ppr(36, vector(x))
#define safe ppr(33, "safe")
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#define safe void(0)
#endif
const int mod = 998244353, N = 100000;

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    
}