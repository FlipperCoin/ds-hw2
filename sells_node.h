//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_SELLS_NODE_H
#define DS_HW2_SELLS_NODE_H

#include "car_data.h"
#include "shared_pointer.h"
#include <string>

struct SellsNode {
    CarData carData;

    bool operator<(const SellsNode& other) const;
    bool operator>=(const SellsNode& other) const;
    bool operator==(const SellsNode& other) const;
    std::string str() const;
};
#endif //DS_HW2_SELLS_NODE_H
