//
// Created by achikamor on 06/11/18.
//

#include "../include/Dish.h"
//constuctor
Dish::Dish(int d_id, std::string d_name, int d_price, DishType d_type):id(d_id),name(d_name),price(d_price),type(d_type){}
//Destructor
//Dish::~Dish(){}
//Copy Constructor
//Dish::Dish(const Dish& other): id(other.getId()),name(other.getName()),price(other.getPrice()),type(other.getType()){}
//Copy Operator NOT FINISHED!!!
//void Dish::operator=(const Dish& other){
// if(this!= &other){
//   delete this;
//   this=new Dish(other);
//    }
//}



//getters
int Dish::getId() const {
    return  id;
}

std::string Dish::getName() const{
    return name;
}

int Dish::getPrice() const{
    return price;
}
DishType Dish::getType() const{
    return type;
}

std::string Dish::tostring(){
    std::string output=this->getName()+" ";
    if(this->getType()==VEG)
        output=output+"VEG" + " ";
    if(this->getType()==SPC)
        output=output+"SPC" + " ";
    if(this->getType()==BVG)
        output=output+"BVG" + " ";
    if(this->getType()==ALC)
        output=output+"ALC" + " ";
    output=output+std::to_string(this->getPrice())+" "+std::to_string(this->getPrice())+"NIS";
    return output;

}