#ifndef UML_GENERATOR_FIELD_H
#define UML_GENERATOR_FIELD_H


#include <string>
#include <utility>
#include <clang-c/Index.h>

#include "Access.h"

class Field {
    Access access;
    std::string type;
    std::string name;
public:
    Field(Access access, std::string type, std::string name);

    static Field parse(CXCursor fieldCursor, Access acc);

    [[nodiscard]] Access getAccess() const;

    [[nodiscard]] const std::string &getType() const;

    [[nodiscard]] const std::string &getName() const;
};


#endif //UML_GENERATOR_FIELD_H
