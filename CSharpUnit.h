#ifndef CSHARPUNIT_H
#define CSHARPUNIT_H

#include <string>
#include <vector>
#include "Unit.h"

class ClassCSharp : public Unit
{
public:
    ClassCSharp();
    enum AccessModifier {
        PUBLIC = 1,
        FILE,
        INTERNAL,
        PRIVATE,
        PROTECTED,
        PRIVATE_PROTECTED,
        PROTECTED_INTERNAL
    };
    static const std::vector< std::string > ACCESS_MODIFIERS;

public:
    explicit ClassCSharp( const std::string& name, Flags flags = 0 ) : m_name( name ), m_flags( flags ) { }

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

class MethodCSharp : public Unit
{
public:
    enum AccessModifier {
        PUBLIC,
        FILE,
        INTERNAL,
        PRIVATE,
        PROTECTED,
        PRIVATE_PROTECTED,
        PROTECTED_INTERNAL
    };

public:
    MethodCSharp( const std::string& name, const std::string& returnType, Flags flags ) :
        m_name( name ), m_returnType( returnType ), m_flags( flags ) { }
    void add( const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0 )
    {
        m_body.push_back( unit );
    }
    std::string compile( unsigned int level = 0 ) const
    {
        std::string result = generateShift( level );

        switch (m_flags) {
        case PUBLIC:
            result += "public ";
            break;
        case PROTECTED:
            result += "protected ";
            break;
        case FILE:
            result += "file ";
            break;
        case INTERNAL:
            result += "internal ";
            break;
        case PRIVATE:
            result += "private ";
            break;
        case PRIVATE_PROTECTED:
            result += "private protected ";
            break;
        case PROTECTED_INTERNAL:
            result += "protected internal ";
            break;
        }

        result += m_returnType + " " + m_name + "(){\n";

        for( const auto& b : m_body ) {
            result += b->compile( level + 1 );
        }
        result += generateShift( level ) + "}\n";

        return result;
    }

private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;
    std::vector< std::shared_ptr< Unit > > m_body;
};

class PrintOperatorUnitCSharp : public Unit {
public:
    explicit PrintOperatorUnitCSharp( const std::string& text ) : m_text( text ) { }
    std::string compile( unsigned int level = 0 ) const {
        return generateShift( level ) + "printf( \"" + m_text + "\" );\n";
    }

private:
    std::string m_text;
};


#endif // CSHARPUNIT_H
