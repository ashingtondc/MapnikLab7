/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "psData.h"
#include <iostream>
#include <algorithm>
#include <tuple>

dataAQ::dataAQ() {}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
// Takes in a list of all of the counties, and returns a map that maps STATE_NAME to DEMOG_STATE
void dataAQ::createStateData(std::vector<shared_ptr<demogData> > theData)
{
  std::map<std::string, shared_ptr<demogState> > stateData; // declare stateData map 
  for (const auto &elem : theData) // iterate through the county data 
  {
    std::string stateName = elem->getState(); 

    if (stateData.count(stateName) == 0) // if state is NOT in the map already
    { // insert the state name, along with an instance of a NEW demogState pointer
      stateData[stateName] =  std::make_shared<demogState>(stateName, elem->getTotalPop2020(), elem->getPop65(), elem->getPop18(),
                                                        elem->getPop5(), elem->getPctFemale(), elem->getRaceEthnicity(), elem->getMedIncome(),
                                                        elem->getAvgPeoplePHome(), elem->getVeteransPop(), elem->getHighSchoolDipPop(),
                                                        elem->getBachelorsPop(), elem->getForeignBorn(), elem->getHousingUnits(), elem->getHomeOwnershipRate(),
                                                        elem->getHouseholds());
      stateData[stateName]->incrementCounties();
    } else { // if the state has aleady been inserted, add new county 
      stateData[stateName]->addCounty(elem);
    }
  }
  allStateData = stateData;
}



void dataAQ::createStatePoliceData(std::vector<shared_ptr<psData> > theData){
 std::map<std::string, shared_ptr<psCombo> > comboData; 
  for (const auto &elem : theData) 
  {
    std::string stateName = elem->getState(); 

    if (comboData.count(stateName) == 0) 
    { 
      comboData[stateName] =  std::make_shared<psCombo>(stateName);
    } 
    comboData[stateName]->addPoliceShooting(elem);
  }
   allStatePoliceData = comboData;
}

std::vector<std::string> dataAQ::reportTopShootingsPerCapita() {
  std::vector<std::tuple <std::string, double> > shootingsPerCapita;
  std::vector<std::string> policeStateNames;

  std::map<std::string, shared_ptr<psCombo> >::iterator it = allStatePoliceData.begin();
  while (it != allStatePoliceData.end())
  {
    // Accessing KEY from element pointed by it.
    std::string state = it->first;
    // Accessing VALUE from element pointed by it.
    shared_ptr<psCombo> psStateData = it->second;
    double pop = allStateData[state]->getTotalPop2020();

    shootingsPerCapita.push_back(std::make_tuple(state, psStateData->getNumberOfCases() / pop));
    // Increment the Iterator to point to next entry
    it++;
  }
  std::sort(shootingsPerCapita.begin(), shootingsPerCapita.end(), [](std::tuple<std::string, double> first, std::tuple<std::string, double> second) {return get<1>(first) > get<1>(second);});
  
  for (auto stateData : shootingsPerCapita) {
    policeStateNames.push_back(get<0>(stateData));
  }

  return policeStateNames;
}


//sort and report the top ten states in terms of number of police shootings 
std::vector<std::string> dataAQ::reportTopTenStatesPS() {
  std::vector<shared_ptr<psCombo>> policeStates;
  std::vector<std::string> policeStateNames;

  std::map<std::string, shared_ptr<psCombo> >::iterator it = allStatePoliceData.begin();
  while (it != allStatePoliceData.end())
  {
    // Accessing KEY from element pointed by it.
    std::string state = it->first;
    // Accessing VALUE from element pointed by it.
    shared_ptr<psCombo> stateData = it->second;
    policeStates.push_back(stateData);
    // Increment the Iterator to point to next entry
    it++;
  }
  std::sort(policeStates.begin(), policeStates.end(), [](shared_ptr<psCombo> first, shared_ptr<psCombo> second) {return first->getNumberOfCases() > second->getNumberOfCases();});
  
  for (auto &stateData : policeStates) {
    policeStateNames.push_back(stateData->getRegion());
  }

  return policeStateNames;

  /*
  cout << "Top ten states sorted on number police shootings & the associated census data:" << endl;
  for (int i = 0; i < 10; i++) {
    string state = policeStates[i]->getRegion();
    int pop = allStateData[state]->getTotalPop2020();
    double shootings = policeStates[i]->getNumberOfCases();
    double homeOwner = allStateData[state]->getHomeOwnershipRate();
    cout << state << endl;
    cout << "Total population: " << pop << " Percentage home ownership: " << homeOwner << "%" << endl;
    cout << "Police shooting incidents: " << shootings << " Percent of population: " << shootings / pop * 100 << "%" << endl;
  }
  cout << "\n\n**Full listings for top 3 police shootings & the associated census data:" << endl;
  for (int i =0; i < 3; i++) {
    cout << *(policeStates[i]) << endl;
    string state = policeStates[i]->getRegion();
    cout << *(allStateData[state]) << endl;
  }
  */
}

