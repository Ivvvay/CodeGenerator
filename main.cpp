#include <QCoreApplication>
#include "Unit.h"
#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"

#include "Factory.h"
#include "CppUnit.h"
#include "CSharpUnit.h"
#include "JavaUnit.h"

std::string generateProgram(Factory* factory) {
    std::shared_ptr<ClassUnit> myClass = factory->buildClass("MyClass");

    myClass->add(
        factory->buildMethod("testFunc1", "void", MethodUnit::PUBLIC),
        ClassUnit::PUBLIC
        );

    myClass->add(
        factory->buildMethod("testFunc2", "void", MethodUnit::STATIC | MethodUnit::PRIVATE),
        ClassUnit::PRIVATE
        );

    myClass->add(
        factory->buildMethod("testFunc3", "void", MethodUnit::CONST | MethodUnit::PROTECTED | MethodUnit::PRIVATE),
        ClassUnit::PROTECTED
        );

    std::shared_ptr<MethodUnit> method = factory->buildMethod("testFunc4", "void", MethodUnit::STATIC | MethodUnit::PROTECTED);
    method->add(factory->buildPrintOperator( R"(Hello, world!\n)"));
    myClass->add(method, ClassUnit::PROTECTED);

    return myClass->compile();
}

int main()
{
    std::cout << "C++:" << std::endl;
    CppFactory cppFactory;
    std::cout << generateProgram(&cppFactory) << std::endl;

    std::cout << "C#:" << std::endl;
    CSharpFactory cSharpFactory;
    std::cout << generateProgram(&cSharpFactory) << std::endl;

    std::cout << "JAVA:" << std::endl;
    JavaFactory javaFactory;
    std::cout << generateProgram(&javaFactory) << std::endl;

    return 0;
}
