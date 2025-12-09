import random


class ControlJuego:
    """
    Clase Singleton que maneja el estado global de un juego.
    Garantiza que todos los componentes del juego accedan al mismo estado.
    """
    _instancia = None
    
    def __new__(cls):
        """
        Sobrescribe __new__ para controlar la creación de instancias.
        Si ya existe una instancia, la retorna; si no, crea una nueva.
        """
        if cls._instancia is None:
            print("🎮 Inicializando Control del Juego...")
            cls._instancia = super(ControlJuego, cls).__new__(cls)
            cls._instancia._inicializado = False
        return cls._instancia
    
    def __init__(self):
        """
        Inicializa el estado del juego solo la primera vez.
        """
        if not self._inicializado:
            self._inicializado = True
            self._nivel_actual = 1
            self._puntaje = 0
            self._vidas = 3
            self._puntuacion_maxima = 0
            self._juego_en_curso = False
            self._enemigos_eliminados = 0
            self._items_recolectados = 0
            print("✅ Estado del juego inicializado")
    
    def iniciar_juego(self):
        """Inicia una nueva partida"""
        if self._juego_en_curso:
            print("⚠️  Ya hay un juego en curso")
            return False
        
        print("\n" + "=" * 60)
        print("🎮 INICIANDO NUEVO JUEGO")
        print("=" * 60)
        self._nivel_actual = 1
        self._puntaje = 0
        self._vidas = 3
        self._enemigos_eliminados = 0
        self._items_recolectados = 0
        self._juego_en_curso = True
        self.mostrar_estado()
        return True
    
    def finalizar_juego(self):
        """Finaliza la partida actual"""
        if not self._juego_en_curso:
            print("⚠️  No hay juego en curso")
            return False
        
        print("\n" + "=" * 60)
        print("🏁 JUEGO FINALIZADO")
        print("=" * 60)
        
        if self._puntaje > self._puntuacion_maxima:
            self._puntuacion_maxima = self._puntaje
            print("🏆 ¡NUEVO RÉCORD!")
        
        print(f"Puntaje final: {self._puntaje}")
        print(f"Nivel alcanzado: {self._nivel_actual}")
        print(f"Enemigos eliminados: {self._enemigos_eliminados}")
        print(f"Items recolectados: {self._items_recolectados}")
        print(f"Récord: {self._puntuacion_maxima}")
        print("=" * 60)
        
        self._juego_en_curso = False
        return True
    
    def subir_nivel(self):
        """Avanza al siguiente nivel"""
        if not self._juego_en_curso:
            print("❌ No hay juego en curso")
            return False
        
        self._nivel_actual += 1
        bonus = self._nivel_actual * 100
        self._puntaje += bonus
        print(f"\n🎉 ¡NIVEL {self._nivel_actual} COMPLETADO!")
        print(f"   Bonus de nivel: +{bonus} puntos")
        return True
    
    def sumar_puntos(self, puntos):
        """Suma puntos al puntaje actual"""
        if not self._juego_en_curso:
            return False
        
        self._puntaje += puntos
        print(f"   ✨ +{puntos} puntos (Total: {self._puntaje})")
        return True
    
    def perder_vida(self):
        """Resta una vida al jugador"""
        if not self._juego_en_curso:
            return False
        
        self._vidas -= 1
        print(f"   💔 Perdiste una vida (Vidas restantes: {self._vidas})")
        
        if self._vidas <= 0:
            print("   ☠️  GAME OVER - Sin vidas restantes")
            self.finalizar_juego()
            return False
        
        return True
    
    def ganar_vida(self):
        """Suma una vida al jugador"""
        if not self._juego_en_curso:
            return False
        
        self._vidas += 1
        print(f"   💚 ¡Ganaste una vida! (Vidas: {self._vidas})")
        return True
    
    def registrar_enemigo_eliminado(self):
        """Registra la eliminación de un enemigo"""
        if not self._juego_en_curso:
            return False
        
        self._enemigos_eliminados += 1
        return True
    
    def registrar_item_recolectado(self):
        """Registra la recolección de un item"""
        if not self._juego_en_curso:
            return False
        
        self._items_recolectados += 1
        return True
    
    def mostrar_estado(self):
        """Muestra el estado actual del juego"""
        print("\n" + "=" * 60)
        print("📊 ESTADO DEL JUEGO")
        print("=" * 60)
        print(f"Estado: {'🟢 EN CURSO' if self._juego_en_curso else '🔴 DETENIDO'}")
        print(f"Nivel: {self._nivel_actual}")
        print(f"Puntaje: {self._puntaje}")
        print(f"Vidas: {'❤️ ' * self._vidas}")
        print(f"Enemigos eliminados: {self._enemigos_eliminados}")
        print(f"Items recolectados: {self._items_recolectados}")
        print(f"Récord histórico: {self._puntuacion_maxima}")
        print("=" * 60)
    
    # Getters para acceso de solo lectura
    def get_nivel(self):
        return self._nivel_actual
    
    def get_puntaje(self):
        return self._puntaje
    
    def get_vidas(self):
        return self._vidas
    
    def esta_en_curso(self):
        return self._juego_en_curso


