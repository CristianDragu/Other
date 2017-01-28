`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   14:41:56 11/02/2015
// Design Name:   register
// Module Name:   C:/Users/student/addpipe/reg_test.v
// Project Name:  addpipe
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: register
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module reg_test;

	// Inputs
	reg [63:0] in1;
	reg clk;
	reg load;
	reg clr;

	// Outputs
	wire [63:0] out1;

	// Instantiate the Unit Under Test (UUT)
	register uut (
		.in1(in1), 
		.out1(out1), 
		.clk(clk), 
		.load(load), 
		.clr(clr)
	);

	initial begin
		// Initialize Inputs
		in1 = 0;
		clk = 0;
		load = 0;
		clr = 0;
	end
	
	always begin
		#100;
		clk = !clk;
	end
	
	initial begin
		// Initialize Inputs
		in1 = 41;
		in2 = 35;
		load = 0;
		clr = 0;
		
		// Wait 100 ns for global reset to finish
		#100;
		load = 1;
		
		#100
		
		load = 0;
		clr = 1;
		
		#100
		clr = 0;
		in1 = 64;
		
		#200
		
		in1 = 5;
		load = 1;
		
		#200
		
		load = 0;
		clr = 1;
	end
      
endmodule

