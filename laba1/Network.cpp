#include "Network.h"
#include <set>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <ranges>
#include "utils.h"
#include "pipeline.h"
#include "nps.h"

int Network::findAvailablePipe(int diameter) {
    for (const auto& pair : pipes) {
        if (pair.second.GetDiametr() == diameter && !pair.second.GetRepair()) {
            bool isUsed = false;
            for (const auto& edges : adjacencyList) {
                for (const auto& edge : edges.second) {
                    if (edge.pipeId == pair.first) {
                        isUsed = true;
                    }
                }
            }
            if (!isUsed) return pair.first;
        }
    }
    return -1;
}

bool Network::connectStations(int fromStationId, int toStationId, int diameter) {

    if (stations.find(fromStationId) == stations.end() || 
        stations.find(toStationId) == stations.end()) {
        return false;
    }

    int pipeId = findAvailablePipe(diameter);
    if (pipeId == -1) {
        return false;
    }

    Edge edge{fromStationId, toStationId, pipeId};
    adjacencyList[fromStationId].push_back(edge);
    return true;
}

bool Network::hasCycle() {
    std::set<int> visited;
    std::set<int> recursionStack;
    
    std::function<bool(int)> hasCycleUtil = [&](int vertex) {
        visited.insert(vertex);
        recursionStack.insert(vertex);
        
        for (const Edge& edge : adjacencyList[vertex]) {
            if (visited.find(edge.to) == visited.end()) {
                if (hasCycleUtil(edge.to))
                    return true;
            }
            else if (recursionStack.find(edge.to) != recursionStack.end()) {
                return true;
            }
        }
        
        recursionStack.erase(vertex);
        return false;
    };
    
    for (const auto& pair : stations) {
        if (visited.find(pair.first) == visited.end()) {
            if (hasCycleUtil(pair.first))
                return true;
        }
    }
    
    return false;
}

std::vector<int> Network::topologicalSort() {
    std::vector<int> result;
    if (hasCycle()) {
        return result; 
    }

    std::unordered_map<int, int> inDegree;
    for (const auto& station : stations) {
        inDegree[station.first] = 0;
    }
    
    for (const auto& adj : adjacencyList) {
        for (const Edge& edge : adj.second) {
            inDegree[edge.to]++;
        }
    }

    std::queue<int> q;
    for (const auto& station : stations) {
        if (inDegree[station.first] == 0) {
            q.push(station.first);
        }
    }

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        result.push_back(vertex);

        for (const Edge& edge : adjacencyList[vertex]) {
            inDegree[edge.to]--;
            if (inDegree[edge.to] == 0) {
                q.push(edge.to);
            }
        }
    }

    return result;
}

std::vector<Edge> Network::getEdges() const {
    std::vector<Edge> edges;
    for (const auto& adj : adjacencyList) {
        for (const Edge& edge : adj.second) {
            edges.push_back(edge);
        }
    }
    return edges;
}

void Network::removeConnection(int pipeId) {
    for (auto& adj : adjacencyList) {
        auto& edges = adj.second;
        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                [pipeId](const Edge& edge) { return edge.pipeId == pipeId; }),
            edges.end()
        );
    }
}

void Network::handleConnect() {
    if (stations.size() < 2) {
        std::cout << "Need at least 2 stations to connect" << std::endl;
        return;
    }
    if (pipes.size() == 0) {
        std::cout << "No pipelines available" << std::endl;
        return;
    }
    
    std::cout << "Available stations:" << std::endl;
    ShowAllNPS(stations);
    
    int fromId, toId, diameter;
    std::cout << "Enter ID of input station: ";
    std::string input;
    std::getline(std::cin, input);
    while (!is_number(input) or std::stoi(input) == 0 or stations.find(std::stoi(input)) == stations.end()) {
        std::cout << "Enter available ID" << std::endl;
        std::getline(std::cin, input);
    }
    fromId = std::stoi(input);
    std::cout << "Enter ID of output station: ";
    std::getline(std::cin, input);
    while (!is_number(input) or std::stoi(input) == 0 or stations.find(std::stoi(input)) == stations.end()) {
        std::cout << "Enter available ID" << std::endl;
        std::getline(std::cin, input);
    }
    toId = std::stoi(input);
    std::cout << "Enter pipe diameter (500, 700, 1000, 1400): ";
    std::getline(std::cin, input);
    while (!is_number(input) or std::stoi(input) != 500 and std::stoi(input) != 700 and std::stoi(input) != 1000 and std::stoi(input) != 1400) {
        std::cout << "Enter available diameter" << std::endl;
        std::getline(std::cin, input);
    }
    diameter = std::stoi(input);
    if (connectStations(fromId, toId, diameter)) {
        std::cout << "Stations connected successfully" << std::endl;
    } else {
        std::cout << "Failed to connect stations. Check station IDs and available pipes" << std::endl;
    }
}

void Network::viewNetwork() const {
    auto edges = getEdges();
    if (edges.empty()) {
        std::cout << "Network is empty" << std::endl;
    } else {
        std::cout << "Network connections:" << std::endl;
        for (const auto& edge : edges) {
            std::cout << "Station " << edge.from << " -> Station " << edge.to 
                     << " (Pipe ID: " << edge.pipeId << ")" << std::endl;
        }
    }
}

void Network::viewTopologicalSort() const {
    auto sorted = const_cast<Network*>(this)->topologicalSort();
    if (sorted.empty()) {
        std::cout << "Cannot perform topological sort: network contains cycles or is empty" << std::endl;
    } else {
        std::cout << "Topological order of stations:" << std::endl;
        for (int id : sorted) {
            std::cout << "Station " << id << " (" << stations.at(id).GetName() << ")" << std::endl;
        }
    }
}