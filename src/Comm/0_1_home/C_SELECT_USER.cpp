#include "Sharun.hpp"

void* C_SELECT_USER_f(player* player_l, packet* packet_l)
{
	player_Load(player_l, packet_l->read_4());
	const void *args[] = {player_l, NULL, NULL, NULL, NULL};
/*
	Sharun->OpCodes.Send[S_SELECT_USER](args);
	Sharun->OpCodes.Send[S_UPDATE_CONTENTS_ON_OFF](args);
//	Sharun->OpCodes.Send[S_BROCAST_GUILD_FLAG](args);

	Sharun->OpCodes.Send[S_LOGIN](args);

//	Sharun->OpCodes.Send[S_SHOW_NPC_TO_MAP](args);

	Sharun->OpCodes.Send[S_LOAD_TOPO](args);
	Sharun->OpCodes.Send[S_LOAD_HINT](args);

//	Sharun->OpCodes.Send[S_AVAILABLE_SOCIAL_LIST](args);
//	Sharun->OpCodes.Send[S_CLEAR_QUEST_INFO](args);
////	Sharun->OpCodes.Send[S_QUEST_INFO](args);
////	Sharun->OpCodes.Send[S_EVENT_QUEST_SUMMARY](args);
//	Sharun->OpCodes.Send[S_DAILY_QUEST_COMPLETE_COUNT](args);
////	Sharun->OpCodes.Send[S_COMPLETED_MISSION_INFO](args);
//	Sharun->OpCodes.Send[S_ARTISAN_SKILL_LIST](args);
//	Sharun->OpCodes.Send[S_ARTISAN_RECIPE_LIST](args);
//	Sharun->OpCodes.Send[S_NPCGUILD_LIST](args);
//	Sharun->OpCodes.Send[S_PET_INCUBATOR_INFO_CHANGE](args);
//	Sharun->OpCodes.Send[S_PET_INFO_CLEAR](args);
	Sharun->OpCodes.Send[S_VIRTUAL_LATENCY](args);
	Sharun->OpCodes.Send[S_MOVE_DISTANCE_DELTA](args);
//	Sharun->OpCodes.Send[S_MY_DESCRIPTION](args);
//	Sharun->OpCodes.Send[S_F2P_PremiumUser_Permission](args);
////	Sharun->OpCodes.Send[S_TOKEN_POINT_STATUS](args);
//	Sharun->OpCodes.Send[S_AVAILABLE_EVENT_MATCHING_LIST](args);
//	Sharun->OpCodes.Send[S_USER_EXTERNAL_CHANGE](args);
//	Sharun->OpCodes.Send[S_USER_ITEM_EQUIP_CHANGER](args);
//	Sharun->OpCodes.Send[S_FESTIVAL_LIST](args);

//	Sharun->OpCodes.Send[S_ACCOUNT_BENEFIT_LIST](args);
//	Sharun->OpCodes.Send[S_CURRENT_ELECTION_STATE](args);
//	Sharun->OpCodes.Send[S_SEND_USER_PLAY_TIME](args);
//	Sharun->OpCodes.Send[S_PCBANGINVENTORY_DATALIST](args);
//	Sharun->OpCodes.Send[S_FATIGABILITY_POINT](args);
//	Sharun->OpCodes.Send[S_LOAD_EP_INFO](args);

	Sharun->OpCodes.Send[S_INVEN](args);
//	uint ABNORMALITY_ID_1 = 99020000;
//	uint ABNORMALITY_ID_2 = 2147483647;
//	args[3] = &ABNORMALITY_ID_1;
//	args[4] = &ABNORMALITY_ID_2;
//	Sharun->OpCodes.Send[S_ABNORMALITY_BEGIN](args);
//	args[3] = args[4] = NULL;
//	Sharun->OpCodes.Send[S_USER_EXTERNAL_CHANGE](args);
//	args[1] = &ABNORMALITY_ID_1;
//	Sharun->OpCodes.Send[S_ABNORMALITY_END](args);
//	args[1] = NULL;
//	Sharun->OpCodes.Send[S_INVEN](args);

//	Sharun->OpCodes.Send[S_NOTIFY_CHANGE_CLASS_AND_ELITE](args);
//	Sharun->OpCodes.Send[S_MASSTIGE_STATUS](args);
//	Sharun->OpCodes.Send[S_RETURN_USER](args);

	Sharun->OpCodes.Send[S_LOAD_CLIENT_USER_SETTING](args);
	Sharun->OpCodes.Send[S_LOAD_CHAT_SETTING](args);
*/
// OLD VERSION
	Sharun->OpCodes.Send[S_SELECT_USER](args);
	Sharun->OpCodes.Send[S_BROCAST_GUILD_FLAG](args);
	Sharun->OpCodes.Send[S_CURRENT_ELECTION_STATE](args);
	Sharun->OpCodes.Send[S_ONGOING_HUNTING_EVENT_LIST](args);
	Sharun->OpCodes.Send[S_LOGIN](args);

	Sharun->OpCodes.Send[S_SHOW_NPC_TO_MAP](args);

	Sharun->OpCodes.Send[S_INVEN](args);

	Sharun->OpCodes.Send[S_SKILL_LIST](args);
	Sharun->OpCodes.Send[S_AVAILABLE_SOCIAL_LIST](args);

	Sharun->OpCodes.Send[S_CLEAR_QUEST_INFO](args);
////	Sharun->OpCodes.Send[S_QUEST_INFO](args);
////	Sharun->OpCodes.Send[S_EVENT_QUEST_SUMMARY](args);

	Sharun->OpCodes.Send[S_ARTISAN_SKILL_LIST](args);
	Sharun->OpCodes.Send[S_ARTISAN_RECIPE_LIST](args);
	Sharun->OpCodes.Send[S_NPCGUILD_LIST](args);
	Sharun->OpCodes.Send[S_PET_INCUBATOR_INFO_CHANGE](args);
	Sharun->OpCodes.Send[S_PET_INFO_CLEAR](args);
	Sharun->OpCodes.Send[S_VIRTUAL_LATENCY](args);
	Sharun->OpCodes.Send[S_MOVE_DISTANCE_DELTA](args);
	Sharun->OpCodes.Send[S_MY_DESCRIPTION](args);
	Sharun->OpCodes.Send[S_F2P_PremiumUser_Permission](args);
	Sharun->OpCodes.Send[S_NOTIFY_CHANGE_CLASS_AND_ELITE](args);
	Sharun->OpCodes.Send[S_MASSTIGE_STATUS](args);
	Sharun->OpCodes.Send[S_RETURN_USER](args);
	Sharun->OpCodes.Send[S_AVAILABLE_EVENT_MATCHING_LIST](args);
	Sharun->OpCodes.Send[S_FESTIVAL_LIST](args);

	Sharun->OpCodes.Send[S_LOAD_TOPO](args);
	Sharun->OpCodes.Send[S_LOAD_HINT](args);
	Sharun->OpCodes.Send[S_ACCOUNT_BENEFIT_LIST](args);
	Sharun->OpCodes.Send[S_SEND_USER_PLAY_TIME](args);
	Sharun->OpCodes.Send[S_PCBANGINVENTORY_DATALIST](args);

	Sharun->OpCodes.Send[S_FATIGABILITY_POINT](args);
	Sharun->OpCodes.Send[S_LOAD_EP_INFO](args);

	Sharun->OpCodes.Send[S_COMPLETED_MISSION_INFO](args);
	Sharun->OpCodes.Send[S_DAILY_QUEST_COMPLETE_COUNT](args);
	Sharun->OpCodes.Send[S_AVAILABLE_EVENT_MATCHING_LIST](args);

	Sharun->OpCodes.Send[S_USER_BLOCK_LIST](args);
	Sharun->OpCodes.Send[S_FRIEND_GROUP_LIST](args);
	Sharun->OpCodes.Send[S_FRIEND_LIST](args);
	Sharun->OpCodes.Send[S_UPDATE_FRIEND_INFO](args);

	Sharun->OpCodes.Send[S_LOAD_CLIENT_USER_SETTING](args);
	Sharun->OpCodes.Send[S_LOAD_CHAT_SETTING](args);

	return NULL;
}
