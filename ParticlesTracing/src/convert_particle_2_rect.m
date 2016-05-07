function rect = convert_particle_2_rect(particle, sz_I)
    % Input:
    % particle: [c_x; c_y; s_x; s_y], (c_x, c_y) is the center, s_x and s_y
    % are scales compared with sz_I
    % sz_I: the base rect size
    % Output:
    % rect: [x; y; width; height], where (x, y) is the top left point
    % convert partilcle to rect
    %
    width = sz_I(1)*particle(3);
    height = sz_I(2)*particle(4);
    x = particle(1) - width / 2;
    y = particle(2) - height / 2;

    rect = floor([x, y, width, height]);

end
