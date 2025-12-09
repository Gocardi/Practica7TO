# Ejercicio 03: Conexión Simulada a Base de Datos (Singleton)

## Objetivo
Crear una clase `ConexionBD` que simule la conexión a una base de datos, garantizando que solo exista una conexión activa en toda la aplicación mediante el patrón Singleton.

## Descripción del Problema
En aplicaciones reales, mantener múltiples conexiones a una base de datos consume recursos innecesarios y puede causar problemas de:
- **Rendimiento**: Cada conexión consume memoria y recursos del servidor
- **Concurrencia**: Múltiples conexiones pueden causar conflictos de bloqueo
- **Costo**: Algunos servicios de BD cobran por conexión activa
- **Complejidad**: Dificulta el control del estado de las transacciones

El patrón Singleton asegura que todos los módulos de la aplicación usen la misma conexión.

## Implementación

### Clase ConexionBD
- **Atributo de clase `_instancia`**: Almacena la única instancia de la conexión
- **Atributos de configuración**:
  - `_host`: Servidor de la base de datos (por defecto "localhost")
  - `_puerto`: Puerto de conexión (por defecto 5432)
  - `_base_datos`: Nombre de la base de datos
  - `_usuario`: Usuario de conexión
- **Estado de la conexión**:
  - `_conectado`: Indica si hay una conexión activa
  - `_tiempo_conexion`: Timestamp de cuando se estableció la conexión
  - `_consultas_ejecutadas`: Contador de consultas realizadas

### Métodos Principales

#### conectar()
- Establece la conexión a la base de datos
- Verifica que no haya una conexión activa previa
- Simula el proceso de conexión (delay de 1 segundo)
- Registra el timestamp de conexión

#### desconectar()
- Cierra la conexión activa
- Muestra estadísticas (tiempo activo, consultas ejecutadas)
- Libera recursos

#### estado()
- Muestra información completa del estado de la conexión
- Indica si está conectada o desconectada
- Muestra configuración y estadísticas

#### ejecutar_consulta(consulta)
- Simula la ejecución de una consulta SQL
- Valida que exista una conexión activa
- Incrementa el contador de consultas

#### configurar(host, puerto, base_datos, usuario)
- Permite cambiar la configuración de conexión
- Solo funciona si la conexión está desconectada

## Características del Patrón Singleton Implementado

1. **Instancia única**: Solo puede existir una conexión en toda la aplicación
2. **Reutilización**: Nuevas referencias obtienen la instancia existente
3. **Estado compartido**: Todos los módulos ven el mismo estado de conexión
4. **Control de recursos**: Evita conexiones duplicadas e innecesarias
5. **Feedback visual**: Mensajes claros sobre creación/reutilización de instancia

## Clases de Demostración

### RepositorioUsuarios
Simula un módulo que accede a la tabla de usuarios. Obtiene su propia referencia a ConexionBD, pero recibe la misma instancia.

### RepositorioProductos
Simula un módulo que accede a la tabla de productos. También usa la misma instancia de ConexionBD.

## Ejecución

```bash
python conexion_bd.py
```

## Resultado Esperado

El programa demuestra:
1. **Creación única**: La primera llamada crea la instancia, las siguientes la reutilizan
2. **IDs idénticos**: Todas las referencias tienen el mismo ID de objeto
3. **Estado compartido**: Conectar desde una referencia afecta a todas
4. **Contadores compartidos**: Las consultas se cuentan globalmente
5. **Módulos integrados**: Diferentes clases acceden a la misma conexión

## Flujo de Ejecución

```
1. Crear tres referencias → Solo se crea una instancia
2. Verificar que todas son idénticas (mismo ID)
3. Conectar desde conexion1
4. Ejecutar consultas desde diferentes referencias
5. Usar la conexión desde RepositorioUsuarios y RepositorioProductos
6. Verificar que todos comparten el mismo contador
7. Desconectar y mostrar estadísticas
```

## Ventajas de este Enfoque

- ✅ **Eficiencia de recursos**: Una sola conexión para toda la aplicación
- ✅ **Consistencia**: Todos los módulos ven el mismo estado
- ✅ **Control centralizado**: Fácil gestionar el ciclo de vida de la conexión
- ✅ **Evita errores**: Imposible tener conexiones múltiples accidentales
- ✅ **Simplifica testing**: Un solo punto de control para mockear
- ✅ **Trazabilidad**: Estadísticas centralizadas de uso

## Casos de Uso Reales

- Conexiones a bases de datos (PostgreSQL, MySQL, MongoDB)
- Pools de conexiones
- Conexiones a APIs externas
- Clientes de caché (Redis, Memcached)
- Conexiones a servicios de mensajería (RabbitMQ, Kafka)
