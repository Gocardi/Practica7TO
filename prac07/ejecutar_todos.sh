#!/bin/bash
# Script para probar todos los ejercicios de la práctica 07

echo "========================================================================"
echo "EJECUTANDO TODOS LOS EJERCICIOS DE LA PRÁCTICA 07"
echo "========================================================================"
echo ""

# Guardar el directorio actual
ORIGINAL_DIR=$(pwd)

# Ejercicio 01
echo "========================================================================"
echo "EJERCICIO 01: Singleton Básico (Configuración)"
echo "========================================================================"
cd "$ORIGINAL_DIR/prac07/eje01"
python3 configuracion.py
echo ""
echo "Presiona Enter para continuar..."
read

# Ejercicio 02
echo ""
echo "========================================================================"
echo "EJERCICIO 02: Logger con Singleton"
echo "========================================================================"
cd "$ORIGINAL_DIR/prac07/eje02"
python3 logger.py
echo ""
echo "Archivo de log generado: bitacora.log"
echo "Presiona Enter para continuar..."
read

# Ejercicio 03
echo ""
echo "========================================================================"
echo "EJERCICIO 03: Conexión BD con Singleton"
echo "========================================================================"
cd "$ORIGINAL_DIR/prac07/eje03"
python3 conexion_bd.py
echo ""
echo "Presiona Enter para continuar..."
read

# Ejercicio 04
echo ""
echo "========================================================================"
echo "EJERCICIO 04: Control de Juego con Singleton"
echo "========================================================================"
cd "$ORIGINAL_DIR/prac07/eje04"
python3 control_juego.py
echo ""
echo "Presiona Enter para continuar..."
read

# Ejercicio 05
echo ""
echo "========================================================================"
echo "EJERCICIO 05: Singleton Thread-Safe"
echo "========================================================================"
cd "$ORIGINAL_DIR/prac07/eje05"
python3 singleton_threadsafe.py
echo ""
echo "Archivo de log generado: bitacora_threadsafe.log"
echo ""

# Volver al directorio original
cd "$ORIGINAL_DIR"

echo "========================================================================"
echo "✅ TODOS LOS EJERCICIOS HAN SIDO EJECUTADOS"
echo "========================================================================"
echo ""
echo "Archivos generados:"
echo "  - prac07/eje02/bitacora.log"
echo "  - prac07/eje05/bitacora_threadsafe.log"
echo ""
echo "Revisa cada ejercicio para ver su funcionamiento detallado."
