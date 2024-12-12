#ifndef PROJECT_H
#define PROJECT_H

#include "stdafx.h"
#include "transaction.h"
#include "transaction_collection.h"

class Project : public QMainWindow {
    Q_OBJECT

public:
    explicit Project(int userId, QWidget *parent = nullptr);
    ~Project();

private slots:
    void onAddIncome();
    void onAddExpense();
    void onViewCategory();
    void onResetView();

private:
    // View modes enum
    enum ViewMode {
        BalanceSheet,
        CategoryView
    };

    void setupUi();
    void connectDatabase();
    void loadData();
    void createChart();
    void setupBalanceSheet();
    void setupCategoryView(const QString& category);
    void formatBalanceSheet();
    void formatCategoryView();

    TransactionCollection<Transaction> transactions;
    QTableWidget* tableWidget;
    QPushButton* addIncomeButton;
    QPushButton* addExpenseButton;
    QPushButton* viewCategoryButton;
    QPushButton* resetViewButton;
    QLabel* totalLabel;
    QMenuBar* menuBar;
    QToolBar* toolBar;
    QStatusBar* statusBar;
    QChartView* chartView;
    QSqlDatabase db;
    int userId;
    double currentBalance;
    ViewMode currentViewMode;
    QString currentCategory;
};

#endif // PROJECT_H