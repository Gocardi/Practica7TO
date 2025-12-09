from datetime import datetime
import os


class Logger:
    """
    Clase Singleton para registrar mensajes de log en un archivo.
    Garantiza que solo exista una instancia del logger en toda la aplicación.
    """
    _instancia = None
    _archivo_log = "bitacora.log"
    
    def __new__(cls):
        """
        Sobrescribe __new__ para controlar la creación de instancias.
        Si ya existe una instancia, la retorna; si no, crea una nueva.
        """
        if cls._instancia is None:
            cls._instancia = super(Logger, cls).__new__(cls)
            cls._instancia._inicializado = False
        return cls._instancia
    
    def __init__(self):
        """
        Inicializa el logger solo la primera vez.
        """
        if not self._inicializado:
            self._inicializado = True
            # Crear o abrir el archivo de log
            with open(self._archivo_log, 'a', encoding='utf-8') as f:
                f.write("\n" + "=" * 80 + "\n")
                f.write(f"NUEVA SESIÓN DE LOG - {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
                f.write("=" * 80 + "\n")
    
    def log(self, mensaje, nivel="INFO"):
        """
        Registra un mensaje en el archivo de log con la fecha y hora actual.
        
        Args:
            mensaje (str): El mensaje a registrar
            nivel (str): Nivel del log (INFO, WARNING, ERROR, DEBUG)
        """
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        linea_log = f"[{timestamp}] [{nivel}] {mensaje}\n"
        
        # Escribir en el archivo
        with open(self._archivo_log, 'a', encoding='utf-8') as f:
            f.write(linea_log)
        
        # También imprimir en consola
        print(linea_log.strip())
    
    def info(self, mensaje):
        """Registra un mensaje de información"""
        self.log(mensaje, "INFO")
    
    def warning(self, mensaje):
        """Registra un mensaje de advertencia"""
        self.log(mensaje, "WARNING")
    
    def error(self, mensaje):
        """Registra un mensaje de error"""
        self.log(mensaje, "ERROR")
    
    def debug(self, mensaje):
        """Registra un mensaje de depuración"""
        self.log(mensaje, "DEBUG")
    
    def leer_log(self):
        """Lee y muestra el contenido del archivo de log"""
        if os.path.exists(self._archivo_log):
            with open(self._archivo_log, 'r', encoding='utf-8') as f:
                return f.read()
        return "El archivo de log no existe aún."


# Simulación de diferentes módulos del sistema
class ModuloUsuarios:
    """Simula un módulo que gestiona usuarios"""
    def __init__(self):
        self.logger = Logger()
    
    def crear_usuario(self, nombre):
        self.logger.info(f"ModuloUsuarios: Creando usuario '{nombre}'")
        self.logger.debug(f"ModuloUsuarios: Validando datos del usuario '{nombre}'")
        self.logger.info(f"ModuloUsuarios: Usuario '{nombre}' creado exitosamente")


class ModuloAutenticacion:
    """Simula un módulo de autenticación"""
    def __init__(self):
        self.logger = Logger()
    
    def login(self, usuario):
        self.logger.info(f"ModuloAutenticacion: Intento de login del usuario '{usuario}'")
        if usuario == "admin":
            self.logger.info(f"ModuloAutenticacion: Login exitoso para '{usuario}'")
        else:
            self.logger.warning(f"ModuloAutenticacion: Credenciales inválidas para '{usuario}'")


class ModuloBaseDatos:
    """Simula un módulo de base de datos"""
    def __init__(self):
        self.logger = Logger()
    
    def conectar(self):
        self.logger.info("ModuloBaseDatos: Iniciando conexión a la base de datos")
        self.logger.debug("ModuloBaseDatos: Verificando credenciales...")
        self.logger.info("ModuloBaseDatos: Conexión establecida exitosamente")
    
    def consultar(self, query):
        self.logger.debug(f"ModuloBaseDatos: Ejecutando query: {query}")
        self.logger.error("ModuloBaseDatos: Error de sintaxis en la query")


if __name__ == "__main__":
    print("=" * 80)
    print("DEMOSTRACIÓN DEL PATRÓN SINGLETON - LOGGER")
    print("=" * 80)
    
    # Crear instancias de logger desde diferentes puntos
    logger1 = Logger()
    logger2 = Logger()
    logger3 = Logger()
    
    print(f"\nlogger1 ID: {id(logger1)}")
    print(f"logger2 ID: {id(logger2)}")
    print(f"logger3 ID: {id(logger3)}")
    print(f"\nTodas las instancias son iguales: {logger1 is logger2 is logger3}")
    
    print("\n" + "=" * 80)
    print("REGISTRANDO EVENTOS DESDE DIFERENTES MÓDULOS")
    print("=" * 80 + "\n")
    
    # Simular uso desde diferentes módulos
    modulo_usuarios = ModuloUsuarios()
    modulo_usuarios.crear_usuario("Juan Pérez")
    
    print()
    modulo_auth = ModuloAutenticacion()
    modulo_auth.login("admin")
    modulo_auth.login("juan")
    
    print()
    modulo_bd = ModuloBaseDatos()
    modulo_bd.conectar()
    modulo_bd.consultar("SELECT * FROM usuarios WHERE id = 1")
    
    print()
    # Usar el logger directamente
    logger_directo = Logger()
    logger_directo.info("Mensaje directo desde el main")
    logger_directo.warning("Esta es una advertencia importante")
    logger_directo.error("Se ha detectado un error crítico")
    
    print("\n" + "=" * 80)
    print("VERIFICACIÓN: Todos los módulos usan el mismo archivo de log")
    print("=" * 80)
    print(f"Archivo de log: {Logger._archivo_log}")
    print(f"Verifica el contenido del archivo '{Logger._archivo_log}' para confirmar.")
