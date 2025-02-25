#ifndef CLASSUNIT_H
#define CLASSUNIT_H

#include "Unit.h"
#include <vector>

class ClassUnit : public Unit {
public:
    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };

    static const std::vector< std::string > ACCESS_MODIFIERS;

public:
    explicit ClassUnit( const std::string& name ) : m_name( name ) {
        m_fields.resize( ACCESS_MODIFIERS.size() );
    }

    void add( const std::shared_ptr< Unit >& unit, Flags flags)
    {
        int accessModifier = PRIVATE;

        if( flags < ACCESS_MODIFIERS.size() ) {
            accessModifier = flags;
        }

        m_fields[ accessModifier ].push_back( unit );
    }

protected:
    std::string m_name;
    using Fields = std::vector< std::shared_ptr< Unit > >;
    std::vector< Fields > m_fields;
};

const std::vector< std::string > ClassUnit::ACCESS_MODIFIERS = { "public", "protected", "private" };

#endif // CLASSUNIT_H
