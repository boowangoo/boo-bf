#pragma once

#include <functional>
#include <iostream>
#include <vector>

#define BITQUANT 30000

enum resultCodes {
    SUCCESS = 0,
    OVER_PTR,
    UNDER_PTR,
};
typedef enum resultCodes RESULTS;

RESULTS bfRight(long &dataPtr, int moves = 1);
RESULTS bfLeft(long &dataPtr, int moves = 1);
RESULTS bfPlus(char &cell, int incr = 1);
RESULTS bfMinus(char &cell, int decr = 1);
RESULTS bfInput(char &cell);
RESULTS bfOutput(char cell);
RESULTS bfLoop(char *bytes, long &dataPtr, std::vector<std::function<RESULTS()>> fns);
RESULTS bfMacroReset(char &cell);
