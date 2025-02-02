#include "Airport.h"

string Airport::getCode() const { return _code; }

string Airport::getName() const { return _name; }

string Airport::getCity() const { return _city; }

string Airport::getCountry() const { return _country; }

double Airport::getLatitude() const { return _latitude; }

double Airport::getLongitude() const { return _longitude; }

bool Airport::operator==(const Airport &airport) const {
    return _code == airport._code;
}

bool Airport::operator<(const Airport &rhs) const {
    return _code < rhs._code;
}


