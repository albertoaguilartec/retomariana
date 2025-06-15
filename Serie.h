#ifndef SERIE_H
#define SERIE_H

#include "Video.h"
#include "Episodio.h"
#include <vector>
#include <string>

class Serie : public Video {
private:
    std::vector<Episodio> episodios;

public:
    // Constructor
    Serie(int id_val = 0, const std::string& nombre_val = "", int duracion_val = 0,
          const std::string& genero_val = "", int calif_promedio_val = 0);

    // Setter para añadir un episodio
    void agregarEpisodio(const Episodio& epi);

    // Getter para obtener todos los episodios
    const std::vector<Episodio>& getEpisodios() const;

    // Implementación del método imprimir para Serie
    void imprimir() const override;
};

#endif // SERIE_H
