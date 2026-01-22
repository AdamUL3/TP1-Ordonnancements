#include "Ordonnanceur.h"
#include "File.h"
#include "Processus.h"
#include "ContratException.h"
#include <vector>
#include <algorithm>


using namespace std;

namespace TP {
    File<Processus> fcfs(File<Processus> f_entree, int &temps) {
        PRECONDITION(0 <= temps);
        unsigned int tailleFile = f_entree.getTaille();
        File<Processus> nouvelleFile;
        // On loop tant que les processus n'ont pas tous été traités
        while (!f_entree.isEmpty()) {
            Processus CurrentProcess = f_entree.defiler();
            // Si processus arrivé
            if (CurrentProcess.getArrivee() <= temps) {
                // On complète le processus
                CurrentProcess.setAttente(temps - CurrentProcess.getArrivee());
                CurrentProcess.setFin(temps);
                temps = temps + CurrentProcess.getDuree();
                nouvelleFile.enfiler(CurrentProcess);
            } else {
                // Incrémenter le temps si aucun processus arrivé
                f_entree.enfiler(CurrentProcess);
                temps++;
            }
        }
        POSTCONDITION(tailleFile == nouvelleFile.getTaille());
        POSTCONDITION(f_entree.isEmpty());
        return nouvelleFile;
    }

    File<Processus> fjs(File<Processus> f_entree, int &temps) {
        PRECONDITION(0 <= temps);
        unsigned int tailleFile = f_entree.getTaille();
        File<Processus> nouvelleFile;
        vector<Processus> processusArrives;
        // On loop tant que les processus n'ont pas tous été traités
        while (!f_entree.isEmpty() || !processusArrives.empty()) {
            // Check les processus arrivés
            for (unsigned int i = 0; i < f_entree.getTaille(); ++i) {
                if (f_entree.getTete().getArrivee() <= temps) {
                    processusArrives.push_back(f_entree.defiler());
                    i--;
                } else { f_entree.enfiler(f_entree.defiler()); }
            }
            // Sort() les processus arrivés du vector selon la durée la plus courte
            if (!processusArrives.empty()) {
                sort(processusArrives.begin(), processusArrives.end(), [](const Processus &a, const Processus &b) {
                    return a.getDuree() < b.getDuree();
                });
                Processus processusActuelle = processusArrives.front(); // Processus avec la durée la plus courte
                processusArrives.erase(processusArrives.begin()); // On l'enlève de la liste des processus arrivés
                // On complète le processus
                processusActuelle.setAttente(temps - processusActuelle.getArrivee());
                temps += processusActuelle.getDuree();
                processusActuelle.setFin(temps);
                nouvelleFile.enfiler(processusActuelle);
            } else {
                // Incrémenter le temps si aucun processus arrivé
                temps++;
            }
        }
        POSTCONDITION(tailleFile == nouvelleFile.getTaille());
        POSTCONDITION(processusArrives.empty());
        POSTCONDITION(f_entree.isEmpty());
        return nouvelleFile;
    }

    File<Processus> round_robin(File<Processus> f_entree, int quantum, int &temps) {
        PRECONDITION(0 <= temps);
        PRECONDITION(0 < quantum);
        unsigned int tailleFile = f_entree.getTaille();
        File<Processus> nouvelleFile;
        std::vector<Processus> processusArrives;
        // On loop tant que les processus n'ont pas tous été traités
        while (!f_entree.isEmpty() || !processusArrives.empty()) {
            // Check les processus arrivés
            for (unsigned int i = 0; i < f_entree.getTaille(); ++i) {
                Processus UnProcessus = f_entree.defiler();
                if (UnProcessus.getArrivee() <= temps) {
                    UnProcessus.setRestant(UnProcessus.getDuree());
                    processusArrives.push_back(UnProcessus);
                    i--;
                } else { f_entree.enfiler(UnProcessus); }
            }

            // Si des processus sont prêts à être traités
            if (!processusArrives.empty()) {
                Processus &processusActuel = processusArrives.front();
                // On complète le processus
                unsigned int tempsExecution = min(processusActuel.getRestant(), quantum);
                processusActuel.setRestant(processusActuel.getRestant() - tempsExecution);
                // On update le temps d'attente des autres processus
                for (unsigned int i = 1; i < processusArrives.size(); ++i) {
                    processusArrives[i].setAttente(processusArrives[i].getAttente() + tempsExecution);
                }
                temps += tempsExecution;

                // Si le processus est terminé
                if (processusActuel.getRestant() == 0) {
                    processusActuel.setFin(temps);
                    nouvelleFile.enfiler(processusActuel);
                    processusArrives.erase(processusArrives.begin());
                } else {
                    // On remet derrière la file pour passer au processus suivant (tourniquet)
                    processusArrives.push_back(processusActuel);
                    processusArrives.erase(processusArrives.begin());
                }
            } else {
                // Incrémenter le temps si aucun processus arrivé
                temps++;
            }
        }
        POSTCONDITION(tailleFile == nouvelleFile.getTaille());
        POSTCONDITION(processusArrives.empty());
        POSTCONDITION(f_entree.isEmpty());
        return nouvelleFile;
    }

