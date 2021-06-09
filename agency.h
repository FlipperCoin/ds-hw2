//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_AGENCY_H
#define DS_HW2_AGENCY_H

#include "btree_23.h"
#include "car_node.h"

struct Agency {
    BTree23<CarNode> cars_tree = BTree23<CarNode>();
};

#endif //DS_HW2_AGENCY_H
