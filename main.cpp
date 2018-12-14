#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define BITQUANT 30000

bool goBack(char&);
int brainFkSM(char);

std::ifstream file;
char* bytes = new char[BITQUANT];
long dataPt = 0;
int bracketCnt = 0;

std::vector<char> codes;
std::vector<char>::iterator it;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: bad args" << std::endl;
        return -1;
    }

    file.open(argv[1]);
    
    char c;
    while (file.get(c)) {
        codes.push_back(c);
    }

    for (it = codes.begin(); it != codes.end(); it++) {
        brainFkSM(*it);
    }

    std::cout << std::endl;

    file.close();

    return 0;
}

int brainFkSM(char c) {
    switch (c) {
        case '>':
            if (++dataPt < BITQUANT) { return 0; }
            dataPt--;
            return 1;
        case '<':
            if (--dataPt >= 0) { return 0; }
            dataPt++;
            return 1;
        case '+':
            bytes[dataPt]++;
            return 0;
        case '-':
            bytes[dataPt]--;
            return 0;
        case '.':
            std::cout << bytes[dataPt];
            return 0;
        case ',':
            std::cin.get(bytes[dataPt]);
            return 0;
        case '[':
            if (bytes[dataPt]) {
                return 0;
            }
            bracketCnt++;
            while (*(++it)) {
                if (*it == '[') {
                    bracketCnt++;
                } else if (*it == ']') {
                    bracketCnt--;
                    if (bracketCnt == 0) {
                        break;
                    }
                }
            }
            return 0;   
        case ']':
            if (!bytes[dataPt]) {
                return 0;
            }
            bracketCnt--;
     
            while(*(--it)) {
                if (*it == ']') {
                    bracketCnt--;
                } else if (*it == '[') {
                    bracketCnt++;
                    if (bracketCnt == 0) {
                        break;
                    }
                }
            }
            return 0;
        default:
            return 0;
    }
}

bool goBack(char &c) {
    file.seekg(-2, file.cur);   
    return file.get(c) ? true : false;
}
