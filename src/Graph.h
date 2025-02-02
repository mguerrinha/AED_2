#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include "Airline.h"
#include "Airport.h"
#include <unordered_map>
#include <memory>

using namespace std;

/**
 * @brief Classe que representa uma Edge, que permite ligar dois aeroportos, estando associada aos voos
 */
class Edge;

/**
 * @brief Classe que representa um Grafo dirigido e todos os métodos associados ao mesmo
 */
class Graph;

/**
 * @brief Classe que representa um Vertex, que por sua vez corresponde a um aeroporto
 */
class Vertex;

class Vertex {
private:
    /// Aeroporto associado ao vértice
    Airport info;

    /// Lista de vértices (aeroportos) que saem deste vértice
    vector<Edge> _adj;

    /// Booleano que indica se o vértice já foi visitado numa pesquisa
    bool _visited{};

    /// Booleano que indica se o vértice está a ser processado numa pesquisa
    bool _processing{};

    /// Número de arestas (voos) que entram neste vértice
    int _indegree{};

    /// Número identificador único atribuído a este vértice
    int _num{};

    /// Valor utilizado em algoritmos de busca em profundidade para determinar a menor conectividade
    int _low{};

    /// Número de paragens necessárias para chegar a este vértice a partir de um ponto de origem
    int _stops{};

    /// A maior distância registrada em voos a partir deste aeroporto
    int _longestTrip = 0;

public:
    /**
     * @brief Constructor da classe Vertex
     * @param in Aeroporto que será associado ao vértice
     */
    explicit Vertex(Airport in);

    /**
     * @brief Retorna a maior distância registrada em voos a partir do aeroporto
     * @return Maior distância registrada
     */
    [[nodiscard]] int getLongestTrip() const;

    /**
     * @brief Define a nova distância máxima de um aeroporto
     * @param longestTrip
     */
    void setLongestTrip(int longestTrip);

    /**
     * @brief Retorna o aeroporto correspondente ao vértice pretendido
     * @return Aeroporto associado ao vértice
     */
    [[nodiscard]] Airport getInfo() const;

    /**
     * @brief Adiciona uma nova aresta ao grafo
     * @param d Aeroporto de destino
     * @param w Companhia aérea associada à aresta
     */
    void addEdge(Vertex *d, const std::shared_ptr<Airline>& w);

    /**
     * @brief Remove uma aresta de saída para um destino específico (d) a partir do vértice
     * @param d Aeporto de destino
     * @return True se for bem-sucedida e false se tal aresta não existir.
     */
    bool removeEdgeTo(Vertex *d);

    /**
     * @brief Associa um aeroporto ao vértice
     * @param in
     */
    [[maybe_unused]] void setInfo(Airport in);

    /**
     * @brief Verifica se o vértice foi visitado numa pesquisa
     * @return True se foi visitado, false caso contrário
     */
    [[nodiscard]] bool isVisited() const;

    /**
     * @brief Define se o vértice foi visitado numa pesquisa
     * @param v Booleano que indica se foi visitado
     */
    void setVisited(bool v);

    /**
     * @brief Verifica se o vértice está a ser processado por um algoritmo
     * @return True se estiver a ser processado, false caso contrário
     */
    [[maybe_unused]] [[nodiscard]] bool isProcessing() const;

    /**
     * @brief Define se o vértice está a ser processado por um algoritmo
     * @param p Booleano que indica se está a ser processado
     */
    [[maybe_unused]] void setProcessing(bool p);

    /**
     * @brief Obtém a lista de arestas (vértices de destino) associadas ao vértice
     * @return Vetor de arestas associadas ao vértice
     */
    [[nodiscard]] vector<Edge> getAdj() const;

    /**
     * @brief Define a lista de arestas (vértices de destino) associadas ao vértice
     * @param adj Vetor de arestas a ser definido
     */
    [[maybe_unused]] void setAdj(const vector<Edge> &adj);

    /**
     * @brief Obtém o número de arestas que entram no vértice
     * @return Número de arestas que entram no vértice
     */
    [[nodiscard]] int getIndegree() const;

    /**
     * @brief Define o número de arestas que entram no vértice
     * @param indegree Valor do número de arestas a ser definido
     */
    void setIndegree(int indegree);

