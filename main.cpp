#include <QCoreApplication>
#include "Unit.h"
#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"

#include "CSharpUnit.h"


std::string generateProgram() {
    auto myClass = std::make_shared< ClassCSharp >( "MyClass", ClassCSharp::INTERNAL);

    auto myClass3 = std::make_shared< ClassCSharp >( "MyClass3", ClassCSharp::PUBLIC);

    auto method = std::make_shared< MethodCSharp >( "testFunc2", "void", 0 );

    method->add(std::make_shared< PrintOperatorUnitCSharp >( R"(Hello, world!\n)" ));

    method->add(myClass3);

    method->add(std::make_shared< MethodCSharp >( "testFunc3", "real", 4 ));

    myClass->add(method);


    return myClass->compile();
}


int main()
{
    std::cout << generateProgram() << std::endl;

    return 0;
}
