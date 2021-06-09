//
// Created by Itai on 09/06/2021.
//

#include "sells_node.h"

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
