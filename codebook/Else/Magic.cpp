#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#include <ext/rope>
using namespace __gnu_cxx;
int main () {
     __gnu_pbds::priority_queue <int> pq1, pq2;
    pq1.join(pq2); // pq1 += pq2, pq2 = {}
    cc_hash_table<int, int> m1;
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> oset;
    oset.insert(2), oset.insert(4);
    cout << *oset.find_by_order(1) << ' ' << oset.order_of_key(1) << '\n'; // 4 0
    bitset <100> BS;
    BS.flip(3), BS.flip(5);
    cout << BS._Find_first() << ' ' << BS._Find_next(3) << '\n'; // 3 5
    rope <int> rp1, rp2; 
    rp1.push_back(1), rp1.push_back(3);
    rp1.insert(0, 2); // pos, num
    rp1.erase(0, 2); // pos, len
    rp1.substr(0, 2); // pos, len
    rp2.push_back(4);
    rp1 += rp2;
    rp2 = rp1;
    cout << rp2[0] << ' ' << rp2[1] << '\n'; // 3 4
}