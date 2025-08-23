#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set;
// greater<int> - sorted descending(ordered_rset)
//less_equal<int> - sorted ascending(ordered_multiset)
// greater_equal<int> - sorted descending(ordered_rmultiset)
/*
***Don't use long long as defined when using it***
1>declare ==> ordered_set A
2>insert ==> A.insert(val);
3>finding kth element (0 based - index) ==> *A.find_by_order(k);
4>finding the index in which val is located
if not found returns its relative position(position if inserted)
==> A.order_of_key(val);
5>lower Bound ==> *A.lower_bound(val);
6>Upper Bound ==> *A.upper_bound(val);
7>Erase ==> A.erase(val or pointer);
For multiset use custom delete function!
*/
void myErase(ordered_set &t, int v){
    int rank = t.order_of_key(v);
    ordered_set::iterator it = t.find_by_order(rank);
    if(*it == v)t.erase(it);
}