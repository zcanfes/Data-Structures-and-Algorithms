/*
Student Name:Zehranaz Canfes
Student Number:2017205138
Project Number: 4
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "HelpStudents.h"

using namespace std;

HelpStudents::HelpStudents(int  N, int  M, int K, vector <pair<pair<int,int> , int >> ways) {
    adjacencyList = new list <pair<int, int>> [N];
    for(int i = 0; i < M; i++){//initializes the adjacency list of the nodes in the graph
        adjacencyList[ways[i].first.first - 1].emplace_back(ways[i].first.second, ways[i].second);
        adjacencyList[ways[i].first.second - 1].emplace_back(ways[i].first.first, ways[i].second);
    }
    this->nodes = N;
    this->edges = M;
    this->summit = K;
}

long long int HelpStudents::firstStudent() {//Dijkstra's shortest path algorithm
    set <pair<long long int, int>> processing;//keeps the nodes that are in the queue to be processed, sorted
    vector<long long int> distance (nodes, -2);//keeps the distances of all nodes to the source
    vector<bool> known(nodes, false);//keeps whether the distance from the node to the source is set
    distance[0] = 0;//distance from the source
    processing.insert(make_pair(0, 1));//sorts according to the distances

    while(!processing.empty()){
        pair<long long int, int> vertex = *(processing.begin());
        int node = vertex.second;//the node that is being processed
        known[node - 1] = true;//its distance is set, it is known
        long long int distanceSource = distance[node - 1];
        processing.erase(processing.begin());
        list <pair<int, int>>::iterator itr;
        for(itr = adjacencyList[node - 1].begin(); itr != adjacencyList[node - 1].end(); ++itr){//traverses the adjacency list of the node and calculates their distance
            pair <int, int> adjacent = *(itr);
            int adj  = adjacent.first;
            if(!known[adj -1]) {
                int weight = adjacent.second;
                if (distance[adj - 1] > distanceSource + weight || distance[adj - 1] == -2) {//if the distance is not set or current distance is smaller
                    if (distance[adj - 1] != -2)
                        processing.erase(processing.find(make_pair(distance[adj - 1], adj)));
                    distance[adj - 1] = distanceSource + weight;
                    processing.insert(make_pair(distance[adj - 1], adj));
                }
            }
        }
        if(known[summit - 1])//if summit is reached, stop
            break;
    }
    return distance[summit - 1];
}
long long int HelpStudents::secondStudent() {//Prim's algorithm, similar to firstStudent, only now the distances to the current node is kept
    set <pair<long long int, int>> processing;
    set<long long int> spanningTree;//keeps the processed distances in the sorted tree set
    vector<long long int> distance (nodes, -2);
    vector<bool> known(nodes, false);
    distance[0] = 0;
    processing.insert(make_pair(0, 1));

    while(!processing.empty()){
        pair<long long int, int> vertex = *(processing.begin());
        int node = vertex.second;
        known[node - 1] = true;
        spanningTree.insert(distance[node - 1]);
        processing.erase(processing.begin());
        list <pair<int, int>>::iterator itr;
        for(itr = adjacencyList[node - 1].begin(); itr != adjacencyList[node - 1].end(); ++itr){
            pair <int, int> adjacent = *(itr);
            int adj  = adjacent.first;
            if(!known[adj -1]) {
                int weight = adjacent.second;
                if (distance[adj - 1] > weight || distance[adj - 1] == -2) {
                    if (distance[adj - 1] != -2)
                        processing.erase(processing.find(make_pair(distance[adj - 1], adj)));
                    distance[adj - 1] = weight;
                    processing.insert(make_pair(distance[adj - 1], adj));
                }
            }
        }
        if(known[summit - 1])
            break;
    }
    return *(--spanningTree.end());//returns the maximum distance in the tree
}
long long int HelpStudents::thirdStudent() {//unweighted graph, similar to firstStudent only the weights are taken to be 1 to count the number of edges
    set <pair<long long int, int>> processing;
    vector<long long int> distance (nodes, -2);
    vector<bool> known(nodes, false);
    distance[0] = 0;
    processing.insert(make_pair(0, 1));

    while(!processing.empty()){
        pair<long long int, int> vertex = *(processing.begin());
        int node = vertex.second;
        known[node - 1] = true;
        long long int distanceSource = distance[node - 1];
        processing.erase(processing.begin());
        list <pair<int, int>>::iterator itr;
        for(itr = adjacencyList[node - 1].begin(); itr != adjacencyList[node - 1].end(); ++itr){
            pair <int, int> adjacent = *(itr);
            int adj  = adjacent.first;
            if(!known[adj -1]) {
                if (distance[adj - 1] > distanceSource + 1 || distance[adj - 1] == -2) {
                    if (distance[adj - 1] != -2)
                        processing.erase(processing.find(make_pair(distance[adj - 1], adj)));
                    distance[adj - 1] = distanceSource + 1;
                    processing.insert(make_pair(distance[adj - 1], adj));
                }
            }
        }
        if(known[summit - 1])
            break;
    }
    return distance[summit - 1];
}
long long int HelpStudents::fourthStudent() {//Greedy algorithm that chooses the smallest edge every time, may not reach the summit
    long long int t = 0;//time
    set<pair<int, int>> processing;
    int *visitedEdges = new int [nodes * nodes];//keeps the array of the graph not to pass from the same edge again
    processing.insert(make_pair(0, 1));
    while(!processing.empty()){
        pair<int, int> vertex = *(processing.begin());
        processing.clear();//after selecting the minumum edge, delete the others from the set
        int node = vertex.second;
        int weight = vertex.first;
        t += weight;
        if(node == summit)//if the summit is reached, stop
            return t;
        list<pair<int, int>>::iterator itr;
        for(itr = adjacencyList[node - 1].begin(); itr != adjacencyList[node - 1].end(); ++itr){
            pair<int, int> adjacent = *(itr);
            int w = adjacent.first;
            int weight2 = adjacent.second;
            if(visitedEdges[(node - 1) * nodes + w - 1] != -1) {//if visitedEdges[node - 1][w - 1] is not visited;
                processing.insert(make_pair(weight2, w));//process the edge
            }
        }
        if(!processing.empty()) {
            pair<int, int> min = *(processing.begin());//keep the minimum edge
            int path = min.second;//since it is the directed graph both directions from the graph must be deleted, i.e. set to -1
            visitedEdges[(path - 1) * nodes + node - 1] = -1;
            visitedEdges[(node - 1) * nodes + path - 1] = -1;
        }
    }
    return -1;//if the summit is not reached at the end
}
long long int HelpStudents::fifthStudent() {
    set <pair<pair<long long int, int>, int>> processing;
    vector<long long int> distance (nodes, -2);//keeps the distances in the graph of every node in 0 charge
    vector<long long int> distance1(nodes, -2);//1 charge
    vector<long long int> distance2(nodes, -2);//2 charge, after that the student can skip the edge
    bool begin = true;
    int n = 0;
    long long int distanceSource = 0;
    if(summit == 1)
        return 0;
    processing.insert(make_pair(make_pair(-2, 1), 0));
    while(!processing.empty()){
        pair<pair<long long int, int>, int> vertex = *(processing.begin());
        int node = vertex.first.second;
        int power = vertex.second;
        if(begin){
            n = 2;//since all the distances are -2, 2 must be added at first to every calculated distance
        } else {
            n = 0;
        }
        if(power == 0)
            distanceSource = distance[node - 1];
        else if(power == 1)
            distanceSource = distance1[node - 1];
        else
            distanceSource = distance2[node - 1];
        processing.erase(processing.begin());
        list <pair<int, int>>::iterator itr;
        for(itr = adjacencyList[node - 1].begin(); itr != adjacencyList[node - 1].end(); ++itr){
            pair <int, int> adjacent = *(itr);
            int adj  = adjacent.first;
            int weight = adjacent.second;
            if(power + 1 == 3)//the student skips the edge, weight is taken to be 0
                weight = 0;
            if (power == 0){//look to the distance vector with charge 1
                if (distance1[adj - 1] > distanceSource + weight + n || distance1[adj - 1] == -2) {
                    if (distance1[adj - 1] != -2) {
                        processing.erase(processing.find(make_pair(make_pair(distance1[adj - 1], adj), 1)));//delete if there is already a calculated distance
                    }
                    distance1[adj - 1] = distanceSource + weight + n;//update the distances
                    processing.insert(make_pair(make_pair(distance1[adj - 1], adj), (power + 1) % 3));
                }
            }else if(power == 1){//look at the distance vector charge 2
                if (distance2[adj - 1] > distanceSource + weight + n || distance2[adj - 1] == -2) {
                    if (distance2[adj - 1] != -2)
                        processing.erase(processing.find(make_pair(make_pair(distance2[adj - 1], adj), 2)));
                    distance2[adj - 1] = distanceSource + weight + n;
                    processing.insert(make_pair(make_pair(distance2[adj - 1], adj), (power + 1) % 3));
                }
            }else{//look at the distance vector with charge 0, since after this step, the student skips the edge
                if (distance[adj - 1] > distanceSource + weight + n || distance[adj - 1] == -2) {
                    if (distance[adj - 1] != -2)
                        processing.erase(processing.find(make_pair(make_pair(distance[adj - 1], adj), 0)));
                    distance[adj - 1] = distanceSource + weight + n;
                    processing.insert(make_pair(make_pair(distance[adj - 1], adj), (power + 1) % 3));
                }
            }
            begin = false;
        }
    }
    return min(distance[summit - 1], min(distance1[summit - 1], distance2[summit - 1]));//returns the minimum of the distances in three vectors
}

// YOU CAN ADD YOUR HELPER FUNCTIONS
