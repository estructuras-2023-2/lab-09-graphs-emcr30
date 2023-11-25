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

    bool todosConectados(const vector<string>& ciudades) {
        if (ciudades.empty()) return true;
        string raiz = buscar(ciudades.front());
        for (const auto& ciudad : ciudades) {
            if (buscar(ciudad) != raiz) return false;
        }
        return true;
    }
};

struct Carretera {
    string id;
    string ciudad1;
    string ciudad2;
    int costo;

    Carretera(string i, string c1, string c2, int co = -1) : id(i), ciudad1(c1), ciudad2(c2), costo(co) {}
};

vector<string> dividir(const string& str, char delim) {
    vector<string> tokens;
    size_t inicio = 0;
    size_t fin = str.find(delim);
    while (fin != string::npos) {
        tokens.push_back(str.substr(inicio, fin - inicio));
        inicio = fin + 1;
        fin = str.find(delim, inicio);
    }
    tokens.push_back(str.substr(inicio));
    return tokens;
}


