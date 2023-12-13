%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% The filter funtion
% \param x , the input vector
% \param c , the coefficients
% \param y, the filtered output (specified here so that the mex generation
%           will create a reference to y, allowing us to set its data type
%           outside the function)
% \return y, the filtered output
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function y = fir_m(x, c, y)
N = length(x); L = length(c); k = 1;
for i = 1 : N
    for j = 1 : min(i, L)
        y(i) = y(i) + x(i - j + 1) * c(j);
    end
end
end
