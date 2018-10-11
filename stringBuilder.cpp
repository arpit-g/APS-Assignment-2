// #include<iostream>
// #include<vector>
// #include<cstring>
// #include<cstdlib>

// using namespace std;

// class stringBuilder {	

// public:

// 	const char* str;
// 	// int t_size;
// 	stringBuilder* next;
// 	stringBuilder(const char*);
// 	void append(stringBuilder* s);
// 	void generateString();
// 	void display();
// };

// stringBuilder::stringBuilder(const char* str1) {
// 	str = str1;
// 	// t_size = sizeof(str1)/sizeof(char);
// 	// cout<<t_size<<endl;
// 	next = NULL;
// }

// void stringBuilder::append(stringBuilder* s) {
// 	stringBuilder* st = this;
// 	while(st->next!=NULL) st = st->next;
// 	st->next = s;
// 	// t_size += sizeof(s->str)/sizeof(const char*);
// }

// void generateString() {
// 	const char* st;

// }

// void stringBuilder::display() {
// 	int iter = 0;
// 	stringBuilder* s = this;
// 	// cout<<s->t_size;
// 	do {
// 		cout<<s->str;		
// 		s = s->next;
// 	}while(s!=NULL);
// 	cout<<endl;
// }

// stringBuilder stringInitialize(const char* str) {
// 	stringBuilder s(str);
// 	return s;
// }

// stringBuilder stringAppend(stringBuilder& s1,stringBuilder& s2) {
// 	stringBuilder s("");
// 	stringBuilder* tmp1 = &s1;
// 	stringBuilder* tmp2 = &s2;
// 	s.append(tmp1);
// 	s.append(tmp2);
// 	return s;
// }

// int* calculateLPS(const char* pat,int pat_length) {
// 	int lps[pat_length];
// 	int i=0,cnt=0;
// 	while(i<pat_length) {
// 		if(i==0) {lps[i]=0;i++;}
// 		else {
// 			if(pat[i]==pat[cnt]) {				
// 				cnt++;
// 				lps[i]=cnt;
// 				i++;
// 			}
// 			else {
// 				if(cnt==0) {
// 					lps[i]=0;
// 					i++;
// 				}
// 				else {
// 					cnt = lps[cnt-1];
// 				}
// 			}
// 		}
// 	}
// 	return lps;
// }

// int findSubstring(stringBuilder s,const char* pat) {
// 	int pat_length = strlen(pat);
// 	int* lps = calculateLPS(pat,pat_length);

// }

// int main() {
// 	stringBuilder s1 = stringInitialize("Hello World!");
// 	stringBuilder s2 = stringInitialize("I am Arpit.");	
// 	stringBuilder s3 = stringAppend(s1,s2);	
// 	s1.display();
// 	s3.display();
// 	return 0;
// }

#include<iostream>
#include<vector>
#include<cstring>
#include<cstdlib>

#define MAX 10000000
#define debug(x) cout<<"Checkpoint "<<x<<endl

using namespace std;

class stringBuilder {	

public:

	const char* str;
	vector<stringBuilder*> next;

	stringBuilder(const char*);
	void append(stringBuilder* s);
	char* generateString();
	void generateStringUtil(char *st,int *length);
	void display();
};

stringBuilder::stringBuilder(const char* str1) {
	str = str1;
}

void stringBuilder::append(stringBuilder* s) {
	next.push_back(s);
}

void stringBuilder::generateStringUtil(char* st,int *length) {
	int i=0;
	for(i=0;i<strlen(str);i++) {
		st[(*length)++]=str[i];
	}
	// int new_index = i+1;
	for(i=0;i<next.size();i++) {
		next[i]->generateStringUtil(st,length);
	}
}

char* stringBuilder::generateString() {
	// debug(1);
	char* st=new char[MAX];
	// debug(2);
	int length=0;
	generateStringUtil(st,&length);
	return st;
}

void stringBuilder::display() {
	cout<<str;
	for(int i=0;i<next.size();i++) {
		next[i]->display();
	}
}

stringBuilder stringInitialize(const char* str) {
	stringBuilder s(str);
	return s;
}

stringBuilder stringAppend(stringBuilder& s1,stringBuilder& s2) {
	stringBuilder s("");
	stringBuilder* tmp1 = &s1;
	stringBuilder* tmp2 = &s2;
	s.append(tmp1);
	s.append(tmp2);
	return s;
}

int* calculateLPS(const char* pat,int pat_length) {
	int* lps = new int[pat_length];
	int i=0,cnt=0;
	while(i<pat_length) {
		if(i==0) {lps[i]=0;i++;}
		else {
			if(pat[i]==pat[cnt]) {				
				cnt++;
				lps[i]=cnt;
				i++;
			}
			else {
				if(cnt==0) {
					lps[i]=0;
					i++;
				}
				else {
					cnt = lps[cnt-1];
				}
			}
		}
	}
	return lps;
}

int findSubstring(stringBuilder s,const char* pat) {
	int pat_length = strlen(pat);
	
	int* lps = calculateLPS(pat,pat_length);
	
	char* st = s.generateString();
	
	int i = 0,j = 0;
	while(i<strlen(st)) {
		// cout<<i<<" "<<j<<endl;
		debug("tmlk");
		debug(i);
		if(st[i]==pat[j]) {
			i++;j++;
		}

		if(j==pat_length) {
			return i-j;
		}

		//debug(i*i*i);
		else if(i<strlen(st) && st[i]!=pat[j]){
			if(j!=0)
			{
				cout<<sizeof(lps)/sizeof(int)<<" "<<j-1<<endl;
				j = lps[j-1];
			}
			else i++;
		}
	}
	// cout<<st;
	return -1;
}

void func(stringBuilder s) {
	// debug(0);
	char* st = s.generateString();
	cout<<st;
}

int main() {
	debug(1);
	stringBuilder s1 = stringInitialize("dsra");
	
	debug(2);
	stringBuilder s2 = stringInitialize("daba");	
	
	debug(3);
	stringBuilder s3 = stringAppend(s1,s2);	
	
	debug(4);
	int index = findSubstring(s3,"sr");
	
	debug(5);
	s3.display();
	
	debug(6);
	cout<<index<<endl;
	index = findSubstring(s2,"sr");
	cout<<index<<endl;

	// stringBuilder str1 = stringInitialize("DABA");
 //    stringBuilder str2 = stringInitialize("DABA");
 //    stringBuilder str3 = stringInitialize("CDAB");
 //    stringBuilder str4 = stringInitialize("ABCABAB");
 //    debug(0); 
 //    stringBuilder str5 = stringAppend(str1,str2); 
 //    debug(1);
 //    str5.display();
 //    stringBuilder str6 = stringAppend(str3,str4);
 //    stringBuilder str7 = stringAppend(str5,str6);
    // stringBuilder st1 = stringInitialize("hello");
    // stringBuilder st2 = stringInitialize("world");
    // stringBuilder st3 = stringInitialize("my");
    // stringBuilder st4 = stringInitialize("bae"); 
    // stringBuilder st5 = stringAppend(st1,st2); 
    // stringBuilder st6 = stringAppend(st3,st4);
    // stringBuilder st7 = stringAppend(st5,st6);
    // stringBuilder str8 = stringAppend(st7,st7);
    // str8.display();
    // cout<<endl;
    // st7.display();
    // cout<<endl;
    // cout<<findSubstring(str8, "yb")<<endl;
	
	return 0;
}