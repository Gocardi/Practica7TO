#include "Logger.h"
#include <iostream>

// Simulación de módulos del sistema
class ModuloUsuarios {
private:
    Logger* logger;
public:
    ModuloUsuarios() : logger(Logger::obtenerInstancia()) {}
    
    void crearUsuario(const std::string& nombre) {
        logger->info("ModuloUsuarios: Creando usuario '" + nombre + "'");
        logger->debug("ModuloUsuarios: Validando datos del usuario '" + nombre + "'");
        logger->info("ModuloUsuarios: Usuario '" + nombre + "' creado exitosamente");
    }
};

class ModuloAutenticacion {
private:
    Logger* logger;
public:
    ModuloAutenticacion() : logger(Logger::obtenerInstancia()) {}
    
    void login(const std::string& usuario) {
        logger->info("ModuloAutenticacion: Intento de login del usuario '" + usuario + "'");
        if (usuario == "admin") {
            logger->info("ModuloAutenticacion: Login exitoso para '" + usuario + "'");
        } else {
            logger->warning("ModuloAutenticacion: Credenciales inválidas para '" + usuario + "'");
        }
    }
};

class ModuloBaseDatos {
private:
    Logger* logger;
public:
    ModuloBaseDatos() : logger(Logger::obtenerInstancia()) {}
    
    void conectar() {
        logger->info("ModuloBaseDatos: Iniciando conexión a la base de datos");
        logger->debug("ModuloBaseDatos: Verificando credenciales...");
        logger->info("ModuloBaseDatos: Conexión establecida exitosamente");
    }
    
    void consultar(const std::string& query) {
        logger->debug("ModuloBaseDatos: Ejecutando query: " + query);
        logger->error("ModuloBaseDatos: Error de sintaxis en la query");
    }
};

int main() {
    std::cout << std::string(80, '=') << "\n";
    std::cout << "EJERCICIO 02: LOGGER CON SINGLETON\n";
    std::cout << std::string(80, '=') << "\n\n";
    
    // Crear instancias del logger
    Logger* logger1 = Logger::obtenerInstancia();
    Logger* logger2 = Logger::obtenerInstancia();
    Logger* logger3 = Logger::obtenerInstancia();
    
    std::cout << "logger1 dirección: " << logger1 << "\n";
    std::cout << "logger2 dirección: " << logger2 << "\n";
    std::cout << "logger3 dirección: " << logger3 << "\n";
    std::cout << "Todas las instancias son iguales: " 
              << (logger1 == logger2 && logger2 == logger3 ? "true" : "false") << "\n\n";
    
    std::cout << std::string(80, '=') << "\n";
    std::cout << "REGISTRANDO EVENTOS DESDE DIFERENTES MÓDULOS\n";
    std::cout << std::string(80, '=') << "\n\n";
    
    // Simular uso desde diferentes módulos
    ModuloUsuarios moduloUsuarios;
    moduloUsuarios.crearUsuario("Juan Pérez");
    
    std::cout << "\n";
    ModuloAutenticacion moduloAuth;
    moduloAuth.login("admin");
    moduloAuth.login("juan");
    
    std::cout << "\n";
    ModuloBaseDatos moduloBD;
    moduloBD.conectar();
    moduloBD.consultar("SELECT * FROM usuarios WHERE id = 1");
    
    std::cout << "\n";
    Logger* loggerDirecto = Logger::obtenerInstancia();
    loggerDirecto->info("Mensaje directo desde el main");
    loggerDirecto->warning("Esta es una advertencia importante");
    loggerDirecto->error("Se ha detectado un error crítico");
    
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "VERIFICACIÓN: Todos los módulos usan el mismo archivo de log\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "Archivo de log: bitacora.log\n";
    std::cout << "Verifica el contenido del archivo para confirmar.\n";
    
    Logger::destruirInstancia();
    return 0;
}
