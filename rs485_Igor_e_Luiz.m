clear;
close all;

fs = 1*10^(-6); % frequência de amostragem
t = [0:fs:0.1];

f = 5000; %Frequência do sinal

y = 4*square(2*pi*f*t);
plot(t,y) %y é o sinal onda quadrada
hold on

As = 5.1; %Amplitude do sinal

acc = 0;
for i=1:2:100
  v = (As/i)*sin(2*pi*i*f*t);
  acc = acc + v;
end

plot(t, acc); %acc soma de senoides
title('Sinal Digital');
%%
acc2 = 0;
Asr = 1; %Amplitude eco
for i=1:2:100
  eco = (Asr/i)*sin(2*pi*i*f*t+pi/2);
  
  acc2 = acc2 + eco; %Eco

end 

figure
plot(t, acc2 + acc);
title('Sinal com eco');

%%
ar = 1; %amplitude do ruido
fr = 60; %Frequência ruído
r = 0;
acc4 = 0;
for i=1:2:7
  r = (ar/i)*sin(2*pi*i*fr*t);
  acc4 = acc4 + r;
end

figure;
plot(t,acc4+acc)
%plot(t,acc4)
%acc3 = awgn(acc, 12, 'measured');
%plot(t,acc3)
hold on
%plot(t,acc)
%%
%Análise da frequência
my_fft(acc,f);