# Componentes del juego que interactúan con ControlJuego
class Jugador:
    """Representa al jugador del juego"""
    def __init__(self, nombre):
        self.nombre = nombre
        self.control = ControlJuego()
        print(f"\n👤 Jugador '{nombre}' conectado al juego")
    
    def atacar_enemigo(self, enemigo):
        """Ataca a un enemigo"""
        print(f"\n⚔️  {self.nombre} ataca a {enemigo.nombre}")
        if random.random() > 0.3:  # 70% de éxito
            enemigo.recibir_dano()
        else:
            print(f"   ❌ ¡Fallo el ataque!")
            self.recibir_dano()
    
    def recolectar_item(self, item):
        """Recolecta un item"""
        print(f"\n🎁 {self.nombre} recolecta: {item.nombre}")
        item.aplicar_efecto()
    
    def recibir_dano(self):
        """El jugador recibe daño"""
        print(f"   💥 {self.nombre} recibió daño")
        self.control.perder_vida()


class Enemigo:
    """Representa a un enemigo en el juego"""
    _contador = 0
    
    def __init__(self, tipo="Básico"):
        Enemigo._contador += 1
        self.nombre = f"{tipo} #{Enemigo._contador}"
        self.vida = 100
        self.control = ControlJuego()
        self.puntos_otorgados = 50 if tipo == "Básico" else 150
    
    def recibir_dano(self):
        """El enemigo recibe daño"""
        self.vida -= random.randint(30, 60)
        print(f"   💥 {self.nombre} recibió daño (Vida: {max(0, self.vida)})")
        
        if self.vida <= 0:
            self.eliminar()
    
    def eliminar(self):
        """Elimina al enemigo y otorga puntos"""
        print(f"   ☠️  {self.nombre} eliminado")
        self.control.sumar_puntos(self.puntos_otorgados)
        self.control.registrar_enemigo_eliminado()


class Item:
    """Representa un item recolectable"""
    def __init__(self, nombre, tipo):
        self.nombre = nombre
        self.tipo = tipo
        self.control = ControlJuego()
    
    def aplicar_efecto(self):
        """Aplica el efecto del item"""
        self.control.registrar_item_recolectado()
        
        if self.tipo == "puntos":
            puntos = random.randint(100, 300)
            self.control.sumar_puntos(puntos)
            print(f"   ⭐ Ganaste {puntos} puntos")
        elif self.tipo == "vida":
            self.control.ganar_vida()
        elif self.tipo == "poder":
            puntos = 500
            self.control.sumar_puntos(puntos)
            print(f"   ⚡ ¡Poder especial activado! +{puntos} puntos")


class InterfazJuego:
    """Representa la interfaz de usuario del juego"""
    def __init__(self):
        self.control = ControlJuego()
        print("\n🖥️  Interfaz de juego inicializada")
    
    def actualizar_pantalla(self):
        """Actualiza la visualización del juego"""
        self.control.mostrar_estado()
    
    def notificar_evento(self, mensaje):
        """Muestra un mensaje en la interfaz"""
        print(f"\n📢 NOTIFICACIÓN: {mensaje}")


if __name__ == "__main__":
    print("=" * 60)
    print("DEMOSTRACIÓN DEL PATRÓN SINGLETON - CONTROL DE JUEGO")
    print("=" * 60)
    
    # Verificar que todos los componentes usan la misma instancia
    control1 = ControlJuego()
    control2 = ControlJuego()
    print(f"\n✅ Misma instancia de control: {control1 is control2}")
    
    # Crear componentes del juego
    interfaz = InterfazJuego()
    jugador = Jugador("Héroe")
    
    print(f"\nID ControlJuego en interfaz: {id(interfaz.control)}")
    print(f"ID ControlJuego en jugador: {id(jugador.control)}")
    print(f"ID ControlJuego directo: {id(control1)}")
    print(f"✅ Todos usan la misma instancia: {interfaz.control is jugador.control is control1}")
    
    # Iniciar juego
    control1.iniciar_juego()
    
    # Simulación de nivel 1
    print("\n" + "=" * 60)
    print("🎮 NIVEL 1")
    print("=" * 60)
    
    enemigo1 = Enemigo("Básico")
    enemigo2 = Enemigo("Básico")
    
    jugador.atacar_enemigo(enemigo1)
    jugador.atacar_enemigo(enemigo2)
    
    item1 = Item("Moneda de oro", "puntos")
    jugador.recolectar_item(item1)
    
    interfaz.actualizar_pantalla()
    
    # Completar nivel y subir
    control1.subir_nivel()
    
    # Simulación de nivel 2
    print("\n" + "=" * 60)
    print("🎮 NIVEL 2")
    print("=" * 60)
    
    enemigo3 = Enemigo("Élite")
    enemigo3.puntos_otorgados = 300
    jugador.atacar_enemigo(enemigo3)
    
    item2 = Item("Corazón", "vida")
    jugador.recolectar_item(item2)
    
    item3 = Item("Estrella", "poder")
    jugador.recolectar_item(item3)
    
    interfaz.actualizar_pantalla()
    
    # Finalizar juego
    control1.finalizar_juego()
    
    # Intentar nueva partida
    print("\n" + "=" * 60)
    print("🎮 NUEVA PARTIDA")
    print("=" * 60)
    control2.iniciar_juego()
    
    enemigo4 = Enemigo("Básico")
    jugador.atacar_enemigo(enemigo4)
    
    interfaz.actualizar_pantalla()
    control2.finalizar_juego()
    
    print("\n" + "=" * 60)
    print("CONCLUSIÓN")
    print("=" * 60)
    print("✅ Todos los componentes (Jugador, Enemigo, Item, Interfaz)")
    print("   acceden y modifican el mismo estado de juego")
    print("✅ El ControlJuego mantiene la consistencia global")
    print("✅ El patrón Singleton facilita la comunicación entre componentes")
