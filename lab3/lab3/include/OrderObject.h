#ifndef ORDER_OBJECT
#define ORDER_OBJECT

#include <vector>
using namespace std;

namespace Tribbler{

struct Ordering {
  enum type {
    LT,
    GT,
    EQ // ,
    // UNK <- if unknown ordering, order by server id
  };
};

class OrderObject {
public:
    vector<int> _vt;
    int _hostid;

    static Ordering::type compare(OrderObject& lhs, OrderObject& rhs);

    bool operator> (OrderObject const & o2) const;

    Ordering::type compare(const OrderObject& oo) const;

};

}


#endif
