//
// Created by achikamor on 06/11/18.
//

#include "../include/Table.h"
#include <vector>
#include<iostream>
#include "../include/Customer.h"
#include "../include/Dish.h"
#include "../include/Customer.h"

//Constructor
Table::Table(int t_capacity):capacity(t_capacity),open(false){}

int Table::getCapacity() const {return this->capacity;}

void Table::addCustomer(Customer* customer){customersList.push_back(customer);}

void Table::removeCustomer(int id) {


    bool found= false;
    int size=((int)this->customersList.size());
    for(int i=0;i<size, !found;i++) {
        if(customersList[i]->getId()==id){
            delete(*(customersList.begin()+i));
            *(customersList.begin()+i)= nullptr;
            customersList.erase(customersList.begin()+i);
            found=true;
        }
    }

    //removing the customer orders from the table
    if(found){
        int j=0;
        std::vector<OrderPair> tmpOrderList;
        for(auto order:orderList) {
            if (order.first != id)
                tmpOrderList.push_back(order);
        }
        orderList.clear();
        for(auto order:tmpOrderList)
            orderList.push_back(order);
    }
}

Customer* Table::getCustomer(int id) {  //if the id is not in the table return nullptr.
    Customer* output= nullptr;
    bool found=false;
    int size=((int)this->customersList.size());
    for(int i=0;i<size, !found;i++) {
        if (customersList[i]->getId() == id) {
            output = customersList[i];
            found = true;
        }
    }
    if(found)
        return output;
    return nullptr;
}

std::vector<Customer*>& Table::getCustomers(){return customersList;}

std::vector<OrderPair>& Table::getOrders(){return orderList;}

void Table::openTable(){open=true;}

bool Table::isOpen(){return open;}

void Table::order(const std::vector<Dish> &menu){

    std::vector<int> customerOrders;
    for(auto customer:customersList) {
        customerOrders = customer->order(menu);
        for (auto order:customerOrders) {
            orderList.push_back(OrderPair(customer->getId(), menu[order]));
            std::cout<<customer->getName()<<" ordered " << menu[order].getName()<< std::endl;
        }
    }
}

void Table::closeTable(){open= false;}

int Table::getBill(){
    int output=0;
    int size=((int)this->orderList.size());
    for(int i=0;i<size;i++)
        output+=orderList[i].second.getPrice();
    return output;
}

//Destructor
Table:: ~Table(){
    int size=((int)this->customersList.size());
    for(int i=0;i<size;i++)                   //There is no need to delete a vector of objects
        delete customersList[i];                                // In case of pointers we have to delete each pointer
    customersList.clear();                                     //After deleting each pointer we need to delete the vector itself
}

//CopyConstructor
Table::Table(Table& other):capacity(other.getCapacity()),orderList(other.orderList),open(other.open){
    int size=((int)other.customersList.size());
    for(int i=0;i<size;i++)
        this->customersList.push_back(other.customersList[i]->clone());
    int size1=((int)other.orderList.size());
    for (int i = 0; i < size1; i++)
        this->orderList.push_back(other.orderList[i]);

}
//copy assignment operator
Table& Table::operator=(const Table& other) {
    if(this==&other)
        return *this;
    this->capacity = other.getCapacity();
    this->open = other.open;
    int size=((int)this->customersList.size());
    for (int i = 0; i < size; i++) {
        delete(this->customersList[i]);
        this->customersList[i]= nullptr;
    }
    this->orderList.clear();
    int size1=((int)other.orderList.size());
    for (int i = 0; i < size1; i++)
        this->orderList.push_back(other.orderList[i]);
    int size2=((int)other.customersList.size());
    for (int i = 0; i < size2; i++)
        this->customersList.push_back(other.customersList[i]);
}
//MoveConstructor
Table::Table(Table&& other):open(other.isOpen()),capacity(other.getCapacity()){
    int size=((int)other.orderList.size());
    for (int i = 0; i < size; i++)
        this->orderList.push_back(other.orderList[i]);
    int size1=((int)other.customersList.size());
    for (int i = 0; i <size1; i++) {
        this->customersList.push_back(other.customersList[i]);
        other.customersList[i]= nullptr;
    }
    other.customersList.clear();
    other.orderList.clear();
}


Table& Table::operator=(Table&& other){
    if(this!=&other){
        this->capacity=other.capacity;
        this->open=other.open;
        int size=((int)this->customersList.size());
        for(int i=0;i<size;i++){
            delete(this->customersList[i]);
            this->customersList[i]= nullptr;
        }
        this->customersList.clear();
        int size1=((int)other.customersList.size());
        for(int i=0;i<size1;i++)
            this->customersList.push_back(other.customersList[i]);
        this->orderList.clear();
        int size2=((int)other.orderList.size());
        for(int i=0;i<size2;i++)
            this->orderList.push_back(other.orderList[i]);
        other.customersList.clear();
        other.orderList.clear();

    }
    return *this;
}