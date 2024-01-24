#include "modify.h"

class modifyData : public QSharedData
{
public:

};

modify::modify() : data(new modifyData)
{

}

modify::modify(const modify &rhs) : data(rhs.data)
{

}

modify &modify::operator=(const modify &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

modify::~modify()
{

}
