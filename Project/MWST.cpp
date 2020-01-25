#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

struct Graph
{
    int numVertices, numEdges;
    std::vector<std::pair<int, std::pair<int, int>>> graphEdges;
    std::vector<std::pair<int, std::pair<int, int>>> MST;
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
    
    void addEdge(int edge1, int edge2, int weight)
    {
        graphEdges.push_back({weight, {edge1, edge2}});
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
            vertex1 = find_set(graphEdges[i].second.first);
            vertex2 = find_set(graphEdges[i].second.second);
            if(vertex1 != vertex2)
            {
                MST.push_back(graphEdges[i]);
                union_set(vertex1, vertex2);
            }
        }
    }
    
};

int main()
{
    return 0;
}
