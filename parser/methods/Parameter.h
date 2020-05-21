#ifndef UML_GENERATOR_PARAMETER_H
#define UML_GENERATOR_PARAMETER_H

#include <string>
#include <utility>
#include <clang-c/Index.h>
#include <iostream>

class Parameter {
    std::string name;
    std::string type;
    std::string defaultValue;
public:
    explicit Parameter(std::string name, std::string type);

    static Parameter parse(CXCursor parameterCursor);

    [[nodiscard]] const std::string &getType() const;

    const std::string &getName() const;

    const std::string &getDefaultValue() const;

    void setDefaultValue(const std::string &defaultValue);
};


#endif //UML_GENERATOR_PARAMETER_H
