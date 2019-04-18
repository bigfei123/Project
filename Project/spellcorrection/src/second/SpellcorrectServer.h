
#ifndef __MYSP_SPELLCORRECTSERVER_H__
#define __MYSP_SPELLCORRECTSERVER_H__

#include "Server.h"

namespace mysp
{

class SpellcorrectServer
: public Server{

	public:
		SpellcorrectServer();
		void start();

	private:
		void onConnection(const TcpConnectionPtr &);
		void onMessage(const TcpConnectionPtr &);
		void onClose(const TcpConnectionPtr &);

};

}

#endif
