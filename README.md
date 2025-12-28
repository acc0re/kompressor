# kompressor

**kompressor** is a minimal command-line tool for file compression and decompression.  
It is written in **C** and uses Google’s **Snappy** library, which prioritizes speed and low CPU overhead over maximum compression ratios.

This project is intentionally simple and designed for high-throughput data workflows rather than everyday file archiving.

---

## Purpose

`kompressor` is most useful when working with **large data volumes**.

Snappy’s strengths become apparent at scale, where predictable performance and fast processing matter more than saving a few extra percent of disk space. In practice, this means the tool is best suited for:

- Terabyte-scale datasets  
- Large log archives  
- Backup and restore pipelines  
- Streaming and batch processing systems  

For small files or general-purpose compression, formats such as ZIP, Zstandard, or 7z are usually more appropriate.

---

## Features

- Implemented in C for performance and portability  
- Very fast compression and decompression  
- Simple, no-frills command-line interface  
- Works with any file type  

---

## Performance

Approximate throughput on modern hardware:

- Compression: up to ~250 MB/s  
- Decompression: up to ~500 MB/s  

These numbers reflect Snappy’s design goal: high and consistent throughput rather than optimal compression ratios.

---

## Dependencies

- [Snappy](https://github.com/google/snappy)

---

## Build and Installation

```bash
git clone https://github.com/acc0re/kompressor.git
cd kompressor
mkdir build
cd build
cmake ..
cmake --build .
