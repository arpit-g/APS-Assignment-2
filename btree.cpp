#include<iostream>

using namespace std;
#define debug(x) cout<<"Checkpoint "<<x<<endl

class bTreeNode {

public:
	bool is_leaf;
	int t;
	int size;
	bTreeNode** childs;
	int* keys;

	bTreeNode(int t,bool is_leaf) {
		this->t = t;
		this->is_leaf = is_leaf;
		keys = new int[2*t-1];
		childs = new bTreeNode*[2*t];
	}

	void atCurNode(int val) {
		int i = size-1;
		// cout<<i<<" ";
		while(i>=0 && keys[i]>val) {
			// debug(7);
			// if() {
				keys[i+1]=keys[i];
				i--;
			}
		// }
		keys[i+1]=val;
		size++;
		// debug(44444);
	}

	void insert(int val) {
		if(is_leaf) atCurNode(val);
		else {
			int i = size-1;
			while(i>=0 && keys[i]>val) {
				// debug(40);
				i--;
			}
			// debug(20);
			if(childs[i+1]->size==2*t-1) {
				// debug(10);
				split(childs[i+1],i+1);
				// debug(21);
				if(keys[i+1]<val) i++;				
			}

			childs[i+1]->insert(val);
			// debug(29);
		}
	}

	void split(bTreeNode* child,int index) {
		int median_index;
		(child->size%2==0) ? median_index = (child->size/2)-1 : median_index = (child->size/2);
		// debug(index);
		for(int i=index+1;i<size+1;i++) keys[i]=keys[i-1];
		for(int i=index+2;i<=size+1;i++) childs[i]=childs[i-1];
		// size++;
		keys[index] = child->keys[median_index];
		// debug(median_index);

		bTreeNode* newNode = new bTreeNode(t,child->is_leaf);

		newNode->size = child->size - median_index - 1;
		for(int i=0;i<newNode->size;i++) {
			// debug(i);
			newNode->keys[i] = child->keys[i+median_index+1];
			// newNode->childs[i] = child->childs[i+median_index+1];
		}

		for(int i=0;i<=newNode->size;i++) {
			// newNode->keys[i] = child->keys[i+median_index+1];
			newNode->childs[i] = child->childs[i+median_index+1];
		}		

		// for(int i=size;i>=index+1;i--) childs[i+1] = childs[i]; 

		child->size = median_index;
		childs[index+1] = newNode;
		size++;
	}

	int find(int val) {		
		// debug(0);
		// cout<<"Outside "<<keys[0]<<endl;
		
		int i=0;
		while(i<=size-1 && keys[i]<val) {			
			// cout<<keys[i]<<endl;
			if(keys[i]==val) return 1;
			i++;
			// if(keys[i]<val) i++;
		}
		if(keys[i]==val) return 1;
		if(!is_leaf) return childs[i]->find(val);
		else return 0;
	}

