# Ejercicio 03: Conexión Simulada a Base de Datos

## Descripción
Simulación de una conexión a base de datos utilizando el patrón Singleton para garantizar que solo exista una conexión activa en toda la aplicación.

## Objetivo
Implementar una clase `ConexionBD` que controle el acceso a la base de datos, evitando múltiples conexiones simultáneas que consumen recursos innecesarios.

## Implementación

### Características Principales
- Instancia única de conexión
- Control de estado (conectado/desconectado)
- Métodos de gestión: conectar(), desconectar(), estado()
- Ejecución de consultas con validación de conexión
- Contador de consultas ejecutadas
- Configuración de parámetros de conexión

### Estructura
```
ConexionBD (Singleton)
├── conectado (bool)
├── host, puerto, baseDatos, usuario
├── consultasEjecutadas
└── métodos:
    ├── obtenerInstancia()
    ├── conectar()
    ├── desconectar()
    ├── estado()
    ├── ejecutarConsulta()
    └── configurar()
```

### Clases de Demostración
- **RepositorioUsuarios**: Acceso a tabla de usuarios
- **RepositorioProductos**: Acceso a tabla de productos

## Compilación y Ejecución

```bash
g++ -std=c++11 main.cpp -o conexionbd -pthread
./conexionbd
```

## Resultado Esperado
- Solo se crea una instancia de la conexión
- Todas las referencias tienen la misma dirección de memoria
- El estado de conexión es compartido entre todos los módulos
- Las consultas se cuentan de forma centralizada
