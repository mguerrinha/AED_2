#ifndef PROJECT_2_ATFMS_AIRPORT_H
#define PROJECT_2_ATFMS_AIRPORT_H

#include <string>
#include <utility>

using namespace std;

/**
 * @brief Classe que representa um aeroporto
 */

class Airport {
private:
    /// Código do aeroporto
    string _code;

    /// Nome do aeroporto
    string _name;

    /// Cidade do aeroporto
    string _city;

    /// País do aeroporto
    string _country;

    /// Latitude do aeroporto
    double _latitude;

    /// Longitude do aeroporto
    double _longitude;

public:
    /**
     * @brief Retorna o código do aeroporto
     * @return Código do aeroporto
     */
    [[nodiscard]] string getCode() const;

    /**
     * @brief Retorna o nome do aeroporto
     * @return Nome do aeroporto
     */
    [[nodiscard]] string getName() const;

    /**
     * @brief Retorna a cidade do aeroporto
     * @return Cidade do aeroporto
     */
    [[nodiscard]] string getCity() const;

    /**
     * @brief Retorna o país do aeroporto
     * @return País do aeroporto
     */
    [[nodiscard]] string getCountry() const;

    /**
     * @brief Retorna a latitude do aeroporto
     * @return Latitude do aeroporto
     */
    [[nodiscard]] double getLatitude() const;

    /**
     * @brief Longitude do aeroporto
     * @return Longitude do aeroporto
     */
    [[nodiscard]] double getLongitude() const;

    /**
     * @brief Constructor da classe Airport
     * @param code Código do aeroporto
     * @param name Nome do aeroporto
     * @param city Cidade do aeroporto
     * @param country País do aeroporto
     * @param latitude Latitude do aeroporto
     * @param longitude Longitude do aeroporto
     */
    Airport(string code, string name, string city, string country, double latitude, double longitude) : _code(
            std::move(code)), _name(std::move(name)), _city(std::move(city)), _country(std::move(country)), _latitude(
            latitude), _longitude(longitude) {};

    /**
     * @brief Operador de igualdade
     * @param airport Aeroporto a comparar
     * @return True se os códigos dos aeroportos forem iguais, false caso contrário
     */
    bool operator==(const Airport &airport) const;

    /**
     * @brief Operador de menor
     * @param rhs Aeroporto a comparar
     * @return True se o código do aeroporto for menor, false caso contrário
     */
    bool operator<(const Airport &rhs) const;
};


#endif //PROJECT_2_ATFMS_AIRPORT_H