	void remove(int val) {
		int i=0;
		while(i<size && keys[i]<val) {
			i++;
		}
		// debug(i);
		if(keys[i]==val && i<size) {
			if(is_leaf) {
				// debug(34);
				for(int j=i+1;j<size;j++) keys[j-1]=keys[j];
				size--;
			}
			else {
				if(childs[i]->size>=t) {
					bTreeNode* pred = childs[i];
					while(!pred->is_leaf) {
						pred = pred->childs[pred->size];
					}
					keys[i]=pred->keys[pred->size-1];
					childs[i]->remove(pred->keys[pred->size-1]);
				}
				else if(childs[i+1]->size>=t) {
					bTreeNode* succ = childs[i+1];
					while(!succ->is_leaf) {
						succ = succ->childs[succ->size];
					}
					keys[i]=succ->keys[succ->size-1];
					childs[i+1]->remove(succ->keys[succ->size-1]);	
				}
				else {
					bTreeNode* left = childs[i];
					bTreeNode* right = childs[i+1];

					left->size += right->size + 1;

					for(int j=0;j<right->size;j++) {
						left->keys[j+left->t] = right->keys[j];
					}

					if(!left->is_leaf) {
						for(int j=0;j<=right->size;j++) {
							left->childs[j+left->t] = right->childs[j];
						}
					}

					delete(right);

					for(int j=i+1;j<size;j++) {
						keys[j-1] = keys[j];
					}

					for(int j=i+2;j<=size;j++) {
						childs[j-1] = childs[j];
					}
					size--;
				}
			}
		}
		else {
			if(is_leaf) cout<<val<<" is not present in the tree."<<endl;
			else {
				// debug(i);
				bool flag=false;
				if(childs[i]->size<t) {					
					if(i!=0 && childs[i-1]->size>=t) {
						bTreeNode* left = childs[i-1];
						bTreeNode* right = childs[i];

						for(int j=1;j<right->size;j++) {
							right->keys[j]=right->keys[j-1];
						}
						if(!right->is_leaf) {
							for(int j=1;j<=right->size;j++) {
								right->childs[j]=right->childs[j-1];
							}	
						}

						right->keys[0] = keys[i-1];
						if(!right->is_leaf) right->childs[0] = left->childs[left->size];

						keys[i-1] = left->keys[left->size-1];
						left->size--;
						right->size++;
					}
					else if(i!=size && childs[i+1]->size>=t) {
						debug(0);
						bTreeNode* left = childs[i];
						bTreeNode* right = childs[i+1];

						// for(int i=0;i<left->size;i++) {
						// 	right->keys[i+1]=right->keys[i];
						// }
						// if(!right->is_leaf) {
						// 	for(int i=0;i<=right->size;i++) {
						// 		right->childs[i+1]=right->childs[i];
						// 	}	
						// }

						left->keys[left->size] = keys[i];
						if(!left->is_leaf) left->childs[left->size+1] = right->childs[0];

						keys[i] = right->keys[0];

						for(int j=1;j<right->size;j++) {
							right->keys[j-1]=right->keys[j];
						}
						if(!right->is_leaf) {
							for(int j=1;j<=right->size;j++) {
								right->childs[j-1]=right->childs[j];
							}	
						}

						left->size++;
						right->size--;
					}
					else {
						// debug(0);
						if(i==size) {
							flag=true;
							bTreeNode* left = childs[i-1];
							bTreeNode* right = childs[i];

							left->size += right->size + 1;

							for(int j=0;j<right->size;j++) {
								left->keys[j+left->t] = right->keys[j];
							}

							if(!left->is_leaf) {
								for(int j=0;j<=right->size;j++) {
									left->childs[j+left->t] = right->childs[j];
								}
							}

							delete(right);

							for(int j=i+1;j<size;j++) {
								keys[j-1] = keys[j];
							}

							for(int j=i+2;j<=size;j++) {
								childs[j-1] = childs[j];
							}
							size--;
						}
						else {
							// debug(1);
							// cout<<i<<endl;
							bTreeNode* left = childs[i];
							bTreeNode* right = childs[i+1];

							left->size += right->size + 1;

							for(int j=0;j<right->size;j++) {
								left->keys[j+left->t] = right->keys[j];
							}

							if(!left->is_leaf) {
								for(int j=0;j<=right->size;j++) {
									left->childs[j+left->t] = right->childs[j];
								}
							}

							delete(right);

							for(int j=i+1;j<size;j++) {
								keys[j-1] = keys[j];
							}

							for(int j=i+2;j<=size;j++) {
								childs[j-1] = childs[j];
							}
							size--;
						}
					}
				}
				if(flag) childs[i-1]->remove(val);
				else childs[i]->remove(val);
			}
		}
	}

	void display() {
		// debug(0);	
		// cout<<size<<endl;
		for(int i=0;i<size;i++) {
			cout<<keys[i]<<" ";
		}
		cout<<endl;
		// debug(1);
		if(!is_leaf) {
			for(int i=0;i<size+1;i++) {
				// debug(i);
				childs[i]->display();
			}
		}
	}
};

class bTree {

	int node_size;
	bTreeNode* node;		

public:

	bTree(int t) {
		node_size = t;
		node = NULL;
	}

	void insert(int val) {
		// debug(0);
		if(node==NULL) {
			// debug(1);
			node = new bTreeNode(node_size,true);
			node->keys[0] = val;
			node->size = 1;
		}
		else {
			// debug(3);
			if(node->size!=2*node_size-1) {
				// debug(5);
				node->insert(val);
			}
			else {
				// debug(4);
				bTreeNode* parent = new bTreeNode(node_size,false);
				parent->childs[0] = node;
				parent->split(node,0);

				int i = parent->size-1;
				while(i>=0 && parent->keys[i]>val) {
					i--;
				}
				parent->childs[i+1]->insert(val);

				node = parent;
			}
		}

	}

	int search(int val) {
		return node->find(val);
	}

	void remove(int val) {
		node->remove(val);
	}

	void display() {
		node->display();
	}

};

int main() {
	bTree b(3);
	b.insert(10);
	// b.display();
	b.insert(20);
	b.insert(30);
	b.insert(40);
	b.insert(50);
	// debug(2);
	b.insert(60);
	b.insert(70);	
	b.insert(80);
	// debug(2);
	// b.display();
	b.insert(90);	
	b.insert(45);
	b.insert(46);
	b.insert(47);
	// debug("from here");
	b.insert(48);
	// debug("sdfk");
	b.display();
	cout<<endl;
	// if(b.search(60)) cout<<"Found"<<endl;
	// else cout<<"Not Found"<<endl;
	b.remove(70);
	b.remove(80);
	b.display();
	return 0;
}