

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Restaurant.h"
#include "Table.h"
#include "Dish.h"



Restaurant::Restaurant():open(false) {}

Restaurant::Restaurant(const std::string &configFilePath) {
    std::ifstream sourceFile(configFilePath);
    std::string nextLn="";

    std::getline(sourceFile,nextLn);    //first #
    std::getline(sourceFile,nextLn);    //num of tables
    int tempInt=std::stoi(nextLn, nullptr,10);

    std::getline(sourceFile,nextLn);    //second #
    std::getline(sourceFile,nextLn);    //seats on tables
    initTable(tempInt,nextLn);

    std::getline(sourceFile,nextLn);    //3rd #
    int dishId=0;
    std::string dishName;
    std::string dishType;
    std::string dishPrice;

    menu.clear();
    while(std::getline(sourceFile,nextLn)){
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

void Restaurant::start() {

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
    return 0;
}

Table *Restaurant::getTable(int ind) {
    return nullptr;
}

const std::vector<BaseAction *> &Restaurant::getActionsLog() const {
    return <#initializer#>;
}

std::vector<Dish> &Restaurant::getMenu() {
    return <#initializer#>;
}

//
// Created by achikamor on 06/11/18.
//

#include "Restaurant.h"
#include<iostream>
#include<fstream>

//constructor

