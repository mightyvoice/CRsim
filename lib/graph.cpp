//
//  graph.cpp
//  CRsim
//
//  Created by Ji on 14-11-4.
//  Copyright (c) 2014年 lj. All rights reserved.
//

#include "graph.h"

Edge:: Edge(int s, int e)
{
    start = s;
    end = e;
    next = -1;
}

Edge flipAnEdge(const Edge &e)
{
    Edge tmp = e;
    int t = tmp.end;
    tmp.end = tmp.start;
    tmp.start= t;
    return tmp;
}

GraphEdgeList::GraphEdgeList(int n)
{
    edgeStartIndex.resize(n+1);
    edgeCurIndex.resize(n+1);
    for(int i = 0; i <= n; i++){
        edgeStartIndex[i] = -1;
        edgeCurIndex[i] = -1;
    }
    curEdgeNum = 0;
}

void GraphEdgeList:: addEdge(const Edge &e)
{
    allEdge.push_back(e);
    curEdgeNum++;
    if(edgeStartIndex[e.start] == -1){
        edgeStartIndex[e.start] = curEdgeNum-1; //edge index from 0
    }
    if(edgeCurIndex[e.start] != -1){
        allEdge[edgeCurIndex[e.start]].next = curEdgeNum-1;
    }
    edgeCurIndex[e.start] = curEdgeNum - 1;
}

GraphAdjMatrix:: GraphAdjMatrix()
{
    memset(adjMatrix, 0, sizeof(adjMatrix));
    memset(capacity, 0, sizeof(capacity));
    memset(remain, 0, sizeof(remain));
    maxCapacity = 0;
}

void GraphAdjMatrix:: printAdjMatrixFrom0()
{
    int n = nodeNum;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(capacity[i][j]) cout<<i<<' '<<j<<endl;
        }
    }
}

void GraphAdjMatrix:: printAdjMatrixFrom1()
{
    int n = nodeNum;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cout<<adjMatrix[i][j]<<' ';
        }
        cout<<endl;
    }
}

int CRgraphAlgorithm:: maxFlowEKalgorithm(GraphAdjMatrix *g)
{
    int source = g->sourceID, sink =g->sinkID;
    int flow = 0, maxc = g->maxCapacity, data;
    int vis[MAX_NODE_NUM], pre[MAX_NODE_NUM], low[MAX_NODE_NUM];
    for(data = 0; data < 31; data++){
        if((1<<data) > maxc) break;
    }
    data = (1<<(data-1));
    while(data >= 1){
        do{
            memset(vis, 0, sizeof(vis));
            memset(pre, 0, sizeof(pre));
            memset(low, 0, sizeof(low));
            int q[MAX_NODE_NUM], head = 1, tail = 0;
            low[source] = global::INT_MAX_VAL;
            q[head] = source;
            while(head != tail){
                int u = q[++tail];
                for(int v = source; v <= sink && !vis[sink]; v++){
                    if(!vis[v] && g->remain[u][v] >= data){
                        vis[v] = 1;
                        low[v] = g->remain[u][v];
                        pre[v] = u;
                        q[++head] = v;
                        if(low[v] > low[u]) low[v] = low[u];
                    }
                }
            }
            if(low[sink] > 0){
                flow += low[sink];
                int j = sink, i;
                while(j != source){
                    i = pre[j];
                    g->remain[i][j] -= low[sink];
                    g->remain[j][i] += low[sink];
                    j = i;
                }
            }
        }while(low[sink] > 0);
        data = data >> 1;
    }
    return flow;
}

bool CRgraphAlgorithm:: ifIsClique(GraphAdjMatrix g, vI x)
{
    int n = (int)x.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(g.adjMatrix[x[i]][x[j]] == 0){
                return false;
            }
        }
    }
    return true;
}

void CRgraphAlgorithm:: maxCliqueBruteForce(GraphAdjMatrix g, int n, vI &ans)
{
    int m = 0;
    for(int i = 1; i < (1<<n); i++){
        vI tmp;
        for(int j = 0; j < n; j++){
            if((1<<j) & i){
                tmp.push_back(j+1);
            }
            if(ifIsClique(g, tmp) && tmp.size() > m){
                m = (int)tmp.size();
                ans.clear();
                for(int i = 0; i < m; i++) ans.push_back(tmp[i]);
            }
        }
    }
}
