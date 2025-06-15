#include <iostream>
#include <vector>
#include "Pelicula.h"
#include "Serie.h"
#include "Episodio.h"

// Función para inicializar y llenar los objetos de películas y series
void inicializarContenido(std::vector<Pelicula>& peliculas, std::vector<Serie>& series) {
    // --- Llenar 3 Películas ---
    peliculas.emplace_back(101, "Interestelar", 169, "Ciencia Ficcion", 5);
    peliculas.emplace_back(102, "El Origen", 148, "Accion", 4);
    peliculas.emplace_back(103, "Parásitos", 132, "Drama", 5);

    // --- Llenar 2 Series (cada una con 5 episodios) ---

    // Serie 1: Stranger Things
    Serie strangerThings(201, "Stranger Things", 500, "Ciencia Ficcion", 5);
    strangerThings.agregarEpisodio(Episodio(1, "Capitulo Uno: La Desaparicion de Will Byers", 1, 4));
    strangerThings.agregarEpisodio(Episodio(2, "Capitulo Dos: La Loca de Maple Street", 1, 5));
    strangerThings.agregarEpisodio(Episodio(3, "Capitulo Tres: Holly, Jolly", 1, 4));
    strangerThings.agregarEpisodio(Episodio(4, "Capitulo Cuatro: El Cuerpo", 1, 5));
    strangerThings.agregarEpisodio(Episodio(5, "Capitulo Cinco: La Pulga y el Acrobata", 1, 5));
    series.push_back(strangerThings);

    // Serie 2: The Mandalorian
    Serie mandalorian(202, "The Mandalorian", 400, "Ciencia Ficcion", 5);
    mandalorian.agregarEpisodio(Episodio(1, "Capitulo 1: El Mandaloriano", 1, 5));
    mandalorian.agregarEpisodio(Episodio(2, "Capitulo 2: El Niño", 1, 5));
    mandalorian.agregarEpisodio(Episodio(3, "Capitulo 3: El Pecado", 1, 4));
    mandalorian.agregarEpisodio(Episodio(4, "Capitulo 4: El Santuario", 1, 4));
    mandalorian.agregarEpisodio(Episodio(5, "Capitulo 5: El Pistolero", 1, 5));
    series.push_back(mandalorian);
}

int main() {
    std::vector<Pelicula> peliculas;
    std::vector<Serie> series;

    // Llama a la función para inicializar el contenido
    inicializarContenido(peliculas, series);

    std::cout << "--- Peliculas ---" << std::endl;
    for (const auto& peli : peliculas) {
        peli.imprimir();
    }
    std::cout << std::endl;

    std::cout << "--- Series ---" << std::endl;
    for (const auto& serie : series) {
        serie.imprimir();
        std::cout << std::endl;
    }

    return 0;
}
