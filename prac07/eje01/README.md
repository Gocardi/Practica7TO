# Ejercicio 01: Implementación Directa del Singleton

## Objetivo
Crear una clase `Configuracion` que almacene las configuraciones generales del sistema (idioma y zona horaria) asegurando que solo exista una instancia de esta clase.

## Descripción del Problema
En muchas aplicaciones necesitamos mantener configuraciones globales que deben ser consistentes en toda la aplicación. El patrón Singleton garantiza que solo exista una única instancia de la clase de configuración.

## Implementación

### Clase Configuracion
- **Atributo de clase `_instancia`**: Almacena la única instancia de la clase.
- **Método `__new__`**: Sobrescrito para controlar la creación de instancias.
- **Atributos de instancia**:
  - `idioma`: Idioma del sistema (por defecto "Español")
  - `zona_horaria`: Zona horaria del sistema (por defecto "UTC-6")

### Métodos
- `set_idioma(idioma)`: Establece el idioma del sistema
- `set_zona_horaria(zona)`: Establece la zona horaria
- `mostrar_configuracion()`: Muestra los valores actuales de configuración

## Características del Patrón Singleton Implementado
1. **Control de instancia**: El método `__new__` verifica si ya existe una instancia antes de crear una nueva.
2. **Inicialización única**: Los valores por defecto solo se establecen cuando se crea la primera instancia.
3. **Acceso global**: Cualquier parte del código puede acceder a la misma instancia.

## Ejecución

```bash
python configuracion.py
```

## Resultado Esperado
El programa demuestra que:
- Múltiples "instancias" tienen el mismo ID de objeto
- Los cambios realizados desde cualquier referencia se reflejan en todas
- Solo existe una configuración en memoria

## Ventajas de este Enfoque
- Garantiza consistencia en la configuración
- Evita duplicación de datos
- Fácil acceso desde cualquier parte del código
- Control centralizado de configuraciones
