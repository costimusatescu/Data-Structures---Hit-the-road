// Copyright 2018 Musatescu Costin-Teodor 314CA
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "hashtable.h"

// Hash string
unsigned int hash_fct(string str) {
    unsigned int hash = 5381;

    for (int i = 0; i < str.size(); i++) {
        hash = ((hash << 5) + hash) + str[i];
    }

    return hash;
}

// Hash int
unsigned int HashingFunction(int nr) {
    return nr % 10;
}

// Dfs recursiv
void DFSUtil(int u, vector<int> adj[], vector<bool> &visited) {
    visited[u] = true;
	
    for (int i = 0; i < adj[u].size(); i++) {
        if (visited[adj[u][i]] == false) {
            DFSUtil(adj[u][i], adj, visited);
        }
    }
}

// Componente conexe
int componente_conexe(vector<int> adj[], int V) {
    int l = 0;
    vector<bool> visited(V, false);
	
    for (int u = 0; u < V; u++) {
        if (visited[u] == false) {
            DFSUtil(u, adj, visited);
            l++;
        }
    }
	
    return l;
}

int main()
{	
    // Initializare date
    int N = 0, M = 0;
    int i;
    int max_aglom = -1;
    int *gr_aglom;
    string oras_aglom = "zzz";
    string x, y;
    string word;

    // Initializare fisiere de iesire
    ofstream t1;
    ofstream t2;

    t1.open("task1.out");
    t2.open("task2.out");

    std::cin >> N >> M;

    vector <int> v[N];

    // Alocare memorie
    gr_aglom = new int[N];

    // Initializare grad de aglomeratie cu 0 
    for (i = 0; i < N; i++) {
        gr_aglom[i] = 0;
    }

    Hashtable<string, int> htable1(N, &hash_fct);
    Hashtable<int, string> htable2(N, &HashingFunction);

    // Citirea oraselor si punerea lor in noduri
    for (i = 0; i < N; i++) {
        std::cin >> word;
        htable1.put(word, i);
        htable2.put(i, word);
    }

    // Citirea legaturilor dintre orase
    for (i = 0; i < M ; i++) {
        std::cin >> x >> y;
        v[htable1.get(x)].push_back(htable1.get(y));
        gr_aglom[htable1.get(y)]++;
    }

    // Cel mai aglomerat oras
    for (i = 0; i < N; i++) {
        if (gr_aglom[i] > max_aglom) {
            max_aglom = gr_aglom[i];
            oras_aglom = htable2.get(i);
        }
    }

    // Scrierea in primul fisier
    t1  << oras_aglom << " " << max_aglom;

    // Scrierea in cel de-al doilea fisier
    if (componente_conexe(v, N) == 1) {
        t2 << "HARTA VALIDA";
    }
    else
    {
        t2 << "HARTA INVALIDA";
    }

    // Dealocarea memoriei
    delete[] gr_aglom;

    // Inchiderea fisierelor
    t1.close();
    t2.close();

    return 0;
}
