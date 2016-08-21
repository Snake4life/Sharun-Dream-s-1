#ifndef _BROADCAST_HPP_
#define _BROADCAST_HPP_

enum BROADCAST_TYPE {
	BC_TYPE_MAIN	= 1,
	BC_TYPE_NOT_ME	= 2,
	BC_TYPE_PARTY	= 4,
	BC_TYPE_RAID	= 8,
	BC_TYPE_GUILD	= 16,
	BC_TYPE_ZONE	= 32,
	BC_TYPE_ARROUND	= 64,
	BC_TYPE_TARGET	= 128,
	BC_TYPE_FORCE	= 256
};

#ifdef DLL_VERSION
extern void (*BroadcastD_Add)(packet*);
extern void (*BroadcastD_Greet)(player*, OpCode_Enum, BROADCAST_TYPE);
#else
extern "C" {
void BroadcastD_Add(packet*);
void BroadcastD_Greet(player*, OpCode_Enum, BROADCAST_TYPE);
}
#endif // DLL_VERSION

#endif // _BROADCAST_HPP_
