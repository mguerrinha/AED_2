#ifndef PROJECT_2_ATFMS_FLIGHTMANAGER_H
#define PROJECT_2_ATFMS_FLIGHTMANAGER_H

#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include "Graph.h"
#include "Flight.h"
#include "Haversine.h"

using namespace std;

/**
 * @brief Classe que representa um sistema de gestão de voos e aeroportos
 */

class FlightManager {
private:
    /// Representa o sistema de voos e aeroportos como um grafo
    static Graph _flightSystem;

    /// Conjunto de voos disponíveis no sistema
    set<Flight> _flights;

    /// Hash table tendo o código de um aeroporto associado a um objeto Airport
    unordered_map<string, Airport> _airportMap;

    /// Hash table tendo o código de uma companhia aérea associada a um objeto Airline
    unordered_map<string, std::shared_ptr<Airline>> _airlineMap;
public:
    /**
     * @brief Constructor default da classe FlightManager
     */
    FlightManager();

    /**
     * @brief Carrega as informações sobre as companhias aéreas a partir de um arquivo CSV
     * Complexidade : O(N)
     * @param file
     */
    void load_airlines(const string &file);

    /**
     * @brief Carrega as informações sobre os aeroportos a partir de um arquivo CSV
     * Complexidade : O(N)
     * @param file
     */
    void load_airports(const string &file);

    /**
     * @brief Carrega as informações sobre os voos a partir de um arquivo CSV
     * Complexidade : O(N)
     * @param file
     */
    void load_flights(const string &file);

    /**
     * @brief Obtém a hash table associada aos aeroportos
     * @return Hash table associada aos aeroportos
     */
    unordered_map<string, Airport> getAirportMap() const;

    /**
     * @brief Obtém o grafo que representa o sistema de voos e aeroportos
     * @return Grafo que representa o sistema de voos e aeroportos
     */
    static const Graph &getFlightSystem();

    /**
     * @brief Obtém o conjunto de voos disponíveis no sistema
     * @return Conjunto de voos disponíveis no sistema
     */
    set<Flight> getFlights() const;

    /**
     * @brief Verifica se um código de aeroporto está presente no sistema
     * Complexidade : O(1)
     * @param airportCode Código do aeroporto a ser verificado
     * @return True se o código do aeroporto estiver presente, false caso contrário
     */
    static bool isAirportCode(const string &airportCode);

    /**
     * @brief Calcula o número de voos e companhias aéreas associadas a um determinado aeroporto
     * Complexidade : O(N)
     * @param airportCode Código do aeroporto
     */
    static void numFlightsAndAirlinesForAirport(const string &airportCode);

    /**
     * @brief Calcula o número de voos que partem e chegam de uma cidade
     * Complexidade : O(N)
     * @param cityName Nome da cidade
     */
    static void numFlightsPerCity(const string &cityName);

    /**
     * @brief Calcula o número de voos associados a uma companhia aérea
     * Complexidade : O(|V| * |E|)
     * @param airlineName Nome da companhia aérea
     */
    static void numFlightsPerAirline(const string &airlineName);

    /**
     * @brief Calcula o número de diferentes países que uma dada cidade tem voos
     * Complexidade : O(|V| * |E|)
     * @param cityName Nome da cidade
     */
    static void numDestCountriesForCity(const string &cityName);

    /**
     * @brief Calcula o número de diferentes países que um dado aeroporto tem voos
     * Complexidade : O(N)
     * @param airportCode Código do aeroporto
     */
    static void numDestCountriesForAirports(const string &airportCode);

    /**
     * @brief Calcula o número total de destinos de um determinado aeroporto
     * Complexidade : O(|V| + |E|)
     * @param airportCode Código do aeroporto
     */
    static void numDestinationsForAirports(const string &airportCode);

    /**
     * @brief Calcula o número de destinos alcançáveis a partir de um aeroporto com um determinado número de paragens
     * Complexidade : O(|V| + |E|)
     * @param airportCode Código do aeroporto
     * @param num_stops Número de paragens desejadas
     */
    static void numReachableDestinations(const string &airportCode, int num_stops);

    /**
     * @brief Encontra o itinerário com a viagem mais longa
     * Complexidade : O(|V| * (|V| + |E|) + N)
     */
    static void maxTrip();

    /**
     * @brief Encontra os aeroportos com o maior número de tráfego aéreo
     * Complexidade : O(|V| + logN)
     * @param num_top Número da lista desejado
     */
    static void topNumAirportWithGreatestAirTraffic(int num_top);

    /**
     * @brief Encontra os aeroportos essenciais, aqueles que quando removidos certas áreas tornam-se inacessíveis
     * Complexidade : O(2|V| + 2(|V| * |E|) + N)
     */
    static void essentialAirports();

    /**
     * @brief Executa uma busca pelos melhores voos entre dois aeroportos, especificados pelos códigos de aeroporto
     * Complexidade : O(|V| + 2|E| + N^2)
     * @param src Código do aeroporto de partida
     * @param dest Código do aeroporto de destino
     * @param graph Grafo no qual a busca será realizada
     */
    static void bestTripAirportCode(const string &src, const string &dest, const Graph &graph);

    /**
     * @brief Transforma o input inicial, neste caso o nome do aeroporto, no código correspondente
     * Complexidade : O(|V|)
     * @param src Aeroporto de origem
     * @param graph Grafo no qual a busca será realizada
     * @return Código do aeroporto de destino
     */
    static string bestTripAirportName(const string &src, const Graph &graph);

    /**
     * @brief Transforma o input inicial, neste caso o nome da cidade, num vetor que contém os códigos dos aeroportos pertencentes à cidade
     * Complexidade : O(|V|)
     * @param srcCity Cidade de origem
     * @param graph Grafo no qual a busca será realizada
     * @return Vetor contendo os códigos dos aeroportos de destino
     */
    static vector<string> bestTripCityName(const std::string &srcCity, const Graph &graph);

    /**
     * @brief Transforma o input inicial, neste caso uma coordenada geográfica, num vetor que contém os códigos dos aeroportos mais próximos da mesma
     * Complexidade : O(|V|)
     * @param source Coordenadas geográficas do ponto de partida
     * @param target Coordenadas geográficas do ponto de destino
     * @param graph Grafo no qual a busca será realizada
     * @return Vetor contendo os códigos dos aeroportos mais próximos ao ponto de partida
     */
    static vector<string> bestTripCoordinates(const Haversine::Coordinates &source, const Graph &graph);

    /**
     * @brief Filtra o grafo pelos códigos de companhias aéreas especificados
     * Complexidade : O(|V| + |V| * |E|)
     * @param airlineCodes Vetor de códigos de companhias aéreas a serem consideradas no filtro
     * @return Novo grafo resultante do filtro
     */
    static Graph filterGraphByAirline(const vector<string> &airlineCodes);
};


#endif //PROJECT_2_ATFMS_FLIGHTMANAGER_H
