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