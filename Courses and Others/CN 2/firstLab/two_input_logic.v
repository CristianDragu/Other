`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:24:44 10/05/2015 
// Design Name: 
// Module Name:    two_input_logic 
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
module two_input_logic(in1, in2, out1);
input in1, in2;
output out1;

	assign out1 = in1 ^ in2;

endmodule
