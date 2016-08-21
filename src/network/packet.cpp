#include <Sharun/Sharun.hpp>

packet::packet(int initial_size)
{
	id = 0;
	size = 4;
	Op_ID = OPC_MAX;
	sender = NULL;
	BC_Type = BC_TYPE_MAIN;
	if (initial_size < 0|| Sharun->Settings.Packets_Fill_Size)
		size_max = PACKET_MAX_SIZE;
	else
		size_max = 4 + (initial_size ? initial_size : 0);
	pos = 4;
	pos_switch = 0;
	raw = (byte*)malloc(sizeof(byte) * size_max);
	memset(raw, 0, size);
}

packet::~packet()
{
	if (raw)
		free(raw);
	raw = NULL;
}

void packet::reset(int initial_size)
{
	id = 0;
	size = 4;
	Op_ID = OPC_MAX;
	sender = NULL;
	BC_Type = BC_TYPE_MAIN;
	if (initial_size < 0|| Sharun->Settings.Packets_Fill_Size)
		size_max = PACKET_MAX_SIZE;
	else
		size_max = 4 + (initial_size ? initial_size : 0);
	pos = 4;
	pos_switch = 0;
	free(raw);
	raw = (byte*)malloc(sizeof(byte) * size_max);
	memset(raw, 0, size);
}

int packet::seek(int offset, int origin)
{
	ushort pos_t = pos;
	switch (origin)
	{
		case SEEK_END:
			pos_t = size + offset;
			break;
		case SEEK_SET:
			pos_t = offset;
			break;
		default:
			pos_t += offset;
	}
	if (pos_t < 4 || pos_t > size)
		return 1;
	pos = pos_t;
	return 0;
}

bool packet::eof()
{
	if (pos >= size)
		return true;
	return false;
}

bool packet::swap()
{
	if (pos_switch < 4)
		return false;
	size -= pos - pos2;
	pos = pos_switch;
	return true;
}

bool packet::swap(ushort pos_n)
{
	if (pos_n > size)
		return false;
	pos_switch = pos;
	pos = pos_n;
	pos2 = pos;
	return true;
}

char* packet::clone()
{
	char* packet_t = new char[size];
	if (packet_t) {
		memcpy(packet_t, raw, size);
		memcpy(packet_t, &size, 2);
		memcpy(packet_t + 2, &Op_ID, 2);
	}
	return packet_t;
}

void packet::resize(int size_f)
{
	byte *raw_n = (byte*)malloc(sizeof(byte) * size_max);
	if (size_f >= 0)
		memcpy(raw_n, raw, size_f ? size_f : size);
	if (raw)
		free(raw);
	raw = raw_n;
}

ushort packet::full_size()
{
	size_max = PACKET_MAX_SIZE;
	resize(0);
	return 0;
}

void packet::get_header()
{
	memcpy(&size, &raw[0], 2);
	memcpy(&id, &raw[2], 2);
	size_max = size;
	resize(size);
}

void packet::set_header(int id_n)
{
	if (id_n > -1)
		id = id_n;
	memcpy(&raw[0], &size, 2);
	memcpy(&raw[2], &id, 2);
}

void packet::write_len(ushort len)
{
	if (size_max < size + len) {
		size_max = size + len;
		byte *raw_n = (byte*)realloc((void*)raw, sizeof(byte) * size_max);
		if (!raw_n)
			resize(0);
		else
			raw = raw_n;
	}
	size += len;
}

ushort packet::write(const void* src, ushort len)
{
	write_len(len);
	memcpy(&raw[pos], src, len);
	pos += len;
	return len;
}

ushort packet::write_C(const char* src)
{
	size_t len = 0;
	len = (str8_strlen16(src) + 1) * 2;
	write_len(len);
	strcpy8_16((char16_t*) &raw[pos], src);
	pos += len;
	return len;
}

ushort packet::write_S(const char16_t* src)
{
	size_t len = 0;
	len = strlen16_bin(src);
	write_len(len);
	memcpy(&raw[pos], src, len);
	pos += len;
	return len;
}

ushort packet::write_Pos(ushort pos_t)
{
	ushort pos_u = 0;
	if (!pos_t) {
		pos_u = pos;
		write_2(pos);
	}
	if (pos_t >= 4) {
		pos_u = pos;
		swap(pos_t);
		write_2(pos_switch);
		swap();
	}
	return pos_u;
}

ushort packet::write_NextPos()
{
	ushort pos_u = 0;
	pos_u = pos;
	write_2(0);
	return pos_u;
}

ushort packet::read(void* dst, ushort len)
{
	if (pos + len > size)
		return 0;
	memcpy(dst, &raw[pos], len);
	pos += len;
	return len;
}

void* packet::read_D(ushort len)
{
	if (len >= 4)
		return &raw[len];
	return &raw[pos];
}

char* packet::read_C(char* dst_t)
{
	ushort len = 0;
	len = str_strlen((char16_t*) &raw[pos]);
	if (!dst_t)
		dst_t = new char[len + 1];
	len = strlen16((char16_t*) &raw[pos]);
	strcpy16_8(dst_t, (char16_t*)&raw[pos]);
	pos += (len + 1) * 2;
	return dst_t;
}

char16_t* packet::read_S(char16_t* dst_t)
{
	ushort len = 0;
	len = strlen16((char16_t*) &raw[pos]);
	if (!dst_t)
		dst_t = new char16_t[len + 1];
	len = (len + 1) * 2;
	memcpy(dst_t, &raw[pos], len);
	pos += len;
	return dst_t;
}

uchar packet::read_1()
{
	uchar dst_t = 0;
	read((void*)&dst_t, sizeof(dst_t));
	return dst_t;
}

ushort packet::read_2()
{
	ushort dst_t = 0;
	read((void*)&dst_t, sizeof(dst_t));
	return dst_t;
}

uint packet::read_4()
{
	uint dst_t = 0;
	read((void*)&dst_t, sizeof(dst_t));
	return dst_t;
}

ulong packet::read_8()
{
	ulong dst_t = 0;
	read((void*)&dst_t, sizeof(dst_t));
	return dst_t;
}

float packet::read_F()
{
	float dst_t = 0;
	read((void*)&dst_t, sizeof(dst_t));
	return dst_t;
}


/**
 * Easy-Life part...
 **/
ushort packet::write_1(uchar src)
{
	return write(&src, sizeof(src));
}

ushort packet::write_2(ushort src)
{
	return write(&src, sizeof(src));
}

ushort packet::write_4(uint src)
{
	return write(&src, sizeof(src));
}

ushort packet::write_8(ulong src)
{
	return write(&src, sizeof(src));
}

ushort packet::write_F(float src)
{
	return write(&src, sizeof(src));
}
