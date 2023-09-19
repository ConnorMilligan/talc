#include "time.h"

#include <sstream>
#include <iomanip>

std::time_t getEpochTime(const std::string dateTime) {
    // Why do you need the Z? Blame ISO 8601
   static const std::string dateTimeFormat{ "%Y-%m-%dT%H:%M:%SZ" };
   std::istringstream ss{ dateTime };
   std::tm dt;

   ss >> std::get_time(&dt, dateTimeFormat.c_str());
   return std::mktime(&dt);
}