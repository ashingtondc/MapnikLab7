#include <sstream>
#include "psData.h"

/* print police data - fill in*/
std::ostream& operator<<(std::ostream &out, const psData &PD) {
    out << "Police Shotting Info: " << PD.state;
    out << "\nPerson name: " ;
    out << "\nRace:" ;
   out << "\nArmed: " ;
    out << "\nMental Illness: " ; //True or False
    out << "\nBody Camera On: "; //True or False
    return out;
}
