module testx;

reg [7:0]array[15:0];

initial begin
    array[0] = 30;
    array[1] = 21;
    {array[0], array[1]} = {array[1], array[0]};
    $monitor("%d, %d", array[0], array[1]);
end

endmodule
