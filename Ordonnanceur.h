#ifndef ORDONNANCEUR_H
#define ORDONNANCEUR_H

#include "File.h"
#include "Processus.h"

namespace TP {
    File<Processus> fcfs(File<Processus> f_entree, int &temps); // First Come First Served
    File<Processus> fjs(File<Processus> f_entree, int &temps); // Shortest First
    File<Processus> round_robin(File<Processus> f_entree, int quantum, int &temps); // Round Robin (tourniquet)
    File<Processus> priorite(File<Processus> f_entree, int &temps); // Par priorité
    File<Processus> multiniveaux(File<Processus> f_entree, int quantum, int &temps); // File d'attente multiniveaux
}

#endif
