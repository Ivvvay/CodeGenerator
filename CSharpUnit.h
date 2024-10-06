#ifndef CSHARPUNIT_H
#define CSHARPUNIT_H

#include <string>
#include <vector>
#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"

class ClassCSharp : public ClassUnit
{
public:
    ClassCSharp();

public:
    explicit ClassCSharp( const std::string& name, Flags modifier = 0 )
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

        result += "class " + m_name  + " {\n";

        for( const auto& b : m_fields ) {
            result += b->compile( level + 1 );
        }

        result += generateShift( level ) + "};\n";
        return result;
    }
};

class MethodCSharp : public MethodUnit
{
public:
    MethodCSharp( const std::string& name, const std::string& returnType, Flags modifier )
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
            if(m_modifier & PROTECTED)
                result += "protected ";
            else
                if(m_modifier & FILE)
                    result += "public ";
                else
                    if(m_modifier & INTERNAL)
                        result += "internal ";
                    else
                        if(m_modifier & PRIVATE)
                            result += "private ";
                        else
                            if(m_modifier & PRIVATE_PROTECTED)
                                result += "private protected ";
                            else
                                if(m_modifier & PROTECTED_INTERNAL)
                                    result += "protected internal ";


        result += m_returnType + " " + m_name + "(){\n";

        for( const auto& b : m_body ) {
            result += b->compile( level + 1 );
        }
        result += generateShift( level ) + "}\n";

        return result;
    }
};

class PrintOperatorCSharp : public PrintOperatorUnit {
public:
    explicit PrintOperatorCSharp( const std::string& text )
    {
        m_text = text;
    }
    std::string compile( unsigned int level = 0 ) const {
        return generateShift( level ) + "printf( \"" + m_text + "\" );\n";
    }
};


#endif // CSHARPUNIT_H
