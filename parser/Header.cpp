#include "Header.h"

Header::Header(std::string path) : path(std::move(path)) {}

std::vector<Class> Header::parse(const std::vector<std::string> &classes) {
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(
            index,
            path.c_str(), nullptr, 0,
            nullptr, 0,
            CXTranslationUnit_None);
    if (unit == nullptr) {
        std::cerr << "Unable to parse translation unit. Quitting." << std::endl;
        exit(-1);
    }


    struct clientData {
        std::vector<std::string> classes;
        std::vector<Class> result;
    } clientData;
    clientData.classes = classes;

    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(
            cursor,
            [](CXCursor c, CXCursor parent, CXClientData client_data) {
                auto *data = static_cast<struct clientData *>(client_data);
                std::vector<std::string> classes = data->classes;
                std::string name = clang_getCString(clang_getCursorSpelling(c));
                bool userDefined = std::find(classes.begin(), classes.end(), name) != classes.end();
                CXCursorKind kind = clang_getCursorKind(c);
                bool isClass = kind == CXCursor_ClassDecl || kind == CXCursor_ClassTemplate;
                bool isStruct = kind == CXCursor_StructDecl;
                if ((userDefined && (isClass || isStruct))) {
                    Class cla = Class::parse(c, isStruct);
                    data->result.push_back(cla);
                    return CXChildVisit_Continue;
                }
                return CXChildVisit_Recurse;
            },
            (void *) &clientData
    );

    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);

    return clientData.result;
}

std::vector<std::string> Header::extractClasses(const std::string &path) {
    std::ifstream stream(path);
    std::string code;
    if (stream.is_open()) {
        std::string line;
        while (getline(stream, line)) {
            code += line + " ";
        }
    }
    std::vector<std::string> result;

    std::regex classRegex(R"((class|struct)\s+\S+)");
    std::smatch matches;
    std::string::const_iterator it = code.cbegin();
    while (std::regex_search(it, code.cend(), matches, classRegex)) {
        std::regex replaceRegex(R"((class|struct)\s+)");
        result.push_back(std::regex_replace(std::string(matches[0]), replaceRegex, ""));
        it = matches.suffix().first;
    }

    return result;
}

