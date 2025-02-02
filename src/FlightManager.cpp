#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <climits>
#include "FlightManager.h"
#include "Airline.h"
#include "Airport.h"

FlightManager::FlightManager() = default;

Graph FlightManager::_flightSystem;

void FlightManager::load_airlines(const string &file) {
    ifstream arquivo(file);
    string linha;
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
        stringstream linhaStream(linha);
        string code, name, callsign, country;
        if (getline(linhaStream, code, ',')
            && getline(linhaStream, name, ',')
            && getline(linhaStream, callsign, ',')
            && getline(linhaStream, country, ',')) {
            _airlineMap.emplace(code, std::make_shared<Airline>(code, name, callsign, country));
        }
    }
}

void FlightManager::load_airports(const std::string &file) {
    ifstream arquivo(file);
    string linha;
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
        stringstream linhaStream(linha);
        string code, name, city, country, latitude, longitude;
        if (getline(linhaStream, code, ',')
            && getline(linhaStream, name, ',')
            && getline(linhaStream, city, ',')
            && getline(linhaStream, country, ',')
            && getline(linhaStream, latitude, ',')
            && getline(linhaStream, longitude, ',')) {
            Airport airport(code, name, city, country, stod(latitude), stod(longitude));
            _airportMap.emplace(code, airport);
            _flightSystem.addVertex(airport);
        }
    }
}

void FlightManager::load_flights(const std::string &file) {
    ifstream arquivo(file);
    string linha;
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
        stringstream linhaStream(linha);
        string source, target, airline;
        if (getline(linhaStream, source, ',')
            && getline(linhaStream, target, ',')
            && getline(linhaStream, airline, ',')) {
            _flights.emplace(source, target, airline);
            _flightSystem.addEdge(_airportMap.at(source), _airportMap.at(target), _airlineMap.at(airline));
        }

    }
}

unordered_map<string, Airport> FlightManager::getAirportMap() const {
    return _airportMap;
}

set<Flight> FlightManager::getFlights() const {
    return _flights;
}

const Graph &FlightManager::getFlightSystem() {
    return _flightSystem;
}

bool FlightManager::isAirportCode(const string &airportCode) {
    return _flightSystem.getVertexSet().find(airportCode) != _flightSystem.getVertexSet().end();
}

void FlightManager::numFlightsAndAirlinesForAirport(const string &airportCode) {
    if (!isAirportCode(airportCode)) {
        std::cout << "Aeroporto não encontrado." << std::endl;
        return;
    }

    Vertex *airport = _flightSystem.getVertexSet().at(airportCode);
    auto flightsOut = airport->getAdj().size();
    set<shared_ptr<Airline>> temp;
    for (const auto &line: airport->getAdj()) {
        temp.insert(line.getWeight());
    }
    auto airlinesOut = temp.size();

    std::cout << "Número de voos que saem de " << airport->getInfo().getName() << ": " << flightsOut << std::endl;
    std::cout << "Número de companhias aérias disponíveis: " << airlinesOut << std::endl;


}

void FlightManager::numFlightsPerCity(const string &cityName) {
    unsigned totalFlights = 0;
    for (const auto &airport: _flightSystem.getVertexSet()) {
        if (airport.second->getInfo().getCity() == cityName) {
            totalFlights += airport.second->getAdj().size();
            totalFlights += airport.second->getIndegree();
        }
    }
    std::cout << "O número de voos que partem ou chegam a " << cityName << " é: " << totalFlights << std::endl;
}

void FlightManager::numFlightsPerAirline(const string &airlineName) {
    unsigned totalFlights = 0;
    for (const auto &v: _flightSystem.getVertexSet()) {
        for (const auto &e: v.second->getAdj()) {
            if (e.getWeight()->getName() == airlineName) {
                totalFlights++;
            }
        }
    }
    std::cout << "O número de voos da companhia " << airlineName << " é: " << totalFlights << std::endl;
}

void FlightManager::numDestCountriesForCity(const string &cityName) {
    set<string> countries;
    for (const auto &v: _flightSystem.getVertexSet()) {
        if (v.second->getInfo().getCity() == cityName) {
            for (const auto &e: v.second->getAdj()) {
                countries.insert(e.getDest()->getInfo().getCountry());
            }
        }
    }
    std::cout << "O número de países para os quais " << cityName << " tem voos é: " << countries.size() << std::endl;
}

