# Ejercicio 04: Singleton en un Juego

## Descripción
Sistema de control de estado global para un videojuego utilizando el patrón Singleton. Gestiona nivel, puntaje, vidas y estadísticas compartidas entre todos los componentes del juego.

## Objetivo
Implementar una clase `ControlJuego` que centralice el estado del juego, permitiendo que todos los componentes (Jugador, Enemigos, Items, Interfaz) accedan y modifiquen el mismo estado de forma consistente.

## Implementación

### Características Principales
- Estado global compartido: nivel, puntaje, vidas
- Gestión de partidas: iniciar, finalizar, pausar
- Sistema de progresión: niveles, bonus, récords
- Estadísticas: enemigos eliminados, items recolectados
- Validación de estado (solo modificable durante partida activa)

### Estructura
```
ControlJuego (Singleton)
├── nivelActual
├── puntaje
├── vidas
├── puntuacionMaxima
├── juegoEnCurso
├── enemigosEliminados
├── itemsRecolectados
└── métodos:
    ├── obtenerInstancia()
    ├── iniciarJuego()
    ├── finalizarJuego()
    ├── subirNivel()
    ├── sumarPuntos()
    ├── perderVida() / ganarVida()
    └── mostrarEstado()
```

### Componentes del Juego
- **Jugador**: Realiza acciones, recibe daño
- **Enemigo**: Puede ser eliminado, otorga puntos
- **Item**: Efectos (puntos, vida, poder)
- **InterfazJuego**: Visualiza el estado

## Compilación y Ejecución

```bash
g++ -std=c++11 main.cpp -o controljuego
./controljuego
```

## Resultado Esperado
- Todos los componentes usan la misma instancia de ControlJuego
- Los cambios de estado son visibles para todos los componentes
- Las estadísticas se actualizan correctamente
- El récord se mantiene entre partidas

### Clase Jugador
Representa al jugador principal del juego. Interactúa con ControlJuego para:
- Recibir daño y perder vidas
- Atacar enemigos
- Recolectar items

**Métodos:**
- `atacar_enemigo(enemigo)`: Intenta eliminar un enemigo
- `recolectar_item(item)`: Recoge un item del escenario
- `recibir_dano()`: Pierde una vida

### Clase Enemigo
Representa a los enemigos del juego. Usa ControlJuego para:
- Otorgar puntos al ser eliminado
- Registrar su eliminación en estadísticas

**Atributos:**
- `nombre`: Identificador del enemigo
- `vida`: Puntos de vida
- `puntos_otorgados`: Puntos que da al ser derrotado

**Métodos:**
- `recibir_dano()`: Reduce vida, verifica si debe ser eliminado
- `eliminar()`: Otorga puntos y actualiza estadísticas

### Clase Item
Representa objetos recolectables en el juego. Tipos de items:
- **Puntos**: Otorgan puntos extra
- **Vida**: Restauran o añaden vidas
- **Poder**: Otorgan bonificaciones especiales

**Métodos:**
- `aplicar_efecto()`: Aplica el beneficio del item al jugador

### Clase InterfazJuego
Representa la UI del juego. Consulta ControlJuego para:
- Mostrar información actualizada del estado
- Notificar eventos al jugador

**Métodos:**
- `actualizar_pantalla()`: Muestra el estado actual
- `notificar_evento(mensaje)`: Muestra notificaciones

## Flujo de Ejecución

```
1. Crear componentes del juego (todos obtienen la misma instancia de ControlJuego)
2. Iniciar partida
3. Simulación Nivel 1:
   - Crear enemigos
   - Jugador ataca enemigos
   - Recolectar items
   - Actualizar interfaz
4. Subir de nivel
5. Simulación Nivel 2:
   - Enemigos más difíciles
   - Más items
6. Finalizar juego
7. Iniciar nueva partida (el récord se mantiene)
```

## Características del Patrón Singleton Implementado

1. **Estado Global Compartido**: Todos los componentes ven y modifican el mismo estado
2. **Consistencia**: No puede haber desincronización entre componentes
3. **Simplicidad**: Los componentes no necesitan pasarse referencias entre sí
4. **Persistencia de Datos**: El récord histórico se mantiene entre partidas
5. **Punto de Control Único**: Fácil implementar lógica de game over, pausas, etc.

## Ejecución

```bash
python control_juego.py
```

## Resultado Esperado

El programa demuestra:
- ✅ Todos los componentes usan la misma instancia de ControlJuego
- ✅ Los cambios de estado son visibles inmediatamente para todos
- ✅ Las estadísticas se actualizan correctamente desde diferentes componentes
- ✅ La interfaz siempre muestra el estado actualizado
- ✅ El récord se mantiene entre partidas

## Ventajas en el Desarrollo de Juegos

- **Arquitectura Simple**: No se necesita pasar referencias del estado por todo el código
- **Debugging Fácil**: Un solo lugar donde verificar el estado del juego
- **Extensibilidad**: Nuevos componentes pueden acceder fácilmente al estado
- **Sincronización Automática**: Todos los componentes siempre están actualizados
- **Save/Load Simple**: Un solo objeto para serializar el estado
- **Replay System**: Fácil grabar y reproducir secuencias de juego

## Casos de Uso Reales

Este patrón se usa comúnmente en:
- **Gestión de estado en juegos** (Unity, Unreal Engine)
- **Sistemas de puntuación y progresión**
- **Managers de audio global**
- **Gestión de configuraciones de juego**
- **Sistema de achievements/logros**
- **Persistencia de datos entre escenas**

## Consideraciones

⚠️ **Advertencia**: En juegos grandes, un único Singleton puede volverse demasiado complejo. Considerar:
- Dividir en múltiples Singletons especializados (AudioManager, ScoreManager, etc.)
- Usar sistemas de eventos para comunicación entre componentes
- Implementar el patrón Service Locator para mayor flexibilidad
