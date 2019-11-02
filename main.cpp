
// A simple representation of graph using STL
#include <iostream>
#include <fstream>
#include <stdexcept>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

#define maxints 1000
ifstream inf;
int count1 =0;
int j = 0;
int x;
int v1[100];
int v2[100];
int dist[100];
int l1[maxints];


// To add an edge
void addEdge(vector <pair<int, int> > adj[], int u, int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void readinput()
{
    inf.open("ints.txt");
  if (inf.fail())
  {
    cerr << "Error: Could not open input file\n";
    exit(1);
  }
  while (x != 99999)//Marks the end of the file
  {
    try
    {
        inf >> x;
    }
    catch (std::ifstream::failure e)
    {
        break;
    }
    if(x < 999)
    {

      l1[count1++]=x;
    }
  }
inf.close(); //Close the file at the end of your program.
}

void input_matrix(int l1[])
{
    ///For V1
    for(int i = 0; i < count1; i=i+3)
    {
        v1[j] = l1[i];
        j++;
    }

    ///For V2
    j=0;
    for(int i = 1; i < count1; i=i+3)
    {
        v2[j] = l1[i];
        j++;
    }

    ///For distance
    j=0;
    for(int i = 2; i < count1; i=i+3)
    {
        dist[j] = l1[i];
        j++;
    }

}

void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j] == 0)
       return;
    printPath(parent, parent[j]);
    cout << " --> " << j;
}

void dijakstra(vector<pair<int,int> > adj[], int V, int src,int dest)
{
    // Create a priority queue to store vertices that are being preprocessed. This is weird syntax in C++.
    // Refer below link for details of this syntax  http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

    // Create a vector for distances and initialize all distances as infinite (INF)
    vector<int> dist(V, INF);
    int parent[100] = {-1};
    parent[0] = -1;
    // Insert source itself in priority queue and initialize its distance as 0.
    pq.push(make_pair(0, src));
    dist[src] = 0;

    /* Looping till priority queue becomes empty (or all distances are not finalized) */
    while (!pq.empty())
    {

        int u = pq.top().second;
        pq.pop();

        // Get all adjacent of u.
        for (auto x : adj[u])
        {
            // Get vertex label and weight of current adjacent of u.

            int v = x.first;
            int weight = x.second;

            // If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                parent[v] = u;
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    if(dist[dest] > 10000)
    {
        cout<< "Invalid points not preset on the map";
    }
    else
    {
        cout << "Distance from "<< src << " to " << dest << " is: "<<dist[dest];
        cout <<"\n";
        cout << "Path for the shortest distance";
        cout <<"\n";
        cout << src;
        printPath(parent,dest);
    }
}

// Driver code
int main()
{
    readinput();
    input_matrix(l1);
    int V = 100;
    int source,desti;
    vector<iPair > adj[V];
    for(int i =0;i<100;i++)
    {
        addEdge(adj,v1[i],v2[i],dist[i]);
    }
    cout << "Enter the source: ";
    cin >> source;
    cout << "Enter the destination: ";
    cin >> desti;
    dijakstra(adj, V,source,desti);
	return 0;
}
