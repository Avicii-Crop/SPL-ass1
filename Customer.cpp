//
// Created by achikamor on 06/11/18.
//

#include "Customer.h"
#include "Dish.h"
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
            if (menu[i].getType() == BVG, (menu[i].getPrice() > bvPrice || (menu[i].getPrice()==bvPrice,menu[i].getId()<bvId)) {
                bvPrice = menu[i].getPrice();
                bvId = menu[i].getId();
                bvg = i;
            }
        if(bvg!=-1,dish!=-1) {

            output.push_back(bvId);
            orders.push_back(bvg);
            output.push_back(TmpId);
            orders.push_back(dish);
        }

    return output;
}
}

std::string VegetarianCustomer:: toString() const{
    std::string s=std::to_string(this.getId())+" "+this->getName();
    return s;
}

//CHP
CheapCustomer::CheapCustomer(std::string name, int id):Customer(name,id){}

std::vector<int>CheapCustomer:: order(const std::vector<Dish> &menu){



    std::vector<int> output;
    if(this->orders.size()==0) {
        int tmpPrice = std::numeric_limits<int>::max();
        int tmpId = std::numeric_limits<int>::max();
        int dishIndex=0;
        for (int i = 0; i < menu.size(); i++) {
            if (menu[i].getPrice() <= tmpPrice)
                if (menu[i].getPrice() == tmpPrice, tmpId > menu[i].getId() || menu[i].getPrice() < tmpPrice) {
                    tmpId = menu[i].getId();
                    tmpPrice = menu[i].getPrice();
                    dishIndex=i;
                }


        }
        output.push_back(tmpId);
        orders.push_back(dishIndex);
    }
    return output;

}
std::string CheapCustomer:: toString() const{
    std::string s=std::to_string(this.getId())+" "+this->getName();
    return s;
}


//SPC
SpicyCustomer::SpicyCustomer(std::string name, int id):Customer(name,id){}

std::vector<int>SpicyCustomer:: order(const std::vector<Dish> &menu){
    std::vector<int> output;
    int dishIndex=-1;
    int dishId = std::numeric_limits<int>::max();
    if(orders.empty()) {
        int dishPrice = 0;

        for (int i = 0; i < menu.size(); i++) {
            if (menu[i].getPrice() > dishPrice || (menu[i].getPrice() == dishPrice, menu[i].getId() < dishId)) {
                dishPrice = menu[i].getPrice();
                dishId = menu[i].getId();
                dishIndex = i;
            }
        }
    }
    else if(orders.size()==1){
        int bvPrice = std::numeric_limits<int>::max();
        for (int i = 0; i < menu.size(); i++) {
            if (menu[i].getType() == BVG, (menu[i].getPrice() < bvPrice || (menu[i].getPrice()==bvPrice,menu[i].getId()<dishId)) {
                bvPrice=menu[i].getPrice();
                dishId=menu[i].getId();
                dishIndex=i;

            }



        }
    } else{
        output.push_back(menu[orders.back()].getId());
        orders.push_back(orders.back());

    }
    if(dishIndex!=-1){
        output.push_back(menu[dishIndex].getId());
        orders.push_back(dishIndex);
    }
    return output;


}

std::string SpicyCustomer:: toString() const{
    std::string s=std::to_string(this.getId())+" "+this->getName();
    return s;
}


//ALC
AlchoholicCustomer::AlchoholicCustomer(std::string name, int id):Customer(name,id){}

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


std::vector<int>AlchoholicCustomer:: order(const std::vector<Dish> &menu) {
    std::vector<int> output;
    int alcId = std::numeric_limits<int>::max();
    int alcPrice = std::numeric_limits<int>::max();
    int alcIndex = -1;
    if(orders.empty()) {
        sortALC(menu);
        if(sortedALC.empty()){
            orders.push_back(sortedALC[0]);
            output.push_back(menu[orders[0]].getId());
        }
    }
    else if(orders.size()<sortedALC.size()){
        orders.push_back(sortedALC[orders.size()]);
        output.push_back(menu[orders.back()].getId());

    }


}