#include <iomanip>
#include "psCombo.h"
#include "psRaceDemogData.h"

/* print state data - as aggregate of all incidents in this state */
std::ostream& operator<<(std::ostream &out, const psCombo& PD) {
    out << "Region Info: " << PD.getRegion();
    out << "\nNumber of incidents: " << PD.getNumberOfCases();
    out << "\nIncidents involving unarmed or armed with toy weapons: " << PD.getUnArmedCount() << ", " << PD.getUnArmedCount()  / PD.getNumberOfCases() * 100 <<"%";
    out << "\nIncidents involving mental illness: " << PD.getNumMentalI() << ", " <<  PD.getNumMentalI() / PD.getNumberOfCases() * 100 <<"%";
    out << "\nIncidents with body camera on: " << PD.getNumBodyCam() << ", " <<  PD.getNumBodyCam() / PD.getNumberOfCases() * 100 <<"%";
    out << "\nRacial demographics of state incidents: " << PD.getRaceDemogData()->communityRacialCount(PD.getNumberOfCases());
    return out;
}

void psCombo::addPoliceShooting(shared_ptr<psData> shootingData)
    {
        totalCases += 1;
        if(( shootingData->getArmed().compare("unarmed") == 0) ||
        ( shootingData->getArmed().empty() )) {
            unarmed += 1;
        } else if ( shootingData->getArmed().compare("toy weapon") == 0) {
            unarmed += 1;
        }
        if(shootingData->getBodyCamera() == true) {
            bodyCam += 1;
        }
        if(shootingData->getSignOfMentalIllness() == true) {
            mentalI += 1;
        }
        raceEthnicity->addPSCase(shootingData->getRace());
    }