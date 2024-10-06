#ifndef CLASSUNIT_H
#define CLASSUNIT_H

#include "Unit.h"
#include <vector>

class ClassUnit : public Unit {
public:
    virtual void add( const std::shared_ptr< Unit >& unit ) override
    {
        m_fields.push_back( unit );
    }

protected:
    using Fields = std::vector< std::shared_ptr< Unit > >;
    Fields m_fields;
};

#endif // CLASSUNIT_H
