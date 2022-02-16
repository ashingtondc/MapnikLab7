
#ifndef PSRACEDEMOGDATA_H
#define PSRACEDEMOGDATA_H

#include <math.h>
#include <memory>
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <iostream>

class psRaceDemogData
{
public:
psRaceDemogData();

  double getWhite() const { return whiteNHCount / totalCases; }
  double getBlack() const { return blackNHCount / totalCases; }
  double getNativeAmeri() const { return nativeAmericanCount / totalCases; }
  double getAsian() const { return asCount / totalCases; }
  double getHispLatino() const { return hispanicCount / totalCases; }
  double getUnspecified() const { return unspecifiedCount / totalCases; }
  double getUnknown() const { return unknownCount / totalCases; }
  double getNumCases() const { return totalCases; }

  void addPSCase(std::string race);

  std::string communityRacialCount(int population) const {
    std::ostringstream one;
    std::ostringstream two; 
    std::ostringstream three; 
    std::ostringstream four; 
    std::ostringstream five; 
    std::ostringstream six; 
    std::ostringstream seven; 
    std::ostringstream eight;  
    std::ostringstream nine; 
    std::ostringstream total;
    std::ostringstream final_title;
    std::ostringstream final;
    one << "% American Indian and Alaska Native Percent: " << nativeAmericanCount / totalCases * 100 << " count: " << nativeAmericanCount << "\n";
    two << "% Asian American percent: " << asCount / totalCases * 100 << " count: " << asCount << "\n";
    three << "% Black/African American percent: " << blackNHCount / totalCases * 100 << " count: " << blackNHCount << "\n";
    four << "% Hispanic or Latinx percent: " << hispanicCount / totalCases * 100 << " count: " << hispanicCount << "\n";
    five << "% Native Hawaiian and Other Pacific Islander count: " << 0 << "\n";
    six << "% Two or More Races count: " << 0 << "\n";
    seven << "% White (inclusive) percent: " << whiteNHCount / totalCases * 100 << " count: " << whiteNHCount << "\n";
    eight << "% White (nonHispanic) percent: " << whiteNHCount / totalCases * 100 << " count: " << whiteNHCount << "\n";
    nine << "% Unspecified percent : " << unspecifiedCount / totalCases * 100 << " count: " << unspecifiedCount << "\n";
    total << "total Racial Demographic count: " << totalCases << "\n";
    final_title << "\nRacial Demographics Info:\n";
    return final_title.str() + one.str() + two.str() + three.str() + four.str() + five.str() + six.str() + seven.str() + eight.str() + nine.str() + total.str();
  }

  friend std::ostream &operator<<(std::ostream &out, const psRaceDemogData &SD);

protected:
  double whiteNHCount = 0;
  double blackNHCount = 0;
  double asCount = 0;
  double nativeAmericanCount = 0;
  double hispanicCount = 0;
  double unspecifiedCount = 0;
  double unknownCount = 0; 
  double totalCases = 0;
};

#endif
