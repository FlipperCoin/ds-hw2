#ifndef DS_EX1_TREE23_H
#define DS_EX1_TREE23_H

#include "tree_node.h"
#include "shared_pointer.h"

#include <iostream>
#include <string>
#include <exception>
#include "vector.h"

using std::cout;
using std::endl;
using std::string;

/**
 * Generic implementation of a 2-3 tree
 * @tparam DataType type supporting operators '<','>=','==' and method str() for print only
 */
template <typename DataType>
class BTree23 {
private:
    /**
     * root of the tree
     */
    SharedPointer<TreeNode<DataType>> root = SharedPointer<TreeNode<DataType>>();
    /**
     * Smallest leaf (child), head of the leaves linked-list
     */
    SharedPointer<TreeNode<DataType>> child = SharedPointer<TreeNode<DataType>>();

    void printTree(SharedPointer<TreeNode<DataType>> node, bool is_right_most = true, const string& prefix = "") const;
    void printMidNode(const SharedPointer<TreeNode<DataType>> &node) const;
    void fix_insert(SharedPointer<TreeNode<DataType>> node);
    void fix_remove(SharedPointer<TreeNode<DataType>> node);
    void createRow(Vector<SharedPointer<TreeNode<DataType>>> &nodes, int k, int r) const;
    static bool compare(const TreeNode<DataType>& node1, const TreeNode<DataType>& node2);
    void link(SharedPointer<TreeNode<DataType>> node);
    void copy(SharedPointer<BTree23<DataType>> t);
    void copy(SharedPointer<BTree23<DataType>> t1,SharedPointer<BTree23<DataType>> t2);

public:
    /**
     * Inits tree with given root (defaults to empty tree)
     * for n being the number of nodes in the given tree, inits the tree in O(n)
     * @param root root of the tree to copy
     */
    explicit BTree23(SharedPointer<TreeNode<DataType>> root = SharedPointer<TreeNode<DataType>>());
    /**
     * Inits tree with ascending values from 0 to n-1 in O(n)
     * Implemented for DataType of type int only (see zero_grade_type_node.cpp)
     * @param n amount of leaves wanted
     */
    explicit BTree23(int n);
    /**
     * Joins 2 trees into a single tree in O(m1+m2)
     * @param t1 tree with m1 leaves
     * @param t2 tree with m2 leaves
     */
    BTree23(SharedPointer<BTree23> t1, SharedPointer<BTree23> t2);

    /**
     * Insert the given value to the tree as a leaf in O(log(n))
     * @param value the value to insert
     * @return pointer to the leaf if was inserted,
     * otherwise (value was already in the tree) returns an empty shared pointer
     */
    SharedPointer<TreeNode<DataType>> insert(DataType value);
    /**
     * Remove the leaf corresponding to the given value from the tree in O(log(n))
     * @param value the value to remove
     * @return always an empty shared pointer
     */
    SharedPointer<TreeNode<DataType>> remove(DataType value);
    /**
     * Search for a leaf containing the given value in O(log(n))
     * @param value the value to search for
     * @param node node to start the search from, defaults to the root of the tree
     * @param insertUpdateOnPath should the method update on its path the minimum child in each node and inc ranks by 1
     * @param removeUpdateOnPath should the method lower the ranks by 1 of each node in its path
     * @return the leaf if found, last parent on the path otherwise
     */
    SharedPointer<TreeNode<DataType>> find(DataType value,
                                           SharedPointer<TreeNode<DataType>> node = SharedPointer<TreeNode<DataType>>(),
                                           bool insertUpdateOnPath = false,
                                           bool removeUpdateOnPath = false) const;

    /**
     * @return the node referred by i
     */
    SharedPointer<TreeNode<DataType>> findByRank(int i, SharedPointer<TreeNode<DataType>> current = SharedPointer<TreeNode<DataType>>()) const;

