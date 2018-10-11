#include<iostream>
#include<sstream>
#include<cstring>
#include<vector>
#include<list>
#include<cmath>
#include<cstdlib>

using namespace std;

template <class T1,class T2>
class hashTable {

	int cnt,p;
	vector< list< pair<T1,T2> > > v;

public:

	hashTable(int t_size) {		
		cnt=0;
		p=getNextPrime(t_size);
		cout<<"Table Size - "<<p<<endl;
		vector< list< pair<T1,T2> > > tmp(p);		
		v=tmp;
	}

	int getNextPrime(int t_size) {
		bool flag=true;
		int i = t_size+1;
		while(flag==true) {
			flag=false;
			int limit = sqrt(i);	
			for(int j=2;j<=limit;j++) 
				if(i%j==0) flag=true;
			if(flag==true) i++;
		}
		return i;
	}

	int hash(T1 k) {
		ostringstream str;
		str<<k;
		string l = str.str();
		int h=0;
		for(int i=0;i<l.size();i++) {
			h = (h*31+l[i])%p;
		}
		return h;
	}

	int rebuild_hash() {
		p = 2*v.size();
		vector< list< pair<T1,T2> > > tmp(p);
		cnt=0;
		for(int i=0;i<v.size();i++) {
			for(typename list< pair<T1,T2> >::iterator it=v[i].begin();it!=v[i].end();it++) {
				int h = hash(it->first);
				if(tmp[h].size()==0) cnt++;		
				tmp[h].push_back(make_pair(it->first,it->second));
			}		
		}
		v.clear();
		v=tmp;
		return cnt;
	}

	void insert(T1 a,T2 b) {
		if(find(a)=="Not Found") {
			int h = hash(a);
			if(v[h].size()==0) cnt++;
			v[h].push_back(make_pair(a,b));
			if(float(cnt/p)>=0.75) cnt=rebuild_hash();
		}
		else cout<<"Key already present!"<<endl;
	}

	string find(T1 a) {
		int h = hash(a);
		for(typename list< pair<T1,T2> >::iterator it=v[h].begin();it!=v[h].end();it++) {
			if(it->first==a) {
				ostringstream str;
				str<<it->second;
				string l = str.str();
				return l;
			}
		}		
		return "Not Found";
	}

	void remove(T1 a) {
		int h = hash(a);
		for(typename list< pair<T1,T2> >::iterator it=v[h].begin();it!=v[h].end();it++) {
			if(it->first==a) {v[h].erase(it);break;}
		}
		
	}

	void display() {
		for(int i=0;i<v.size();i++) {
			cout<<i<<" -> ";
			for(typename list< pair<T1,T2> >::iterator it=v[i].begin();it!=v[i].end();it++) {
				cout<<"("<<it->first<<","<<it->second<<") ";
			}
			cout<<endl;
		}
	}
	
};

int main() {
	int p;
	cout<<"Enter hash table size - ";
	cin>>p;

	// hashTable<int,int>h1(p);
	// h1.insert(23,65);
	// h1.display();
	// cout<<h1.find(23)<<endl;
	// cout<<h1.find(10)<<endl;
	// h1.insert(23,60);
	// h1.insert(23,65);
	// h1.remove(23);
	// h1.display();
	// cout<<endl;

	// hashTable<string,int>h2(p);
	// h2.insert("string 23",65);
	// h2.display();
	// cout<<h2.find("string 23")<<endl;
	// h2.remove("string 23");
	// h2.display();

	// hashTable<string,string>h3(p);
	// h3.insert("string 23","something");
	// h3.display();
	// cout<<h3.find("string 23")<<endl;
	// h3.remove("string 23");
	// h3.display();

	// hashTable<int,string>h4(p);
	// h4.insert(65,"string 23");
	// h4.display();
	// cout<<h4.find(65)<<endl;
	// h4.remove(65);
	// h4.display();
	return 0;
}