#include <algorithm>

#include "StringUtils.hpp"


namespace StringUtils
{
    std::vector<std::string> split_to(const std::string& str, char c)
    {
        std::vector<std::string> parts{};

        auto begin{ std::begin(str) };
        auto end{ std::end(str) };
        auto split{ std::find(begin, end, c) };

        while (split != end)
        {
            parts.emplace_back(begin, split);
            begin = split + 1;
            split = std::find(begin, end, c);
        }

        parts.emplace_back(begin, end);
        return parts;
    }
}