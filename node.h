//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_NODE_H
#define DS_HW2_NODE_H

#include "shared_pointer.h"

template<typename T>
struct Node {
    SharedPointer<Node<T>> parent = SharedPointer<Node<T>>();
};

#include "vector.h"
#include "shared_pointer.h"

#endif //DS_HW2_NODE_H
