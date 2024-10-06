#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <memory>

using namespace std;

class Unit {
public:
    using Flags = unsigned int;

    enum Modifier {
        PUBLIC = 1,
        FILE = 1 << 1,
        INTERNAL = 1 << 2,
        PRIVATE = 1 << 3,
        PROTECTED = 1 << 4,
        PRIVATE_PROTECTED = 1 << 5,
        PROTECTED_INTERNAL = 1 << 6,
        FINAL = 1 << 7,
        ABSTRACT = 1 << 8,
        STATIC = 1 << 9,
        CONST = 1 << 10,
        VIRTUAL = 1 << 11
    };


public:
    virtual ~Unit() = default;

    virtual void add( const std::shared_ptr< Unit >& ) {
        throw std::runtime_error( "Not supported" );
    }

    virtual std::string compile( unsigned int level = 0 ) const = 0;

    Flags getModifier(){
        return m_modifier;
    }

protected:
    virtual std::string generateShift( unsigned int level ) const
    {
        static const auto DEFAULT_SHIFT = " ";
        std::string result;

        for ( unsigned int i = 0; i < level; ++i ) {
            result += DEFAULT_SHIFT;
        }

        return result;
    }
    std::string m_name;
    Flags m_modifier;
};

#endif // UNIT_H
