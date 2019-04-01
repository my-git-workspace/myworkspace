#include <iostream>
#include <cstring>
using namespace std;
#define MCR 34
void function(unsigned long len){
	cout<<"len: "<<len<<endl;	
	char a[] = {"Geeks for"}; 
        char b[] = {'G','e','e','k','s',' ','f','o','r'}; 
        cout << "sizeof(a) = " << sizeof(a); 
        cout << "\nstrlen(a) = "<< strlen(a); 
        cout<<  "\nsizeof(b) = " << sizeof(b); 
        cout<<  "\nstrlen(b) = " << std::strlen(b)<<endl; 
};

int main(int argc, char **argv){
	unsigned int cmp_len = 30;
	function( cmp_len - MCR );
	//return 0
	return (0);
}
