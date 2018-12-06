#ifndef COMMON_H_
#define COMMON_H_

#include "ethsnarks.hpp"

ethsnarks::ProtoboardT getProtoboard(const char* assignment);

/**
 * Needs to be overridden and return the total number of input variables.
 */
uint64_t inputSize();

/**
 * Needs to be overridden and return the total number of output variables.
 */
uint64_t outputSize();

// COMMON_H_
#endif

