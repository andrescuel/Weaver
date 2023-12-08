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
Vertex<T> *Graph<T>::getVertex(const T &value) const {
    for(int i=0; i < vertexList.size();i++ ){
        if(vertexList.get(i)->data == value) return vertexList.get(i);
    }
    return NULL;
}

template<class T>
vector<T> Graph<T>::dijkstraShortestPath(const T &inicio, const T &fin) const {
    unordered_map<T, int> distancias;
    unordered_map<T, T> predecesores;

    // Cola de prioridad para almacenar los vértices con menor distancia
    priority_queue<pair<int, Vertex<T>*>, vector<pair<int, Vertex<T>*> >, greater<>> pq;

    // Inicializar distancias con 'infinito' y predecesores con nulo
    for (Vertex<T>* vertice : vertexList) {
        distancias[vertice->data] = numeric_limits<int>::max();
        predecesores[vertice->data] = nullptr;
    }

    // Establecer la distancia al vértice de inicio como 0
    distancias[inicio] = 0;

    // Encolar el vértice de inicio
    pq.push({0, getVertex(inicio)});

    // Algoritmo de Dijkstra
    while (!pq.empty()) {
        Vertex<T>* verticeActual = pq.top().second;
        int distanciaActual = pq.top().first;
        pq.pop();

        // Si llegamos al vértice de destino, reconstruir el camino y devolverlo
        if (verticeActual->data == fin) {
            vector<T> camino;
            T actual = fin;
            while (actual != inicio) {
                camino.push_back(actual);
                actual = predecesores[actual];
            }
            camino.push_back(inicio);
            reverse(camino.begin(), camino.end());
            return camino;
        }

        // Iterar a través de los vecinos del vértice actual
        for (Edge<T>* arista: verticeActual->connectedTo) {
            Vertex<T>* vecino = arista->to;
            int nuevaDistancia = distanciaActual + arista->weight;

            // Actualizar la distancia si se encuentra un camino más corto
            if (nuevaDistancia < distancias[vecino->data]) {
                distancias[vecino->data] = nuevaDistancia;
                predecesores[vecino->data] = verticeActual->data;
                pq.push({nuevaDistancia, vecino});
            }
        }
    }

    // Si no se encuentra un camino, devolver un vector vacío
    return {};
}

template class Edge<string>;
template class Vertex<string>;
template class Graph<string>;
