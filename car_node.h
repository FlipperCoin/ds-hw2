//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_CAR_NODE_H
#define DS_HW2_CAR_NODE_H

#include "shared_pointer.h"
#include "car_data.h"

#include <string>

struct CarNode {
    CarData carData;

    bool operator<(const CarNode& other) const;
    bool operator>=(const CarNode& other) const;
    bool operator==(const CarNode& other) const;
    std::string str() const;
};

#endif //DS_HW2_CAR_NODE_H
