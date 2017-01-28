`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   15:25:00 11/02/2015
// Design Name:   adunare
// Module Name:   C:/Users/student/addpipe/test_assembly.v
// Project Name:  addpipe
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: adunare
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_assembly;

	// Inputs
	reg [63:0] in1;

	// Outputs
	wire [63:0] out1;

	// Instantiate the Unit Under Test (UUT)
	adunare uut (
		.in1(in1), 
		.out1(out1)
	);

	initial begin
		// Initialize Inputs
		in1 = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

