#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

class connexion_list;

class network {
	public:
		network();
		virtual ~network();
		connexion_list*	Connnect(const char*, unsigned short);
		char*	WGet(const char*);
		int start();
		void stop();
};

extern network *Network;

#endif // _NETWORK_HPP_
