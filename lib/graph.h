//
// Created by Ji Li on 2017/9/9.
//

#ifndef CRSIM_GRAPH_H
#define CRSIM_GRAPH_H

#include "../global/include.h"

const int MAX_NODE_NUM = 110;// maximum number of nodes

class Edge{
public:
    int start; //start node
    int end; //end node
    int capacity; //capability of each edge
    int remain; //remaining capability of each edge
    int weight; //the weight of each edge
    int next; //the id of the next edge with the same start point;
    Edge(int s, int e);
};

Edge flipAnEdge(int s, int e);

/* node id and edge id all start from 0 */

class CRgraph{
public:
    int nodeNum;
    int edgeNum;
    int sourceID;
    int sinkID;
    vector<Edge> allEdge;
    int adjMatrix[MAX_NODE_NUM][MAX_NODE_NUM];
    struct node{
        int x;
        node* next;
    };
    node *adjList[MAX_NODE_NUM];
};

class GraphEdgeList : public CRgraph{
public:
    int curEdgeNum;
    vI edgeStartIndex;

    GraphEdgeList(int n);
    void addEdge(const Edge &e);
private:
    vI edgeCurIndex;
};

class GraphAdjMatrix: public CRgraph{
public:
    int capacity[MAX_NODE_NUM][MAX_NODE_NUM];
    int maxCapacity;
    int remain[MAX_NODE_NUM][MAX_NODE_NUM];

    GraphAdjMatrix();
    void printAdjMatrixFrom0();
    void printAdjMatrixFrom1();
};

class GraphAdjList: public CRgraph{
public:
    GraphAdjList();
};

class CRgraphAlgorithm{
public:
    static bool ifIsClique(GraphAdjMatrix g, vI x);
    static void maxCliqueBruteForce(GraphAdjMatrix g, int n, vI &ans);
    static int maxFlowEKalgorithm(GraphAdjMatrix *g);

};

#endif //CRSIM_GRAPH_H
