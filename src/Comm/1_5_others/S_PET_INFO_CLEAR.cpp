#include "Sharun.hpp"

void* S_PET_INFO_CLEAR_f(const void** argv)
{
	return packet_send_empty(S_PET_INFO_CLEAR, argv);
}
