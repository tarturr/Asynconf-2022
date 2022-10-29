#include <string>
#include <iostream>

#include "Common/IO/Input.hpp"

#include "Exercice 1/Etoiles.hpp"
#include "Exercice 2/Phantom.hpp"
#include "Exercice 3/Tasks.hpp"
#include "Exercice 4/Supernova.hpp"


int main()
{
    std::string action;
    while (IO::non_empty_input(action, "Voulez-vous effectuer les tests predefinis (test) ou essayer le programme (run) ? (Laisser vide pour stopper) [test/run] : "))
    {
        if (action == "test")
        {
            int exercice;
            IO::secure_input(
                    exercice,
                    "Quel exercice voulez-vous tester ? [1-5] : ",
                    [](int number) { return number >= 1 && number <= 5; },
                    "L'exercice doit etre compris entre 1 et 5."
            );

            switch (exercice)
            {
                case 1:
                    first_test();
                    break;
                case 2:
                    second_test();
                    break;
                default:
                    std::cout << "Aucun test n'a ete ecrit pour cet exercice." << std::endl;
                    break;
            }
        }
        else if (action == "run")
        {
            int exercice;
            IO::secure_input(
                    exercice,
                    "Quel exercice voulez-vous tester ? [1-5] : ",
                    [](int number) { return number >= 1 && number <= 5; },
                    "L'exercice doit etre compris entre 1 et 5."
            );

            switch (exercice)
            {
                case 1:
                    first_run();
                    break;
                case 2:
                    second_run();
                    break;
                case 3:
                    third_run();
                    break;
                default:
                    std::cout << "Exercice non termine." << std::endl;
                    break;
            }
        }
        else
        {
            std::cout << "Je n'ai pas compris la demande. Assurez-vous d'avoir ecrit la commande en minuscule." << std::endl;
        }
    }
}