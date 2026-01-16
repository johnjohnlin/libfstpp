
ALL := bench2

bench2: testbench.v picorv32.v
	verilator --cc testbench.v picorv32.v -Mdir fixed --cc -trace-fst \
  --top-module picorv32_wrapper -Wno-lint -DCOMPRESSED_ISA