    /**
     * @return is the tree empty (without any leaves)
     */
    bool isEmpty();
    /**
     * @return the smallest child (leaf) in the tree, head of the linked-list of all leaves
     */
    SharedPointer<TreeNode<DataType>> getSmallestChild() const;
    /**
     * Prints a graph of the tree to stdout
     */
    void printTree() const;
    /**
     * Compare this tree with other
     * @param other the tree to compare with
     * @return are the trees equal
     */
    bool operator==(const BTree23<DataType>& other) const;
};

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::insert(DataType value) {
    if (root.isEmpty()) {
        root = SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(value)); // add new tree node
        child = root;
        return root;
    }

    if (root->isLeaf()) {
        // if already in tree
        if (root->Value == value) return SharedPointer<TreeNode<DataType>>();

        SharedPointer<TreeNode<DataType>> new_root(new TreeNode<DataType>(DataType()));
        SharedPointer<TreeNode<DataType>> new_node(new TreeNode<DataType>(value, new_root.rawPointer()));
        root->Parent = new_root.rawPointer();
        new_root->Sons = 2;

        if(value < root->Value){
            new_root->Children[0] = new_node;
            new_root->Children[1] = root;
            new_root->Indices[0] = root->Value;
            //fix linked list connections
            new_node->Next = new_root->Children[1].rawPointer();
            new_root->Children[1]->Previous = new_node.rawPointer();
        }
        else {
            new_root->Children[0] = root;
            new_root->Children[1] = new_node;
            new_root->Indices[0] = new_node->Value;
            //fix linked list connections
            new_root->Children[0]->Next = new_node.rawPointer();
            new_node->Previous = new_root->Children[0].rawPointer();
        }
        new_root->Value = new_root->Children[0]->Value;
        root = new_root;
        root->Rank = 2;
        child = root->Children[0];
        return new_node;
    }

    SharedPointer<TreeNode<DataType>> place = find(value, root, true);
    if (place->isLeaf()) { // value is already in tree!
        return SharedPointer<TreeNode<DataType>>();
    }
    // else - insert new node in father
    SharedPointer<TreeNode<DataType>> new_node =
            SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(value, place.rawPointer()));
    place->insertValue(new_node); // also ups the rank in 1
    if (value < child->Value) child = new_node;
    if(place->Sons != 3) fix_insert(place);
    return new_node;
}

template<typename DataType>
void BTree23<DataType>::fix_insert(SharedPointer<TreeNode<DataType>> node) {
    auto first_half = SharedPointer<TreeNode<DataType>>(
            new TreeNode<DataType>(node->Children[0], node->Children[1], node->Indices[0]));
    auto second_half = SharedPointer<TreeNode<DataType>>(
            new TreeNode<DataType>(node->Children[2], node->Children[3], node->Indices[2]));
    if (node->Parent == nullptr){
        root = SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(first_half, second_half,node->Indices[1]));
        return;
    }
    node->Parent->swap(first_half, second_half,node->Indices[1]);
    if (node->Parent->Sons == 4) {
        auto p = node->getSharedParent();
        if (p.isEmpty()) p = root;
        fix_insert(p);
    }
}

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::remove(DataType value) {
    SharedPointer<TreeNode<DataType>> node = find(value, root);
    if (node.isEmpty()) return node; // returns NULL

    if (!(node->isLeaf())) { // check if the value doesn't exist
        return SharedPointer<TreeNode<DataType>>(); // what to give back ????
    }
    if (node->Parent == nullptr) {
        root = SharedPointer<TreeNode<DataType>>();
        child = SharedPointer<TreeNode<DataType>>();
        return root;
    }

    // dec rank by 1
    find(value, root,false,true);

    auto p = node->getSharedParent();
    if (p.isEmpty()) p = root;

    if (child == node) {
        child = p->Children[1];
    }

    SharedPointer<TreeNode<DataType>> v_node = p;
    v_node->removeSon(value);
    // recursive function here!!
    fix_remove(v_node);
    return SharedPointer<TreeNode<DataType>>();
}

