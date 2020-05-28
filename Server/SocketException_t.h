//-------------------------------------------------------------
//					SocketException_t.h
//-------------------------------------------------------------
//  SocketException Class to Manage All errors reported by an implementation/use of socket.
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _SOCKET_EXP_H_
#define _SOCKET_EXP_H_

#include <string>
using namespace std;
class SocketException_t{

	string MsgString;
public:
	
	
	SocketException_t (string String):MsgString(String){};  //Error into MsgString
	~SocketException_t (){};
	
	string Description() {return MsgString;}              //Report Error 
	
};
#endif