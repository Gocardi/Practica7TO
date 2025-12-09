# Makefile para compilar todos los ejercicios de Singleton
# Práctica 07 - Tópicos de Optimización

CXX = g++
CXXFLAGS = -std=c++11 -Wall
THREAD_FLAGS = -pthread

# Directorios
EJE01_DIR = eje01
EJE02_DIR = eje02
EJE03_DIR = eje03
EJE04_DIR = eje04
EJE05_DIR = eje05

# Ejecutables
EJE01_TARGET = $(EJE01_DIR)/configuracion
EJE02_TARGET = $(EJE02_DIR)/logger
EJE03_TARGET = $(EJE03_DIR)/conexionbd
EJE04_TARGET = $(EJE04_DIR)/controljuego
EJE05_TARGET = $(EJE05_DIR)/singleton_threadsafe

# Regla principal: compilar todos
all: eje01 eje02 eje03 eje04 eje05
	@echo "✅ Todos los ejercicios compilados exitosamente"

# Ejercicio 01
eje01:
	@echo "🔨 Compilando Ejercicio 01: Configuración..."
	$(CXX) $(CXXFLAGS) $(EJE01_DIR)/main.cpp -o $(EJE01_TARGET)
	@echo "✅ Ejercicio 01 compilado"

# Ejercicio 02
eje02:
	@echo "🔨 Compilando Ejercicio 02: Logger..."
	$(CXX) $(CXXFLAGS) $(EJE02_DIR)/main.cpp -o $(EJE02_TARGET)
	@echo "✅ Ejercicio 02 compilado"

# Ejercicio 03
eje03:
	@echo "🔨 Compilando Ejercicio 03: ConexionBD..."
	$(CXX) $(CXXFLAGS) $(THREAD_FLAGS) $(EJE03_DIR)/main.cpp -o $(EJE03_TARGET)
	@echo "✅ Ejercicio 03 compilado"

# Ejercicio 04
eje04:
	@echo "🔨 Compilando Ejercicio 04: ControlJuego..."
	$(CXX) $(CXXFLAGS) $(EJE04_DIR)/main.cpp -o $(EJE04_TARGET)
	@echo "✅ Ejercicio 04 compilado"

# Ejercicio 05
eje05:
	@echo "🔨 Compilando Ejercicio 05: Singleton Thread-Safe..."
	$(CXX) $(CXXFLAGS) $(THREAD_FLAGS) $(EJE05_DIR)/main.cpp -o $(EJE05_TARGET)
	@echo "✅ Ejercicio 05 compilado"

# Ejecutar todos los ejercicios
run-all: all
	@echo ""
	@echo "═══════════════════════════════════════════════════════════"
	@echo "EJECUTANDO EJERCICIO 01: CONFIGURACIÓN"
	@echo "═══════════════════════════════════════════════════════════"
	@./$(EJE01_TARGET)
	@echo ""
	@echo "═══════════════════════════════════════════════════════════"
	@echo "EJECUTANDO EJERCICIO 02: LOGGER"
	@echo "═══════════════════════════════════════════════════════════"
	@./$(EJE02_TARGET)
	@echo ""
	@echo "═══════════════════════════════════════════════════════════"
	@echo "EJECUTANDO EJERCICIO 03: CONEXIÓN BD"
	@echo "═══════════════════════════════════════════════════════════"
	@./$(EJE03_TARGET)
	@echo ""
	@echo "═══════════════════════════════════════════════════════════"
	@echo "EJECUTANDO EJERCICIO 04: CONTROL JUEGO"
	@echo "═══════════════════════════════════════════════════════════"
	@./$(EJE04_TARGET)
	@echo ""
	@echo "═══════════════════════════════════════════════════════════"
	@echo "EJECUTANDO EJERCICIO 05: SINGLETON THREAD-SAFE"
	@echo "═══════════════════════════════════════════════════════════"
	@./$(EJE05_TARGET)

# Ejecutar ejercicios individuales
run-eje01: eje01
	@./$(EJE01_TARGET)

run-eje02: eje02
	@./$(EJE02_TARGET)

run-eje03: eje03
	@./$(EJE03_TARGET)

run-eje04: eje04
	@./$(EJE04_TARGET)

run-eje05: eje05
	@./$(EJE05_TARGET)

# Limpiar archivos compilados y logs
clean:
	@echo "🧹 Limpiando archivos compilados y logs..."
	@rm -f $(EJE01_TARGET) $(EJE02_TARGET) $(EJE03_TARGET) $(EJE04_TARGET) $(EJE05_TARGET)
	@rm -f $(EJE02_DIR)/*.log $(EJE05_DIR)/*.log
	@echo "✅ Limpieza completada"

# Limpiar solo ejecutables
clean-bin:
	@echo "🧹 Limpiando ejecutables..."
	@rm -f $(EJE01_TARGET) $(EJE02_TARGET) $(EJE03_TARGET) $(EJE04_TARGET) $(EJE05_TARGET)
	@echo "✅ Ejecutables eliminados"

# Limpiar solo logs
clean-logs:
	@echo "🧹 Limpiando archivos de log..."
	@rm -f $(EJE02_DIR)/*.log $(EJE05_DIR)/*.log
	@echo "✅ Logs eliminados"

# Ayuda
help:
	@echo "Makefile - Práctica 07: Patrón Singleton"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make              - Compila todos los ejercicios"
	@echo "  make all          - Compila todos los ejercicios"
	@echo "  make eje01        - Compila solo el ejercicio 01"
	@echo "  make eje02        - Compila solo el ejercicio 02"
	@echo "  make eje03        - Compila solo el ejercicio 03"
	@echo "  make eje04        - Compila solo el ejercicio 04"
	@echo "  make eje05        - Compila solo el ejercicio 05"
	@echo ""
	@echo "  make run-all      - Compila y ejecuta todos los ejercicios"
	@echo "  make run-eje01    - Compila y ejecuta el ejercicio 01"
	@echo "  make run-eje02    - Compila y ejecuta el ejercicio 02"
	@echo "  make run-eje03    - Compila y ejecuta el ejercicio 03"
	@echo "  make run-eje04    - Compila y ejecuta el ejercicio 04"
	@echo "  make run-eje05    - Compila y ejecuta el ejercicio 05"
	@echo ""
	@echo "  make clean        - Elimina ejecutables y archivos de log"
	@echo "  make clean-bin    - Elimina solo ejecutables"
	@echo "  make clean-logs   - Elimina solo archivos de log"
	@echo "  make help         - Muestra esta ayuda"

.PHONY: all eje01 eje02 eje03 eje04 eje05 run-all run-eje01 run-eje02 run-eje03 run-eje04 run-eje05 clean clean-bin clean-logs help
