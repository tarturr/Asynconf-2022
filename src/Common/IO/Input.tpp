#include <limits>
#include <string>
#include <iostream>
#include "Input.hpp"


namespace IO
{
    template<typename T, typename Predicate>
    bool secure_input(T& var, const std::string& prefix, const Predicate& predicate, const std::string& what)
    {
        std::cout << prefix;

        while (!(std::cin >> var) || !predicate(var))
        {
            if (std::cin.eof())
            {
                throw std::runtime_error("[ERREUR D'ENTREE] La fin du fichier a ete atteinte.");
            }
            else if (std::cin.fail())
            {
                std::cout << "Erreur d'entree. Recommencez." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                std::cout << what << std::endl;
            }
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    template<typename Predicate>
    bool input_once(std::string& var, const Predicate& predicate, const std::string& prefix)
    {
        std::cout << prefix;
        return std::getline(std::cin, var) && predicate(var);
    }
}