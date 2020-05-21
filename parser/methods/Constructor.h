#ifndef UML_GENERATOR_CONSTRUCTOR_H
#define UML_GENERATOR_CONSTRUCTOR_H

#include <vector>
#include <string>
#include <utility>
#include <clang-c/Index.h>

#include "Access.h"
#include "Parameter.h"

class Constructor {
    Access access;
public:
    std::vector<Parameter> parameters;

    Constructor(Access access);

    static Constructor parse(CXCursor constructorCursor, Access currentAccess);

    [[nodiscard]] Access getAccess() const;
};


#endif //UML_GENERATOR_CONSTRUCTOR_H
