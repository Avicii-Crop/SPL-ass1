//
// Created by achikamor on 13/11/18.
//

#ifndef SPL_ASS1_DISH_H
#define DISH_H_

#include <string>

enum DishType{
    VEG, SPC, BVG, ALC
};

class Dish{
public:
    Dish(int d_id, std::string d_name, int d_price, DishType d_type);
    virtual ~Dish();
    Dish(const Dish& other);
    void operator=(const Dish& other);
    int getId() const;
    std::string getName() const;
    int getPrice() const;
    DishType getType() const;
private:
    const int id;
    const std::string name;
    const int price;
    const DishType type;
};


#endif
