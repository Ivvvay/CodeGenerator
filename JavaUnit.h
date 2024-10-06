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
    ClassJAVA(const std::string& name) : ClassUnit(name) {}

    std::string compile( unsigned int level = 0 ) const override
    {
        std::string result = generateShift(level) + "class " + m_name + " {\n";

        for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
            if (m_fields[i].empty()) {
                continue;
            }

            for (const auto& f : m_fields[i]) {
                result += f->compile(level + 1);
                result += "\n";
            }
        }

        result += generateShift(level) + "};\n";
        return result;
    }
};

class MethodJAVA : public MethodUnit
{
public:
    enum Modifier {
        STATIC = 1,
        FINAL = 1 << 3,
        ABSTRACT = 1 << 4,
        PUBLIC = 1 << 5,
        PROTECTED = 1 << 6,
        PRIVATE = 1 << 7
    };
public:
    MethodJAVA(const std::string& name, const std::string& returnType, Flags flags)
        : MethodUnit(name, returnType, flags) {}

    std::string compile( unsigned int level = 0 ) const override
    {
        std::string result = generateShift( level );

        if (m_flags & PUBLIC) {
            result += "public ";
        } else if (m_flags & PROTECTED) {
            result += "protected ";
        } else if (m_flags & PRIVATE) {
            result += "private ";
        }

        if (m_flags & STATIC) {
            result += "static ";
        } else if (m_flags & FINAL) {
            result += "final ";
        }

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
    PrintOperatorJAVA(const std::string& text) : PrintOperatorUnit(text) {}

    std::string compile( unsigned int level = 0 ) const override
    {
        return generateShift( level ) + "System.out.println( \"" + m_text + "\" );\n";
    }
};

#endif // JAVAUNIT_H
