#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
//or a single line
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
//older namespace pb_ds;
typedef tree<
int,
null_type, //older versions null_mapped_type
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

//methods
tree.find_by_order(k) //returns pointer to the k-th smallest element
tree.order_of_key(x)  //returns how many elements are smaller than x
//if element does not exist
tree.end() == tree.find_by_order(k) //true

