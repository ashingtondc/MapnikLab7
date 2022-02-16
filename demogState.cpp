#include "demogState.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>

std::ostream& operator<<(std::ostream &out, const demogState&SD) {
    out << "**US census data:State Info:" << SD.getName();
    out << "\nNumber of counties: " << SD.getNumCounties();
    out << "\nTotal population: " << SD.getTotalPop2020();
    out << "\n" << SD.getRaceEthnicity()->communityRacialCount(SD.getTotalPop2020());
    out << "\n--Population Age info:";
    out << "\n(under 5): " << SD.getPop5()  << " and total: " << SD.getPop5Count();
    out << "\n(under 18): " << SD.getPop18()  << " and total: " << SD.getPop18Count();
    out << "\n(over 65): " << SD.getPop65()  << " and total: " << SD.getPop65Count() ;
    
    out << "\n--Population other demographics";
    out << "\n(female): " << SD.getPctFemale() << " and total: " << SD.getPctFemaleCount();
    out << "\n(foreign born): " << SD.getForeignBorn()  << " and total: " << SD.getForeignBornCount();
    out << "\n(veterans): " << 100*SD.getVeteransPop()/SD.getTotalPop2020()  << " and total: " << SD.getVeteransPop();

    out << "\n--County housing/economy info:";
    out << "\n(avg. persons per house): " << SD.getAvgPeoplePHome() << " and total: " << SD.getAvgPeoplePHomeCount();
    out << "\n(home ownership): " << SD.getHomeOwnershipRate() << " and total: " << SD.getHomeOwnershipCount();
    out << "\n(number housing units): " << SD. getHousingUnits();
    out << "\n(medium income): " << SD.getMedIncome();

    out << "\n--County education: ";
    out << "\n(Bachelor or more): " << SD.getBachelorsPop() << " and total: " << SD.getBachelorsPopCount();
    out << "\n(high school or more): " << SD.getHighSchoolDipPop() << " and total: " << SD.getHighSchoolDipCount() << endl;
    
    return out;
}

