#include "../include/stdafx.h"
#include "../include/project.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QHeaderView>
#include <QPalette>

Project::Project(int userId, QWidget *parent)
    : QMainWindow(parent)
    , userId(userId)
    , currentBalance(0.0)
    , tableWidget(nullptr)
    , addIncomeButton(nullptr)
    , addExpenseButton(nullptr)
    , viewCategoryButton(nullptr)
    , resetViewButton(nullptr)
    , totalLabel(nullptr)
    , menuBar(nullptr)
    , toolBar(nullptr)
    , statusBar(nullptr)
    , chartView(nullptr)
    , currentViewMode(BalanceSheet)
    , currentCategory("")
{
    setupUi();
    connectDatabase();
    loadData();
    createChart();

    connect(addIncomeButton, SIGNAL(clicked()), this, SLOT(onAddIncome()));
    connect(addExpenseButton, SIGNAL(clicked()), this, SLOT(onAddExpense()));
    connect(viewCategoryButton, SIGNAL(clicked()), this, SLOT(onViewCategory()));
    connect(resetViewButton, SIGNAL(clicked()), this, SLOT(onResetView()));
}

Project::~Project()
{
    db.close();
}

// ...existing code...

void Project::setupUi()
{
    // Set main window size for better visibility
    resize(1024, 768);
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Setup table with larger default size
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels({
        "Date", "Category", "Subcategory", "Amount", "Balance"
    });
    tableWidget->setMinimumHeight(400);  // Make table larger
    tableWidget->setAlternatingRowColors(true);  // Improve readability
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(tableWidget);

    // Create button layout for better organization
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    
    addIncomeButton = new QPushButton("Add Income", this);
    addExpenseButton = new QPushButton("Add Expense", this);
    viewCategoryButton = new QPushButton("View Category", this);
    resetViewButton = new QPushButton("Reset View", this);
    
    // Add tooltips for better UX
    addIncomeButton->setToolTip("Add a new income transaction");
    addExpenseButton->setToolTip("Add a new expense transaction");
    viewCategoryButton->setToolTip("View transactions for a specific category");
    resetViewButton->setToolTip("Reset to full transaction view");
    
    buttonLayout->addWidget(addIncomeButton);
    buttonLayout->addWidget(addExpenseButton);
    buttonLayout->addWidget(viewCategoryButton);
    buttonLayout->addWidget(resetViewButton);
    
    mainLayout->addLayout(buttonLayout);
    
    totalLabel = new QLabel(this);
    totalLabel->setAlignment(Qt::AlignRight);
    totalLabel->setStyleSheet("QLabel { font-weight: bold; }");
    mainLayout->addWidget(totalLabel);

    // ...existing menuBar, toolBar, statusBar setup...

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void Project::connectDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("budget_tracker.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        exit(-1);
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "username TEXT UNIQUE,"
               "password TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS transactions ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER,"
               "date TEXT,"
               "category TEXT,"
               "subcategory TEXT,"
               "amount REAL,"
               "balance REAL,"
               "FOREIGN KEY(user_id) REFERENCES users(id))");
}

void Project::loadData()
{
    if (currentViewMode == BalanceSheet) {
        setupBalanceSheet();
    } else {
        setupCategoryView(currentCategory);
    }
}

void Project::setupBalanceSheet()
{
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels(
        {"Date", "Category", "Subcategory", "Amount", "Balance"});
    
    QSqlQuery query;
    query.prepare("SELECT date, category, subcategory, amount, balance "
                 "FROM transactions WHERE user_id = :user_id ORDER BY date");
    query.bindValue(":user_id", userId);
    
    if (query.exec()) {
        tableWidget->setRowCount(0);
        int row = 0;
        while (query.next()) {
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            
            double amount = query.value(3).toDouble();
            QString amountStr = QString("%1%2")
                .arg(amount < 0 ? "-" : "")
                .arg(QString::number(std::abs(amount), 'f', 2));
            tableWidget->setItem(row, 3, new QTableWidgetItem(amountStr));
            
            tableWidget->setItem(row, 4, new QTableWidgetItem(
                QString::number(query.value(4).toDouble(), 'f', 2)));
            
            currentBalance = query.value(4).toDouble();
            row++;
        }
    }
    formatBalanceSheet();
    createChart();
}

