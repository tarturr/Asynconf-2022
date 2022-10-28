cmake_minimum_required(VERSION 3.23)
project(Thread_Learning)

set(CMAKE_CXX_STANDARD 14)

add_executable(Thread_Learning src/main.cpp
        src/Common/IO/Input.cpp src/Common/IO/Input.hpp src/Common/IO/Input.tpp
        src/Common/Test/Test.tpp src/Common/Test/Test.hpp
        src/Common/String/StringUtils.hpp src/Common/String/StringUtils.cpp
        "src/Exercice 1/Etoiles.cpp" "src/Exercice 1/Etoiles.hpp"
        "src/Exercice 2/Phantom.cpp" "src/Exercice 2/Phantom.hpp"
        "src/Exercice 3/Tasks.cpp" "src/Exercice 3/Tasks.hpp"
        "src/Exercice 4/Supernova.cpp" "src/Exercice 4/Supernova.hpp"
        "src/Exercice 3/CLI/CLIManagement.cpp" "src/Exercice 3/CLI/CLIManagement.hpp" "src/Exercice 3/CLI/Commands.cpp" "src/Exercice 3/CLI/Commands.hpp")
