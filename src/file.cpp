#include "file.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

std::string readFile(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier : " << filename << endl;
        return "";
    }
    // Lire tout le contenu du fichier dans un string
    string content((std::istreambuf_iterator<char>(file)),
                         istreambuf_iterator<char>());

    file.close();

    return content;
}


