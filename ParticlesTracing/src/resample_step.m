function particles = resample_step(particles, weights)
    % resaple particles according to weights
    % Input: 
    % particles: a 4xN matrix, each column is a particle
    % weights: a vector, each element corresponds to a particle
    % Output:
    % particles: resampled particles
    
    [~,n_particles] = size(particles);
    weights = round(n_particles * weights);
    %now weights is number maybe less maybe more
    s_sum = sum(weights);
    %make sum to N random add or dec
    if s_sum>n_particles
        for i = 1 : s_sum-n_particles
            while true
                tp = round(rand()*(n_particles-1))+1;
                if weights(tp)>0
                    weights(tp) = weights(tp) - 1;
                    break
                end
            end
        end
    elseif s_sum<n_particles
        for i = 1:n_particles-s_sum
            tp = round(rand()*(n_particles-1))+1;
            weights(tp) = weights(tp) + 1;            
        end
    end
    %renew particles
    outdata = [];
    for i = 1:n_particles
        n = weights(i);
        if n==0
            continue
        end
        if n == 1
            tp_particle = particles(:,i);
            outdata = [outdata tp_particle];
            continue
        end
        for j = 1:n
            tp_particle = particles(:,i);
            outdata = [outdata tp_particle];
        end
    end
    particles = outdata;
end