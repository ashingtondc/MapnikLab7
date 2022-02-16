
#ifndef RACEDEMOG_H
#define RACEDEMOG_H

#include <math.h>
#include <memory>
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <iostream>

class raceDemogData
{
public:
  raceDemogData(double inW, double inB, double inAIAN, double inA, double inHPI, double in2M, double inHL, double inWNHL) : 
            white(inW), black(inB), americanIndianAlaskNative(inAIAN), asian(inA), hawaiianPacificIslander(inHPI),
            twoOrMore(in2M), hispanicOrLatino(inHL), whiteNotHispanicOrLatino(inWNHL)
  {}

  double getWhite() const { return white; }
  double getBlack() const { return black; }
  double getAmericanIndianAlaskaNative() const { return americanIndianAlaskNative; }
  double getAsian() const { return asian; }
  double getHawPacific() const { return hawaiianPacificIslander; }
  double getTwoOrMore() const { return twoOrMore; }
  double getHispLatino() const { return hispanicOrLatino; }
  double getWhiteNonHispLatino() const { return whiteNotHispanicOrLatino; }

  void addCountyRE(std::shared_ptr<raceDemogData> inRE, double countyPop, double totalPop) {
    white = (inRE->getWhite() * countyPop + white * totalPop) / (countyPop + totalPop);
    black = (inRE->getBlack() * countyPop  + black * totalPop) / (countyPop + totalPop);
    americanIndianAlaskNative = (inRE->getAmericanIndianAlaskaNative() * countyPop + americanIndianAlaskNative * totalPop) / (countyPop + totalPop) ;
    asian = (inRE->getAsian() * countyPop  + asian * totalPop) / (countyPop + totalPop);
    hawaiianPacificIslander = (inRE->getHawPacific() * countyPop  + hawaiianPacificIslander * totalPop) / (countyPop + totalPop);
    twoOrMore = (inRE->getTwoOrMore() * countyPop  + twoOrMore * totalPop) / (countyPop + totalPop);
    hispanicOrLatino = (inRE->getHispLatino() * countyPop  + hispanicOrLatino * totalPop) / (countyPop + totalPop);
    whiteNotHispanicOrLatino = (inRE->getWhiteNonHispLatino() * countyPop  + whiteNotHispanicOrLatino * totalPop) / (countyPop + totalPop);
  }

  void setPopulation(int population) {
    totalPopulation = population;
  }

  std::string communityRacialCount(int population) const {
    std::ostringstream one;
    std::ostringstream two; 
    std::ostringstream three; 
    std::ostringstream four; 
    std::ostringstream five; 
    std::ostringstream six; 
    std::ostringstream seven; 
    std::ostringstream eight;  
    std::ostringstream total;
    std::ostringstream final_title;
    std::ostringstream final;
    one << "% American Indian and Alaska Native Percent: " << americanIndianAlaskNative << " count: " << (int)round(americanIndianAlaskNative * population / 100.0) << "\n";
    two << "% Asian American percent: " << asian << " count: " << (int)round(asian * population / 100) << "\n";
    three << "% Black/African American percent: " << black << " count: " << (int)round(black * population / 100) << "\n";
    four << "% Hispanic or Latinx percent: " << hispanicOrLatino << " count: " << (int)round(hispanicOrLatino * population) / 100 << "\n";
    five << "% Native Hawaiian and Other Pacific Islander: " << hawaiianPacificIslander << " count: " << (int)round(hawaiianPacificIslander * population / 100) << "\n";
    six << "% Two or More Races percent: " << twoOrMore << " count: " << (int)round(twoOrMore * population / 100) << "\n";
    seven << "% White (inclusive) percent: " << white << " count: " << (int)round(white * population / 100) << "\n";
    eight << "% White (nonHispanic) percent: " << whiteNotHispanicOrLatino << " count: " << (int)round(whiteNotHispanicOrLatino * population / 100) << "\n";
    total << "total Racial Demographic Count: " << population << "\n";
    final_title << "\nRacial Demographics Info:\n";
    return final_title.str() + one.str() + two.str() + three.str() + four.str() + five.str() + six.str() + seven.str() + eight.str() + total.str();
  }

  friend std::ostream &operator<<(std::ostream &out, const raceDemogData &SD);

private:
  double white;
  double black;
  double americanIndianAlaskNative;
  double asian;
  double hawaiianPacificIslander;
  double twoOrMore;
  double hispanicOrLatino;
  double whiteNotHispanicOrLatino;
  double totalPopulation = 0;
};
#endif
