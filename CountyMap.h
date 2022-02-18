/* ZJW helper code to get county ids - works in conjunction with uscities.csv file*/

#ifndef COUNTMAP_H
#define COUNTMAP_H

#include  <map>
#include <iostream>
#include "parse.h"

/* helper struct */
typedef struct countyID {
    std::string countyName;
    int countyfips;
} countyID;

class CountyMap {
  public:
	CountyMap(std::string filename) {
		noMatch = 0;
        read_csvCityCounty(filename);
	}

	void read_csvCityCounty(std::string fileIn);

  public:
	std::map<std::string, countyID> keyToCounty;
	int noMatch = 0;
};

#endif

