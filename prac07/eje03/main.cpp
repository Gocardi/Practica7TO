#include "ConexionBD.h"
#include <iostream>

class RepositorioUsuarios {
private:
    ConexionBD* conexion;
public:
    RepositorioUsuarios() : conexion(ConexionBD::obtenerInstancia()) {}
    
    void obtenerUsuarios() {
        std::cout << "\n--- RepositorioUsuarios: Obteniendo usuarios ---\n";
        conexion->ejecutarConsulta("SELECT * FROM usuarios");
    }
};

class RepositorioProductos {
private:
    ConexionBD* conexion;
public:
    RepositorioProductos() : conexion(ConexionBD::obtenerInstancia()) {}
    
    void obtenerProductos() {
        std::cout << "\n--- RepositorioProductos: Obteniendo productos ---\n";
        conexion->ejecutarConsulta("SELECT * FROM productos");
    }
};

int main() {
    std::cout << std::string(60, '=') << "\n";
    std::cout << "EJERCICIO 03: CONEXIÓN BD CON SINGLETON\n";
    std::cout << std::string(60, '=') << "\n";
    
    std::cout << "\n1️⃣  Creando primera referencia a ConexionBD...\n";
    ConexionBD* conexion1 = ConexionBD::obtenerInstancia();
    std::cout << "   ID de conexion1: " << conexion1 << "\n";
    
    std::cout << "\n2️⃣  Creando segunda referencia a ConexionBD...\n";
    ConexionBD* conexion2 = ConexionBD::obtenerInstancia();
    std::cout << "   ID de conexion2: " << conexion2 << "\n";
    
    std::cout << "\n3️⃣  Creando tercera referencia a ConexionBD...\n";
    ConexionBD* conexion3 = ConexionBD::obtenerInstancia();
    std::cout << "   ID de conexion3: " << conexion3 << "\n";
    
    std::cout << "\n✅ Verificación: Todas son la misma instancia: " 
              << (conexion1 == conexion2 && conexion2 == conexion3 ? "true" : "false") << "\n";
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "OPERACIONES CON LA CONEXIÓN\n";
    std::cout << std::string(60, '=') << "\n";
    
    conexion1->estado();
    conexion1->conectar();
    conexion1->estado();
    
    conexion2->ejecutarConsulta("SELECT * FROM usuarios WHERE id = 1");
    conexion3->ejecutarConsulta("SELECT COUNT(*) FROM productos");
    conexion1->ejecutarConsulta("INSERT INTO logs VALUES ('Nueva entrada')");
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "ACCESO DESDE DIFERENTES MÓDULOS\n";
    std::cout << std::string(60, '=') << "\n";
    
    RepositorioUsuarios repoUsuarios;
    std::cout << "ConexionBD en RepositorioUsuarios: " << ConexionBD::obtenerInstancia() << "\n";
    repoUsuarios.obtenerUsuarios();
    
    RepositorioProductos repoProductos;
    std::cout << "\nConexionBD en RepositorioProductos: " << ConexionBD::obtenerInstancia() << "\n";
    repoProductos.obtenerProductos();
    
    conexion1->estado();
    conexion1->desconectar();
    conexion1->estado();
    
    conexion2->ejecutarConsulta("SELECT * FROM test");
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "CONCLUSIÓN\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "✅ Todas las referencias apuntan a la misma instancia\n";
    std::cout << "✅ Solo existe una conexión activa en todo momento\n";
    std::cout << "✅ Todos los módulos comparten el mismo estado de conexión\n";
    
    ConexionBD::destruirInstancia();
    return 0;
}
