#ifndef STATE_H
#define STATE_H
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include "demogData.h"
#include "raceDemogData.h"
#include <iostream>
#include <map>

/*
  class to represent state data - fairly redundant at this point but will use
  inheritence later - FILL IN
*/
class demogState
{
public:
  demogState(string inN, double totalPop2020, double in65, double in18, double in5, float inPF, shared_ptr<raceDemogData> inRE, double medInc,
             double pplPH, double vetPop, double hSDP, double bDP, double inFB, double inHU, double inHOR, double inNHH) : name(inN), totalPopulation2020(totalPop2020), popOver65(in65), popUnder18(in18), popUnder5(in5),
             percentFemale(inPF), raceEthnicity(inRE), medianIncome(medInc), avgPeoplePerHome(pplPH), veteransPop(vetPop),
             highSchoolDipPop(hSDP), bachelorsDegreePop(bDP), foreignBorn(inFB), housingUnits(inHU), homeOwnershipRate(inHOR), numHouseholds(inNHH)
  {}

  void addCounty(shared_ptr<demogData> countyData)
  {
    numCounties += 1;

    popOver65 = ((countyData->getPop65() * countyData->getTotalPop2020()) + (popOver65 * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020());
    popUnder18 = ((countyData->getPop18() * countyData->getTotalPop2020()) + (popUnder18 * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020());
    popUnder5 = ((countyData->getPop5() * countyData->getTotalPop2020()) + (popUnder5 * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020());
    
    raceEthnicity->addCountyRE(countyData->getRaceEthnicity(), countyData->getTotalPop2020(), totalPopulation2020);
    percentFemale = ((countyData->getPctFemale() * countyData->getTotalPop2020()) + (percentFemale * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020());
    foreignBorn = ((countyData->getForeignBorn() * countyData->getTotalPop2020()) + (foreignBorn  * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020());
    veteransPop = ((countyData->getVeteransPop() * countyData->getTotalPop2020()) + (veteransPop * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020());

    medianIncome = ((countyData->getHouseholds() * countyData->getMedIncome()) + (medianIncome * numHouseholds)) / (countyData->getHouseholds() + numHouseholds); 
    avgPeoplePerHome = ((countyData->getAvgPeoplePHome() * countyData->getTotalPop2020()) + (avgPeoplePerHome * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020()); 
    housingUnits = ((countyData->getHousingUnits() * countyData->getTotalPop2020()) + (housingUnits * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020());          
    homeOwnershipRate = ((countyData->getHomeOwnershipRate()* countyData->getTotalPop2020()) + (homeOwnershipRate * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020()); 
    numHouseholds += countyData->getHouseholds(); 

    highSchoolDipPop = ((countyData->getHighSchoolDipPop() * countyData->getTotalPop2020()) + (highSchoolDipPop * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020());
    bachelorsDegreePop = ((countyData->getBachelorsPop() * countyData->getTotalPop2020()) + (bachelorsDegreePop * totalPopulation2020)) / (totalPopulation2020 + countyData->getTotalPop2020());
  
    totalPopulation2020 += countyData->getTotalPop2020();
  }

  void incrementCounties()
  {
    numCounties += 1;
  }

  static bool compareDoubles(double d1, double d2)
  {
    return d1 < d2;
  }

  double findMedian(double medInc)
  {
    countyMedianIncomes.push_back(medInc);                                        // add new median income value
    sort(countyMedianIncomes.begin(), countyMedianIncomes.end(), compareDoubles); // sort smallest -> largest
    if (countyMedianIncomes.size() % 2 != 0)
    { // if odd length, median is middle
      return countyMedianIncomes[round(countyMedianIncomes.size() / 2)];
    }
    else
    {
      return (countyMedianIncomes[round(countyMedianIncomes.size() / 2)] +
              countyMedianIncomes[round(countyMedianIncomes.size() / 2) - 1]) /
             2;
    }
  }

  string getName() const { return name; }
  double getTotalPop2020() const { return totalPopulation2020; }
  double getPop65() const { return popOver65; }
  double getPop18() const { return popUnder18; }
  double getPop5() const { return popUnder5; }
  float getPctFemale() const { return percentFemale; }
  shared_ptr<raceDemogData> getRaceEthnicity() const { return raceEthnicity; }
  double getMedIncome() const { return medianIncome; }
  double getAvgPeoplePHome() const { return avgPeoplePerHome; }
  double getVeteransPop() const { return veteransPop; }
  double getHighSchoolDipPop() const { return highSchoolDipPop; }
  double getBachelorsPop() const { return bachelorsDegreePop; }
  double getForeignBorn() const { return foreignBorn; }
  double getHousingUnits() const { return housingUnits; }
  double getHomeOwnershipRate() const { return homeOwnershipRate; }
  double getNumCounties() const { return numCounties; }
  double getNumHouseholds() const { return numHouseholds; }

  // counts
  int getPop5Count() const { return (int)round(popUnder5 * totalPopulation2020 / 100); }
  int getPop65Count() const { return (int)round(popOver65 * totalPopulation2020 / 100); }
  int getPop18Count() const { return (int)round(popUnder18 * totalPopulation2020 / 100); }
  int getPctFemaleCount() const { return (int)round(percentFemale * totalPopulation2020 / 100); }
  int getAvgPeoplePHomeCount() const { return (int)round(avgPeoplePerHome * housingUnits); }
  //int getVeteransPopCount() const { return (int)round(veteransPop * totalPopulation2020 / 100); }
  int getHighSchoolDipCount() const { return (int)round(highSchoolDipPop * totalPopulation2020 / 100); }
  int getBachelorsPopCount() const { return (int)round(bachelorsDegreePop * totalPopulation2020 / 100); }
  int getForeignBornCount() const { return (int)round(foreignBorn * totalPopulation2020 / 100); }
  int getHomeOwnershipCount() const { return (int)round(homeOwnershipRate * totalPopulation2020 / 100); }

  friend std::ostream &operator<<(std::ostream &out, const demogState &SD);

private:
  const string name;
  double totalPopulation2020;
  double popOver65;
  double popUnder18;
  double popUnder5;
  float percentFemale;
  shared_ptr<raceDemogData> raceEthnicity;
  double medianIncome;
  double avgPeoplePerHome;
  double veteransPop;
  double highSchoolDipPop;
  double bachelorsDegreePop;
  double foreignBorn;
  double housingUnits;
  double homeOwnershipRate;
  double numCounties;
  std::vector<double> countyMedianIncomes;
  double numHouseholds;
};
#endif

