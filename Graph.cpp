//
// Created by camil on 07/12/2023.
//

#include "Graph.h"

template<class T>
Vertex<T>::Vertex(const T& value) {
    data = value;
    inDegree = 0;
    outDegree = 0;
    connectedTo = {};
}
template<class T>
Vertex<T>::~Vertex() {
}
template<class T>
void Vertex<T>::addNeighbor(Vertex<T> *to, int weight) {
    Edge<T>* temp = new Edge<T>;
    temp->to = to;
    temp->weight = weight;
    outDegree++;
    to->inDegree++;
    connectedTo.insert(connectedTo.size(), temp);
}
template<class T>
int Vertex<T>::getWeight(const T &value) {
    for(int i=0; i < connectedTo.size(); i++){
        Edge<T>* temp = connectedTo.get(i);
        if(temp->to->data == value){
            return connectedTo.get(i)->weight;
        }
    }
    return NULL;
}
template<class T>
Graph<T>::Graph() {
    count = 0;
    vertexList = {};
}

template<class T>
Graph<T>::~Graph() {
}

template<class T>
Vertex<T>* Graph<T>::addVertex(const T &value) {
    Vertex<T>* newVertex = new Vertex<T>(value);
    vertexList.insert(vertexList.size(), newVertex);
    count++;
    return newVertex;
}

template<class T>
void Graph<T>::addEdge(const T& from, const T& to, int weight) {
    Vertex<T>* fromVertex = getVertex(from);
    if(!fromVertex){
        fromVertex = addVertex(from);
    }
    Vertex<T>* toVertex = getVertex(to);
    if(!toVertex){
        toVertex = addVertex(to);
    }
    fromVertex->addNeighbor(toVertex, weight);
}

template<class T>
Vertex<T> *Graph<T>::getVertex(const T &value) {
    for(int i=0; i < vertexList.size();i++ ){
        if(vertexList.get(i)->data == value) return vertexList.get(i);
    }
    return NULL;
}
