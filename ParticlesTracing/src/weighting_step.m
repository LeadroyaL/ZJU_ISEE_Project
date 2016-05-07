function weights = weighting_step(img, particles, sz_I, y, feature_type)
    % This function first compute feature for each particle, then compute
    % similarity between features of particles and y

    % Input:
    % img: input image
    % particles: a 4xN matrix, each col corresponds to a particle state
    % sz_I: base size that a rect should be resized to
    % y: the feature of the last tracked rect.
    % feature_type: the type of feature
    % Oputput:
    % weights: a vector, each element corresponds to a particle

    %calc particles_feature 255*400
    [~,n_particles] = size(particles);
    particles_feature = zeros( sz_I(1)*sz_I(2) , n_particles );
    for i = 1:n_particles
        tp_rect = convert_particle_2_rect( particles(:,i) , sz_I );
        tp_feature = feature_extract(img, tp_rect, sz_I, feature_type);
        particles_feature(:,i) = tp_feature;
    end

    %calc similarity to y
    similarity = compute_similarity(particles_feature,y);
    weights = similarity / sum(similarity);
end
