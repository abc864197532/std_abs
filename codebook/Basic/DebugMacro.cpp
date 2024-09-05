void db() { cerr << endl; }
template <typename T, typename ...U>
void db(T i, U ...j) { cerr << i << ' ', db(j...); }
#ifdef ABS
#define bug(x...) db("[" + string(#x) + "]", x)
#define safe cerr << __PRETTY_FUNCTION__ << " line " << __LINE__ << " safe" << endl
#else
#define bug(x...) void(0)
#define safe void(0)
#endif