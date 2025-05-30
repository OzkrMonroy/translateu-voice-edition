#include "AuthController.h"


using namespace std;

AuthController* AuthController::instance = nullptr;

AuthController::AuthController(const std::string& dbPath) : dbPath(dbPath) {
	UserModel model(dbPath);
	model.createTable();
}

AuthController::~AuthController() = default;

AuthController* AuthController::getInstance(const std::string& dbPath)
{
	if (instance == nullptr) {
		instance = new AuthController(dbPath); 
	}
	return instance;
}

bool AuthController::login(const std::string& userName, const std::string& password)
{
	UserModel model(dbPath);
	auto user = model.getUser(userName, password); 
	if (user.has_value()) {
		currentUser = user;
		return true;
	}
	return false;
}

bool AuthController::registeredUser(const NewUser& user) const
{
	UserModel model(dbPath);
    return model.addUser(user);
}

void AuthController::logout() {
	currentUser = nullopt;
}


std::optional<User> AuthController::getCurrentUser() const
{
	return currentUser;
}
