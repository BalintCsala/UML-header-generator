#ifndef UML_GENERATOR_CLASS_H
#define UML_GENERATOR_CLASS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include <clang-c/Index.h>
#include "Access.h"
#include "Field.h"
#include "methods/Method.h"
#include "methods/Constructor.h"
#include "methods/Destructor.h"

class Class {
public:

private:
    std::string name;
    std::string base;
public:
    std::vector<std::string> templateParameters;
    std::vector<Constructor> constructors;
    std::vector<Field> fields;
    std::vector<Method> methods;
    std::vector<Class> innerClasses;
    Destructor *destructor;

    Class(const std::string &name);

    static Class parse(CXCursor classCursor, bool isStruct = false);

    const std::string &getName() const;

    std::string getBase() const;
};


#endif //UML_GENERATOR_CLASS_H
