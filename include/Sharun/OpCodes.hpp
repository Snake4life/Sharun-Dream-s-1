#ifndef _OPCODES_HPP_
#define _OPCODES_HPP_

#include "OpCode_Gen.hpp"

#define Max_OpName_Size 60
#define Max_OpCode_List 10

extern const char *OpCode_Gen[];

typedef struct opcode_unk_t {
	ushort	code;
	void	(*func)(const void**);
	const char*	name;
	opcode_unk_t*	next;
} opcode_unk_t;

typedef struct opcode_t {
	float	version;
	int	detect;
	int	Send[OPC_MAX];
	void*	(*Recv[PACKET_MAX_SIZE])(player*, packet*);
	const char*	OpName[PACKET_MAX_SIZE];
	opcode_unk_t*	Unknow;
} opcode_t;

class opcodes {
	public:
		opcodes();
		~opcodes();
		bool	load();
		ushort	size;
		int	Get_GID(packet*);
		void*	(*Send[OPC_MAX])(const void**);
		char	opNames[0xffff+1][Max_OpName_Size];
		opcode_t	list[Max_OpCode_List];
		void	Set_Recv(const char*, void*(*)(const void**));
		void	Set_Send(OpCode_Enum, void*(*)(const void**));
		void*	Recv(player*, packet*);
		const char*	Recv_name(player*, packet*);
		const char*	Send_name(packet*);
};

#endif // _OPCODES_HPP_
