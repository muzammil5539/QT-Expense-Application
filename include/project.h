#ifndef PROJECT_H
#define PROJECT_H

#include "stdafx.h"
#include "transaction.h"
#include "transaction_collection.h"

/**
 * @file project.h
 * @brief Main application window class for the Budget Tracker
 */

/**
 * @class Project
 * @brief Main window class managing the application UI and business logic
 * 
 * This class inherits from QMainWindow and serves as the primary interface
 * for the Budget Tracker application. It handles all user interactions,
 * manages transaction data, displays financial information in tables and
 * charts, and persists data to the SQLite database.
 * 
 * The class supports two view modes:
 * - BalanceSheet: Shows all transactions with running balance
 * - CategoryView: Shows filtered transactions for a specific category
 */
class Project : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param userId The unique identifier of the logged-in user
     * @param parent Optional parent widget (default: nullptr)
     */
    explicit Project(int userId, QWidget *parent = nullptr);
    
    /**
     * @brief Destructor
     * 
     * Closes database connections and cleans up resources
     */
    ~Project();

private slots:
    /**
     * @brief Slot for handling "Add Income" button click
     * 
     * Opens a dialog to collect income transaction details,
     * validates input, and adds the transaction to the database
     * and display.
     */
    void onAddIncome();
    
    /**
     * @brief Slot for handling "Add Expense" button click
     * 
     * Opens a dialog to collect expense transaction details,
     * validates input, and adds the transaction to the database
     * and display.
     */
    void onAddExpense();
    
    /**
     * @brief Slot for viewing transactions by category
     * 
     * Displays a dialog to select a category, then filters and
     * displays only transactions from that category.
     */
    void onViewCategory();
    
    /**
     * @brief Slot for resetting view to show all transactions
     * 
     * Returns to the balance sheet view showing all transactions
     * in chronological order.
     */
    void onResetView();

private:
    /**
     * @enum ViewMode
     * @brief Enumeration of available view modes
     */
    enum ViewMode {
        BalanceSheet,   ///< Shows all transactions with running balance
        CategoryView    ///< Shows filtered transactions for a category
    };

    /**
     * @brief Sets up the user interface
     * 
     * Creates and configures all UI widgets including buttons,
     * table, charts, and layout.
     */
    void setupUi();
    
    /**
     * @brief Establishes database connection
     * 
     * Opens the SQLite database connection for the current user
     * and creates necessary tables if they don't exist.
     */
    void connectDatabase();
    
    /**
     * @brief Loads transaction data from database
     * 
     * Retrieves all transactions for the current user from the
     * database and populates the transaction collection.
     */
    void loadData();
    
    /**
     * @brief Creates and initializes the financial chart
     * 
     * Sets up Qt Charts with three series (balance, income, expense)
     * and configures axes and appearance.
     */
    void createChart();
    
    /**
     * @brief Sets up balance sheet view
     * 
     * Configures the table widget to display all transactions
     * with a running balance column.
     */
    void setupBalanceSheet();
    
    /**
     * @brief Sets up category-filtered view
     * @param category The category to filter by
     * 
     * Configures the table widget to show only transactions
     * from the specified category.
     */
    void setupCategoryView(const QString& category);
    
    /**
     * @brief Formats and displays balance sheet data
     * 
     * Populates the table with all transactions and calculates
     * running balance for each row.
     */
    void formatBalanceSheet();
    
    /**
     * @brief Formats and displays category view data
     * 
     * Populates the table with filtered transactions and shows
     * total for the selected category.
     */
    void formatCategoryView();

    // Data members
    TransactionCollection<Transaction> transactions;  ///< Collection of all transactions
    
    // UI Components
    QTableWidget* tableWidget;        ///< Table displaying transaction data
    QPushButton* addIncomeButton;     ///< Button to add income transaction
    QPushButton* addExpenseButton;    ///< Button to add expense transaction
    QPushButton* viewCategoryButton;  ///< Button to filter by category
    QPushButton* resetViewButton;     ///< Button to reset to balance sheet view
    QLabel* totalLabel;               ///< Label displaying current balance or total
    QMenuBar* menuBar;                ///< Application menu bar
    QToolBar* toolBar;                ///< Application toolbar
    QStatusBar* statusBar;            ///< Application status bar
    QChartView* chartView;            ///< Widget displaying financial chart
    
    // State
    QSqlDatabase db;                  ///< SQLite database connection
    int userId;                       ///< Current user's unique identifier
    double currentBalance;            ///< User's current balance
    ViewMode currentViewMode;         ///< Current display mode
    QString currentCategory;          ///< Currently filtered category (if any)
};

#endif // PROJECT_H