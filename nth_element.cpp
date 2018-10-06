#include<iostream>
#include<cstdlib>

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
		int pivot = low + rand()%(high-low+1);
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
	int a[10];
	for(int i=0;i<10;i++) {
		a[i]=rand()%100+1;
		cout<<a[i]<<" ";
	}
	cout<<endl;
	for(int i=1;i<=10;i++) {
		// cout<<"For "<<i<<" "<<endl;
		int index = nth_smallest(a,0,9,i-1);
		// cout<<"Answer - "<<index<<" ";
		cout<<i<<"-"<<a[index]<<endl;
	}
	// for(int i=0;i<10;i++) cout<<a[i]<<" ";
	// cout<<endl;	
	return 0;
}