void Project::setupCategoryView(const QString& category)
{
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels({"Date", "Subcategory", "Amount"});
    
    QSqlQuery query;
    query.prepare("SELECT date, subcategory, amount FROM transactions "
                 "WHERE user_id = :user_id AND category = :category ORDER BY date");
    query.bindValue(":user_id", userId);
    query.bindValue(":category", category);
    
    if (query.exec()) {
        tableWidget->setRowCount(0);
        double total = 0.0;
        int row = 0;
        
        while (query.next()) {
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            
            double amount = std::abs(query.value(2).toDouble());
            tableWidget->setItem(row, 2, new QTableWidgetItem(
                QString::number(amount, 'f', 2)));
            total += amount;
            row++;
        }
        
        totalLabel->setText(QString("%1 Total: $%2")
            .arg(category)
            .arg(total, 0, 'f', 2));
    }
    formatCategoryView();
}

void Project::onAddIncome()
{
    bool ok;
    QString category = QInputDialog::getItem(this, "Add Income", "Category:", 
        {"Salary", "Investment", "Other"}, 0, false, &ok);
    if (!ok || category.isEmpty()) return;

    QString subcategory = QInputDialog::getText(this, "Add Income", 
        "Subcategory:", QLineEdit::Normal, QString(), &ok);
    if (!ok) return;

    double amount = QInputDialog::getDouble(this, "Add Income", 
        "Amount:", 0, 0, 1000000, 2, &ok);
    if (!ok || amount == 0) return;

    QDate date = QDate::currentDate();

    Income income(amount, category, subcategory, date);
    transactions.add(income);
    currentBalance += amount;

    QSqlQuery query;
    query.prepare("INSERT INTO transactions (user_id, date, category, subcategory, amount, balance) "
        "VALUES (:user_id, :date, :category, :subcategory, :amount, :balance)");
    query.bindValue(":user_id", userId);
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":category", category);
    query.bindValue(":subcategory", subcategory);
    query.bindValue(":amount", amount);
    query.bindValue(":balance", currentBalance);
    if (query.exec()) {
        loadData();
    }
}

void Project::createChart()
{
    if (!centralWidget() || !centralWidget()->layout()) {
        return;
    }

    if (chartView) {
        delete chartView;
        chartView = nullptr;
    }

    // Create series
    QLineSeries *balanceSeries = new QLineSeries(this);
    QLineSeries *expenseSeries = new QLineSeries(this);
    QLineSeries *incomeSeries = new QLineSeries(this);

    // Style series
    QPen balancePen(QColor("#2196F3")); // Blue
    balancePen.setWidth(3);
    balanceSeries->setPen(balancePen);
    balanceSeries->setName("Balance");

    QPen expensePen(QColor("#F44336")); // Red
    expensePen.setWidth(2);
    expenseSeries->setPen(expensePen);
    expenseSeries->setName("Expenses");

    QPen incomePen(QColor("#4CAF50")); // Green
    incomePen.setWidth(2);
    incomeSeries->setPen(incomePen);
    incomeSeries->setName("Income");

    // Fetch data
    QSqlQuery query;
    query.prepare("SELECT date, amount, balance FROM transactions "
                 "WHERE user_id = :user_id ORDER BY date");
    query.bindValue(":user_id", userId);
    
    QDateTime minDate, maxDate;
    double minAmount = 0, maxAmount = 0;
    bool firstRow = true;

    if (query.exec()) {
        while (query.next()) {
            QDateTime dateTime = QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd");
            double amount = query.value(1).toDouble();
            double balance = query.value(2).toDouble();

            if (firstRow) {
                minDate = maxDate = dateTime;
                minAmount = qMin(amount, balance);
                maxAmount = qMax(amount, balance);
                firstRow = false;
            } else {
                minDate = qMin(minDate, dateTime);
                maxDate = qMax(maxDate, dateTime);
                minAmount = qMin(minAmount, qMin(amount, balance));
                maxAmount = qMax(maxAmount, qMax(amount, balance));
            }

            balanceSeries->append(dateTime.toMSecsSinceEpoch(), balance);
            if (amount > 0) {
                incomeSeries->append(dateTime.toMSecsSinceEpoch(), amount);
            } else {
                expenseSeries->append(dateTime.toMSecsSinceEpoch(), -amount);
            }
        }
    }

    // Create chart
    QChart *chart = new QChart();
    chart->addSeries(balanceSeries);
    chart->addSeries(expenseSeries);
    chart->addSeries(incomeSeries);
    chart->setTitle("Financial Overview");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Style X axis (Time)
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("MMM dd, yyyy");
    axisX->setTitleText("Date");
    axisX->setRange(minDate, maxDate.addDays(1));
    axisX->setGridLineColor(QColor("#E0E0E0"));
    chart->addAxis(axisX, Qt::AlignBottom);
    balanceSeries->attachAxis(axisX);
    expenseSeries->attachAxis(axisX);
    incomeSeries->attachAxis(axisX);

    // Style Y axis (Money)
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Amount ($)");
    axisY->setLabelFormat("$%.2f");
    axisY->setRange(minAmount * 1.1, maxAmount * 1.1); // Add 10% padding
    axisY->setGridLineColor(QColor("#E0E0E0"));
    chart->addAxis(axisY, Qt::AlignLeft);
    balanceSeries->attachAxis(axisY);
    expenseSeries->attachAxis(axisY);
    incomeSeries->attachAxis(axisY);

    // Setup chart view
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(300);
    chartView->setBackgroundBrush(QBrush(Qt::white));
    
    // Add chart to layout with margins
    QWidget* container = new QWidget(this);
    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(10, 10, 10, 10);
    containerLayout->addWidget(chartView);
    
    if (QLayout* layout = centralWidget()->layout()) {
        layout->addWidget(container);
    }
}

