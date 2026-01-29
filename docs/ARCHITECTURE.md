# Architecture Documentation

## Overview

The Budget Tracker Application is built using the Qt framework in C++ and follows object-oriented design principles. The application uses a modular architecture that separates concerns between user interface, business logic, and data persistence.

## Project Structure

```
QT-Expense-Application/
├── src/                    # Source files
│   ├── main.cpp           # Application entry point
│   ├── login.cpp          # Login/registration logic
│   ├── project.cpp        # Main application logic
│   └── stdafx.cpp         # Precompiled headers
├── include/               # Header files
│   ├── login.h            # Login class declaration
│   ├── project.h          # Project class declaration
│   ├── stdafx.h           # Standard includes
│   ├── transaction.h      # Transaction classes
│   └── transaction_collection.h  # Transaction container
├── resources/             # Resource files
│   └── project.qrc        # Qt resource file
├── build/                 # Build configuration
│   ├── Project.vcxproj    # Visual Studio project
│   ├── Project.vcxproj.filters
│   └── Project.rc         # Resource script
├── docs/                  # Documentation
└── README.md              # Project overview
```

## Core Components

### 1. Application Entry Point (`main.cpp`)

**Responsibilities:**
- Initialize Qt application
- Set up SQLite database connection
- Create database tables if they don't exist
- Show login dialog
- Launch main application window upon successful authentication

**Key Functions:**
```cpp
int main(int argc, char *argv[])
```

**Flow:**
1. Create QApplication instance
2. Initialize database connection
3. Create users table
4. Display login dialog
5. If login successful, show main window
6. Enter Qt event loop

### 2. Login Module (`login.h`, `login.cpp`)

**Class:** `Login`

**Responsibilities:**
- Handle user authentication
- Manage user registration
- Validate credentials against database
- Store authenticated user ID

**Key Methods:**
- `Login(QWidget* parent)` - Constructor, sets up UI
- `getUserId()` - Returns the authenticated user's ID
- `onLoginButtonClicked()` - Validates credentials
- `onRegisterButtonClicked()` - Creates new user account

**Database Interaction:**
- Queries users table for authentication
- Inserts new users during registration
- Uses prepared statements to prevent SQL injection

### 3. Main Application (`project.h`, `project.cpp`)

**Class:** `Project` (inherits from `QMainWindow`)

**Responsibilities:**
- Display main user interface
- Manage transaction data
- Handle user interactions (add income/expense, view categories)
- Generate financial charts
- Persist data to database

**Key Methods:**
- `Project(int userId, QWidget *parent)` - Constructor
- `setupUi()` - Constructs the user interface
- `connectDatabase()` - Establishes database connection
- `loadData()` - Loads user transactions from database
- `createChart()` - Generates financial visualization
- `onAddIncome()` - Slot for adding income transactions
- `onAddExpense()` - Slot for adding expense transactions
- `onViewCategory()` - Slot for filtering by category
- `onResetView()` - Slot for resetting to balance sheet view

**View Modes:**
- **BalanceSheet**: Shows all transactions with running balance
- **CategoryView**: Shows filtered transactions for a specific category

**UI Components:**
- `tableWidget` - Displays transaction data
- `chartView` - Shows financial trends
- Action buttons (Add Income, Add Expense, View Category, Reset)
- Status label showing totals

### 4. Transaction Module (`transaction.h`)

**Abstract Base Class:** `Transaction`

**Responsibilities:**
- Define common interface for all transactions
- Store transaction data (amount, category, subcategory, date)

**Derived Classes:**

**`Income`**
- Represents positive cash flow
- Stores amount as positive value

**`Expense`**
- Represents negative cash flow
- Stores amount as negative value (automatically negated)

**Key Methods:**
- `getAmount()` - Returns transaction amount
- `getCategory()` - Returns category name
- `getSubcategory()` - Returns subcategory name
- `getDate()` - Returns transaction date
- `clone()` - Creates a copy of the transaction

### 5. Transaction Collection (`transaction_collection.h`)

**Template Class:** `TransactionCollection<T>`

**Responsibilities:**
- Manage a collection of transactions
- Provide utility methods for transaction data

**Key Methods:**
- `add(const T& transaction)` - Adds a transaction to the collection
- `getTotalAmount()` - Calculates sum of all transactions
- `getByCategory(const QString& category)` - Filters transactions by category

**Implementation Details:**
- Uses `std::vector` with `std::unique_ptr` for memory management
- Stores cloned transactions to ensure data independence
- Template-based for flexibility

## Data Flow

### Adding a Transaction

```
User clicks "Add Income" or "Add Expense"
    ↓
Dialog prompts for category, subcategory, amount
    ↓
User confirms
    ↓
Transaction object created (Income or Expense)
    ↓
Transaction added to database
    ↓
Transaction added to local collection
    ↓
UI updates (table and chart refresh)
    ↓
Balance recalculated and displayed
```

### Viewing by Category

```
User clicks "View Category"
    ↓
Dialog shows list of available categories
    ↓
User selects category
    ↓
Transactions filtered by category
    ↓
Table displays only matching transactions
    ↓
Total calculated for selected category
    ↓
Chart updates to show category data
```

