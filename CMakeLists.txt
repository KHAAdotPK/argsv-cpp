cmake_minimum_required(VERSION 3.24)
project(argsv-cpp-demo)

# Add include directories
include_directories("C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Tools\\MSVC\\14.37.32822\\include")

# Add a definition for the GRAMMAR_END_OF_TOKEN_MARKER macro globally
## add_definitions(-DGRAMMAR_END_OF_TOKEN_MARKER=" ")
## add_definitions(-DGRAMMAR_END_OF_TOKEN_MARKER_SIZE=1)

# --------------------
#  argsv-cpp-demo.exe
# --------------------
# Add the source file
set(SOURCES_ARGSV_CPP_DEMO src/main.cpp)
add_executable(argsv-cpp-demo ${SOURCES_ARGSV_CPP_DEMO})

# Add a definition for the GRAMMAR_END_OF_TOKEN_MARKER macro for the argsv-cpp-demo target
target_compile_definitions(argsv-cpp-demo PRIVATE GRAMMAR_END_OF_TOKEN_MARKER=" ")
target_compile_definitions(argsv-cpp-demo PRIVATE GRAMMAR_END_OF_TOKEN_MARKER_SIZE=1)





