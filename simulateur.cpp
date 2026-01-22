#include "Processus.h"
#include "File.h"
#include "Ordonnanceur.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace TP;
using namespace std;

int main() {
    ifstream inputFile("Test.txt");
    if (!inputFile) {
        throw runtime_error("Erreur a l'ouverture du fichier.");
    }
    // Création File Test pour FCFS, SFJ (FJS) et Round Robin
    File<Processus> UneFile;
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string pid;
        int arrive, duree, attente, priorite, type;
        if (iss >> pid >> arrive >> duree >> attente >> priorite >> type) {
            const Processus newProcessus(pid, arrive, duree, attente, priorite, static_cast<TypeProcessus>(type));
            cout << newProcessus << endl;
            UneFile.enfiler(newProcessus);
        } else {
            throw runtime_error("Ligne invalide");
        }
    }
    inputFile.close();
    cout << "fin chargement" << endl << endl;

    // Test FCFS (First Come First Served)
    cout << "simulation de FCFS Resultat:" << endl;
    int tempsInitial = 0;
    float attenteTotal = 0;
    File<Processus> Result = fcfs(UneFile, tempsInitial);
    unsigned int taille = Result.getTaille();
    while (!Result.isEmpty()) {
        attenteTotal += Result.getTete().getAttente();
        cout << Result.defiler() << endl;
    }
    cout << "Temps d'attente moyen : " << attenteTotal / taille << endl;

    // Test SFJ (Shortest Job First)
    cout << "simulation de FJS Resultat:" << endl;
    tempsInitial = 0;
    attenteTotal = 0;
    Result = fjs(UneFile, tempsInitial);
    taille = Result.getTaille();
    while (!Result.isEmpty()) {
        attenteTotal += Result.getTete().getAttente();
        cout << Result.defiler() << endl;
    }
    cout << "Temps d'attente moyen : " << attenteTotal / taille << endl;

    // Test Round Robin (Tourniquet)
    cout << "simulation de Round Robin Resultat:" << endl;
    tempsInitial = 0;
    attenteTotal = 0;
    Result = round_robin(UneFile, 4, tempsInitial);
    taille = Result.getTaille();
    while (!Result.isEmpty()) {
        attenteTotal += Result.getTete().getAttente();
        cout << Result.defiler() << endl;
    }
    cout << "Temps d'attente moyen : " << attenteTotal / taille << endl;


    File<Processus> UneFile2;
    ifstream inputFile2("TestPriorite.txt");
    if (!inputFile2) {
        throw runtime_error("Erreur a l'ouverture du fichier.");
    }
    // Création File Test pour ordonnancement avec priorité
    cout << endl;
    while (getline(inputFile2, line)) {
        istringstream iss(line);
        string pid;
        int arrive, duree, attente, priorite, type;
        if (iss >> pid >> arrive >> duree >> attente >> priorite >> type) {
            const Processus newProcessus(pid, arrive, duree, attente, priorite, static_cast<TypeProcessus>(1));
            cout << newProcessus << endl;
            UneFile2.enfiler(newProcessus);
        } else {
            throw runtime_error("Ligne invalide");
        }
    }
    inputFile2.close();
    cout << "fin chargement" << endl;

    // Test de l'ordonancement avec priorité
    cout << "simulation avec priorite Resultat:" << endl;
    tempsInitial = 0;
    attenteTotal = 0;
    Result = priorite(UneFile2, tempsInitial);
    taille = Result.getTaille();
    while (!Result.isEmpty()) {
        attenteTotal += Result.getTete().getAttente();
        cout << Result.defiler() << endl;
    }
    cout << "Temps d'attente moyen : " << attenteTotal / taille << endl;

    File<Processus> UneFile3;
    ifstream inputFile3("TestMultiniveaux.txt");
    if (!inputFile3) {
        throw runtime_error("Erreur a l'ouverture du fichier.");
    }
    // Création File Test pour ordonnancement multiniveaux
    cout << endl;
    while (getline(inputFile3, line)) {
        istringstream iss(line);
        string pid;
        int arrive, duree, attente, priorite, type;
        if (iss >> pid >> arrive >> duree >> attente >> priorite >> type) {
            const Processus newProcessus(pid, arrive, duree, attente, priorite, static_cast<TypeProcessus>(type));
            cout << newProcessus << endl;
            UneFile3.enfiler(newProcessus);
        } else {
            throw runtime_error("Ligne invalide");
        }
    }
    inputFile3.close();
    cout << "fin chargement" << endl;

    // Test de l'ordonancement multiniveaux
    cout << "simulation multiniveaux Resultat:" << endl;
    tempsInitial = 0;
    attenteTotal = 0;
    Result = multiniveaux(UneFile3, 4, tempsInitial);
    taille = Result.getTaille();
    while (!Result.isEmpty()) {
        attenteTotal += Result.getTete().getAttente();
        cout << Result.defiler() << endl;
    }
    cout << "Temps d'attente moyen : " << attenteTotal / taille << endl;

    cout << endl << "Fin du programme" << endl;

    return 0;
}