void dataAQ::reportBottomTenStatesHomeOwn(){
  vector<shared_ptr<psCombo> > policeStates;
  std::map<std::string, shared_ptr<psCombo> >::iterator it = allStatePoliceData.begin();
  while (it != allStatePoliceData.end())
  {
    // Accessing KEY from element pointed by it.
    std::string state = it->first;
    // Accessing VALUE from element pointed by it.
    shared_ptr<psCombo> stateData = it->second;
    policeStates.push_back(stateData);
    // Increment the Iterator to point to next entry
    it++;
  }
  std::sort(policeStates.begin(), policeStates.end(), [](shared_ptr<psCombo> first, shared_ptr<psCombo> second) {return first->getNumberOfCases() < second->getNumberOfCases();});
  cout << "Bottom ten states sorted on number police shootings & the associated census data:" << endl;
  for (int i = 0; i < 10; i++) {
    string state = policeStates[i]->getRegion();
    int pop = allStateData[state]->getTotalPop2020();
    double shootings = policeStates[i]->getNumberOfCases();
    double homeOwner = allStateData[state]->getHomeOwnershipRate();
    cout << state << endl;
    cout << "Total population: " << pop << " Percentage home ownership: " << homeOwner << "%" << endl;
    cout << "Police shooting incidents: " << shootings << " Percent of population: " << shootings / pop * 100 << "%" << endl;
  }
    cout << "\n\n**Full listings for bottom 3 home ownership rates & the associated census data:" << endl;
   for (int i =0; i < 3; i++) {
    cout << *(policeStates[i]) << endl;
    string state = policeStates[i]->getRegion();
    cout << *(allStateData[state]) << endl;
  }
}

//return the name of the state with the largest population under age 5
string dataAQ::youngestPop()
{
  std::string result = "";
  int pop = 0;
  std::map<std::string, shared_ptr<demogState> >::iterator it = allStateData.begin();
  while (it != allStateData.end())
    {
        // Accessing KEY from element pointed by it.
        std::string state = it->first;
        // Accessing VALUE from element pointed by it.
        shared_ptr<demogState> stateData = it->second;
        if (stateData->getPop5() > pop) {
          pop = stateData->getPop5();
          result = state;
        }
        // Increment the Iterator to point to next entry
        it++;
    }
  //FILL in
  return result;
}

//return the name of the state with the largest population under age 18
string dataAQ::teenPop()
{
  std::string result = "";
  int pop = 0;
  std::map<std::string, shared_ptr<demogState> >::iterator it = allStateData.begin();
  while (it != allStateData.end())
    {
        // Accessing KEY from element pointed by it.
        std::string state = it->first;
        // Accessing VALUE from element pointed by it.
        shared_ptr<demogState> stateData = it->second;
        if (stateData->getPop18() > pop) {
          pop = stateData->getPop18();
          result = state;
        }
        // Increment the Iterator to point to next entry
        it++;
    }
  //FILL in
  return result;
}

//return the name of the state with the largest population over age 65
string dataAQ::wisePop()
{
  std::string result = "";
  int pop = 0;
  std::map<std::string, shared_ptr<demogState> >::iterator it = allStateData.begin();
  while (it != allStateData.end())
    {
        // Accessing KEY from element pointed by it.
        std::string state = it->first;
        // Accessing VALUE from element pointed by it.
        shared_ptr<demogState> stateData = it->second;
        if (stateData->getPop65() > pop) {
          pop = stateData->getPop65();
          result = state;
        }
        // Increment the Iterator to point to next entry
        it++;
    }
  //FILL in
  return result;
}

//return the name of the state with the largest population who did not receive high school diploma
string dataAQ::underServeHS()
{
  std::string result = "";
  double pop = 0;
  std::map<std::string, shared_ptr<demogState> >::iterator it = allStateData.begin();
  while (it != allStateData.end())
    {
        // Accessing KEY from element pointed by it.
        std::string state = it->first;
        // Accessing VALUE from element pointed by it.
        shared_ptr<demogState> stateData = it->second;
        if (100 - stateData->getHighSchoolDipPop() > pop) {
          pop = 100 - stateData->getHighSchoolDipPop();
          result = state;
        }
        // Increment the Iterator to point to next entry
        it++;
    }
  return result;
}

