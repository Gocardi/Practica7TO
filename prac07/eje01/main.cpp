#include "Configuracion.h"
#include <iostream>

int main() {
    std::cout << "==================================================\n";
    std::cout << "EJERCICIO 01: SINGLETON BÁSICO - CONFIGURACIÓN\n";
    std::cout << "==================================================\n\n";
    
    // Crear primera referencia
    Configuracion* config1 = Configuracion::obtenerInstancia();
    std::cout << "config1 dirección: " << config1 << "\n";
    config1->mostrarConfiguracion();
    
    std::cout << "\n--- Modificando configuración desde config1 ---\n";
    config1->setIdioma("Inglés");
    config1->setZonaHoraria("UTC+0");
    
    // Crear segunda referencia
    Configuracion* config2 = Configuracion::obtenerInstancia();
    std::cout << "\nconfig2 dirección: " << config2 << "\n";
    config2->mostrarConfiguracion();
    
    // Crear tercera referencia
    Configuracion* config3 = Configuracion::obtenerInstancia();
    std::cout << "\nconfig3 dirección: " << config3 << "\n";
    
    // Verificar que todas son la misma instancia
    std::cout << "\n--- Verificación de instancia única ---\n";
    std::cout << "config1 == config2: " << (config1 == config2 ? "true" : "false") << "\n";
    std::cout << "config2 == config3: " << (config2 == config3 ? "true" : "false") << "\n";
    std::cout << "config1 == config3: " << (config1 == config3 ? "true" : "false") << "\n";
    
    // Modificar desde config3
    std::cout << "\n--- Modificando desde config3 ---\n";
    config3->setIdioma("Francés");
    config3->setZonaHoraria("UTC+1");
    
    std::cout << "\nVerificando config1:\n";
    config1->mostrarConfiguracion();
    
    // Limpiar
    Configuracion::destruirInstancia();
    
    return 0;
}
