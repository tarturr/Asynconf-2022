#include <algorithm>
#include <iostream>

#include "Input.hpp"


namespace IO
{
    bool non_empty_input(std::string& var, const std::string& prefix)
    {
        // Prédicat qui s'assure que l'input n'est pas vide.
        auto non_empty{ [](const std::string& str) -> bool
        {
            return !str.empty();
        }};

        return input_once(var, non_empty, prefix);
    }
}