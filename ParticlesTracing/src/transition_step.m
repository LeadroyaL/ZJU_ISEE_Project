function particles = transition_step(particles, stds)
    % Sample particles from gaussian distribution N(particles, stds)
    % Input:
    % particles:  a matrix of 4 rows and n_particles cols
    % stds: a 4 dimention vector, each is a standard deviation for a
    % dimension of particle
    % Ouput:
    % particles: output particles
    [~,n_particles] = size(particles);
    particles(1,:) = particles(1,:) + normrnd(0,1,1,n_particles)*stds(1);
    particles(2,:) = particles(2,:) + normrnd(0,1,1,n_particles)*stds(2);
    particles(3,:) = particles(3,:) + normrnd(0,1,1,n_particles)*stds(3);
    particles(4,:) = particles(4,:) + normrnd(0,1,1,n_particles)*stds(4);

end
