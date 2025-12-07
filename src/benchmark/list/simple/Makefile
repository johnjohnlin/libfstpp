
ALL := simple

simple: Simple.sv
	verilator --cc Simple.sv -Mdir fixed --cc -trace-fst \
	--top-module Simple -Wno-lint