//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_SET_NODE_H
#define DS_HW2_SET_NODE_H

#include "shared_pointer.h"
#include "vector.h"

template<typename T>
struct SetNode {
    SharedPointer<SetNode<T>> parent = SharedPointer<SetNode<T>>();
    int size;
    SharedPointer<T> value;
};

#endif //DS_HW2_SET_NODE_H
