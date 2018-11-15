//
// Created by achikamor on 06/11/18.
//

#include "../include/Customer.h"
#include "../include/Dish.h"
#include<iostream>
#include<fstream>
#include<string>
#include <limits>

//constructor
Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id){}

//getters
std::string Customer::getName() const{
    return this->name;
}


int Customer::getId() const{
    return this->id;
}
// VEG
VegetarianCustomer::VegetarianCustomer(std::string name, int id):Customer(name,id){}

std::vector<int> VegetarianCustomer:: order(const std::vector<Dish> &menu){
    std::vector<int> output;

    int TmpId = std::numeric_limits<int>::max();
    int bvId = 0;
    int dish = -1;
    int bvg = -1;
    int bvPrice = 0;
    for (int i = 0; i < menu.size(); i++) {
        if (menu[i].getType() == VEG, menu[i].getId() < TmpId) {
            TmpId = menu[i].getId();
            dish = i;
        }
        if (menu[i].getType() == BVG, (menu[i].getPrice() > bvPrice || (menu[i].getPrice()==bvPrice,menu[i].getId()<bvId))) {
            bvPrice = menu[i].getPrice();
            bvId = menu[i].getId();
            bvg = i;
        }
        if(bvg!=-1,dish!=-1) {

            output.push_back(TmpId);
            output.push_back(bvId);
        }

        return output;
    }
}

std::string VegetarianCustomer:: toString() const{
    std::string s=this->getName()+",veg";
    return s;
}
Customer* VegetarianCustomer::clone(){
  return new VegetarianCustomer(*this);
}

//CHP
CheapCustomer::CheapCustomer(std::string name, int id):Customer(name,id),ordered(false){}

std::vector<int>CheapCustomer:: order(const std::vector<Dish> &menu) {
    std::vector<int> output;
    if (!ordered) {
        int tmpPrice = std::numeric_limits<int>::max();
        int tmpId = std::numeric_limits<int>::max();
        bool foundDish=false;
        for (int i = 0; i < menu.size(); i++) {
            if ((menu[i].getPrice() == tmpPrice, tmpId > menu[i].getId()) || menu[i].getPrice() < tmpPrice) {
                tmpId = menu[i].getId();
                tmpPrice = menu[i].getPrice();
                foundDish=true;
            }
            if(foundDish)
                output.push_back(tmpId);
        }
    }
    return output;
}
Customer* CheapCustomer:: clone(){
    return new CheapCustomer(*this);
}


std::string CheapCustomer:: toString() const{
    std::string s=this->getName()+",chp";
    return s;
}


//SPC
SpicyCustomer::SpicyCustomer(std::string name, int id):Customer(name,id),orderCount(0),bvgId(-1){}

std::vector<int>SpicyCustomer:: order(const std::vector<Dish> &menu){
    std::vector<int> output;
    int dishId = std::numeric_limits<int>::max();
    bool foundDish=false;
    switch (orderCount){
        case 0:{
            int dishPrice = 0;

            for (int i = 0; i < menu.size(); i++) {
                if(menu[i].getType()==SPC)
                    if (menu[i].getPrice() > dishPrice || (menu[i].getPrice() == dishPrice, menu[i].getId() < dishId)) {
                        dishPrice = menu[i].getPrice();
                        dishId = menu[i].getId();
                        foundDish=true;
                    }
            }

        }
        case 1:{
            int bvPrice = std::numeric_limits<int>::max();
            for (int i = 0; i < menu.size(); i++) {
                if (menu[i].getType() == BVG, (menu[i].getPrice() < bvPrice || (menu[i].getPrice()==bvPrice,menu[i].getId()<dishId))) {
                    bvPrice=menu[i].getPrice();
                    dishId=menu[i].getId();
                    foundDish=true;
                    bvgId=dishId;
                }
            }
        }
        case 2:{
            output.push_back(bvgId);

        }
    }

    if(foundDish){
        orderCount++;
        output.push_back(dishId);
    }

    return output;


}

Customer* SpicyCustomer:: clone(){
    return new SpicyCustomer(*this);
}

std::string SpicyCustomer:: toString() const{
    std::string s=this->getName()+",spc";
    return s;
}


//ALC
AlchoholicCustomer::AlchoholicCustomer(std::string name, int id):Customer(name,id),orderCount(0){}



//pulling all the ALC from the menu and sorting them
void AlchoholicCustomer:: sortALC(const std::vector<Dish> &menu){
    for (int i = 0; i < menu.size(); i++) {  //pulling all the ALC to specific vector
        if (menu[i].getType() == ALC)
            sortedALC.push_back(i);
    }
    if(!sortedALC.empty()) {    //bubble sorting the vector
        int tmp ;
        for (int j = 0; j < sortedALC.size(); j++)
            for (int i = 0; i < sortedALC.size() - j - 1; i++) {
                if (menu[sortedALC[i]].getPrice() > menu[sortedALC[i + 1]].getPrice() ||
                    (menu[sortedALC[i]].getPrice() == menu[sortedALC[i + 1]].getPrice(),menu[sortedALC[i]].getId() > menu[sortedALC[i + 1]].getId())) {
                    tmp = sortedALC[i];
                    sortedALC[i]=sortedALC[i+1];
                    sortedALC[i+1]=tmp;

                }
            }
    }
}


std::vector<int> AlchoholicCustomer:: order(const std::vector<Dish> &menu) {
    std::vector<int> output;
    if(orderCount==0) {
        sortALC(menu);
        if(!sortedALC.empty()){
            output.push_back(sortedALC[0]);
            orderCount++;
        }
        else
            orderCount=-1;
    }
    else if(orderCount>0,orderCount<sortedALC.size()){
        output.push_back(sortedALC[orderCount]);
        orderCount++;
    }

    return output;
}


Customer* AlchoholicCustomer:: clone(){
    return new AlchoholicCustomer(*this);
}

std::string AlchoholicCustomer:: toString() const{
    std::string s=this->getName()+",alc";
    return s;
}