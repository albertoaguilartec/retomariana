#include "Video.h"
#include <iostream> // Aunque no se usa directamente en este .cpp, es buena práctica para Video base

Video::Video(int id_val, const std::string& nombre_val, int duracion_val,
             const std::string& genero_val, int calif_promedio_val)
    : id(id_val), nombre(nombre_val), duracion(duracion_val), genero(genero_val),
      calif_promedio(calif_promedio_val) {}

void Video::setId(int id_val) {
    id = id_val;
}

void Video::setNombre(const std::string& nombre_val) {
    nombre = nombre_val;
}

void Video::setDuracion(int duracion_val) {
    duracion = duracion_val;
}

void Video::setGenero(const std::string& genero_val) {
    genero = genero_val;
}

void Video::setCalifPromedio(int calif_promedio_val) {
    calif_promedio = calif_promedio_val;
}

int Video::getId() const {
    return id;
}

std::string Video::getNombre() const {
    return nombre;
}

int Video::getDuracion() const {
    return duracion;
}

std::string Video::getGenero() const {
    return genero;
}

int Video::getCalifPromedio() const {
    return calif_promedio;
}
