//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_SELLS_NODE_H
#define DS_HW2_SELLS_NODE_H

#include "car_data.h"
struct SellsNode {
    SharedPointer<CarData> carData;

    bool operator<(const SellsNode& other) const;
    bool operator>=(const SellsNode& other) const;
    bool operator==(const SellsNode& other) const;
};

bool SellsNode::operator<(const SellsNode &other) const {
    return carData->sells < other.carData->sells ||
            ((carData->sells == other.carData->sells) && carData->typeID < other.carData->typeID);
}

bool SellsNode::operator>=(const SellsNode &other) const {
    return !(*this<other);
}

bool SellsNode::operator==(const SellsNode &other) const {
    return carData->sells == other.carData->sells && carData->typeID == other.carData->typeID;
}

#endif //DS_HW2_SELLS_NODE_H