void FlightManager::numDestCountriesForAirports(const string &airportCode) {
    if (!isAirportCode(airportCode)) {
        std::cout << "Aeroporto não encontrado." << std::endl;
        return;
    }
    set<string> countries;
    for (const auto &e: _flightSystem.getVertexSet().at(airportCode)->getAdj()) {
        countries.insert(e.getDest()->getInfo().getCountry());
    }
    std::cout << "O número de países para os quais " << airportCode << " tem voos é: " << countries.size() << std::endl;
}

void FlightManager::numDestinationsForAirports(const string &airportCode) {
    if (!isAirportCode(airportCode)) {
        std::cout << "Aeroporto não encontrado." << std::endl;
        return;
    }

    int numAirports = 0;
    set<pair<string, string>> cities;
    set<string> countries;

    Vertex *airport = _flightSystem.getVertexSet().at(airportCode);

    for (const auto &pair: _flightSystem.getVertexSet()) {
        pair.second->setVisited(false);
    }

    queue<Vertex *> bfsQueue;
    bfsQueue.push(airport);
    airport->setVisited(true);

    while (!bfsQueue.empty()) {
        Vertex *currentVertex = bfsQueue.front();
        bfsQueue.pop();

        for (const auto &e: currentVertex->getAdj()) {
            Vertex *neighbor = e.getDest();
            if (!neighbor->isVisited()) {
                numAirports++;
                cities.insert({neighbor->getInfo().getCity(), neighbor->getInfo().getCountry()});
                countries.insert(neighbor->getInfo().getCountry());
                bfsQueue.push(neighbor);
                neighbor->setVisited(true);
            }
        }
    }
    std::cout << "O número de destinos para os quais " << airport->getInfo().getName() << " tem voos é: " << std::endl;
    std::cout << "Aeroportos: " << numAirports << std::endl;
    std::cout << "Cidades: " << cities.size() << std::endl;
    std::cout << "Países: " << countries.size() << std::endl;
}

void FlightManager::numReachableDestinations(const string &airportCode, int num_stops) {
    if (!isAirportCode(airportCode)) {
        std::cout << "Aeroporto não encontrado." << std::endl;
        return;
    }

    int num_airports = 0;
    set<pair<string, string>> aux_cities;
    set<string> aux_countries;
    Vertex *airport = _flightSystem.getVertexSet().at(airportCode);

    for (const auto &pair: _flightSystem.getVertexSet()) {
        pair.second->setVisited(false);
    }

    queue<pair < Vertex * , int>>
    bfsQueue;
    bfsQueue.emplace(airport, 0);
    airport->setVisited(true);

    while (!bfsQueue.empty()) {
        auto [currentVertex, dist] = bfsQueue.front();
        bfsQueue.pop();

        if (dist >= num_stops) continue;

        for (const auto &e: currentVertex->getAdj()) {
            Vertex *neighbor = e.getDest();
            if (!neighbor->isVisited()) {
                num_airports++;
                aux_cities.insert({neighbor->getInfo().getCity(), neighbor->getInfo().getCountry()});
                aux_countries.insert(neighbor->getInfo().getCountry());
                bfsQueue.emplace(neighbor, dist + 1);
                neighbor->setVisited(true);
            }
        }
    }

    std::cout << "O número de destinos para os quais " << airport->getInfo().getName() << " tem voos com até "
              << num_stops << " paragens é: " << std::endl;
    std::cout << "Aeroportos: " << num_airports << std::endl;
    std::cout << "Cidades: " << aux_cities.size() << std::endl;
    std::cout << "Países: " << aux_countries.size() << std::endl;
}

void FlightManager::maxTrip() {
    int maxTrip = 0;

    vector<pair<string, string >> maxTripPath;
    for (const auto &vertex: _flightSystem.getVertexSet()) {
        Vertex *v = vertex.second;
        for (const auto &vertex1: _flightSystem.getVertexSet()) {
            vertex1.second->setVisited(false);
            vertex1.second->setLongestTrip(0);
        }
        queue<Vertex *> q;
        v->setVisited(true);
        q.push(v);

        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            for (auto &e: current->getAdj()) {
                if (!e.getDest()->isVisited()) {
                    e.getDest()->setLongestTrip(current->getLongestTrip() + 1);
                    if (e.getDest()->getLongestTrip() > maxTrip) {
                        maxTripPath.clear();
                        maxTripPath.emplace_back(v->getInfo().getCode(), e.getDest()->getInfo().getCode());
                    } else if (e.getDest()->getLongestTrip() == maxTrip) {
                        maxTripPath.emplace_back(v->getInfo().getCode(), e.getDest()->getInfo().getCode());
                    }
                    maxTrip = max(maxTrip, e.getDest()->getLongestTrip());
                    q.push(e.getDest());
                    e.getDest()->setVisited(true);
                }
            }
        }
    }
    std::cout << "A(s) viagem(s) com o maior número de paragem(ns) é(são): " << std::endl;
    for (auto &pair: maxTripPath) {
        cout << "De " << pair.first << " para " << pair.second << endl;
    }
    std::cout << "O comprimento máximo de um voo é: " << maxTrip << " paragens" << std::endl;
}

