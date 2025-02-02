#ifndef PROJECT_2_ATFMS_FLIGHT_H
#define PROJECT_2_ATFMS_FLIGHT_H

#include <string>
#include <utility>

using namespace std;

/**
 * @brief Classe que representa um voo
 */

class Flight {
private:
    /// Aeroporto de partida do voo
    string _airportSource;

    /// Aeroporto de destino do voo
    string _airportTarget;

    /// Companhia aérea associada ao voo
    string _airline;

public:
    /**
     * @brief Constructor da classe Flight
     * @param airportSource Aeroporto de partida do voo
     * @param airportTarget Aeroporto de destino do voo
     * @param airline Companhia aérea associada ao voo
     */
    Flight(string airportSource, string airportTarget, string airline) : _airportSource(std::move(airportSource)),
                                                                         _airportTarget(std::move(airportTarget)),
                                                                         _airline(std::move(airline)) {};

    /**
     * @brief Retorna o aeroporto de partida do voo
     * @return Aeroporto de partida do voo
     */
    [[maybe_unused]] string getAirportSource();

    /**
     * @brief Retorna o aeroporto de destino do voo
     * @return Aeroporto de destino do voo
     */
    [[maybe_unused]] string getAirportTarget();

    /**
     * @brief Retorna a companhia aérea associada ao voo
     * @return Companhia aérea associada ao voo
     */
    [[maybe_unused]] string getAirline();

    /**
     * @brief Operador de menor
     * @param rhs Voo a comparar
     * @return True se o voo atual for menor que o voo rhs, false caso contrário
     */
    bool operator<(const Flight &rhs) const;
};


#endif //PROJECT_2_ATFMS_FLIGHT_H
