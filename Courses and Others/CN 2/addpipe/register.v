`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:36:23 11/02/2015 
// Design Name: 
// Module Name:    register 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module register(in1, clk, load, clr, out1);

	parameter size = 32;
	
	input [size-1:0] in1;
	output reg [size-1:0] out1;
	input clk, load, clr;
	 
	 always @(posedge clk)
		if(clr)
			out1 <= 0;
		else
			if (load)
				out1 <= in1;

endmodule