void FlightManager::topNumAirportWithGreatestAirTraffic(int num_top) {
    vector<pair<Vertex *, int>> airports;
    for (const auto &v: _flightSystem.getVertexSet()) {
        airports.emplace_back(v.second, v.second->getAdj().size() + v.second->getIndegree());
    }
    sort(airports.begin(), airports.end(), [](const pair<Vertex *, int> &a, const pair<Vertex *, int> &b) {
        return a.second > b.second;
    });
    if (num_top <= airports.size()) {
        cout << "Aeroporto com o " << num_top << "º maior número de voos: "
             << airports[num_top - 1].first->getInfo().getName() << endl;
        cout << "Número total de voos: " << airports[num_top - 1].second << endl;
    }
}

void dfsAux(const Graph &g, Vertex *vertex, stack<Airport> &s, unordered_set<string> &res, int &i);

void FlightManager::essentialAirports() {
    Graph undirectedGraph;

    for (const auto &vertex: _flightSystem.getVertexSet()) {
        undirectedGraph.addVertex(vertex.second->getInfo());
    }

    for (const auto &vertex: _flightSystem.getVertexSet()) {
        for (const auto &edge: vertex.second->getAdj()) {
            Airport a = vertex.second->getInfo();
            Airport b = edge.getDest()->getInfo();
            undirectedGraph.addEdge(a, b, edge.getWeight());
            undirectedGraph.addEdge(b, a, edge.getWeight());
        }
    }
    unordered_set<string> res;
    stack<Airport> s;
    int i = 0;
    for (auto vertex: undirectedGraph.getVertexSet()) {
        vertex.second->setNum(i);
    }

    i++;
    for (const auto &vertex: undirectedGraph.getVertexSet()) {
        if (vertex.second->getNum() == 0) {
            dfsAux(undirectedGraph, vertex.second, s, res, i);
        }
    }
    int count = 0;
    for (const auto &aux: res) {
        count++;
        auto v = undirectedGraph.getVertexSet().find(aux);
        std::cout << v->second->getInfo().getName() << std::endl;
    }
    cout << "Existem " << count << " aeroportos essenciais" << endl;
}

void dfsAux(const Graph &g, Vertex *vertex, stack<Airport> &s, unordered_set<string> &res, int &i) {
    vertex->setNum(i);
    vertex->setLow(i);
    i++;
    int children = 0;
    s.push(vertex->getInfo());
    for (const auto &edge: vertex->getAdj()) {
        if (edge.getDest()->getNum() == 0) {
            children++;
            dfsAux(g, edge.getDest(), s, res, i);
            vertex->setLow(min(vertex->getLow(), edge.getDest()->getLow()));
            if (vertex->getInfo().getCode() != g.getVertexSet().begin()->second->getInfo().getCode() &&
                edge.getDest()->getLow() >= vertex->getNum()) {
                res.insert(vertex->getInfo().getCode());
            }
        } else if (edge.getDest()->getNum() > 0) {
            vertex->setLow(min(vertex->getLow(), edge.getDest()->getNum()));
        }
    }
    s.pop();
    if (vertex->getInfo() == g.getVertexSet().begin()->second->getInfo() && children > 1) {
        res.insert(vertex->getInfo().getCode());
    }
}

void dfs(Vertex *current, Vertex *destination, vector<Airport> &currentPath, vector<vector<Airport>> &path);

