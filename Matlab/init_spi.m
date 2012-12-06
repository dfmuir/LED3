% Initialize IOWarrior56 For SPI Special Mode Functionality
% Return connection to connection
function [connection] = init_spi()
loadlibrary('iowkit.dll', @iowarrior, 'alias', 'iowkit');

connection = 0;

if(libisloaded('iowkit'))
    connection = calllib('iowkit', 'IowKitOpenDevice', connection);
    io_id = calllib('iowkit', 'IowKitGetProductId', connection);
    if(io_id == 5379) % Ensure that this is the IOWarrior56 device
        disp('Connected to LED3');
        report = zeros([1,64]);
        report(1)=8;
        report(2)=1;
        report(3)=6;
        report(4) = 255;
        reportPointer = libpointer('uint8Ptr', report);
        res = calllib('iowkit', 'IowKitWrite', connection, 1, reportPointer, 64);
    end
end

end

