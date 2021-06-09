//
// Created by Itai on 09/06/2021.
//

#include "CarDealershipManager.h"
#include "union_find.h"

StatusType CarDealershipManager::AddAgency() {
    agencies.makeSet(agencies.getNumberOfItems());
    return SUCCESS;
}

StatusType CarDealershipManager::SellCar(int agencyID, int typeID, int k) {
    if (k <= 0 || agencyID < 0){
        return INVALID_INPUT;
    }
    Set<Agency> agency_set = agencies.find(typeID);
    if(agency_set.value == nullptr){
        return FAILURE;
    }
    BTree23<CarNode> types_tree = agency_set.value->typesTree;
    BTree23<SellsNode> sells_tree = agency_set.value->sellsTree;

    // find car node only by type from types tree
    SharedPointer<CarData> car_data = SharedPointer<CarData>(new CarData());
    car_data->typeID = typeID;
    SharedPointer<TreeNode<CarNode>> carNode = types_tree.find({.carData = car_data});

    // update car node and sells tree
    sells_tree.remove({.carData = carNode->Value.carData});
    carNode->Value.carData->sells += k;
    sells_tree.insert({.carData= carNode->Value.carData});

    return SUCCESS;
}

StatusType CarDealershipManager::UniteAgencies(int agencyID1, int agencyID2) {
    return FAILURE;
}

StatusType CarDealershipManager::GetIthSoldType(int agencyID, int i, int *res) {
    return FAILURE;
}
