#include <Sharun/Sharun.hpp>

int player::Send(packet* packet_l)
{
	if (packet_l)
		return Send_Packet(this, packet_l);
	return 0;
}

void player::Chat(CHAT_TYPE c_type, const char* text1, const char16_t* text2)
{
	
	const void *args[] = {
	  NULL, 
	  &c_type, 
	  NULL, 
	  text1, 
	  text2};
	packet*	packet_l = (packet*) Sharun->OpCodes.Send[S_CHAT](args);
	if (packet_l)
		this->Send(packet_l);
}
