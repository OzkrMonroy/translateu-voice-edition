#pragma once
#include <iostream>
#include <string>
#include <optional>
#include "../../models/user/UserModel.h"
#include "../../models/structs/NewUser.h"
#include "../../utils/paths/AppPaths.h"

class AuthController 
{

private:
	static AuthController* instance;
	std::string dbPath;
	std::optional<User> currentUser; 

	AuthController(const std::string& dbPath);

public: 

	AuthController(const AuthController&) = delete; 
	AuthController& operator = (const AuthController&) = delete; 

	~AuthController();

	static AuthController* getInstance(const std::string& dbPath = (AppPaths::getDataDir() / "users.db").string());

	
	bool login(const std::string& userName, const std::string& password);
	bool registeredUser(const NewUser& user) const;
	void logout();
	std::optional<User> getCurrentUser() const;
};
