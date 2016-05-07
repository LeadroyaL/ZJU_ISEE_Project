function particle = convert_rect_2_particle(rect, sz_I)
    % Input:
    % rect: [x; y; width; height], where (x, y) is the top left point
    % sz_I: the base size
    % Output:
    % particle: [c_x; c_y; s_x; s_y], (c_x, c_y) is the center, s_x and s_y
    % are scales compared with sz_I
    
    % This function convert rectangle to particle
    
    c_x = rect(1) + rect(3)/2;
    c_y = rect(2) + rect(4)/2;
    s_x = rect(3) / sz_I(1);
    s_y = rect(4) / sz_I(2);
    particle = [c_x, c_y, s_x, s_y]';

end