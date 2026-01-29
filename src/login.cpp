#include "../include/stdafx.h"
#include "../include/login.h"
#include "ui_login.h"  // Include the header file for Ui_Login

// Constructor for the Login class
Login::Login(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Login())
    , userId(-1)  // Initialize userId to -1
{
    ui->setupUi(this);  // Set up the UI
    // Connect the login button click signal to the onLoginButtonClicked slot
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::onLoginButtonClicked);
    // Connect the register button click signal to the onRegisterButtonClicked slot
    connect(ui->registerButton, &QPushButton::clicked, this, &Login::onRegisterButtonClicked);
}

// Destructor for the Login class
Login::~Login()
{
    delete ui;  // Clean up the UI
}

// Getter for userId
int Login::getUserId() const
{
    return userId;
}

// Slot for handling login button click
void Login::onLoginButtonClicked()
{
    QString username = ui->usernameLineEdit->text();  // Get the username from the input field
    QString password = ui->passwordLineEdit->text();  // Get the password from the input field

    QSqlQuery query;
    // Prepare the SQL query to check the username and password
    query.prepare("SELECT id FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec()) {
        if (query.next()) {
            userId = query.value(0).toInt();  // Set the userId if login is successful
            accept();  // Close the dialog with an accepted status
        }
        else {
            // Show a warning message if the login fails
            QMessageBox::warning(this, "Login Failed", "Incorrect username or password.");
        }
    }
}

// Slot for handling register button click
void Login::onRegisterButtonClicked()
{
    QString username = ui->usernameLineEdit->text();  // Get the username from the input field
    QString password = ui->passwordLineEdit->text();  // Get the password from the input field

    if (username.isEmpty() || password.isEmpty()) {
        // Show a warning message if username or password is empty
        QMessageBox::warning(this, "Registration Error", "Username and password cannot be empty.");
        return;
    }

    // Check if the username already exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM users WHERE username = :username");
    checkQuery.bindValue(":username", username);
    
    if (checkQuery.exec() && checkQuery.next()) {
        // Show a warning message if the username already exists
        QMessageBox::warning(this, "Registration Error", "Username already exists.");
        return;
    }

    // Insert the new user into the database
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    insertQuery.bindValue(":username", username);
    insertQuery.bindValue(":password", password);
    
    if (insertQuery.exec()) {
        userId = insertQuery.lastInsertId().toInt();  // Set the userId to the new user's ID
        accept();  // Close the dialog with an accepted status
    } else {
        // Show a warning message if the registration fails
        QMessageBox::warning(this, "Registration Error", insertQuery.lastError().text());
    }
}