#include "Field.h"

Field::Field(Access access, std::string type, std::string name)
        : access(access), type(std::move(type)), name(std::move(name)) {}

Access Field::getAccess() const {
    return access;
}

const std::string &Field::getType() const {
    return type;
}

const std::string &Field::getName() const {
    return name;
}

Field Field::parse(CXCursor fieldCursor, Access acc) {
    return Field(
            acc,
            clang_getCString(clang_getCursorSpelling(fieldCursor)),
            clang_getCString(clang_getTypeSpelling(clang_getCursorType(fieldCursor)))
    );
}
