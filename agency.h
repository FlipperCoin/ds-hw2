//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_AGENCY_H
#define DS_HW2_AGENCY_H

#include "btree_23.h"
#include "car_node.h"
#include "sells_node.h"

struct Agency {
    BTree23<CarNode> typesTree = BTree23<CarNode>();
    BTree23<SellsNode> sellsTree = BTree23<SellsNode>();
};

#endif //DS_HW2_AGENCY_H
