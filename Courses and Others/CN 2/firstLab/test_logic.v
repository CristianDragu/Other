`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   16:26:52 10/05/2015
// Design Name:   two_input_logic
// Module Name:   T:/firstLab/test_logic.v
// Project Name:  firstLab
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: two_input_logic
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_logic;

	// Inputs
	reg in1;
	reg in2;

	// Outputs
	wire out1;

	// Instantiate the Unit Under Test (UUT)
	two_input_logic uut (
		.in1(in1), 
		.in2(in2), 
		.out1(out1)
	);

	initial begin
		// Initialize Inputs
		in1 = 0;
		in2 = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		in1 = 1;
		in2 = 0;
		
		#100;
		in1 = 0;
		in2 = 1;
		
		#100;
		in1 = 1;
		in2 = 1;
		
	end
      
endmodule

