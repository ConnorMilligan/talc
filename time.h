#ifndef TIME_H
#define TIME_H

#include <ctime>
#include <string>

/**
 * @brief Parses the string in a date format to a ctime object
 * 
 * https://stackoverflow.com/questions/4781852/how-to-convert-a-string-to-datetime-in-c
 * 
 * @param dateTime - The date as a string
 * @return std::time_t the date in ctime
 */
std::time_t getEpochTime(const std::string dateTime);

#endif