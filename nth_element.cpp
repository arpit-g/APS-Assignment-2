// #include<iostream>
// #include<cstdlib>
#include<bits/stdc++.h>

using namespace std;

void swap(int *m,int *n) {
	int tmp = *m;
	*m = *n;
	*n = tmp;
}

int partition(int a[],int low,int high,int pivot) {
	swap(&a[high],&a[pivot]);
	pivot=high;
	//for(int i=0;i<5;i++) cout<<a[i]<<" ";
	//cout<<endl;
	//int l;cin>>l;
	int i=low-1;
	for(int k=low;k<=high-1;k++) {
		if(a[k]<=a[pivot]) {
			i++;
			//cout<<"Swapping "<<i<<" "<<k<<endl;
			swap(&a[i],&a[k]);			
			//if(i==pivot) pivot=k;
			//if(k==pivot) pivot=i;
		}
	}
	i++;
	swap(&a[i],&a[pivot]);
	// for(int i=0;i<10;i++) cout<<a[i]<<" ";
	// cout<<endl;
	return i;
}

int nth_smallest(int a[],int low,int high,int n) {
	if(low<high) {
		//cout<<low<<" "<<high<<endl;
		int pivot = low + rand()%(high-low);
		int part_index = partition(a,low,high,pivot);
		//cout<<pivot<<" "<<part_index<<endl;
		if(part_index-low==n) return part_index;		
		if(part_index-low>n) {
		//	cout<<" Left"<<endl;
			return nth_smallest(a,low,part_index-1,n);
		}
		//cout<<" Right"<<endl;
		return nth_smallest(a,part_index+1,high,n-part_index+low-1);
	}
}

int main() {
	freopen("infile.txt","r",stdin);
	int t;
	clock_t time;
	cin>>t;
	int flag=0;
	while(t--) {
		int n,k;
		cin>>n>>k;
		int a[n],b[n];
		for(int i=0;i<n;i++) {
			cin>>a[i];
			b[i]=a[i];
		}
		// cin>>k;
		time = clock();
		int index = nth_smallest(a,0,n-1,k-1);
		time = clock()-time;
		double time_taken = ((double)time)/CLOCKS_PER_SEC;
		cout<<"My implementation - "<<time_taken<<endl;

		time = clock();
		nth_element(b,b+k-1,b+n);
		time = clock()-time;
		time_taken = ((double)time)/CLOCKS_PER_SEC;
		cout<<"STL's implementation - "<<time_taken<<endl;
		if(b[k-1]!=a[index]) flag=1;
		cout<<endl;
		// int y;
		// cin>>y;		
	}
	return 0;
}