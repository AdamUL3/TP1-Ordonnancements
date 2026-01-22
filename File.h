
#ifndef FILE_H
#define FILE_H

#include <list>


namespace TP {
    template<typename Objet>

    class File {
    public:
        File();

        ~File();

        void enfiler(const Objet &x);

        Objet defiler();

        unsigned int getTaille() const;

        bool isEmpty() const;

        Objet getTete() const; // Lecture du prochain élément à défiler.
    private:
        std::list<Objet> laFile;
    };
}


#endif //FILE_H
