#include "Sharun.hpp"

void* C_LOAD_TOPO_FIN_f(player* player_l, packet* packet_l)
{
//	*player_l->Still_Online = time(NULL);

	const void *args[] = {player_l, NULL, NULL};

	Sharun->OpCodes.Send[S_PLAYER_STAT_UPDATE](args);
	args[1] = u"@888";
	Sharun->OpCodes.Send[S_SYSTEM_MESSAGE](args);	// Play responsibly
	args[1] = NULL;
	Sharun->OpCodes.Send[S_INVEN](args);
	Sharun->OpCodes.Send[S_ONGOING_HUNTING_EVENT_LIST](args);
	Sharun->OpCodes.Send[S_SKILL_LIST](args);

/*
0000000110 - S_VISITED_SECTION_LIST
0000000111 - S_REQUEST_INVITE_GUILD_TAG
0000000112 - S_USER_BLOCK_LIST
0000000113 - S_FRIEND_GROUP_LIST
0000000114 - S_FRIEND_LIST
0000000115 - S_UPDATE_FRIEND_INFO
0000000118 - S_TRADE_BROKER_CALC_NOTIFY
0000000120 - S_PARCEL_READ_RECV_STATUS
0000000121 - S_ONGOING_LEVEL_EVENT_LIST
0000000122 - S_ONGOING_HUNTING_EVENT_LIST
0000000123 - S_EP_SYSTEM_DAILY_EVENT_EXP_ON_OFF
0000000124 - S_ADD_AWAKEN_ENCHANT_DATA
0000000126 - S_SPAWN_ME
0000000127 - S_SPAWN_NPC
0000000142 - S_RESET_CHARM_STATUS*/
	args[1] = u"@636";
	Sharun->OpCodes.Send[S_SYSTEM_MESSAGE](args); // Abondant Stamina
	args[1] = NULL;
/*0000000144 - S_ADD_CHARM_STATUS
0000000145 - S_PLAYER_STAT_UPDATE
0000000146 - S_PLAYER_CHANGE_ALL_PROF
0000000148 - S_CREST_INFO
0000000149 - S_LOAD_ACHIEVEMENT_LIST
0000000150 - S_UPDATE_ACHIEVEMENT_PROGRESS
0000000151 - S_LOAD_SKILL_SCRIPT_LIST
0000000152 - S_ACCOUNT_BENEFIT_LIST
0000000153 - S_ABNORMALITY_BEGIN
0000000154 - S_PLAYER_STAT_UPDATE
0000000157 - S_USER_STATUS
0000000158 - S_SKILL_PERIOD
0000000159 - S_CLEAR_WORLD_QUEST_VILLAGER_INFO
0000000161 - S_WORLD_QUEST_VILLAGER_INFO
*/	Sharun->OpCodes.Send[S_CURRENT_CHANNEL](args);/*
0000000163 - S_BATTLE_FIELD_SEASON_RANKER
0000000165 - S_ITEM_CUSTOM_STRING
0000000166 - S_FATIGABILITY_POINT
0000000167 - S_DUNGEON_UI_HIGHLIGHT
*/	Sharun->OpCodes.Send[S_ANNOUNCE_MESSAGE](args);/*
0000000169 - S_UNICAST_FLOATING_CASTLE_INFO
0000000227 - S_GUARD_PK_POLICY
 */
	World_Spam(player_l);

	Sharun->OpCodes.Send[S_PLAYER_STAT_UPDATE](args);
	return NULL;
}

/*
	@Override
	public void runImpl()
	{
		// получаем менеджера по игрокам
		PlayerManager playerManager = PlayerManager.getInstance();

		// обрабатываем вход в мир
		playerManager.enterInWorld(getOwner()); ==
	
		player.sendPacket(S_Spawn_Me.getInstance(player), true);

		player.spawnMe();

		//player.sendPacket(Test35.getInstance(player), true);
		player.sendPacket(S_Player_Stat_Update.getInstance(player), true);

		player.sendReuseSkills(); // todo
		player.sendReuseItems(); // todo
		player.sendEffects(); // todo

		if(player.isDead())
		{
			player.broadcastPacket(CharDead.getInstance(player, true));
			player.sendPacket(PlayerDeadWindow.getInstance(), true);
		}

		//if(player.isPK())
		//	player.sendPacket(NameColor.getInstance(NameColor.COLOR_ORANGE, player), true);
		//else 
		if(player.isPvPMode())
			player.sendPacket(NameColor.getInstance(NameColor.COLOR_RED, player), true);
	}
}
	
*/
