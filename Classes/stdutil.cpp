//
//  stdutil.cpp
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-24.
//
//

#include "stdutil.h"

std::string toLowerCase(std::string str) {
    long nChars = str.length();
    for (int i = 0; i < nChars; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

//std::string format(const char *format, ...)
//{
//    va_list args;
//    va_start(args, format);
//    
//    char buf[80];
//    vsnprintf(buf, 80-3, format, args);
//    va_end(args);
//    
//    return buf;
//}

std::string timeToStr(time_t time, const char *format) {
    char buffer [80];
    //    time_t time = (time + 8) * 3600;
    strftime(buffer, 80, format, gmtime(&time));
    return buffer;
}
