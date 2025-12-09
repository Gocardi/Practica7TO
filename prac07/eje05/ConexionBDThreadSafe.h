#ifndef CONEXIONBDTHREADSAFE_H
#define CONEXIONBDTHREADSAFE_H

#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

class ConexionBDThreadSafe {
private:
    static ConexionBDThreadSafe* instancia;
    static std::mutex mutexInstancia;
    std::mutex mutexConexion;
    std::mutex mutexContador;
    
    bool conectado;
    int consultasEjecutadas;
    bool inicializado;
    
    ConexionBDThreadSafe() : conectado(false), consultasEjecutadas(0), 
                             inicializado(false) {}
    
    ConexionBDThreadSafe(const ConexionBDThreadSafe&) = delete;
    ConexionBDThreadSafe& operator=(const ConexionBDThreadSafe&) = delete;

public:
    static ConexionBDThreadSafe* obtenerInstancia() {
        // Double-checked locking
        if (instancia == nullptr) {
            std::lock_guard<std::mutex> lock(mutexInstancia);
            if (instancia == nullptr) {
                std::cout << "🔧 Creando nueva instancia de ConexionBDThreadSafe...\n";
                instancia = new ConexionBDThreadSafe();
                instancia->inicializado = true;
                std::cout << "✅ Instancia de ConexionBDThreadSafe inicializada\n";
            }
        }
        return instancia;
    }
    
    bool conectar() {
        std::lock_guard<std::mutex> lock(mutexConexion);
        if (conectado) {
            std::cout << "⚠️  La conexión ya está activa\n";
            return false;
        }
        
        std::cout << "🔌 Estableciendo conexión...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        conectado = true;
        std::cout << "✅ Conexión establecida\n";
        return true;
    }
    
    std::string ejecutarConsulta(const std::string& consulta) {
        if (!conectado) {
            std::cout << "❌ No hay conexión activa\n";
            return "";
        }
        
        std::cout << "📊 Ejecutando: " << consulta << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        // Incrementar contador de forma thread-safe
        int numConsulta;
        {
            std::lock_guard<std::mutex> lock(mutexContador);
            consultasEjecutadas++;
            numConsulta = consultasEjecutadas;
        }
        
        std::cout << "✅ Consulta #" << numConsulta << " completada\n";
        return "Resultado #" + std::to_string(numConsulta);
    }
    
    int obtenerEstadisticas() {
        std::lock_guard<std::mutex> lock(mutexContador);
        return consultasEjecutadas;
    }
    
    static void destruirInstancia() {
        std::lock_guard<std::mutex> lock(mutexInstancia);
        if (instancia != nullptr) {
            delete instancia;
            instancia = nullptr;
        }
    }
};

ConexionBDThreadSafe* ConexionBDThreadSafe::instancia = nullptr;
std::mutex ConexionBDThreadSafe::mutexInstancia;

#endif
