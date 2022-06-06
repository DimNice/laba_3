#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string> 
#include <iomanip>
#include <sstream>
#include <stack>
#include <cmath>
#include <string.h>
#include  <numeric>
using namespace std;
vector<string>split(string& str, char delim = ' ')
{
    string word;
    stringstream in(str);
    vector<string>ans;
    while (getline(in, word, delim))
    {
        ans.push_back(word);
    }
    return ans;
}
class Punkt
{
private:
    string name;
    int cntPeople;
public:
    Punkt(const string& nm, const int& cn)
    {
        this->name = nm;
        this->cntPeople = cn;
    }
    Punkt(const Punkt& p)
    {
        this->name = p.getName();
        this->cntPeople = p.getPeoples();
    }

    string getName()const
    {
        return this->name;
    }

    int getPeoples()const
    {
        return this->cntPeople;
    }

    Punkt operator=(const Punkt& p)
    {
        if (this != &p)
        {
            this->cntPeople = p.getPeoples();
            this->name = p.getName();
        }
        return (*this);
    }
    void setName(const string& str)
    {
        this->name = str;
    }
    void setPeoples(const int& d)
    {
        this->cntPeople = d;
    }
    bool operator==(const Punkt& p)
    {
        return (this->getName() == p.getName() && this->cntPeople == p.getPeoples());
    }
    bool operator==(const string& str)
    {
        string a = this->getName();
        return equal(a.begin(), a.end(), str.begin(), str.end(), [](char a, char b) {
            return tolower(a) == tolower(b);
            });
    }
    friend istream& operator>>(istream& in, Punkt& p);
    friend ostream& operator<<(ostream& out, const Punkt& p);
};

class TGraph
{
private:
    vector<Punkt>vertex;

    struct Edge
    {
        int a;
        int b;
        double wieght;
        Edge(int src, int to, double wg)
        {
            this->a = src;
            this->b = to;
            this->wieght = wg;
        }
    };

    vector<Edge>edges;

    int getIndexVertex(const string& s);
    double getLenghWays(int src, int to);
public:

    void AddVertex(const Punkt& p);
    void AddEdge(const string& src, const string& to, double wg);
    void removeVertex(const string& name);
    void removeEdge(int index);
    void PrintVertexes();
    vector<vector<int>> toAdjList();
    void DFS(const string& src);
    void PrintGraf();
    void Djeykstra(const string& src);
    ~TGraph()
    {
        vertex.clear();
        edges.clear();
    }

};

int main()
{

    TGraph gr;

    gr.AddVertex(Punkt("Moscow", 12366666));
    gr.AddVertex(Punkt("Sankt Peterburg", 11368664));
    gr.AddVertex(Punkt("New York", 112366546));
    gr.AddVertex(Punkt("Texas", 84521245));
    gr.AddVertex(Punkt("Irkutsk", 84546125));
    gr.AddVertex(Punkt("Washington D.C", 45821245));
    gr.AddVertex(Punkt("Sidney", 5000252));
    gr.AddVertex(Punkt("Tokiyo", 4584525454));
    gr.AddVertex(Punkt("Krasniy Yar", 14941));
    gr.AddVertex(Punkt("Pekin", 122452145));
    gr.AddVertex(Punkt("Samara", 1000012));
    gr.AddVertex(Punkt("Parij", 45121636));
    gr.AddVertex(Punkt("Rio-Dijaynero", 4512656));

    gr.AddEdge("Moscow", "Samara", 890);
    gr.AddEdge("Moscow", "Irkutsk", 100);
    gr.AddEdge("Irkutsk", "Pekin", 1250);
    gr.AddEdge("Pekin", "Parij", 2000);
    gr.AddEdge("Parij", "Washington D.C", 1524);
    gr.AddEdge("Washington D.C", "Texas", 425);
    gr.AddEdge("Texas", "Krasniy Yar", 1200);
    gr.AddEdge("Pekin", "Tokiyo", 320);
    gr.AddEdge("Pekin", "Krasniy Yar", 120);
    gr.AddEdge("Krasniy Yar", "Tokiyo", 70);
    gr.AddEdge("Tokiyo", "Sidney", 220);

    gr.DFS("Moscow");
    gr.Djeykstra("Moscow");
    cout << endl;
    return 0;
}

istream& operator>>(istream& in, Punkt& p)
{
    string st;
    getline(in, st);
    vector<string>sp = split(st, ';');
    p.setName(sp[0]);
    p.setPeoples(std::stoi(sp[1].c_str()));
    return in;
}

ostream& operator<<(ostream& out, const Punkt& p)
{
    out << setw(25) << p.getName() << "|" << setw(8) << p.getPeoples();
    return out;
}

int TGraph::getIndexVertex(const string& s)
{
    for (int i = 0; i < this->vertex.size(); i++)
        if (this->vertex[i] == s)
            return i;
    return -1;
}

double TGraph::getLenghWays(int src, int to)
{
    for (auto& it : edges)
    {
        if (it.a == src && it.b == to)
            return it.wieght;
    }
    return 100000000.0;
}

void TGraph::AddVertex(const Punkt& p)
{
    this->vertex.push_back(p);
}

