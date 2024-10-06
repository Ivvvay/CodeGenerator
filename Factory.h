#ifndef FACTORY_H
#define FACTORY_H

#include "Unit.h"
#include "ClassUnit.h"
#include "MethodUnit.h"
#include "PrintOperatorUnit.h"

#include "CppUnit.h"
#include "CSharpUnit.h"
#include "JavaUnit.h"

class Factory {
public:
    virtual std::shared_ptr<ClassUnit> buildClass(const std::string& name) = 0;
    virtual std::shared_ptr<MethodUnit> buildMethod(const std::string& name, const std::string& returnType, Unit::Flags flags) = 0;
    virtual std::shared_ptr<PrintOperatorUnit> buildPrintOperator(const std::string& text) = 0;
};

class CppFactory : public Factory {
public:
    std::shared_ptr<ClassUnit> buildClass(const std::string& name) override {
        return std::make_shared<ClassCpp>(name);
    }
    std::shared_ptr<MethodUnit> buildMethod(const std::string& name, const std::string& returnType, Unit::Flags flags) override {
        return std::make_shared<MethodCpp>(name, returnType, flags);
    }
    std::shared_ptr<PrintOperatorUnit> buildPrintOperator(const std::string& text) override {
        return std::make_shared<PrintOperatorCpp>(text);
    }
};

class JavaFactory : public Factory {
public:
    std::shared_ptr<ClassUnit> buildClass(const std::string& name) override {
        return std::make_shared<ClassJAVA>(name);
    }
    std::shared_ptr<MethodUnit> buildMethod(const std::string& name, const std::string& returnType, Unit::Flags flags) override {
        return std::make_shared<MethodJAVA>(name, returnType, flags);
    }
    std::shared_ptr<PrintOperatorUnit> buildPrintOperator(const std::string& text) override {
        return std::make_shared<PrintOperatorJAVA>(text);
    }
};

class CSharpFactory : public Factory {
public:
    std::shared_ptr<ClassUnit> buildClass(const std::string& name) override {
        return std::make_shared<ClassCSharp>(name);
    }
    std::shared_ptr<MethodUnit> buildMethod(const std::string& name, const std::string& returnType, Unit::Flags flags) override {
        return std::make_shared<MethodCSharp>(name, returnType, flags);
    }
    std::shared_ptr<PrintOperatorUnit> buildPrintOperator(const std::string& text) override {
        return std::make_shared<PrintOperatorCSharp>(text);
    }
};



#endif // FACTORY_H
