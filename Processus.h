#ifndef PROCESSUS_H
#define PROCESSUS_H

#include <iostream>
#include <string>

namespace TP {
    enum class TypeProcessus {
        SYSTEME = 1,
        INTERACTIF = 2,
        BATCH = 3,
        UTILISATEUR = 4
    };

    class Processus {
    private:
        std::string m_pid; // Identifiant pour l’affichage du résultat
        int m_arrivee; // Instant d’arrivée du processus dans le système
        int m_duree; // Duree d’exécution initiale du processus
        int m_restant = 0; // Temps restant à exécuter
        int m_attente; // Temps d’attente cumulé
        int m_fin = 0; // Temps à la préhemption (RR)
        int m_priorite; // priorité du processus
        TypeProcessus m_type; // Type du processus pour multiniveaux
        void verifieInvariant() const;

    public:
        Processus(const std::string &p_pid, int p_arrivee, int p_duree, int p_attente, int p_priorite,
                  TypeProcessus p_type);

        // Accesseurs
        std::string getPid() const;

        int getArrivee() const;

        int getDuree() const;

        int getRestant() const;

        int getAttente() const;

        int getFin() const;

        int getPriorite() const;

        TypeProcessus getType() const;

        // Mutateurs
        void setRestant(int p_restant);

        void setAttente(int p_attente);

        void setFin(int p_fin);

        // Méthodes surchagées
        friend std::ostream &operator<<(std::ostream &os, const Processus &p_processus);

        bool operator<(const Processus &other) const;
    };
}
#endif //PROCESSUS_H
