#include <iostream>
#include "Constructor.h"
#include "Parameter.h"

Constructor::Constructor(Access access)
        : access(access) {}

Constructor Constructor::parse(CXCursor constructorCursor, Access currentAccess) {
    Constructor constructor(currentAccess);

    std::cout << "    ConstructorDecl" << std::endl;

    clang_visitChildren(constructorCursor, [](CXCursor parameterCursor, CXCursor parent, CXClientData clientData) {
        Constructor constructor = *static_cast<Constructor *>(clientData);

        CXCursorKind kind = clang_getCursorKind(parameterCursor);
        if (kind == CXCursor_ParmDecl) {
            Parameter param = Parameter::parse(parameterCursor);
            constructor.parameters.push_back(param);
        }

        return CXChildVisit_Continue;
    }, (void *) &constructor);

    return constructor;
}

Access Constructor::getAccess() const {
    return access;
}
