#ifndef  _HASH_MAP_H_
#define _HASH_MAP_H_
#include <vector>
#include <limits.h>
using namespace std;
#define Test(m) 
#define Trace(m) 
#define it(i,l) for(int i=0;i<l;i++) 
#define its(i, b, l) for(int i=b;i<l;i++) 
template<class B>
class DefaultEqual{
	public:
		template<class T>
		bool operator()(const T &a, const T &b){
			//what if a, b is a char *
			return a==b;
		}
		bool operator()(const char *a, const char *b){
			//what if a, b is a char *
			while(*a && *a++==*b++);
			return *a==0 && *b==0;
		}
};

template<class B>
class DefaultHash{
	//Basically, return the sume of memroy it occupied.
	typedef int HashType;
	public:
		HashType operator()(const int& key){
			Test(cout<<"const int&"<<endl);
			return key;
		}
		HashType operator()(const char& key){
			Test(cout<<"const char&"<<endl;);
			return (int)key;
		}
		HashType operator()(const char* key){
			Test(cout<<"const char*"<<endl;);
			typedef unsigned char byte;
			const int tlen=sizeof(HashType);
			HashType hash=0;
			byte *f = (byte *)key;
			byte *t = (byte *)&hash;
			for(int i=0; key[i] != '\0'; i++){
				t[i%tlen]+=f[i];	
			}
			return hash;
		}
		template<class T>
		HashType operator()(const T* key){
			Test(cout<<"const T *"<<endl;);
			typedef unsigned char byte;
			const int flen=sizeof(T);
			const int tlen=sizeof(HashType);
			HashType hash=0;
			byte *f = (byte *)key;
			byte *t = (byte *)&hash;
			it(i,flen){
				t[i%tlen]+=f[i];	
			}
			return hash;
		}
		template<class T>
		HashType operator()(const T& key){
			Test(cout<<"const T&"<<endl;);
			typedef unsigned char byte;
			const int flen=sizeof(T);
			const int tlen=sizeof(HashType);
			HashType hash=0;
			byte *f = (byte *)&key;
			byte *t = (byte *)&hash;
			it(i,flen){
				t[i%tlen]+=f[i];	
			}
			return hash;
		}
};

/*
 * If type of key is use-defined class, you have better implement the hashKeyFunc
 * Since, the default hashKeyFunc is based on the value of key object occupied.
 * */
