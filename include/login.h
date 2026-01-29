#pragma once
#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QScopedPointer>
#include "ui_login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

/**
 * @brief The Login class handles user authentication
 * 
 * Provides login and registration functionality for users,
 * managing access to the budget tracking application.
 */
class Login : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for Login class
     * @param parent Pointer to the parent widget, default is nullptr
     */
    explicit Login(QWidget* parent = nullptr);

    /**
     * @brief Deleted copy constructor to prevent copying
     */
    Login(const Login&) = delete;

    /**
     * @brief Deleted assignment operator to prevent assignment
     */
    Login& operator=(const Login&) = delete;

    /**
     * @brief Destructor for Login class
     */
    ~Login();

    /**
     * @brief Gets the user ID of the logged-in user
     * @return User ID as an integer
     */
    int getUserId() const;

private slots:
    /**
     * @brief Slot for handling login button click
     * 
     * Validates user credentials and grants access
     */
    void onLoginButtonClicked();

    /**
     * @brief Slot for handling register button click
     * 
     * Creates a new user account
     */
    void onRegisterButtonClicked();

private:
    Ui::Login* ui = nullptr;  // Pointer to the UI elements
    int userId = -1;  // Stores the user ID of the logged-in user
};

#endif // LOGIN_H