#ifndef JAVAUNIT_H
#define JAVAUNIT_H

#include <string>
#include <vector>
#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"

class ClassJAVA : public ClassUnit
{

public:
    explicit ClassJAVA( const std::string& name, Flags modifier = 0 )
    {
        m_name = name;
        m_modifier =  modifier;
    }

    std::string compile( unsigned int level = 0 ) const
    {
        std::string result = generateShift( level );

        if(m_modifier & PUBLIC)
            result += "public ";
        else
            if(m_modifier & FILE)
                result += "file ";
            else
                if(m_modifier & INTERNAL)
                    result += "internal ";

        if(m_modifier & FINAL)
            result += "final ";
        else
            if(m_modifier & ABSTRACT)
                result += "abstract ";

        result += "class " + m_name  + " {\n";

        for( const auto& b : m_fields ) {
            result += b->compile( level + 1 );
        }

        result += generateShift( level ) + "};\n";
        return result;
    }
};

class MethodJAVA : public MethodUnit
{
public:
    MethodJAVA( const std::string& name, const std::string& returnType, Flags modifier )
    {
        m_name = name;
        m_returnType = returnType;
        m_modifier = modifier;
    }


    std::string compile( unsigned int level = 0 ) const
    {
        std::string result = generateShift( level );

        if(m_modifier & PUBLIC)
            result += "public ";
        else
            if(m_modifier & FILE)
                result += "file ";
            else
                if(m_modifier & INTERNAL)
                    result += "internal ";

        if(m_modifier & STATIC)
            result += "static ";

        if(m_modifier & FINAL)
            result += "final ";
        else
            if(m_modifier & ABSTRACT)
                result += "abstract ";

        result += m_returnType + " " + m_name + "(){\n";

        for( const auto& b : m_body ) {
            result += b->compile( level + 1 );
        }
        result += generateShift( level ) + "}\n";

        return result;
    }
};

class PrintOperatorJAVA : public PrintOperatorUnit
{
public:
    explicit PrintOperatorJAVA( const std::string& text )
    {
        m_text = text;
    }
    std::string compile( unsigned int level = 0 ) const {
        return generateShift( level ) + "println( \"" + m_text + "\" );\n";
    }
};

#endif // JAVAUNIT_H
