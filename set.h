//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_SET_H
#define DS_HW2_SET_H

#include "shared_pointer.h"
#include "set_node.h"

template<typename T>
struct Set {
    SharedPointer<SetNode<T>> root;
    int size = 0;
    SharedPointer<T> value;
};

#endif //DS_HW2_SET_H
