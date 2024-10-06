#include <QCoreApplication>
#include "Unit.h"
#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"

#include "CppUnit.h"
#include "CSharpUnit.h"
#include "JavaUnit.h"

std::string generateCpp() {
    ClassCpp myClass( "CppClass" );

    auto myClass2= std::make_shared< ClassCpp >( "MyClassCpp", ClassCpp::PUBLIC);
    myClass.add(myClass2);

    auto method1 = std::make_shared< MethodCpp >("testfunAc1", "real", MethodCpp::VIRTUAL | MethodCpp::PROTECTED);

    myClass2->add(method1);

    method1->add(std::make_shared< PrintOperatorCpp >( "(Hello, Cpp!" ));

    return myClass.compile();
}

std::string generateCSharp() {

    auto myClass = std::make_shared< ClassCSharp >( "MyClassC#", ClassCSharp::INTERNAL);

    auto method = std::make_shared< MethodCSharp >( "testFunc2", "void", ClassCSharp::PRIVATE_PROTECTED );

    method->add(std::make_shared< PrintOperatorCSharp >( "(Hello, C#!" ));

    myClass->add(method);

    return myClass->compile();
}

std::string generateJAVA() {
    auto myClass = std::make_shared< ClassJAVA >( "MeClassJAVA", ClassJAVA::FINAL | ClassJAVA::PUBLIC);

    auto method1 = std::make_shared< MethodJAVA >("testFucn1", "long",
                                                MethodJAVA::PROTECTED | MethodJAVA::ABSTRACT | MethodJAVA::STATIC);

    method1->add(std::make_shared< PrintOperatorJAVA >( "(Hello, JAVA!" ));

    myClass->add(method1);

    return myClass->compile();
}

int main()
{
    std::cout << generateJAVA() << std::endl;

    return 0;
}
