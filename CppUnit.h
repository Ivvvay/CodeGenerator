#ifndef CPPUNIT_H
#define CPPUNIT_H

#include <string>
#include <vector>
#include <QDebug>
#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"

class ClassCpp: public ClassUnit
{

public:
    std::vector< bool > ACCESS_MODIFIERS = {0, 0, 0};

    explicit ClassCpp( const std::string& name, Flags modifier = PRIVATE )
    {
        m_name = name;

        if(!(modifier & PUBLIC || modifier & PROTECTED || modifier & PRIVATE ))
            modifier |= PRIVATE;

        m_modifier =  modifier;
    }

    void add( const std::shared_ptr< Unit >& unit ) {

        qDebug() << unit->getModifier();

        if(unit->getModifier() & PUBLIC)
            ACCESS_MODIFIERS[0] = true;
        if(unit->getModifier() & PROTECTED)
            ACCESS_MODIFIERS[1] = true;
        if(unit->getModifier() & PRIVATE)
            ACCESS_MODIFIERS[2] = true;

        m_fields.push_back( unit );
    }

    std::string compile( unsigned int level = 0 ) const
    {
        std::string result = generateShift( level ) + "class " + m_name + " {\n";


        if(ACCESS_MODIFIERS[0])
        {
            result += generateShift( level ) + "public:\n";
            for( const auto& b : m_fields ) {
                if(b->getModifier() & PUBLIC)
                    result += b->compile( level + 1 );
            }
        }


        if(ACCESS_MODIFIERS[1])
        {
            result += generateShift( level ) + "protected:\n";
            for( const auto& b : m_fields ) {
                if(b->getModifier() & PROTECTED)
                    result += b->compile( level + 1 );
            }
        }


        if(ACCESS_MODIFIERS[2])
        {
            result += generateShift( level ) + "private:\n";
            for( const auto& b : m_fields ) {
                if(b->getModifier() & PRIVATE)
                    result += b->compile( level + 1 );
            }
        }

        result += generateShift( level ) + "};\n";

        return result;
    }


};

class MethodCpp: public MethodUnit
{
public:
    MethodCpp( const std::string& name, const std::string& returnType, Flags modifier = PRIVATE )
    {
        m_name = name;
        m_returnType = returnType;

        if(!(modifier & PUBLIC || modifier & PROTECTED || modifier & PRIVATE ))
            modifier |= PRIVATE;

        m_modifier = modifier;
    }

    std::string compile( unsigned int level = 0 ) const {
        std::string result = generateShift( level );
        if( m_modifier & STATIC ) {
            result += "static ";
        } else if( m_modifier & VIRTUAL ) {
            result += "virtual ";
        }
        result += m_returnType + " ";
        result += m_name + "()";
        if( m_modifier & CONST ) {
            result += " const";
        }
        result += " {\n";
        for( const auto& b : m_body ) {
            result += b->compile( level + 1 );
        }
        result += generateShift( level ) + "}\n";

        return result;
    }


};

class PrintOperatorCpp: public PrintOperatorUnit
{
public:
    explicit PrintOperatorCpp( const std::string& text )
    {
        m_text = text;
    }
    std::string compile( unsigned int level = 0 ) const {
        return generateShift( level ) + "printf( \"" + m_text + "\" );\n";
    }
};

#endif // CPPUNIT_H