void FlightManager::bestTripAirportCode(const string &src, const string &dest, const Graph &graph) {
    if (!isAirportCode(src) || !isAirportCode(dest)) {
        std::cout << "Aeroporto não encontrado." << std::endl;
        return;
    }

    Vertex *source = graph.getVertexSet().at(src);
    Vertex *destination = graph.getVertexSet().at(dest);
    priority_queue<pair<int, Vertex *>> pq;

    for (const auto &vertex: graph.getVertexSet()) {
        vertex.second->setVisited(false);
        vertex.second->setStops(INT_MAX);
    }

    source->setStops(0);
    pq.emplace(0, source);

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();
        auto currentVertex = current.second;
        if (currentVertex->isVisited()) continue;
        currentVertex->setVisited(true);
        for (const auto &e: currentVertex->getAdj()) {
            int aux = currentVertex->getStops() + 1;
            if (e.getDest()->getStops() >= aux) {
                e.getDest()->setStops(aux);
                pq.emplace(-aux, e.getDest());
            }
        }
    }

    if (destination->getStops() == INT_MAX) {
        std::cout << "Não existe caminho entre " << source->getInfo().getName() << " e "
                  << destination->getInfo().getName() << std::endl;
        return;
    }

    vector<vector<Airport>> path;
    vector<Airport> currentPath;
    dfs(source, destination, currentPath, path);

    std::cout << "O(s) melhor(es) caminho(s) entre " << source->getInfo().getName() << " e "
              << destination->getInfo().getName() << " é(são): " << std::endl;
    for (const auto &i: path) {
        for (const auto &j: i) {
            std::cout << j.getName() << " -> ";
        }
        std::cout << destination->getInfo().getName() << std::endl;
    }
    std::cout << "Número de paragens: " << destination->getStops() - 1 << std::endl;
}

void dfs(Vertex *current, Vertex *destination, vector<Airport> &currentPath, vector<vector<Airport>> &path) {
    if (current == destination) {
        if (currentPath.size() < destination->getStops()) {
            return;
        }
        path.push_back(currentPath);
        return;
    }
    currentPath.push_back(current->getInfo());
    for (const auto &e: current->getAdj()) {
        if (e.getDest()->getStops() == current->getStops() + 1) {
            dfs(e.getDest(), destination, currentPath, path);
            if (currentPath.empty()) {
                return;
            }
            currentPath.pop_back();
        }
    }
}

string FlightManager::bestTripAirportName(const string &src, const Graph &graph = _flightSystem) {
    Vertex *source = nullptr;
    for (const auto &vertex: graph.getVertexSet()) {
        if (vertex.second->getInfo().getName() == src) {
            source = vertex.second;
        }
    }
    if (source == nullptr) {
        std::cout << "Aeroportos de origem ou destino não encontrados." << std::endl;
        return "";
    }
    return source->getInfo().getCode();
}

vector<string> FlightManager::bestTripCityName(const std::string &srcCity, const Graph &graph = _flightSystem) {
    vector<string> sourceAirports;
    for (const auto &vertex: graph.getVertexSet()) {
        if (vertex.second->getInfo().getCity() == srcCity) {
            sourceAirports.push_back(vertex.second->getInfo().getCode());
        }
    }
    if (sourceAirports.empty()) {
        std::cout << "Aeroportos de origem ou destino não encontrados." << std::endl;
        return {};
    }
    return sourceAirports;
}

vector<string>
FlightManager::bestTripCoordinates(const Haversine::Coordinates &source, const Graph &graph = _flightSystem) {
    vector<string> nearestSourceAirports;
    double minSourceDistance = INT_MAX;

    for (const auto &vertexPair: graph.getVertexSet()) {
        const auto &airport = vertexPair.second->getInfo();
        double sourceDistance = Haversine::calculateDistance(source, {airport.getLatitude(), airport.getLongitude()});

        if (sourceDistance < minSourceDistance) {
            nearestSourceAirports.clear();
            minSourceDistance = sourceDistance;
        }
        if (sourceDistance == minSourceDistance) {
            nearestSourceAirports.push_back(airport.getCode());
        }
    }

    if (nearestSourceAirports.empty()) {
        std::cout << "Aeroportos mais próximos não encontrados." << std::endl;
        return {};
    }
    return nearestSourceAirports;
}

Graph FlightManager::filterGraphByAirline(const vector<string> &airlineCodes) {
    Graph filteredGraph;
    for (const auto &vertexPair: _flightSystem.getVertexSet()) {
        filteredGraph.addVertex(vertexPair.second->getInfo());
    }

    for (const auto &vertexPair: _flightSystem.getVertexSet()) {
        for (const auto &edge: vertexPair.second->getAdj()) {
            if (std::find(airlineCodes.begin(), airlineCodes.end(), edge.getWeight()->getCode()) !=
                airlineCodes.end()) {
                filteredGraph.addEdge(vertexPair.second->getInfo(), edge.getDest()->getInfo(), edge.getWeight());
            }
        }
    }

    return filteredGraph;
}


