#ifndef METHODUNIT_H
#define METHODUNIT_H

#include "Unit.h"
#include <vector>

class MethodUnit : public Unit {
public:

    void add( const std::shared_ptr< Unit >& unit)
    {
        m_body.push_back( unit );
    }

protected:
    std::string m_returnType;
    std::vector< std::shared_ptr< Unit > > m_body;
};


#endif // METHODUNIT_H
