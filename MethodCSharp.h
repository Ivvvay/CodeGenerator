#ifndef METHODCSHARP_H
#define METHODCSHARP_H

#include "Unit.h"
#include <vector>
#include <QDebug>

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
        qDebug() << "compile rabotaet";
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
        result += m_returnType + m_name + "(){\n";
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

#endif // METHODCSHARP_H
