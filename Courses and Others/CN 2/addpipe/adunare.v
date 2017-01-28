`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:23:13 11/02/2015 
// Design Name: 
// Module Name:    adunare 
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

module adunare(
		input clk,
		input [31:0] in1,
		input [31:0] in2,
		output [31:0] out1
    );

	reg clr = 0, load = 0;
	integer clear_timer = 0;
	reg [31:0] outaux1;
	reg [31:0] outaux2;
	reg [31:0] outaux3;

	register R1(
		.in1 (in1),
		.out1(outaux1),
		.clk (clk),
		.clr (clr),
		.load(load)
	);
	register R2(
		.in1 (outaux1),
		.out1(outaux2),
		.clk (clk),
		.clr (clr),
		.load(load)
	);
	register R3(
		.in1 (outaux2),
		.out1(outaux3),
		.clk (clk),
		.clr (clr),
		.load(load)
	);
	register R4(
		.in1 (outaux3),
		.out1(out1),
		.clk (clk),
		.clr (clr),
		.load(load)
	);
/*
	always @(*)
		begin
			clk = !clk;
			if(clk == 1)
				begin
					load = 1;
					clr = 0;
					clear_timer = clear_timer + 1;
				end
			else
				if(clear_time == 4)
					begin
						load = 0;
						clr = 1;
						clear_time = 0;
					end
		end
*/
endmodule
