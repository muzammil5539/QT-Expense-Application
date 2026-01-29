#pragma once
#ifndef TRANSACTION_COLLECTION_H
#define TRANSACTION_COLLECTION_H

#include <vector>
#include <memory>
#include "transaction.h"

/**
 * @file transaction_collection.h
 * @brief Template class for managing collections of transactions
 */

/**
 * @class TransactionCollection
 * @brief Template-based container for managing transaction objects
 * 
 * This class provides a type-safe container for storing and managing
 * transaction objects. It uses smart pointers (unique_ptr) for automatic
 * memory management and provides utility methods for common operations
 * like calculating totals and filtering by category.
 * 
 * @tparam T Transaction type (must inherit from Transaction)
 * 
 * @example
 * @code
 * TransactionCollection<Transaction> allTransactions;
 * Income income(1000.0, "Salary", "Monthly", QDate::currentDate());
 * allTransactions.add(income);
 * double total = allTransactions.getTotalAmount();
 * @endcode
 */
template<typename T>
class TransactionCollection {
public:
    /**
     * @brief Adds a transaction to the collection
     * 
     * Creates a clone of the provided transaction and stores it in the
     * collection using a unique_ptr. This ensures the collection owns
     * its data and prevents memory leaks.
     * 
     * @param transaction The transaction to add (will be cloned)
     */
    void add(const T& transaction) {
        // Clone the transaction and store it in the collection
        // Using unique_ptr ensures automatic memory management
        transactions.push_back(std::unique_ptr<T>(transaction.clone()));
    }

    /**
     * @brief Calculates the total amount of all transactions
     * 
     * Iterates through all transactions in the collection and sums
     * their amounts. Useful for calculating net balance or category
     * totals.
     * 
     * @return Sum of all transaction amounts
     */
    double getTotalAmount() const {
        double total = 0.0;
        // Iterate through all transactions and sum their amounts
        for (const auto& trans : transactions) {
            total += trans->getAmount();
        }
        return total;
    }

    /**
     * @brief Retrieves transactions belonging to a specific category
     * 
     * Filters the collection to return only transactions that match
     * the specified category. Returns raw pointers to the transactions,
     * but the collection retains ownership.
     * 
     * @param category The category to filter by
     * @return Vector of pointers to matching transactions (non-owning)
     * 
     * @note The returned pointers are valid only as long as the
     *       collection exists and is not modified.
     */
    std::vector<T*> getByCategory(const QString& category) const {
        std::vector<T*> result;
        // Iterate through all transactions and add those that match the category
        for (const auto& trans : transactions) {
            if (trans->getCategory() == category) {
                result.push_back(trans.get());
            }
        }
        return result;
    }

private:
    /// Vector storing unique pointers to transactions for automatic memory management
    std::vector<std::unique_ptr<T>> transactions;
};

#endif // TRANSACTION_COLLECTION_H