#include<iostream>  // cout
#include<fstream> // ofstream
#include<algorithm> // swap
#include<vector>  // vector
#include<array>
#include<string>

using std::vector;
using std::array;
using std::endl;
using std::cout;
using std::cerr;
using std::string;
using std::ofstream;
using std::swap;
using std::cin;

////////////////////////////////////////////////////////////////////////////////


/* Mitzählen, wie oft Vergleiche stattfinden */
int64_t total_cmps;
int z; //dummy
/* Schlüssel haben Templateparameter, der beeinflusst,
 * wie teuer Vergleiche sind */
template<int extra_cmp_cost>
struct Key {
    int x;
    Key() : x(0) {};
    Key(int x) : x(x) {};
    inline bool operator<=( const Key& k ) const { ++total_cmps; for (int i=0; i<extra_cmp_cost; z+=z+i++); return x<=k.x; }
    inline bool operator>=( const Key& k ) const { ++total_cmps; for (int i=0; i<extra_cmp_cost; z+=z+i++); return x>=k.x; }
    inline bool operator< ( const Key& k ) const { ++total_cmps; for (int i=0; i<extra_cmp_cost; z+=z+i++); return x< k.x; }
    inline bool operator> ( const Key& k ) const { ++total_cmps; for (int i=0; i<extra_cmp_cost; z+=z+i++); return x> k.x; }
    inline bool operator==( const Key& k ) const { return x==k.x; }
    inline bool operator!=( const Key& k ) const { return x!=k.x; }
};
template<int extra_cmp_cost>
std::ostream & operator <<(std::ostream &os, const Key<extra_cmp_cost>& k) {
    return os << k.x;
}

/* Item mit Größe (und damit Kopierkosten) extraSize
   sowie Vergleichskosten cmp_cost */
template<int extraSize, int extra_cmp_cost>
struct Item {
    typedef Key<extra_cmp_cost> KeyType;
    typedef int ValueType;
    KeyType k;
    ValueType v[extraSize];
    Item() {}
    Item( const KeyType k ) : k(k) { }
    KeyType key() const { return k; }
    inline bool operator<=( const Item& i ) const { return k<=i.k; }
    inline bool operator>=( const Item& i ) const { return k>=i.k; }
    inline bool operator< ( const Item& i ) const { return k< i.k; }
    inline bool operator> ( const Item& i ) const { return k> i.k; }
    inline bool operator==( const Item& i ) const { return k==i.k; }
    inline bool operator!=( const Item& i ) const { return k!=i.k; }
};

// E=0: Objekte klein, Vergleich billig
// E=1: Objekte groß, Vergleich billig
// E=2: Objekte klein, Vergleich teuer

typedef Item< 0, 0> CheapItem;
typedef Item<16, 0> LargeItem;
typedef Item< 0,32> SlowItem;


/* write vector into an octave script  */
template<int i>
void writeOctaveVec(std::ostream &os, const string &name, const vector<std::array<double,i>> vec) {
    cout << "Writing " << name << endl;
    os << name << " = [";
    for (auto v: vec) {
        for(auto x: v)
            os << x << ",";
        os << ";";
    }
    os << "];" << endl;
}
