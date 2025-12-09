#ifndef CONTROLJUEGO_H
#define CONTROLJUEGO_H

#include <iostream>
#include <string>

class ControlJuego {
private:
    static ControlJuego* instancia;
    int nivelActual;
    int puntaje;
    int vidas;
    int puntuacionMaxima;
    bool juegoEnCurso;
    int enemigosEliminados;
    int itemsRecolectados;
    
    ControlJuego() : nivelActual(1), puntaje(0), vidas(3), 
                     puntuacionMaxima(0), juegoEnCurso(false),
                     enemigosEliminados(0), itemsRecolectados(0) {}
    
    ControlJuego(const ControlJuego&) = delete;
    ControlJuego& operator=(const ControlJuego&) = delete;

public:
    static ControlJuego* obtenerInstancia() {
        if (instancia == nullptr) {
            std::cout << "🎮 Inicializando Control del Juego...\n";
            instancia = new ControlJuego();
            std::cout << "✅ Estado del juego inicializado\n";
        }
        return instancia;
    }
    
    bool iniciarJuego() {
        if (juegoEnCurso) {
            std::cout << "⚠️  Ya hay un juego en curso\n";
            return false;
        }
        
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "🎮 INICIANDO NUEVO JUEGO\n";
        std::cout << std::string(60, '=') << "\n";
        nivelActual = 1;
        puntaje = 0;
        vidas = 3;
        enemigosEliminados = 0;
        itemsRecolectados = 0;
        juegoEnCurso = true;
        mostrarEstado();
        return true;
    }
    
    bool finalizarJuego() {
        if (!juegoEnCurso) {
            std::cout << "⚠️  No hay juego en curso\n";
            return false;
        }
        
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "🏁 JUEGO FINALIZADO\n";
        std::cout << std::string(60, '=') << "\n";
        
        if (puntaje > puntuacionMaxima) {
            puntuacionMaxima = puntaje;
            std::cout << "🏆 ¡NUEVO RÉCORD!\n";
        }
        
        std::cout << "Puntaje final: " << puntaje << "\n";
        std::cout << "Nivel alcanzado: " << nivelActual << "\n";
        std::cout << "Enemigos eliminados: " << enemigosEliminados << "\n";
        std::cout << "Items recolectados: " << itemsRecolectados << "\n";
        std::cout << "Récord: " << puntuacionMaxima << "\n";
        std::cout << std::string(60, '=') << "\n";
        
        juegoEnCurso = false;
        return true;
    }
    
    bool subirNivel() {
        if (!juegoEnCurso) {
            std::cout << "❌ No hay juego en curso\n";
            return false;
        }
        
        nivelActual++;
        int bonus = nivelActual * 100;
        puntaje += bonus;
        std::cout << "\n🎉 ¡NIVEL " << nivelActual << " COMPLETADO!\n";
        std::cout << "   Bonus de nivel: +" << bonus << " puntos\n";
        return true;
    }
    
    bool sumarPuntos(int puntos) {
        if (!juegoEnCurso) return false;
        puntaje += puntos;
        std::cout << "   ✨ +" << puntos << " puntos (Total: " << puntaje << ")\n";
        return true;
    }
    
    bool perderVida() {
        if (!juegoEnCurso) return false;
        vidas--;
        std::cout << "   💔 Perdiste una vida (Vidas restantes: " << vidas << ")\n";
        
        if (vidas <= 0) {
            std::cout << "   ☠️  GAME OVER - Sin vidas restantes\n";
            finalizarJuego();
            return false;
        }
        return true;
    }
    
    bool ganarVida() {
        if (!juegoEnCurso) return false;
        vidas++;
        std::cout << "   💚 ¡Ganaste una vida! (Vidas: " << vidas << ")\n";
        return true;
    }
    
    void registrarEnemigoEliminado() {
        if (juegoEnCurso) enemigosEliminados++;
    }
    
    void registrarItemRecolectado() {
        if (juegoEnCurso) itemsRecolectados++;
    }
    
    void mostrarEstado() const {
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "📊 ESTADO DEL JUEGO\n";
        std::cout << std::string(60, '=') << "\n";
        std::cout << "Estado: " << (juegoEnCurso ? "🟢 EN CURSO" : "🔴 DETENIDO") << "\n";
        std::cout << "Nivel: " << nivelActual << "\n";
        std::cout << "Puntaje: " << puntaje << "\n";
        std::cout << "Vidas: ";
        for (int i = 0; i < vidas; i++) std::cout << "❤️ ";
        std::cout << "\n";
        std::cout << "Enemigos eliminados: " << enemigosEliminados << "\n";
        std::cout << "Items recolectados: " << itemsRecolectados << "\n";
        std::cout << "Récord histórico: " << puntuacionMaxima << "\n";
        std::cout << std::string(60, '=') << "\n";
    }
    
    int getNivel() const { return nivelActual; }
    int getPuntaje() const { return puntaje; }
    int getVidas() const { return vidas; }
    bool estaEnCurso() const { return juegoEnCurso; }
    
    static void destruirInstancia() {
        if (instancia != nullptr) {
            delete instancia;
            instancia = nullptr;
        }
    }
};

ControlJuego* ControlJuego::instancia = nullptr;

#endif
