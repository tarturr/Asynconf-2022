#pragma once

#include "CLIManagement.hpp"

#include <string>

namespace Commands
{
    bool add(CLI* cli, User* sender, const std::vector<std::string>& args);
    bool remove(CLI* cli, User* sender, const std::vector<std::string>& args);
    bool complete(CLI* cli, User* sender, const std::vector<std::string>& args);
    bool list(CLI* cli, User* sender, const std::vector<std::string>& args);
    bool empty(CLI* cli, User* sender, const std::vector<std::string>& args);
    bool add_account(CLI* cli, User* sender, const std::vector<std::string>& args);
    bool remove_account(CLI* cli, User* sender, const std::vector<std::string>& args);
    bool connect(CLI* cli, User* sender, const std::vector<std::string>& args);
}