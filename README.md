# Image Processing with OpenMP

A parallel image processing toolkit demonstrating:
- Gaussian Blur
- Anime Style Conversion
- Oil Painting Effect
- Pencil Sketch
- Thermal Camera Effect

## Features
- Parallel processing using OpenMP
- Performance benchmarking
- Automated report generation

## Prerequisites
- C++17 compatible compiler
- CMake 3.20 or higher
- OpenMP support in compiler
- Python 3.x (for running benchmarking analysis script)

## Build Instructions

To clean previous builds and build the project in Release mode:

```powershell
Remove-Item -Recurse -Force .\build\
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

## Usage

### Run Benchmarks

```powershell
cd build\Release
.\ImageProcessingOpenMP.exe --benchmark
```

### Apply Image Effects

```powershell
cd build\Release
.\ImageProcessingOpenMP.exe ..\..\input\input.jpg output_blur.jpg blur --parallel
.\ImageProcessingOpenMP.exe ..\..\input\input.jpg output_anime.jpg anime --parallel
.\ImageProcessingOpenMP.exe ..\..\input\input.jpg output_oil.jpg oil --parallel
.\ImageProcessingOpenMP.exe ..\..\input\input.jpg output_pencil.jpg pencil --parallel
.\ImageProcessingOpenMP.exe ..\..\input\input.jpg output_thermal.jpg thermal --parallel
```

### Generate Graphs

```powershell
cd ..\..\benchmarking
python analysis.py
```

## License

(Add your license information here, e.g., MIT, GPL, etc.)

## Contributing

Contributions are welcome! Please open issues or submit pull requests for improvements or bug fixes.
