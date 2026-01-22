#include "File.h"
#include "Processus.h"
#include <stdexcept>

namespace TP {
    template<typename Objet>
    File<Objet>::File() {
    }

    template<typename Objet>
    File<Objet>::~File() { laFile.clear(); }

    template<typename Objet>
    void File<Objet>::enfiler(const Objet &x) { laFile.push_front(x); }

    template<typename Objet>
    Objet File<Objet>::defiler() {
        if (getTaille() == 0) throw std::logic_error("La file est vide");
        Objet ret = laFile.back();
        laFile.pop_back();
        return ret;
    }

    template<typename Objet>
    bool File<Objet>::isEmpty() const { return laFile.empty(); }

    template<typename Objet>
    unsigned int File<Objet>::getTaille() const { return laFile.size(); };

    template<typename Objet>
    Objet File<Objet>::getTete() const {
        if (getTaille() == 0) throw std::logic_error("La file est vide");
        return laFile.back();
    }

    // Instanciation de la classe pour Processus
    template class File<Processus>;
}
