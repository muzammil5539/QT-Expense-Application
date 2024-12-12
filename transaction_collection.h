#pragma once
#ifndef TRANSACTION_COLLECTION_H
#define TRANSACTION_COLLECTION_H

#include <vector>
#include <memory>
#include "transaction.h"

// Template class to manage a collection of transactions
template<typename T>
class TransactionCollection {
public:
    // Adds a transaction to the collection
    void add(const T& transaction) {
        // Clone the transaction and store it in the collection
        transactions.push_back(std::unique_ptr<T>(transaction.clone()));
    }

    // Calculates the total amount of all transactions in the collection
    double getTotalAmount() const {
        double total = 0.0;
        // Iterate through all transactions and sum their amounts
        for (const auto& trans : transactions) {
            total += trans->getAmount();
        }
        return total;
    }

    // Retrieves all transactions that belong to a specific category
    std::vector<T*> getByCategory(const QString& category) const {
        std::vector<T*> result;
        // Iterate through all transactions and add those that match the category to the result
        for (const auto& trans : transactions) {
            if (trans->getCategory() == category) {
                result.push_back(trans.get());
            }
        }
        return result;
    }

private:
    // Vector to store unique pointers to transactions
    std::vector<std::unique_ptr<T>> transactions;
};

#endif // TRANSACTION_COLLECTION_H