#include "CountyMap.h"
#include <fstream>

using namespace std;

//helper to create map from city to county
void CountyMap::read_csvCityCounty(std::string filename) {
     // Create an input filestream
     std::ifstream myFile(filename);

     // Make sure the file is open
     if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
     }

     if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and enter into the map
        while(std::getline(myFile, line)) {

          std::stringstream ss(line);

          std::string city = getField(ss);
          std::string junk1 = getField(ss);  //"city_ascii","city_alt"
          std::string junk0 = getField(ss);
          std::string state = getField(ss);
          std::string junk2 = getField(ss); //"state_name"
          std::string countyfips = getField(ss);
          std::string county = getField(ss);

          std::string Key = county+state;

          keyToCounty[Key] = countyID{county, std::stoi(countyfips)};

          //cout << "line: " << line << endl;
          //cout << "pair (key, county): " << Key << ": " << county << " state " << state << " fip" << countyfips <<  endl;
        }

        // Close file
        myFile.close();
      }
}