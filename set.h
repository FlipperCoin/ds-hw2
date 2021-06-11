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

    bool operator==(const Set& other) const;
};

template<typename T>
bool Set<T>::operator==(const Set &other) const {
    return root == other.root;
}

#endif //DS_HW2_SET_H
