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
    /* Está comentado porque el archivo ya está generado, ahora se puede editar el archivo contenido_video.txt
    inicializarContenido(peliculas, series);
    std::cout << "--- Contenido Inicial ---" << std::endl;
    std::cout << "Peliculas generadas: " << peliculas.size() << std::endl;
    std::cout << "Series generadas: " << series.size() << std::endl;
    guardarInformacion(nombre_archivo, peliculas, series);
    std::cout << std::endl;
    */


    int opcion = 1;
    while (opcion != 0) {
        std::cout << "\n--- Menu Principal ---" << std::endl;
        std::cout << "1. Cargar archivo de datos" << std::endl;
        std::cout << "2. Mostrar los videos en general con una cierta calificacion o de un cierto genero" << std::endl;
        std::cout << "3. Mostrar los episodios de una determinada serie con una calificacion determinada" << std::endl;
        std::cout << "4. Mostrar las peliculas con cierta calificacion" << std::endl;
        std::cout << "5. Calificar un video" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout <<"ingresa opcion:"<< std::endl;
        std::cin >> opcion;

        if (opcion == 1) {
            /* INICIA CARGAR Y MOSTRAR INFORMACION */
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
            /* TERMINA CARGAR Y MOSTRAR INFORMACION */
        }
        if (opcion == 2) {
            int filtro =0;
            std::cout<<"quieres filtrar Calificación (1) o un género (2)?"<<std::endl;
            std::cin >> filtro;
            if (filtro == 1) {
                int calificacion = 0;
                std::cout<<"dame la calif entre 1-5: "<<std::endl;
                std::cin >> calificacion;
                // Limpiar los vectores para asegurar que se carga desde cero
                peliculas.clear();
                series.clear();

                if (cargarInformacion(nombre_archivo, peliculas, series)) {
                    std::cout << "\n--- Peliculas con calificacion ---"<< calificacion << std::endl;
                    for (const auto& peli : peliculas) {
                        if (peli.getCalifPromedio()==calificacion) {
                            peli.imprimir();
                        }
                    }
                    std::cout << std::endl;

                    std::cout << "--- Series con calificacion---" << calificacion<< std::endl;
                    for (const auto& serie : series) {
                        if (serie.getCalifPromedio()==calificacion) {
                            serie.imprimir();
                        }
                        std::cout << std::endl;
                    }
                } else {
                    std::cerr << "No se pudo cargar la informacion." << std::endl;
                }

            }
            if (filtro == 2) {
                std::string genero;
                std::cout<<"dame el genero (Drama, Accion, CienciaFiccion) escribir tal cual: "<<std::endl;
                std::cin >> genero;
                peliculas.clear();
                series.clear();

                if (cargarInformacion(nombre_archivo, peliculas, series)) {
                    std::cout << "\n--- Peliculas con genero ---"<< genero << std::endl;
                    for (const auto& peli : peliculas) {
                        if (peli.getGenero()==genero) {
                            peli.imprimir();
                        }
                    }
                    std::cout << std::endl;

                    std::cout << "--- Series con genero---" << genero<< std::endl;
                    for (const auto& serie : series) {
                        if (serie.getGenero()==genero) {
                            serie.imprimir();
                        }
                        std::cout << std::endl;
                    }
                } else {
                    std::cerr << "No se pudo cargar la informacion." << std::endl;
                }
            }

        }
        if (opcion == 3) {
            int calificacion = 0;
            std::cout<<"Dame la cali de la serie 1-5: "<<std::endl;
            std::cin >> calificacion;

            peliculas.clear();
            series.clear();

            if (cargarInformacion(nombre_archivo, peliculas, series)) {

                std::cout << "--- Series con calificacion---" << calificacion<< std::endl;
                for (const auto& serie : series) {
                    if (serie.getCalifPromedio()==calificacion) {
                        serie.imprimir();
                    }
                    std::cout << std::endl;
                }
            } else {
                std::cerr << "No se pudo cargar la informacion." << std::endl;
            }
        }


    }



    return 0;
}
