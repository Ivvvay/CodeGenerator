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
    ClassCSharp(const std::string& name) : ClassUnit(name) {}

    std::string compile( unsigned int level = 0 ) const override
    {
        std::string result = generateShift( level );

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (m_fields[i].empty()) {
                continue;
            }

            for (const auto& f : m_fields[i]) {
                result += f->compile(level + 1);
                result += "\n";
            }
        }

        result += generateShift(level) + "}\n";
        return result;
    }
};

class MethodCSharp : public MethodUnit
{
public:
    enum Modifier {
        STATIC = 1,
        CONST = 1 << 1,
        VIRTUAL = 1 << 2,
        PUBLIC = 1 << 5,
        PROTECTED = 1 << 6,
        PRIVATE = 1 << 7,
        INTERNAL = 1 << 8
    };
public:
    MethodCSharp(const std::string& name, const std::string& returnType, Flags flags) : MethodUnit(name, returnType, flags) {}

    std::string compile( unsigned int level = 0 ) const override
    {
        std::string result = generateShift( level );

        if (m_flags & PUBLIC) {
            result += "public ";
        } else if (m_flags & PROTECTED) {
            result += "protected ";
        } else if (m_flags & PRIVATE) {
            result += "private ";
        } else if (m_flags & INTERNAL) {
            result += "internal ";
        }

        if (m_flags & STATIC) {
            result += "static ";
        } else if (m_flags & CONST) {
            result += "const ";
        } else if (m_flags & VIRTUAL) {
            result += "virtual ";
        }

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
    PrintOperatorCSharp(const std::string& text) : PrintOperatorUnit(text) {}

    std::string compile( unsigned int level = 0 ) const override
    {
        return generateShift( level ) + "Console.WriteLine( \"" + m_text + "\" );\n";
    }
};

#endif // CSHARPUNIT_H
