/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>

/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) {
    temp.erase(
        remove(temp.begin(), temp.end(), '\"' ),
        temp.end());
    return temp;
}

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss) {
    string data, junk;
    //ignore the first quotes
    std::getline(ss, junk, '\"');
    //read the data (not to comma as some data includes comma (Hospital names))
    std::getline(ss, data, '\"');
    //read to comma final comma (to consume and prep for next)
    std::getline(ss, junk, ',');
    //data includes final quote (see note line 18)
    return stripQuotes(data);
}

string getFieldNQ(std::stringstream &ss)
{
    string temp;
    std::getline(ss, temp, ',');
    //std::cout << temp << std:: endl;
    return temp;
}

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile) {
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while(std::getline(ss, colname, ',')) {
    //    std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<demogData> readCSVLineDemog(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string state = getField(ss);
    double popOver65 = stod(getField(ss));
    double popUnder18 = stod(getField(ss));
    double popUnder5 = stod(getField(ss)); 
    double bachelorDegreeUp = stod(getField(ss));
    double highSchoolUp = stod(getField(ss));
    //skip 1
    getField(ss);
    //store initial data as percent (then convert to count)
    double FirstNation= stod(getField(ss));
    double Asian= stod(getField(ss));
    double Black= stod(getField(ss));
    double Latinx= stod(getField(ss));
    double HIPacificIsle= stod(getField(ss));
    double MultiRace= stod(getField(ss));
    double White= stod(getField(ss));
    double WhiteNH = stod(getField(ss));
    float homeOwnRate = stod(getField(ss));
    int numHouseHold = stoi(getField(ss));
    //skip 2
    int housingUnits = stoi(getField(ss));
    getField(ss);
    float avgPerPerHouse = stod(getField(ss));
    //turn into mathematical percent
    long int houseIncome = stoi(getField(ss));
    //skip 1
    getField(ss);
    double foreignBorn= stod(getField(ss));
    //skip 5
    for (int i=0; i < 5; i++)
        getField(ss);
    double popFemale = stod(getField(ss));
    int veterans = stoi(getField(ss));
    int totalPop2020 = stoi(getField(ss));

    //community racial mix created with counts not percents
    /*TO DO construct your type for race/ethnicity info */

    //store demographic data as counts
    /*TO DO fix to construct your type */
   return make_shared<demogData>(name, state, totalPop2020, popOver65, popUnder18,
                                  popUnder5, popFemale,
                                  make_shared<raceDemogData>(White, Black, FirstNation, Asian,
                                                                 HIPacificIsle, MultiRace, Latinx, WhiteNH),
                                  houseIncome, avgPerPerHouse, veterans, highSchoolUp,
                                  bachelorDegreeUp, foreignBorn, housingUnits, homeOwnRate, numHouseHold);
}

//read one line of police data
shared_ptr<psData> readCSVLinePolice(std::string theLine) {
    std::stringstream ss(theLine);
    
    //TO DO read in the fields - use getFieldNQ as no quotes!!
    getField(ss); //ignore id
    string name = getField(ss);
    //skip 2
    getField(ss);
    getField(ss);
   //fill in
    string armed = getField(ss);
    getField(ss);
    getField(ss);
    string race = getField(ss);
    string city = getField(ss);
    string state = getField(ss);
    bool mental = getField(ss) == "TRUE";
    getField(ss);
    getField(ss);
    bool bodyCamera = getField(ss) == "TRUE";
    getField(ss);
    getField(ss);
    getField(ss);

    /* TO DO fix */
    return make_shared<psData>(state, city, name, race, mental, armed, bodyCamera);
}

//read from a CSV file (for a given data type) return a vector of the data
// DO NOT modify 
std::vector<shared_ptr<demogData> > read_csv(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<demogData> > theData;

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

        // Now read data, line by line and create demographic dataobject
        while(std::getline(myFile, line)) {
            if (fileType == DEMOG) {
                theData.push_back(readCSVLineDemog(line));
            } else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }

    return theData;
}


// Reads a CSV file 
std::vector<shared_ptr<psData> > read_csvPolice(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<psData> > theData;

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

        // Now read data, line by line and create a county info object
        while(std::getline(myFile, line)) {
            if (fileType == POLICE) {
                theData.push_back(readCSVLinePolice(line));
            } else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            } 
        }
        // Close file
        myFile.close();
    }
    return theData;
}


