#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <string>
#include <iostream>

class Configuracion {
private:
    static Configuracion* instancia;
    std::string idioma;
    std::string zonaHoraria;
    
    // Constructor privado para evitar instanciación externa
    Configuracion() : idioma("Español"), zonaHoraria("UTC-6") {}
    
    // Evitar copia
    Configuracion(const Configuracion&) = delete;
    Configuracion& operator=(const Configuracion&) = delete;

public:
    static Configuracion* obtenerInstancia() {
        if (instancia == nullptr) {
            instancia = new Configuracion();
        }
        return instancia;
    }
    
    void setIdioma(const std::string& nuevoIdioma) {
        idioma = nuevoIdioma;
    }
    
    void setZonaHoraria(const std::string& nuevaZona) {
        zonaHoraria = nuevaZona;
    }
    
    std::string getIdioma() const {
        return idioma;
    }
    
    std::string getZonaHoraria() const {
        return zonaHoraria;
    }
    
    void mostrarConfiguracion() const {
        std::cout << "==================================================\n";
        std::cout << "CONFIGURACIÓN DEL SISTEMA\n";
        std::cout << "==================================================\n";
        std::cout << "Idioma: " << idioma << "\n";
        std::cout << "Zona Horaria: " << zonaHoraria << "\n";
        std::cout << "==================================================\n";
    }
    
    static void destruirInstancia() {
        if (instancia != nullptr) {
            delete instancia;
            instancia = nullptr;
        }
    }
};

// Inicialización del puntero estático
Configuracion* Configuracion::instancia = nullptr;

#endif
