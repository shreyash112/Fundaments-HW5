#include<bits/stdc++.h>
using namespace std;
# define infi 0x3f3f3f3f
#define size_of_file 72 ///total line in the text file
int num_size = size_of_file * 3;
typedef pair<int, float> v_w;

string convert_s(string a);
#define maxints 300
ifstream inf;

int count1 =0;
int j = 0;
string x;
int v1[size_of_file];
int v2[size_of_file];
float dist[size_of_file];
string l1[maxints];
static int count2;

void readinput()
{
  inf.open("map_points.txt");
  if (inf.fail())
  {
    cerr << "Error: Could not open input file\n";
    exit(1);
  }
  while (count1 < maxints)
  {
    try
    {
        inf >> x;
    }
    catch (std::ifstream::failure e)
    {
        break;
    }
    l1[count1++] = x;
  }
  count2 = count1;
inf.close(); //Close the file at the end of your program.
}

void input_matrix(string l1[])
{
    ///For V1
    for(int i = 0; i < num_size; i=i+3)
    {
        string v_1 = l1[i];
        v_1 = convert_s(v_1);
        int u = stoi(v_1);
        v1[j] = u ;
        j++;
    }
    ///For V2
    j=0;
    for(int i = 1; i < num_size; i=i+3)
    {
        string v_2 = l1[i];
        v_2 = convert_s(v_2);
        int v = stoi(v_2);
        v2[j] = v;
        j++;
    }
    ///For distance
    j=0;
    for(int i = 2; i < num_size; i=i+3)
    {
        string z = l1[i];
        float z1 = stof(z);
        dist[j] = z1;
        j++;
    }

}

string convert_i(int j)
{
    if(j==89)
        return "23a";
    if(j==85)
        return "23b";
    if(j==87)
        return "23c";
    if(j==88)
        return "23e";
    if(j==86)
        return "23f";
    if(j==83)
        return "23g";
    if(j==84)
        return "23h";
    else
        return to_string(j);

}

string convert_s(string a)
{
    if(a=="23a")
        return "89";
    if(a=="23b")
        return "85";
    if(a=="23c")
        return "87";
    if(a=="23e")
        return "88";
    if(a=="23f")
        return "86";
    if(a=="23g")
        return "83";
    if(a=="23h")
        return "84";
    else
        return a;
}

void printPath(int parent[], int j)
{
    if (parent[j] == 0)
       return;
    printPath(parent, parent[j]);
    string f = convert_i(j);
    cout << " --> " << f;
}

void addEdge(vector <pair<int, float> > adj[], int u, int v, float wt)
{
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void dijakstra(vector<pair<int,float> > adj[], int V, int src,int dest)
{
    priority_queue< v_w, vector <v_w>,greater<v_w> > pq;
    vector<float> dist(V, infi);
    int parent[100] = {-1};
    parent[0] = -1;
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        for (auto x : adj[u])
        {
            int v = x.first;
            float weight = x.second;
            if (dist[v] > dist[u] + weight)
            {
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
        string destin = convert_i(dest);
        cout << "Distance from "<< src << " to " << destin << " is: "<<dist[dest];
        cout <<"\n";
        cout << "Path for the shortest distance";
        cout <<"\n";
        cout << convert_i(src);
        printPath(parent,dest);
    }
}

int main()
{
    readinput();
    input_matrix(l1);
    int V = 100;
    string source,desti;
    vector<v_w> adj[V];
    for(int i = 0;i < size_of_file;i++)
    {
        addEdge(adj,v1[i],v2[i],dist[i]);
    }
    cout << "Enter the source: ";
    cin >> source;
    cout << "Enter the destination: ";
    cin >> desti;
    source = convert_s(source);
    desti = convert_s(desti);
    dijakstra(adj, V,stoi(source),stoi(desti));

	return 0;
}
