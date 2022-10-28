#include "Commands.hpp"

#include <unordered_map>
#include <iostream>
#include <algorithm>


namespace Commands
{
    bool add(CLI* cli, User* sender, const std::vector<std::string>& args)
    {
        if (sender->has_permission("ajouter"))
        {
            if (args.size() < 3) return false;

            std::string name{ args[0] }, description{ args[1] };
            std::vector<std::string> usernames { args.begin() + 2, args.end() };
            std::vector<User*> users{};

            for (const auto& username : usernames)
            {
                auto current_user{ cli->find_user(username) };
                if (current_user.first != nullptr) users.emplace_back(current_user.first);
            }

            cli->user_tasks.emplace(std::make_unique<Task>(std::move(name), std::move(description)), std::move(users));
        }

        return true;
    }

    bool remove(CLI *cli, User *sender, const std::vector<std::string> &args)
    {
        if (sender->has_permission("supprimer"))
        {
            if (args.size() != 1) return false;
            auto task{ cli->find_task(args[0]) };

            if (task.first != nullptr)
                cli->user_tasks.erase(task.second);
        }

        return true;
    }

    bool complete(CLI *cli, User *sender, const std::vector<std::string> &args)
    {
        if (sender->has_permission("completer"))
        {
            if (args.size() != 1) return false;

            auto task{ cli->find_task(args[0]) };

            if (task.first != nullptr)
            {
                if (task.first->current_state != State::DONE)
                {
                    task.first->current_state = State::DONE;
                    std::cout << "La tache \"" << task.first->name << " est desormais marquee comme etant terminee." << std::endl;
                }
                else
                    std::cout << "La tache \"" << args[0] << " etait deja terminee." << std::endl;
            }
        }

        return true;
    }

    bool list(CLI *cli, User *sender, const std::vector<std::string> &args)
    {
        if (!args.empty()) return false;

        std::cout << "Liste des taches et leur statut :" << std::endl;

        for (const auto& user_task : cli->user_tasks)
        {
            auto users{ user_task.second };
            if (std::find(users.begin(), users.end(), sender) != users.end() || sender->name == "Administrateur")
            {
                std::cout << "- \"" << user_task.first->name << "\" : " << user_task.first->state() << std::endl;
            }
        }

        std::cout << std::endl;
        return true;
    }

    bool empty(CLI *cli, User *sender, const std::vector<std::string> &args)
    {
        if (!args.empty()) return false;

        std::cout << "Suppression de toutes les taches en cours..." << std::endl;
        cli->user_tasks.clear();
        std::cout << "Suppression terminee.\n" << std::endl;
    }

    bool add_account(CLI *cli, User *sender, const std::vector<std::string> &args)
    {
        if (sender->name == "Administrateur")
        {
            if (args.empty()) return false;

            std::unique_ptr<User> user{ std::make_unique<User>(args[0]) };

            if (args.size() > 1)
            {
                std::vector<std::string> permissions{ args.begin() + 1, args.end() };
                std::size_t idx{ 0 };

                for (const auto& permission : permissions)
                {
                    user->authorized_commands[idx] = cli->find_command(permission).first;
                }
            }

            std::cout << "L'utilisateur \"" << user->name << "\" a bien ete cree." << std::endl;
            cli->users.emplace_back(std::move(user));
        }

        std::cout << "Seul l'administrateur peut executer cette commande." << std::endl;
        return true;
    }

    bool remove_account(CLI *cli, User *sender, const std::vector<std::string> &args)
    {
        if (sender->name == "Administrateur")
        {
            if (args.size() != 1) return false;

            auto user{ cli->find_user(args[0]) };

            if (user.first == nullptr)
            {
                std::cout << "L'utilisateur \"" << args[0] << "\" n'a pas ete trouve.\n" << std::endl;
            }
            else
            {
                cli->users.erase(user.second);
                std::cout << "L'utilisateur \"" << args[0] << "\" a bien ete supprime." << std::endl;
            }
        }

        return true;
    }

    bool connect(CLI *cli, User *sender, const std::vector<std::string> &args)
    {
        if (sender->name == "Administrateur")
        {
            if (args.size() != 1) return false;

            auto user{ cli->find_user(args[0]) };

            if (user.first == nullptr)
            {
                std::cout << "L'utilisateur \"" << args[0] << "\" n'a pas ete trouve.\n" << std::endl;
            }
            else
            {
                std::cout << "Connexion en cours..." << std::endl;
                cli->current_user = user.first;
                std::cout << "Connexion reussie." << std::endl;
            }
        }

        return true;
    }
}