#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cctype>
#include <sstream>

#include "../Common/IO/Input.hpp"
#include "../Common/Test/Test.hpp"

#include "Etoiles.hpp"

std::string get_result(std::vector<std::string> planets)
{
    std::vector<std::pair<std::string, int>> planet_codes{};

    //for (const auto& planet : planets)
    for (int i = 0; i < planets.size(); i++)
    {
        std::string planet{ planets[i] };
        std::string prefix{ planet[0] };

        std::size_t index{ 0 };
        
        // Tant que le préfixe de la planète existe déjà dans les codes des
        // planètes, on ajoute le caractère suivant du nom au préfixe.
        for (const auto& pair : planet_codes)
        {
            while (pair.first == prefix)
            {
                ++index;
                prefix += planet[index];
            }
        }

        planet_codes.emplace_back( prefix, 0 );

        // On compte les lettres restantes depuis le dernier index trouvé.
        while (index < planet.size())
        {
            ++index;
            planet_codes[i].second++;
        }
    }

    // Les codes des planètes ont été entrées dans l'ordre inverse de celui qu'on attend.
    // Je traverse donc la map dans l'ordre inverse pour les remettre dans le bon ordre.
    std::ostringstream output{};
    for (const auto& code : planet_codes)
    {
        output << code.first /* Représente le préfixe */
                << code.second - 1 /* Représente le suffixe (le - 1 est obligatoire car je commence le comptage à 1, et pas 0) */;
    }

    return output.str();
}

void first_test()
{
    using namespace std::literals;

    Test::assert_result(get_result({ "Jupiter", "Terre" }), "J6T4"s);
    std::cout << "Test 1 valide." << std::endl;
    Test::assert_result(get_result({ "Lune", "Terre", "Soleil" }), "L3T4S5"s);
    std::cout << "Test 2 valide." << std::endl;
    Test::assert_result(get_result({ "Terre", "Mars", "Mercure" }), "T4M3Me5"s);
    std::cout << "Test 3 valide." << std::endl;
    Test::assert_result(get_result({ "Pluton", "Mercure", "Terre", "Mars", "Calisto" }), "P5M6T4Ma2C6"s);
    std::cout << "Test 4 valide." << std::endl;

    std::cout << "Tous les tests sont corrects." << std::endl;
}

void first_run()
{
    std::vector<std::string> planets{};

    // Pour chaque nom de planète entré, l'ajouter dans le vector.
    std::string current_planet;
    while (IO::non_empty_input(current_planet, "Nom de planete : "))
    {
        planets.emplace_back(std::move(current_planet));
    }

    std::cout << get_result(std::move(planets)) << '\n' << std::endl;
}