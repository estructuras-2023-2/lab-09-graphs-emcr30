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

string reconstruye(vector<string> carreteras) {
    vector<Carretera> todasCarreteras;
    vector<string> todasCiudades;
    UnionFind uf;
    set<string> carreterasReconstruir;

    for (const auto& carreteraStr : carreteras) {
        auto tokens = dividir(carreteraStr, ' ');
        todasCiudades.push_back(tokens[1]);
        todasCiudades.push_back(tokens[2]);
        if (tokens.size() == 4) {
            todasCarreteras.emplace_back(tokens[0], tokens[1], tokens[2], stoi(tokens[3]));
        } else {
            uf.unir(tokens[1], tokens[2]);
        }
    }

 for (const auto& carretera : todasCarreteras) {
        if (!uf.estanConectados(carretera.ciudad1, carretera.ciudad2)) {
            uf.unir(carretera.ciudad1, carretera.ciudad2);
            carreterasReconstruir.insert(carretera.id);
        }
    }

    if (!uf.todosConectados(todasCiudades)) {
        return "IMPOSIBLE";
    }

    string resultado;
    for (const auto& id : carreterasReconstruir) {
        resultado += id + " ";
    }

    return resultado.empty() ? "" : resultado.substr(0, resultado.length() - 1);
}
