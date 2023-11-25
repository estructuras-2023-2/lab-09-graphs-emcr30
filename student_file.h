#include <string>
#include <vector>
#include <map>
#include <climits>
#include <set>

using namespace std;

class UnionFind {
private:
    map<string, string> padre;

public:
    string buscar(const string& s) {
        if (padre.find(s) == padre.end())
            padre[s] = s;
        else if (padre[s] != s)
            padre[s] = buscar(padre[s]);
        return padre[s];
    }

    void unir(const string& a, const string& b) {
        string raizA = buscar(a);
        string raizB = buscar(b);
        if (raizA != raizB)
            padre[raizA] = raizB;
    }

    bool estanConectados(const string& a, const string& b) {
        return buscar(a) == buscar(b);
    }




