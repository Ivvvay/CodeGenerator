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
    ClassCpp( const std::string& name) : ClassUnit(name) {}

    std::string compile( unsigned int level = 0 ) const override
    {
        std::string result = generateShift( level ) + "class " + m_name + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (m_fields[i].empty()) {
                continue;
            }

            result += ACCESS_MODIFIERS[i] + ":\n";

            for (const auto& f : m_fields[i]) {
                result += f->compile(level + 1);
                result += "\n";
            }
        }

        result += generateShift(level) + "};\n";
        return result;
    }
};

class MethodCpp: public MethodUnit
{
public:
    enum Modifier {
        STATIC = 1,
        CONST = 1 << 1,
        VIRTUAL = 1 << 2
    };
public:
    MethodCpp(const std::string& name, const std::string& returnType, Flags flags) : MethodUnit(name, returnType, flags) {}

    std::string compile( unsigned int level = 0 ) const override
    {
        std::string result = generateShift( level );

        if( m_flags  & STATIC ) {
            result += "static ";
        } else if( m_flags  & VIRTUAL ) {
            result += "virtual ";
        }

        result += m_returnType + " ";
        result += m_name + "()";

        if( m_flags  & CONST ) {
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
    PrintOperatorCpp(const std::string& text) : PrintOperatorUnit(text) {}

    std::string compile( unsigned int level = 0 ) const override
    {
        return generateShift( level ) + "printf( \"" + m_text + "\" );\n";
    }
};

#endif // CPPUNIT_H
