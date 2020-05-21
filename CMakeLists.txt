cmake_minimum_required(VERSION 3.00)
project(uml_generator)

set(CMAKE_CXX_STANDARD 17)

include_directories(parser)

link_libraries(stdc++fs clang)

add_executable(uml_generator
        parser/Class.cpp parser/Class.h parser/Header.cpp parser/Header.h main.cpp parser/methods/Method.cpp
        parser/methods/Method.h parser/Access.h parser/Field.cpp parser/Field.h parser/methods/Constructor.cpp
        parser/methods/Constructor.h utils/helpers.h parser/methods/Parameter.h parser/methods/Parameter.cpp
        parser/methods/Destructor.cpp parser/methods/Destructor.h TestClasses.h)
