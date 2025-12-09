# Ejercicio 05: Singleton Thread-Safe (Double-Checked Locking)

## Descripción
Implementación de Singleton seguro para entornos multihilo utilizando double-checked locking y mutexes. Incluye versiones thread-safe de Logger y ConexionBD.

## Objetivo
Modificar las implementaciones previas para hacerlas seguras contra race conditions en aplicaciones concurrentes con múltiples hilos.

## El Problema de Concurrencia

### Race Condition en Singleton Básico
```cpp
// Código NO thread-safe
if (instancia == nullptr) {           // Hilo A y B verifican simultáneamente
    instancia = new Singleton();      // Ambos crean una instancia
}
return instancia;                      // ❌ Dos instancias creadas
```

**Consecuencias**:
- Logger: Corrupción del archivo de log
- ConexionBD: Múltiples conexiones consumiendo recursos
- Estado inconsistente entre componentes

## Solución: Double-Checked Locking

### Técnica Implementada
```cpp
// Primera verificación (sin lock - rápida)
if (instancia == nullptr) {
    std::lock_guard<std::mutex> lock(mutexInstancia);
    // Segunda verificación (con lock - segura)
    if (instancia == nullptr) {
        instancia = new Singleton();
    }
}
return instancia;
```

### Ventajas
1. **Primera verificación**: Rápida, sin bloqueo si la instancia existe
2. **Lock**: Solo se activa si es necesario crear la instancia
3. **Segunda verificación**: Asegura que solo un hilo crea la instancia

## Implementación

### LoggerThreadSafe
- **mutexInstancia**: Protege la creación de la instancia
- **mutexEscritura**: Protege las operaciones de I/O al archivo
- Garantiza escrituras atómicas sin corrupción de datos

### ConexionBDThreadSafe
- **mutexInstancia**: Protege instanciación
- **mutexConexion**: Protege estado de conexión
- **mutexContador**: Protege contador de consultas
- Operaciones thread-safe: conectar(), ejecutarConsulta()

### Pruebas Multihilo
- Múltiples hilos intentan crear instancias simultáneamente
- Ejecución de operaciones concurrentes
- Verificación de instancia única

## Compilación y Ejecución

```bash
g++ -std=c++11 main.cpp -o singleton_threadsafe -pthread
./singleton_threadsafe
```

**Nota**: La bandera `-pthread` es necesaria para soporte de hilos.

## Resultado Esperado
- Solo se crea una instancia del Singleton por clase
- Todas las referencias tienen la misma dirección de memoria
- Las operaciones concurrentes se ejecutan de forma segura
- No hay race conditions ni corrupción de datos
- Archivo `bitacora_threadsafe.log` contiene logs de todos los hilos
            cls._instancia = crear_nueva()
