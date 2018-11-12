//
// Created by achikamor on 06/11/18.
//

#include "Action.h"

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
