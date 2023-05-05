#include <iostream>
#include <forward_list>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

int main()
{
    ifstream inFS;
    inFS.open("FB.txt");
    int id1, id2;
    int oneHundredPlus = 0;
    int totalVerticies = 0;
    double avgDegree = 0;
    string garbage, line;
    forward_list<int> fbFriends[70000]; // array with max value of txt file

    if (!inFS.is_open()) {
        cout << "Could not open file FB.txt";
        return 1; 
    }

    while (!inFS.eof()) {
        inFS >> id1;
        inFS >> id2;
        inFS >> garbage;
        getline(inFS, line);
        fbFriends[id1].remove(id2);
        fbFriends[id2].remove(id1);
        fbFriends[id1].push_front(id2);
        fbFriends[id2].push_front(id1);
    }

    inFS.close();

    for (int i = 0; i < 70000; i++) {
        int count = 0;
        for (auto it = fbFriends[i].begin(); it != fbFriends[i].end(); ++it) {
            count++;
        }
        if (count >= 100) {
            oneHundredPlus++;
        }
        if (count > 0) {
            avgDegree += count;
            totalVerticies++;
        }
    }
    cout << "Number of Verticies with degree of 100+: " << oneHundredPlus << endl;
    cout << "Average degree of verticies: " << avgDegree / totalVerticies << endl;
}
