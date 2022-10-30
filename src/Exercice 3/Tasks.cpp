#include <iostream>
#include "Tasks.hpp"
#include "CLI/CLIManagement.hpp"
#include "../Common/IO/Input.hpp"
#include "../Common/String/StringUtils.hpp"

void third_run()
{
    CLI cli{};

    auto quit = [](const std::string& cmd)
    {
        return cmd != "exit";
    };

    std::string command;
    while (IO::input_once(command, quit, cli.current_user->name + ":~$ "))
    {
        auto args{ StringUtils::split_to(command, ' ') };
        auto cmd{ cli.find_command(args[0]).first };

        if (cmd == nullptr)
        {
            std::cout << "La commande \"" << command << "\" n'a pas ete trouvee.\n" << std::endl;
            continue;
        }

        args = { args.begin() + 1, args.end() };
        if (!cmd->action(cli, cli.current_user, args))
        {
            std::cout << cmd->correct_usage << '\n' << std::endl;
        }
    }
}