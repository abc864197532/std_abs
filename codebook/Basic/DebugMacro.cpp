void db() { cout << endl; }
template <typename T, typename ...U>
void db(T i, U ...j) { cout << i << ' ', db(j...); }
#ifdef ABS
#define bug(x...) db("[" + string(#x) + "]", x)
#else
#define bug(x...) void(0)
#endif