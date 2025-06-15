#ifndef VIDEO_H
#define VIDEO_H

#include <string>

class Video {
protected:
    int id;
    std::string nombre;
    int duracion;
    std::string genero;
    int calif_promedio;

public:
    // Constructor
    Video(int id_val = 0, const std::string& nombre_val = "", int duracion_val = 0,
          const std::string& genero_val = "", int calif_promedio_val = 0);

    // Setters
    void setId(int id_val);
    void setNombre(const std::string& nombre_val);
    void setDuracion(int duracion_val);
    void setGenero(const std::string& genero_val);
    void setCalifPromedio(int calif_promedio_val);

    // Getters
    int getId() const;
    std::string getNombre() const;
    int getDuracion() const;
    std::string getGenero() const;
    int getCalifPromedio() const;

    // Método virtual puro para imprimir (hace a Video abstracta)
    virtual void imprimir() const = 0;
};

#endif // VIDEO_H
