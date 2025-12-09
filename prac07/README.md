# Práctica 07 - Patrón de Diseño: Singleton

## Integrantes del Equipo
- **[Nombre Integrante 1]** - [Matrícula/ID]
- **[Nombre Integrante 2]** - [Matrícula/ID]
- **[Nombre Integrante 3]** - [Matrícula/ID]

> ⚠️ **Nota**: Reemplazar con los nombres reales de los integrantes del equipo.

---

## Descripción

Implementación de 5 ejercicios prácticos sobre el **Patrón de Diseño Singleton** en C++, desde implementaciones básicas hasta versiones avanzadas thread-safe.

---

## Estructura del Proyecto

```
prac07/
├── eje01/                    # Singleton básico (Configuración)
│   ├── Configuracion.h
│   ├── main.cpp
│   └── README.md
│
├── eje02/                    # Singleton con recursos compartidos (Logger)
│   ├── Logger.h
│   ├── main.cpp
│   └── README.md
│
├── eje03/                    # Conexión a base de datos
│   ├── ConexionBD.h
│   ├── main.cpp
│   └── README.md
│
├── eje04/                    # Control de juego
│   ├── ControlJuego.h
│   ├── main.cpp
│   └── README.md
│
├── eje05/                    # Singleton thread-safe
│   ├── LoggerThreadSafe.h
│   ├── ConexionBDThreadSafe.h
│   ├── main.cpp
│   └── README.md
│
└── README.md                 # Este archivo
```

---

## Ejercicios Implementados

### Ejercicio 01: Implementación Básica
- **Clase**: `Configuracion`
- **Función**: Almacenar configuraciones del sistema (idioma, zona horaria)
- **Compilación**: `g++ -std=c++11 main.cpp -o configuracion`

### Ejercicio 02: Recursos Compartidos
- **Clase**: `Logger`
- **Función**: Sistema de logging centralizado con archivo `bitacora.log`
- **Compilación**: `g++ -std=c++11 main.cpp -o logger`

### Ejercicio 03: Conexión a BD
- **Clase**: `ConexionBD`
- **Función**: Simulación de conexión única a base de datos
- **Compilación**: `g++ -std=c++11 main.cpp -o conexionbd -pthread`

### Ejercicio 04: Control de Juego
- **Clase**: `ControlJuego`
- **Función**: Estado global de juego (nivel, puntaje, vidas)
- **Compilación**: `g++ -std=c++11 main.cpp -o controljuego`

### Ejercicio 05: Thread-Safe
- **Clases**: `LoggerThreadSafe`, `ConexionBDThreadSafe`
- **Función**: Singleton seguro para entornos multihilo
- **Compilación**: `g++ -std=c++11 main.cpp -o singleton_threadsafe -pthread`

---

## Requisitos

- **Compilador**: g++ con soporte C++11 o superior
- **Sistema**: Linux/Unix (para threading)
- **Librerías**: Estándar de C++ (iostream, fstream, thread, mutex)

---

## Instrucciones de Ejecución

```bash
# Compilar y ejecutar cada ejercicio
cd prac07/eje01
g++ -std=c++11 main.cpp -o configuracion
./configuracion

cd ../eje02
g++ -std=c++11 main.cpp -o logger
./logger

cd ../eje03
g++ -std=c++11 main.cpp -o conexionbd -pthread
./conexionbd

cd ../eje04
g++ -std=c++11 main.cpp -o controljuego
./controljuego

cd ../eje05
g++ -std=c++11 main.cpp -o singleton_threadsafe -pthread
./singleton_threadsafe
```

---

## Cuestionario

### 1. ¿Qué desventajas tiene el patrón Singleton en pruebas unitarias?

- **Estado global compartido**: El estado persiste entre tests, causando interferencias
- **Difícil de mockear**: Los frameworks de testing no pueden sustituir fácilmente la instancia
- **Acoplamiento fuerte**: Las clases quedan acopladas al Singleton, dificultando el testing aislado
- **Dependencias ocultas**: No se declaran explícitamente, violando el principio de Dependency Injection
- **Tests en paralelo**: Imposible ejecutar tests concurrentemente si comparten el Singleton

**Solución**: Usar Dependency Injection o interfaces para permitir inyección de mocks.

---

### 2. ¿Cuándo no es recomendable usar Singleton?

- **Testing extensivo**: Proyectos con alta cobertura de tests unitarios o TDD
- **Múltiples contextos**: Cuando diferentes partes requieren configuraciones independientes
- **Arquitecturas distribuidas**: Microservicios, aplicaciones cloud con múltiples instancias
- **Necesidad de flexibilidad**: Requisitos que pueden cambiar a necesitar múltiples instancias
- **Resources pools**: Cuando se necesitan múltiples recursos limitados (usar Pool Pattern)
- **Violación de SOLID**: Si causa acoplamiento excesivo o dependencias ocultas

**Alternativas**: Dependency Injection, Factory Pattern, Service Locator, Module-level variables.

---

### 3. ¿Cómo se diferencia de una clase estática?

| Aspecto | Singleton | Clase Estática |
|---------|-----------|----------------|
| **Instanciación** | Crea UNA instancia | No se instancia |
| **Estado** | Estado de instancia | Solo variables de clase |
| **Herencia** | Puede heredar y ser heredado | Difícil heredar |
| **Polimorfismo** | Soporta polimorfismo | No soporta |
| **Lazy Loading** | Se crea cuando se necesita | Existe al cargar la clase |
| **Interfaces** | Puede implementar interfaces | No puede |
| **Ciclo de vida** | Controlable | Existe toda la ejecución |

**Singleton**: Para gestión de estado y recursos con control de instancia única.  
**Clase Estática**: Para funciones de utilidad sin estado (ej: StringUtils, MathUtils).

---

## Tecnologías Utilizadas

- **Lenguaje**: C++11
- **Librerías**:
  - `<iostream>`: Entrada/salida estándar
  - `<fstream>`: Manejo de archivos
  - `<thread>`: Soporte de hilos
  - `<mutex>`: Sincronización thread-safe
  - `<chrono>`: Temporizadores

---

## Referencias

- Gang of Four (GoF): Design Patterns - Elements of Reusable Object-Oriented Software
- C++ Concurrency in Action - Anthony Williams
- Effective C++ - Scott Meyers

---

**Fecha de Entrega**: 9 de diciembre de 2025  
**Curso**: Tópicos de Optimización  
**Práctica**: 07 - Patrón Singleton
