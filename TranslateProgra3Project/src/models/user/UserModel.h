#pragma once
#include <string>
#include <optional>
#include <vector>
#include <iostream>
#include "../structs/User.h"
#include "../structs/NewUser.h"
#include "../../utils/paths/AppPaths.h"
#include <sqlite3.h>

class UserModel {
public:
    UserModel(const std::string& dbPath = (AppPaths::getDataDir() /"users.db").string());
    ~UserModel();

    bool createTable();
    bool addUser(const NewUser& user);
    std::optional<User> getUser(const std::string& username, const std::string& password);
    std::optional<User> getUserByUsername(const std::string& username);

private:
    void openConnection();
    void closeConnection();
    std::optional<User> findUserByQuery(const std::string& sql, const std::vector<std::string>& params);


    std::string databasePath;
    sqlite3* db;
    AppPaths appPaths;
};
