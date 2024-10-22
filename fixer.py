import os
import shutil

# Diccionario que define la estructura original
estructura_original = {
    "src": {
        "app": ["CarmenSandiegoApp.cpp", "CarmenSandiegoApp.hpp", "WelcomeWindow.cpp", "WelcomeWindow.hpp", "main.cpp"],
        "core": ["game_controller.cpp", "game_controller.hpp", "game_logic.cpp", "game_logic.hpp"],
        "models": ["UserDAO.cpp", "UserDAO.hpp", "PistaDAO.cpp", "PistaDAO.hpp"],
        "assets": {
            "audio": ["CSD.mp3"],
            "images": ["logo.png", "bg.jpg"]
        }
    },
    "CMakeLists.txt": None,
    "contenido_proyecto.txt": None,
    "estructura.txt": None
}

# Función para restaurar la estructura original
def restaurar_estructura(estructura, base_path, relative_path=""):
    for key, value in estructura.items():
        path = os.path.join(base_path, key)
        relative_file_path = os.path.join(relative_path, key)
        
        if isinstance(value, dict):
            # Si es un directorio, crearlo y llamar recursivamente
            if not os.path.exists(path):
                print(f"Restaurando carpeta: {path}")
                os.makedirs(path)
            restaurar_estructura(value, path, relative_file_path)
        else:
            # Si es un archivo, restaurarlo
            for file_name in value:
                file_path = os.path.join(path, file_name)
                backup_file_path = os.path.join("backup", relative_file_path, file_name)
                
                if not os.path.exists(file_path):
                    print(f"Restaurando archivo: {file_path}")
                    # Restauramos el archivo desde el backup si existe
                    if os.path.exists(backup_file_path):
                        shutil.copy(backup_file_path, file_path)
                    else:
                        print(f"Archivo de backup no encontrado: {backup_file_path}")

# Ruta base de tu proyecto
ruta_proyecto = os.getcwd()

# Ejecuta el script para restaurar la estructura
restaurar_estructura(estructura_original, ruta_proyecto)
