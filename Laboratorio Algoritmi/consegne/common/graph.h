//
// Created by sandr_ft5c0vu on 19/05/2026.
//

#ifndef LABORATORIO_ALGORITMI_GRAPH_H
#define LABORATORIO_ALGORITMI_GRAPH_H

#include <iostream>
#include <fstream>

#define DEBUG_MODE false

struct queue;
typedef struct queue queue_t;

struct queue_node;
typedef struct queue_node qnode_t;

/// @brief Struttura del vertice
struct vertex;
typedef struct vertex vertex_t;

/// @brief Struttura del grafo
class graph;
typedef class graph graph_t;

/// @brief DFS modificato per vedere se un array di interi e' presente con lo stesso
/// ordine nel grafo
/// @param g        Grafo
/// @param n        Dimensione dell'array di interi `datas`
/// @param datas    Array di interi
bool dfs(graph_t* g, int* datas, int n, bool debug = DEBUG_MODE);
/// @param u        Nodo di partenza
/// @param visited  Array per tenere traccia delle visite
/// @param edges    Archi del grafo
/// @param datas    Array di interi
/// @param n        Dimensione dell'array di interi `datas`
/// @param count    Varabile contatore per tenere traccia i dati di `datas` trovati
bool dfsAux(int u, vertex_t* edges[], int* datas, int n, int count, bool debug = DEBUG_MODE);

#endif //LABORATORIO_ALGORITMI_GRAPH_H
