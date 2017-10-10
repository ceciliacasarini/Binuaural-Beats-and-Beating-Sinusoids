clear all
close all
clc

% Author: Cecilia Casarini

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                          BEATING SINUSOIDS                              %
%                                                                         %
% In this code a beating effect is created by summing two sinusoids       %
% having a small difference in their frequencies. The resulting signal    %
% will be a sinusoid of frequency corresponding to the lower among the two%
% multiplied by (or amplitude modulated by) a low frequency component with%
% frequency equal to the difference between the two original frequencies. %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Parameters ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

% Sample rate
Fs = 44100;

% Sample Period
Ts = 1/Fs;

% Duration (s)
Tf = 10;

% Amplitude
A = 1;

% Time vector
t = 0:Ts:Tf;

% Frequency 1 (Hz)
f1 = 440;

% Frequency 2 (Hz) slightly above frequency 1. A bigger difference between
% f1 and f1 results in a higher frequency of the beating effect.
f2 = 441;

% Angular frequency 1
w1 = 2*pi*f1;

% Angular frequency 2 
w2 = 2*pi*f2;


%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Sinudoids ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

% Sinusoid 1
s1 = sin(w1*t);

% Sinusoid 2
s2 = sin(w2*t);

% Sum of he two sinusoids
sum = s1+s2;

% Normalization
sum = sum./max(abs(sum));

%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Plot ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%

plot(t, s1, 'b', t, s2, 'r', t, sum, 'g')
title('Beating Sinusoids')
xlabel('Time')
ylabel('Amplitude')
legend('s1', 's2', 'Sum')


%~~~~~~~~~~~~~~~~~~~~~~~~~~~ Play and Save ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%

% Play
soundsc(sum, Fs, 16)

% Save
audiowrite('beating_sinusoids.wav', sum, Fs, 'bitspersample', 16);




