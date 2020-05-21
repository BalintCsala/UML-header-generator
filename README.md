## UML header generator

Generate compileable header files that double as UML diagrams.

### Building

Requires LibClang and CMake

Run

```
cmake -f CMakeLists.txt
make
```

### Usage

```
uml_generator <source directory> <main file> <output directory>
```

The output directory will contain all the files needed