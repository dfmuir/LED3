function [] = write_data(connection, data)

if(length(data) <= 61)
    report(1)=9;
    report(2)=length(data);
    report(3)=0;
    
    report = [report data];
    
    reportPointer = libpointer('uint8Ptr', report);
    res = calllib('iowkit', 'IowKitWrite', connection, 1, reportPointer, 64);
    
else
    disp('Error in write_data function: Vector too long');
end
        
end

