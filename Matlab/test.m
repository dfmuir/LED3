red = 1; green = 2; blue = 3; cyan = 4; pink = 5; yellow = 6; white = 7; off = 0;


frame = zeros([8,8,8]);
blues = ones([8,8,8])*blue;
red = ones([8,8,8])*red;



connection = init_spi();

write_frame(connection, red)
% 
% 
% while 1
% write_frame(connection, red)
% write_frame(connection, red)
% end

close_connection(connection)