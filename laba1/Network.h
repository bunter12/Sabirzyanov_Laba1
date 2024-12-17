#pragma once
#include "pipeline.h"
#include "nps.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>

class nps;
class pipeline;

using namespace std;

struct Edge {
    int from;
    int to;
    int pipeId;
};

class Network {
private:
    std::unordered_map<int, std::vector<Edge>> list;
    std::unordered_map<int, pipeline>& pipes;
    std::unordered_map<int, nps>& stations;

public:
    Network(std::unordered_map<int, pipeline>& p, std::unordered_map<int, nps>& s) 
        : pipes(p), stations(s) {}

    bool connectStations(int fromStationId, int toStationId, int diameter);
    int findAvailablePipe(int diameter);
    std::vector<int> topologicalSort();
    bool hasCycle();
    std::vector<Edge> getEdges() const;
    void removeConnection(int pipeId);
    void removeStationConnections(int stationId);
    void handleConnect();
    void viewNetwork() const;
    void viewTopologicalSort() const;
    void NetworkToFile(std::ofstream& file);
    std::unordered_map<int, std::vector<Edge>> NetworkFromFile(std::ifstream& file);
};