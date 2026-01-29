# Budget Tracker Application

<div align="center">

![Qt](https://img.shields.io/badge/Qt-6.8.1-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![C++](https://img.shields.io/badge/C++-11-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SQLite](https://img.shields.io/badge/SQLite-3-003B57?style=for-the-badge&logo=sqlite&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

**A powerful and intuitive desktop application for managing personal finances**

[Features](#features) • [Installation](#setup-and-installation) • [Usage](#usage-guide) • [Documentation](#documentation) • [Contributing](#contributing)

</div>

---

## Introduction

The **Budget Tracker Application** is a desktop software developed using the Qt framework in C++. It aims to provide users with an intuitive and efficient way to manage their personal finances. The application allows users to track their incomes and expenses, categorize transactions, view financial summaries, and visualize their financial data through charts.

---

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Screenshots](#screenshots)
- [Project Structure](#project-structure)
- [Architecture](#architecture)
- [Setup and Installation](#setup-and-installation)
- [Usage Guide](#usage-guide)
- [Documentation](#documentation)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

---

## Features

### 🔐 User Authentication
- Secure login system with username and password
- Quick registration for new users
- Individual user accounts with unique identifiers
- Session management for personalized data

### 💰 Transaction Management
- **Add Income**: Record earnings with categories and details
- **Add Expense**: Track spending across multiple categories
- Custom categories and subcategories for detailed organization
- Date tracking for all transactions
- Automatic balance calculation

### 📊 Financial Overview
- Comprehensive balance sheet displaying all transactions
- Real-time balance updates
- Chronological transaction history
- Detailed information for each entry (date, category, amount, balance)

### 🔍 Category Filtering
- Filter transactions by specific categories
- View totals for individual categories
- Analyze spending patterns by category
- Quick reset to view all transactions

### 📈 Data Visualization
- Interactive line charts powered by Qt Charts
- Visual representation of financial trends
- Three data series:
  - 💙 **Balance**: Track your overall financial position
  - 💚 **Income**: Monitor earnings over time
  - ❤️ **Expenses**: Visualize spending patterns
- Hover over data points for detailed information
- Automatic chart updates with new transactions

---

## Screenshots

> **Note**: Screenshots coming soon! The application features a clean, modern interface built with Qt Widgets.

### Login Window
- Clean and simple authentication interface
- Easy registration for new users

### Main Window
- Intuitive layout with clear action buttons
- Comprehensive transaction table
- Interactive financial charts
- Real-time balance display

---

## Project Structure

```
QT-Expense-Application/
├── src/                          # Source files (.cpp)
│   ├── main.cpp                 # Application entry point
│   ├── login.cpp                # Login and registration logic
│   ├── project.cpp              # Main application logic
│   └── stdafx.cpp               # Precompiled headers
├── include/                      # Header files (.h)
│   ├── login.h                  # Login class declaration
│   ├── project.h                # Main window class
│   ├── transaction.h            # Transaction base classes
│   ├── transaction_collection.h # Transaction container
│   └── stdafx.h                 # Standard includes
├── resources/                    # Resource files
│   └── project.qrc              # Qt resource collection
├── build/                        # Build configuration
│   ├── Project.vcxproj          # Visual Studio project
│   └── Project.vcxproj.filters  # VS filters
├── docs/                         # Documentation
│   ├── ARCHITECTURE.md          # Technical architecture
│   └── SETUP.md                 # Detailed setup guide
├── README.md                     # This file
├── CONTRIBUTING.md              # Contribution guidelines
├── CODE_OF_CONDUCT.md           # Code of conduct
├── CHANGELOG.md                 # Version history
├── LICENSE                       # MIT License
└── .gitignore                   # Git ignore rules
```

---

## Architecture

### Project Architecture Overview

The application follows a modular, object-oriented design:

- **Main Application**: Entry point that initializes the application and manages user sessions
- **Login Module**: Handles user authentication and registration
- **Transaction Module**: Core business logic for financial transactions
- **Database Module**: SQLite integration for data persistence
- **User Interface**: Qt Widgets-based GUI components
- **Visualization**: Qt Charts integration for data representation

### Key Classes

**`Project`**
- Inherits from `QMainWindow`
- Core class integrating UI and backend logic
- Manages the main application window and user interactions

**`Transaction`** (Abstract Base Class)
- Represents a financial transaction
- Defines common interface for all transaction types

**`Income` / `Expense`**
- Derived from `Transaction`
- Represent positive and negative cash flows respectively

**`TransactionCollection<T>`**
- Template class for managing transaction collections
- Provides filtering and aggregation functionality

**`Login`**
- Manages authentication dialogs
- Handles user login and registration

For detailed architecture information, see [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md).

---

## Database Schema

The application uses **SQLite** for lightweight, embedded data persistence.

### `users` Table

| Column   | Type    | Description                    |
|----------|---------|--------------------------------|
| id       | INTEGER | Primary key (auto-increment)   |
| username | TEXT    | Unique username for login      |
| password | TEXT    | User password                  |

### `transactions` Table

| Column      | Type    | Description                           |
|-------------|---------|---------------------------------------|
| id          | INTEGER | Primary key (auto-increment)          |
| user_id     | INTEGER | Foreign key to users.id               |
| date        | TEXT    | Transaction date (ISO format)         |
| category    | TEXT    | Transaction category                  |
| subcategory | TEXT    | Transaction subcategory (optional)    |
| amount      | REAL    | Transaction amount (+/-)              |
| balance     | REAL    | Running balance after transaction     |

---

## Setup and Installation

### Quick Start

1. **Prerequisites**
   - Qt Framework 6.x (6.8.1 recommended) or Qt 5.15+
   - C++ Compiler (MSVC, GCC, or Clang)
   - SQLite (included with Qt SQL module)

2. **Clone the Repository**
   ```bash
   git clone https://github.com/muzammil5539/QT-Expense-Application.git
   cd QT-Expense-Application
   ```

3. **Build the Project**
   
   **Using Visual Studio:**
   - Open `build/Project.vcxproj`
   - Configure Qt paths in Qt VS Tools
   - Build → Build Solution

   **Using Qt Creator:**
   - Open `build/Project.vcxproj` or create a `.pro` file
   - Configure the kit
   - Build → Build All

4. **Run**
   - Execute the compiled binary
   - Register a new user
   - Start tracking your finances!

For detailed installation instructions, see [docs/SETUP.md](docs/SETUP.md).

### System Requirements

- **OS**: Windows 10/11, Linux (Ubuntu 20.04+), or macOS 10.15+
- **RAM**: 4 GB minimum (8 GB recommended)
- **Disk Space**: ~100 MB for application
- **Display**: 1024x768 minimum resolution

---

## Usage Guide

### Getting Started

1. **Launch the Application**
   - Run the executable
   - The login window will appear

2. **Create an Account**
   - Enter a unique username
   - Set a secure password
   - Click **Register**

3. **Login**
   - Enter your credentials
   - Click **Login** to access your dashboard

### Managing Transactions

#### Adding Income

1. Click the **"Add Income"** button
2. Select a category from the dropdown:
   - Salary
   - Investment
   - Business
   - Freelance
   - Other
3. Enter a subcategory (optional, e.g., "Monthly Salary")
4. Enter the amount
5. Click **OK** to save

The transaction is immediately added to your balance sheet and chart.

#### Adding Expenses

1. Click the **"Add Expense"** button
2. Choose a category:
   - Housing (rent, mortgage, utilities)
   - Food (groceries, dining out)
   - Transportation (gas, public transit)
   - Healthcare
   - Entertainment
   - Other
3. Enter a subcategory for more detail
4. Enter the amount
5. Click **OK**

Your balance updates automatically, and the expense appears in the table.

### Viewing Transactions

**Balance Sheet View** (Default)
- Shows all transactions chronologically
- Displays running balance after each transaction
- Columns: Date | Category | Subcategory | Amount | Balance

**Category View**
- Click **"View Category"**
- Select a category from the list
- See only transactions for that category
- View total amount for the category

**Reset View**
- Click **"Reset View"** to return to Balance Sheet
- Shows all transactions again

### Understanding the Chart

The chart at the bottom displays three lines:

- **Blue Line (Balance)**: Your current financial position over time
- **Green Line (Income)**: Income transactions plotted by date
- **Red Line (Expenses)**: Expense transactions plotted by date

Hover over any point to see exact values and dates.

---

## Documentation

Comprehensive documentation is available in the `docs/` directory:

- **[ARCHITECTURE.md](docs/ARCHITECTURE.md)**: Detailed technical architecture, design patterns, and code structure
- **[SETUP.md](docs/SETUP.md)**: Complete setup and installation guide for all platforms
- **[CONTRIBUTING.md](CONTRIBUTING.md)**: Guidelines for contributing to the project
- **[CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)**: Community standards and behavior expectations
- **[CHANGELOG.md](CHANGELOG.md)**: Version history and release notes

---

## Future Enhancements

Planned features and improvements:

### Security & Authentication
- 🔐 **Password Encryption**: Implement bcrypt/Argon2 for secure password storage
- 🔑 **Two-Factor Authentication**: Add 2FA for enhanced security
- 🛡️ **Database Encryption**: Encrypt SQLite database file

### Features
- ✏️ **Transaction Editing**: Modify or delete existing transactions
- 📅 **Date Range Filtering**: Filter transactions by custom date ranges
- 📤 **Export Functionality**: Export data to CSV, Excel, or PDF
- 📊 **Advanced Reports**: Generate monthly/yearly financial reports
- 💵 **Multi-Currency Support**: Handle transactions in different currencies
- 🎯 **Budget Planning**: Set budgets for categories and track adherence
- 📱 **Recurring Transactions**: Set up automatic recurring entries
- 🏷️ **Tags and Notes**: Add custom tags and notes to transactions

### User Experience
- 🌙 **Dark Mode**: Add dark theme option
- 🌍 **Internationalization**: Support for multiple languages
- 📲 **Mobile Version**: Develop mobile app using Qt for Android/iOS
- ☁️ **Cloud Sync**: Synchronize data across multiple devices
- 🔔 **Notifications**: Reminders for recurring transactions or budget limits

### Technical Improvements
- ⚡ **Performance**: Optimize for large datasets with lazy loading
- 🧪 **Testing**: Implement comprehensive unit and integration tests
- 📊 **Analytics**: Add advanced analytics dashboard
- 🔌 **API**: Create REST API for third-party integrations

---

## Contributing

Contributions are welcome and appreciated! Here's how you can help:

1. **🍴 Fork the Repository**
   - Create your own fork on GitHub

2. **🌿 Create a Feature Branch**
   ```bash
   git checkout -b feature/AmazingFeature
   ```

3. **✍️ Make Your Changes**
   - Follow the coding style guidelines
   - Write clear, commented code
   - Update documentation as needed

4. **✅ Test Your Changes**
   - Ensure the application builds successfully
   - Test all affected functionality

5. **💾 Commit Your Changes**
   ```bash
   git commit -m "Add some AmazingFeature"
   ```

6. **📤 Push to Your Fork**
   ```bash
   git push origin feature/AmazingFeature
   ```

7. **🔁 Open a Pull Request**
   - Provide a clear description of your changes
   - Reference any related issues

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for detailed guidelines, coding standards, and the code of conduct.

---

## License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

```
MIT License - Copyright (c) 2024 Muzammil Nawaz Khan
```

You are free to:
- ✅ Use commercially
- ✅ Modify
- ✅ Distribute
- ✅ Sublicense
- ✅ Private use

---

## Contact

**Muzammil Nawaz Khan**

- 📧 Email: [mnk.7muzammil86@gmail.com](mailto:mnk.7muzammil86@gmail.com)
- 💼 LinkedIn: [Muzammil Nawaz Khan](https://www.linkedin.com/in/mnk539)
- 🐙 GitHub: [@muzammil5539](https://github.com/muzammil5539)

### Support

- 🐛 Found a bug? [Open an issue](https://github.com/muzammil5539/QT-Expense-Application/issues)
- 💡 Have a feature request? [Start a discussion](https://github.com/muzammil5539/QT-Expense-Application/discussions)
- 📧 Need help? Email me or open an issue

---

## Acknowledgments

- Built with [Qt Framework](https://www.qt.io/)
- Database powered by [SQLite](https://www.sqlite.org/)
- Charts by [Qt Charts](https://doc.qt.io/qt-6/qtcharts-index.html)
- Inspired by the need for simple, effective personal finance management

---

<div align="center">

**⭐ Star this repository if you find it helpful!**

Made with ❤️ by [Muzammil Nawaz Khan](https://github.com/muzammil5539)

</div>
