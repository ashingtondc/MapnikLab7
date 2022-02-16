#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <iostream>
#include <utility>

using namespace std;

/*
  class to represent police shooting data
  from Washington Post
*/
class psData {
  public:
    //add appropriate function paramaters to constructor once you add data
    psData(string inState, string inCity, string inName, string inRace, bool inMental, string inArmed, bool inBodyCamera) 
      : state(inState), city(inCity), name(inName), race(inRace), signOfMentalIllness(inMental), armed(inArmed), bodyCamera(inBodyCamera) {}

    std::string getState() const { return state; }
    std::string getCity() const { return city; }
    std::string getName() const { return name; }
    std::string getRace() const { return race; }
    bool getSignOfMentalIllness() const { return signOfMentalIllness; }
    std::string getArmed() const { return armed; }
    bool getBodyCamera() const { return bodyCamera; }

   friend std::ostream& operator<<(std::ostream &out, const psData &PD);

private:
    const std::string state;
    const std::string city;
    const std::string name;
    const std::string race;
    const bool signOfMentalIllness;
    const std::string armed;
    const bool bodyCamera;
    //add others

};

#endif
