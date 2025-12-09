import time
from datetime import datetime


class ConexionBD:
    """
    Clase Singleton que simula una conexión a base de datos.
    Garantiza que solo exista una conexión activa en toda la aplicación.
    """
    _instancia = None
    
    def __new__(cls):
        """
        Sobrescribe __new__ para controlar la creación de instancias.
        Si ya existe una instancia, la retorna; si no, crea una nueva.
        """
        if cls._instancia is None:
            print("🔧 Creando nueva instancia de ConexionBD...")
            cls._instancia = super(ConexionBD, cls).__new__(cls)
            cls._instancia._inicializado = False
        else:
            print("♻️  Reutilizando instancia existente de ConexionBD...")
        return cls._instancia
    
    def __init__(self):
        """
        Inicializa la conexión solo la primera vez.
        """
        if not self._inicializado:
            self._inicializado = True
            self._conectado = False
            self._host = "localhost"
            self._puerto = 5432
            self._base_datos = "mi_aplicacion"
            self._usuario = "admin"
            self._tiempo_conexion = None
            self._consultas_ejecutadas = 0
            print("✅ Instancia de ConexionBD inicializada correctamente")
    
    def conectar(self):
        """
        Simula el establecimiento de una conexión a la base de datos.
        """
        if self._conectado:
            print("⚠️  Ya existe una conexión activa")
            return False
        
        print("\n🔌 Intentando conectar a la base de datos...")
        print(f"   Host: {self._host}")
        print(f"   Puerto: {self._puerto}")
        print(f"   Base de datos: {self._base_datos}")
        print(f"   Usuario: {self._usuario}")
        
        # Simular tiempo de conexión
        time.sleep(1)
        
        self._conectado = True
        self._tiempo_conexion = datetime.now()
        print("✅ Conexión establecida exitosamente")
        return True
    
    def desconectar(self):
        """
        Simula el cierre de la conexión a la base de datos.
        """
        if not self._conectado:
            print("⚠️  No hay conexión activa para cerrar")
            return False
        
        print("\n🔌 Cerrando conexión a la base de datos...")
        
        # Simular tiempo de desconexión
        time.sleep(0.5)
        
        self._conectado = False
        tiempo_activa = datetime.now() - self._tiempo_conexion
        print(f"✅ Conexión cerrada exitosamente")
        print(f"   Tiempo de conexión activa: {tiempo_activa.total_seconds():.2f} segundos")
        print(f"   Consultas ejecutadas: {self._consultas_ejecutadas}")
        self._tiempo_conexion = None
        return True
    
    def estado(self):
        """
        Muestra el estado actual de la conexión.
        """
        print("\n" + "=" * 60)
        print("ESTADO DE LA CONEXIÓN A BASE DE DATOS")
        print("=" * 60)
        print(f"Estado: {'🟢 CONECTADA' if self._conectado else '🔴 DESCONECTADA'}")
        print(f"Host: {self._host}:{self._puerto}")
        print(f"Base de datos: {self._base_datos}")
        print(f"Usuario: {self._usuario}")
        
        if self._conectado and self._tiempo_conexion:
            tiempo_activa = datetime.now() - self._tiempo_conexion
            print(f"Tiempo activa: {tiempo_activa.total_seconds():.2f} segundos")
        
        print(f"Consultas ejecutadas: {self._consultas_ejecutadas}")
        print("=" * 60)
        
        return self._conectado
    
    def ejecutar_consulta(self, consulta):
        """
        Simula la ejecución de una consulta SQL.
        
        Args:
            consulta (str): La consulta SQL a ejecutar
        """
        if not self._conectado:
            print("❌ Error: No hay conexión activa. Debes conectar primero.")
            return None
        
        print(f"\n📊 Ejecutando consulta: {consulta}")
        time.sleep(0.3)  # Simular tiempo de ejecución
        self._consultas_ejecutadas += 1
        print(f"✅ Consulta ejecutada exitosamente (#{self._consultas_ejecutadas})")
        
        # Simular resultado
        return f"Resultado de la consulta #{self._consultas_ejecutadas}"
    
    def configurar(self, host=None, puerto=None, base_datos=None, usuario=None):
        """
        Configura los parámetros de conexión.
        Solo se puede configurar si la conexión está desconectada.
        """
        if self._conectado:
            print("❌ No se puede configurar mientras hay una conexión activa")
            return False
        
        if host:
            self._host = host
        if puerto:
            self._puerto = puerto
        if base_datos:
            self._base_datos = base_datos
        if usuario:
            self._usuario = usuario
        
        print("✅ Configuración actualizada correctamente")
        return True


