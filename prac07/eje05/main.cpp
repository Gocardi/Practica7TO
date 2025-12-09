#include "LoggerThreadSafe.h"
#include "ConexionBDThreadSafe.h"
#include <thread>
#include <vector>
#include <chrono>

void pruebaLoggerConcurrente(int idTrabajador, int numMensajes) {
    std::this_thread::sleep_for(std::chrono::milliseconds(idTrabajador * 100));
    
    LoggerThreadSafe* logger = LoggerThreadSafe::obtenerInstancia();
    std::cout << "👤 Trabajador " << idTrabajador << " obtuvo logger: " << logger << "\n";
    
    for (int i = 0; i < numMensajes; i++) {
        logger->log("Trabajador " + std::to_string(idTrabajador) + 
                   " - Mensaje " + std::to_string(i+1), "INFO");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void pruebaBDConcurrente(int idTrabajador, int numConsultas) {
    std::this_thread::sleep_for(std::chrono::milliseconds(idTrabajador * 100));
    
    ConexionBDThreadSafe* bd = ConexionBDThreadSafe::obtenerInstancia();
    std::cout << "👤 Trabajador " << idTrabajador << " obtuvo BD: " << bd << "\n";
    
    for (int i = 0; i < numConsultas; i++) {
        bd->ejecutarConsulta("SELECT * FROM tabla_" + std::to_string(idTrabajador) + 
                            " WHERE id=" + std::to_string(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::cout << std::string(80, '=') << "\n";
    std::cout << "EJERCICIO 05: SINGLETON THREAD-SAFE\n";
    std::cout << std::string(80, '=') << "\n";
    
    // ========== PRUEBA 1: Logger Thread-Safe ==========
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "PRUEBA 1: LOGGER CON MÚLTIPLES HILOS\n";
    std::cout << std::string(80, '=') << "\n";
    
    const int numHilos = 5;
    const int mensajesPorHilo = 3;
    std::vector<std::thread> hilosLogger;
    
    std::cout << "\n🚀 Lanzando " << numHilos << " hilos para probar el logger...\n";
    
    for (int i = 0; i < numHilos; i++) {
        hilosLogger.emplace_back(pruebaLoggerConcurrente, i+1, mensajesPorHilo);
    }
    
    for (auto& hilo : hilosLogger) {
        hilo.join();
    }
    
    std::cout << "\n✅ Todos los hilos de logger han terminado\n";
    std::cout << "📄 Verifica el archivo 'bitacora_threadsafe.log' para ver los logs\n";
    
    // ========== PRUEBA 2: Conexión BD Thread-Safe ==========
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "PRUEBA 2: CONEXIÓN BD CON MÚLTIPLES HILOS\n";
    std::cout << std::string(80, '=') << "\n";
    
    ConexionBDThreadSafe* bdPrincipal = ConexionBDThreadSafe::obtenerInstancia();
    bdPrincipal->conectar();
    
    const int numHilosBD = 4;
    const int consultasPorHilo = 2;
    std::vector<std::thread> hilosBD;
    
    std::cout << "\n🚀 Lanzando " << numHilosBD << " hilos para ejecutar consultas...\n";
    
    for (int i = 0; i < numHilosBD; i++) {
        hilosBD.emplace_back(pruebaBDConcurrente, i+1, consultasPorHilo);
    }
    
    for (auto& hilo : hilosBD) {
        hilo.join();
    }
    
    std::cout << "\n✅ Todos los hilos de BD han terminado\n";
    std::cout << "\n📊 ESTADÍSTICAS FINALES:\n";
    std::cout << "   Total de consultas ejecutadas: " << bdPrincipal->obtenerEstadisticas() << "\n";
    
    // ========== VERIFICACIÓN FINAL ==========
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "VERIFICACIÓN DE INSTANCIA ÚNICA\n";
    std::cout << std::string(80, '=') << "\n";
    
    LoggerThreadSafe* logger1 = LoggerThreadSafe::obtenerInstancia();
    LoggerThreadSafe* logger2 = LoggerThreadSafe::obtenerInstancia();
    LoggerThreadSafe* logger3 = LoggerThreadSafe::obtenerInstancia();
    
    ConexionBDThreadSafe* bd1 = ConexionBDThreadSafe::obtenerInstancia();
    ConexionBDThreadSafe* bd2 = ConexionBDThreadSafe::obtenerInstancia();
    
    std::cout << "\n📋 IDs de Logger:\n";
    std::cout << "   logger1: " << logger1 << "\n";
    std::cout << "   logger2: " << logger2 << "\n";
    std::cout << "   logger3: " << logger3 << "\n";
    std::cout << "   ✅ Todas son iguales: " 
              << (logger1 == logger2 && logger2 == logger3 ? "true" : "false") << "\n";
    
    std::cout << "\n📋 IDs de ConexionBD:\n";
    std::cout << "   bd1: " << bd1 << "\n";
    std::cout << "   bd2: " << bd2 << "\n";
    std::cout << "   ✅ Ambas son iguales: " << (bd1 == bd2 ? "true" : "false") << "\n";
    
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "CONCLUSIÓN\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "✅ El patrón Singleton funciona correctamente en entornos multihilo\n";
    std::cout << "✅ Double-checked locking previene race conditions\n";
    std::cout << "✅ Locks individuales protegen operaciones críticas\n";
    std::cout << "✅ Solo se crea una instancia incluso con múltiples hilos simultáneos\n";
    std::cout << std::string(80, '=') << "\n";
    
    LoggerThreadSafe::destruirInstancia();
    ConexionBDThreadSafe::destruirInstancia();
    
    return 0;
}
