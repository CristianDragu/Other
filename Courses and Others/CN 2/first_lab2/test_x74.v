`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   17:30:01 10/05/2015
// Design Name:   x74_194
// Module Name:   T:/first_lab2/test_x74.v
// Project Name:  first_lab2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: x74_194
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_x74;

	// Inputs
	reg s0;
	reg s1;
	reg sli;
	reg sri;
	reg ck;
	reg clr;
	reg a;
	reg b;
	reg c;
	reg d;

	// Outputs
	wire qa;
	wire qb;
	wire qc;
	wire qd;

	// Instantiate the Unit Under Test (UUT)
	x74_194 uut (
		.s0(s0), 
		.s1(s1), 
		.sli(sli), 
		.sri(sri), 
		.ck(ck), 
		.clr(clr), 
		.a(a), 
		.b(b), 
		.c(c), 
		.d(d), 
		.qa(qa), 
		.qb(qb), 
		.qc(qc), 
		.qd(qd)
	);

	initial begin
		// Initialize Inputs
		a = 0;
		b = 1;
		c = 0;
		d = 0;
		sli = 0;
		sri = 0;
		s0 = 0;
		s1 = 0;
		ck = 0;
		clr = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
        clr = 1;
        ck = 1;
        s0 = 1;
        s1 = 1;

        #100;

        ck = 0;
        s0 = 1;
        s1 = 0;

        #100;

        ck = 1;

		
	end
      
endmodule

