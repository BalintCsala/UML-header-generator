#include <iostream>
#include "Method.h"
#include "Parameter.h"

Method::Method(Access access, std::string returnType, std::string name)
        : access(access), returnType(std::move(returnType)), name(std::move(name)) {}

Access Method::getAccess() const {
    return access;
}

const std::string &Method::getReturnType() const {
    return returnType;
}

const std::string &Method::getName() const {
    return name;
}

Method Method::parse(CXCursor methodCursor, Access acc) {
    Method method(
            acc,
            clang_getCString(clang_getTypeSpelling(clang_getCursorType(methodCursor))),
            clang_getCString(clang_getCursorSpelling(methodCursor)));
    std::cout << "    MethodDecl: " << method.getName() << std::endl;

    clang_visitChildren(methodCursor, [](CXCursor parameterCursor, CXCursor parent, CXClientData clientData) {
        Method method = *static_cast<Method *>(clientData);

        CXCursorKind kind = clang_getCursorKind(parameterCursor);
        if (kind == CXCursor_ParmDecl) {
            Parameter param = Parameter::parse(parameterCursor);
            method.parameters.push_back(param);
        } else if (kind == CXCursor_TemplateTypeParameter || kind == CXCursor_NonTypeTemplateParameter) {
            std::string parameter = clang_getCString(clang_getCursorSpelling(parameterCursor));
            if (kind == CXCursor_NonTypeTemplateParameter) {
                parameter += ": ";
                parameter += clang_getCString(clang_getTypeSpelling(clang_getCursorType(parameterCursor)));
            }
            std::cout << "        TemplateTypeParameterDecl: " << parameter << std::endl;
            method.templateParameters.push_back(parameter);
        }

        return CXChildVisit_Continue;
    }, (void *) &method);

    return method;
}
