#include "Global.h"


const int StringToInt(char* ch)
{
	string k=ch;
	const char* temp=k.c_str();
	for(int indx=0;indx<k.length();indx++)
	{
		if(temp[indx]>'9' || temp[indx]<'0')
			return 0;
	}
	return atoi(k.c_str());
}
//============================================================
const int StringToInt(string k)
{
	const char* temp=k.c_str();
	for(int indx=0;indx<k.length();indx++)
	{
		if(temp[indx]>'9' || temp[indx]<'0')
			return 0;
	}
	return atoi(k.c_str());
}
//=============================================================
void sendAck(Socket_t *Sock)
{
	(*Sock)<<"OK";
}
//=============================================================
void getAck(Socket_t *Sock)
{
	string temp;
	(*Sock)>>temp;
	if(temp!="OK")
	{
		throw "getack";;
	}
}