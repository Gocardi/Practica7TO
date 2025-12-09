# Ejercicio 02: Singleton con Recursos Compartidos (Logger)

## Objetivo
Implementar una clase `Logger` que registre mensajes de log en un archivo de texto (`bitacora.log`), asegurando que solo exista una instancia del logger en toda la aplicación.

## Descripción del Problema
En aplicaciones complejas, múltiples módulos necesitan registrar eventos, errores y mensajes de depuración. Es crucial que todos estos módulos escriban en el mismo archivo de log de manera consistente, sin duplicar instancias del logger ni correr el riesgo de corrupción de datos.

## Implementación

### Clase Logger
- **Atributo de clase `_instancia`**: Almacena la única instancia del logger.
- **Atributo de clase `_archivo_log`**: Nombre del archivo donde se guardan los logs ("bitacora.log").
- **Control de inicialización**: Usa `_inicializado` para evitar reinicializar el logger.

### Métodos Principales
- `log(mensaje, nivel)`: Registra un mensaje con timestamp y nivel especificado
- `info(mensaje)`: Registra mensaje de información
- `warning(mensaje)`: Registra mensaje de advertencia
- `error(mensaje)`: Registra mensaje de error
- `debug(mensaje)`: Registra mensaje de depuración
- `leer_log()`: Lee y retorna el contenido del archivo de log

## Características del Patrón Singleton Implementado
1. **Instancia única**: Solo existe un logger en toda la aplicación
2. **Recurso compartido**: Todos los módulos escriben en el mismo archivo
3. **Thread-safe básico**: Cada escritura se realiza de forma atómica
4. **Timestamp automático**: Cada mensaje incluye fecha y hora
5. **Niveles de log**: INFO, WARNING, ERROR, DEBUG

## Clases de Demostración
El ejemplo incluye tres módulos simulados que usan el mismo logger:
- **ModuloUsuarios**: Gestión de usuarios
- **ModuloAutenticacion**: Autenticación de usuarios
- **ModuloBaseDatos**: Operaciones de base de datos

## Ejecución

```bash
python logger.py
```

## Resultado Esperado
1. Todas las instancias de Logger tienen el mismo ID de objeto
2. Los mensajes de todos los módulos se escriben en `bitacora.log`
3. Cada mensaje incluye timestamp y nivel de severidad
4. El archivo se puede inspeccionar para verificar que todos los módulos lo usan

## Archivo de Log (bitacora.log)
El archivo generado tiene el formato:
```
================================================================================
NUEVA SESIÓN DE LOG - 2025-12-08 15:30:45
================================================================================
[2025-12-08 15:30:45] [INFO] ModuloUsuarios: Creando usuario 'Juan Pérez'
[2025-12-08 15:30:45] [DEBUG] ModuloUsuarios: Validando datos del usuario...
[2025-12-08 15:30:46] [WARNING] ModuloAutenticacion: Credenciales inválidas
```

## Ventajas de este Enfoque
- **Centralización**: Un solo punto de control para el logging
- **Consistencia**: Formato uniforme en todos los logs
- **Eficiencia**: No se duplican recursos ni archivos
- **Trazabilidad**: Todos los eventos en un mismo lugar cronológico
- **Mantenibilidad**: Fácil modificar el comportamiento del logging
