# Ejercicio 01: Implementación Básica del Singleton

## Descripción
Implementación de una clase `Configuracion` que almacena configuraciones del sistema (idioma y zona horaria) utilizando el patrón Singleton.

## Objetivo
Garantizar que solo exista una instancia de la clase de configuración en toda la aplicación.

## Implementación

### Características Principales
- Constructor privado para prevenir instanciación externa
- Método estático `obtenerInstancia()` para acceso controlado
- Eliminación de constructores de copia y asignación
- Gestión de memoria con método `destruirInstancia()`

### Estructura
```
Configuracion (Singleton)
├── instancia (static)
├── idioma
├── zonaHoraria
└── métodos:
    ├── obtenerInstancia()
    ├── setIdioma()
    ├── setZonaHoraria()
    └── mostrarConfiguracion()
```

## Compilación y Ejecución

```bash
g++ -std=c++11 main.cpp -o configuracion
./configuracion
```

## Resultado Esperado
- Múltiples referencias apuntan a la misma dirección de memoria
- Los cambios desde cualquier referencia se reflejan en todas
- Solo existe una configuración en memoria
