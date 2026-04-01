import os
import subprocess
import platform

# Archivos c++
programa = ["main.cpp", "scanner.cpp", "token.cpp"]

# Compilar
compile = ["g++"] + programa
print("Compilando:", " ".join(compile))
result = subprocess.run(compile, capture_output=True, text=True)

if result.returncode != 0:
    print("Error en compilación:\n", result.stderr)
    exit(1)

print("Compilación exitosa")

# Ejecutar
input_dir = "inputs"
for i in range(1, 11): 
    filename = f"input{i}.txt"
    filepath = os.path.join(input_dir, filename)
    if os.path.isfile(filepath):
        print(f"Ejecutado {filename}")
        if platform.system() == "Windows":
            run_cmd = ["a.exe", filepath]
        elif platform.system() == "Darwin":
            run_cmd = ["./a.out", filepath]
        subprocess.run(run_cmd, capture_output=True, text=True)
    else:
        print(filename, "no encontrado en",input_dir)