#include <vector>
#include <iostream>
#include "OrderObject.h"
using namespace std;
using namespace Tribbler;

Ordering::type OrderObject::compare(OrderObject& lhs, OrderObject& rhs)
{
    return lhs.compare(rhs);
}

bool OrderObject::operator> (OrderObject const & o2) const
{
    if(compare(o2) == Ordering::GT)
        return true;
    else
        return false;
}

Ordering::type OrderObject::compare(const OrderObject& oo) const
{
    cout << "Starting compare" << endl;

    // ASSUMES equal sized vecs 
    if(oo._vt.size() != _vt.size())
    {
        cout << "VECS ARE NOT THE SAME SIZE*********" << endl;
        cout << "\t" << oo._vt.size() << endl;
        cout << "\t" << _vt.size() << endl;
    }

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
    cout << "Got thru compare" << endl;
}
