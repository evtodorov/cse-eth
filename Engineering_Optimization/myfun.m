function [ b ] = myfun( A )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    B = sort(A, 'descend');
    b = B(1,1);

end

