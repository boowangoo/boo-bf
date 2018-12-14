#include <fstream>

#include "boo_bf.h"

bool goBack(char&);
void parse(std::vector<char>::iterator&, std::vector<std::function<RESULTS()>>&);
void checkBrackets(std::vector<char>::iterator &, std::vector<std::function<RESULTS()>>&);
int checkRepeats(std::vector<char>::iterator&);

std::ifstream file;
char* bytes = new char[BITQUANT];
long dataPtr = 0;
int bracketCnt = 0;

std::vector<char> codes;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: bad args" << std::endl;
        return -1;
    }

    file.open(argv[1]);
    
    std::vector<int> lBrackPos;
    char c;
    while (file.get(c)) {
        codes.push_back(c);
    }

    std::vector<std::function<RESULTS()>> calls;

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

void parse(std::vector<char>::iterator &it, std::vector<std::function<RESULTS()>> &calls) {
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
            break;
        case ']':
            break;
        default:
            break;
    }
}

void checkBrackets(std::vector<char>::iterator &it, std::vector<std::function<RESULTS()>> &calls) {
    if (it + 1 < codes.end()) {
        auto start = ++it;
    }
    int i = 1;
    int bracketCnt = 1;
}

int checkRepeats(std::vector<char>::iterator &it) {
    int i = 1;
    while (*(it + i) == *it) {
        i++;
    }
    it += i - 1;
    return i;
}

bool goBack(char &c) {
    file.seekg(-2, file.cur);   
    return file.get(c) ? true : false;
}
