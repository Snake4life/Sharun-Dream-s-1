#ifndef _PACKET_HPP_
#define _PACKET_HPP_

#include "data_type.hpp"
#include "OpCode_Gen.hpp"

#define PACKET_MAX_SIZE 0xffff

class packet
{
	protected:
		ushort	pos_switch;
		ushort	size_max;
		virtual void	write_len(ushort);

	public:
		packet(int);
		virtual ~packet();
		OpCode_Enum	Op_ID;	// OpCode ID in Sharun (common version)
		ushort	id;	// OpCode ID in packet (depend client version)
		ushort	size;
		ushort	pos;
		ushort	pos2;
		byte*	raw;
		BROADCAST_TYPE	BC_Type;
		player*	sender;

		virtual void	reset(int);
		virtual int	seek(int, int);
		virtual bool	eof();

		virtual bool	swap();
		virtual bool	swap(ushort);
		virtual char*	clone();
		virtual ushort	full_size();
		virtual void	resize(int);
		virtual void	get_header();
		virtual void	set_header(int);

		virtual ushort	write(const void*, ushort);
		virtual ushort	write_C(const char*);
		virtual ushort	write_S(const char16_t*);
		virtual ushort	write_Pos(ushort);
		virtual ushort	write_NextPos();
		virtual ushort	write_1(uchar);
		virtual ushort	write_2(ushort);
		virtual ushort	write_4(uint);
		virtual ushort	write_8(ulong);
		virtual ushort	write_F(float);

		virtual ushort	read(void*, ushort);
		virtual void*	read_D(ushort); // direct like to data. int 4 < actual pos, 4 >= this pos
		virtual char*	read_C(char*);
		virtual char16_t*	read_S(char16_t*);
		virtual uchar	read_1();
		virtual ushort	read_2();
		virtual uint	read_4();
		virtual ulong	read_8();
		virtual float	read_F();
};

#ifdef _WINDLL
extern packet*	(*new_packet)(OpCode_Enum, int);
extern void*	(*packet_send_empty)(OpCode_Enum, const void**);
#else
extern "C" {
packet*	new_packet(OpCode_Enum, int);
void*	packet_send_empty(OpCode_Enum, const void**);
}
#endif // _WINDLL

#endif // _PACKET_HPP_
