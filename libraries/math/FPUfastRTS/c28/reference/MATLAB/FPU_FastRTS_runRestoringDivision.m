%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  Restoring Division (Slow Division)
% \author Vishal Coelho
% \date   03/21/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% Restoring Division (Integer) Function
%
%% Required Parameters
% * *N* , Numerator integer
% * *D* , Denominator integer
%
%% Returns
% * *Q* , the quotient
% * *R* , the remainder

%% Function Prototype
%
function [Q, R] = FPU_FastRTS_runRestoringDivision(N, D)
% figure out the number of digits in the numerator
n = max(numel(dec2bin(N)), numel(dec2bin(N)));

% The following works for n < 32. for n == 32 bit shifting the numerator
% up 32 places may result in wrapping the number over to the negative range
% NOTE: you can just use the else portion to do the division for n < 32 but
% you need to do it 32 times even though the numerator has fewer bits
if(n < 32)
    % Start with the partial remainder equal to the numerator, and divisor
    % shifted up 'n' places. P and D need twice the width of N and Q
    P = N;
    D = bitshift(D, n);
    Q = 0;
    for i  = n -1 : -1 : 0
        % Multiply the partial remainder by the radix (2) and figure out if its
        % greater than the divisor. If it is you can obviously divide once so
        % place a 1 in the ith place of the quotient.
        T = bitshift(P,1);
        P = T - D;
        if(P >= 0)
            % Q(i) = 1
            Q = bitor(Q, bitshift(1, i));
        else
            % P < 0 meaning 2P < D, no quotient bit for this i so lets just
            % restore P to its original
            % Q(i) = 0 -- by default bit position i is 0
            P = T;
        end
    end
    
    % The final remainder is in P, but this will now be shifted up by n, we
    % shifted it back down
    R = bitshift(P, -n);
else
    R = 0;
    % Shift remainder up 1, tack on most significant bit of the numerator
    % and subtract the denominator to see if its negative; if T is positive
    % D divides it once so incrment thr quotient else keep shift up the
    % numerator bits
    for i = 0 : n-1
        T = bitshift(R,1) + bitshift(N,-(n-1)) - D;
        if(T >= 0)
            R = bitand(T, 2^n - 1);
            N = bitshift(N,1) + 1;
            N = bitand(N , 2^n - 1); %only keep n bits
        else
            % shift the remainder up 1 and tack on the MSb of the numerator
            % keep n+1 bits; shift up the numerator 1 and keep only n bits
            R = bitshift(R,1) + bitshift(N,-(n-1));
            R = bitand(R, 2^(n+1)-1);
            N = bitand(bitshift(N,1), 2^n - 1);
        end
    end
    Q = N;
end
%%
% End of file
