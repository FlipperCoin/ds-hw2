//
// Created by Itai on 09/06/2021.
//

#include "car_node.h"
#include <sstream>

bool CarNode::operator<(const CarNode &other) const {
    return carData.typeID < other.carData.typeID;
}

bool CarNode::operator>=(const CarNode &other) const {
    return !(*this<other);
}

bool CarNode::operator==(const CarNode &other) const {
    return carData.typeID == other.carData.typeID;
}

std::string CarNode::str() const {
    std::stringstream s;
    s << "(" << carData.typeID << "," << carData.sells << ")";
    return s.str();
}