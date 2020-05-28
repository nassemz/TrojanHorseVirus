#ifndef SOCKET_EXCEP_H
#define SOCKET_EXCEP_H
//  SocketException Class to Manage All errors reported by an implementation/use of socket.
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <string>

class SocketException{

	string MsgString;
	
public:
	SocketException (string String):MsgString(String){};  //Error into MsgString
	~SocketException (){};
	
	string Description() {return MsgString;}              //Report Error 
};
#endif