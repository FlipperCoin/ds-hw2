//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_CAR_NODE_H
#define DS_HW2_CAR_NODE_H

#include "shared_pointer.h"
#include "car_data.h"

struct CarNode {
    SharedPointer<CarData> carData;

    bool operator<(const CarNode& other) const;
    bool operator>=(const CarNode& other) const;
    bool operator==(const CarNode& other) const;
};

bool CarNode::operator<(const CarNode &other) const {
    return carData->typeID < other.carData->typeID;
}

bool CarNode::operator>=(const CarNode &other) const {
    return !(*this<other);
}

bool CarNode::operator==(const CarNode &other) const {
    return carData->typeID == other.carData->typeID;
}

#endif //DS_HW2_CAR_NODE_H
