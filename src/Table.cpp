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

    std::vector<Customer*>::iterator it=customersList.begin();
    bool found= false;                          //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
      for(int i=0;i<customersList.size(), !found;i++) { //while(it != customersList.end(),!found)
        if(customersList[i]->getId()==id){         //might have to change (*it) to customerList[i]XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            customersList.erase(customersList.begin()+i);
            found=true;
        }
    }

    //removing the customer orders from the table
    if(found){
        std::vector<OrderPair>::iterator orderIt=orderList.begin();
        while(orderIt!=orderList.end()){
            if((*orderIt).first==id)
                orderList.erase(orderIt);
        }
    }
}

Customer* Table::getCustomer(int id) {  //if the id is not in the table return nullptr.
    Customer* output= nullptr;
    bool found=false;
    for(int i=0;i<customersList.size(), !found;i++) {
        if (customersList[i]->getId() == id) {
            output = customersList[i];
            found = true;
        }
    }
    return output;
}

std::vector<Customer*>& Table::getCustomers(){return customersList;}

std::vector<OrderPair>& Table::getOrders(){return orderList;}

void Table::openTable(){open=true;}

bool Table::isOpen(){return open;}

void Table::order(const std::vector<Dish> &menu){
    std::vector<Customer*>::iterator it=customersList.begin();
    std::vector<int> itCustomerOrders;
    while(it!=customersList.end()) {
        itCustomerOrders = (*it)->order(menu);
        for (int i = 0; i < itCustomerOrders.size(); i++) {
            orderList.push_back(OrderPair((*it)->getId(), menu[itCustomerOrders[i]]));
            std::cout<<(*it)->getName()<<" ordered " << menu[itCustomerOrders[i]].getName()<< std::endl;
        }
    }
}

void Table::closeTable(){open= false;}

int Table::getBill(){
    int output=0;
    for(int i=0;i<orderList.size();i++)
        output+=orderList[i].second.getPrice();
    return output;
}

//Destructor
Table:: ~Table(){
    // std::vector<Customers*>::iterator it=customersList.begin();
    for(int i=0;i<customersList.size();i++)                   //There is no need to delete a vector of objects
        delete customersList[i];                                // In case of pointers we have to delete each pointer
    customersList.clear();                                     //After deleting each pointer we need to delete the vector itself
}

//CopyConstructor
Table::Table(Table& other):capacity(other.getCapacity()),orderList(other.orderList),open(other.open){
    for(int i=0;i<other.customersList.size();i++)
        this->customersList.push_back(other.customersList[i]->clone());
    for (int i = 0; i < other.orderList.size(); i++)
        this->orderList.push_back(other.orderList[i]);

}
//copy assignment operator
Table& Table::operator=(const Table& other) {
    if(this==&other)
        return *this;
    this->capacity = other.getCapacity();
    this->open = other.open;                        //Deleted the 'this' before open
    for (int i = 0; i < this->customersList.size(); i++) {
        delete(this->customersList[i]);
        this->customersList[i]= nullptr;
    }
    this->orderList.clear();
    for (int i = 0; i < other.orderList.size(); i++)
        this->orderList.push_back(other.orderList[i]);

    for (int i = 0; i < other.customersList.size(); i++)
        this->customersList.push_back(other.customersList[i]);
}
//MoveConstructor
Table::Table(Table&& other):open(other.isOpen()),capacity(other.getCapacity()){
    for (int i = 0; i < other.orderList.size(); i++)
        this->orderList.push_back(other.orderList[i]);

    for (int i = 0; i < other.customersList.size(); i++) {
        this->customersList.push_back(other.customersList[i]);
        other.customersList[i]= nullptr;
    }
    other.customersList.clear();
    other.orderList.clear();
}

//MoveAssignmentOperator
Table& Table::operator=(Table&& other){
    if(this!=&other){
        this->orderList.clear();
        for(int i=0;i<this->customersList.size();i++){
            delete(this->customersList[i]);
            this->customersList[i]= nullptr;
        }
        this->customersList.clear();
        this->customersList=other.customersList;
        other.customersList.clear();
        this->orderList=other.orderList;
        other.orderList.clear();
        this->capacity=other.capacity;
        this->open=other.open;

    }
    return *this;
}
