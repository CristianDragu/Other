`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:21:41 11/16/2015 
// Design Name: 
// Module Name:    cmp_exp 
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
module cmp_exp(
		input clk,
		input clr,
		input [31:0] in1,
		input [31:0] in2,
		output reg [7:0] dif,
		output reg [31:0] out_dif
    );
	
	always @(in1, in2)
	begin
		if(clr == 0)
		begin
			dif = { in1[30:23] - in2[30:23] };
			if(dif[7] == 1'b0)
				out_dif = { 1'b1, dif[7:0], in1[31], in1[22:0], in2[31], in2[31:0] };
			else
				out_dif = { 1'b0, dif[7:0], in1[31], in1[22:0], in2[31], in2[31:0] };
		end
		else
			dif[7:0] = { 7'b0 };
	end

endmodule
