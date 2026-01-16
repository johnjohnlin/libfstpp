# About this repo

An experiment to rewrite `fstapi.c` for better Verilator simulation speed.

# Project structure
Everything is under `src/`

* `fstapi/fstcpp`: The main focus of this repo.
* `fstapi/gtkwave`: Original fstapi C implementation from GtkWave.
* `benchmark/`: The directory of overall benchmark cases and test cases
* `benchmark/verilatorshare`: The snapshot of files to built a verilator project. Copied from version 5.042.
* `benchmark/list/RSA256`: Benchmark 1, RSA256 implemented in systemverilog
* `benchmark/list/picorv32`: Benchmark 2, picorv32 full emulation
* `golden_bench1.fst`,`golden_benc2.fst`: The fst file dumped by gtkwave

# How to run
I have snapshot the Verilator output, and you just need to follow the standard cmake process. No Verilator is needed at all. You need a C++20 compiler as Verilator needs it.

```
cmake -B build src -DCMAKE_BUILD_TYPE=Release
cd build
make -j $(nproc)
* ./${benchmark} 0         # No FST version
* ./${benchmark}_gtkwave 1 # gtkwave version
* ./${benchmark} 1         # cpp FST version
```

# Reference

Please refer to the [unofficial document](https://blog.timhutt.co.uk/fst_spec/) of the fst waveform specification

# Profiling results

We collect following benchmark:
1. [RSA256](https://github.com/yodalee/rsa256)
2. [picorv32](https://github.com/YosysHQ/picorv32)

CPU: AMD Ryzen 9 7950X, release mode, cell is the runtime (ms).

| Mode        | RSA256 | picorv32 |
|:------------|-------:|---------:|
| GtkWave FST |  163.5 |   1287.7 |
| This FST    |   73.9 |    825.9 |
| No FST      |    7.5 |     78.4 |
