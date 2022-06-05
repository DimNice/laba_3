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
    return INT_MAX * 1.0;
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
        //Если нет такое вершина
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
