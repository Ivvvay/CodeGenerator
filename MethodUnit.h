#ifndef METHODUNIT_H
#define METHODUNIT_H

#include "Unit.h"
#include <vector>

class MethodUnit : public Unit {
public:
    enum Modifier {
        STATIC = 1,
        CONST = 1 << 1,
        VIRTUAL = 1 << 2,
        FINAL = 1 << 3,
        ABSTRACT = 1 << 4,
        PUBLIC = 1 << 5,
        PROTECTED = 1 << 6,
        PRIVATE = 1 << 7,
        INTERNAL = 1 << 8
    };

public:
    MethodUnit( const std::string& name, const std::string& returnType, Flags flags )
        : m_name( name ), m_returnType( returnType ), m_flags( flags ) {}

    void add( const std::shared_ptr< Unit >& unit,  Flags /* flags */ = 0)
    {
        m_body.push_back( unit );
    }

protected:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;
    std::vector< std::shared_ptr< Unit > > m_body;
};


#endif // METHODUNIT_H
