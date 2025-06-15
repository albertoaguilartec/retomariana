#include "Episodio.h"
#include <iostream>

Episodio::Episodio(int id_val, const std::string& titulo_val, int temporada_val, int calif_prom_val)
    : id(id_val), titulo(titulo_val), temporada(temporada_val), calif_prom(calif_prom_val) {}

void Episodio::setId(int id_val) {
    id = id_val;
}

void Episodio::setTitulo(const std::string& titulo_val) {
    titulo = titulo_val;
}

void Episodio::setTemporada(int temporada_val) {
    temporada = temporada_val;
}

void Episodio::setCalifProm(int calif_prom_val) {
    calif_prom = calif_prom_val;
}

int Episodio::getId() const {
    return id;
}

std::string Episodio::getTitulo() const {
    return titulo;
}

int Episodio::getTemporada() const {
    return temporada;
}

int Episodio::getCalifProm() const {
    return calif_prom;
}

void Episodio::imprimir() const {
    std::cout << "  Episodio ID: " << id << ", Titulo: " << titulo
              << ", Temporada: " << temporada << ", Calificacion: " << calif_prom << std::endl;
}
