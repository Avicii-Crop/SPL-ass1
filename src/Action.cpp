//
// Created by achikamor on 06/11/18.
//

#include "../include/Action.h"
#include "../include/Table.h"
#include "../include/Restaurant.h"
#include <iostream>


BaseAction::BaseAction():status(PENDING){

}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status=COMPLETED;

}

void BaseAction::error(std::string errorMsg) {

}

std::string BaseAction::getErrorMsg() const {
    return std::__cxx11::string();
}

OpenTable::OpenTable(int id, std::vector<Customer*> &customersList): BaseAction(),tableId(id) ,customers(customersList){}

void OpenTable::act(Restaurant &restaurant) {
    Table* tbl=restaurant.getTable(tableId);
    for(auto customer :customers){
        tbl->addCustomer(customer);
    }
    this->complete();

}

std::string OpenTable::toString() const {
    std::string output="open "+ std::to_string(tableId);
    for(auto customer :customers) {
        output +=" "+customer->toString();
    }
    return output;
}

Order::Order(int id):BaseAction(),tableId(id) {}
void Order::act(Restaurant &restaurant) {

}

std::string Order::toString() const {  //NEED TO COMPLETE
    return std::__cxx11::string();
}

/*
MoveCustomer::MoveCustomer(int src,int dst,int customerId):BaseAction() ,srcTable(src),dstTable(dst),id(customerId){
    
}*/

PrintTableStatus::PrintTableStatus(int id):BaseAction(),tableId(id){}

void PrintTableStatus::act(Restaurant &restaurant) {
    Table* tbl=restaurant.getTable(tableId);
    if(tbl->isOpen()){
        std::cout << "Table "<< std::to_string(tableId) <<" status: open" << std::endl;

        std::cout << "Customers:" << std::endl;
        for(auto customer:tbl->getCustomers())
            std::cout << customer->getId() << " " << customer->getName() << std::endl;

        std::cout << "Orders:" << std::endl;
        for(auto order:tbl->getOrders())
            std::cout << order.second.getName() << " " << order.second.getPrice() <<"NIS " << order.first << std::endl;

        std::cout << "Current Bill: " << tbl->getBill() << "NIS" << std::endl;
    }
    else{
        std::cout << "Table "<< std::to_string(tableId) <<" status: close" << std::endl;
    }

    complete();
}

std::string PrintTableStatus::toString() const {
    return "status "+std::to_string(tableId)+" "+std::to_string(getStatus());
}
