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
    
    static Ordering::type compare(OrderObject& lhs, OrderObject& rhs)
    {
        return lhs.compare(rhs);
    }

    Ordering::type compare(OrderObject& oo)
    {
        // ASSUMES vck
        bool foundLarger = false;
        bool foundSmaller = false;
        for(unsigned int i = 0; i < oo._vt.size(); i++)
        {
            if(_vt[i] < oo._vt[i])
            {
                foundSmaller = true;
            }
            else if(_vt[i] > oo._vt[i])
            {
                foundLarger = true;
            }
        }

        if(foundSmaller && !foundLarger)
        {
            return Ordering::LT;
        }
        else if(!foundSmaller && foundLarger)
        {
            return Ordering::GT;
        }
        else if(foundSmaller && foundLarger)
        {
            // unk
            if(_hostid < oo._hostid)
            {
                return Ordering::LT;
            }
            else
            {
                return Ordering::GT;
            }
        }
        else // (!foundLarger && !foundSmaller)
        {
            return Ordering::EQ;
        }
    }
};



};
