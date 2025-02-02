#ifndef PROJECT_2_ATFMS_AIRLINE_H
#define PROJECT_2_ATFMS_AIRLINE_H

#include <string>
#include <utility>

using namespace std;

/**
 * @brief Classe que representa uma companhia aérea
 */

class Airline {
private:
    /// Código da companhia aérea
    string _code;

    /// Nome da companhia aérea
    string _name;

    /// Call sign da companhia aérea
    string _callSign;

    /// País de origem da companhia aérea
    string _country;

public:
    /**
     * @brief Retorna o código da companhia aérea
     * @return Código da companhia aérea
     */
    [[nodiscard]] string getCode() const;

    /**
     * @brief Retorna o nome da companhia aérea
     * @return Nome da companhia aérea
     */
    [[nodiscard]] string getName() const;

    /**
     * @brief Retorna o call sign da companhia aérea
     * @return Call sign da companhia aérea
     */
    [[maybe_unused]] [[nodiscard]] string getCallSign() const;

    /**
     * @brief Retorna o país de origem da companhia aérea
     * @return País de origem da companhia aérea
     */
    [[maybe_unused]] [[nodiscard]] string getCountry() const;

    /**
     * @brief Constructor da classe Airline
     * @param code Código da companhia aérea
     * @param name Nome da companhia aérea
     * @param callSign Call sign da companhia aérea
     * @param country País de origem da companhia aérea
     */
    Airline(string code, string name, string callSign, string country) : _code(std::move(code)), _name(std::move(name)),
                                                                         _callSign(std::move(callSign)),
                                                                         _country(std::move(country)) {};

    /**
     * @brief Operador de menor
     * @param rhs Diferente companhia aérea a comparar
     * @return Retorna true se o código da companhia aérea for menor que o código da companhia aérea passada como argumento
     */
    bool operator<(const Airline &rhs) const;
};


#endif //PROJECT_2_ATFMS_AIRLINE_H
