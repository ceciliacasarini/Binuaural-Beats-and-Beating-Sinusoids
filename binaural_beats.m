clear all
close all
clc

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                          BINAURAL BEATS                                 %
%                                                                         %
% In this code the binaural beats effect is obtained by expoiting two     %
% sinusoids with similar frequencies. They are played in two different    %
% channels (left and right) and the effect is created in the listener's   %
% without the need to multiply or add the two sinusoids.                  %
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

% Frequency 2 (Hz) slightly above frequency 1. 
f2 = 442;

% Angular frequency 1
w1 = 2*pi*f1;

% Angular frequency 2 
w2 = 2*pi*f2;


%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Sinudoids ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

% Sinusoid 1
s1 = sin(w1*t);

% Sinusoid 2
s2 = sin(w2*t);

% Binaural beats vector: the two sinusoids are respectively put in two
% different channels. They are not added nor multiplied.
s = [s1;s2];
s = s'; % Needed to communicate that the number of channels is 2 and not 44101

%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Plot ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%

plot(t, s1, 'b', t, s2, 'r', t, s, 'g')
title('Binaural Beats')
xlabel('Time')
ylabel('Amplitude')
legend('s1', 's2', 'Binaural Beats')


%~~~~~~~~~~~~~~~~~~~~~~~~~~~ Play and Save ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%

% Play
soundsc(s, Fs, 16)

% Save
audiowrite('stereo binaural_beats.wav', s, Fs, 'bitspersample', 16);
           
