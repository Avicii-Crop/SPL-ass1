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
    std::string c_type;
    std::string c_name;
    while(it!=customersList.end()){
        c_type=(*it)->getName().substr((*it)->getName().length()-3,3);
        c_name=(*it)->getName().substr(0,(*it)->getName().length()-4);
        if(c_type=="veg"){}

    }

}

void Table::closeTable(){open= false;}