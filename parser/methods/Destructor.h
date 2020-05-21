#ifndef UML_GENERATOR_DESTRUCTOR_H
#define UML_GENERATOR_DESTRUCTOR_H

#include <iostream>
#include <string>
#include <clang-c/Index.h>
#include <Access.h>

class Destructor {
    Access access;
    std::string name;
public:

    Destructor(const std::string &name, Access access);

    static Destructor parse(CXCursor destructorCursor, Access currentAccess);

    const std::string &getName() const;

};


#endif //UML_GENERATOR_DESTRUCTOR_H
