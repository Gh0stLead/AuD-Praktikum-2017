#include<chrono>
#include<random>
#include<functional>

std::mt19937 randomEngine;

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::seconds;
using std::chrono::milliseconds;

void Test(int minSize, int maxSize, int D = 0, int minSec = 1) {
  auto t    = high_resolution_clock::now(), tprt = t;
  seconds d(minSec);

  typedef CheapItem  I;
  typedef I::KeyType K;
  vector<I> A; A.reserve(maxSize);

  /* use fixed D, if provided, otherwise random */
  std::uniform_int_distribution<int> dDist(D ? D : D_MIN, D ? D : D_MAX);
  std::uniform_int_distribution<int> sizeDist(minSize,maxSize);

  for (int i = 0; high_resolution_clock::now() - t < d; ) {
    int size = sizeDist(randomEngine);
    A.resize(size);

    // Array generieren, Häufigkeiten zählen
    std::uniform_int_distribution<int> elementDist(0,size);
    for(I &v : A) {
        v = I { K { elementDist(randomEngine) } };
    }

    vector<I> Aorig(A);
    vector<I> Acopy(A);

    // Sortieren
    DAryHeapSort(A, A.size(), dDist(randomEngine) );
    std::sort(Acopy.begin(),Acopy.end(),std::greater<I>());

    // Aufsteigend sortiert?
    if (!std::is_sorted(A.rbegin(), A.rend())) {
        cerr<<"\rFehler: HeapSort liefert keine sortierte Folge!" << endl;
    } else if (Acopy != A) {
        cerr<<"\rFehler: Nach HeapSort enthält das Array nicht mehr die selbe Menge von Elementen!" << endl;
    } else {
        static const char x[] = { '|', '/', '-', '\\', '|', '/', '-', '\\' };
        if (tprt - high_resolution_clock::now() > milliseconds(100)) {
            cout<<"\rAbbrechen mit STRG+C. Teste... "<<x[i&7];
        }
        continue;
    }
    if (A.size() < 20)
    cout << endl << "Eingabe Array:" << endl;
    for(I i: Aorig) cout << i.key() << ",";
    cout << endl << "Ausgabe:" << endl;
    for(I i: A) cout << i.key() << ",";
    cout << endl << "erwartet:" << endl;
    for(I i: Acopy) cout << i.key() << ",";
    exit(1);
  }

  cout<<"\rTest abgeschlossen.             "<<endl;
}

/* Returns tripples (D,#comp,time) */
template<typename I>
vector<array<double,3>> ScanD() {
  static const int N = 1000000; //Messung für diese Arraygröße
  static const int min_times(10); //so oft mindestens messen
  static const milliseconds min_time(500); //so lange mindestens messen

  vector<array<double,3>> results;

  vector<I> A(N);
  for(int i = 0; i < N; A[i] = I(i),i++);

  for(int D=D_MIN; D<=D_MAX; ++D) {
    total_cmps=0;
    auto t0 = high_resolution_clock::now();
    int times=0;
    while (times < min_times || high_resolution_clock::now() - t0 < min_time) {
      std::shuffle(A.begin(), A.end(),randomEngine);
      DAryHeapSort( A, A.size(), D );
      ++times;
    }
    duration<double> dt(high_resolution_clock::now() - t0);

    results.push_back({(double)D,(double)total_cmps/times,dt.count()/times});
    cout<<'.';
  }
  return results;
}

template<int P>
vector<array<double,2>> RunPhase() {
  static const int N  = 100000; //Messung für diese Arraygröße
  static const int DN =   5000; //Abstände
  static const int min_times(10); //so oft mindestens messen
  static const milliseconds min_time(500); //so lange mindestens messen

  //RNG zurücksetzen
  randomEngine.seed(42);

  vector<array<double,2>> results;
  vector<CheapItem> A; A.reserve(N);
  typedef CheapItem::KeyType K;

  for (int n=DN; n< (int)A.capacity(); n+=DN) {
    A.resize(n);
    total_cmps=0;
    auto t0 = high_resolution_clock::now();
    int times=0;
    while (times < min_times || high_resolution_clock::now() - t0 < min_time) {
      for (int j=0; j<(int)A.size(); ++j) A[j]= CheapItem{K{j}};
      std::shuffle(A.begin(), A.end(),randomEngine);
      switch (P) {
        case 0: MakeHeap(A, A.size(), BEST_D); break;
        case 1: DAryHeapSort(A, A.size(), BEST_D); break;
        default: break;
      }
      ++times;
    }

    duration<double> dt(high_resolution_clock::now() - t0);
    results.push_back({(double)n,dt.count()/times});
    cout<<'.';
  }
  return results;
}

vector<array<double,3>> TimeMakeHeap() {
  vector<array<double,2>> tMake = RunPhase<0>();
  vector<array<double,2>> tSort = RunPhase<1>();
  vector<array<double,2>> tGen  = RunPhase<2>();

  vector<array<double,3>> result;

  for(int D = D_MIN; D <= D_MAX; ++D) {
    int i = D - D_MIN;
    result.push_back({tMake[i][0],tMake[i][1]-tGen[i][1],tSort[i][1]-tMake[i][1]});
  }

  return result;
}

