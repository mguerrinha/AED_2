#include "Flight.h"

[[maybe_unused]] string Flight::getAirportSource() { return _airportSource; }

[[maybe_unused]] string Flight::getAirportTarget() { return _airportTarget; }

[[maybe_unused]] string Flight::getAirline() { return _airline; }

bool Flight::operator<(const Flight &rhs) const {
    if (_airportSource < rhs._airportSource)
        return true;
    if (rhs._airportSource < _airportSource)
        return false;
    if (_airportTarget < rhs._airportTarget)
        return true;
    if (rhs._airportTarget < _airportTarget)
        return false;
    return _airline < rhs._airline;
}