template<typename DataType>
void BTree23<DataType>::fix_remove(SharedPointer<TreeNode<DataType>> v_node) {
    if (v_node->Sons != 1) return;

    if (v_node == root.rawPointer()) {
        root = v_node->Children[0];
        root->Parent = nullptr;
        return;
    }
    // v_node has one son but he's not root
    if (v_node->Parent->Children[0] == v_node) { // if this is first child - id = 0
        if (v_node->Parent->Children[1]->Sons == 3) v_node->borrow(0, 1); // borrow from second child
        else v_node->combine(0, 1); // combine with second child
    }
    else if (v_node->Parent->Children[1] == v_node) { // if this is middle child - id = 1
        if (v_node->Parent->Children[0]->Sons == 3) v_node->borrow(1, 0); // borrow from first child
        else if (v_node->Parent->Sons == 3) { // if parent has three sons
            if (v_node->Parent->Children[2]->Sons == 3) v_node->borrow(1, 2); // borrow from third side
            else v_node->combine(1, 2); // combine with third side

        }
        else {
            v_node->combine(1, 0);
        }
    }
    else { // this is the third child - id = 2
        if (v_node->Parent->Children[1]->Sons == 3) v_node->borrow(2, 1);
        else v_node->combine(2, 1);
    }
    auto p = v_node->getSharedParent();
    if (p.isEmpty()) p = root;
    fix_remove(p);
}

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::find(DataType value,
                                                          SharedPointer<TreeNode<DataType>> node,
                                                          bool insertUpdateOnPath,
                                                          bool removeUpdateOnPath) const {
    if (root.isEmpty()) {
        return root; // returning null
    }

    // first run, init from root
    if (node.isEmpty()) {
        node = root;
    }

    // reached a leaf, its either the wanted value or the value is not in the tree
    if (node->isLeaf()) {
        // return an empty pointer indicating the value's not in the tree
        // and the parent should be returned instead
        if (!(value == node->Value)) {
            return SharedPointer<TreeNode<DataType>>();
        }

        // return the found leaf with the wanted value
        return node;
    }

    // if find should update on path the smallest value in the node's subtrees & inc rank by 1
    if (insertUpdateOnPath) {
        node->Rank += 1;
        if (value < node->Value)
            node->Value = value;
    }
    if (removeUpdateOnPath) {
        node->Rank -= 1;
    }

    // recall find on correct subtree
    SharedPointer<TreeNode<DataType>> found;
    for (int i = 0; i < node->Sons-1; i++) {
        // if not less than this part, check if it was the last part
        if (!(value < node->Indices[i])) {
            if (i == node->Sons-2) {
                // definitely larger equals node->Indices[node->Sons-1])
                found = find(value, node->Children[i+1], insertUpdateOnPath, removeUpdateOnPath);
            }

            // if not the last, continue in the loop
            continue;
        };

        // value is in this part, try find and break
        found = find(value, node->Children[i], insertUpdateOnPath, removeUpdateOnPath);
        break;
    }

    // if didn't find, return parent
    if (found.isEmpty()) {
        return node;
    }

    // return leaf (or parent from below)
    return found;
}


template<typename DataType>
void BTree23<DataType>::printTree() const {
    printTree(root);
}
template<typename DataType>
void BTree23<DataType>::printTree(SharedPointer<TreeNode<DataType>> node, bool is_right_most, const string& prefix) const {
    if (node.isEmpty()) {
        cout << "[]" << endl;
        return;
    }

    if (node->isLeaf()) {
        cout << node->Value.str() << endl;
        return;
    }

    printMidNode(node);
    cout << "-";
    string padding = "";
    for (int i = 0; i < ((node->Sons-1)*2); i++) padding += " ";
    printTree(node->Children[node->Sons-1], true, prefix + padding + "| ");
    for (int i = node->Sons-2; i > 0; i--) {
        cout << prefix << padding << "|-";
        printTree(node->Children[i], false, prefix + padding + "| ");
    }
    cout << prefix << padding << "\\-";
    printTree(node->Children[0], false, prefix + padding + "  ");
}

