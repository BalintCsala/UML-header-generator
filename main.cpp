#include <iostream>
#include <experimental/filesystem>
#include "parser/Header.h"
#include "TestClasses.h"

namespace filesystem = std::experimental::filesystem;

void findClasses(std::vector<std::string> &classes, const std::string &path) {
    for (const auto &entry : filesystem::directory_iterator(path)) {
        std::string ext = entry.path().extension();
        if (filesystem::is_directory(entry.path())) {
            findClasses(classes, entry.path());
        } else if (ext == ".h" || ext == ".hpp" || ext == ".cpp") {
            std::vector<std::string> result = Header::extractClasses(entry.path());
            classes.insert(classes.end(), result.begin(), result.end());
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <directory> <main file> <output directory>" << std::endl;
        return 0;
    }

    // Clear ast output
    std::ofstream ofstream("test.ast");
    ofstream.close();

    MultipleTemplateClassTest<long, int, 10> a;
    a.helloDefault(20);

    testNameSpace::NameSpaceTest nameSpaceTest;

    std::string directory = argv[1];
    std::string mainPath = argv[2];
    std::string outputDirectory = argv[3];

    std::vector<std::string> classes;
    findClasses(classes, directory);

    std::vector<Class> parsedClasses = Header(mainPath).parse(classes);

    std::cout << std::endl;
    std::cout << "Parsed class count: " << parsedClasses.size() << std::endl;

    return 0;
}
