#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "demogState.h"
#include "psCombo.h"

/*
  data aggregator and query for testing
*/
class dataAQ {
  public:
    dataAQ();

    void createStateData(std::vector<shared_ptr<demogData> > theData);
    void createStatePoliceData(std::vector<shared_ptr<psData> > theData);

    //return the name of the state with the largest population under age 5
    string youngestPop();
    //return the name of the state with the largest population under age 18
    string teenPop();
    //return the name of the state with the largest population over age 65
    string wisePop();
    //return the name of the state with the largest population who did not finish high school
    string underServeHS();
    //return the name of the state with the largest population who completed college
    string collegeGrads();
    //return the name of the state with the lowest median income
    string lowestMedIncome();
    //return the name of the state with the largest percentage of the population who are foreign born
    string mostForBorn();
    //return the name of the state with the largest number of people per household
    string mostPerHouse();
    //return the name of the state with the largest percentage of veterans
    string mostVeterans();

    string belowPoverty(); 
    string lowestMedInc(); 




    //sort and report the top ten states in terms of number of police shootings 
    std::vector<std::string> reportTopTenStatesPS();
    std::vector<std::string> reportTopShootingsPerCapita();

    void reportBottomTenStatesHomeOwn();
    
    shared_ptr<demogState> getStateData(string stateName) { return allStateData[stateName]; }
    std::map<string, shared_ptr<demogState> > getAllStateData() { return allStateData; }

    shared_ptr<psCombo> getStatePoliceData(string stateName) { return allStatePoliceData[stateName]; }
    std::map<string, shared_ptr<psCombo> > getAllStatePoliceData() { return allStatePoliceData; }

    friend std::ostream& operator<<(std::ostream &out, const dataAQ &allStateData);

    //this quarter restriction
    private:
       std::map<string, shared_ptr<demogState> > allStateData;
       std::map<string, shared_ptr<psCombo> > allStatePoliceData;

};
#endif
