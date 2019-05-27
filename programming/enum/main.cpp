#include <iostream>
using namespace std;

enum EncryptionVersion {
    ENCRYPTION_VERSION_0 = 0, // Software encryption not enabled.
    ENCRYPTION_VERSION_1 = 1,  // Software encryption enabled.
    ENCRYPTION_VERSION_INVALID = -1
};
static EncryptionVersion ver(){
	return EncryptionVersion(false);
}
int main(){
	cout <<ver()<<endl;
	return 0;
}
