#pragma once

#include <functional>
#include <iostream>
#include <vector>

#define BITQUANT 30000

enum resultCodes {
    SUCCESS = 0,
    OVER_PTR,
    UNDER_PTR,
    NO_BRACKET_PAIR
};
typedef enum resultCodes RESULTS;

typedef std::function<RESULTS()> RESULTS_FN;

RESULTS bfRight(long &dataPtr, int moves = 1);
RESULTS bfLeft(long &dataPtr, int moves = 1);
RESULTS bfPlus(char &cell, int incr = 1);
RESULTS bfMinus(char &cell, int decr = 1);
RESULTS bfInput(char &cell);
RESULTS bfOutput(char cell);
RESULTS bfLoop(char *bytes, long &dataPtr, std::vector<RESULTS_FN> fns);
RESULTS bfMacroReset(char &cell);
