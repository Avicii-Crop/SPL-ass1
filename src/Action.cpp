//
// Created by achikamor on 06/11/18.
//

#include "../include/Action.h"
#include "Customer.cpp"

BaseAction::BaseAction() {

}

ActionStatus BaseAction::getStatus() const {
    return COMPLETED;
}

void BaseAction::complete() {

}

void BaseAction::error(std::string errorMsg) {

}

std::string BaseAction::getErrorMsg() const {
    return std::__cxx11::string();
}

OpenTable::OpenTable(int id, std::vector<Customer*> &customersList): BaseAction(),tableId(id) ,customers(customersList){}

void OpenTable::act(Restaurant &restaurant) {

}

std::string OpenTable::toString() const {
    return std::__cxx11::string();
}
