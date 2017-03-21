//Author: Ericlin(463222898@qq.com);
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#include<map>

//C++11
#if 1
#include<unordered_map>
#endif


using namespace std;
template<class T>
void printArr(const T& arr){
	cout<<"[";
	int len=arr.size();
	if(!arr.empty())cout<<arr[0];
	for(int i=1;i<arr.size();i++){
		cout<<", "<<arr[i];
	}
	cout<<"]";
	cout<<endl;
}

#define it(i,l) for(int i=0;i<l;i++) 
#define its(i,b,l) for(int i=b;i<l;i++) 

//Toggle Debug mode.
#define Cpp_Debug2
//The following codes make debug mode active only when Makefile_Debug1 and Cpp_Debug2 is defined.
#ifdef Makefile_Debug1
#ifdef Cpp_Debug2
#define DEBUG
#endif
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

int main(){
    cout<<"Hello World."<<endl;
	int i=3;
	Trace(i);
	vector<int>a;
	it(i,4)a.push_back(i*3);
	Test(printArr(a));
	cout<<endl;
	Test(cout<<"hello"<<endl;);
	ASSERT(i==3);
	ASSERT(i!=3);
    return 0;
}


