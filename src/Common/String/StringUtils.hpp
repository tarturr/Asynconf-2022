#pragma once

#include <string>
#include <vector>
#include <sstream>


namespace StringUtils
{
    template<typename Predicate>
    void filter(std::string& str, const Predicate& predicate);

    std::vector<std::string> split_to(const std::string& str, char c);
}

#include "StringUtils.tpp"