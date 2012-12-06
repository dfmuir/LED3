switch current_slide
    case 0
        c.intro()
    case 1
        c.set_cube(c.blue)
    case 2
        c.set_cube(c.red)
    case 3
        c.set_cube(c.green)
    case 4
        c.set_cube(c.white)
    case 5
        c.set_cube(c.cyan)
    case 6
        c.set_cube(c.yellow)
    case 7
        c.set_cube(c.pink)
    case 8
        c.dark()
    case 9
        c.four_cubes()
    case 10
        c.flag()
    case 11
        c.cube()
    case 12
        c.rain()
    case 13
        c.led()
    case 14
        c.rotate()
    case 15
        c.alien()
    case 16
        c.a()
    case 17
        c.rainbow()
        
    

end

current_slide = current_slide + 1
    
            
