import os

def generate_file_content_report(directory, output_file):
    cpp_count = 0
    hpp_count = 0
    other_count = 0
    error_count = 0
    total_size = 0
    max_preview_size = 100000  # Limitar la cantidad de contenido leído a 100 KB
    extensions_to_analyze = ['.cpp', '.hpp', '.txt', '.md']  # Extensiones que podemos encontrar útiles

    with open(output_file, 'w', encoding='utf-8') as report_file:
        report_file.write("INFORME DETALLADO DEL PROYECTO\n\n")
        
        for root, _, files in os.walk(directory):
            report_file.write(f"Directorio: {root}\n")
            report_file.write("=" * 80 + "\n\n")
            
            for file in files:
                filepath = os.path.join(root, file)
                file_extension = os.path.splitext(file)[1]

                try:
                    if file_extension in extensions_to_analyze:
                        # Leer el contenido del archivo si es de las extensiones a analizar
                        with open(filepath, 'r', encoding='utf-8') as f:
                            content = f.read(max_preview_size)  # Leer solo los primeros 100 KB
                        
                        # Contar líneas del archivo
                        line_count = len(content.splitlines())
                        file_size = os.path.getsize(filepath)
                        total_size += file_size

                        # Escribir el reporte del archivo
                        report_file.write(f"Archivo: {filepath}\n")
                        report_file.write(f"Extensión: {file_extension}, Tamaño: {file_size} bytes, Líneas: {line_count}\n")
                        report_file.write(f"Contenido (primeros {max_preview_size} caracteres):\n{content}\n")
                        report_file.write("#" * 80 + "\n\n")

                        # Contar tipos de archivos
                        if file.endswith('.cpp'):
                            cpp_count += 1
                        elif file.endswith('.hpp'):
                            hpp_count += 1
                        else:
                            other_count += 1
                    else:
                        report_file.write(f"Archivo: {filepath} (omitido, extensión no relevante)\n")
                        report_file.write("#" * 80 + "\n\n")
                except Exception as e:
                    # Capturar errores de lectura
                    report_file.write(f"Archivo: {filepath}\n")
                    report_file.write(f"Error al leer el archivo: {e}\n")
                    report_file.write("#" * 80 + "\n\n")
                    error_count += 1
    
    # Escribir un resumen al final del archivo
    with open(output_file, 'a', encoding='utf-8') as report_file:
        report_file.write("\n\nRESUMEN DEL INFORME\n")
        report_file.write("=" * 80 + "\n")
        report_file.write(f"Archivos .cpp encontrados: {cpp_count}\n")
        report_file.write(f"Archivos .hpp encontrados: {hpp_count}\n")
        report_file.write(f"Otros archivos encontrados (.txt, .md, etc.): {other_count}\n")
        report_file.write(f"Errores de lectura: {error_count}\n")
        report_file.write(f"Tamaño total de archivos leídos: {total_size} bytes\n")
        report_file.write(f"Ruta analizada: {directory}\n")

# Ruta del proyecto
project_directory = "."  # Cambia a la ruta de tu proyecto si es necesario

# Archivo de salida
output_file = "contenido_proyecto.txt"

# Generar el reporte
generate_file_content_report(project_directory, output_file)
