
plot( cheapItems(:,1),cheapItems(:,2)/1e7,'x','markersize',2 );
title('D-aeres Heapsort: Vergleichsanzahl');
xlabel('Parameter D');
ylabel('Vergleiche / 10^7');

figure;
plot( cheapItems(:,1),cheapItems(:,3)*1000,'x','markersize',2 );
title('Experiment 1: Arrayelemente klein, Schlüsselvergleiche schnell.');
xlabel('Parameter D');
ylabel('Laufzeit in ms');

figure;
plot( largeItems(:,1),largeItems(:,3)*1000,'x','markersize',2 );
title('Experiment 2: Arrayelemente groß, Schlüsselvergleiche schnell.');
xlabel('Parameter D');
ylabel('Laufzeit in ms');

figure;
plot( slowItem(:,1),slowItem(:,3)*1000,'x','markersize',2 );
title('Experiment 3: Arrayelemente klein, Schlüsselvergleiche langsam.');
xlabel('Parameter D');
ylabel('Laufzeit in ms');

figure;
