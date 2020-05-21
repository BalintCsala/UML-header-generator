#include "Destructor.h"

Destructor::Destructor(const std::string &name, Access access) : name(name), access(access) {}

Destructor Destructor::parse(CXCursor destructorCursor, Access currentAccess) {
    Destructor destructor(clang_getCString(clang_getCursorSpelling(destructorCursor)), currentAccess);
    std::cout << "    DestructorDecl: " << destructor.name << std::endl;
    return destructor;
}

const std::string &Destructor::getName() const {
    return name;
}

