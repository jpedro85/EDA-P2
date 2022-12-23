#include <string>
#include <fstream>

using namespace std;

int tamanho(string nome) {
    fstream fs;

    fs.open(nome, ifstream::in);
    if (fs.is_open()) {

        int nl = 0;
        string line;
        while (getline(fs, line))
            ++nl;
        fs.close();
        return nl;
    }
}

void import_files(string nome, string v[]) {
    fstream ficheiro;
    string line;
    int i = 0;
    ficheiro.open(nome, ifstream::in);
    if (ficheiro.is_open()) {
        while (getline(ficheiro, line)) {
            v[i] = line;
            i++;
        }
    }
    ficheiro.close();
}

void save_file(std::string directory, std::string areas[], int capacidade) {
    fstream file;
    string line;
    file.open(directory, fstream::out);
    if (file.is_open()) {
        for (int i = 0; i < capacidade; i++)
        {
            file << areas[i] << endl;
        }
    }
    file.close();
}