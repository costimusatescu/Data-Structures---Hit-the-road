// Copyright 2018 Musatescu Costin-Teodor 314CA
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

using namespace std;

// Structura pentru retinerea valorilor pereche de tip cheie-valoare
template <typename Tkey, typename Tvalue> struct elem_info {
  Tkey key;
  Tvalue value;
};

template <typename Tkey, typename Tvalue> class Hashtable {
private:
  // *H pointer la buckets de tip arraylist
  std::list<struct elem_info<Tkey, Tvalue> > * H; 
  int HMAX; // nr de bucketuri
  unsigned int (*hash)(Tkey);  // pointer la o functie hash

public:
	// Constructor, unde *h e functia de hash
  Hashtable(int hmax, unsigned int (*h)(Tkey)) {
	this->HMAX = hmax;
	this->hash = h;
	H = new std::list<struct elem_info<Tkey, Tvalue> >[HMAX];
  }

  ~Hashtable() {
    // Destructor
    delete[] H;
  }

  // Pune o pereche cheie valoare in hashtable
  void put(Tkey key, Tvalue value) {
    int hashValue = hash(key) % HMAX;
    struct elem_info<Tkey, Tvalue> newElem;
    newElem.key = key;
    newElem.value = value;

    bool found = false;

    typename std::list<struct elem_info<Tkey, Tvalue> >::iterator i;
    for (i = H[hashValue].begin(); i != H[hashValue].end(); i++) {
        if (i->key == key) {
            i->value = value;
            found = true;
        }
    }
    if (!found) {
        H[hashValue].push_back(newElem);
    }
  }
	
  // Scoate entry-ul cu cheia key din hashtable  
  void remove(Tkey key) {
    int hashValue = hash(key) % HMAX;
    typename std::list<struct elem_info<Tkey, Tvalue> >::iterator i;
    for (i = H[hashValue].begin(); i != H[hashValue].end(); i++) {
        if (i->key == key) {
            break;
        }
    }
    if (i != H[hashValue].end()) {
        H[hashValue].erase(i);
    }
  }

  // Intoarce valoarea de la cheia key
  Tvalue get(Tkey key) {
    int hashValue = hash(key) % HMAX;
    typename std::list<struct elem_info<Tkey, Tvalue> >::iterator i;
    for (i = H[hashValue].begin(); i != H[hashValue].end(); i++) {
        if (i->key == key) {
            return i->value;
        }
    }
    return Tvalue();
 }
  bool has_key(Tkey key) {
      int hashValue = hash(key) % HMAX;
      typename std::list<struct elem_info<Tkey, Tvalue> >::iterator i;
      for (i = H[hashValue].begin(); i != H[hashValue].end(); i++) {
          if (i->key == key) {
              return true;
          }
      }
      return false;
  }
};

#endif // HASHTABLE_H_
