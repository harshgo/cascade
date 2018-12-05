wire signed[68:0] minus_one = -1;
wire signed[68:0] left_shifted, test1, test2;
assign left_shifted = minus_one <<< 1;
assign test1 = left_shifted >> 1; 
assign test2 = left_shifted >>> 1;

wire signed[68:0] six_bits = minus_one >>> 6;

initial begin
    $display("minus_one %d", minus_one);
    $display("left_shifted %d", left_shifted);
    $display("ggt %d gggt %d", test1, test2);
    $display("six_bits %d", six_bits);
end
