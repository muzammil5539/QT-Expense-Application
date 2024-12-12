#pragma once

// Qt Core
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHeaderView>

// Qt SQL
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

// Qt Charts - using fully qualified names
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

// Other Qt includes
#include <QtCore/QDateTime>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>

// Forward declare Qt Charts classes
QT_BEGIN_NAMESPACE
namespace QtCharts {
    class QChartView;
    class QChart;
    class QLineSeries;
    class QDateTimeAxis;
    class QValueAxis;
}
QT_END_NAMESPACE

// Remove the using declarations
// using QtCharts::QChartView;
// using QtCharts::QChart;
// using QtCharts::QLineSeries;
// using QtCharts::QDateTimeAxis;
// using QtCharts::QValueAxis;