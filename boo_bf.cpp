#include "boo_bf.h"

RESULTS bfRight(long &dataPtr, int moves) {
    if (dataPtr + moves > BITQUANT) {
        return OVER_PTR;
    }
    dataPtr += moves;
    return SUCCESS;
}

RESULTS bfLeft(long &dataPtr, int moves) {
    if (dataPtr - moves < 0) {
        return UNDER_PTR;
    }
    dataPtr -= moves;
    return SUCCESS;
}

RESULTS bfPlus(char &cell, int incr) {
    cell += incr;
    return SUCCESS;
}

RESULTS bfMinus(char &cell, int decr) {
    cell -= decr;
    return SUCCESS;
}

RESULTS bfInput(char &cell) {
    std::cin.get(cell);
    return SUCCESS;
}

RESULTS bfOutput(char cell) {
    std::cout << cell;
    return SUCCESS;
}

RESULTS bfLoop(char *bytes, long &dataPtr, std::vector<RESULTS_FN> fns) {
    while (bytes[dataPtr]) {
        for (auto fn: fns) { fn(); }
    }
}

RESULTS bfMacroReset(char &cell) {
   cell = 0;
   return SUCCESS;
}
