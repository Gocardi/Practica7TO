import threading
import time
from datetime import datetime


class LoggerThreadSafe:
    """
    Clase Singleton thread-safe para registrar mensajes de log.
    Usa double-checked locking para garantizar una única instancia en entornos multihilo.
    """
    _instancia = None
    _lock = threading.Lock()  # Lock para proteger la creación de instancia
    _archivo_log = "bitacora_threadsafe.log"
    
    def __new__(cls):
        """
        Implementa double-checked locking para thread-safety.
        Primera verificación sin lock (rápida), segunda con lock (segura).
        """
        # Primera verificación (sin lock, más rápida)
        if cls._instancia is None:
            # Adquirir lock solo si la instancia no existe
            with cls._lock:
                # Segunda verificación (con lock, para evitar race conditions)
                if cls._instancia is None:
                    thread_id = threading.current_thread().name
                    print(f"🔧 [{thread_id}] Creando nueva instancia de LoggerThreadSafe...")
                    cls._instancia = super(LoggerThreadSafe, cls).__new__(cls)
                    cls._instancia._inicializado = False
                    cls._instancia._lock_escritura = threading.Lock()  # Lock para escritura de archivo
        
        return cls._instancia
    
    def __init__(self):
        """
        Inicializa el logger solo la primera vez de forma thread-safe.
        """
        if not self._inicializado:
            with self._lock_escritura:
                if not self._inicializado:
                    self._inicializado = True
                    with open(self._archivo_log, 'a', encoding='utf-8') as f:
                        f.write("\n" + "=" * 80 + "\n")
                        f.write(f"NUEVA SESIÓN (THREAD-SAFE) - {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
                        f.write("=" * 80 + "\n")
    
    def log(self, mensaje, nivel="INFO"):
        """
        Registra un mensaje de forma thread-safe.
        
        Args:
            mensaje (str): El mensaje a registrar
            nivel (str): Nivel del log (INFO, WARNING, ERROR, DEBUG)
        """
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]
        thread_name = threading.current_thread().name
        linea_log = f"[{timestamp}] [{nivel}] [Thread: {thread_name}] {mensaje}\n"
        
        # Proteger la escritura al archivo con un lock
        with self._lock_escritura:
            with open(self._archivo_log, 'a', encoding='utf-8') as f:
                f.write(linea_log)
            print(linea_log.strip())


class ConexionBDThreadSafe:
    """
    Clase Singleton thread-safe que simula una conexión a base de datos.
    Implementa double-checked locking para seguridad en entornos multihilo.
    """
    _instancia = None
    _lock = threading.Lock()
    
    def __new__(cls):
        """
        Implementa double-checked locking para thread-safety.
        """
        # Primera verificación sin lock
        if cls._instancia is None:
            with cls._lock:
                # Segunda verificación con lock
                if cls._instancia is None:
                    thread_id = threading.current_thread().name
                    print(f"🔧 [{thread_id}] Creando nueva instancia de ConexionBDThreadSafe...")
                    cls._instancia = super(ConexionBDThreadSafe, cls).__new__(cls)
                    cls._instancia._inicializado = False
        
        return cls._instancia
    
    def __init__(self):
        """
        Inicializa la conexión de forma thread-safe.
        """
        if not self._inicializado:
            with self._lock:
                if not self._inicializado:
                    self._inicializado = True
                    self._conectado = False
                    self._lock_conexion = threading.Lock()
                    self._consultas_ejecutadas = 0
                    self._lock_contador = threading.Lock()
                    print("✅ Instancia de ConexionBDThreadSafe inicializada")
    
    def conectar(self):
        """Establece la conexión de forma thread-safe"""
        with self._lock_conexion:
            if self._conectado:
                thread_name = threading.current_thread().name
                print(f"⚠️  [{thread_name}] La conexión ya está activa")
                return False
            
            thread_name = threading.current_thread().name
            print(f"🔌 [{thread_name}] Estableciendo conexión...")
            time.sleep(0.5)  # Simular tiempo de conexión
            self._conectado = True
            print(f"✅ [{thread_name}] Conexión establecida")
            return True
    
    def ejecutar_consulta(self, consulta):
        """Ejecuta una consulta de forma thread-safe"""
        if not self._conectado:
            thread_name = threading.current_thread().name
            print(f"❌ [{thread_name}] No hay conexión activa")
            return None
        
        thread_name = threading.current_thread().name
        print(f"📊 [{thread_name}] Ejecutando: {consulta}")
        time.sleep(0.2)  # Simular tiempo de ejecución
        
        # Incrementar contador de forma thread-safe
        with self._lock_contador:
            self._consultas_ejecutadas += 1
            num_consulta = self._consultas_ejecutadas
        
        print(f"✅ [{thread_name}] Consulta #{num_consulta} completada")
        return f"Resultado #{num_consulta}"
    
    def get_estadisticas(self):
        """Obtiene estadísticas de forma thread-safe"""
        with self._lock_contador:
            return {
                'conectado': self._conectado,
                'consultas': self._consultas_ejecutadas
            }


