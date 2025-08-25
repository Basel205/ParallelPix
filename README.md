# ParallelPix: High-Performance Image Processing with OpenMP

![C++17](https://img.shields.io/badge/C++-17-blue)
![OpenMP](https://img.shields.io/badge/OpenMP-enabled-orange)
![License](https://img.shields.io/badge/license-MIT-green)

ParallelPix is a powerful C++ toolkit that demonstrates **high-performance image processing using OpenMP for parallelization**.
It provides a collection of image filters and effects, a benchmarking suite to compare serial vs. parallel performance, and a simple GUI for easy interaction.

---

## Table of Contents

* [About The Project](#about-the-project)
* [Key Technologies](#key-technologies)
* [Features](#features)
* [Getting Started](#getting-started)

  * [Prerequisites](#prerequisites)
  * [Build Instructions](#build-instructions)
* [Usage](#usage)

  * [Command-Line Interface (CLI)](#command-line-interface-cli)
  * [Graphical User Interface (GUI)](#graphical-user-interface-gui)
* [Benchmarking and Analysis](#benchmarking-and-analysis)
* [Contributing](#contributing)
* [License](#license)

---

## About The Project

This project was created to explore and showcase the benefits of **parallel computing** in the context of image processing.
By leveraging the OpenMP API, ParallelPix can significantly speed up computationally intensive image filtering tasks.
The included benchmarking tools provide a clear visualization of the performance gains achieved through parallelization.

---

## Key Technologies

* **C++17**: For modern, efficient, and robust code
* **OpenMP**: For multi-threaded parallel processing
* **CMake**: For cross-platform builds
* **Python**: For data analysis and visualization of benchmark results
* **Tkinter**: For the graphical user interface

---

## Features

* **A Variety of Image Filters**

  * Gaussian Blur
  * Anime Style
  * Oil Painting
  * Pencil Sketch
  * Thermal Effect

* **High-Performance Parallel Processing**
  Utilizes OpenMP to accelerate image filtering tasks on multi-core processors.

* **Comprehensive Benchmarking Suite**
  Compare the performance of serial and parallel execution for different filters and image sizes.

* **Automated Reporting and Visualization**
  Generate insightful graphs that visualize speedup and execution time comparison.

* **User-Friendly GUI**
  An intuitive graphical interface for easy application of filters without using the command line.

---

## Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

* C++17 compatible compiler
* CMake 3.20 or higher
* OpenMP support in your compiler
* Python 3.x
* Python libraries: `pandas`, `matplotlib`, `seaborn`

Install Python dependencies:

```bash
pip install pandas matplotlib seaborn
```

### Build Instructions

Clone the repo:

```bash
git clone https://github.com/your_username/ParallelPix.git
cd ParallelPix
```

Clean previous builds and build the project in **Release** mode:

```powershell
Remove-Item -Recurse -Force .\build\
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

---

## Usage

ParallelPix can be used either via **command line (CLI)** for control and scripting, or via the **GUI** for ease of use.

### Command-Line Interface (CLI)

From the `build/Release` directory:

```powershell
# Apply Gaussian Blur
.\ImageProcessingOpenMP.exe ..\..\input\input.jpg output_blur.jpg blur --parallel

# Apply Anime Style Filter
.\ImageProcessingOpenMP.exe ..\..\input\input.jpg output_anime.jpg anime --parallel

# Apply Oil Painting Effect
.\ImageProcessingOpenMP.exe ..\..\input\input.jpg output_oil.jpg oil --parallel

# Apply Pencil Sketch Effect
.\ImageProcessingOpenMP.exe ..\..\input\input.jpg output_pencil.jpg pencil --parallel

# Apply Thermal Effect
.\ImageProcessingOpenMP.exe ..\..\input\input.jpg output_thermal.jpg thermal --parallel
```

### Graphical User Interface (GUI)

Navigate to the GUI directory and run:

```bash
cd ../../gui
python gui_app.py
```

---

## Benchmarking and Analysis

ParallelPix includes a benchmarking suite to evaluate and visualize performance gains from parallelization.

Run the benchmarks:

```powershell
cd build\Release
.\ImageProcessingOpenMP.exe --benchmark
```

Generate the analysis graphs:

```powershell
cd ..\..\benchmarking
python analysis.py
```

*Example benchmark output:*
![Benchmark Speedup Graph](assets/benchmark_example.png)
*(Replace with your generated graph)*

---

## Contributing

Contributions are welcome! Please open issues or submit pull requests for improvements or bug fixes.

---

## License

Distributed under the **MIT License**.
See [`LICENSE`](LICENSE) for more information.