return cls._instancia
```

### ¿Por qué "Double-Checked"?

1. **Primera verificación (sin lock)**:
   - Rápida, sin bloqueo
   - Si la instancia ya existe, retorna inmediatamente
   - Evita bloqueos innecesarios en el 99.9% de los casos

2. **Bloqueo con Lock**:
   - Solo se activa si la instancia no existe
   - Impide que múltiples hilos entren simultáneamente

3. **Segunda verificación (con lock)**:
   - Asegura que solo un hilo cree la instancia
   - Otro hilo que estaba esperando el lock verá que ya se creó

## Implementaciones

### 1. LoggerThreadSafe

#### Características
- **Lock de creación** (`_lock`): Protege la creación de la instancia
- **Lock de escritura** (`_lock_escritura`): Protege las operaciones de I/O al archivo
- **Thread-safe initialization**: Evita múltiples inicializaciones

#### Locks Utilizados
```python
_lock = threading.Lock()              # Para creación de instancia
_lock_escritura = threading.Lock()    # Para escritura en archivo
```

#### Flujo Thread-Safe
1. Verificación rápida sin lock
2. Si necesario, adquirir lock de creación
3. Segunda verificación con lock
4. Crear instancia si aún es None
5. Para escritura: Siempre usar `_lock_escritura`

#### Métodos
- `log(mensaje, nivel)`: Escribe al archivo de forma thread-safe
- Incluye timestamp y nombre del thread en cada mensaje

### 2. ConexionBDThreadSafe

#### Características
- **Lock de creación** (`_lock`): Protege instanciación
- **Lock de conexión** (`_lock_conexion`): Protege estado de conexión
- **Lock de contador** (`_lock_contador`): Protege contador de consultas

#### Locks Utilizados
```python
_lock = threading.Lock()              # Para creación de instancia
_lock_conexion = threading.Lock()     # Para operaciones de conexión
_lock_contador = threading.Lock()     # Para incrementar contadores
```

#### Métodos Thread-Safe
- `conectar()`: Conecta de forma segura, evita dobles conexiones
- `ejecutar_consulta(consulta)`: Ejecuta y cuenta consultas de forma atómica
- `get_estadisticas()`: Retorna estadísticas sin race conditions

## Funciones de Prueba

### prueba_logger_concurrente(id_trabajador, num_mensajes)
Simula múltiples hilos intentando:
1. Crear su "propia" instancia del logger
2. Registrar múltiples mensajes simultáneamente
3. Verificar que todos usan la misma instancia

### prueba_bd_concurrente(id_trabajador, num_consultas)
Simula múltiples hilos:
1. Obteniendo la conexión a BD
2. Ejecutando consultas simultáneas
3. Incrementando contadores de forma segura

## Conceptos Clave de Threading

### threading.Lock()
- Objeto de sincronización que permite exclusión mutua
- Solo un hilo puede adquirir el lock a la vez
- Otros hilos esperan hasta que se libere

### with cls._lock:
- Context manager que adquiere y libera automáticamente el lock
- Garantiza que el lock se libere incluso si hay excepciones
- Equivalente a `try-finally` con `acquire()` y `release()`

### threading.current_thread()
- Retorna el objeto Thread del hilo actual
- Útil para identificar qué hilo ejecuta cada operación
- `.name` proporciona el nombre del hilo para logging

## Ejecución

```bash
python singleton_threadsafe.py
```

## Resultado Esperado

### Prueba de Logger
```
🚀 Lanzando 5 hilos para probar el logger...
🔧 [LogWorker-1] Creando nueva instancia de LoggerThreadSafe...
♻️  [LogWorker-2] Reutilizando instancia existente...
♻️  [LogWorker-3] Reutilizando instancia existente...
...
✅ Todos los hilos de logger han terminado
```

### Prueba de Conexión BD
```
🚀 Lanzando 4 hilos para ejecutar consultas...
📊 [DBWorker-1] Ejecutando: SELECT * FROM tabla_1...
📊 [DBWorker-2] Ejecutando: SELECT * FROM tabla_2...
...
📊 ESTADÍSTICAS FINALES:
   Total de consultas ejecutadas: 8
```

### Verificación
```
✅ Todas las instancias tienen el mismo ID
✅ Solo se creó una instancia del Singleton
✅ Todas las operaciones se ejecutaron correctamente
```

## Patrones de Diseño Relacionados

### Comparación de Técnicas Thread-Safe

| Técnica | Ventajas | Desventajas |
|---------|----------|-------------|
| **Double-Checked Locking** | Eficiente, solo bloquea al crear | Más complejo |
| **Lock siempre** | Simple, muy seguro | Overhead en cada acceso |
| **Eager Initialization** | Thread-safe por defecto | Consume memoria siempre |
| **Lock-free (atomic)** | Muy eficiente | Requiere operaciones atómicas |

### Eager Initialization (Alternativa)
```python
class Singleton:
    _instancia = Singleton()  # Se crea al cargar la clase
    
    def __new__(cls):
        return cls._instancia
```
✅ Thread-safe por diseño de Python
❌ Se crea incluso si nunca se usa

## Ventajas del Enfoque Implementado

1. ✅ **Thread-Safety Garantizado**: Imposible crear múltiples instancias
2. ✅ **Eficiencia**: Solo bloquea cuando es necesario
3. ✅ **Protección de Recursos**: Locks separados para diferentes operaciones
4. ✅ **Trazabilidad**: Cada operación registra el thread que la ejecuta
5. ✅ **Escalabilidad**: Funciona bien con muchos threads
6. ✅ **Integridad de Datos**: Contadores y estado siempre consistentes

## Casos de Uso Reales

- **Servicios web con múltiples workers** (Flask, FastAPI)
- **Aplicaciones con thread pools**
- **Procesamiento paralelo de datos**
- **Servidores con múltiples conexiones simultáneas**
- **Sistemas de cache compartido**
- **Gestión de recursos limitados (conexiones, sockets)**

## Consideraciones Importantes

⚠️ **En Python con CPython**:
- El GIL (Global Interpreter Lock) proporciona cierta protección
- Sin embargo, NO garantiza atomicidad de operaciones complejas
- Es necesario usar locks explícitos para garantizar thread-safety

⚠️ **Overhead de Performance**:
- Los locks tienen un costo de rendimiento
- Para aplicaciones de un solo hilo, usar Singleton simple
- Para aplicaciones multi-threaded, este overhead es necesario

✅ **Best Practice**:
- Usar locks granulares (diferentes locks para diferentes recursos)
- Minimizar el código dentro del bloque con lock
- Documentar claramente qué protege cada lock
