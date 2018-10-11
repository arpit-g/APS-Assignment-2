// template <typename T1>
// int hash(T1 k,int p) {
// 	ostringstream str;
// 	str<<k;
// 	string l = str.str();
// 	int h=0;
// 	for(int i=0;i<l.size();i++) {
// 		h = (h*31+l[i])%p;
// 	}
// 	return h;
// }

// template <typename T1, typename T2>
// int rebuild_hash(vector< pair< T1,list<T2> > > &v,int &p) {
// 	p = 2*v.size();
// 	vector< pair< T1,list<T2> > > tmp(p);	
// 	int cnt=0;
// 	for(int i=0;i<v.size();i++) {
// 		for(typename list<T2>::iterator it=v[i].second.begin();it!=v[i].second.end();it++) {
// 			int h = hash(v[i].first,p);
// 			tmp[h].first = v[i].first;
// 			if(tmp[h].second.size()==0) cnt++;		
// 			tmp[h].second.push_back(*it);
// 		}		
// 	}
// 	v.clear();
// 	v=tmp;
// 	return cnt;
// }

// template <typename T1, typename T2>
// void display(vector< pair< T1,list<T2> > > v) {
// 	for(int i=0;i<v.size();i++) {
// 		cout<<i<<" -> "<<v[i].first<<" - ";
// 		for(typename list<T2>::iterator it=v[i].second.begin();it!=v[i].second.end();it++) {
// 			cout<<*it<<" ";
// 		}
// 		cout<<endl;
// 	}
// }

// template <typename T1, typename T2>
// void insert(vector< pair< T1,list<T2> > > &v,T1 a,T2 b,int &p,int &cnt) {
// 	int h = hash(a,p);
// 	v[h].first = a;
// 	if(v[h].second.size()==0) cnt++;		
// 	v[h].second.push_back(b);
// 	if(float(cnt/p)>=0.75) cnt=rebuild_hash(v,p);
// }

#include<iostream>
#include<sstream>
#include<cstring>
#include<vector>
#include<list>
#include<cstdlib>

using namespace std;
#define debug(x) cout<<"Checkpoint "<<x<<endl

template <class T1,class T2>
class hashTable {

	int cnt,p;
	vector< list< pair<T1,T2> > > v;

public:

	hashTable(int t_size) {
		vector< list< pair<T1,T2> > > tmp(10);		
		v=tmp;
		cnt=0;
		p=t_size;
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
				// tmp[h].first = v[i].first;
				if(tmp[h].size()==0) cnt++;		
				tmp[h].push_back(make_pair(it->first,it->second));
			}		
		}
		v.clear();
		v=tmp;
		return cnt;
	}

	void insert(T1 a,T2 b) {
		int h = hash(a);
		if(v[h].size()==0) cnt++;
		v[h].push_back(make_pair(a,b));
		if(float(cnt/p)>=0.75) cnt=rebuild_hash();
	}

	string find(T1 a) {
		// T2 ret_val = 
		int h = hash(a);
		for(typename list< pair<T1,T2> >::iterator it=v[h].begin();it!=v[h].end();it++) {
			if(it->first==a) {
				ostringstream str;
				str<<it->second;
				string l = str.str();
				return l;
			}
		}		
		// if(T2==int) return -1;
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
	int p=10;

	hashTable<int,int>h1(10);
	h1.insert(23,65);
	h1.display();
	cout<<h1.find(23)<<endl;
	cout<<h1.find(10)<<endl;
	h1.remove(23);
	h1.display();
	cout<<endl;

	hashTable<string,int>h2(10);
	h2.insert("string 23",65);
	h2.display();
	cout<<h2.find("string 23")<<endl;
	h2.remove("string 23");
	h2.display();

	hashTable<string,string>h3(10);
	h3.insert("string 23","something");
	h3.display();
	cout<<h3.find("string 23")<<endl;
	h3.remove("string 23");
	h3.display();

	hashTable<int,string>h4(10);
	h4.insert(65,"string 23");
	h4.display();
	cout<<h4.find(65)<<endl;
	h4.remove(65);
	h4.display();
	return 0;
}