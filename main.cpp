#include <QCoreApplication>
#include "Unit.h"
#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"

#include "ClassCSharp.h"
#include "MethodCSharp.h"

std::string generateProgram() {

    ClassCSharp myClass( "MyClass", ClassCSharp::INTERNAL);

    myClass.add(std::make_shared< MethodCSharp >( "testFunc1", "void", 0 ));

    return myClass.compile();
}

int main()
{
    std::cout << generateProgram() << std::endl;

    return 0;
}
