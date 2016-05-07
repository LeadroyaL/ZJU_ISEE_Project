function [n_frames, s_frames] = readImageSequences(data_dir, img_type)
    names = dir([data_dir '*.' img_type]);
    n_frames = length(names);
    s_frames = cell(1, n_frames);
    for i = 1:n_frames
        s_frames{i} = [data_dir names(i).name];
    end
end