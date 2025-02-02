#ifndef PROJECT_2_ATFMS_INTERFACE_H
#define PROJECT_2_ATFMS_INTERFACE_H

#include "FlightManager.h"

class Interface {
public:
    /**
     * @brief Constructor default da classe Interface
     */
    Interface();

    /**
     * @brief Executa o programa
     */
    static void run();

private:
    /**
     * @brief Objeto da classe FlightManager, que contêm toda a informação do sistema de voos
     */
    static FlightManager _flightManager;

    /**
     * @brief Menu principal do programa
     * @return Número correspondente à ação que o utilizador pretende realizar
     */
    static int displayMainMenu();

    /**
     * @brief Menu onde é processada a resposta do utilizador ao menu de informações gerais sobre os aeroportos, campanhias aéreas e cidades
     * @see displayGeralInformationMenu()
     */
    static void geralInformationMenu();

    /**
     * @brief Menu que contêm informações gerais sobre os aeroportos, campanhias aéreas e cidades
     * @return Número correspondente à ação que o utilizador pretende realizar
     */
    static int displayGeralInformationMenu();

    /**
     * @brief Menu onde é processada a resposta do utilizador ao menu de informações gerais sobre os voos
     * @see flightInformationMenu()
     */
    static void flightInformationMenu();

    /**
     * @brief Menu que contêm informações gerais sobre os voos
     * @return Número correspondente à ação que o utilizador pretende realizar
     */
    static int displayFlightInformationMenu();

    /**
     * @brief Menu onde é processada a resposta do utilizador ao menu de melhores voos, relativamente ao aeroporto de partida
     * @see bestFlightsMenu1()
     */
    static void bestFlightsMenu1();

    /**
     * @brief Menu que permite ao utilizador optar por diferentes tipos de input, consoante o desejado, para um aeroporto de partida
     * @return Número correspondente à ação que o utilizador pretende realizar
     */
    static int displayBestFlightsMenu1();

    /**
     * @brief Menu onde é processada a resposta do utilizador ao menu de melhores voos, relativamente ao aeroporto de chegada
     * @param ap1
     * @param graph
     * @see bestFlightsMenu2()
     */
    static void bestFlightsMenu2(const vector<string> &ap1, const Graph &graph);

    /**
     * @brief Menu que permite ao utilizador optar por diferentes tipos de input, consoante o desejado, para um aeroporto de destino
     * @return Número correspondente à ação que o utilizador pretende realizar
     */
    static int displayBestFlightsMenu2();

    /**
     * @brief Menu onde é filtrada a informação tendo em conta a preferência do utilizador em certas airlines
     * @return Grafo apenas com as airlines desejadas
     */
    static Graph filterFlightsByAirline();
};


#endif //PROJECT_2_ATFMS_INTERFACE_H
