/********************************************************
@lab5
@Author: Jiaxuan Cao
@Last modify Date: 12.9.2023
@Know bugs: none
********************************************************/
#include<iostream>
#include<queue>
#include"DirectedWeightedGraph.h"
using namespace std;

int main(){

    DirectedWeightedGraph graph;

    VertexType v1,v2,v3,v4,v5,v6,v7;
    v1.item.Initialize(1);
    v2.item.Initialize(2);
    v3.item.Initialize(3);
    v4.item.Initialize(4);
    v5.item.Initialize(5);
    v6.item.Initialize(6);
    v7.item.Initialize(7);

    graph.AddVertex(v1);
    graph.AddVertex(v2);
    graph.AddVertex(v3);
    graph.AddVertex(v4);
    graph.AddVertex(v5);
    graph.AddVertex(v6);
    graph.AddVertex(v7);

    graph.AddEdge(v1,v2,100);
    graph.AddEdge(v1,v3,50);
    graph.AddEdge(v1,v4,150);
    graph.AddEdge(v3,v1,10);
    graph.AddEdge(v3,v7,50);
    graph.AddEdge(v4,v5,200);
    graph.AddEdge(v4,v6,100);
    graph.AddEdge(v5,v6,100);
    graph.AddEdge(v7,v6,30);

    cout << "After inserting all " << graph.getNumberOfVertices() << " vertices and " << graph.getNumberOfEdges() << " edges: "<<endl;
    cout << endl;

    graph.Print(); // print the graph
    cout << endl;
    
    //BFT
    cout << "The Breadth First Traversal Results: "<<endl; //choose v1 to start
    graph.BFT(v1);
    cout << endl;
    
   //delete v4
    cout << "Delete v4: " <<endl;
    graph.DeleteVertex(v4);
    graph.Print(); 

    return 0;
}