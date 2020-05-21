#ifndef UML_GENERATOR_HELPERS_H
#define UML_GENERATOR_HELPERS_H

#include <iostream>
#include <clang-c/CXString.h>

std::ostream &operator<<(std::ostream &stream, const CXString &str) {
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const CXType &type) {
    stream << clang_getTypeSpelling(type);
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const CXCursorKind &kind) {
    stream << clang_getCursorKindSpelling(kind);
    return stream;
}

namespace printer {

    struct recursivePrintData {
        std::string indent;
        std::ofstream *stream;
    };

    CXChildVisitResult printVisitor(CXCursor c, CXCursor parent, CXClientData clientData) {
        recursivePrintData data = *static_cast<recursivePrintData *>(clientData);

        *(data.stream) <<
                       data.indent <<
                       clang_getCursorKindSpelling(clang_getCursorKind(c)) <<
                       ": " << clang_getCString(clang_getCursorSpelling(c)) <<
                       ", " << clang_getTypeSpelling(clang_getCursorType(c)) <<
                       std::endl;

        recursivePrintData newDat(data);
        data.indent += "    ";

        clang_visitChildren(c, printVisitor, (void *) &data);

        return CXChildVisit_Recurse;
    }

    void printChildren(CXCursor cursor, recursivePrintData data) {
        clang_visitChildren(cursor, printVisitor, (void*) &data);
    }
}

#endif //UML_GENERATOR_HELPERS_H
