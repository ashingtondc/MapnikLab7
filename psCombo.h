#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "psRaceDemogData.h"
#include "psData.h"

using namespace std;

class psCombo {
public:
    psCombo(string inS) : 
    state(inS)
    {} 

    void addPoliceShooting(shared_ptr<psData> shootingData);
    
    //complete these
    double getNumMentalI() const { return mentalI; } //total count “TRUE”
    double getUnArmedCount() const { return unarmed; } //total count blank, ‘unarmed’
    double getArmedToy() const { return armedToy; }  //total count ’toy weapon’
    double getNumBodyCam() const { return bodyCam; } //total count “TRUE”
    double getNumberOfCases() const { return totalCases; }//total number for a region
    shared_ptr<psRaceDemogData> getRaceDemogData() const { return raceEthnicity; }
    string getRegion() const { return state; } //return state for p2

    //add any others needed

    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);

protected:
    double mentalI = 0;
    double  unarmed = 0;
    double  armedToy = 0;
    double  bodyCam = 0;
    double  totalCases = 0;
    shared_ptr<psRaceDemogData> raceEthnicity = std::make_shared<psRaceDemogData>();
    const string state;
};

#endif