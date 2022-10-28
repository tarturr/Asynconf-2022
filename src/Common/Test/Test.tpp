#include <memory>
#include <cassert>
#include <iostream>

namespace Test
{
    template<class T>
    void assert_result(T provided, T expected)
    {
        if (provided != expected)
        {
            std::cout << "Votre programme a donne l'output : \"" << provided
                    << "\"\nMais la reponse attendue etait : \"" << expected << '"' << std::endl;

            assert(provided == expected && "The provided result is different from the expected one.");
        }
    }
}