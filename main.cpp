#include <iostream>
#include <vector>
#include <fstream>   // Para operaciones de archivo
#include <sstream>   // Para std::stringstream
#include <limits>    // Para std::numeric_limits
#include "Pelicula.h"
#include "Serie.h"
#include "Episodio.h"

// ... (other helper functions and inicializarContenido remain the same) ...

// Función auxiliar para leer un segmento de stringstream y convertirlo a int de forma segura
int getIntFromSsSafe(std::stringstream& ss, char delimiter, const std::string& line_context, const std::string& field_name) {
    std::string segment;
    if (!std::getline(ss, segment, delimiter)) {
        // This case handles situations where getline fails (e.g., unexpected end of line/stream)
        throw std::runtime_error("Error de formato: Falta campo '" + field_name + "' en la línea: " + line_context);
    }
    try {
        return std::stoi(segment);
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Error de conversion: Campo '" + field_name + "' no es un numero valido ('" + segment + "') en la línea: " + line_context);
    } catch (const std::out_of_range& e) {
        throw std::out_of_range("Error de rango: Numero demasiado grande/pequeño para el campo '" + field_name + "' ('" + segment + "') en la línea: " + line_context);
    }
}

// Función auxiliar para leer un segmento de stringstream y convertirlo a string (sin cambios)
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
    int line_num = 0; // Para referencia en mensajes de error
    while (std::getline(archivo, linea)) {
        line_num++;
        if (linea.empty()) continue; // Saltar líneas vacías

        std::stringstream ss(linea);
        std::string tipo_video_str;
        std::getline(ss, tipo_video_str, ','); // Leer el tipo de video

        try { // Try block to catch errors for this specific line
            if (tipo_video_str == "Pelicula") {
                int id = getIntFromSsSafe(ss, ',', linea, "ID Pelicula");
                std::string nombre = getStringFromSs(ss, ',');
                int duracion = getIntFromSsSafe(ss, ',', linea, "Duracion Pelicula");
                std::string genero = getStringFromSs(ss, ',');
                int calif_promedio = getIntFromSsSafe(ss, '\n', linea, "Calificacion Promedio Pelicula");

                peliculas.emplace_back(id, nombre, duracion, genero, calif_promedio);
            } else if (tipo_video_str == "Serie") {
                int id = getIntFromSsSafe(ss, ',', linea, "ID Serie");
                std::string nombre = getStringFromSs(ss, ',');
                int duracion = getIntFromSsSafe(ss, ',', linea, "Duracion Serie");
                std::string genero = getStringFromSs(ss, ',');
                int calif_promedio = getIntFromSsSafe(ss, ',', linea, "Calificacion Promedio Serie");

                int num_episodios = getIntFromSsSafe(ss, ',', linea, "Numero Episodios");

                Serie nuevaSerie(id, nombre, duracion, genero, calif_promedio);

                for (int i = 0; i < num_episodios; ++i) {
                    int epi_id = getIntFromSsSafe(ss, ',', linea, "ID Episodio");
                    std::string epi_titulo = getStringFromSs(ss, ',');
                    int epi_temporada = getIntFromSsSafe(ss, ',', linea, "Temporada Episodio");
                    int epi_calif_prom;
                    if (i == num_episodios - 1) {
                        epi_calif_prom = getIntFromSsSafe(ss, '\n', linea, "Calificacion Promedio Episodio");
                    } else {
                        epi_calif_prom = getIntFromSsSafe(ss, ',', linea, "Calificacion Promedio Episodio");
                    }

                    nuevaSerie.agregarEpisodio(Episodio(epi_id, epi_titulo, epi_temporada, epi_calif_prom));
                }
                series.push_back(nuevaSerie);
            } else {
                std::cerr << "Advertencia (linea " << line_num << "): Tipo de video desconocido o formato incorrecto en la linea: " << linea << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al procesar linea " << line_num << ": " << e.what() << std::endl;
            // Optionally, you could choose to continue to the next line or stop loading.
            // For now, it just logs the error and continues.
        }
    }

    archivo.close();
    std::cout << "Informacion cargada exitosamente desde " << nombre_archivo << std::endl;
    return true;
}

// ... (main function remains the same) ...

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
