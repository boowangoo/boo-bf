#include <fstream>
#include <map>

#include "boo_bf.h"

typedef std::vector<char>::iterator iterator;

void parse(iterator&, std::vector<RESULTS_FN>&);
int checkRepeats(iterator&);
RESULTS_FN checkBrackets(iterator&, std::vector<RESULTS_FN>&);

std::ifstream file;
char* bytes = new char[BITQUANT];
long dataPtr = 0;

std::vector<char> codes;
std::map<iterator, iterator> brackets;

std::vector<RESULTS_FN> calls;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: bad args" << std::endl;
        return -1;
    }

    file.open(argv[1]);
    
    std::vector<iterator> lBrackets;
    char c;
    while (file.get(c)) {
        codes.push_back(c);
        if (c == '[') {
            lBrackets.push_back(codes.end() - 1);
        } else if (c == ']' && lBrackets.size() > 0) {
            iterator lBrack = lBrackets.back();
            lBrackets.pop_back();
            brackets.insert(lBrack, codes.end() - 1);
        }
    }

    for (auto it = codes.begin(); it != codes.end(); it++) {
        parse(it, calls);
    }

    for (auto call: calls) {
        call();
    }

    std::cout << std::endl;

    file.close();

    return 0;
}

void parse(iterator &it, std::vector<RESULTS_FN> &calls) {
    switch (*it) {
        case '>':
            calls.push_back([&] { return bfRight(dataPtr, checkRepeats(it)); });
            break;
        case '<':
            calls.push_back([&] { return bfLeft(dataPtr, checkRepeats(it)); });
            break;
        case '+':
            calls.push_back([&] { return bfPlus(bytes[dataPtr], checkRepeats(it)); });
            break;
        case '-':
            calls.push_back([&] { return bfMinus(bytes[dataPtr], checkRepeats(it)); });
            break;
        case '.':
            calls.push_back([] { return bfOutput(bytes[dataPtr]); });
            break;
        case ',':
            calls.push_back([&] { return bfInput(bytes[dataPtr]); });
            break;
        case '[':
            calls.push_back(checkBrackets(it, calls));
            break;
        case ']':
        default:
            break;
    }
}

RESULTS_FN checkBrackets(iterator &it, std::vector<RESULTS_FN> &calls) {
    if ( brackets.find(it) == brackets.end() ) {
        return [&] { return NO_BRACKET_PAIR; };
    }

    auto start = it + 1;
    auto end = brackets[it];

    if (start + 1 == end && (*start = '+' || *start == '-')) {
        return [&] {
            bytes[dataPtr] = 0;
            return SUCCESS;
        };
    }

    std::vector<RESULTS_FN> brackCalls;
    for (auto it = start; it != end; it++) {
        parse(it, brackCalls);
    }

    return [&] {
        RESULTS result;
        for (auto call: brackCalls) {
            result = call();
            if (result != SUCCESS) { return result; }
        }
        return SUCCESS;
    };
}

int checkRepeats(iterator &it) {
    int i = 1;
    while (*(it + i) == *it) {
        i++;
    }
    it += i - 1;
    return i;
}
