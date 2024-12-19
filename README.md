## 📦 **kompressor**

**kompressor** is a simple and efficient command-line tool for file compression and decompression, written in **C** and utilizing the [Snappy library](https://github.com/google/snappy) by Google. It delivers high speeds while maintaining ease of use.

---

### 🚀 **Features**
- **Written in C**: Lightweight and efficient for high performance.  
- **Fast Compression**: Up to **250 MB/s**.  
- **Fast Decompression**: Up to **500 MB/s**.  
- **Easy to Use**: Specify input and output files directly from the command line.  
- **File-Based**: Works with any file type.  

---

### ⚙️ **Dependencies**
This project uses **Snappy**, a fast and lightweight compression/decompression library.

---

### 🔧 **Installation**
1. Clone the repository:
   ```bash
   git clone https://github.com/acc0re/kompressor.git
   cd kompressor
   ```

2. Build the project using **CMake**:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

3. Run the program:
   ```bash
   kompressor <input_file> <output_file>
   ```

---

### 📘 **Usage**
To **compress** a file:
```bash
kompressor input.txt output.snappy
```

To **decompress** a file:
```bash
kompressor output.snappy restored.txt
```

---

### 📊 **Performance**
- **Compression Speed**: Up to **250 MB/s**.  
- **Decompression Speed**: Up to **500 MB/s**.  

Snappy achieves these speeds by optimizing for modern CPUs, prioritizing performance over maximum compression ratios.

---

### 🛠️ **Build Systems**
- Written in **C** for efficiency and portability.  
- Uses **CMake** for building.  
- Currently tested only on **Windows** and **macOS (ARM)**.

---

### 🌐 **References**
- Snappy Library: [https://github.com/google/snappy](https://github.com/google/snappy)

---

### 📄 **License**
This project is licensed under the **MIT License**.

---
