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
    status=ERROR;
    this->errorMsg=errorMsg;
}

std::string BaseAction::getErrorMsg() const {
    return this->errorMsg;
}

OpenTable::OpenTable(int id, std::vector<Customer*> &customersList): BaseAction(),tableId(id) ,customers(customersList){

}


void OpenTable::act(Restaurant &restaurant) {
    Table* tbl=restaurant.getTable(tableId);
    if(tbl == nullptr || tbl->isOpen()) {
        error("Table does not exist or is already open");
        std::cout << getErrorMsg() << std::endl;
    }
    else{
        tbl->openTable();
        for(auto customer :customers){
            tbl->addCustomer(customer);
        }
        complete();
    }
}

std::string OpenTable::toString() const {
    std::string output="open "+ std::to_string(tableId);
    for(auto customer :customers) {
        output +=" "+customer->toString();
    }
    if(getStatus()==ERROR)
        output+=" Error: "+getErrorMsg();
    else
        output+=" Completed";
    return output;
}

Order::Order(int id):BaseAction(),tableId(id) {}
void Order::act(Restaurant &restaurant) {
    Table* tbl=restaurant.getTable(tableId);
    if(tbl == nullptr || !tbl->isOpen()){
        error("Table does not exist or is already open");
        std::cout << getErrorMsg() << std::endl;
    }
    else{
        tbl->order(restaurant.getMenu());
        complete();
    }
}

std::string Order::toString() const {
    std::string output ="order "+std::to_string(tableId);
    if(getStatus()==ERROR)
        output+=" Error: "+getErrorMsg();
    else
        output+=" Completed";
    return output;
}



MoveCustomer::MoveCustomer(int src,int dst,int customerId):BaseAction() ,srcTable(src),dstTable(dst),id(customerId){}
void MoveCustomer::act(Restaurant &restaurant){
    Table* srcT=restaurant.getTable(srcTable);
    Table* dstT=restaurant.getTable(dstTable);
    if((srcT== nullptr||dstT== nullptr) || (!srcT->isOpen()|| !dstT->isOpen() ) ||
    dstT->getCapacity()==dstT->getCustomers().size()|| srcT->getCustomer(id)== nullptr){
        error("Cannot move customer");
        std:: cout << getErrorMsg()<< std::endl;
    }
    else{
        dstT->addCustomer(srcT->getCustomer(id));  //NEED TO ADD TO THE NEW TABLE THE CUSTOMERS ORDERS AND DELETE THEM (AND THEIR PRICES) FROM THE SRCTABLE
        for(auto order:srcT->getOrders()){
            if(order.first==id){
                dstT->getOrders().push_back(OrderPair(id,order.second));
            }
        }
        srcT->removeCustomer(id);
        complete();

    }
}

std::string MoveCustomer::toString() const {
    std::string output ="move "+std::to_string(srcTable)+" "+std::to_string(dstTable)+" "+std::to_string(id);
    if(getStatus()==ERROR)
        output+=" Error: "+getErrorMsg();
    else
        output+=" Completed";
    return output;
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

Close::Close(int id): BaseAction(), tableId(id){}

void Close::act(Restaurant &restaurant) {
    Table* table=restaurant.getTable(tableId);
    if(table== nullptr ||!table->isOpen()){
        error("Table does not exist or is not open");
        std::cout<< getErrorMsg()<< std::endl;
    }
    else{
        for(auto customer:table->getCustomers())
            table->removeCustomer(customer->getId());
        table->closeTable();
        std::cout<<"Table "<<tableId<<"was closed. Bill "<<table->getBill()<<std::endl;
        complete();
    }


}

std::string Close::toString() const {
    std::string output ="close "+std::to_string(tableId);
    if(getStatus()==ERROR)
        output+=" Error: "+getErrorMsg();
    else
        output+=" Completed";
    return output;
}

CloseAll::CloseAll(): BaseAction() {}

void CloseAll::act(Restaurant &restaurant) {
    for(int i=0; i<restaurant.getNumOfTables();i++){
        if(restaurant.getTable(i)->isOpen()){
            Close action=Close(i);
            action.act(restaurant);
            std::cout<<action.toString()<<std::
        }
        complete();

    }

}

std::string CloseAll::toString() const {
    std::string output ="closeall ";
    if(getStatus()==COMPLETED)
        output+=" Completed";
    else
        output+=" Pending";
    return output;
}
