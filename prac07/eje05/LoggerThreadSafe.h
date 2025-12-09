#ifndef LOGGERTHREADSAFE_H
#define LOGGERTHREADSAFE_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <mutex>
#include <sstream>

class LoggerThreadSafe {
private:
    static LoggerThreadSafe* instancia;
    static std::mutex mutexInstancia;
    std::mutex mutexEscritura;
    std::string archivoLog;
    bool inicializado;
    
    LoggerThreadSafe() : archivoLog("bitacora_threadsafe.log"), inicializado(false) {}
    
    LoggerThreadSafe(const LoggerThreadSafe&) = delete;
    LoggerThreadSafe& operator=(const LoggerThreadSafe&) = delete;
    
    void inicializar() {
        if (!inicializado) {
            std::lock_guard<std::mutex> lock(mutexEscritura);
            if (!inicializado) {
                std::ofstream archivo(archivoLog, std::ios::app);
                if (archivo.is_open()) {
                    archivo << "\n" << std::string(80, '=') << "\n";
                    archivo << "NUEVA SESIÓN (THREAD-SAFE) - " << obtenerTimestamp() << "\n";
                    archivo << std::string(80, '=') << "\n";
                    archivo.close();
                }
                inicializado = true;
            }
        }
    }
    
    std::string obtenerTimestamp() const {
        time_t ahora = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&ahora);
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
        return buf;
    }

public:
    static LoggerThreadSafe* obtenerInstancia() {
        // Primera verificación sin lock (rápida)
        if (instancia == nullptr) {
            // Lock solo si necesitamos crear la instancia
            std::lock_guard<std::mutex> lock(mutexInstancia);
            // Segunda verificación con lock (segura)
            if (instancia == nullptr) {
                std::cout << "🔧 Creando nueva instancia de LoggerThreadSafe...\n";
                instancia = new LoggerThreadSafe();
                instancia->inicializar();
            }
        }
        return instancia;
    }
    
    void log(const std::string& mensaje, const std::string& nivel = "INFO") {
        std::string timestamp = obtenerTimestamp();
        std::stringstream lineaLog;
        lineaLog << "[" << timestamp << "] [" << nivel << "] " << mensaje;
        
        // Proteger la escritura con mutex
        std::lock_guard<std::mutex> lock(mutexEscritura);
        std::ofstream archivo(archivoLog, std::ios::app);
        if (archivo.is_open()) {
            archivo << lineaLog.str() << "\n";
            archivo.close();
        }
        std::cout << lineaLog.str() << "\n";
    }
    
    static void destruirInstancia() {
        std::lock_guard<std::mutex> lock(mutexInstancia);
        if (instancia != nullptr) {
            delete instancia;
            instancia = nullptr;
        }
    }
};

LoggerThreadSafe* LoggerThreadSafe::instancia = nullptr;
std::mutex LoggerThreadSafe::mutexInstancia;

#endif