    /**
     * @brief Obtém o número associado ao vértice
     * @return Número associado ao vértice
     */
    [[nodiscard]] int getNum() const;

    /**
     * @brief Define o número associado ao vértice
     * @param num Valor do número a ser definido
     */
    void setNum(int num);

    /**
     * @brief Obtém o valor "low" associado ao vértice
     * @return Valor "low" associado ao vértice
     */
    [[nodiscard]] int getLow() const;

    /**
     * @brief Define o valor "low" associado ao vértice
     * @param low Valor do "low" a ser definido
     */
    void setLow(int low);

    /**
     * @brief Obtém o número de paragens associado ao vértice
     * @return Número de paragens associado ao vértice
     */
    [[nodiscard]] int getStops() const;

    /**
     * @brief Define o número de paragens associado ao vértice
     * @param stops stops Número de paragens a ser definido
     */
    void setStops(int stops);

    /**
     * @brief Operador de igualdade
     * @param rhs Vértice a ser comparado
     * @return True se os vértices são iguais, false caso contrário
     */
    bool operator==(const Vertex &rhs) const;
};

class Edge {
    /// Vértice (aeroporto) de destino da aresta
    Vertex *_dest;

    /// Companhia aérea associada à aresta
    std::shared_ptr<Airline> _weight;
public:
    /**
     * @brief Construtor da classe Edge
     * @param d Vértice de destino
     * @param w Companhia aérea associada à aresta
     */
    Edge(Vertex *d, std::shared_ptr<Airline> w);

    /**
     * @brief Obtém o vértice de destino da aresta
     * @return Vértice de destino
     */
    [[nodiscard]] Vertex *getDest() const;

    /**
     * @brief Define o vértice de destino da aresta
     * @param dest Vértice de destino a ser definido
     */
    [[maybe_unused]] void setDest(Vertex *dest);

    /**
     * @brief Obtém a companhia aérea à aresta
     * @return Companhia aérea associada à aresta
     */
    [[nodiscard]] std::shared_ptr<Airline> getWeight() const;

    /**
     * @brief Define a companhia aérea associada à aresta
     * @param weight Companhia aérea a ser definida
     */
    [[maybe_unused]] void setWeight(std::shared_ptr<Airline> weight);
};

class Graph {
    /// Hash table com o código do aeroporto e um vértice associado para representar todos os vértices presentes no grafo
    unordered_map<string, Vertex *> _vertexSet;

public:
    /**
     * @brief Encontra um vértice com base nas informações de um aeroporto
     * @param in Aeroporto a ser procurado
     * @return Pointer para o vértice encontrado ou nullptr se não encontrado
     */
    [[nodiscard]] Vertex *findVertex(const Airport &in) const;

    /**
     * @brief Adiciona um vértice ao grafo
     * @param in Aeroporto a ser associado ao vértice
     * @return True se adicionado com sucesso, false se o vértice já existir
     */
    bool addVertex(const Airport &in);

    /**
     * @brief Remove um vértice do grafo, juntamente com todas as arestas de entrada e saída
     * @param in Informações do aeroporto a serem removidas
     * @return True se removido com sucesso, false se o vértice não existir
     */
    [[maybe_unused]] [[maybe_unused]] bool removeVertex(const Airport &in);

    /**
     * @brief Adiciona uma aresta (voo) entre dois aeroportos
     * @param sourc Aeroporto de partida
     * @param dest Aeroporto de destino
     * @param w Companhia aérea associada ao voo
     * @return True se a aresta foi adicionada com sucesso, false se os aeroportos não foram encontrados
     */
    bool addEdge(const Airport &sourc, const Airport &dest, const std::shared_ptr<Airline>& w) const;

    /**
     * @brief Remove uma aresta entre dois aeroportos
     * @param sourc Aeroporto de partida
     * @param dest Aeroporto de destino
     * @return True se a aresta foi removida com sucesso, false se a aresta não foi encontrada
     */
    [[maybe_unused]] [[maybe_unused]] bool removeEdge(const Airport &sourc, const Airport &dest) const;

    /**
     * @brief Obtém o conjunto de vértices do grafo
     * @return Hash table associada ao grafo
     */
    [[nodiscard]] unordered_map<string, Vertex *> getVertexSet() const;
};

#endif /* GRAPH_H_ */
