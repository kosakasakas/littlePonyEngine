//
//  Utility.cpp
//  UCEngine
//
//  Created by Takahiro Kosaka on 2014/04/23.
//
//

#include "Utility.h"
#include <ctype.h>

bool Utility::isDecimalValue(const char* text) {
    int i = 0;
    while (text[i] != '\0' ) {
        if (text[i] == '.' || isdigit(text[i])) {
            i++;
        } else {
            return false;
        }
    }
    return (i > 0) ? true : false;
}

const char* Utility::getStrFromFloatValue(float val) {
    char str[256];
    sprintf(str, "%.2f", val);
    std::string result = str;
    return result.c_str();
}

int Utility::getRandomInt(int limit) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_sec + tv.tv_usec);
    int randNum = rand()%limit;
    return randNum;
}

const char* Utility::getStrFromFloatInt(int val) {
    char str[256];
    sprintf(str, "%d", val);
    const char* ret = const_cast<char*>(str);
    return ret;
}