
module Simple (
  // input
  input clk,
  input rst_n
);

logic [1:0] counter_add;
always_ff @(posedge clk or negedge rst_n) begin
  if (!rst_n) begin
    counter_add <= 2'b00;
  end else begin
    counter_add <= counter_add + 2'b01;
  end
end

// Unable to handle right now
// logic [126:0] counter_shift;
// always_ff @(posedge clk or negedge rst_n) begin
//   if (!rst_n) begin
//     counter_shift <= 127'b0;
//   end else begin
//     counter_shift <= {counter_shift[125:0], 1'b1};
//   end
// end

endmodule