//return the name of the state with the largest population who did receive bachelors degree and up
string dataAQ::collegeGrads()
{
  std::string result = "";
  int pop = 0;
  std::map<std::string, shared_ptr<demogState> >::iterator it = allStateData.begin();
  while (it != allStateData.end())
    {
        // Accessing KEY from element pointed by it.
        std::string state = it->first;
        // Accessing VALUE from element pointed by it.
        shared_ptr<demogState> stateData = it->second;
        if (stateData->getBachelorsPop() > pop) {
          pop = stateData->getBachelorsPop();
          result = state;
        }
        // Increment the Iterator to point to next entry
        it++;
    }
  //FILL in
  return result;
}

//return the name of the state with the largest population below the poverty line
string dataAQ::belowPoverty()
{
  std::string result1 = "";
  std::string result2 = "";

  int poverty = 31661;
  int lowestMedian = 500000; // Bad initial value, but should work for now; result1
  int medIncomeClosest = 500000; // result2
  std::map<std::string, shared_ptr<demogState> >::iterator it = allStateData.begin();
  while (it != allStateData.end())
    {
        // Accessing KEY from element pointed by it.
        std::string state = it->first;
        // Accessing VALUE from element pointed by it.
        shared_ptr<demogState> stateData = it->second;
        if (stateData->getMedIncome() - poverty < medIncomeClosest - poverty) {
          medIncomeClosest = stateData->getMedIncome();
          result2 = state;
        }
        if (stateData->getMedIncome() < lowestMedian) {
          lowestMedian = stateData->getMedIncome();
          result1 = state;
        }
        // Increment the Iterator to point to next entry
        it++;
    }

  //FILL in
  if (lowestMedian < medIncomeClosest) {
    return result1;
  } else {
    return result2;
  }
}

string dataAQ::lowestMedInc() {
    std::string result1 = "";

    int poverty = 31661;
    int lowestMedian = 500000; // Bad initial value, but should work for now; result1
    int medIncomeClosest = 500000; // result2
    std::map<std::string, shared_ptr<demogState> >::iterator it = allStateData.begin();
    while (it != allStateData.end())
      {
          // Accessing KEY from element pointed by it.
          std::string state = it->first;
          // Accessing VALUE from element pointed by it.
          shared_ptr<demogState> stateData = it->second;
          if (stateData->getMedIncome() < lowestMedian) {
            lowestMedian = stateData->getMedIncome();
            result1 = state;
          }
          // Increment the Iterator to point to next entry
          it++;
      }

    //FILL in
    return result1;
}

string dataAQ::mostForBorn() {
    std::string result = "";
    int pop = 0;
    std::map<std::string, shared_ptr<demogState> >::iterator it = allStateData.begin();
    while (it != allStateData.end())
    {
        // Accessing KEY from element pointed by it.
        std::string state = it->first;
        // Accessing VALUE from element pointed by it.
        shared_ptr<demogState> stateData = it->second;
        if (stateData->getForeignBorn() > pop) {
            pop = stateData->getForeignBorn();
            result = state;
        }
        // Increment the Iterator to point to next entry
        it++;
    }
    //FILL in
    return result;
}

string dataAQ::mostPerHouse() {
  std::string result = "";
  int pop = 0;
  std::map<std::string, shared_ptr<demogState> >::iterator it = allStateData.begin();
  while (it != allStateData.end())
    {
        // Accessing KEY from element pointed by it.
        std::string state = it->first;
        // Accessing VALUE from element pointed by it.
        shared_ptr<demogState> stateData = it->second;
        if (stateData->getAvgPeoplePHome() > pop) {
          pop = stateData->getAvgPeoplePHome();
          result = state;
        }
        // Increment the Iterator to point to next entry
        it++;
    }
  //FILL in
  return result;
} 

string dataAQ::mostVeterans() {
  std::string result = "";
  int pop = 0;
  std::map<std::string, shared_ptr<demogState> >::iterator it = allStateData.begin();
  while (it != allStateData.end())
    {
        // Accessing KEY from element pointed by it.
        std::string state = it->first;
        // Accessing VALUE from element pointed by it.
        shared_ptr<demogState> stateData = it->second;
        if (stateData->getVeteransPop() > pop) {
          pop = stateData->getVeteransPop();
          result = state;
        }
        // Increment the Iterator to point to next entry
        it++;
    }
  //FILL in
  return result;
}



