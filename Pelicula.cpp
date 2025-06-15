#include "Pelicula.h"
#include <iostream>

Pelicula::Pelicula(int id_val, const std::string& nombre_val, int duracion_val,
                   const std::string& genero_val, int calif_promedio_val)
    : Video(id_val, nombre_val, duracion_val, genero_val, calif_promedio_val) {}

void Pelicula::imprimir() const {
    std::cout << "Pelicula ID: " << id << ", Nombre: " << nombre
              << ", Duracion: " << duracion << " min, Genero: " << genero
              << ", Calificacion Promedio: " << calif_promedio << std::endl;
}
