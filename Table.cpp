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
virtual void Table:: ~Table(){
   // std::vector<Customers*>::iterator it=customersList.begin();
    for(int i=0;i<orderList.size();i++){
        delete orderList(i);
    }
    for(int i=0;i<customersList.size();i++){
        delete customersList(i);   //NOT SURE ABOUT THE ORDER OF THE DELETE COMMANDS
        customersList(i)= nullptr;
    }

}

//CopyConstructor
virtual Table::Table(const Table& table):capacity(table.getCapacity(),open(table.isOpen(),orderList(table))){}

//copy assignment operator
Table& Table::operator=(const Table& other){
    this->capacity=other.getCapacity();
    this->open=other.isOpen();
    this->customersList=other.getCustomers();
    this->orderList=other.getOrders();

}

//MoveConstructor
Table Table::Table(Table&& other){
    steal(other);

}

void Table::steal(Table &other) {
    this->open=other.isOpen();
    this->capacity=other.getCapacity();
    this->orderList=other.getOrders();
    this->customersList=other.getCustomers();
    other= nullptr;

}

//MoveAssignmentOperator
Table& Table::operator=(Table&& other){
    delete ();
    steal(other);
    return *this;
}
