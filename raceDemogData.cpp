#include "raceDemogData.h"
#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream &out, const raceDemogData &DD) {
    out << "Racial Demographics Info: ";
    out << std::setprecision(2) << std::fixed;
    out << "fix me";
    return out;
}
