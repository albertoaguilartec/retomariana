#include "Serie.h"
#include <iostream>

Serie::Serie(int id_val, const std::string& nombre_val, int duracion_val,
             const std::string& genero_val, int calif_promedio_val)
    : Video(id_val, nombre_val, duracion_val, genero_val, calif_promedio_val) {}

void Serie::agregarEpisodio(const Episodio& epi) {
    episodios.push_back(epi);
}

const std::vector<Episodio>& Serie::getEpisodios() const {
    return episodios;
}

void Serie::imprimir() const {
    std::cout << "Serie ID: " << id << ", Nombre: " << nombre
              << ", Duracion Total: " << duracion << " min, Genero: " << genero
              << ", Calificacion Promedio: " << calif_promedio << std::endl;
    std::cout << "  Episodios:" << std::endl;
    for (const auto& epi : episodios) {
        epi.imprimir();
    }
}
