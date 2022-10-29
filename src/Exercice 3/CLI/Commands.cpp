#include "Commands.hpp"

#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <sstream>


namespace Commands
{
    bool add(CLI* cli, User* sender, const std::vector<std::string>& args)
    {
        if (sender->has_permission("ajouter"))
        {
            if (args.size() < 3) return false;
            if (args[1][0] != '"') return false;

            std::string name{ args[0] };
            std::ostringstream description;

            bool is_closed{ false };
            std::size_t idx{ 1 };
            for (; idx < args.size() || is_closed; idx++)
            {
                std::string word{ args[idx] };

                if (idx == 1)
                    word = { word.begin() + 1, word.end() };
                else
                {
                    auto last_char{ word.end() - 1 };

                    if (*last_char == '"')
                    {
                        word = { word.begin(), last_char };
                        is_closed = true;
                        std::cout << "Ok !" << std::endl;
                    }
                }

                description << word << " ";
            }

            if (!is_closed) return false;

            std::cout << "Final description: " << description.str() << std::endl;

            std::vector<std::string> usernames { args.begin() + idx, args.end() };
            std::vector<User*> users{};

            for (const auto& username : usernames)
            {
                auto current_user{ cli->find_user(username) };
                if (current_user.first != nullptr) users.emplace_back(current_user.first);
            }

            cli->user_tasks.emplace(std::make_unique<Task>(std::move(name), description.str()), std::move(users));
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

            return true;
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

    bool help(CLI *cli, User *sender, const std::vector<std::string> &args)
    {
        if (args.empty())
        {
            std::cout << "Voici toutes les commandes qui vous sont disponibles:" << std::endl;
            for (const auto& cmd : sender->authorized_commands)
            {
                std::cout << "- " << cmd->correct_usage << std::endl;
            }
        }
        else
        {
            for (const auto& cmd_name : args)
            {
                auto command{ cli->find_command(cmd_name) };

                if (command.first != nullptr)
                {
                    std::cout << "- " << command.first->correct_usage << std::endl;
                }
            }
        }

        return true;
    }
}