#include "Sharun.hpp"

void* S_RETURN_USER_f(const void** argv)
{
	return packet_send_empty(S_RETURN_USER, argv);
}
