class Configuracion:
    """
    Clase Singleton para manejar las configuraciones generales del sistema.
    Solo permite una única instancia en toda la aplicación.
    """
    _instancia = None
    
    def __new__(cls):
        """
        Sobrescribe __new__ para controlar la creación de instancias.
        Si ya existe una instancia, la retorna; si no, crea una nueva.
        """
        if cls._instancia is None:
            cls._instancia = super(Configuracion, cls).__new__(cls)
            # Inicializar configuraciones por defecto
            cls._instancia.idioma = "Español"
            cls._instancia.zona_horaria = "UTC-6"
        return cls._instancia
    
    def set_idioma(self, idioma):
        """Establece el idioma del sistema"""
        self.idioma = idioma
    
    def set_zona_horaria(self, zona):
        """Establece la zona horaria del sistema"""
        self.zona_horaria = zona
    
    def mostrar_configuracion(self):
        """Imprime los valores actuales de configuración"""
        print("=" * 50)
        print("CONFIGURACIÓN DEL SISTEMA")
        print("=" * 50)
        print(f"Idioma: {self.idioma}")
        print(f"Zona Horaria: {self.zona_horaria}")
        print("=" * 50)


if __name__ == "__main__":
    # Crear primera instancia
    config1 = Configuracion()
    print(f"config1 ID: {id(config1)}")
    config1.mostrar_configuracion()
    
    print("\n--- Modificando configuración desde config1 ---")
    config1.set_idioma("Inglés")
    config1.set_zona_horaria("UTC+0")
    
    # Crear segunda "instancia" (realmente obtendremos la misma)
    config2 = Configuracion()
    print(f"\nconfig2 ID: {id(config2)}")
    config2.mostrar_configuracion()
    
    # Crear tercera "instancia"
    config3 = Configuracion()
    print(f"\nconfig3 ID: {id(config3)}")
    
    # Verificar que todas son la misma instancia
    print("\n--- Verificación de instancia única ---")
    print(f"config1 es config2: {config1 is config2}")
    print(f"config2 es config3: {config2 is config3}")
    print(f"config1 es config3: {config1 is config3}")
    
    # Modificar desde config3
    print("\n--- Modificando desde config3 ---")
    config3.set_idioma("Francés")
    config3.set_zona_horaria("UTC+1")
    
    # Verificar que el cambio se refleja en todas
    print("\nVerificando config1:")
    config1.mostrar_configuracion()
