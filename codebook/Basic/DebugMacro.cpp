void db() { cout << endl; }
template <typename T, typename ...U>
void db(T i, U ...j) { cout << i << ' ', db(j...); }
#define test(x...) db("[" + string(x) + "]", x)