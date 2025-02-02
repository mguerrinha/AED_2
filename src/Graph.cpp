#include "Graph.h"

#include <utility>

Vertex::Vertex(Airport in) : info(std::move(in)) {}

Edge::Edge(Vertex *d, std::shared_ptr<Airline> w) : _dest(d), _weight(std::move(w)) {}

unordered_map<string, Vertex *> Graph::getVertexSet() const {
    return _vertexSet;
}

Airport Vertex::getInfo() const {
    return info;
}

[[maybe_unused]] void Vertex::setInfo(Airport in) {
    Vertex::info = std::move(in);
}

[[maybe_unused]] bool Vertex::isProcessing() const {
    return _processing;
}

[[maybe_unused]] void Vertex::setProcessing(bool p) {
    Vertex::_processing = p;
}

Vertex *Edge::getDest() const {
    return _dest;
}

[[maybe_unused]] void Edge::setDest(Vertex *d) {
    Edge::_dest = d;
}

std::shared_ptr<Airline> Edge::getWeight() const {
    return _weight;
}

[[maybe_unused]] void Edge::setWeight(std::shared_ptr<Airline> weight) {
    Edge::_weight = std::move(weight);
}

Vertex *Graph::findVertex(const Airport &in) const {
    auto it = _vertexSet.find(in.getCode());
    return (it != _vertexSet.end()) ? it->second : nullptr;
}

bool Vertex::isVisited() const {
    return _visited;
}

int Vertex::getIndegree() const {
    return _indegree;
}

void Vertex::setIndegree(int indegree) {
    Vertex::_indegree = indegree;
}

int Vertex::getNum() const {
    return _num;
}

void Vertex::setNum(int num) {
    Vertex::_num = num;
}

int Vertex::getLow() const {
    return _low;
}

void Vertex::setLow(int low) {
    Vertex::_low = low;
}

void Vertex::setVisited(bool v) {
    Vertex::_visited = v;
}

vector<Edge> Vertex::getAdj() const {
    return _adj;
}

[[maybe_unused]] void Vertex::setAdj(const vector<Edge> &adj) {
    Vertex::_adj = adj;
}

bool Graph::addVertex(const Airport &in) {
    if (findVertex(in) != nullptr)
        return false;
    _vertexSet.emplace(in.getCode(), new Vertex(in));
    return true;
}

bool Graph::addEdge(const Airport &sourc, const Airport &dest, const std::shared_ptr<Airline>& w) const {
    Vertex *v1 = findVertex(sourc);
    Vertex *v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    v2->setIndegree(v2->getIndegree() + 1);
    return true;
}

void Vertex::addEdge(Vertex *d, const std::shared_ptr<Airline>& w) {
    _adj.emplace_back(d, w);
}

[[maybe_unused]] bool Graph::removeEdge(const Airport &sourc, const Airport &dest) const {
    Vertex *v1 = findVertex(sourc);
    Vertex *v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    return v1->removeEdgeTo(v2);
}

bool Vertex::removeEdgeTo(Vertex *d) {
    for (auto it = _adj.begin(); it != _adj.end(); it++)
        if (it->getDest() == d) {
            _adj.erase(it);
            return true;
        }
    return false;
}

bool Vertex::operator==(const Vertex &rhs) const {
    return info == rhs.info;
}

void Vertex::setStops(int stops) {
    _stops = stops;
}

int Vertex::getStops() const {
    return _stops;
}

int Vertex::getLongestTrip() const {
    return _longestTrip;
}

void Vertex::setLongestTrip(int longestTrip) {
    _longestTrip = longestTrip;
}

[[maybe_unused]] bool Graph::removeVertex(const Airport &in) {
    for (auto it = _vertexSet.begin(); it != _vertexSet.end(); it++)
        if ((*it).first == in.getCode()) {
            Vertex *v = it->second;
            _vertexSet.erase(it);
            for (auto vertexSet: _vertexSet)
                vertexSet.second->removeEdgeTo(v);
            _vertexSet.erase(in.getCode());
            return true;
        }
    return false;
}

