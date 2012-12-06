function [] = write_frame(connection, frame)
red = 1; green = 2; blue = 3; cyan = 4; pink = 5; yellow = 6; white = 7; off = 0;

i = 192;

vector = zeros([1,192]);

for z = 1:8
    for y = 1:8
        for x = 1:8
            color = frame(x,9-z,y);
            %Red
            vector(i)   = vector(i)   + 2^(x-1) * ((color==red) | (color ==pink) | (color == yellow) | (color == white));
            %Green
            vector(i-1) = vector(i-1) + 2^(x-1) * ((color==green) | (color == cyan) | (color == yellow) | (color == white));
            %Blue
            vector(i-2) = vector(i-2) + 2^(x-1) * ((color==blue) | (color == pink) | (color == cyan) | (color == white));
        end
        i = i - 3;
    end
    
end
        
    

%write_data(connection, vector(1:61));
%write_data(connection, vector(62:122));
%write_data(connection, vector(123:183));
%write_data(connection, vector(184:192));

write_data(connection, 255); % Signal start of data dump

for i=1:192
write_data(connection, vector(i));
end
    


end

