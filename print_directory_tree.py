import os

def print_directory_tree(root_dir, prefix="", output_file=None):
    files = os.listdir(root_dir)
    files.sort()
    for index, file in enumerate(files):
        path = os.path.join(root_dir, file)
        connector = "└── " if index == len(files) - 1 else "├── "
        line = prefix + connector + file
        if output_file:
            output_file.write(line + "\n")
        if os.path.isdir(path):
            new_prefix = "    " if index == len(files) - 1 else "│   "
            print_directory_tree(path, prefix + new_prefix, output_file)

# Directorio raíz que quieres listar (cámbialo si es necesario)
root_directory = "H:/TALLER UNO I/1a_PROYECT/PROYECT"
output_path = "estructura.txt"

# Ejecutar el listado y guardar en archivo
if __name__ == "__main__":
    print("Guardando la estructura de directorios en estructura.txt")
    with open(output_path, "w", encoding="utf-8") as output_file:
        output_file.write("Estructura de directorios:\n")
        print_directory_tree(root_directory, output_file=output_file)

    print(f"Estructura guardada en {output_path}")
