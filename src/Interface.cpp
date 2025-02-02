#include "Interface.h"
#include <iostream>

Interface::Interface() = default;

FlightManager Interface::_flightManager;

void Interface::run() {
    system("clear");


    _flightManager.load_airlines("../dataset/airlines.csv");
    _flightManager.load_airports("../dataset/airports.csv");
    _flightManager.load_flights("../dataset/flights.csv");


    bool running = true;

    cout << "Bem vindo ao sistema de gerenciamento de voos!" << endl;


    while (running) {
        int choice = displayMainMenu();
        std::string lol;
        std::string lol2;
        switch (choice) {
            case 0:
                cout << "Obrigado por utilizar o nosso sistema de gerenciamento de voos!" << endl;
                std::cout << "Prima Enter para terminar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
                running = false;
                break;

            case 1:
                geralInformationMenu();
                break;

            case 2:
                flightInformationMenu();
                break;

            case 3:
                bestFlightsMenu1();
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }

}

int Interface::displayMainMenu() {
    system("clear");
    cout << "---------------- Sistema de gestão de voos ----------------" << endl;
    cout << "1 - Informações gerais sobre aeroportos, campanhias aéreas e cidades." << endl;
    cout << "2 - Informações gerais sobre voos." << endl;
    cout << "3 - Melhor viagem entre dois aeroportos." << endl;
    cout << "0 - Sair" << endl;
    cout << "Selecione uma opção: ";
    int choice;
    cin >> choice;
    return choice;
}

void Interface::geralInformationMenu() {
    bool running = true;
    while (running) {
        int choice = displayGeralInformationMenu();
        std::string lol;
        switch (choice) {
            case 0:
                running = false;
                break;

            case 1:
                cout << "Número de aeroportos: " << _flightManager.getAirportMap().size() << endl;
                cout << "Número de voos disponíveis: " << _flightManager.getFlights().size() << endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                break;

            case 2:
                std::cout << "Qual é o código do Aeroporto?" << std::endl;
                std::cin >> lol;
                FlightManager::numFlightsAndAirlinesForAirport(lol);
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                break;

            case 3:
                std::cout << "Qual é o nome da cidade?" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, lol);
                FlightManager::numFlightsPerCity(lol);
                std::cout << "Prima Enter para continuar.";
                std::cin.get();
                break;

            case 4:
                std::cout << "Qual é o nome (não o código) da companhia aérea?" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, lol);
                FlightManager::numFlightsPerAirline(lol);
                std::cout << "Prima Enter para continuar.";
                std::cin.get();
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

int Interface::displayGeralInformationMenu() {
    system("clear");
    cout << "---------------- Informações gerais ----------------" << endl;
    cout << "1 - Número de aeroportos e número de voos disponiveis." << endl;
    cout << "2 - Número de voos de saída e airlines de um aeroporto." << std::endl;
    cout << "3 - Número de voos total numa cidade." << std::endl;
    cout << "4 - Número de voos de uma airline." << std::endl;
    cout << "0 - Voltar atrás" << endl;
    cout << "Selecione uma opção: ";
    int choice;
    cin >> choice;
    return choice;

}

void Interface::flightInformationMenu() {
    bool running = true;
    while (running) {
        int choice = displayFlightInformationMenu();
        std::string lol;
        int num;
        switch (choice) {
            case 0:
                running = false;
                break;

            case 1:
                std::cout << "Qual é o nome da cidade?" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, lol);
                FlightManager::numDestCountriesForCity(lol);
                std::cout << "Prima Enter para continuar.";
                std::cin.get();
                break;

            case 2:
                std::cout << "Qual é o código do Aeroporto?" << std::endl;
                std::cin >> lol;
                FlightManager::numDestCountriesForAirports(lol);
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                break;

            case 3:
                std::cout << "Qual é o código do Aeroporto?" << std::endl;
                std::cin >> lol;
                FlightManager::numDestinationsForAirports(lol);
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                break;

            case 4:
                cout << "Qual o código do aeroporto pretendido?" << endl;
                cin >> lol;
                cout << "E o número de paragens máximas?" << endl;
                cin >> num;
                FlightManager::numReachableDestinations(lol, num);
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                break;

            case 5:
                FlightManager::maxTrip();
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                break;

            case 6:
                cout << "Posição desejada : ";
                cin >> num;
                FlightManager::topNumAirportWithGreatestAirTraffic(num);
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                break;

            case 7:
                FlightManager::essentialAirports();
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

int Interface::displayFlightInformationMenu() {
    system("clear");
    cout << "---------------- Informações gerais de voos ----------------" << endl;
    cout << "1 - Número de países para o qual se pode voar partindo de uma dada cidade." << std::endl;
    cout << "2 - Número de países para o qual se pode voar partindo de um dado aeroporto." << std::endl;
    cout << "3 - Número de destinos disponíveis a partir de um dado aeroporto." << endl;
    cout << "4 - Número de aeroportos, cidades e países atingíveis dentro de um certo número de paragens." << endl;
    cout << "5 - Maior viagem possível." << std::endl;
    cout << "6 - O enésimo aeroporto com o maior número de voos." << endl;
    cout << "7 - Aeroportos essenciais." << std::endl;
    cout << "0 - Voltar atrás" << endl;
    cout << "Selecione uma opção: ";
    int choice;
    cin >> choice;
    return choice;
}

void Interface::bestFlightsMenu1() {
    bool running = true;
    vector<string> ap1;
    while (running) {
        Graph graph = filterFlightsByAirline();
        int choice = displayBestFlightsMenu1();
        std::string lol, lol2;
        double lat1, long1;
        switch (choice) {
            case 0:
                running = false;
                break;

            case 1:
                cout << "Qual o código do aeroporto de partida?" << endl;
                cin >> lol;
                ap1.push_back(lol);
                bestFlightsMenu2(ap1, graph);
                running = false;
                break;

            case 2:
                cout << "Qual o nome do aeroporto de partida?" << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, lol);
                ap1.push_back(FlightManager::bestTripAirportName(lol, graph));
                bestFlightsMenu2(ap1, graph);
                running = false;
                break;

            case 3:
                cout << "Qual o nome da cidade de partida?" << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, lol);
                ap1 = FlightManager::bestTripCityName(lol, graph);
                bestFlightsMenu2(ap1, graph);
                running = false;
                break;

            case 4:
                cout << "Qual a latitude do aeroporto de partida?" << endl;
                cin >> lat1;
                cout << "Qual a longitude do aeroporto de partida?" << endl;
                cin >> long1;
                ap1 = FlightManager::bestTripCoordinates(Haversine::Coordinates{lat1, long1}, graph);
                bestFlightsMenu2(ap1, graph);
                running = false;
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

int Interface::displayBestFlightsMenu1() {
    system("clear");
    cout << "---------------- Melhor viagem entre dois aeroportos ----------------" << endl;
    cout << "1 - Código do aeroporto de partida" << endl;
    cout << "2 - Nome do aeroporto de partida" << endl;
    cout << "3 - Cidade do aeroporto de partida" << endl;
    cout << "4 - Localização do aeroporto de partida" << endl;
    cout << "0 - Voltar atrás" << endl;
    cout << "Selecione uma opção: ";
    int choice;
    cin >> choice;
    return choice;
}

void Interface::bestFlightsMenu2(const vector<string> &ap1, const Graph &graph) {
    bool running = true;
    vector<string> ap2;
    while (running) {
        int choice = displayBestFlightsMenu2();
        std::string lol, lol2;
        double lat1, long1;
        switch (choice) {
            case 0:
                running = false;
                break;

            case 1:
                cout << "Qual o código do aeroporto de chegada?" << endl;
                cin >> lol;
                ap2.push_back(lol);
                for (auto &i: ap1) {
                    for (auto &j: ap2) {
                        FlightManager::bestTripAirportCode(i, j, graph);
                    }
                }
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                running = false;
                break;

            case 2:
                cout << "Qual o nome do aeroporto de chegada?" << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, lol);
                ap2.push_back(FlightManager::bestTripAirportName(lol, graph));
                for (auto &i: ap1) {
                    for (auto &j: ap2) {
                        FlightManager::bestTripAirportCode(i, j, graph);
                    }
                }
                std::cout << "Prima Enter para continuar.";
                std::cin.get();
                running = false;
                break;

            case 3:

                cout << "Qual o nome da cidade de partida?" << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, lol);
                ap2 = FlightManager::bestTripCityName(lol, graph);
                for (auto &i: ap1) {
                    for (auto &j: ap2) {
                        FlightManager::bestTripAirportCode(i, j, graph);
                    }
                }
                std::cout << "Prima Enter para continuar.";
                std::cin.get();
                running = false;
                break;

            case 4:
                cout << "Qual a latitude do aeroporto de chegada?" << endl;
                cin >> lat1;
                cout << "Qual a longitude do aeroporto de chegada?" << endl;
                cin >> long1;
                ap2 = FlightManager::bestTripCoordinates(Haversine::Coordinates{lat1, long1}, graph);
                for (auto &i: ap1) {
                    for (auto &j: ap2) {
                        FlightManager::bestTripAirportCode(i, j, graph);
                    }
                }
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                running = false;
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

int Interface::displayBestFlightsMenu2() {
    system("clear");
    cout << "---------------- Melhor viagem entre dois aeroportos ----------------" << endl;
    cout << "1 - Código do aeroporto de destino" << endl;
    cout << "2 - Nome do aeroporto de destino" << endl;
    cout << "3 - Cidade do aeroporto de destino" << endl;
    cout << "4 - Localização do aeroporto de destino" << endl;
    cout << "0 - Voltar atrás" << endl;
    cout << "Selecione uma opção: ";
    int choice;
    cin >> choice;
    return choice;
}

Graph Interface::filterFlightsByAirline() {
    vector<string> airlines;
    string airline;
    char choice;

    std::cout << "Deseja filtrar voos por companhia aérea? (Y/N): ";
    std::cin >> choice;

    while (toupper(choice) == 'Y') {
        std::cout << "Qual o código da Airline? ";
        std::cin >> airline;
        airlines.push_back(airline);

        std::cout << "Quer filtrar por mais alguma companhia aérea? (Y/N): ";
        std::cin >> choice;
    }

    Graph filteredGraph = FlightManager::getFlightSystem();
    if (!airlines.empty()) {
        filteredGraph = FlightManager::filterGraphByAirline(airlines);
    }
    return filteredGraph;
}


