#include <iostream>
#include <iomanip>
#include "psRaceDemogData.h"

psRaceDemogData::psRaceDemogData() {}

std::ostream &operator<<(std::ostream &out, const psRaceDemogData &DD)
{
    out << "Racial Demographics Info: ";
    out << std::setprecision(2) << std::fixed;
    out << "fix me";
    return out;
}

void psRaceDemogData::addPSCase(std::string race)
{
    if (race.compare("W") == 0)
    {
        whiteNHCount += 1;
    }
    else if (race.compare("B") == 0)
    {
        blackNHCount += 1;
    }
    else if (race.compare("A") == 0)
    {
        asCount += 1;
    }
    else if (race.compare("N") == 0)
    {
        nativeAmericanCount += 1;
    }
    else if (race.compare("H") == 0)
    {
        hispanicCount += 1;
    }
    else if (race.compare("O") == 0)
    {
        unspecifiedCount += 1;
    }
    else
    {
        unknownCount += 1;
    }
    totalCases += 1;
}
