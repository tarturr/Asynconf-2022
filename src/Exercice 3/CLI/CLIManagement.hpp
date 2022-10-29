#pragma once


#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>


class CLI;
struct User;


struct Command
{
public:
    Command() = delete;
    Command(const Command&) = default;
    Command(Command&&) = default;
    Command& operator=(const Command&) = default;
    Command& operator=(Command&&) = default;

    Command(std::string name, std::string correct_usage, std::function<bool(CLI*, User*, const std::vector<std::string>&)> action) noexcept;

    std::string name;
    std::string correct_usage;
    std::function<bool(CLI*, User*, const std::vector<std::string>&)> action;
};

enum State
{
    TO_DO,
    DONE
};

struct Task
{
    Task() = delete;
    Task(const Task&) = default;
    Task(Task&&) = default;
    Task& operator=(const Task&) = default;
    Task& operator=(Task&&) = default;

    Task(std::string name, std::string description) noexcept;

    std::string state() const noexcept;

    std::string name;
    std::string description;
    State current_state;
};


struct User
{
public:
    User() = default;
    User(const User&) = default;
    User(User&&) = default;
    User& operator=(const User&) = default;
    User& operator=(User&&) = default;

    explicit User(std::string name, std::array<Command*, 9> authorized_commands = {}) noexcept;

    bool has_permission(const std::string& command_name) noexcept;

    std::string name;
    std::array<Command*, 9> authorized_commands{};
};


class CLI
{
public:
    CLI() noexcept;

    std::pair<Command*, std::array<std::unique_ptr<Command>, 9>::iterator> find_command(const std::string& commandname) noexcept;
    std::pair<User*, std::vector<std::unique_ptr<User>>::iterator> find_user(const std::string& username) noexcept;
    std::pair<Task*, std::unordered_map<std::unique_ptr<Task>, std::vector<User*>>::iterator> find_task(const std::string& taskname) noexcept;

    std::array<std::unique_ptr<Command>, 9> commands;
    std::vector<std::unique_ptr<User>> users;
    std::unordered_map<std::unique_ptr<Task>, std::vector<User*>> user_tasks;

    User* current_user;
};