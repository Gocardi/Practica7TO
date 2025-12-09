#ifndef CONEXIONBD_H
#define CONEXIONBD_H

#include <string>
#include <iostream>
#include <thread>
#include <chrono>

class ConexionBD {
private:
    static ConexionBD* instancia;
    bool conectado;
    std::string host;
    int puerto;
    std::string baseDatos;
    std::string usuario;
    int consultasEjecutadas;
    
    ConexionBD() : conectado(false), host("localhost"), puerto(5432),
                   baseDatos("mi_aplicacion"), usuario("admin"), 
                   consultasEjecutadas(0) {}
    
    ConexionBD(const ConexionBD&) = delete;
    ConexionBD& operator=(const ConexionBD&) = delete;

public:
    static ConexionBD* obtenerInstancia() {
        if (instancia == nullptr) {
            std::cout << "🔧 Creando nueva instancia de ConexionBD...\n";
            instancia = new ConexionBD();
            std::cout << "✅ Instancia de ConexionBD inicializada\n";
        } else {
            std::cout << "♻️  Reutilizando instancia existente de ConexionBD...\n";
        }
        return instancia;
    }
    
    bool conectar() {
        if (conectado) {
            std::cout << "⚠️  Ya existe una conexión activa\n";
            return false;
        }
        
        std::cout << "\n🔌 Intentando conectar a la base de datos...\n";
        std::cout << "   Host: " << host << "\n";
        std::cout << "   Puerto: " << puerto << "\n";
        std::cout << "   Base de datos: " << baseDatos << "\n";
        std::cout << "   Usuario: " << usuario << "\n";
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        conectado = true;
        std::cout << "✅ Conexión establecida exitosamente\n";
        return true;
    }
    
    bool desconectar() {
        if (!conectado) {
            std::cout << "⚠️  No hay conexión activa para cerrar\n";
            return false;
        }
        
        std::cout << "\n🔌 Cerrando conexión a la base de datos...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        conectado = false;
        std::cout << "✅ Conexión cerrada exitosamente\n";
        std::cout << "   Consultas ejecutadas: " << consultasEjecutadas << "\n";
        return true;
    }
    
    bool estado() const {
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "ESTADO DE LA CONEXIÓN A BASE DE DATOS\n";
        std::cout << std::string(60, '=') << "\n";
        std::cout << "Estado: " << (conectado ? "🟢 CONECTADA" : "🔴 DESCONECTADA") << "\n";
        std::cout << "Host: " << host << ":" << puerto << "\n";
        std::cout << "Base de datos: " << baseDatos << "\n";
        std::cout << "Usuario: " << usuario << "\n";
        std::cout << "Consultas ejecutadas: " << consultasEjecutadas << "\n";
        std::cout << std::string(60, '=') << "\n";
        return conectado;
    }
    
    std::string ejecutarConsulta(const std::string& consulta) {
        if (!conectado) {
            std::cout << "❌ Error: No hay conexión activa. Debes conectar primero.\n";
            return "";
        }
        
        std::cout << "\n📊 Ejecutando consulta: " << consulta << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        consultasEjecutadas++;
        std::cout << "✅ Consulta ejecutada exitosamente (#" << consultasEjecutadas << ")\n";
        
        return "Resultado de la consulta #" + std::to_string(consultasEjecutadas);
    }
    
    bool configurar(const std::string& nuevoHost = "", int nuevoPuerto = 0,
                    const std::string& nuevaBD = "", const std::string& nuevoUsuario = "") {
        if (conectado) {
            std::cout << "❌ No se puede configurar mientras hay una conexión activa\n";
            return false;
        }
        
        if (!nuevoHost.empty()) host = nuevoHost;
        if (nuevoPuerto > 0) puerto = nuevoPuerto;
        if (!nuevaBD.empty()) baseDatos = nuevaBD;
        if (!nuevoUsuario.empty()) usuario = nuevoUsuario;
        
        std::cout << "✅ Configuración actualizada correctamente\n";
        return true;
    }
    
    static void destruirInstancia() {
        if (instancia != nullptr) {
            delete instancia;
            instancia = nullptr;
        }
    }
};

ConexionBD* ConexionBD::instancia = nullptr;

#endif
