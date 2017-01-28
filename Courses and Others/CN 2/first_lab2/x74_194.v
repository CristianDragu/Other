`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:01:29 10/05/2015 
// Design Name: 
// Module Name:    x74_194 
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
module x74_194(s0, s1, sli, sri, ck, clr, a, b, c, d, qa, qb, qc, qd);
input s1, s0, sli, sri, ck, clr, a, b, c, d;
output qa, qb, qc, qd;
reg qa, qb, qc, qd;


	always @ (clr)
	begin
		if(clr == 0) 
		begin
			qa = 0;
			qb = 0;
			qc = 0;
			qd = 0;
		end
	end
	
	always @ (posedge ck) 
	begin
		if(clr == 1) begin
			if(s0 == 1 && s1 == 0) 
			begin
				qa = sri;
				qd = qc;
				qc = qb;
				qb = qa;
			end
			if(s0 == 0 && s1 == 1) 
			begin
				qa = qb;
				qb = qc;
				qc = qd;
				qd = sli;
			end
			if(s0 == 1 && s1 == 1) 
			begin
				qa = a;
				qb = b;
				qc = c;
				qd = d;
			end
		end
	end

endmodule
