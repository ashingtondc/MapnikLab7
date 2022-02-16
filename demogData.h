#ifndef DEMOG_H
#define DEMOG_H
#include "raceDemogData.h"
#include <string>
#include <iostream>



using namespace std;

/*
  class to represent county demographic data
  from CORGIS - fill in with any data we agree as a class we want to include
*/
class demogData
{
public: 
  demogData(string inN, string inS, double totalPop2020, double in65, double in18, double in5, float inPF, shared_ptr<raceDemogData> inRE, 
  double medInc, double pplPH, double vetPop, double hSDP, double bDP, double inFB, double inHU, double inHOR, double inNHH) :
    name(inN), state(inS), totalPopulation2020(totalPop2020),  popOver65(in65), popUnder18(in18), popUnder5(in5), percentFemale(inPF), 
    raceEthnicity(inRE), medianIncome(medInc), avgPeoplePerHome(pplPH), veteransPop(vetPop),
    highSchoolDipPop(hSDP), bachelorsDegreePop(bDP), foreignBorn(inFB), housingUnits(inHU), homeOwnershipRate(inHOR), numHouseholds(inNHH)
  {}

  string getName() const { return name; }
  string getState() const { return state; }
  double getTotalPop2020() const { return totalPopulation2020; }
  double getPop65() const { return popOver65; }
  double getPop18() const { return popUnder18; }
  double getPop5() const { return popUnder5; }
  float getPctFemale() const { return percentFemale; }
  shared_ptr<raceDemogData> getRaceEthnicity() const { return raceEthnicity; }
  double getMedIncome() const { return medianIncome; }
  double getAvgPeoplePHome() const { return avgPeoplePerHome;}
  double getVeteransPop() const { return veteransPop; }
  double getHighSchoolDipPop() const { return highSchoolDipPop; }
  double getBachelorsPop() const { return bachelorsDegreePop; }
  double getForeignBorn() const { return foreignBorn; }
  double getHousingUnits() const { return housingUnits; }
  double getHomeOwnershipRate() const { return homeOwnershipRate; }
  double getHouseholds() const { return numHouseholds; }

  // counts
  int getPop5Count() const { return (int)round(popUnder5 * totalPopulation2020 / 100); }
  int getPop65Count() const { return (int)round(popOver65 * totalPopulation2020 / 100); }
  int getPop18Count() const { return (int)round(popUnder18 * totalPopulation2020 / 100); }
  int getPctFemaleCount() const { return (int)round(percentFemale * totalPopulation2020 / 100); }
  int getAvgPeoplePHomeCount() const { return (int)round(avgPeoplePerHome * housingUnits); }
  int getVeteransPopCount() const { return (int)round(veteransPop * totalPopulation2020 / 100); }
  int getHighSchoolDipCount() const { return (int)round(highSchoolDipPop * totalPopulation2020 / 100); }
  int getBachelorsPopCount() const { return (int)round(bachelorsDegreePop * totalPopulation2020 / 100); }
  int getForeignBornCount() const { return (int)round(foreignBorn * totalPopulation2020 / 100); }
  int getHomeOwnershipCount() const { return (int)round(homeOwnershipRate * totalPopulation2020 / 100); }

  friend std::ostream &operator<<(std::ostream &out, const demogData &DD);

private:
  const string name;
  const string state;
  const double totalPopulation2020;
  const double popOver65;
  const double popUnder18;
  const double popUnder5;
  const float percentFemale;
  const shared_ptr<raceDemogData> raceEthnicity;
  const double medianIncome;
  const double avgPeoplePerHome;
  const double veteransPop;
  const double highSchoolDipPop;
  const double bachelorsDegreePop;
  const double foreignBorn;
  const double housingUnits;
  const double homeOwnershipRate;
  const double numHouseholds;
  
};
#endif
