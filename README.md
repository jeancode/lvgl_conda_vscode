# Configurando un Entorno de Desarrollo con Conda  

## Introducción  
Conda es un potente gestor de paquetes y entornos que facilita la instalación y configuración de herramientas para desarrollo de software. Este artículo te guiará para instalar cuatro herramientas esenciales:  

- **m2w64-toolchain**  
- **cmake**  
- **sdl**  
- **make**  

Estas herramientas son esenciales para compilar y construir proyectos en entornos Windows o multiplataforma.  

---

## Paso 1: Crear y Activar un Entorno de Conda  

Antes de instalar los paquetes, es recomendable crear un entorno específico para mantener las herramientas aisladas.  

```bash  
conda create --name cplusEnv python=3.9
conda activate cplusEnv  
```

### Instalar m2w64-toolchain
El paquete m2w64-toolchain proporciona un conjunto de herramientas de desarrollo basadas en MinGW, útiles para compilar programas en Windows.
```bash  
conda install -c conda-forge m2w64-toolchain  
```
### Instalar CMake
CMake es una herramienta de construcción que simplifica la generación de sistemas de compilación multiplataforma.
```bash  
conda install -c conda-forge cmake
```
### Instalar SDL (Simple DirectMedia Layer)
SDL es una biblioteca de desarrollo multimedia que proporciona acceso a gráficos, audio y otros periféricos.
```bash  
conda install -c conda-forge sdl
conda install -c conda-forge sdl2
conda install -c conda-forge sdl2_image sdl2_ttf sdl2_mixer
```
Make es una herramienta clásica utilizada para automatizar la construcción de programas a partir de código fuente.
### Instalar Make
```bash  
conda install -c conda-forge make  
```
Después de instalar las herramientas, verifica que todo esté correctamente configurado:
```bash  

gcc --version       # Para verificar m2w64-toolchain  
cmake --version     # Para verificar CMake  
sdl2-config --version # Para SDL  
make --version      # Para Make

```

# Instrucciones para compilar LVGL


```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make
```  

