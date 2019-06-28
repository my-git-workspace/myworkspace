#include <iostream>
#include <map>

using namespace std;
class ControlPoint;
class CallBack{
	public:
	      CallBack(){}
	      virtual void atControlPoint()=0;
};
class ControlPoint {
    public:
	ControlPoint (){ }
	void addCallback(string key, CallBack *callback){
		callbacks.insert({key, callback});
	}
	void callBack(string key){
		if(callbacks[key]){
			callbacks[key]->atControlPoint();
		}
	}
    private:
	map <string, CallBack*> callbacks;
};
ControlPoint *cp=new ControlPoint();
#define CONTROL_POINT(c) (cp->callBack(c))
#define ADD_CALLBACK(key, callback) (cp->addCallback(key, callback))
class DemoCallBack:public CallBack{
	public:
		void atControlPoint(){
			cout<<"Control Point Called"<<endl;
		}
};

int main(int argc, char **argv){

	DemoCallBack cb;

	ADD_CALLBACK("DemoCallBack", &cb);

	CONTROL_POINT("DemoCallBack");

	//return from main
	return (0);
}
