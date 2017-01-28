`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   17:42:15 11/16/2015
// Design Name:   cmp_exp
// Module Name:   T:/332/addpipe/test_cmp_exp.v
// Project Name:  addpipe
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: cmp_exp
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_cmp_exp;

	// Inputs
	reg clk;
	reg clr;
	reg [31:0] in1;
	reg [31:0] in2;

	// Outputs
	wire [7:0] dif;
	wire [31:0] out_dif;

	// Instantiate the Unit Under Test (UUT)
	cmp_exp uut (
		.clk(clk), 
		.clr(clr), 
		.in1(in1), 
		.in2(in2), 
		.dif(dif), 
		.out_dif(out_dif)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		clr = 0;
		in1 = 32'b01000010001001000000000000000000;
		in2 = 32'b01000010000011000000000000000000;

		// Wait 100 ns for global reset to finish
		#100;
       
		clk = 1;
		
		#100;
		#100;
		// Add stimulus here

	end
      
endmodule

