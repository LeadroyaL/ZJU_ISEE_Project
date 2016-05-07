function show_and_store(tracked_rect, t, img, s_frames, save_dir)
    % show tracking result and store some information
    if t == 1
        figure(500);
    end
    if ~exist(save_dir)
        mkdir(save_dir);
    end
    imshow(img);hold on;
    rectangle('Position', tracked_rect(:, t)', 'EdgeColor', [1 1 1]);hold on;
    text(50, 30, ['frame ' num2str(t)], 'Color', [1 0 0], 'Fontsize', 20); hold off;
    frm = getframe( 500 );
    [~, pure_name, ~] = fileparts(s_frames{t});
    imwrite(frm.cdata, [save_dir pure_name '.jpg']);
    

end