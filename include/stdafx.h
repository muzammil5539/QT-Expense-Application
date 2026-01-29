#pragma once

/**
 * @file stdafx.h
 * @brief Precompiled header file for the Budget Tracker Application
 * 
 * This file includes all frequently used Qt headers to speed up compilation.
 * It is compiled once and reused across all source files that include it.
 * 
 * Precompiled headers are particularly useful for large frameworks like Qt
 * where many headers are included in multiple files.
 */

// ========================================================================
// Qt Core Module
// ========================================================================
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

// ========================================================================
// Qt SQL Module
// ========================================================================
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

// ========================================================================
// Qt Charts Module
// ========================================================================
// Using fully qualified names to avoid namespace conflicts
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

// ========================================================================
// Other Qt Includes
// ========================================================================
#include <QtCore/QDateTime>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>

// ========================================================================
// Forward Declarations
// ========================================================================
// Forward declare Qt Charts classes to avoid unnecessary includes
QT_BEGIN_NAMESPACE
namespace QtCharts {
    class QChartView;
    class QChart;
    class QLineSeries;
    class QDateTimeAxis;
    class QValueAxis;
}
QT_END_NAMESPACE

// Note: Avoid using namespace declarations in headers
// This prevents namespace pollution in files that include this header
// Instead, use fully qualified names (e.g., QtCharts::QChart)