# Ejercicio 02: Singleton con Recursos Compartidos (Logger)

## Descripción
Sistema de registro de eventos (logging) que utiliza el patrón Singleton para garantizar que todos los módulos de la aplicación escriban en el mismo archivo de log.

## Objetivo
Implementar un logger único que centralice el registro de eventos, errores y mensajes de depuración desde múltiples módulos.

## Implementación

### Características Principales
- Instancia única del logger
- Escritura sincronizada en archivo `bitacora.log`
- Niveles de log: INFO, WARNING, ERROR, DEBUG
- Timestamp automático en cada registro
- Múltiples módulos usando el mismo recurso

### Estructura
```
Logger (Singleton)
├── archivoLog
└── métodos:
    ├── obtenerInstancia()
    ├── log(mensaje, nivel)
    ├── info()
    ├── warning()
    ├── error()
    └── debug()
```

### Módulos de Demostración
- **ModuloUsuarios**: Gestión de usuarios
- **ModuloAutenticacion**: Validación de credenciales
- **ModuloBaseDatos**: Operaciones de BD

## Compilación y Ejecución

```bash
g++ -std=c++11 main.cpp -o logger
./logger
```

## Resultado Esperado
- Todas las instancias del logger tienen la misma dirección de memoria
- Todos los módulos escriben en `bitacora.log`
- Los mensajes incluyen timestamp y nivel de severidad
