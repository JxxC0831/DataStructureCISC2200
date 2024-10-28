/********************************************************
 * File : DirectedWeightedGraph.cpp
 * Date : 11/30/2023
 * Description : Impelementation file of DirectedWeightedGrap class
 ********************************************************/

#include "DirectedWeightedGraph.h"

DirectedWeightedGraph::DirectedWeightedGraph()
{
    maxVertices = 100; //default value of maxVertices, assume the number is 100
    numberOfVertices = 0; //default value of numberOfVertices, assume the number is 0
    vertices = new VertexType[maxVertices];

}

DirectedWeightedGraph::DirectedWeightedGraph(int max)
{
    maxVertices = max; //set the maxVertices to the value of max
    numberOfVertices = 0; //default value of numberOfVertices, assume the number is 0
    vertices = new VertexType[maxVertices];

}

DirectedWeightedGraph::~DirectedWeightedGraph()
{
    delete[] vertices;//clear the memory
}

bool DirectedWeightedGraph::IsEmpty() const
{
    return numberOfVertices == 0; //return true if the number of vertices is 0
}

bool DirectedWeightedGraph::IsFull() const
{
    return numberOfVertices == maxVertices; //return true if the number of vertices is equal to the maxVertices
}

void DirectedWeightedGraph::AddVertex(VertexType v)
{

        vertices[numberOfVertices] = v;
        //set the weight of the edge between the new vertex and other vertices to 0
        for(int i = 0; i < numberOfVertices; i++)
        {
            edges[numberOfVertices][i] = 0;
            edges[i][numberOfVertices] = 0;
        }
        numberOfVertices++;

}

void DirectedWeightedGraph::AddEdge(VertexType v1, VertexType v2, int w)
{
    int index1 = IndexIs(v1); //get the index of v1
    int index2 = IndexIs(v2); //get the index of v2
    edges[index1][index2] = w; //set the weight of the edge
}


void DirectedWeightedGraph::DeleteVertex(VertexType v)
{
    int index = IndexIs(v);
    if(index == -1 || IsEmpty()) //check whether the vertex exists                                                                                                                                                                                   
    {
        cout << "Vertex not found" << endl;
        return;
    }
   
    for(int i=0; i<numberOfVertices-1; i++)
    {
        edges[index][i] = edges[numberOfVertices-1][i];//move the last row to the position of the deleted vertex                                                                                                                                     

        edges[i][index] = edges[i][numberOfVertices-1]; //move the last column to the position of the deleted vertex                                                                                                                                 
    }
    for(int j=0; j<numberOfVertices; j++)
    {
        DeleteEdge(vertices[numberOfVertices-1], vertices[j]);// use delete edge to delete the edge between the last vertex and other vertices                                                                                                       
        DeleteEdge(vertices[j], vertices[numberOfVertices-1]);
    }
    vertices[index] = vertices[numberOfVertices-1]; //move the last vertex to the position of the deleted vertex
    numberOfVertices--; //decrease the number of vertices by 1                                                                                                                                                                                       
}

void DirectedWeightedGraph::DeleteEdge(VertexType v1, VertexType v2)
{
    int index1 = IndexIs(v1); //use v1 and v2 find the index of the edge
    int index2 = IndexIs(v2); 
    edges[index1][index2] = 0; //set the weight of the edge to 0 
}

int DirectedWeightedGraph::GetWeight(VertexType v1, VertexType v2)
{ 
    int index1 = IndexIs(v1);// use v1 and v2 find the edge
    int index2 = IndexIs(v2);

    return edges[index1][index2]; //return the weight
}

bool DirectedWeightedGraph::EdgeExists(VertexType v1, VertexType v2)
{
    int index1 = IndexIs(v1);
    int index2 = IndexIs(v2);

    if(edges[index1][index2] != 0)
        return true; // edge exists, return true
    else
        return false;//return false. not exists
}

bool DirectedWeightedGraph::VertexExists(VertexType v)
{
    for(int i = 0; i< numberOfVertices; i++)
    {
        if(vertices[i].item.ComparedTo(v.item) == EQUAL)
            return true; //vertex exists, return true
    }
    return false; //return false, not exists
}

void DirectedWeightedGraph::Print()
{
    cout << "There are " << numberOfVertices << " vertices in this Graph" << endl;
    for(int i = 0; i < numberOfVertices; i++)
    {  
        
        cout << vertices[i].item << " ";

    }
    cout << endl;

    cout << "Edges are: " << endl;
    cout << "  ";
    for(int i = 0; i < numberOfVertices; i++)
    {  
        
        cout << i << " ";

    }
    cout << endl;

    for(int i = 0; i < numberOfVertices; i++)
    {
        for(int j = 0; j < numberOfVertices; j++)
        {
            if(j == 0)
            {
                cout << i << " ";
            }
            cout << edges[i][j] << " ";
        }
        cout << endl;
    }

}

void DirectedWeightedGraph::MarkVertex(VertexType v, MARK m)//mark whether the vertex has been visited or queued
{
    for(int i = 0; i < numberOfVertices; i++)
    {
        if(vertices[i].item.ComparedTo(v.item) == EQUAL)
            vertices[i].mark = m; //mark the vertex
    }
}

void DirectedWeightedGraph::GetNeighbors(VertexType v, queue<VertexType>& nq)
{
    int index = IndexIs(v);
    for (int i=0; i<numberOfVertices;i++)
    {
        if (edges[index][i] != 0 && vertices[i].mark != VISITED && vertices[i].mark != QUEUED)
        {
            nq.push(vertices[i]);
            vertices[i].mark = QUEUED;
        }
    }
}

void DirectedWeightedGraph::BFT(VertexType v)
{
    int index = IndexIs(v);

    queue<VertexType> nq;

    for(int i = 0; i< numberOfVertices; i++)
    {
        vertices[i].mark = DEFAULT; //set all the vertices to default at the begaining
    }

    MarkVertex(vertices[index],QUEUED); //mark the first vertex as queued
    nq.push(vertices[index]); //push the vertex into the queue
    
    while(!nq.empty())
    {
        VertexType temp = nq.front(); //get the front vertex

        temp.item.Print();
        cout << " ";

        MarkVertex(temp, VISITED);

        GetNeighbors(temp, nq);

        nq.pop();
    }
    cout << endl;
}

int DirectedWeightedGraph::IndexIs(VertexType v)
{
    for(int i = 0; i < numberOfVertices; i++)
    {
        if(vertices[i].item.ComparedTo(v.item) == EQUAL)
            return i; //return the index of the vertex
    }
    return -1; //return -1 if not found
}

int DirectedWeightedGraph::getNumberOfVertices()
{
    return numberOfVertices; //return the number of vertices
}

int DirectedWeightedGraph::getNumberOfEdges()
{
    int count = 0;
    for(int i = 0; i < numberOfVertices; i++)
    {
        for(int j = 0; j < numberOfVertices; j++)
        {
            if(edges[i][j] != 0)
                count++; //count the number of edges
        }
    }
    return count; //return the number of edges
}