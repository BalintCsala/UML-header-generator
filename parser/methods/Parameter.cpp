#include "Parameter.h"

Parameter::Parameter(std::string name, std::string type)
        : name(std::move(name)), type(std::move(type)) {}

Parameter Parameter::parse(CXCursor parameterCursor) {
    Parameter param(
            clang_getCString(clang_getCursorSpelling(parameterCursor)),
            clang_getCString(clang_getTypeSpelling(clang_getCursorType(parameterCursor)))
    );
    std::cout << "        ParameterDecl: " << param.name << " (" << param.type << ")" << std::endl;

    // TODO: Check for default type
    /*clang_visitChildren(parameterCursor, [](CXCursor dataCursor, CXCursor parent, CXClientData clientData) {
        return CXChildVisit_Continue;
    }, (void*)&param)*/

    return param;
}

const std::string &Parameter::getType() const {
    return type;
}

const std::string &Parameter::getName() const {
    return name;
}

const std::string &Parameter::getDefaultValue() const {
    return defaultValue;
}

void Parameter::setDefaultValue(const std::string &defaultValue) {
    Parameter::defaultValue = defaultValue;
}