void Project::onViewCategory()
{
    QString category = QInputDialog::getItem(this, "Select Category",
        "Category:", {"Income", "Automobile", "Rent"}, 0, false);
    if (!category.isEmpty()) {
        currentViewMode = CategoryView;
        currentCategory = category;
        loadData();
    }
}

void Project::onResetView()
{
    currentViewMode = BalanceSheet;
    totalLabel->clear();
    loadData();
}

void Project::formatBalanceSheet()
{
    QHeaderView* header = tableWidget->horizontalHeader();
    if (header) {
        header->setSectionResizeMode(QHeaderView::ResizeToContents);
        header->setStretchLastSection(true);
        header->setStyleSheet("QHeaderView::section { padding: 6px; }");
    }
    
    // Set column widths for better readability
    tableWidget->setColumnWidth(0, 120); // Date
    tableWidget->setColumnWidth(1, 150); // Category
    tableWidget->setColumnWidth(2, 150); // Subcategory
    tableWidget->setColumnWidth(3, 100); // Amount
    tableWidget->setColumnWidth(4, 100); // Balance

    // ...existing code for amount coloring...

    // Set alternating row colors for better readability
    QPalette palette = tableWidget->palette();
    palette.setColor(QPalette::Base, QColor("#F0F0F0"));
    tableWidget->setPalette(palette);

    // Set font size for better readability
    QFont font = tableWidget->font();
    font.setPointSize(10);
    tableWidget->setFont(font);

    // Set font size for total label
    font.setPointSize(12);
    totalLabel->setFont(font);
    totalLabel->setStyleSheet("QLabel { font-weight: bold; }");
    
}

void Project::formatCategoryView()
{
    QHeaderView* header = tableWidget->horizontalHeader();
    if (header) {
        header->setSectionResizeMode(QHeaderView::ResizeToContents);
        header->setStretchLastSection(true);
    }
    tableWidget->setStyleSheet(
        "QHeaderView::section { background-color: #f0f0f0; padding: 4px; }"
        "QTableWidget { gridline-color: #d0d0d0; }"
    );
}

void Project::onAddExpense()
{
    bool ok;
    QString category = QInputDialog::getItem(this, "Add Expense", "Category:", 
        {"Automobile", "Housing", "Food", "Utilities", "Other"}, 0, false, &ok);
    if (!ok || category.isEmpty()) return;

    QString subcategory = QInputDialog::getText(this, "Add Expense", 
        "Subcategory:", QLineEdit::Normal, QString(), &ok);
    if (!ok) return;

    double amount = QInputDialog::getDouble(this, "Add Expense", 
        "Amount:", 0, 0, 1000000, 2, &ok);
    if (!ok || amount == 0) return;

    // Pass positive amount to Expense constructor, which will negate it internally
    QDate date = QDate::currentDate();
    Expense expense(amount, category, subcategory, date);
    transactions.add(expense);
    
    // Update balance with the negative amount from the expense
    currentBalance += expense.getAmount();

    QSqlQuery query;
    query.prepare("INSERT INTO transactions (user_id, date, category, subcategory, amount, balance) "
                  "VALUES (:user_id, :date, :category, :subcategory, :amount, :balance)");
    query.bindValue(":user_id", userId);
    query.bindValue(":date", date.toString("yyyy-MM-dd")); // Correct bindValue usage
    query.bindValue(":category", category);
    query.bindValue(":subcategory", subcategory);
    query.bindValue(":amount", amount);
    query.bindValue(":balance", currentBalance);
    if (query.exec()) {
        loadData();
    }
}