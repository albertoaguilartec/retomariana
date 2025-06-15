#include <iostream>
#include <vector>
#include <fstream>   // Para operaciones de archivo
#include <sstream>   // Para std::stringstream
#include <limits>    // Para std::numeric_limits
#include "Pelicula.h"
#include "Serie.h"
#include "Episodio.h"

// Función para guardar la información en un archivo de texto plano
bool guardarInformacion(const std::string& nombre_archivo,
                        const std::vector<Pelicula>& peliculas,
                        const std::vector<Serie>& series) {
    std::ofstream archivo(nombre_archivo); // Abre el archivo para escritura

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar." << std::endl;
        return false;
    }

    // Escribir películas
    for (const auto& peli : peliculas) {
        archivo << "Pelicula," << peli.getId() << "," << peli.getNombre() << ","
                << peli.getDuracion() << "," << peli.getGenero() << ","
                << peli.getCalifPromedio() << std::endl;
    }

    // Escribir series
    for (const auto& serie : series) {
        archivo << "Serie," << serie.getId() << "," << serie.getNombre() << ","
                << serie.getDuracion() << "," << serie.getGenero() << ","
                << serie.getCalifPromedio();

        archivo << "," << serie.getEpisodios().size(); // Número de episodios

        for (const auto& epi : serie.getEpisodios()) {
            archivo << "," << epi.getId() << "," << epi.getTitulo() << ","
                    << epi.getTemporada() << "," << epi.getCalifProm();
        }
        archivo << std::endl;
    }

    archivo.close();
    std::cout << "Informacion guardada exitosamente en " << nombre_archivo << std::endl;
    return true;
}

// Función auxiliar para leer un segmento de stringstream y convertirlo a int
int getIntFromSs(std::stringstream& ss, char delimiter) {
    std::string segment;
    std::getline(ss, segment, delimiter);
    return std::stoi(segment);
}

// Función auxiliar para leer un segmento de stringstream y convertirlo a string
std::string getStringFromSs(std::stringstream& ss, char delimiter) {
    std::string segment;
    std::getline(ss, segment, delimiter);
    return segment;
}


// Función para cargar la información desde un archivo de texto plano
bool cargarInformacion(const std::string& nombre_archivo,
                       std::vector<Pelicula>& peliculas,
                       std::vector<Serie>& series) {
    std::ifstream archivo(nombre_archivo); // Abre el archivo para lectura

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para cargar." << std::endl;
        return false;
    }

    // Limpiar vectores existentes antes de cargar nueva información
    peliculas.clear();
    series.clear();

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue; // Saltar líneas vacías

        std::stringstream ss(linea);
        std::string tipo_video_str;
        std::getline(ss, tipo_video_str, ','); // Leer el tipo de video

        if (tipo_video_str == "Pelicula") {
            int id = getIntFromSs(ss, ',');
            std::string nombre = getStringFromSs(ss, ',');
            int duracion = getIntFromSs(ss, ',');
            std::string genero = getStringFromSs(ss, ',');
            int calif_promedio = getIntFromSs(ss, '\n'); // Último campo, usa '\n' como delimitador o no hay delimitador

            peliculas.emplace_back(id, nombre, duracion, genero, calif_promedio);
        } else if (tipo_video_str == "Serie") {
            int id = getIntFromSs(ss, ',');
            std::string nombre = getStringFromSs(ss, ',');
            int duracion = getIntFromSs(ss, ',');
            std::string genero = getStringFromSs(ss, ',');
            int calif_promedio = getIntFromSs(ss, ',');

            int num_episodios = getIntFromSs(ss, ',');

            Serie nuevaSerie(id, nombre, duracion, genero, calif_promedio);

            for (int i = 0; i < num_episodios; ++i) {
                int epi_id = getIntFromSs(ss, ',');
                std::string epi_titulo = getStringFromSs(ss, ',');
                int epi_temporada = getIntFromSs(ss, ',');
                // Si es el último episodio o el último campo del episodio, el delimitador podría ser '\n'
                int epi_calif_prom;
                if (i == num_episodios - 1) {
                    epi_calif_prom = getIntFromSs(ss, '\n'); // Último campo de la línea
                } else {
                    epi_calif_prom = getIntFromSs(ss, ',');
                }

                nuevaSerie.agregarEpisodio(Episodio(epi_id, epi_titulo, epi_temporada, epi_calif_prom));
            }
            series.push_back(nuevaSerie);
        } else {
            std::cerr << "Advertencia: Tipo de video desconocido o formato incorrecto en la linea: " << linea << std::endl;
        }
    }

    archivo.close();
    std::cout << "Informacion cargada exitosamente desde " << nombre_archivo << std::endl;
    return true;
}


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
    const std::string nombre_archivo = "contenido_video.txt";

    // --- Guardar información inicial ---
    inicializarContenido(peliculas, series);
    std::cout << "--- Contenido Inicial ---" << std::endl;
    std::cout << "Peliculas generadas: " << peliculas.size() << std::endl;
    std::cout << "Series generadas: " << series.size() << std::endl;
    guardarInformacion(nombre_archivo, peliculas, series);
    std::cout << std::endl;

    // --- Cargar información y mostrar ---
    std::cout << "--- Cargando Contenido desde Archivo ---" << std::endl;
    // Limpiar los vectores para asegurar que se carga desde cero
    peliculas.clear();
    series.clear();

    if (cargarInformacion(nombre_archivo, peliculas, series)) {
        std::cout << "\n--- Peliculas Cargadas ---" << std::endl;
        for (const auto& peli : peliculas) {
            peli.imprimir();
        }
        std::cout << std::endl;

        std::cout << "--- Series Cargadas ---" << std::endl;
        for (const auto& serie : series) {
            serie.imprimir();
            std::cout << std::endl;
        }
    } else {
        std::cerr << "No se pudo cargar la informacion." << std::endl;
    }

    return 0;
}
