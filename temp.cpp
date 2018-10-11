// #include<iostream>
// #include<vector>
// #include<cstdlib>

// using namespace std;

// class stringBuilder {	

// public:

// 	const char* str;
// 	stringBuilder* next;
// 	stringBuilder(const char*);
// 	void append(stringBuilder* s);
// 	void display();
// };

// stringBuilder::stringBuilder(const char* str1) {
// 	str = str1;
// 	next = NULL;
// }

// void stringBuilder::append(stringBuilder* s) {
// 	stringBuilder* st = this;
// 	while(st->next!=NULL) st = st->next;
// 	st->next = s;
// }

// void stringBuilder::display() {
// 	int iter = 0;
// 	stringBuilder* s = this;
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

// int main() {
// 	stringBuilder s1 = stringInitialize("Hello World!");
// 	stringBuilder s2 = stringInitialize("I am Arpit.");	
// 	stringBuilder s3 = stringAppend(s1,s2);	
// 	s3.display();
// 	return 0;
// }

#include<iostream>

using namespace std;

void computeLPSArray(char* pat, int M, int* lps) 
{ 
    // length of the previous longest prefix suffix 
    int len = 0; 
  
    lps[0] = 0; // lps[0] is always 0 
  
    // the loop calculates lps[i] for i = 1 to M-1 
    int i = 1; 
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else // (pat[i] != pat[len]) 
        { 
            // This is tricky. Consider the example. 
            // AAACAAAA and i = 7. The idea is similar 
            // to search step. 
            if (len != 0) {
                cout<<i<<" "<<len<<" "; 
                len = lps[len - 1]; 
                cout<<len;
  
                // Also, note that we do not increment 
                // i here 
            } 
            else // if (len == 0) 
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 

int main() {
	char* pat = "BAABAB";
	int m=6;
	int lps[m];
	computeLPSArray(pat,m,lps);
	for(int i=0;i<m;i++) {
		cout<<lps[i]<<" ";
	}
	cout<<endl;
	return 0;
}