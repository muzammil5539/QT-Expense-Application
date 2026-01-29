#include "../include/stdafx.h"
#include "../include/project.h"
#include "../include/login.h"
#include <QDialog>
#include <QApplication>
#include <QtCharts/QChart>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QGraphicsItem>
#include <QtSql/QSqlError>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set up the SQLite database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("budget_tracker.db");

    // Open the database and check for errors
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
        return -1;
    }

    // Create users table if it doesn't exist
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "username TEXT UNIQUE,"
                   "password TEXT)")) {
        QMessageBox::critical(nullptr, "Database Error", query.lastError().text());
        return -1;
    }

    // Show the login dialog
    Login* loginDialog = new Login(nullptr);
    int result = loginDialog->exec();
    
    if (result != QDialog::Accepted) {
        delete loginDialog;
        return 0;
    }

    // Get the user ID from the login dialog
    int userId = loginDialog->getUserId();
    delete loginDialog;

    // Create and show the main project window
    Project* w = new Project(userId);
    w->show();
    
    // Execute the application event loop
    return a.exec();
}