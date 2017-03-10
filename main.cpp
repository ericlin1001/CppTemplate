#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#define it(i,l) for(int i=0;i<l;i++) 
//Toggle Debug mode.
#define DEBUG
//
#ifdef DEBUG
#define Trace(m) cout<<#m"=\""<<(m)<<"\""<<endl;
#define Test(m) m;
#define ASSERT(cond) if(!(cond)){cerr<<"ASSERT> "<<__FILE__<<"("<<__LINE__<<"): Conditon("#cond") fails!"<<endl;abort();}
#else
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
