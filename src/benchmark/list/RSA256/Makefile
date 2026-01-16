ALL := bench1

SRCS := RSA_tb.sv \
	Pipeline.sv \
	PipelineCombine.sv \
	PipelineDistribute.sv \
	PipelineFilter.sv \
	PipelineLoop.sv \
	Montgomery.sv \
	RSA.sv \
	RSAMont.sv \
	TwoPower.sv

bench1: $(SRCS)
	verilator --cc $(SRCS) -Mdir fixed --trace-fst -Wno-lint --timing