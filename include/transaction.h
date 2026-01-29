#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "stdafx.h"

/**
 * @file transaction.h
 * @brief Defines transaction classes for the Budget Tracker Application
 * 
 * This file contains the abstract Transaction base class and its derived
 * classes Income and Expense, which represent financial transactions.
 */

/**
 * @class Transaction
 * @brief Abstract base class representing a financial transaction
 * 
 * This class provides the common interface for all transaction types.
 * It stores basic transaction information including amount, category,
 * subcategory, and date. Derived classes must implement getAmount(),
 * getCategory(), and clone() methods.
 */
class Transaction {
public:
    /**
     * @brief Default constructor
     * 
     * Initializes a transaction with zero amount, empty strings for
     * category/subcategory, and current date.
     */
    Transaction() : amount(0.0), category(""), subcategory(""), date(QDate::currentDate()) {}
    
    /**
     * @brief Virtual destructor
     * 
     * Ensures proper cleanup of derived classes.
     */
    virtual ~Transaction() = default;

    /**
     * @brief Gets the transaction amount
     * @return Transaction amount (positive for income, negative for expense)
     */
    virtual double getAmount() const = 0;
    
    /**
     * @brief Gets the transaction category
     * @return Category name as QString
     */
    virtual QString getCategory() const = 0;
    
    /**
     * @brief Gets the transaction subcategory
     * @return Subcategory name as QString
     */
    virtual QString getSubcategory() const { return subcategory; }
    
    /**
     * @brief Gets the transaction date
     * @return Transaction date as QDate
     */
    virtual QDate getDate() const { return date; }
    
    /**
     * @brief Creates a copy of the transaction
     * @return Pointer to a new transaction object (caller owns the memory)
     */
    virtual Transaction* clone() const = 0;

protected:
    double amount;        ///< Transaction amount
    QString category;     ///< Main category (e.g., "Salary", "Housing")
    QString subcategory;  ///< Optional subcategory for detailed tracking
    QDate date;           ///< Date of the transaction
};

/**
 * @class Income
 * @brief Represents an income transaction (positive cash flow)
 * 
 * Income transactions represent money coming in, such as salary,
 * investments, or business revenue. The amount is stored as a
 * positive value.
 */
class Income : public Transaction {
public:
    /**
     * @brief Constructs an Income transaction
     * @param amount Transaction amount (stored as positive)
     * @param category Main category (e.g., "Salary", "Investment")
     * @param subcategory Optional subcategory for details
     * @param date Date of the transaction
     */
    Income(double amount, const QString& category,
          const QString& subcategory, const QDate& date) {
        this->amount = amount;
        this->category = category;
        this->subcategory = subcategory;
        this->date = date;
    }

    /**
     * @brief Gets the income amount
     * @return Positive amount value
     */
    double getAmount() const override { return amount; }
    
    /**
     * @brief Gets the income category
     * @return Category name
     */
    QString getCategory() const override { return category; }
    
    /**
     * @brief Creates a copy of this income transaction
     * @return Pointer to new Income object
     */
    Transaction* clone() const override { return new Income(*this); }
};

/**
 * @class Expense
 * @brief Represents an expense transaction (negative cash flow)
 * 
 * Expense transactions represent money going out, such as bills,
 * purchases, or payments. The amount is automatically stored as a
 * negative value.
 */
class Expense : public Transaction {
public:
    /**
     * @brief Constructs an Expense transaction
     * @param amount Transaction amount (automatically negated for storage)
     * @param category Main category (e.g., "Housing", "Food")
     * @param subcategory Optional subcategory for details
     * @param date Date of the transaction
     */
    Expense(double amount, const QString& category,
           const QString& subcategory, const QDate& date) {
        this->amount = -amount;  // Store as negative
        this->category = category;
        this->subcategory = subcategory;
        this->date = date;
    }

    /**
     * @brief Gets the expense amount
     * @return Negative amount value
     */
    double getAmount() const override { return amount; }
    
    /**
     * @brief Gets the expense category
     * @return Category name
     */
    QString getCategory() const override { return category; }
    
    /**
     * @brief Creates a copy of this expense transaction
     * @return Pointer to new Expense object
     */
    Transaction* clone() const override { return new Expense(*this); }
};

#endif // TRANSACTION_H