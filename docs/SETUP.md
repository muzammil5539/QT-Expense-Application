# Setup and Installation Guide

This guide provides detailed instructions for setting up and building the Budget Tracker Application on your development machine.

## Table of Contents

- [System Requirements](#system-requirements)
- [Prerequisites](#prerequisites)
- [Installation Steps](#installation-steps)
  - [Windows Setup](#windows-setup)
  - [Linux Setup](#linux-setup)
  - [macOS Setup](#macos-setup)
- [Building the Project](#building-the-project)
  - [Using Visual Studio](#using-visual-studio)
  - [Using Qt Creator](#using-qt-creator)
  - [Using Command Line](#using-command-line)
- [Running the Application](#running-the-application)
- [Troubleshooting](#troubleshooting)
- [Development Tools](#development-tools)

## System Requirements

### Minimum Requirements
- **OS**: Windows 10/11, Linux (Ubuntu 20.04+), or macOS 10.15+
- **RAM**: 4 GB minimum, 8 GB recommended
- **Disk Space**: 2 GB for Qt installation, 100 MB for project
- **Display**: 1024x768 resolution minimum

### Recommended Requirements
- **OS**: Windows 11 or latest Linux distribution
- **RAM**: 16 GB
- **CPU**: Multi-core processor
- **Disk Space**: 10 GB for development tools
- **Display**: 1920x1080 resolution

## Prerequisites

### 1. Qt Framework

The application requires Qt 5.15 or later (Qt 6.x recommended).

**Download Qt:**
- Visit [Qt Official Website](https://www.qt.io/download)
- Download the open-source version or use online installer
- Select the following components during installation:
  - Qt 6.8.1 (or latest 6.x version)
  - Qt Charts
  - Qt SQL (SQLite driver)
  - Developer and Designer Tools

**Required Qt Modules:**
- Qt Core
- Qt Widgets
- Qt SQL
- Qt Charts

### 2. C++ Compiler

**Windows:**
- Microsoft Visual C++ 2019 or later (MSVC)
- Install Visual Studio Community Edition (free)
- Select "Desktop development with C++" workload

**Linux:**
- GCC 7.0+ or Clang 6.0+
```bash
sudo apt-get update
sudo apt-get install build-essential g++ gcc
```

**macOS:**
- Xcode Command Line Tools
```bash
xcode-select --install
```

### 3. SQLite (Optional)

SQLite is included with Qt SQL module, so no separate installation is required. However, if you want to inspect the database:

**Windows:**
- Download from [sqlite.org](https://www.sqlite.org/download.html)
- Extract and add to PATH

**Linux:**
```bash
sudo apt-get install sqlite3
```

**macOS:**
```bash
brew install sqlite3
```

## Installation Steps

### Windows Setup

1. **Install Visual Studio 2022 Community Edition**
   ```
   - Download from: https://visualstudio.microsoft.com/
   - Select "Desktop development with C++"
   - Install Qt VS Tools extension (optional but recommended)
   ```

2. **Install Qt Framework**
   ```
   - Run Qt Online Installer
   - Select Qt 6.8.1 for MSVC 2022 64-bit
   - Check Qt Charts, Qt SQL components
   - Note the installation path (e.g., C:\Qt\6.8.1\msvc2022_64)
   ```

3. **Configure Environment Variables**
   ```
   - Add Qt bin directory to PATH:
     C:\Qt\6.8.1\msvc2022_64\bin
   - Add Qt plugins:
     C:\Qt\6.8.1\msvc2022_64\plugins
   ```

4. **Clone the Repository**
   ```bash
   git clone https://github.com/muzammil5539/QT-Expense-Application.git
   cd QT-Expense-Application
   ```

### Linux Setup

1. **Install Required Packages**
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential
   sudo apt-get install qt6-base-dev qt6-charts-dev
   sudo apt-get install libqt6sql6-sqlite
   ```

2. **Install Qt Creator (Optional)**
   ```bash
   sudo apt-get install qtcreator
   ```

3. **Clone the Repository**
   ```bash
   git clone https://github.com/muzammil5539/QT-Expense-Application.git
   cd QT-Expense-Application
   ```

### macOS Setup

1. **Install Xcode and Command Line Tools**
   ```bash
   xcode-select --install
   ```

2. **Install Qt using Homebrew**
   ```bash
   brew install qt@6
   brew install qt-creator
   ```

3. **Configure Environment**
   ```bash
   echo 'export PATH="/usr/local/opt/qt@6/bin:$PATH"' >> ~/.zshrc
   source ~/.zshrc
   ```

4. **Clone the Repository**
   ```bash
   git clone https://github.com/muzammil5539/QT-Expense-Application.git
   cd QT-Expense-Application
   ```

## Building the Project

### Using Visual Studio

1. **Open the Project**
   - Launch Visual Studio 2022
   - Open `build/Project.vcxproj`
   - Wait for project to load and dependencies to resolve

2. **Configure Qt**
   - Go to Extensions → Qt VS Tools → Qt Options
   - Add your Qt installation path
   - Set as default version

3. **Build the Project**
   - Select configuration: Debug or Release
   - Build → Build Solution (Ctrl+Shift+B)
   - Wait for compilation to complete

4. **Run the Application**
   - Press F5 to debug or Ctrl+F5 to run without debugging

### Using Qt Creator

1. **Open the Project**
   - Launch Qt Creator
   - File → Open File or Project
   - Navigate to project directory
   - Select `build/Project.vcxproj` or create new `.pro` file

2. **Configure Kit**
   - Select appropriate kit (Desktop Qt 6.8.1)
   - Verify compiler and Qt version

3. **Build the Project**
   - Click the hammer icon or press Ctrl+B
   - Build → Build All

4. **Run the Application**
   - Click the green play button or press Ctrl+R

### Using Command Line

**Windows (with MSVC):**
```bash
cd QT-Expense-Application
mkdir build-cli
cd build-cli
cmake ..
msbuild Project.vcxproj /p:Configuration=Release
```

**Linux/macOS:**
```bash
cd QT-Expense-Application
mkdir build-cli
cd build-cli
qmake ../QT-Expense-Application.pro
make
```

Or create a `.pro` file first:

**Create `QT-Expense-Application.pro`:**
```qmake
QT += core gui widgets sql charts

TARGET = BudgetTracker
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += include

SOURCES += \
    src/main.cpp \
    src/login.cpp \
    src/project.cpp \
    src/stdafx.cpp

HEADERS += \
    include/login.h \
    include/project.h \
    include/stdafx.h \
    include/transaction.h \
    include/transaction_collection.h

FORMS += \
    login.ui \
    project.ui

RESOURCES += \
    resources/project.qrc
```

Then build:
```bash
qmake
make
```

## Running the Application

### First Run

1. **Launch the Application**
   - Run the compiled executable
   - On Windows: `Debug/Project.exe` or `Release/Project.exe`
   - On Linux/macOS: `./BudgetTracker`

2. **Register a User**
   - Enter a unique username
   - Enter a password
   - Click "Register"

3. **Login**
   - Enter your credentials
   - Click "Login"

4. **Start Using**
   - Add income or expenses
   - View transactions
   - Explore categories

### Database Location

The SQLite database file `budget_tracker.db` is created in the same directory as the executable:
- **Windows**: Same folder as `.exe`
- **Linux/macOS**: Current working directory

To reset the application, delete this file.

## Troubleshooting

### Common Issues

#### 1. "Cannot find Qt libraries"

**Solution:**
- Ensure Qt bin directory is in PATH
- Copy required Qt DLLs to executable directory
- Use `windeployqt` tool on Windows:
  ```bash
  windeployqt path/to/Project.exe
  ```

#### 2. "Missing MSVCP140.dll" (Windows)

**Solution:**
- Install Visual C++ Redistributable
- Download from Microsoft website

#### 3. "Database Error: unable to open database file"

**Solution:**
- Check write permissions in executable directory
- Ensure SQLite Qt plugin is available
- Verify qsqlite.dll is in `sqldrivers/` plugin directory

#### 4. "Charts not displaying"

**Solution:**
- Ensure Qt Charts module is installed
- Check that Qt6Charts.dll is accessible
- Verify Qt Charts plugin in plugins directory

#### 5. Build Fails with "stdafx.h not found"

**Solution:**
- Ensure include directory is in include path
- Check `AdditionalIncludeDirectories` in project settings
- Verify precompiled header settings

#### 6. "MOC: Cannot open options file"

**Solution:**
- Clean and rebuild project
- Check Qt installation path in project settings
- Verify Qt VS Tools or Qt Creator configuration

### Getting Help

If you encounter issues not covered here:

1. Check the [GitHub Issues](https://github.com/muzammil5539/QT-Expense-Application/issues)
2. Search Qt documentation at [doc.qt.io](https://doc.qt.io)
3. Contact maintainer: mnk.7muzammil86@gmail.com

## Development Tools

### Recommended Tools

1. **Code Editor**
   - Visual Studio 2022 with Qt VS Tools
   - Qt Creator
   - CLion with Qt plugin

2. **Database Browser**
   - DB Browser for SQLite
   - Download: [sqlitebrowser.org](https://sqlitebrowser.org)

3. **Version Control**
   - Git
   - GitHub Desktop (optional)

4. **Debugging**
   - Visual Studio Debugger
   - Qt Creator Debugger
   - GDB (Linux)

5. **Memory Profiling**
   - Visual Studio Profiler
   - Valgrind (Linux)

### Development Setup

1. **Enable Debug Symbols**
   - Build in Debug configuration for development
   - Use Release configuration for deployment

2. **Configure Logging**
   - Use `qDebug()` for debug output
   - Check Qt Creator Application Output pane

3. **Set Breakpoints**
   - Set breakpoints in IDE
   - Inspect variables during debugging

## Next Steps

Once you have successfully built and run the application:

1. Read the [Usage Guide](../README.md#usage-guide) in README
2. Review [Architecture Documentation](ARCHITECTURE.md)
3. Check [Contributing Guidelines](../CONTRIBUTING.md) if you want to contribute
4. Explore the code and experiment with modifications

## Additional Resources

- **Qt Documentation**: https://doc.qt.io
- **Qt Examples**: https://doc.qt.io/qt-6/qtexamplesandtutorials.html
- **SQLite Documentation**: https://www.sqlite.org/docs.html
- **C++ Reference**: https://cppreference.com

---

Need help? Open an issue on [GitHub](https://github.com/muzammil5539/QT-Expense-Application/issues) or contact the maintainer.
