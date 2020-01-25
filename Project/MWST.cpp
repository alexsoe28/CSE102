#include <utility>
#include <vector>
#include <algorithm>
#include <

struct edge
{
    int edge1, edge2, weight;
    edge(int edge1, int edge2, int weight)
    {
        this->edge1 = edge1;
        this->edge2 = edge2;
        this->weight = weight;
    }
};

struct Graph
{
    int numVertices, numEdges;
    std::vector<edge> graphEdges;

    Graph(int numVertices, int numEdges)
    {
        this->numVertices = numVertices;
        this->numEdges = numEdges;
    }
    
    void addEdge(int u, int v, int weight)
    {
        edge newEdge = edge(u, v, weight);
        graphEdges.push_back(newEdge);
    }

};



int main()
{
    return 0;
}
