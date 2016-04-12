clear all
[X,T] = prprob;
%zrobienie dla kazdej angielskiej litery matrycy 10x10

alfabet = [];
for j = 1:26
    tmp = X(:,j);
    tmp2 = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]';
    for i=1:5:35
        tmp2 = [tmp2;0; 0; 0; tmp(i:i+4); 0; 0];
    end
    tmp2 = [tmp2; [0 0 0 0 0 0 0 0 0 0]'];
    alfabet = [alfabet tmp2];
end

%dodanie do alfabetu polskich znakow

  a = alfabet(:,1);
  a(98:100) = 1;
  
  c = alfabet(:,3);
  c(7) = 1;
  c(16) = 1;
  
  e = alfabet(:,5);
  e(98:100) = 1;
  
  l = alfabet(:,12);
  l(36) = 1;
  l(45) = 1;
  l(63) = 1;
  l(72) = 1;
  
  n = alfabet(:,14);
  n(7) = 1;
  n(16) = 1;
  
  o = alfabet(:,15);
  o(7) = 1;
  o(16) = 1;
  
  s = alfabet(:,19);
  s(7) = 1;
  s(16) = 1;
  
  zi = alfabet(:,26);
  zi(7) = 1;
  zi(16) = 1;
  
  z = alfabet(:,26);
  z(6) = 1;
  
  alfabetPolski = [alfabet(:, 1) a alfabet(:, 2:3) c alfabet(:, 4:5) e alfabet(:, 6:12) l alfabet(:, 13:14) n ...
      alfabet(:, 15) o alfabet(:, 16:19) s alfabet(:, 20:26) zi z];
  clear a c e n o l z zi tmp tmp2 X i j s alfabet
  
  % okreslenie oczekiwanych danych wyjsciowych
  Cel = [];
  for i=1:35
      Cel = [Cel zeros(1, 35)'];
      Cel(i,i) = 1;
  end
  
  % konstrukcja pierwszej sieci i trenowania jej na oryginalnych literach
  net1 = feedforwardnet(80);
  view(net1)
  net1.divideFcn = '';
  net1 = train(net1, alfabetPolski, Cel);
  
  % konstrukcja drugiej sieci i trenowania jej na zakloconych literach
  numNoise = 10;
  Xn = min(max(repmat(alfabetPolski,1,numNoise)+randn(100,35*numNoise)*0.2,0),1);
  Tn = repmat(Cel,1,numNoise);
  net2 = feedforwardnet(80);
  net2 = train(net2, Xn, Tn);
  
  %wysiwetlenie diagramu bledow dla pierwszej i drugiej sieci majac po 10
  %zaklocen kazdej literki
  
  noiseLevels = 0:.05:1;
numLevels = length(noiseLevels);
percError1 = zeros(1,numLevels);
percError2 = zeros(1,numLevels);
for i = 1:numLevels
  Xtest = min(max(repmat(alfabetPolski,1,numNoise)+randn(100,35*numNoise)*noiseLevels(i),0),1);
  Y1 = net1(Xtest);
  percError1(i) = sum(sum(abs(Tn-compet(Y1))))/(35*numNoise*2);
  Y2 = net2(Xtest);
  percError2(i) = sum(sum(abs(Tn-compet(Y2))))/(35*numNoise*2);
end

figure
plot(noiseLevels,percError1*100,'--',noiseLevels,percError2*100);
title('Percentage of Recognition Errors');
xlabel('Noise Level');
ylabel('Errors');
legend('Network 1','Network 2','Location','NorthWest')

%dla wyswietlenia literki mala funkcja, w zaleznosci ktora litere chcemy
%wyswietlic to zmieniamy wartosc liczbowa w tmp = alfabetPolski(:,35);
%Mozna od 1 do 35. Nalezy odkomentowac od litera = []; do imshow(litera,[0 1])

% litera = [];
% tmp = alfabetPolski(:,35);
% for i = 1:10:100
%     litera = [litera; (tmp(i:i+9))'];
% end
% imshow(litera,[0 1])