void TGraph::AddEdge(const string& src, const string& to, double wg)
{
    int a = getIndexVertex(src);
    int b = getIndexVertex(to);
    cout << a << endl;
    cout << b << endl;
    if (a == -1)
    {

        cout << "Error we can't found this punkt: \n";
        return;
    }
    if (b == -1)
    {

        cout << "Error we can't found this punkt: \n";
        return;
    }
    Edge ednew = Edge(a, b, wg);
    this->edges.push_back(ednew);
    cout << "added succesfuly\n";
}

void TGraph::removeVertex(const string& name)
{

    int a = getIndexVertex(name);
    if (a != -1)
    {
        vertex.erase(vertex.begin() + a);
        while (1)
        {
            int ind = -1;
            for (int i = 0; i < edges.size(); i++)
            {
                if (edges[i].a == a || edges[i].b == a)
                {
                    ind = i;
                    break;
                }
            }
            if (ind != -1)
            {
                edges.erase(edges.begin() + ind);

            }
            else
                break;
        }
        cout << "Deleted succesfuly\n";
    }
    else
    {
        cout << "Not found given punkt\n";
    }

}

void TGraph::removeEdge(int index)
{
    if (index >= 0 && index < edges.size())
    {
        edges.erase(edges.begin() + index);
        cout << "Has deleted\n";
    }
    else
    {
        cout << "Incorrect index\n";
    }
}

void TGraph::PrintVertexes()
{
    cout << setw(25) << "  Name  " << "|" << setw(8) << "Peoples" << endl;
    cout << "|++++++++++++++++++++++++|++++++++|\n";
    for (auto& it : vertex)
        cout << it << endl;
    cout << "|++++++++++++++++++++++++|++++++++|\n";
}

vector<vector<int>> TGraph::toAdjList()
{
    vector<vector<int>>adj(vertex.size(), vector<int>());//Список смежности
    for (int i = 0; i < edges.size(); i++)
    {
        adj[edges[i].a].push_back(edges[i].b);//Граф ориентированный
    }
    return adj;
}

void TGraph::DFS(const string& src)
{
    cout << "----------------------------------DFS-------------------------------------\n";
    int s = getIndexVertex(src);//индекс населленого пункта
    if (s == -1)
    {
        cout << "Error src Punkt\n";
        return;
    }
    vector<vector<int>>adj = toAdjList();
    //Реализуем обход в глубину
    vector<bool> visited(vertex.size(), false);
    stack<int> stack;

    stack.push(s);
    cout << "\n\n";
    while (!stack.empty())
    {
        int s = stack.top();
        stack.pop();
        if (!visited[s])
        {
            cout << "(**" << vertex[s].getName() << "**)" << "->";
            visited[s] = true;
        }
        for (auto i : adj[s])
            if (!visited[i])
                stack.push(i);
    }
    cout << "\n\n";
}


void TGraph::PrintGraf()
{
    vector<vector<int>>adjList = toAdjList();
    for (int i = 0; i < adjList.size(); i++)
    {
        cout << "(" << vertex[i] << "  )-->";
        for (auto it : adjList[i])
        {
            cout << "[ " << vertex[it] << "{" << it << "}" << " way lenght: " << getLenghWays(i, it) << " ]  ";
        }
        cout << endl;
    }
}

void TGraph::Djeykstra(const string& src)
{
    int s = getIndexVertex(src);//Стартавая вершина
    if (s == -1)
    {
        cout << "Punkt can\'t find\n";
    }
    vector<double>d(vertex.size(), 100000000.0);//Длина дорог
    vector<int>p(vertex.size());
    d[s] = 0.0;
    vector<bool>used(vertex.size(), false);//Использован или нет
    vector<vector<int>> adj = toAdjList();
    PrintGraf();
    for (int i = 0; i < vertex.size(); i++)
    {
        int v = -1;
        for (int j = 0; j < vertex.size(); j++)
        {
            if (!used[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }
        if (d[v] >= 100000000.0 - 1.0)
        {
            break;
        }
        used[v] = true;
        for (size_t j = 0; j < adj[v].size(); j++)
        {
            int to = adj[v][j];
            double len = getLenghWays(v, to);
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }

        }
    }
    cout << endl;
    cout << "The shortest way from " << vertex[s].getName() << " to all punkt\n";

    cout << "s-" << s << endl;
    for (int tos = 0; tos < vertex.size(); tos++)
    {
        vector<int>doroga;
        for (int i = tos; i != s; i = p[i])
            doroga.push_back(i);
        doroga.push_back(s);
        reverse(doroga.begin(), doroga.end());

        if (doroga.size() > 1)
        {
            double ln = 0.0;
            cout << "[ ";
            for (int i = 0; i < doroga.size() - 1; i++)
            {
                cout << vertex[doroga[i]].getName() << "->";
                ln += getLenghWays(doroga[i], doroga[i + 1]);
            }
          //  ln += getLenghWays(doroga[doroga.size() - 2], doroga[doroga.size() - 1]);
            cout << vertex[doroga[doroga.size() - 1]].getName();
            if (ln < 1e+8)
                cout << " ] " << "\tThe short path length=" << setw(8) << ln << " ";

            else
                cout << " \tno way :(\n";
            cout << endl;
        }
    }
}
