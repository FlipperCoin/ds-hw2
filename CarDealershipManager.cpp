//
// Created by Itai on 09/06/2021.
//

#include "CarDealershipManager.h"
#include "union_find.h"

StatusType CarDealershipManager::AddAgency() {
    try {
        agencies.makeSet();
    }
    catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType CarDealershipManager::SellCar(int agencyID, int typeID, int k) {
    if (k <= 0 || agencyID < 0){
        return INVALID_INPUT;
    }

    try {
        Set<Agency> agency_set = agencies.find(agencyID);
        if(agency_set.value == nullptr){
            return FAILURE;
        }
        auto types_tree = agency_set.value->typesTree;
        auto sells_tree = agency_set.value->sellsTree;

        // find car node only by type from types tree
        CarData car_data;
        car_data.typeID = typeID;
        SharedPointer<TreeNode<CarNode>> carNode = types_tree->find({.carData = car_data});

        // if new type set sells to 0
        if (carNode.isEmpty() || !carNode->isLeaf()) {
            car_data.sells = 0;
        } else {
            car_data.sells = carNode->Value.carData.sells;
        }

        // update sells tree
        sells_tree->remove({.carData = car_data});
        types_tree->remove({.carData = car_data});

        car_data.sells += k;

        sells_tree->insert({.carData = car_data});
        types_tree->insert({.carData = car_data});
    }
    catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

StatusType CarDealershipManager::UniteAgencies(int agencyID1, int agencyID2) {
    if (agencyID1 < 0 || agencyID2 < 0) {
        return INVALID_INPUT;
    }

    try {
        auto a1 = agencies.find(agencyID1);
        auto a2 = agencies.find(agencyID2);

        if (a1.value == nullptr || a2.value == nullptr) {
            return FAILURE;
        }

        if (a1 == a2) return SUCCESS;

        agencies.unionSets(a1,a2);
    }
    catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

StatusType CarDealershipManager::GetIthSoldType(int agencyID, int i, int *res) {
    if (i < 0 || agencyID < 0 || res == nullptr){
        return INVALID_INPUT;
    }

    try {
        Set<Agency> agency = agencies.find(agencyID);
        if(agency.value == nullptr){
            return FAILURE;
        }

        auto foundTreeNode = agency.value->sellsTree->findByRank(i);
        if (foundTreeNode.isEmpty()) {
            return FAILURE;
        }

        auto sellsNode = foundTreeNode->Value;
        *res = sellsNode.carData.typeID;
    }
    catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

CarDealershipManager::CarDealershipManager() : agencies(init,unionAgencies) {}

SharedPointer<Agency> CarDealershipManager::init() {
    auto a = SharedPointer<Agency>(new Agency);
    a->typesTree = SharedPointer<BTree23<CarNode>>(new BTree23<CarNode>());
    a->sellsTree = SharedPointer<BTree23<SellsNode>>(new BTree23<SellsNode>());
    return a;
}

SharedPointer<Agency> CarDealershipManager::unionAgencies(SharedPointer<Agency> a1, SharedPointer<Agency> a2) {
    auto a = SharedPointer<Agency>(new Agency);
    a->typesTree = SharedPointer<BTree23<CarNode>>(new BTree23<CarNode>(a1->typesTree,a2->typesTree));
    a->sellsTree = SharedPointer<BTree23<SellsNode>>(new BTree23<SellsNode>(a1->sellsTree,a2->sellsTree));
    return a;
}
