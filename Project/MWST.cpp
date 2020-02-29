#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iomanip>

struct Graph
{
    int numVertices, numEdges;
    std::vector<std::tuple<double, int, int, int>> graphEdges;
    std::vector<std::tuple<double, int, int, int>> MST;

    int *set;

    Graph(int numVertices, int numEdges)
    {
        this->numVertices = numVertices;
        this->numEdges = numEdges;
        set = new int[numVertices];
        for(int i = 0; i < numVertices; i++)
        {
            set[i] = i;
        }
    }
    
    void addEdge(int vert1, int vert2, double weight, int label)
    {
        graphEdges.push_back({weight, label, vert1, vert2});
    }

    int find_set(int i)
    {
        if(i == set[i])
        {
            return i;
        }
        else
        {
            return find_set(set[i]);
        }
    }
    
    void union_set(int edge1, int edge2)
    {
        set[edge1] = set[edge2];
    }

    void kruskal()
    {
        int vertex1, vertex2;
        sort(graphEdges.begin(), graphEdges.end());
        for(std::size_t i = 0; i < graphEdges.size(); i++)
        {
            vertex1 = find_set(std::get<2>(graphEdges[i]));
            vertex2 = find_set(std::get<3>(graphEdges[i]));
            if(vertex1 != vertex2)
            {
                MST.push_back(graphEdges[i]);
                union_set(vertex1, vertex2);
            }
        }
    }

    void print(std::ofstream& outputFile)
    {
        double totalWeight = 0;
        for(std::size_t i = 0; i < MST.size(); i++)
        {
            outputFile << std::fixed 
                       << std::setprecision(1) 
                       <<  std::get<1>(MST[i]) << ":" 
                       << "(" << std::get<2>(MST[i]) << ", " << std::get<3>(MST[i]) << ") " 
                       << std::get<0>(MST[i]) << std::endl;
            totalWeight += std::get<0>(MST[i]);
        }
        outputFile << std::fixed 
                   << std::setprecision(2)
                   << "Total Weight = " << totalWeight << std::endl;
    }
};

int main(int argc, char *argv[])
{
    std::ifstream inputFile;
    std::ofstream outputFile;
    int numVertices; 
    int numEdges;
    int edge1, edge2;
    double weight;
    if(argc < 3)
    {
        fprintf(stderr, "Require Input and Output Files.\n");
        exit(EXIT_FAILURE);
    }

    std::string inFileName = argv[1];
    std::string outFileName = argv[2];

    inputFile.open(inFileName);
    if(!inputFile)
    {
        fprintf(stderr, "Unable to open %s.\n", inFileName.c_str());
        exit(EXIT_FAILURE);
    }
    
    outputFile.open(outFileName);
    if(!outputFile)
    {
        fprintf(stderr, "Unable to open %s.\n", inFileName.c_str());
        exit(EXIT_FAILURE);
    }
    
    std::string numVertStr;
    getline(inputFile, numVertStr);
    numVertices = std::stoi(numVertStr);
    std::string numEdgesStr;
    getline(inputFile, numEdgesStr);
    numEdges = std::stoi(numEdgesStr);

    Graph G(numVertices, numEdges);

    for(int i = 0; i < numEdges; i++)
    {
        std::stringstream s;
        std::string line;
        getline(inputFile, line); 
        s << line;
        s >> edge1;
        s >> edge2;
        s >> weight;
        G.addEdge(edge1, edge2, weight, i+1);
    }

    G.kruskal();
    G.print(outputFile);

    inputFile.close();
    outputFile.close();
}
