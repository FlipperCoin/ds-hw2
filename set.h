//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_SET_H
#define DS_HW2_SET_H

#include "shared_pointer.h"
#include "node.h"

template<typename T>
struct Set {
    SharedPointer<Node<T>> root = SharedPointer<Node<T>>(0);
    int size = 0;
};

#include "vector.h"
#include "shared_pointer.h"
#include "node.h"

#endif //DS_HW2_SET_H
