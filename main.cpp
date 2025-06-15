#include <iostream>
#include <vector>
#include "Pelicula.h"
#include "Serie.h"
#include "Episodio.h" // Incluir Episodio también si se van a crear directamente en main

int main() {
    // --- Llenar 3 Películas ---
    std::vector<Pelicula> peliculas;

    // Pelicula 1
    peliculas.emplace_back(101, "Interestelar", 169, "Ciencia Ficcion", 9);

    // Pelicula 2
    peliculas.emplace_back(102, "El Origen", 148, "Accion", 8);

    // Pelicula 3
    peliculas.emplace_back(103, "Parásitos", 132, "Drama", 9);

    std::cout << "--- Peliculas ---" << std::endl;
    for (const auto& peli : peliculas) {
        peli.imprimir();
    }
    std::cout << std::endl;

    // --- Llenar 2 Series (cada una con 5 episodios) ---
    std::vector<Serie> series;

    // Serie 1: Stranger Things
    Serie strangerThings(201, "Stranger Things", 500, "Ciencia Ficcion", 9);
    strangerThings.agregarEpisodio(Episodio(1, "Capitulo Uno: La Desaparicion de Will Byers", 1, 8));
    strangerThings.agregarEpisodio(Episodio(2, "Capitulo Dos: La Loca de Maple Street", 1, 9));
    strangerThings.agregarEpisodio(Episodio(3, "Capitulo Tres: Holly, Jolly", 1, 8));
    strangerThings.agregarEpisodio(Episodio(4, "Capitulo Cuatro: El Cuerpo", 1, 9));
    strangerThings.agregarEpisodio(Episodio(5, "Capitulo Cinco: La Pulga y el Acrobata", 1, 9));
    series.push_back(strangerThings);

    // Serie 2: The Mandalorian
    Serie mandalorian(202, "The Mandalorian", 400, "Ciencia Ficcion", 9);
    mandalorian.agregarEpisodio(Episodio(1, "Capitulo 1: El Mandaloriano", 1, 9));
    mandalorian.agregarEpisodio(Episodio(2, "Capitulo 2: El Niño", 1, 9));
    mandalorian.agregarEpisodio(Episodio(3, "Capitulo 3: El Pecado", 1, 8));
    mandalorian.agregarEpisodio(Episodio(4, "Capitulo 4: El Santuario", 1, 8));
    mandalorian.agregarEpisodio(Episodio(5, "Capitulo 5: El Pistolero", 1, 9));
    series.push_back(mandalorian);

    std::cout << "--- Series ---" << std::endl;
    for (const auto& serie : series) {
        serie.imprimir();
        std::cout << std::endl;
    }

    return 0;
}
