/*******************/
/* D-äres Heapsort */
/*******************/

// Folgende werte für D werten getestet:
const int D_MIN = 2;
const int D_MAX = 16;

/*
  Sei 'A[0..N-1]' die Arraydarstellung eines D-ären Heaps (linksvollständiger
  D-ärer Baum mit Min-Heapordnung, dessen Knoten sind in 'A' in Levelorder-
  Reihenfolge gespeichert) mit N Knoten und mit einer Fehlstelle am Knoten mit
  Index 'p'. (d.h. verringert man den Schlüssel von 'A[p]' wird 'A' zum Heap).
  Der Aufruf 'BubbleDown(A, N, p, D)' soll 'A' reparieren.

  Hinweis:
   1. Der Schlüssel des Elements 'A[i]' ist 'A[i].key()'.
  2a. Schlüssel haben den Typ 'T::KeyType',
  2b. zwei Schlüssel 'k0' und 'k1' können mit den Operatoren
	  'k0<k1', 'k0<=k1', 'k0>k1' und 'k0>=k1' verglichen werden.
   3. Arrayeinträge haben den Typ 'T'.

  Für eine effiziente Implementierung (kümmern Sie sich zunächst um Korrektheit!):
   4. Vermeiden Sie den Schlüssel des selben Array-Elements mehrfach zu berechnen
	  (speichern Sie den Schlüssel in einer lokalen Variable.)
   5. Vermeiden Sie Einträge, von Vater- und Kindknoten stets zu tauschen,
	  benutzen Sie folgende Idee:
	  Sei A[i0]=a0, A[i1]=a1, ..., A[iM]=aM eine Sequenz der von 'BubbleDown'
	  bearbeiteten (d.h. getauschten) Knoten vor der Bearbeitung.
	  Der Effekt von
		 swap(A[i0], A[i1]); swap(A[i1], A[i2]); ... swap(A[i(M-1)], A[iM]);
	  ist
		 A[i0]=a1, A[i1]=a2, ..., A[i(M-1)]=aM, A[iM]=a0.
	  Der selbe Effekt kann durch eine Sequenz von Zuweisungen erzeugt werden:
		 T tmp=A[i0]; A[i0]=A[i1]; A[i2]=A[i3]; ... A[i(M-1)]=A[iM]; A[iM]=tmp;
	  Statt drei Zuweisungen (swap) benötigt man nur eine Zuweisung pro Array-
	  zelle zzgl. der Zuweisung von 'tmp'! */
template<typename T>
inline void BubbleDown(vector<T> &A, const int N, int p, const int D) {
	typedef typename T::KeyType K;
	/// TODO Anfang

#define OPTIMIZED
#ifndef OPTIMIZED
  // unoptimized version

  // speichere schlüssel der Fehlstelle
	auto pKey = A[p].key();

	// berechne Indizes der Kinderknoten
	auto childIndexMin = p*D + 1;
	auto childIndexMax = (p + 1) * D;

	// prüfe, dass die berechneten Indizes im erlaubten Rahmen sind
	if (childIndexMax >= N) childIndexMax = N - 1;
	if (childIndexMin >= N) return;

	// Finde Schlüsselwert und Index des kleinsten Kindknotens
	auto swapIndex = childIndexMin;
	auto swapKey = A[swapIndex].key();

	for (auto i = childIndexMin + 1; i <= childIndexMax; i++)
	{
		auto curChildKey = A[i].key();
		if (curChildKey < swapKey)
		{
			swapKey = curChildKey;
			swapIndex = i;
		}
	}

	// Falls kleinster Kindknoten kleiner als Fehlstelle...
	if (swapKey < pKey) {
		// ... vertausche mit Fehlstelle
		swap(A[p], A[swapIndex]);
		// wiederhole mit Kindknoten (= neue Fehlstelle)
		return BubbleDown(A, N, swapIndex, D);
	}

#else
	// optimized

	// Speichere Schlüssel und Index der Fehlstelle
	auto pKey = A[p].key();
	auto pValue = A[p];

	// berechne Rahmen der Kindknoten (und überprüfe ob diese valide sind)
	auto childIndexMin = p*D + 1;

	while (childIndexMin < N)
	{
		auto childIndexMax = (p + 1) * D;

		// Finde kleinsten Kindknotenschlüssel und -index
		auto swapIndex = childIndexMin;
		auto swapKey = A[childIndexMin].key();

		for (auto i = childIndexMin + 1; i <= childIndexMax && i < N; ++i)
		{
			auto childKey = A[i].key();
			if (childKey < swapKey)
			{
				swapKey = childKey;
				swapIndex = i;
			}
		}

		// Falls alle Kinderknotenschlüssel größer als der Fehlstellenschlüssel ...
		if (pKey < swapKey)
		{
			// ... speicher die Fehlstelle als Elternknoten und beende BubbleDown
			A[p] = pValue;
			return;
		}

		// Setze Kind als Elternknoten
		A[p] = A[swapIndex];

		// Wiederhole mit ehemaligem Kindknoten als neuem Elternknoten
		p = swapIndex;
		childIndexMin = p*D + 1;
	}

	// Es gibt keine Kinderknoten mehr
	// Wert speichern und fertig
	A[p] = pValue;
#endif
	/// TODO Ende
}

/* Die Funktion 'MakeHeap(A, N, D)' arrangiert das Array 'A[0..N-1]' in einen
   D-ären Min-Heap um (Heapaufbauphase).

   Hinweis:
	 1. In der Heapaufbauphase ist der erste Knoten, an dem etwas zu tun ist,
		der Vater vom Knoten mit Index N-1.
	 2. Die Implementierung ist nur (etwa) zwei Zeilen! */
template<typename T>
void MakeHeap(vector<T> &A, const int N, const int D) {
	/// TODO Anfang

	for (auto i = (N - 1) / 2; i >= 0; --i)
	{
		BubbleDown(A, N, i, D);
        //add vomment
	}

	/// TODO Ende
}

/* Vorausgesetzt, das Array 'A[0..N-1]' ist ein D-ärer Min-Heap, sortiert die
   Funktion 'HeapSelect(A, N, D)' das Array 'A' absteigend.

   Hinweis:
	 1. Die Funktion 'swap(A[i], A[j])' tauscht die Elemente 'A[i]' und 'A[j]'.
	 2. Die Implementierung ist nur (etwa) drei Zeilen! */
template<typename T>
void HeapSelect(vector<T> &A, const int N, const int D) {
	/// TODO Anfang

	for (int k = N - 1; k >= 2; --k)
	{
		swap(A[0], A[k]);
		BubbleDown(A, k, 0, D);
	}
	if (N > 1) swap(A[0], A[1]);

	/// TODO Ende
}

/* Die Funktion 'DAryHeapSort(A, N, D)' sortiert
   das Array 'A[0..N-1]' mit D-ärem Heapsort. */
template<typename T>
void DAryHeapSort(vector<T> &A, const int N, const int D) {
	MakeHeap(A, N, D);
	HeapSelect(A, N, D);
}

/// TODO Anfang Exp4
const int BEST_D = 3; // hier in Experiment 1 ermittelten Wert für D eintragen
/// TODO Ende Exp4