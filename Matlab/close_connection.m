function [] = close_connection( connection )
calllib('iowkit', 'IowKitCloseDevice', connection)

if(libisloaded('iowkit'))
    unloadlibrary('iowkit')
end


end

