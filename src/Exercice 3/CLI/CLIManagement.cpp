#include "CLIManagement.hpp"
#include "Commands.hpp"

#include <algorithm>
#include <memory>
#include <iostream>


Command::Command(std::string name, std::string correct_usage, std::function<bool(CLI*, User*, const std::vector<std::string>&)> action) noexcept
        : name(std::move(name)), correct_usage(std::move(correct_usage)), action(std::move(action))
{
}


User::User(std::string name, std::array<Command*, 9> authorized_commands) noexcept
        : name(std::move(name)), authorized_commands(authorized_commands)
{
}

bool User::has_permission(const std::string& command_name) noexcept
{
    bool is_found{ std::any_of(authorized_commands.begin(), authorized_commands.end(), [&command_name](Command* cmd)
    {
        return cmd->name == command_name;
    }) };

    if (is_found)
        return true;
    else
    {
        std::cout << "Vous n'avez pas la permission d'executer cette commande." << std::endl;
        return false;
    }
}

Task::Task(std::string name, std::string description) noexcept
        : name(std::move(name)), description(std::move(description)), current_state(State::TO_DO)
{
}

std::string Task::state() const noexcept
{
    std::string str_state;

    if (current_state == State::TO_DO)
        str_state = "A faire";
    else
        str_state = "Fait";

    return str_state;
}


CLI::CLI() noexcept
{
    commands = {
            std::make_unique<Command>("ajouter", "/ajouter <nom_de_tache> \"<description>\" <utilisateur> [autres utilisateurs...] : Creer une nouvelle tache.", Commands::add),
            std::make_unique<Command>("retirer", "/retirer <nom> : Supprimer une tache via son nom.", Commands::remove),
            std::make_unique<Command>("completer", "/completer <nom> : Marquer la tache comme completee.", Commands::complete),
            std::make_unique<Command>("liste", "/liste : Afficher toutes les taches qui vous sont visibles.", Commands::list),
            std::make_unique<Command>("vider", "/vider : Supprimer toutes les taches existantes.", Commands::empty),
            std::make_unique<Command>("ajouter-compte", "/ajouter-compte <nom_utilisateur> [permissions...] : Creer un nouvel utilisateur.", Commands::add_account),
            std::make_unique<Command>("supprimer-compte", "/supprimer-compte <nom_utilisateur> : Supprimer un utilisateur existant.", Commands::remove_account),
            std::make_unique<Command>("connecter", "/connecter <nom_utilisateur> : Se connecter au compte d'un utilisateur.", Commands::connect),
            std::make_unique<Command>("aide", "/aide [commandes...] : Obtenir l'usage des commandes demandees ou de toutes les commandes.", Commands::help)
    };

    User admin{ "Administrateur", {} };
    for (int i = 0; i < commands.size(); i++)
        admin.authorized_commands[i] = commands[i].get();

    users.emplace_back(std::make_unique<User>(std::move(admin)));
    current_user = users[0].get();
}

std::pair<User*, std::vector<std::unique_ptr<User>>::iterator> CLI::find_user(const std::string &username) noexcept
{
    for (auto user{ users.begin() }; user != users.end(); user++)
        if ((*user)->name == username)
            return { (*user).get(), user };

    std::cout << "L'utilisateur \"" << username << "\" n'a pas pu etre trouve." << std::endl;
    return { nullptr, users.end() };
}

std::pair<Task*, std::unordered_map<std::unique_ptr<Task>, std::vector<User*>>::iterator> CLI::find_task(const std::string &taskname) noexcept
{
    for (auto task{ user_tasks.begin() }; task != user_tasks.end(); task++)
        if ((*task).first->name == taskname)
            return { (*task).first.get(), task };

    std::cout << "La tache \"" << taskname << "\" n'a pas pu etre trouvee." << std::endl;
    return { nullptr, user_tasks.end() };
}

std::pair<Command *, std::array<std::unique_ptr<Command>, 8>::iterator> CLI::find_command(const std::string &commandname) noexcept
{
    for (auto cmd{ commands.begin() }; cmd != commands.end(); cmd++)
        if ((*cmd)->name == commandname)
            return { (*cmd).get(), cmd };

    return { nullptr, commands.end() };
}
