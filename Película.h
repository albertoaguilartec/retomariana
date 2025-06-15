#ifndef PELICULA_H
#define PELICULA_H

#include "Video.h"
#include <string>

class Pelicula : public Video {
public:
    // Constructor
    Pelicula(int id_val = 0, const std::string& nombre_val = "", int duracion_val = 0,
             const std::string& genero_val = "", int calif_promedio_val = 0);

    // Implementación del método imprimir para Pelicula
    void imprimir() const override;
};

#endif // PELICULA_H
