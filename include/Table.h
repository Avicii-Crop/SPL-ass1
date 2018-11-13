//
// Created by achikamor on 13/11/18.
//

#ifndef SPL_ASS1_TABLE_H
#define TABLE_H_

#include <vector>
#include "../include/Customer.h"
#include "../include/Dish.h"

typedef std::pair<int, Dish> OrderPair;

class Table{
public:
    Table(int t_capacity);
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const std::vector<Dish> &menu);
    void openTable();
    void closeTable();
    int getBill();
    bool isOpen();
    virtual ~Table();
    Table(const Table& table);
    Table& operator=(const Table& other);
    Table(Table&& other);
    void steal(Table& other);
    Table& operator=(Table&& other);
private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order in a table - (customer_id, Dish)
};


#endif