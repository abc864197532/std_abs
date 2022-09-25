void db() {cout << endl;}
template <typename T, typename ...U> void db(T i, U ...j) {
    cout << i << ' ', db(j...);
}
#define tes(x...) db("[" + string(x) + "]", x)