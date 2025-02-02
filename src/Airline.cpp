#include "Airline.h"

string Airline::getCode() const { return _code; }

string Airline::getName() const { return _name; }

[[maybe_unused]] string Airline::getCallSign() const { return _callSign; }

[[maybe_unused]] string Airline::getCountry() const { return _country; }

bool Airline::operator<(const Airline &rhs) const {
    return _code < rhs._code;
}
