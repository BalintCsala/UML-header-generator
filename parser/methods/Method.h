#ifndef UML_GENERATOR_METHOD_H
#define UML_GENERATOR_METHOD_H


#include <vector>
#include <string>
#include <utility>
#include <clang-c/Index.h>

#include "Access.h"
#include "Parameter.h"

class Method {
    Access access;
    std::string returnType;
    std::string name;
public:
    std::vector<std::string> templateParameters;
    std::vector<Parameter> parameters;

    Method(Access access, std::string returnType, std::string name);

    static Method parse(CXCursor methodCursor, Access acc);

    [[nodiscard]] Access getAccess() const;

    [[nodiscard]] const std::string &getReturnType() const;

    [[nodiscard]] const std::string &getName() const;
};


#endif //UML_GENERATOR_METHOD_H
