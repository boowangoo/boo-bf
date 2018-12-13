#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

#define BITQUANT 30000

bool goBack(char&);
int brainFkSM(char);

std::ifstream file;
char* bytes = new char[BITQUANT];
unsigned int dataPt = 0;
int bracketCnt = 0;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: bad args" << std::endl;
        return -1;
    }

    file.open(argv[1]);
    
    char c;
    while (file.get(c)) {
        brainFkSM(c);
    }

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
            if (bytes[dataPt] == 255) {
                bytes[dataPt] = 0;
            } else {
                bytes[dataPt]++;
            }
            return 0;
        case '-':
            if (bytes[dataPt] == 0) {
                bytes[dataPt] = 255;
            } else {
                bytes[dataPt]--;
            }
            return 0;
        case '.':
            std::cout << bytes[dataPt];
            return 0;
        case ',':
            // TODO: LAST
            return 0;
        case '[':
            if (bytes[dataPt]) {
                return 0;
            }
            bracketCnt++;
            while(file.get(c)) {
                if (c == '[') {
                    bracketCnt++;
                } else if (c == ']') {
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
     
            while(goBack(c)) {
                if (c == ']') {
                    bracketCnt--;
                } else if (c == '[') {
                    bracketCnt++;
                    if (bracketCnt == 0) {
                        break;
                    }
                }
            }
            return 0;
        default:
            return -1;
    }
}

bool goBack(char &c) {
    if (file.tellg() < 2) {
        return false;
    }
    file.seekg(-2, file.cur);   
    return file.get(c) ? true : false;
}
