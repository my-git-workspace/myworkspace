#include <iostream>
using namespace std;

int main(int argc, char **argv){
	int *in= new int;
	cout<<"in: "<<in<<endl;
	delete in;
	cout<<"delete in: "<<in<<endl;
	//return
	return 0;
	
}
