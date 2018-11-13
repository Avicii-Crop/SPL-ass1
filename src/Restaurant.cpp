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
            std::cout << nextLn << std::endl;
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
        std::cin >> input;
        std::stringstream ss(input);
        std::getline(ss,word,' ');
        if(word=="open"){
                openTable(input.substr(5));
        }
        else if(word=="order"){

        }
        else if(word=="move"){

        }
        else if(word=="close"){

        }
        else if(word=="closeall"){

        }
        else if(word=="menu"){

        }
        else if(word=="status"){

        }
        else if(word=="log"){

        }
        else if(word=="backup"){

        }
        else if(word=="restore"){

        }

    }

}

void Restaurant::openTable(std::string str){
    std::stringstream ss(str);
    std::vector<Customer *> customers;
    std::string cstmrName;

    std::getline(ss,cstmrName,' ');
    int tableId=std::stoi(cstmrName,nullptr,10);
    if(tableId>=0,tableId<tables.size(),!(tables[tableId]->isOpen())) {

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
        BaseAction *action = new OpenTable(tableId, customers);
        (*action).act(*this);
        actionsLog.push_back(action);
    }
    else{
        std:: cout <<"Table does not exist or is already open" <<std::endl;
    }

}

void Restaurant::initTable(int numOfTables,std::string str){
    std::string tempStr;
    std::stringstream ss(str);
    for(int i=0;i<numOfTables;i++){
        std::getline(ss,tempStr,',');
        tables.push_back(new Table(std::stoi(tempStr, nullptr,10)));
    }
}

int Restaurant::getNumOfTables() const {
    return tables.size();
}

Table *Restaurant::getTable(int ind) {
    return tables[ind-1];

}

const std::vector<BaseAction *> &Restaurant::getActionsLog() const {
    return actionsLog;
}

std::vector<Dish> &Restaurant::getMenu() {
    return menu;
}