    File<Processus> priorite(File<Processus> f_entree, int &temps) {
        PRECONDITION(0 <= temps);
        unsigned int tailleFile = f_entree.getTaille();
        File<Processus> nouvelleFile;
        vector<Processus> processusArrives;
        // On loop tant que les processus n'ont pas tous été traités
        while (!f_entree.isEmpty() || !processusArrives.empty()) {
            // Check les processus arrivés
            for (unsigned int i = 0; i < f_entree.getTaille(); ++i) {
                if (f_entree.getTete().getArrivee() <= temps) {
                    processusArrives.push_back(f_entree.defiler());
                    i--;
                } else { f_entree.enfiler(f_entree.defiler()); }
            }
            // Sort() les processus arrivés du vecteur selon la priorité
            if (!processusArrives.empty()) {
                sort(processusArrives.begin(), processusArrives.end(), [](const Processus &a, const Processus &b) {
                    return a.getPriorite() > b.getPriorite();
                });
                Processus processusActuelle = processusArrives.front(); // Processus le plus prioritaire
                processusArrives.erase(processusArrives.begin()); // On l'enlève de la liste des processus arrivés
                // On complète le processus
                processusActuelle.setAttente(temps - processusActuelle.getArrivee());
                temps += processusActuelle.getDuree();
                processusActuelle.setFin(temps);
                nouvelleFile.enfiler(processusActuelle);
            } else {
                // Incrémenter le temps si aucun processus arrivé
                temps++;
            }
        }
        POSTCONDITION(tailleFile==nouvelleFile.getTaille());
        POSTCONDITION(processusArrives.empty());
        POSTCONDITION(f_entree.isEmpty());
        return nouvelleFile;
    }

