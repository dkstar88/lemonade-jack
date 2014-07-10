//
//  stdutil.h
//  lemoname
//
//  Created by Yang William Yanzhe on 14-5-13.
//
//

#ifndef lemoname_stdutil_h
#define lemoname_stdutil_h

#include <string>   // for ssize_t on linux
#include <time.h>

std::string toLowerCase(std::string str);
//std::string format(const char *format, ...);
std::string timeToStr(time_t time, const char *format = "%I:%M%p.");

//float randomFloatBetween(int num1, int num2)
//{
//    int startVal = num1*10000;
//    int endVal = num2*10000;
//    
//    int randomValue = startVal +(arc4random()%(endVal - startVal));
//    float a = randomValue;
//    
//    return(a /10000.0);
//}

#endif
