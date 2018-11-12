//
// Created by achikamor on 06/11/18.
//

#include "Table.h"
#include <vector>
#include<iostream>
#include "Customer.h"
#include "Dish.h"
#include "Customer.h"

//Constructor
Table::Table(int t_capacity):capacity(t_capacity),open(false){}

int Table::getCapacity() const {return this->capacity;}

void Table::addCustomer(Customer* customer){customersList.push_back(customer);}

void Table::removeCustomer(int id) {

    std::vector<Customer*>::iterator it=customersList.begin();
    bool found= false;                          //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    while(it != customersList.end(),!found){   //for(int i=0;i<customersList.size(), !found;i++) XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        if((*it)->getId()==id){         //might have to change (*it) to customerList[i]XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            customersList.erase(it);
            found=true;
        }
        it++;
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
Table::Table(const Table& table):capacity(table.getCapacity()),orderList(table.orderList),open(table.open){
    for(int i=0;i<table.customersList.size();i++)
        this->customersList[i]=table.customersList[i];

}
//copy assignment operator
Table& Table::operator=(const Table& other) {   //IF we change the argument of the function (table& other) to non const then
    if(this==&other)
        return *this;
    delete this;        //MOST CHECK HOW EXACTLY SHOULD WE DELETE 'THIS' BEFORE ASSIGN OTHER INTO IT
    this->capacity = other.getCapacity();
    open = other.open;                        //Deleted the 'this' before open
    this->orderList = other.orderList;
    for (int i = 0; i < other.customersList.size(); i++)
        this->customersList[i] = other.customersList[i];
}
//MoveConstructor
Table::Table(Table&& other){
    steal(other);

}

void Table::steal(Table& other) {
    this->open=other.isOpen();
    this->capacity=other.getCapacity();
    this->orderList=other.getOrders();
    this->customersList=other.getCustomers();
    other=0;                        //Nullptr DIDNT work so i changed it to 0
}

//MoveAssignmentOperator
Table& Table::operator=(Table&& other){
    delete this;
    steal(other);
    return *this;
}
