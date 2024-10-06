#ifndef CLASSCSHARP_H
#define CLASSCSHARP_H

#include <string>
#include <Unit.h>
#include <vector>

class ClassCSharp : public Unit
{
public:
    ClassCSharp();
    enum AccessModifier {
        PUBLIC = 1,
        FILE,
        INTERNAL
    };
    static const std::vector< std::string > ACCESS_MODIFIERS;

public:
    explicit ClassCSharp( const std::string& name, Flags flags = 0 ) : m_name( name ), m_flags( flags )
    {
    }
    void add( const std::shared_ptr< Unit >& unit, Flags flags = 0 )
    {
        m_fields.push_back( unit );
    }
    std::string compile( unsigned int level = 0 ) const
    {
        std::string result = generateShift( level );
        switch (m_flags) {
        case PUBLIC:
            result += "public ";
            break;
        case FILE:
            result += "file ";
            break;
        case INTERNAL:
            result += "internal ";
        }
        result += "class " + m_name  + " {\n";
        for( const auto& b : m_fields ) {
            result += b->compile( level + 1 );
        }
        result += generateShift( level ) + "};\n";
        return result;
    }

private:
    std::string m_name;
    using Fields = std::vector< std::shared_ptr< Unit > >;
    Flags m_flags;
    std::vector< std::shared_ptr< Unit > > m_fields;
};
const std::vector< std::string > ClassCSharp::ACCESS_MODIFIERS = { "public", "file", "internal" };

#endif // CLASSCSHARP_H
