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
    if(restaurant.getTable(this->tableId) == nullptr || !restaurant.getTable(tableId)->isOpen())
        std::cout << "Table does not exist or is not open" << std::endl;
    else{
        restaurant.getTable(tableId)->order(restaurant.getMenu());
    }
}

std::string Order::toString() const {  //NEED TO COMPLETE
    return std::__cxx11::string();
}



MoveCustomer::MoveCustomer(int src,int dst,int customerId):BaseAction() ,srcTable(src),dstTable(dst),id(customerId){}
void MoveCustomer::act(Restaurant &restaurant){
    if(restaurant.getNumOfTables()<(srcTable |dstTable)| (srcTable|dstTable)<0 | !restaurant.getTable(srcTable)->isOpen()|!restaurant.getTable(dstTable)->isOpen() |
    restaurant.getTable(dstTable)->getCapacity()==restaurant.getTable(dstTable)->getCustomers().size()|
    restaurant.getTable(srcTable)->getCustomer(id)== nullptr)
            std:: cout << "Cannot move customer"<< std::endl;
    else{
        restaurant.getTable(dstTable)->addCustomer(restaurant.getTable(srcTable)->getCustomer(id));  //NEED TO ADD TO THE NEW TABLE THE CUSTOMERS ORDERS AND DELETE THEM (AND THEIR PRICES) FROM THE SRCTABLE

    }
}


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

