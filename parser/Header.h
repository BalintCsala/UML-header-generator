#ifndef UML_GENERATOR_HEADER_H
#define UML_GENERATOR_HEADER_H

#include <string>
#include <vector>
#include <regex>
#include "Class.h"
#include <clang-c/Index.h>
#include <utility>

class Header {
    std::string path;
public:
    explicit Header(std::string path);

    std::vector<Class> parse(const std::vector<std::string>& classes);

    static std::vector<std::string> extractClasses(const std::string &path);
};


#endif //UML_GENERATOR_HEADER_H