template<typename DataType>
void BTree23<DataType>::printMidNode(const SharedPointer<TreeNode<DataType>> &node) const {
    cout << "[";
    for (int i = 0; i < node->Sons-1; i++) {
        cout << node->Indices[i].str();
        if (i != node->Sons-2) {
            cout << ",";
        }
    }
    cout << "]";
}

template<typename DataType>
void BTree23<DataType>::link(SharedPointer<TreeNode<DataType>> node) {
    if (node->isLeaf()) {
        if (child.isEmpty()) {
            child = node;
        }
        return;
    }

    DataType min;
    for (int i = 0; i < node->Sons; i++) {
        node->Children[i]->Parent = node.rawPointer();
        link(node->Children[i]);

        auto val = node->Children[i]->Value;
        if (i == 0) min = val;
        else if (node->Children[i]->Value < min) min = val;
    }

    node->Value = min;
}

template<typename DataType>
BTree23<DataType>::BTree23(SharedPointer<TreeNode<DataType>> root) : root(root), child(SharedPointer<TreeNode<DataType>>()) {
    if (!root.isEmpty()) {
        link(root);
    }
}

template<typename DataType>
bool BTree23<DataType>::operator==(const BTree23<DataType> &other) const {
    if (root.isEmpty()) {
        return other.root.isEmpty();
    }
    else if (other.root.isEmpty()) {
        return false;
    }

    return compare(*root, *(other.root));
}

template<typename DataType>
bool BTree23<DataType>::compare(const TreeNode<DataType> &node1, const TreeNode<DataType> &node2) {
    if (node1.Sons != node2.Sons) return false;
    if (node1.Value != node2.Value) return false;

    // hard to check if parent is valid, this is a best effort for now
    if (node1.Parent == nullptr) {
        if (node1.Parent != node2.Parent) return false;
    }
    else if (node2.Parent == nullptr) return false;
    else {
        if (node1.Parent->Sons != node2.Parent->Sons) return false;
        if (node1.Parent->Value != node2.Parent->Value) return false;
    }

    for (int i = 0; i < node1.Sons-1; i++) {
        if (node1.Indices[i] != node2.Indices[i]) {
            return false;
        }
    }

    for (int i = 0; i < node1.Sons; i++) {
        if (!compare(*(node1.Children[i]),*(node2.Children[i]))) {
            return false;
        }
    }

    return true;
}

/**
 * Not implemented for generic DataType!
 * @tparam DataType
 * @param n
 */
template<typename DataType>
BTree23<DataType>::BTree23(int n) {throw std::exception();}

template<typename DataType>
void BTree23<DataType>::createRow(Vector<SharedPointer<TreeNode<DataType>>> &nodes, int k, int r) const {
    for (int i = r; i < r + k; i+=2) {
        SharedPointer<TreeNode<DataType>> parent;

        // if only 3 left, add a parent to 3 sons
        if ((r+k - i) == 3) {
            parent = SharedPointer<TreeNode<DataType>>(
                    new TreeNode<DataType>(
                            nodes[i],
                            nodes[i+1],
                            nodes[i+2],
                            nodes[i+1]->Value,
                            nodes[i+2]->Value
                    ));
            // use the Value field in non-leaves to save the lowest value under it
            parent->Value = nodes[i]->Value;
            nodes.add(parent);
            nodes[i]->Parent = parent.rawPointer();
            nodes[i+1]->Parent = parent.rawPointer();
            nodes[i+2]->Parent = parent.rawPointer();
            break;
        }
            // add a parent with 2 sons
        else {
            parent = SharedPointer<TreeNode<DataType>>(
                    new TreeNode<DataType>(
                            nodes[i],
                            nodes[i+1],
                            nodes[i+1]->Value
                    ));
            parent->Value = nodes[i]->Value;
        }

        nodes.add(parent);
        nodes[i]->Parent = parent.rawPointer();
        nodes[i+1]->Parent = parent.rawPointer();
    }
}

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::getSmallestChild() const {
    return child;
}