# Funciones para pruebas multihilo
def prueba_logger_concurrente(id_trabajador, num_mensajes):
    """
    Función que simula múltiples hilos intentando crear y usar el logger.
    
    Args:
        id_trabajador (int): ID del trabajador
        num_mensajes (int): Número de mensajes a registrar
    """
    # Simular diferentes tiempos de inicio
    time.sleep(id_trabajador * 0.1)
    
    # Cada hilo intenta crear su "propia" instancia
    logger = LoggerThreadSafe()
    print(f"👤 Trabajador {id_trabajador} obtuvo logger con ID: {id(logger)}")
    
    # Registrar múltiples mensajes
    for i in range(num_mensajes):
        logger.log(f"Trabajador {id_trabajador} - Mensaje {i+1}", "INFO")
        time.sleep(0.05)  # Pequeña pausa entre mensajes


def prueba_bd_concurrente(id_trabajador, num_consultas):
    """
    Función que simula múltiples hilos usando la conexión a BD.
    
    Args:
        id_trabajador (int): ID del trabajador
        num_consultas (int): Número de consultas a ejecutar
    """
    # Simular diferentes tiempos de inicio
    time.sleep(id_trabajador * 0.1)
    
    # Cada hilo intenta obtener la conexión
    bd = ConexionBDThreadSafe()
    print(f"👤 Trabajador {id_trabajador} obtuvo BD con ID: {id(bd)}")
    
    # Ejecutar consultas
    for i in range(num_consultas):
        bd.ejecutar_consulta(f"SELECT * FROM tabla_{id_trabajador} WHERE id={i}")
        time.sleep(0.1)


if __name__ == "__main__":
    print("=" * 80)
    print("DEMOSTRACIÓN DE SINGLETON THREAD-SAFE")
    print("=" * 80)
    
    # ========== PRUEBA 1: Logger Thread-Safe ==========
    print("\n" + "=" * 80)
    print("PRUEBA 1: LOGGER CON MÚLTIPLES HILOS")
    print("=" * 80)
    
    num_hilos = 5
    mensajes_por_hilo = 3
    hilos_logger = []
    
    print(f"\n🚀 Lanzando {num_hilos} hilos para probar el logger...")
    
    for i in range(num_hilos):
        hilo = threading.Thread(
            target=prueba_logger_concurrente,
            args=(i+1, mensajes_por_hilo),
            name=f"LogWorker-{i+1}"
        )
        hilos_logger.append(hilo)
        hilo.start()
    
    # Esperar a que todos los hilos terminen
    for hilo in hilos_logger:
        hilo.join()
    
    print("\n✅ Todos los hilos de logger han terminado")
    print(f"📄 Verifica el archivo '{LoggerThreadSafe._archivo_log}' para ver los logs")
    
    # ========== PRUEBA 2: Conexión BD Thread-Safe ==========
    print("\n" + "=" * 80)
    print("PRUEBA 2: CONEXIÓN BD CON MÚLTIPLES HILOS")
    print("=" * 80)
    
    # Primero conectar desde el hilo principal
    bd_principal = ConexionBDThreadSafe()
    bd_principal.conectar()
    
    num_hilos_bd = 4
    consultas_por_hilo = 2
    hilos_bd = []
    
    print(f"\n🚀 Lanzando {num_hilos_bd} hilos para ejecutar consultas...")
    
    for i in range(num_hilos_bd):
        hilo = threading.Thread(
            target=prueba_bd_concurrente,
            args=(i+1, consultas_por_hilo),
            name=f"DBWorker-{i+1}"
        )
        hilos_bd.append(hilo)
        hilo.start()
    
    # Esperar a que todos los hilos terminen
    for hilo in hilos_bd:
        hilo.join()
    
    print("\n✅ Todos los hilos de BD han terminado")
    
    # Mostrar estadísticas finales
    stats = bd_principal.get_estadisticas()
    print("\n📊 ESTADÍSTICAS FINALES:")
    print(f"   Conexión activa: {stats['conectado']}")
    print(f"   Total de consultas ejecutadas: {stats['consultas']}")
    
    # ========== VERIFICACIÓN FINAL ==========
    print("\n" + "=" * 80)
    print("VERIFICACIÓN DE INSTANCIA ÚNICA")
    print("=" * 80)
    
    # Crear múltiples referencias desde el hilo principal
    logger1 = LoggerThreadSafe()
    logger2 = LoggerThreadSafe()
    logger3 = LoggerThreadSafe()
    
    bd1 = ConexionBDThreadSafe()
    bd2 = ConexionBDThreadSafe()
    
    print(f"\n📋 IDs de Logger:")
    print(f"   logger1: {id(logger1)}")
    print(f"   logger2: {id(logger2)}")
    print(f"   logger3: {id(logger3)}")
    print(f"   ✅ Todas son iguales: {logger1 is logger2 is logger3}")
    
    print(f"\n📋 IDs de ConexionBD:")
    print(f"   bd1: {id(bd1)}")
    print(f"   bd2: {id(bd2)}")
    print(f"   ✅ Ambas son iguales: {bd1 is bd2}")
    
    print("\n" + "=" * 80)
    print("CONCLUSIÓN")
    print("=" * 80)
    print("✅ El patrón Singleton funciona correctamente en entornos multihilo")
    print("✅ Double-checked locking previene race conditions")
    print("✅ Locks individuales protegen operaciones críticas")
    print("✅ Solo se crea una instancia incluso con múltiples hilos simultáneos")
    print("=" * 80)
