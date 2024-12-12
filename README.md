# Budget Tracker Application

## Introduction

The **Budget Tracker Application** is a desktop software developed using the Qt framework in C++. It aims to provide users with an intuitive and efficient way to manage their personal finances. The application allows users to track their incomes and expenses, categorize transactions, view financial summaries, and visualize their financial data through charts.

---

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
  - [User Authentication](#user-authentication)
  - [Transaction Management](#transaction-management)
  - [Financial Overview](#financial-overview)
  - [Category Filtering](#category-filtering)
  - [Data Visualization](#data-visualization)
- [Architecture](#architecture)
  - [Project Structure](#project-structure)
  - [Class Descriptions](#class-descriptions)
- [Database Schema](#database-schema)
- [User Interface](#user-interface)
  - [Login Window](#login-window)
  - [Main Window](#main-window)
- [Setup and Installation](#setup-and-installation)
  - [Prerequisites](#prerequisites)
  - [Building the Project](#building-the-project)
- [Usage Guide](#usage-guide)
  - [Logging In and Registration](#logging-in-and-registration)
  - [Adding Transactions](#adding-transactions)
  - [Viewing Transactions](#viewing-transactions)
  - [Visualizing Data](#visualizing-data)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)
- [Contact Information](#contact-information)

---

## Features

### User Authentication

- Secure login system with username and password.
- Registration functionality for new users.
- Each user has a unique identifier to manage their personal data.

### Transaction Management

- Add **Income** and **Expense** transactions with details like amount, category, subcategory, and date.
- Transactions are categorized to help users track spending habits.
- Supports custom categories and subcategories.

### Financial Overview

- Displays all transactions in a balance sheet format.
- Shows real-time calculation of current balance.
- Provides detailed information for each transaction.

### Category Filtering

- View transactions by specific categories.
- Helps in analyzing expenses or incomes in particular areas.
- Displays total amounts for selected categories.

### Data Visualization

- Integrates Qt Charts to display financial data graphically.
- Line charts show income, expenses, and balance over time.
- Enhances understanding of financial trends.

---

## Architecture

### Project Structure

The application is organized into several key components:

- **Main Application**: Initializes the application and handles user sessions.
- **Login Module**: Manages user authentication.
- **Transaction Module**: Handles transaction data and logic.
- **Database Module**: Interacts with the SQLite database.
- **User Interface**: Constructs the GUI using Qt Widgets.

### Class Descriptions

- **`Project`**: Inherits from `QMainWindow`. It is the core class that ties together the UI and backend logic.
- **`Transaction`**: An abstract base class representing a financial transaction.
  - **`Income`**: Derived from `Transaction`, represents income entries.
  - **`Expense`**: Derived from `Transaction`, represents expense entries.
- **`TransactionCollection`**: Template class managing collections of transactions.
- **`Login`**: Manages the login and registration dialogs and processes.

---

## Database Schema

The application uses SQLite for data persistence with the following tables:

### `users` Table

- **`id`**: Primary key (INTEGER).
- **`username`**: Unique username (TEXT).
- **`password`**: User's password (TEXT).

### `transactions` Table

- **`id`**: Primary key (INTEGER).
- **`user_id`**: Foreign key referencing `users.id` (INTEGER).
- **`date`**: Date of transaction (TEXT).
- **`category`**: Transaction category (TEXT).
- **`subcategory`**: Transaction subcategory (TEXT).
- **`amount`**: Transaction amount (REAL).
- **`balance`**: User's balance after transaction (REAL).

---

## User Interface

### Login Window

- **Username and Password Fields**: Inputs for user credentials.
- **Login Button**: Validates credentials and logs in the user.
- **Register Button**: Creates a new user account.

### Main Window

- **Transaction Table**: Displays a list of transactions with details.
- **Buttons**:
  - **Add Income**: Opens dialog to add an income transaction.
  - **Add Expense**: Opens dialog to add an expense transaction.
  - **View Category**: Filters transactions by category.
  - **Reset View**: Resets filters to show all transactions.
- **Total Label**: Shows the current balance or category totals.
- **Chart Area**: Displays financial data in a line chart.

---

## Setup and Installation

### Prerequisites

- **Qt Framework**: Version 5 or later with Widgets, SQL, and Charts modules.
- **C++ Compiler**: Compatible with C++11 standard or higher.
- **SQLite**: Integrated with Qt SQL module.

### Building the Project

1. **Clone the Repository**: Download the project files to your local machine.

2. **Open the Project**: Use Qt Creator or another IDE that supports Qt projects.

3. **Configure Build Settings**:

   - Ensure all necessary Qt modules are included.
   - Set the correct compiler and Qt version.

4. **Build the Project**:

   - Run the build process from your IDE.
   - Resolve any dependencies or errors if they arise.

5. **Run the Application**:
   - Execute the compiled binary.
   - The Login window should appear upon successful build.

---

## Usage Guide

### Logging In and Registration

- **New Users**:
  - Enter a unique username and password.
  - Click "Register" to create a new account.
- **Existing Users**:
  - Enter your username and password.
  - Click "Login" to access your account.
- **Error Handling**:
  - The application will prompt you if credentials are incorrect or if the username already exists.

### Adding Transactions

- **Add Income**:
  - Click the "Add Income" button.
  - Select a category (e.g., Salary, Investment).
  - Enter a subcategory and amount.
  - The transaction is saved, and the balance updates.
- **Add Expense**:
  - Click the "Add Expense" button.
  - Select a category (e.g., Housing, Food).
  - Enter a subcategory and amount.
  - The transaction is saved with a negative amount, and the balance updates.

### Viewing Transactions

- **Balance Sheet View**:
  - Displays all transactions in order.
  - Columns include Date, Category, Subcategory, Amount, and Balance.
- **Category View**:
  - Click "View Category" and select a category.
  - Shows transactions only from that category.
  - Displays the total amount for the selected category.
- **Reset View**:
  - Click "Reset View" to return to the Balance Sheet view.

### Visualizing Data

- The application displays a chart at the bottom of the main window.
- **Chart Features**:
  - **Balance Series**: Blue line showing the balance over time.
  - **Income Series**: Green line for income transactions.
  - **Expense Series**: Red line for expense transactions.
- **Interactivity**:
  - Hover over data points to see exact values.
  - Chart automatically updates when new transactions are added.

---

## Future Enhancements

- **Password Encryption**: Implement hashing to securely store passwords.
- **Transaction Editing**: Allow users to modify or delete transactions.
- **Advanced Filtering**: Enable filtering by date ranges or subcategories.
- **Reporting**: Generate and export financial reports.
- **Mobile Version**: Develop a mobile app using Qt's cross-platform capabilities.
- **Synchronization**: Sync data across devices using cloud services.
- **Multi-Currency Support**: Handle transactions in different currencies.
- **Budgeting Tools**: Set budgets for categories and track adherence.

---

## Contributing

If you're interested in contributing to the project:

1. **Fork the Repository**: Create your own copy on GitHub.

2. **Create a Branch**: Work on your feature or bugfix in a new branch.

3. **Commit Your Changes**: Write clear and descriptive commit messages.

4. **Push to GitHub**: Push your branch to your forked repository.

5. **Submit a Pull Request**: Explain your changes and submit a PR to the original repository.

---

## License

This project is released under the **MIT License**. You are free to use, modify, and distribute this software as per the license terms.

---

## Contact Information

For any questions, suggestions, or collaboration requests:

- **Developer**: _Your Name_
- **Email**: *your.email@example.com*
- **LinkedIn**: [Your LinkedIn Profile](https://www.linkedin.com/in/yourprofile)
- **GitHub**: [Your GitHub Profile](https://github.com/yourusername)

Feel free to reach out!
