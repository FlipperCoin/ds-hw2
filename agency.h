//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_AGENCY_H
#define DS_HW2_AGENCY_H

#include "btree_23.h"
#include "car_node.h"
#include "sells_node.h"

struct Agency {
    SharedPointer<BTree23<CarNode>> typesTree = SharedPointer<BTree23<CarNode>>();
    SharedPointer<BTree23<SellsNode>> sellsTree = SharedPointer<BTree23<SellsNode>>();
};

#endif //DS_HW2_AGENCY_H
