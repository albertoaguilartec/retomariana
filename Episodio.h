#ifndef EPISODIO_H
#define EPISODIO_H

#include <string>

class Episodio {
private:
    int id;
    std::string titulo;
    int temporada;
    int calif_prom;

public:
    // Constructor
    Episodio(int id_val = 0, const std::string& titulo_val = "", int temporada_val = 0, int calif_prom_val = 0);

    // Setters
    void setId(int id_val);
    void setTitulo(const std::string& titulo_val);
    void setTemporada(int temporada_val);
    void setCalifProm(int calif_prom_val);

    // Getters
    int getId() const;
    std::string getTitulo() const;
    int getTemporada() const;
    int getCalifProm() const;

    // Método para imprimir la información del episodio
    void imprimir() const;
};

#endif // EPISODIO_H
