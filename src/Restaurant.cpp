//
// Created by achikamor on 06/11/18.
//





#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../include/Restaurant.h"
#include "../include/Table.h"
#include "../include/Dish.h"



Restaurant::Restaurant():open(false),customerCount(0) {}

Restaurant::Restaurant(bool status,int count):open(status),customerCount(count) {}

Restaurant::Restaurant(const std::string &configFilePath) :open(false),customerCount(0){
    std::ifstream sourceFile(configFilePath);
    std::string nextLn="";
    bool firstStage=true;
    int dishId=0;
    std::string dishName;
    std::string dishType;
    std::string dishPrice;

    menu.clear();

    while (std::getline(sourceFile,nextLn)){
        if(firstStage){

            while(nextLn.at(0)=='#' || nextLn=="" || nextLn=="\r")
                std::getline(sourceFile,nextLn);
            int tempInt=std::stoi(nextLn, nullptr,10);

            std::getline(sourceFile,nextLn);
            while(nextLn.at(0)=='#' || nextLn=="" || nextLn=="\r")
                std::getline(sourceFile,nextLn);
            initTable(tempInt,nextLn);

            firstStage=false;

        }
        else{
            while(nextLn.at(0)=='#' || nextLn.empty() || nextLn=="\r") {
                std::getline(sourceFile, nextLn);
            }
            std::stringstream ss(nextLn);
            std::getline(ss,dishName,',');
            std::getline(ss,dishType,',');
            std::getline(ss,dishPrice,',');
            if(dishType=="VEG")
                menu.push_back(Dish(dishId,dishName,std::stoi(dishPrice, nullptr,10),VEG));
            else if(dishType=="ALC")
                menu.push_back(Dish(dishId,dishName,std::stoi(dishPrice, nullptr,10),ALC));
            else if(dishType=="SPC")
                menu.push_back(Dish(dishId,dishName,std::stoi(dishPrice, nullptr,10),SPC));
            else if(dishType=="BVG")
                menu.push_back(Dish(dishId,dishName,std::stoi(dishPrice, nullptr,10),BVG));
            dishId++;

        }
    }
}


void Restaurant::start() {
    open=true;
    std:: cout<<"Restaurant is now open!"<<std::endl;
    std::string input;
    std::string word;

    while(open){
        getline(std::cin,input);
        std::stringstream ss(input);
        std::getline(ss,word,' ');
        if(word=="open"){
            openTable(input.substr(5));
        }
        else if(word=="order"){
            std::getline(ss,word,' ');
            int tableId=std::stoi(word);
            actionsLog.push_back(new Order(tableId));
            actionsLog.back()->act(*this);
        }
        else if(word=="move"){
            std::getline(ss,word,' ');
            int strt=std::stoi(word);
            std::getline(ss,word,' ');
            int dst=std::stoi(word);
            std::getline(ss,word,' ');
            int id=std::stoi(word);
            actionsLog.push_back(new MoveCustomer(strt,dst,id));
            actionsLog.back()->act(*this);
        }
        else if(word=="close"){
            std::getline(ss,word,' ');
            int tableId=std::stoi(word);
            actionsLog.push_back(new Close(tableId));
            actionsLog.back()->act(*this);
        }
        else if(word=="closeall"){
            actionsLog.push_back(new CloseAll());
            actionsLog.back()->act(*this);
        }
        else if(word=="menu"){
            actionsLog.push_back(new PrintMenu());
            actionsLog.back()->act(*this);
        }
        else if(word=="status"){
            std::getline(ss,word,' ');
            int tbl=std::stoi(word);
            if(tbl>=0,tbl<tables.size()){
                actionsLog.push_back( new PrintTableStatus(tbl));
                actionsLog.back()->act(*this);
            }
        }
        else if(word=="log"){
            BaseAction* action= new PrintActionsLog();
            action->act(*this);
            actionsLog.push_back(action);
            action= 0;
        }
        else if(word=="backup"){
            actionsLog.push_back( new BackupRestaurant());
            actionsLog.back()->act(*this);
        }
        else if(word=="restore"){
            actionsLog.push_back( new BackupRestaurant());
            actionsLog.back()->act(*this);

        }

    }

}

void Restaurant::openTable(std::string str){
    std::stringstream ss(str);
    std::vector<Customer *> customers;
    std::string cstmrName;

    std::getline(ss,cstmrName,' ');
    int tableId=std::stoi(cstmrName,nullptr,10);
    std::string cstmrType;
    while (std::getline(ss, cstmrName, ',')) {
        std::getline(ss, cstmrType, ' ');
        if (cstmrType == "veg")
            customers.push_back(new VegetarianCustomer(cstmrName, customerCount));
        else if (cstmrType == "chp")
            customers.push_back(new CheapCustomer(cstmrName, customerCount));
        else if (cstmrType == "spc")
            customers.push_back(new SpicyCustomer(cstmrName, customerCount));
        else if (cstmrType == "alc")
            customers.push_back(new AlchoholicCustomer(cstmrName, customerCount));
        customerCount++;
    }
    actionsLog.push_back(new OpenTable(tableId, customers));
    actionsLog.back()->act(*this);



}



void Restaurant::initTable(int numOfTables,std::string str){
    std::string tempStr;
    std::stringstream ss(str);
    for(int i=0;i<numOfTables;i++){
        std::getline(ss,tempStr,',');
        tables.push_back(new Table(std::stoi(tempStr, nullptr,10)));
    }
}
int Restaurant::getCustomerCount() const {
    return customerCount;
}
int Restaurant::getNumOfTables() const {
    return tables.size();
}

Table *Restaurant::getTable(int ind) {
    if(ind>=0,ind<tables.size())
        return tables[ind];
    return nullptr;

}

const std::vector<BaseAction *> &Restaurant::getActionsLog() const {
    return actionsLog;
}

std::vector<Dish> &Restaurant::getMenu() {
    return menu;
}

Restaurant& Restaurant::operator=(Restaurant&& other) {
    if(this==&other)
        return *this;
    this->open = other.open;
    this->customerCount = other.customerCount;
    this->menu.clear();
    for(auto dish:other.menu)
        this->menu.push_back(Dish(dish.getId(),dish.getName(),dish.getPrice(),dish.getType()));

    for(auto table:tables){
        delete(table);
        table= nullptr;
    }
    tables.clear();

    for(auto table:other.tables)
        this->tables.push_back(new Table(*table));

    for(auto action:actionsLog){
        delete(action);
        action= nullptr;
    }
    actionsLog.clear();

    for(auto action:other.actionsLog)
        this->actionsLog.push_back(action->clone());



}

Restaurant::~Restaurant() {
    for(auto table:tables){
        delete(table);
        table= nullptr;
    }

    for(auto action:actionsLog){
        delete(action);
        action= nullptr;
    }

}
