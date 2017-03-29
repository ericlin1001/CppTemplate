//Author: Ericlin(463222898@qq.com);
#include<iostream>
#include "HashMap.h"
using namespace std;

#define it(i,l) for(int i=0;i<l;i++) 
#define its(i,b,l) for(int i=b;i<l;i++) 

//Toggle Debug mode.
//#define Cpp_Debug2
//The following codes make debug mode active only when Makefile_Debug1 and Cpp_Debug2 is defined.
#ifdef Makefile_Debug1
#ifdef Cpp_Debug2
#define DEBUG
#endif
#endif

#ifdef Trace
#undef Trace
#endif
#ifdef Test
#undef Test
#endif

#ifdef DEBUG
//Debug mode's code
#define DEBUG_TAG "Debug> "
#define Trace(m) cout<<DEBUG_TAG#m"=\""<<(m)<<"\""<<endl;
#define Test(m) cout<<DEBUG_TAG#m<<":";m;
#define ASSERT(cond) if(!(cond)){cerr<<DEBUG_TAG"ASSERTION in "<<__FILE__<<"("<<__LINE__<<"): Conditon("#cond") fails!"<<endl;abort();}
#else
//Not-debug mode's code
#define Trace(m) 
#define Test(m) 
#define ASSERT(cond) 
#endif
using namespace std;

#ifdef DEBUG

#endif

void testMapInt(){
	HashMap<int, int> map;
	map.print();
	map.put(1,3);
	map.put(2,8);
	map.print();
	Trace(*map.get(1));
	Trace(map[2]);
	Trace(map[4]);
	map[4]=18;
	Trace(map[4]);
	Trace(map[1]);
	map[9]=19;
	map[9]=18;
	map[4]=18;
	map[6]=18;
	Trace(map[9]);
	map.print();
	cout<<"Testing..."<<endl;
	const int num=100;
	it(i,num){
		map[i]=i*10;
	}
	it(i,num){
		map[i]=-i*10;
	}
	it(i,num){
		if(map[i]!=-i*10){
			cout<<"Error*******************"<<endl;

		}
	}
	map.print();
}
void testCharInt(){
	HashMap<char, int> map;
	cout<<"Testing..."<<endl;
	const int num=50;
	it(i,num){
		map['a'+i]=i*10;
	}
	it(i,num){
		map['a'+i]=-i*10;
	}
	it(i,num){
		if(map['a'+i]!=-i*10){
			cout<<"Error*******************"<<endl;
		}
	}
	map.print();
}
template<class T>
void tt(T t){
	cout<<"t1"<<endl;
}
template<class T>
void tt(T* t){
	cout<<"t2"<<endl;
}
void testCharString(){
	HashMap<char, const char*> map;
	cout<<"Testing..."<<endl;
	const int num=3;
	it(i,num){
		map['a'+i]="hello";
	}
	map['a']=" world";
	map.print();
	int i=3;
	tt(i);
	tt(&i);
}

void 	testHash(){
	DefaultHash<long long> ff;
	DefaultHash<int> af;
	Trace(ff(3));
	Trace(ff(5432112312345678));
	Trace(ff(312345678));
	Trace(ff(123));
	Trace(ff("abc"));
	Trace(ff("abc"));
	Trace(ff("abcd"));
	Trace(ff('a'));
	Trace(ff('a'));
	Trace(ff('b'));
}
void TestEq(){
	DefaultEqual<const char *> eq;
	Trace(eq("abc","abc"));
	Trace(eq("abc","rbc"));
}
int main(){
	testMapInt();
	testCharInt();
	testHash();
	TestEq();

	//This doen't do a deep copy.
	HashMap<const char *,int>m;
	char t[]="abc";
	/*
	   m[t]=5;
	   m.print();
	   Trace(m[t]);
	   Trace(m["abc"]);
	   m.print();
	   Trace(m[t]);
	   */

	m["abc"]=3;
	m["abcd"]=4;
	m["abc"]=2;
	Trace(m["abc"]);
	Trace(m[t]);
	Trace(m["abcd"]);
	Trace((long long)&("abc"));
	Trace((long long)&("abc"));

	return 0;
}


