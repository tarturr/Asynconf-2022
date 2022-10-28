#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "../Common/Test/Test.hpp"
#include "../Common/String/StringUtils.hpp"
#include "../Common/IO/Input.hpp"

#include "Phantom.hpp"


struct SpaceshipData
{
    SpaceshipData(std::vector<std::string> data) noexcept;

    std::string name;
    int speed;
    int price;
};

SpaceshipData::SpaceshipData(std::vector<std::string> data) noexcept
{
    // Définition d'un filtre pour ne conserver que les nombres (et pour omettre les "km/h", par exemple).
    auto keep_nums_only{ [](char c) { return isalpha(c) || c == '/'; } };

    // date[0] est le premier élément des données reçues (ici "name=Crystal").
    // [1] renvoie l'élément à droite du signe égal (ici "Crystal").
    name = StringUtils::split_to(data[0], '=')[1];

    std::string str_speed{ StringUtils::split_to(data[1], '=')[1] };
    // On enlève les caractères n'étant pas des chiffres (ici "km/h").
    StringUtils::filter(str_speed, keep_nums_only);
    speed = std::stoi(str_speed);

    std::string str_price{ StringUtils::split_to(data[2], '=')[1] };
    StringUtils::filter(str_price, keep_nums_only);
    price = std::stoi(str_price);
}

long long get_result(std::string data, long long days)
{
    SpaceshipData spaceship{StringUtils::split_to(data, ';') };
    return static_cast<long long>(days * 24 * spaceship.speed * spaceship.price);
}

void second_test()
{
    Test::assert_result(get_result("name=Crystal;speed=20000km/h;price=400/km", 10), static_cast<long long>(1920000000));
    std::cout << "Test 1 valide." << std::endl;
    Test::assert_result(get_result("name=Atmos;speed=2045km/h;price=23/km", 2), static_cast<long long>(2257680));
    std::cout << "Test 2 valide." << std::endl;
    Test::assert_result(get_result("name=CircleBurn;speed=178547km/h;price=3612/km", 6), static_cast<long long>(92867294016));
    std::cout << "Test 3 valide." << std::endl;
    Test::assert_result(get_result("name=SpaceDestroyer;speed=98928423km/h;price=9294/km", 12), static_cast<long long>(264798939848256));
    std::cout << "Test 4 valide." << std::endl;

    std::cout << "Tous les tests sont valides." << std::endl;
}

void second_run()
{
    std::unordered_map<std::string, long long> carac_and_durations{};

    std::string carac;
    while (IO::non_empty_input(carac, "Caracteristiques du vaisseau: "))
    {
        int duration;
        IO::secure_input(
                duration,
                "Duree du trajet: ",
                [](int n) { return true; }
        );

        carac_and_durations.insert({ std::move(carac), duration });
    }

    for (const auto& pair : carac_and_durations)
    {
        std::cout << get_result(pair.first, pair.second) << "€" << std::endl;
    }
}