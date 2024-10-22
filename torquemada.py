import os
import shutil

# Definir las rutas que se mantendrán en el proyecto
KEEP_FILES = [
    'assets/audio/CSD.mp3',
    'src/app/main.cpp',
    'src/app/WelcomeWindow.cpp',
    'src/app/WelcomeWindow.hpp',
    'src/core/game_controller.cpp',
    'src/core/game_controller.hpp',
    'src/core/game_logic.cpp',
    'src/core/game_logic.hpp',
    'src/dao/',
    'src/database/',
    'src/models/',
    'src/ui/',
    'src/utils/',
    'CMakeLists.txt',
    'prompt.txt'  # Archivo prompt
]

# Obtener las extensiones de archivos que NO deben ser eliminados
KEEP_EXTENSIONS = ['.py']

def should_keep(file_path):
    """Verificar si el archivo debe ser mantenido según la lista KEEP_FILES o extensión."""
    # Normalizar la ruta
    normalized_path = os.path.normpath(file_path)
    # Verificar si está en la lista de archivos a mantener
    for keep_file in KEEP_FILES:
        if normalized_path.endswith(os.path.normpath(keep_file)):
            return True
    # Verificar si tiene una de las extensiones a mantener
    return any(file_path.endswith(ext) for ext in KEEP_EXTENSIONS)

def clean_directory(root_dir):
    """Eliminar archivos y carpetas que no sean necesarios en el proyecto."""
    for dirpath, dirnames, filenames in os.walk(root_dir, topdown=False):
        # Eliminar archivos no deseados
        for filename in filenames:
            file_path = os.path.join(dirpath, filename)
            if not should_keep(file_path):
                print(f"Eliminando archivo: {file_path}")
                os.remove(file_path)

        # Eliminar directorios vacíos que no están en la lista KEEP_FILES
        if dirpath not in [os.path.normpath(os.path.join(root_dir, os.path.dirname(f))) for f in KEEP_FILES]:
            if not os.listdir(dirpath):  # Si el directorio está vacío
                print(f"Eliminando directorio vacío: {dirpath}")
                shutil.rmtree(dirpath)

if __name__ == "__main__":
    # Ruta raíz del proyecto
    root_project = os.path.dirname(os.path.abspath(__file__))  # Ruta actual del script

    # Ejecutar la limpieza
    clean_directory(root_project)

    print("Limpieza completa.")