## Database Schema

### Users Table

```sql
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL
)
```

**Fields:**
- `id`: Unique identifier for each user
- `username`: Unique username for login
- `password`: User password (stored as plain text - should be hashed in production)

### Transactions Table

```sql
CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    date TEXT NOT NULL,
    category TEXT NOT NULL,
    subcategory TEXT,
    amount REAL NOT NULL,
    balance REAL NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(id)
)
```

**Fields:**
- `id`: Unique transaction identifier
- `user_id`: Reference to the user who owns this transaction
- `date`: Transaction date (stored as text in ISO format)
- `category`: Main category (e.g., "Salary", "Housing")
- `subcategory`: Optional subcategory for detailed tracking
- `amount`: Transaction amount (positive for income, negative for expenses)
- `balance`: Running balance after this transaction

## Design Patterns

### 1. Template Method Pattern
- Used in `Transaction` base class with virtual methods
- Derived classes (`Income`, `Expense`) implement specific behavior

### 2. Factory Pattern
- Transaction objects are created based on user selection (Income vs Expense)

### 3. Observer Pattern
- Qt's signal-slot mechanism connects UI events to business logic
- Example: Button clicks trigger slots that update data and UI

### 4. Template Pattern
- `TransactionCollection<T>` uses templates for type-safe collection management

## Qt Framework Usage

### Qt Modules Used

1. **Qt Core** - Basic Qt functionality
2. **Qt Widgets** - UI components (buttons, tables, dialogs)
3. **Qt SQL** - Database connectivity (SQLite)
4. **Qt Charts** - Data visualization (line charts)

### Key Qt Features

- **Signals and Slots**: Event handling mechanism
- **QMainWindow**: Main application window framework
- **QTableWidget**: Spreadsheet-like data display
- **QDialog**: Modal dialogs for user input
- **QSqlDatabase/QSqlQuery**: Database access
- **QChart/QLineSeries**: Chart creation and data series

## Memory Management

- **Smart Pointers**: `std::unique_ptr` used in `TransactionCollection`
- **Qt Parent-Child**: Qt's object tree manages widget lifecycle
- **Manual Deletion**: Some objects deleted explicitly in destructors
- **RAII**: Resource Acquisition Is Initialization for database connections

## Thread Safety

Currently, the application is **single-threaded**:
- All operations run on the main GUI thread
- Database operations are synchronous
- No explicit thread synchronization required

For future multi-threading:
- Consider `QThread` for background operations
- Use `QMutex` for shared data protection
- Emit signals from worker threads to update UI

## Error Handling

- **Database Errors**: Displayed via `QMessageBox::critical()`
- **User Input Validation**: Checked before processing
- **SQL Errors**: Captured with `QSqlError` and displayed to user
- **Exception Safety**: Most Qt operations don't throw exceptions

## Performance Considerations

- **Database Queries**: Uses prepared statements for efficiency
- **UI Updates**: Table and chart refreshed after data changes
- **Memory Usage**: Transactions stored in memory for quick access
- **Lazy Loading**: Could be implemented for large datasets

## Security Considerations

### Current State
- ⚠️ Passwords stored as **plain text** (not secure)
- ⚠️ No session management
- ⚠️ Database file not encrypted

### Recommendations for Production
- ✅ Hash passwords with bcrypt or Argon2
- ✅ Implement session timeout
- ✅ Encrypt database file
- ✅ Use parameterized queries (already done)
- ✅ Add input validation and sanitization
- ✅ Implement proper authentication tokens

## Future Architecture Improvements

1. **Separation of Concerns**
   - Create a dedicated data access layer
   - Implement service layer for business logic
   - Separate UI logic from business logic

2. **Model-View Architecture**
   - Use Qt's Model/View framework
   - Implement custom models for transactions
   - Better separation of data and presentation

3. **Configuration Management**
   - Externalize database connection settings
   - Add application configuration file
   - Support for multiple database backends

4. **Dependency Injection**
   - Reduce tight coupling between components
   - Make components more testable

5. **Event-Driven Architecture**
   - Implement event bus for component communication
   - Decouple components further

## Testing Strategy

### Unit Testing
- Test transaction calculations
- Test database queries
- Test data validation logic

### Integration Testing
- Test database integration
- Test UI component interactions
- Test data flow between modules

### Tools
- Qt Test framework
- Google Test (alternative)
- Mock databases for testing

## Build System

- **Visual Studio Project**: `.vcxproj` files
- **Qt Integration**: Qt VS Tools
- **Compiler**: MSVC (Microsoft Visual C++)
- **Qt Version**: 6.8.1
- **Platform**: Windows (x64)

### Build Process
1. Qt MOC (Meta-Object Compiler) processes headers
2. UI files compiled to C++ headers
3. Resources compiled into binary
4. C++ compilation
5. Linking with Qt libraries

## Deployment

### Requirements
- Qt runtime libraries (Core, Widgets, SQL, Charts)
- Visual C++ Redistributables
- SQLite (included with Qt SQL)

### Distribution
- Use Qt's deployment tool (`windeployqt`)
- Include all required Qt DLLs
- Package as installer or portable application

---

For more information on specific components, refer to the inline code documentation.
