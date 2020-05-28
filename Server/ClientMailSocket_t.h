// Definition of the ClientSocket class


#include "Socket_SMTP.h"

class ClientMailSocket_t : public Socket_SMTP{
public:
	
	ClientMailSocket_t (int port, const char IPAdr[]);
	virtual ~ClientMailSocket_t(){};
	
	const ClientMailSocket_t& operator << ( const std::string& ) const; //recv
	
	const ClientMailSocket_t& operator >> ( std::string& ) const;       //send
	

};
