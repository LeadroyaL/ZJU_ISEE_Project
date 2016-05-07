function s = compute_similarity(Y, y)
    % Compute similarity between y and Y
    % Input:
    % Y: a dxN matrix, d is the dimension of feature, N is number of particle
    % Y contains features for each particle
    % y: feature of the last tracked rect
    % Ouptput:
    % s: a vector indicates the similarity between each column of Y and y

    %similarity = sum(abs(Y-y))
    [~,n_particles] = size(Y);
    s = zeros(1,n_particles);
    for i = 1 : n_particles
        s(i) = abs(corr2(Y(:,i),y));
    end    
end