# Clases que simulan diferentes partes de la aplicación
class RepositorioUsuarios:
    """Simula un repositorio de usuarios que necesita acceso a BD"""
    def __init__(self):
        self.conexion = ConexionBD()
    
    def obtener_usuarios(self):
        print("\n--- RepositorioUsuarios: Obteniendo usuarios ---")
        return self.conexion.ejecutar_consulta("SELECT * FROM usuarios")


class RepositorioProductos:
    """Simula un repositorio de productos que necesita acceso a BD"""
    def __init__(self):
        self.conexion = ConexionBD()
    
    def obtener_productos(self):
        print("\n--- RepositorioProductos: Obteniendo productos ---")
        return self.conexion.ejecutar_consulta("SELECT * FROM productos")


if __name__ == "__main__":
    print("=" * 60)
    print("DEMOSTRACIÓN DEL PATRÓN SINGLETON - CONEXIÓN A BD")
    print("=" * 60)
    
    # Intentar crear múltiples conexiones
    print("\n1️⃣  Creando primera referencia a ConexionBD...")
    conexion1 = ConexionBD()
    print(f"   ID de conexion1: {id(conexion1)}")
    
    print("\n2️⃣  Creando segunda referencia a ConexionBD...")
    conexion2 = ConexionBD()
    print(f"   ID de conexion2: {id(conexion2)}")
    
    print("\n3️⃣  Creando tercera referencia a ConexionBD...")
    conexion3 = ConexionBD()
    print(f"   ID de conexion3: {id(conexion3)}")
    
    print(f"\n✅ Verificación: Todas son la misma instancia: {conexion1 is conexion2 is conexion3}")
    
    # Usar la conexión
    print("\n" + "=" * 60)
    print("OPERACIONES CON LA CONEXIÓN")
    print("=" * 60)
    
    conexion1.estado()
    conexion1.conectar()
    conexion1.estado()
    
    # Ejecutar consultas desde diferentes referencias
    conexion2.ejecutar_consulta("SELECT * FROM usuarios WHERE id = 1")
    conexion3.ejecutar_consulta("SELECT COUNT(*) FROM productos")
    conexion1.ejecutar_consulta("INSERT INTO logs VALUES ('Nueva entrada')")
    
    # Usar desde diferentes módulos
    print("\n" + "=" * 60)
    print("ACCESO DESDE DIFERENTES MÓDULOS")
    print("=" * 60)
    
    repo_usuarios = RepositorioUsuarios()
    print(f"ConexionBD en RepositorioUsuarios: {id(repo_usuarios.conexion)}")
    repo_usuarios.obtener_usuarios()
    
    repo_productos = RepositorioProductos()
    print(f"ConexionBD en RepositorioProductos: {id(repo_productos.conexion)}")
    repo_productos.obtener_productos()
    
    # Estado final
    conexion1.estado()
    
    # Desconectar
    conexion1.desconectar()
    conexion1.estado()
    
    # Intentar ejecutar consulta sin conexión
    conexion2.ejecutar_consulta("SELECT * FROM test")
    
    print("\n" + "=" * 60)
    print("CONCLUSIÓN")
    print("=" * 60)
    print("✅ Todas las referencias apuntan a la misma instancia")
    print("✅ Solo existe una conexión activa en todo momento")
    print("✅ Todos los módulos comparten el mismo estado de conexión")
