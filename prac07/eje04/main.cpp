#include "ControlJuego.h"
#include <cstdlib>
#include <ctime>

class Jugador {
private:
    std::string nombre;
    ControlJuego* control;
public:
    Jugador(const std::string& n) : nombre(n), control(ControlJuego::obtenerInstancia()) {
        std::cout << "\n👤 Jugador '" << nombre << "' conectado al juego\n";
    }
    
    std::string getNombre() const { return nombre; }
    ControlJuego* getControl() { return control; }
    
    void recibirDano() {
        std::cout << "   💥 " << nombre << " recibió daño\n";
        control->perderVida();
    }
};

class Enemigo {
private:
    static int contador;
    std::string nombre;
    int vida;
    ControlJuego* control;
    int puntosOtorgados;
public:
    Enemigo(const std::string& tipo = "Básico") 
        : vida(100), control(ControlJuego::obtenerInstancia()) {
        contador++;
        nombre = tipo + " #" + std::to_string(contador);
        puntosOtorgados = (tipo == "Básico") ? 50 : 150;
    }
    
    std::string getNombre() const { return nombre; }
    
    void recibirDano() {
        vida -= (rand() % 31 + 30);
        std::cout << "   💥 " << nombre << " recibió daño (Vida: " << (vida > 0 ? vida : 0) << ")\n";
        
        if (vida <= 0) {
            eliminar();
        }
    }
    
    void eliminar() {
        std::cout << "   ☠️  " << nombre << " eliminado\n";
        control->sumarPuntos(puntosOtorgados);
        control->registrarEnemigoEliminado();
    }
};

int Enemigo::contador = 0;

class Item {
private:
    std::string nombre;
    std::string tipo;
    ControlJuego* control;
public:
    Item(const std::string& n, const std::string& t) 
        : nombre(n), tipo(t), control(ControlJuego::obtenerInstancia()) {}
    
    std::string getNombre() const { return nombre; }
    
    void aplicarEfecto() {
        control->registrarItemRecolectado();
        
        if (tipo == "puntos") {
            int puntos = rand() % 201 + 100;
            control->sumarPuntos(puntos);
            std::cout << "   ⭐ Ganaste " << puntos << " puntos\n";
        } else if (tipo == "vida") {
            control->ganarVida();
        } else if (tipo == "poder") {
            int puntos = 500;
            control->sumarPuntos(puntos);
            std::cout << "   ⚡ ¡Poder especial activado! +" << puntos << " puntos\n";
        }
    }
};

class InterfazJuego {
private:
    ControlJuego* control;
public:
    InterfazJuego() : control(ControlJuego::obtenerInstancia()) {
        std::cout << "\n🖥️  Interfaz de juego inicializada\n";
    }
    
    void actualizarPantalla() {
        control->mostrarEstado();
    }
    
    ControlJuego* getControl() { return control; }
};

int main() {
    srand(time(0));
    
    std::cout << std::string(60, '=') << "\n";
    std::cout << "EJERCICIO 04: CONTROL DE JUEGO CON SINGLETON\n";
    std::cout << std::string(60, '=') << "\n";
    
    ControlJuego* control1 = ControlJuego::obtenerInstancia();
    ControlJuego* control2 = ControlJuego::obtenerInstancia();
    std::cout << "\n✅ Misma instancia de control: " << (control1 == control2 ? "true" : "false") << "\n";
    
    InterfazJuego interfaz;
    Jugador jugador("Héroe");
    
    std::cout << "\nID ControlJuego en interfaz: " << interfaz.getControl() << "\n";
    std::cout << "ID ControlJuego en jugador: " << jugador.getControl() << "\n";
    std::cout << "ID ControlJuego directo: " << control1 << "\n";
    std::cout << "✅ Todos usan la misma instancia: " 
              << (interfaz.getControl() == jugador.getControl() && 
                  jugador.getControl() == control1 ? "true" : "false") << "\n";
    
    control1->iniciarJuego();
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "🎮 NIVEL 1\n";
    std::cout << std::string(60, '=') << "\n";
    
    Enemigo enemigo1("Básico");
    Enemigo enemigo2("Básico");
    
    std::cout << "\n⚔️  " << jugador.getNombre() << " ataca a " << enemigo1.getNombre() << "\n";
    if (rand() % 10 > 2) {
        enemigo1.recibirDano();
    } else {
        std::cout << "   ❌ ¡Falló el ataque!\n";
        jugador.recibirDano();
    }
    
    std::cout << "\n⚔️  " << jugador.getNombre() << " ataca a " << enemigo2.getNombre() << "\n";
    enemigo2.recibirDano();
    
    Item item1("Moneda de oro", "puntos");
    std::cout << "\n🎁 " << jugador.getNombre() << " recolecta: " << item1.getNombre() << "\n";
    item1.aplicarEfecto();
    
    interfaz.actualizarPantalla();
    control1->subirNivel();
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "🎮 NIVEL 2\n";
    std::cout << std::string(60, '=') << "\n";
    
    Enemigo enemigo3("Élite");
    std::cout << "\n⚔️  " << jugador.getNombre() << " ataca a " << enemigo3.getNombre() << "\n";
    enemigo3.recibirDano();
    
    Item item2("Corazón", "vida");
    std::cout << "\n🎁 " << jugador.getNombre() << " recolecta: " << item2.getNombre() << "\n";
    item2.aplicarEfecto();
    
    Item item3("Estrella", "poder");
    std::cout << "\n🎁 " << jugador.getNombre() << " recolecta: " << item3.getNombre() << "\n";
    item3.aplicarEfecto();
    
    interfaz.actualizarPantalla();
    control1->finalizarJuego();
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "🎮 NUEVA PARTIDA\n";
    std::cout << std::string(60, '=') << "\n";
    control2->iniciarJuego();
    
    Enemigo enemigo4("Básico");
    std::cout << "\n⚔️  " << jugador.getNombre() << " ataca a " << enemigo4.getNombre() << "\n";
    enemigo4.recibirDano();
    
    interfaz.actualizarPantalla();
    control2->finalizarJuego();
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "CONCLUSIÓN\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "✅ Todos los componentes (Jugador, Enemigo, Item, Interfaz)\n";
    std::cout << "   acceden y modifican el mismo estado de juego\n";
    std::cout << "✅ El ControlJuego mantiene la consistencia global\n";
    std::cout << "✅ El patrón Singleton facilita la comunicación entre componentes\n";
    
    ControlJuego::destruirInstancia();
    return 0;
}
