make_vs_sort(:,1) = make_vs_sort(:,1) / 1000;

sizes = make_vs_sort(:,1);
make = make_vs_sort(:,2);
select = make_vs_sort(:,3);
sort = make + select;

figure;
subplot(1,2,1);
plot(
  sizes,make,'x','markersize',2,
  sizes,select,'x','markersize',2,
  sizes,sort,'x','markersize',2
);
grid;
title('Beitrag MakeHeap, HeapSelect.');
xlabel('Arraygroesse in 1000');
ylabel('Laufzeit in ms');
legend( 'MakeHeap', 'HeapSelect', 'HeapSort', 'location', 'northwest' );

subplot(1,2,2);
plot(
  sizes,100-make./sort*100,'x','markersize',2
);
grid;
title('Beitrag HeapSelect');
xlabel('Arraygroesse in 1000');
ylabel('Beitrag zur Gesamtlaufzeit in %');
legend( 'HeapSelect', 'location', 'northwest' );
ylim([80 100]);