% main file of Tracking
% author : LeadroyaL
clc;
clear;
close all;

%% Parameter initialization
dataset = 'David'; % 'car' or 'David'
sz_I = [15, 15]; % width, height
if strcmp(dataset, 'car')
    data_dir = '../data/car/imgs/';
    save_dir = '../data/car/results/';
    ini_rect = [63 50 116 91]';% Initial position [x y width height]
    suffix = 'jpg';
elseif strcmp(dataset, 'David')
    data_dir = '../data/David2/imgs/';
    save_dir = '../data/David2/results/';
    ini_rect = [127, 55, 56, 56];
    suffix = 'jpg';
end

% initial particle, [c_x, c_y, s_x, s_y], (c_x, c_y) is the center
% location, s_x and s_y are scales compared with sz_I
ini_particle = convert_rect_2_particle(ini_rect, sz_I);
n_particles = 400; % Number of particles
stds = [4, 4, 0.03, 0.03]; % standard deviation of [c_x, c_y, s_x, s_y]
feature_type = 'intensity'; % The default feature, you may use another
% feature if you want, see feature_extract function

%% process
% the second parameter is 'jpg' for car and png for bolt
[n_frames, s_frames] = readImageSequences(data_dir, suffix);
img = imread(s_frames{1});
current_rect = ini_rect;
current_state = ini_particle;
% tracked_rect stores rectangles from t = 0  to t = T
tracked_rect = zeros(4, n_frames);
tracked_rect(:, 1) = current_rect;
particles = repmat(current_state, 1, n_particles); %Lead---->400��һëһ���ĵ�
% y is the representation of image in last tracked rect
y = feature_extract(img, current_rect, sz_I, feature_type); % Lead--->225*1 double����Ϊsz_I��15*15
show_and_store(tracked_rect, 1, img, s_frames, save_dir)

for t = 2:n_frames
    % "Transition" step, sample particles from gaussian model N(particles, stds)
    particles = transition_step(particles, stds);
    img = imread(s_frames{t});

    % "Weighting" step, compute weights of particles, inside this function,
    % you need to use feature_extract function to extract features of
    % particles and use compute_similarity function to compute similarity
    % between particles and last tracked rect
    % Note: weights should be normalized to sum to 1
    weights = weighting_step(img, particles, sz_I, y, feature_type);

    % choose particle with largest weight and compute feature of it
    [~, idx_max] = max(weights);
    current_state = particles(:, idx_max);
    current_rect = convert_particle_2_rect(current_state, sz_I);
    tracked_rect(:, t) = current_rect;

    % in 'car' y should not change, in 'David' y should change
    % because 'car' moves less and effected by backgound and
    % 'David' moves more and effected by itself
    if strcmp(dataset,'David')
        y = feature_extract(img, current_rect, sz_I, feature_type);
    end

    % show tracked rect
    show_and_store(tracked_rect, t, img, s_frames, save_dir);

    % "Resample" step
    particles = resample_step(particles, weights);
    %pause(0.1);
end
