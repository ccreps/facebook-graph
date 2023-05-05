// facebookFriendsOfFriends.cpp : This file contains the 'main' function. Program execution begins and ends there.
// implemented using Homework 9 Solution provided to us.

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>

const std::string FACEBOOK_FILENAME = "FB.txt";
const int DEGREE_CUTOFF = 100;

void addEdge(std::vector<std::unordered_set<int>>& adjList, int u, int v);

int main()
{
    std::ifstream inFS;
    std::cout << "Opening file " << FACEBOOK_FILENAME << std::endl;
    inFS.open(FACEBOOK_FILENAME);
    if (!inFS.is_open()) {
        std::cout << "Could not open file " << FACEBOOK_FILENAME << std::endl;
        return 1;
    }

    // Read in edge line by line and add edges
    std::vector<std::unordered_set<int>> facebookAdjList;
    int u, v, lineNum = 0;
    std::string timestamp;
    while (!inFS.eof()) {
        //for (int i = 0; i < 100; i++) {
        lineNum++;

        inFS >> u >> v >> timestamp;
        if (!inFS.fail())
            addEdge(facebookAdjList, u, v);
    }
    inFS.close();

    int totalV = facebookAdjList.size();
    double result = 0;
    // Output degree of each vertex
    for (int i = 0; i < facebookAdjList.size(); i++) {
        double meanDegree = 0;
        int vertexDeg = facebookAdjList.at(i).size();
        for (auto friendOfFriend : facebookAdjList.at(i)) {
            meanDegree += facebookAdjList.at(friendOfFriend).size() / (double) vertexDeg;
        }
        result += meanDegree;
    }

    std::cout << "Mean degree for friends of friends: " << result / totalV << std::endl;

    return 0;
}

void addEdge(std::vector<std::unordered_set<int>>& adjList, int u, int v) {
    // If either node is not already in the outer list, then add it
    if (std::max(u, v) >= adjList.size())
        adjList.resize(std::max(u, v) + 1);

    // Check if v is already in the inner set for node u, and if not, add it,
    // and vice versa
    if (adjList.at(u).count(v) == 0)
        adjList.at(u).insert(v);
    if (adjList.at(v).count(u) == 0)
        adjList.at(v).insert(u);
}