template<typename DataType>
bool BTree23<DataType>::isEmpty() {
    return root.isEmpty();
}

template<typename DataType>
BTree23<DataType>::BTree23(SharedPointer<BTree23> t1, SharedPointer<BTree23> t2) {
    auto r1 = t1->root;
    auto r2 = t2->root;

    if (r1.isEmpty()) copy(t2);
    else if (r2.isEmpty()) copy(t1);
    else copy(t1,t2);
}

template<typename DataType>
SharedPointer<TreeNode<DataType>> BTree23<DataType>::findByRank(int i, SharedPointer<TreeNode<DataType>> current) const {
    if(current.isEmpty()) current = root;

    if (root.isEmpty() || (root->isLeaf() && i > 0)) return SharedPointer<TreeNode<DataType>>();

    if(current->isLeaf()){
        return current;
    }

    for (int j = 0; j < current->Sons; ++j) {
        if(i < current->Children[j]->Rank){
            return findByRank(i, current->Children[j]);
        }
        else if( j != current->Sons-1){
            i -= current->Children[j]->Rank;
        }
        else{
            return SharedPointer<TreeNode<DataType>>();
        }
    }
}

template<typename DataType>
void BTree23<DataType>::copy(SharedPointer<BTree23<DataType>> t) {
    if (t.isEmpty() || t->root.isEmpty()) return;

    int m = t->root->Rank;
    Vector<SharedPointer<TreeNode<DataType>>> nodes(2*m);

    auto iter = t->child.rawPointer();
    for (int i = 0; i < m; i++) {
        nodes.add(SharedPointer<TreeNode<DataType>>((new TreeNode<DataType>(iter->Value))));
        iter = iter->Next;

        if (i != 0) {
            nodes[i-1]->Next = nodes[i].rawPointer();
            nodes[i]->Previous = nodes[i-1].rawPointer();
        }
    }

    child = nodes[0];

    // loop row by row, from the bottom up
    // each time creating the row's parents and linking them
    int k = m;
    int r = 0;
    while (r+k - r > 1) {
        createRow(nodes, k, r);
        r += k;
        k /= 2; // rounding down is a wanted behaviour, in case of 3 sons in the end
    }

    root = nodes[r];
}

template<typename DataType>
void BTree23<DataType>::copy(SharedPointer<BTree23<DataType>> t1, SharedPointer<BTree23<DataType>> t2) {
    int m1 = t1->root->Rank;
    int m2 = t2->root->Rank;

    int m = m1+m2;
    Vector<SharedPointer<TreeNode<DataType>>> nodes(2*m);

    auto iter1 = t1->child.rawPointer();
    auto iter2 = t2->child.rawPointer();

    for (int i = 0; i < m; i++) {
        if (iter1 == nullptr) {
            if (iter2 == nullptr) {
                break;
            }

            nodes.add(SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(iter2->Value)));
            iter2 = iter2->Next;
        }
        else if (iter2 == nullptr || iter1->Value < iter2->Value) {
            nodes.add(SharedPointer<TreeNode<DataType>>((new TreeNode<DataType>(iter1->Value))));
            iter1 = iter1->Next;
        }
        else {
            nodes.add(SharedPointer<TreeNode<DataType>>(new TreeNode<DataType>(iter2->Value)));
            iter2 = iter2->Next;
        }

        if (i != 0) {
            nodes[i-1]->Next = nodes[i].rawPointer();
            nodes[i]->Previous = nodes[i-1].rawPointer();
        }
    }

    child = nodes[0];

    // loop row by row, from the bottom up
    // each time creating the row's parents and linking them
    int k = m;
    int r = 0;
    while (r+k - r > 1) {
        createRow(nodes, k, r);
        r += k;
        k /= 2; // rounding down is a wanted behaviour, in case of 3 sons in the end
    }

    root = nodes[r];
}

#endif //DS_EX1_TREE23_H
