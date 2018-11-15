//
// Created by achikamor on 13/11/18.
//

#ifndef SPL_ASS1_RESTAURANT_H
#define SPL_ASS1_RESTAURANT_H

#include <vector>
#include <string>

#include "../include/Dish.h"
#include "../include/Table.h"
#include "Action.h"


class Restaurant{
public:
    Restaurant();
    Restaurant(const std::string &configFilePath);
    void start();
    int getNumOfTables() const;
    Table* getTable(int ind);
    const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Dish>& getMenu();
    virtual ~Restaurant();
    Restaurant& operator=(Restaurant&& other);
    Restaurant& operator=(const Restaurant& other);
    Restaurant(const Restaurant& restaurant);

private:
    void openTable(std::string str);
    void initTable(int numOfTables,std::string str);    //avishai XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    bool open;
    std::vector<Table*> tables;
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
    int customerCount;
};

#endif