    File<Processus> multiniveaux(File<Processus> f_entree, int quantum, int &temps) {
        PRECONDITION(0 <= temps);
        PRECONDITION(0 < quantum);
        unsigned int tailleFile = f_entree.getTaille();
        // La fonction traite les processus temps par temps (à l'exception de Round Robin où le quantum rentre en jeu).
        File<Processus> nouvelleFile;
        vector<Processus> systemeArrives;
        vector<Processus> interactifArrives;
        vector<Processus> batchArrives;
        vector<Processus> utilisateurArrives;
        vector<vector<Processus> *> TousLesFiles = {
            &systemeArrives, &interactifArrives, &batchArrives, &utilisateurArrives
        }; // Sert pour updater le temps d'attente de tous les processus en meme temps

        // Boucle principale pour traiter les processus
        while (!f_entree.isEmpty() || !systemeArrives.empty() || !interactifArrives.empty() || !batchArrives.empty() ||
               !utilisateurArrives.empty()) {
            // Check les processus arrivés et les place dans leurs vecteurs appropriés
            for (unsigned int i = 0; i < f_entree.getTaille(); ++i) {
                Processus UnProcessus = f_entree.defiler();
                if (UnProcessus.getArrivee() <= temps) {
                    UnProcessus.setRestant(UnProcessus.getDuree());
                    switch (UnProcessus.getType()) {
                        case TypeProcessus::SYSTEME:
                            systemeArrives.push_back(UnProcessus);
                            break;
                        case TypeProcessus::INTERACTIF:
                            interactifArrives.push_back(UnProcessus);
                            break;
                        case TypeProcessus::BATCH:
                            batchArrives.push_back(UnProcessus);
                            break;
                        case TypeProcessus::UTILISATEUR:
                            utilisateurArrives.push_back(UnProcessus);
                            break;
                    }
                    i--;
                } else {
                    f_entree.enfiler(UnProcessus);
                }
            }

            // 1. Traiter les processus systèmes avec priorité
            if (!systemeArrives.empty()) {
                // Sort() les processus arrivés du vecteur selon la priorité
                sort(systemeArrives.begin(), systemeArrives.end(), [](const Processus &a, const Processus &b) {
                    return a.getPriorite() > b.getPriorite();
                });
                Processus &processusActuel = systemeArrives.front(); // Processus le plus prioritaire
                // On incrémente le processus
                processusActuel.setRestant(processusActuel.getRestant() - 1);
                // On update le temps d'attente des autres processus
                for (auto &file: TousLesFiles) {
                    for (auto &f: *file) {
                        if (&f != &processusActuel) {
                            f.setAttente(f.getAttente() + 1);
                        }
                    }
                }
                if (processusActuel.getRestant() == 0) {
                    processusActuel.setFin(temps);
                    nouvelleFile.enfiler(processusActuel);
                    systemeArrives.erase(systemeArrives.begin());
                }
                // 2. Traiter les processus interactif avec Round Robin
            } else if (!interactifArrives.empty()) {
                Processus &processusActuel = interactifArrives.front();
                // On incrémente le processus
                unsigned int tempsExecution = min(processusActuel.getRestant(), quantum);
                processusActuel.setRestant(processusActuel.getRestant() - tempsExecution);
                // Updater le temps d'attente pour les autres processus
                for (auto &file: TousLesFiles) {
                    for (auto &f: *file) {
                        if (&f != &processusActuel) f.setAttente(f.getAttente() + tempsExecution);
                    }
                }
                temps += tempsExecution - 1; // -1 car on incrémente déjà par défaut a la fin des conditions

                // Si le processus est terminé
                if (processusActuel.getRestant() == 0) {
                    processusActuel.setFin(temps);
                    nouvelleFile.enfiler(processusActuel);
                    interactifArrives.erase(interactifArrives.begin());
                } else {
                    // On remet derrière la file pour passer au processus suivant (tourniquet)
                    interactifArrives.push_back(processusActuel);
                    interactifArrives.erase(interactifArrives.begin());
                }
                // 3. Traiter les processus batch avec FCFS
            } else if (!batchArrives.empty()) {
                // On incrémente le processus
                Processus &processusActuel = batchArrives.front();
                processusActuel.setRestant(processusActuel.getRestant() - 1);
                // Updater le temps d'attente pour les autres processus
                for (auto &file: TousLesFiles) {
                    for (auto &f: *file) {
                        if (&f != &processusActuel) f.setAttente(f.getAttente() + 1);
                    }
                }
                if (processusActuel.getRestant() == 0) {
                    processusActuel.setFin(temps);
                    nouvelleFile.enfiler(processusActuel);
                    batchArrives.erase(batchArrives.begin());
                }
                // 4. Traiter les processus utilisateur avec FCFS
            } else if (!utilisateurArrives.empty()) {
                // On incrémente le processus
                Processus &processusActuel = utilisateurArrives.front();
                processusActuel.setRestant(processusActuel.getRestant() - 1);
                // Updater le temps d'attente pour les autres processus
                for (auto &file: TousLesFiles) {
                    for (auto &f: *file) {
                        if (&f != &processusActuel) f.setAttente(f.getAttente() + 1);
                    }
                }
                if (processusActuel.getRestant() == 0) {
                    processusActuel.setFin(temps);
                    nouvelleFile.enfiler(processusActuel);
                    utilisateurArrives.erase(utilisateurArrives.begin());
                }
            }
            // Incrémenter le temps après avoir fait le traitement d'un processus (ou non)
            temps++;
        }
        POSTCONDITION(tailleFile == nouvelleFile.getTaille());
        POSTCONDITION(systemeArrives.empty());
        POSTCONDITION(interactifArrives.empty());
        POSTCONDITION(batchArrives.empty());
        POSTCONDITION(utilisateurArrives.empty());
        POSTCONDITION(f_entree.isEmpty());
        return nouvelleFile;
    }
}
