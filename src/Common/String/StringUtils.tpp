#include <algorithm>

namespace StringUtils
{
    // Filtrer une chaine de caractères en ignorant certains caractères.
    template<typename Predicate>
    void filter(std::string& str, const Predicate& predicate)
    {
        str = { str.begin(), std::find_if(str.begin(), str.end(), predicate) };
    }
}