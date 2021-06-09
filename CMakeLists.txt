cmake_minimum_required(VERSION 3.10)
project(ds_hw2)

set(CMAKE_CXX_STANDARD 11)
set(MySourcesList library2.h
        vector.h
        btree_23.h
        tree_node.h
        library.cpp
        library2.h
        set_node.h
        CarDealershipManager.cpp
        CarDealershipManager.h union_find.h agency.h car_node.h)

add_executable(main_tests main2.cpp ${MySourcesList})