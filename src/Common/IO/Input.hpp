#pragma once

#include <string>

#include "../../Exercice 3/CLI/CLIManagement.hpp"

namespace IO
{
    template<typename T, typename Predicate>
    bool secure_input(T& var, const std::string& prefix = "", const Predicate& predicate = [](const T&) { return true; }, const std::string& what = "");

    template<typename T, typename Predicate>
    bool input_once(T& var, const Predicate& predicate, const std::string& prefix = "");

    bool non_empty_input(std::string& var, const std::string& prefix = "");
}

#include "Input.tpp"