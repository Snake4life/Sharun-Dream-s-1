#include "Sharun.hpp"

void* C_GET_USER_LIST_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_GET_USER_LIST](args);
	Sharun->OpCodes.Send[S_ACCOUNT_PACKAGE_LIST](args);
	Sharun->OpCodes.Send[S_CONFIRM_INVITE_CODE_BUTTON](args);
	Sharun->OpCodes.Send[S_UPDATE_CONTENTS_ON_OFF](args);

	return NULL;
}
