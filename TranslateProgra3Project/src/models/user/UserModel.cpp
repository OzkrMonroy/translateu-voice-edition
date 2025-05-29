#include "UserModel.h"

UserModel::UserModel(const std::string& dbPath) : databasePath(dbPath), db(nullptr) {
    openConnection();
}

UserModel::~UserModel() {
    closeConnection();
}

void UserModel::openConnection() {
    if (sqlite3_open(databasePath.c_str(), &db)) {
        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

void UserModel::closeConnection() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool UserModel::createTable() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            username TEXT NOT NULL UNIQUE,
            password TEXT NOT NULL
        );
    )";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Error al crear la tabla: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool UserModel::addUser(const NewUser& user) {
    if (getUserByUsername(user.username).has_value()) {
        std::cerr << "El usuario con username '" << user.username << "' ya existe." << std::endl;
        return false;
    }

    std::string sql = "INSERT INTO users (name, username, password) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, user.username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, user.password.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

std::optional<User> UserModel::getUserByUsername(const std::string& username) {
    std::cerr << "[DEBUG] Ejecutando getUserByUsername con: " << username << std::endl;

    return findUserByQuery("SELECT id, name, username FROM users WHERE username = ?", { username });
}

std::optional<User> UserModel::getUser(const std::string& username, const std::string& password) {
    return findUserByQuery("SELECT id, name, username FROM users WHERE username = ? AND password = ?", { username, password });
}


std::optional<User> UserModel::findUserByQuery(const std::string& sql, const std::vector<std::string>& params) {
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return std::nullopt;

    for (size_t i = 0; i < params.size(); ++i) {
        sqlite3_bind_text(stmt, static_cast<int>(i + 1), params[i].c_str(), -1, SQLITE_TRANSIENT);
    }

    User user;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        user.id = sqlite3_column_int(stmt, 0);
        user.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        user.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        sqlite3_finalize(stmt);
        return user;
    }

    sqlite3_finalize(stmt);
    return std::nullopt;
}

