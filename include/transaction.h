#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "stdafx.h"

class Transaction {
public:
    Transaction() : amount(0.0), category(""), subcategory(""), date(QDate::currentDate()) {}
    virtual ~Transaction() = default;

    virtual double getAmount() const = 0;
    virtual QString getCategory() const = 0;
    virtual QString getSubcategory() const { return subcategory; }
    virtual QDate getDate() const { return date; }
    virtual Transaction* clone() const = 0;

protected:
    double amount;
    QString category;
    QString subcategory;
    QDate date;
};

class Income : public Transaction {
public:
    Income(double amount, const QString& category,
          const QString& subcategory, const QDate& date) {
        this->amount = amount;
        this->category = category;
        this->subcategory = subcategory;
        this->date = date;
    }

    double getAmount() const override { return amount; }
    QString getCategory() const override { return category; }
    Transaction* clone() const override { return new Income(*this); }
};

class Expense : public Transaction {
public:
    Expense(double amount, const QString& category,
           const QString& subcategory, const QDate& date) {
        this->amount = -amount;
        this->category = category;
        this->subcategory = subcategory;
        this->date = date;
    }

    double getAmount() const override { return amount; }
    QString getCategory() const override { return category; }
    Transaction* clone() const override { return new Expense(*this); }
};

#endif // TRANSACTION_H