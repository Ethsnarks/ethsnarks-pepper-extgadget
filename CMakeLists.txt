cmake_minimum_required(VERSION 2.8)
project(ethsnarks-pepper-gadgets)
add_subdirectory(ethsnarks ethsnarks EXCLUDE_FROM_ALL)

add_executable(gadget0 sha256_bridge.cpp)
target_link_libraries(gadget0 ethsnarks_gadgets gmpxx)

add_executable(gadget1 pedersen_bridge.cpp)
target_link_libraries(gadget1 ethsnarks_jubjub gmpxx)
