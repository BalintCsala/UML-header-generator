#include <methods/Destructor.h>
#include "Class.h"
#include "../utils/helpers.h"

Class::Class(const std::string &name) : name(name), destructor(nullptr) {}

Class Class::parse(CXCursor classCursor, bool isStruct) {

    Class result(clang_getCString(clang_getCursorSpelling(classCursor)));
    std::cout << "ClassDecl: " << result.name << std::endl;
    struct clientData {
        Access currentAccess;
        Class result;

        explicit clientData(Access currentAccess, Class result) : currentAccess(currentAccess), result(result) {}
    } cd(isStruct ? PUBLIC : PRIVATE, result);


    std::ofstream ofstream("test.ast", std::fstream::app);
    ofstream << result.name << std::endl;
    printer::recursivePrintData data;
    data.indent = "    ";
    data.stream = &ofstream;
    printer::printChildren(classCursor, data);


    clang_visitChildren(
            classCursor,
            [](CXCursor classPartCursor, CXCursor parent, CXClientData client_data) {
                auto *data = static_cast<struct clientData *>(client_data);

                // Intentionally using a long if...else chain here
                // Switch statements don't allow for variable declarations inside the cases
                CXCursorKind kind = clang_getCursorKind(classPartCursor);
                if (kind == CXCursor_TemplateTypeParameter || kind == CXCursor_NonTypeTemplateParameter) {
                    std::string param = clang_getCString(clang_getCursorSpelling(classPartCursor));
                    if (kind == CXCursor_NonTypeTemplateParameter) {
                        param += ": ";
                        param += clang_getCString(clang_getTypeSpelling(clang_getCursorType(classPartCursor)));
                    }
                    std::cout << "    TemplateTypeParameterDecl: " << param << std::endl;
                    data->result.templateParameters.push_back(param);
                } else if (kind == CXCursor_CXXBaseSpecifier) {
                    std::string newBase = clang_getCString(clang_getTypeSpelling(clang_getCursorType(classPartCursor)));
                    std::cout << "    Base class: " << newBase << std::endl;
                    data->result.base = newBase;
                } else if (kind == CXCursor_CXXAccessSpecifier) {
                    switch (clang_getCXXAccessSpecifier(classPartCursor)) {
                        case CX_CXXPublic:
                            data->currentAccess = PUBLIC;
                            break;
                        case CX_CXXProtected:
                            data->currentAccess = PROTECTED;
                            break;
                        case CX_CXXPrivate:
                        case CX_CXXInvalidAccessSpecifier:
                            data->currentAccess = PRIVATE;
                            break;
                    }
                } else if (kind == CXCursor_FieldDecl) {
                    Field field = Field::parse(classPartCursor, data->currentAccess);
                    data->result.fields.push_back(field);
                } else if (kind == CXCursor_CXXMethod || kind == CXCursor_FunctionTemplate) {
                    Method method = Method::parse(classPartCursor, data->currentAccess);
                    data->result.methods.push_back(method);
                } else if (kind == CXCursor_Constructor) {
                    Constructor constructor = Constructor::parse(classPartCursor, data->currentAccess);
                    data->result.constructors.push_back(constructor);
                } else if (kind == CXCursor_ClassDecl || kind == CXCursor_StructDecl) {
                    Class cla = Class::parse(classPartCursor, kind == CXCursor_StructDecl);
                    data->result.innerClasses.push_back(cla);
                } else if (kind == CXCursor_Destructor) {
                    Destructor newDestructor = Destructor::parse(classPartCursor, data->currentAccess);
                    data->result.destructor = &newDestructor;
                } else {
                    std::cout << "    Unhandled: " << clang_getCursorKindSpelling(clang_getCursorKind(classPartCursor))
                              << ": " << clang_getCString(clang_getCursorSpelling(classPartCursor)) << std::endl;
                }
                return CXChildVisit_Continue;
            },
            (void *) &cd
    );

    return result;
}

const std::string &Class::getName() const {
    return name;
}

std::string Class::getBase() const {
    return base;
}

