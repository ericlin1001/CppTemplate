//Author: Ericlin(463222898@qq.com);
#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
//Toggle Debug mode.
#define Cpp_Debug2

#define it(i,l) for(int i=0;i<l;i++) 
//The following codes make debug mode active only when Makefile_Debug1 and Cpp_Debug2 is defined.
#ifdef Makefile_Debug1
#ifdef Cpp_Debug2
#define DEBUG
#endif
#endif
#ifdef DEBUG
//Debug mode's code
#define Trace(m) cout<<#m"=\""<<(m)<<"\""<<endl;
#define Test(m) m;
#define ASSERT(cond) if(!(cond)){cerr<<"ASSERT> "<<__FILE__<<"("<<__LINE__<<"): Conditon("#cond") fails!"<<endl;abort();}
#else
//Not-debug mode's code
#define Trace(m) 
#define Test(m) 
#define ASSERT(cond) 
#endif
using namespace std;


int main(){
    cout<<"Hello World."<<endl;
	int i=3;
	Trace(i);
	Test(cout<<"hello"<<endl;);
	ASSERT(i==3);
	ASSERT(i!=3);
    return 0;
}


