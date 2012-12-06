classdef cubekit
    
    properties
        red = 1; green = 2; blue = 3; cyan = 4; pink = 5; yellow = 6; white = 7; off = 0;
        connection = 0;
        frame = zeros([8,8,8]);
        
        %Sounds
        sound_rain = 'C:\Users\Monica Petrella\Desktop\Dropbox\Cube\Sound Effects\rain_loop.wav';
        sound_drumroll = 'C:\Users\Monica Petrella\Desktop\Dropbox\Cube\Sound Effects\drumroll_loop.wav';
        sound_alien = 'C:\Users\Monica Petrella\Desktop\Dropbox\Cube\Sound Effects\alien_loop.wav';
        sound_rotate = 'C:\Users\Monica Petrella\Desktop\Dropbox\Cube\Sound Effects\cubescroll_loop.wav';
        sound_led = 'C:\Users\Monica Petrella\Desktop\Dropbox\Cube\Sound Effects\laser_loop.wav';
        sound_flag = 'C:\Users\Monica Petrella\Desktop\Dropbox\Cube\Sound Effects\flag.wav';

    end
    
    methods
        
        function self = cubekit()
            self.connection = init_spi();
        end
        
        function send_command(self, command)
            
            write_data(self.connection, command);
        
        end
        
        
        function update(self)
            write_frame(self.connection, self.frame);
        end
        

        
        
        % Set the entire cube to a single color
        function set_cube(self, color)
            self.frame = ones([8,8,8]).*color;
            self.update();
        end
        
        function set_matrix(self, m)
            self.frame = m;
            self.update();
        end
        
        
        function dark(self)
            self.set_cube(self.off);
        end
        
        

        
        function set_single_led(self, x, y, z, color)
           self.frame(x,y,z) = color;
           self.update();
        end
        
        function close(self)
            close_connection(self.connection)
        end
        
        %Matlab functions
        function bounce_face(self, face_color, num_repeats)
            for count = 1:num_repeats
                for  i = 1:8
                    f = zeros([8,8,8]);
                    f(:,:,i) = ones([8,8])*face_color;
                    self.set_matrix(f);
                end

                for  i = 1:8
                    f = zeros([8,8,8]);
                    f(:,:,9-i) = ones([8,8])*face_color;
                    self.set_matrix(f);
                end
            end
        end
        
        
        %Onboard Animation Calls
        
        function rainbow(self)
            self.send_command(100);
            [y,Fs,nbits,readinfo]=wavread(self.sound_rain);
            sound(y,Fs)
            pause(14.8);
            self.set_cube(self.off);
        end
        
        function rain(self)
            self.send_command(101);
            [y,Fs,nbits,readinfo]=wavread(self.sound_rain);
            sound(y,Fs)
            pause(14.8);
            self.set_cube(self.off);
        end
        
        function cube(self)
            self.send_command(103);
        end
        
        function led(self)
            self.send_command(104);
            [y,Fs,nbits,readinfo]=wavread(self.sound_led);
            sound(y,Fs)
            pause(3)
            self.set_cube(self.off);

        end
        
        function alien(self)
            self.send_command(101);
            [y,Fs,nbits,readinfo]=wavread(self.sound_alien);
            sound(y,Fs)
            self.send_command(107);
            pause(9.6)
            self.set_cube(self.off);
        end
        
        function rotate(self)
            self.send_command(105);
            [y,Fs,nbits,readinfo]=wavread(self.sound_rotate);
            sound(y,Fs)
            pause(25)
            self.set_cube(self.off);

        end
        
        function blue_box(self)
            self.send_command(203);
        end
        %Still Frames On Board
        function four_cubes(self)
            self.send_command(200);
        end
        function flag(self)
            self.send_command(105);
            [y,Fs,nbits,readinfo]=wavread(self.sound_flag);
            sound(y,Fs)
            self.send_command(201);
        end
        
        function a(self)
            self.send_command(202);
        end
        
        function intro(self)
            self.blue_box()
            [y,Fs,nbits,readinfo]=wavread(self.sound_drumroll);
            sound(y,Fs)
            pause(5.8)
            self.four_cubes()
        end
        
        
        
        
        
    end
    
    
    
end

