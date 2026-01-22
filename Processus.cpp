#include "Processus.h"
#include "ContratException.h"

namespace TP {
    Processus::Processus(const std::string &p_pid, int p_arrivee, int p_duree, int p_attente, int p_priorite,
                         TypeProcessus p_type) : m_pid(p_pid), m_arrivee(p_arrivee), m_attente(p_attente),
                                                 m_duree(p_duree), m_priorite(p_priorite),
                                                 m_type(p_type) {
        PRECONDITION(p_arrivee >= 0);
        PRECONDITION(p_duree > 0);
        PRECONDITION(p_attente >= 0);
        PRECONDITION(0 <= p_priorite <= 127);
        PRECONDITION(1 <= static_cast<int>(p_type) <= 4);
        POSTCONDITION(p_arrivee == m_arrivee);
        POSTCONDITION(p_duree == m_duree);
        POSTCONDITION(p_attente == m_attente);
        POSTCONDITION(p_priorite == m_priorite);
        POSTCONDITION(p_type == m_type);
        INVARIANTS();
    }

    std::string Processus::getPid() const { return m_pid; }
    int Processus::getArrivee() const { return m_arrivee; }
    int Processus::getDuree() const { return m_duree; }
    int Processus::getRestant() const { return m_restant; }
    int Processus::getAttente() const { return m_attente; }
    int Processus::getFin() const { return m_fin; }
    int Processus::getPriorite() const { return m_priorite; }
    TypeProcessus Processus::getType() const { return m_type; }

    void Processus::setRestant(int p_restant) {
        PRECONDITION(p_restant>=0 && p_restant<=m_duree);
        m_restant = p_restant;
        POSTCONDITION(p_restant == m_restant);
        INVARIANTS();
    }

    void Processus::setAttente(int p_attente) {
        PRECONDITION(p_attente>=0);
        m_attente = p_attente;
        POSTCONDITION(m_attente == p_attente);
        INVARIANTS();
    }

    void Processus::setFin(int p_fin) {
        PRECONDITION(p_fin>=0);
        m_fin = p_fin;
        POSTCONDITION(p_fin == m_fin);
        INVARIANTS();
    }

    std::ostream &operator<<(std::ostream &os, const Processus &p_processus) {
        os << p_processus.getPid() << " arrivee : " << p_processus.getArrivee() << " Duree : " << p_processus.getDuree()
                << " temps d'attente : " << p_processus.getAttente()
                << " Priorite : " << p_processus.getPriorite()
                << " Type : " << static_cast<int>(p_processus.getType());
        return os;
    }

    bool Processus::operator<(const Processus &other) const {
        return m_priorite < other.m_priorite;
    }

    void Processus::verifieInvariant() const {
        INVARIANT(m_arrivee >= 0);
        INVARIANT(m_duree > 0);
        INVARIANT(m_attente >= 0);
        INVARIANT(0 <= m_priorite <= 127);
        INVARIANT(1 <= static_cast<int>(m_type) <= 4);
    }
}