template<class Key, class Value, class HashKeyFunc=DefaultHash<Key>, class KeyEqFunc=DefaultEqual<Key> >
class HashMap{
	//typedef int Key;
	//typedef int Value;
	int capacity;
	HashKeyFunc hashKeyFunc;
	KeyEqFunc keyEqFunc;
	int size;
	Value defaultValue=Value();
	struct Entry{
		Key key;
		int hashKey;
		Value value;
		Entry *next=0;
		Entry(){};
		Entry(Key k, Value v, Entry*n, int hk):key(k), value(v), next(n), hashKey(hk){}
	};
	vector<Entry *>table;
	//
	float loadFactor;
	int threshold;
	private:
	void rehashTable(int len){
		//rehash [0,len) to [0, capacity)
		it(i, len){
			//deal with head.
			Entry *n=table[i];
			int k;
			while(n !=nullptr && (k=indexForTable(n->hashKey))!=i){
				//rehash n
				//dettach n, and attach n to table[k].
				Entry *p=n->next;
				table[i]=p;
				n->next=table[k];
				table[k]=n;
				n=p;
			}
			//deal with ...
			Entry *p;
			while((p = n->next) != nullptr){
				if((k = indexForTable(p->hashKey)) != i){
					n->next=p->next;
					p->next=table[k];
					table[k]=p;
					//no need to change n, to point to n->next, since n->next has been removed.
				}else{
					n=p;
				}
			}
		}
	}
	void checkIfSize(){
		if(capacity>(INT_MAX>>1)){
			//capacity canot be bigger.
			//increase the loadFactor, decease the efficency
			//the following two lines's not needed.
			return ;
			//loadFactor+=loadFactor;
			//threshold=loadFactor*capacity;
			//return ;
		}
		if(size>=threshold){
			//resize
			int newCap=capacity<<1;
			table.resize(newCap);
			its(i,capacity,newCap){
				table[i]=nullptr;
			}
			capacity=newCap;
			threshold=loadFactor*capacity;
			rehashTable(capacity>>1);
		}
	}
	void init(int initCapacity=1, float initLoadFactor=2, Value initDefaultValue=0){
		this->~HashMap();
		defaultValue=initDefaultValue;
		capacity=1;
		while(capacity<initCapacity){
			capacity<<=1;
		}
		table.resize(capacity);
		it(i,capacity){
			table[i]=nullptr;
		}
		//
		size=0;
		loadFactor=initLoadFactor;
		threshold=loadFactor*capacity;
	}
	int indexForTable(int hash) const{
		//same as hash%capacity.
		//since capacity=2^k.
		//It doesn't matter if hash<0;
		return hash&(capacity-1);
	}
	Entry *addEntry(int tableIndex, Key key, Value value, int hashKey){
		//add a entry(key, value) with it's next =next.
		checkIfSize();
		Entry *entry=new Entry(key, value, table[tableIndex], hashKey);
		table[tableIndex]=entry;
		size++;
		return entry;
	}
	int getHash(const Key &key) const{
		return ((HashKeyFunc)hashKeyFunc)(key);
	}
	public:
	/*
	 * loadFactor: control when to increase capacity..
	 */
	HashMap(int initCapacity=1, float initLoadFactor=2, Value initDefaultValue=Value()){
		init(initCapacity, initLoadFactor, initDefaultValue);
	}
	void print()const {
		Trace(capacity);
		Trace(threshold);
		Trace(size);
		cout<<"Table["<<endl;
		it(i, table.size()){
			if(table[i] == nullptr) continue;
			cout<<i<<":";
			Entry *e;
			for(e=table[i]; e != nullptr; e = e->next){
				cout<<"("<<e->key<<","<<e->value<<"),";
			}
			cout<<endl;
		}
		cout<<"]"<<endl;
	}
	~HashMap(){
		it(i,table.size()){
			Entry *e = table[i];
			while(e != nullptr){
				Entry *p=e->next;
				delete e;
				e = p;
			}
		}
	}
	Value &put(const Key &key, const Value &value){
		int hashKey = getHash(key);
		int tableIndex = indexForTable(hashKey);
		for(auto i = table[tableIndex]; i != nullptr; i = i->next){
			if( (i->hashKey == hashKey)  && keyEqFunc(i->key, key) ){
				//this only support unique key.
				i->value = value;
				return i->value;
			}
		}
		//add new entry:
		return addEntry(tableIndex, key, value, hashKey)->value;
	}
	Value &operator[](const Key &key){
		Entry *e = getEntry(key);
		if( e == nullptr){
			return put(key, defaultValue);
		}else{
			return e->value;
		}

	}
	const Value &operator[](const Key &key) const{
		const Entry *e = getEntry(key);
		if( e == nullptr){
			return defaultValue;
		}else{
			return e->value;
		}
	}
	bool checkKey(const Key &key)const{
		return getEntry(key) != nullptr;
	}
	Value *get(const Key& key){
		//TODO:: how to return a null object.
		//
		int hashKey = getHash(key);
		int tableIndex = indexForTable(hashKey);
		for(auto i = table[tableIndex]; i != nullptr; i = i->next){
			if( (i->hashKey == hashKey) && keyEqFunc(i->key, key)){
				return  &(i->value);
			}
		}
		return nullptr;
	}
	private:
	const Entry *getEntry(const Key &key) const{
		return (const Entry*)((HashMap*)this)->getEntry(key);
	}
	Entry *getEntry(const Key &key){
		int hashKey = getHash(key);
		int tableIndex = indexForTable(hashKey);
		for(auto i = table[tableIndex]; i != nullptr; i = i->next){
			if( (i->hashKey == hashKey)  && keyEqFunc(i->key, key)){
				return  i;
			}
		}
		return nullptr;
	}
};
#endif

