#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

class Logger {
private:
    static Logger* instancia;
    std::string archivoLog;
    
    Logger() : archivoLog("bitacora.log") {
        std::ofstream archivo(archivoLog, std::ios::app);
        if (archivo.is_open()) {
            archivo << "\n" << std::string(80, '=') << "\n";
            archivo << "NUEVA SESIÓN DE LOG - " << obtenerTimestamp() << "\n";
            archivo << std::string(80, '=') << "\n";
            archivo.close();
        }
    }
    
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    std::string obtenerTimestamp() const {
        time_t ahora = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&ahora);
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
        return buf;
    }

public:
    static Logger* obtenerInstancia() {
        if (instancia == nullptr) {
            instancia = new Logger();
        }
        return instancia;
    }
    
    void log(const std::string& mensaje, const std::string& nivel = "INFO") {
        std::string timestamp = obtenerTimestamp();
        std::stringstream lineaLog;
        lineaLog << "[" << timestamp << "] [" << nivel << "] " << mensaje;
        
        std::ofstream archivo(archivoLog, std::ios::app);
        if (archivo.is_open()) {
            archivo << lineaLog.str() << "\n";
            archivo.close();
        }
        
        std::cout << lineaLog.str() << "\n";
    }
    
    void info(const std::string& mensaje) {
        log(mensaje, "INFO");
    }
    
    void warning(const std::string& mensaje) {
        log(mensaje, "WARNING");
    }
    
    void error(const std::string& mensaje) {
        log(mensaje, "ERROR");
    }
    
    void debug(const std::string& mensaje) {
        log(mensaje, "DEBUG");
    }
    
    static void destruirInstancia() {
        if (instancia != nullptr) {
            delete instancia;
            instancia = nullptr;
        }
    }
};

Logger* Logger::instancia = nullptr;

#endif
