function [ out ] = OvR( multi_in )
%OVR 此处显示有关此函数的摘要
%   此处显示详细说明
    [height , width] = size(multi_in);
    out = zeros(height,1);
    for i  = 1 : height
        tp = multi_in(i,:);
        if(sum(tp)==0)
            out(i) = randi(width)-1;
        elseif(sum(tp)==1)
            out(i) = find(tp)-1;
        else
            tp = find(tp);
            out(i) = tp(randi(length(tp)))-1;
        end
    end
end
