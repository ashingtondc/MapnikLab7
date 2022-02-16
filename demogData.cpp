#include "demogData.h"
#include <sstream>

/* print county demographic data */
/* fill in any other data to make printing easy  */
std::ostream& operator<<(std::ostream &out, const demogData &DD) {
    out << "**County Demographics Info: " << DD.getName() << ", " << DD.state;
    out << "\nTotal population: " << DD.getTotalPop2020();
    out << DD.raceEthnicity->communityRacialCount(DD.getTotalPop2020());

    out << "--Population Age info:";
    out << "\n(under 5): " << DD.getPop5()  << " and total: " << DD.getPop5Count();
    out << "\n(under 18): " << DD.getPop18()  << " and total: " << DD.getPop18Count();
    out << "\n(over 65): " << DD.getPop65()  << " and total: " << DD.getPop65Count() ;
    
    out << "--Population other demographics";
    out << "\n(female): " << DD.getPctFemale() << " and total: " << DD.getPctFemaleCount();
    out << "\n(foreign born): " << DD.getForeignBorn()  << " and total: " << DD.getForeignBornCount();
    out << "\n(veterans): " << DD.getVeteransPop()  << " and total: " << DD.getVeteransPopCount();

    out << "\n--County housing/economy info:";
    out << "\n(avg. persons per house): " << DD.getAvgPeoplePHome() << " and total: " << DD.getAvgPeoplePHomeCount();
    out << "\n(home ownership): " << DD.getHomeOwnershipRate() << " and total: " << DD.getHomeOwnershipCount();
    out << "\n(number housing units): " << DD. getHousingUnits();
    out << "\n(medium income): " << DD.getMedIncome();

    out << "\n--County education: ";
    out << "\n(Bachelor or more): " << DD.getBachelorsPop() << " and total: " << DD.getBachelorsPopCount();
    out << "\n(high school or more): " << DD.getHighSchoolDipPop() << " and total: " << DD.getHighSchoolDipCount();

    return out;
}

