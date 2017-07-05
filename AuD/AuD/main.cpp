#include "util.h"
#include "dheap.h"
#include "testcode.cpp"

int main( int argc, char* argv[] ) {
    int arg = argc < 2 ? 0 : atoi(argv[1]);
    if (arg < 1 || arg > 3) {
        cout<<
          "Syntax: dhsort N\n"
          " N = 1 - D-aeres Heapsort wird auf verschiedenen, zufaellig generierten, Arrays getestet\n"
          " N = 2 - Experimente 1-3 werden ausgefuehrt.\n"
          " N = 3 - Experiment 4 wird ausgefuehrt.\n";
        return 1;
    }
    if (arg == 1) {
        cout << "Kleine Testfaelle mit D == 2..." << endl;
        Test(1,10,2);
        cout << "Kleine Testfaelle mit D == 3..." << endl;
        Test(1,20,3);
        cout << "Mittlere Testfaelle mit verschiedenen D..." << endl;
        Test(1,100);
        cout << "Grosse Testfaelle mit verschiedenen D..." << endl;
        Test(1,10000,0,5);
        cout << "Test abgeschlossen" << endl;
    } else if (arg == 2) {
        ofstream os("octave-exeriments-1-3-online.m.txt");
        cout << "Experiment 1";
        writeOctaveVec<3>(os,string("cheapItems"),ScanD<CheapItem>());
        cout << "Experiment 2";
        writeOctaveVec<3>(os,string("largeItems"),ScanD<LargeItem>());
        cout << "Experiment 3";
        writeOctaveVec<3>(os,string("slowItem"),ScanD<SlowItem>());

        std::ifstream script("exp1-3.code.m");
        os << script.rdbuf();
        os.close();
    } else if (arg == 3) {
        ofstream os("octave-exeriments-4-online.m.txt");
        cout << "Experiment 4";
        writeOctaveVec<3>(os,string("make_vs_sort"), TimeMakeHeap());
        std::ifstream script("exp4.code.m");
        os << script.rdbuf();
        os.close();
    }
    getchar();
    cout<<endl;
    return 0;
}
