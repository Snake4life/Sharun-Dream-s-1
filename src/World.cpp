#include <Dream/Dream.hpp>

//packet*command(player_t *, char *);

void World_Friendly_Spawn(player* player_l)
{
	row_npc* t_npc = player_l->DjW->Zone->Friendly;
	while (t_npc) {
		float dist = getDistance_2D(player_l->DjW->toXYZ, t_npc->NPC->World.XYZ);
		const void *args[] = {player_l, t_npc->NPC, &var_NBR[1]};
		if (dist > 100 && player_l->Spawn->in(t_npc->NPC)) {
			Sharun->OpCodes.Send[S_DESPAWN_NPC](args);
			player_l->Spawn->del(t_npc->NPC);
		} else
		if (dist <= 100 && !player_l->Spawn->in(t_npc->NPC)) {
			Sharun->OpCodes.Send[S_SPAWN_NPC](args);
			player_l->Spawn->add(t_npc->NPC);
		}
		t_npc = t_npc->Next;
	}
}

void World_Monsters_Spawn(player* player_l)
{
	row_monster* t_npc = player_l->DjW->Zone->Monsters;
	while (t_npc) {
		float dist = getDistance_2D(player_l->DjW->toXYZ, t_npc->Monster->World.XYZ);
		const void *args[] = {player_l, t_npc->Monster, &var_NBR[0]};
		if (dist > 100 && player_l->Spawn->in(t_npc->Monster)) {
			Sharun->OpCodes.Send[S_DESPAWN_NPC](args);
			player_l->Spawn->del(t_npc->Monster);
		} else
		if (dist <= 100 && !player_l->Spawn->in(t_npc->Monster)) {
			Sharun->OpCodes.Send[S_SPAWN_NPC](args);
			player_l->Spawn->add(t_npc->Monster);
		}
		t_npc = t_npc->Next;
	}
}

void World_Info(player* player_l)
{
	char Query[100];
	sprintf_s(Query, 100, "Server Version :<br>%s: %s", SYSTEM_NAME, SYSTEM_VERSION);
	player_l->Chat(SYSTEM_CHAT, Query, NULL);
	sprintf_s(Query, "Welcome to %s !<br>Type \"--help\" for commands.", Sharun->Settings.Server_Name);
	player_l->Chat(SYSTEM_CHAT, Query, NULL);
}

void World_Spam(player* player_l)
{
	if (!player_l->loged) {
		Stats_Update(player_l);
		player_l->loged = time(NULL);
		player_l->Saved_Time = player_l->loged;
		player_l->Mount = NULL;
		player_l->Spawn->is = 0;
		player_l->moveType[0] = 0;
		player_l->moveType[1] = 0;
		Sharun->Settings.PLAYER_COUNT++;
		DB_Query_Slow("UPDATE `Server_Stats` SET `Player_Count`=`Player_Count`+1 WHERE `Server_ID`='%i';", Sharun->Settings.Server_ID);
		DB_Query_Slow("INSERT INTO `Server_Used_Character` VALUES ('%i', '%i');", Sharun->Settings.Server_ID, player_l->Id);
		World_Info(player_l);
	}

	const void *args[] = {player_l, NULL};
	Sharun->OpCodes.Send[S_SPAWN_ME](args);

	World_Friendly_Spawn(player_l);
	World_Monsters_Spawn(player_l);

	RegenD_ReWait(player_l);

	BroadcastD_Greet(player_l, S_SPAWN_USER, (BROADCAST_TYPE) (BC_TYPE_ARROUND | BC_TYPE_NOT_ME));

	packet* packet_buf = (packet*) Sharun->OpCodes.Send[S_SPAWN_USER](args);
	if (packet_buf) {
		packet_buf->BC_Type = (BROADCAST_TYPE) (BC_TYPE_ARROUND | BC_TYPE_NOT_ME);
		packet_buf->sender = player_l;
		BroadcastD_Add(packet_buf);
	}
}

void World_UnSpam(player* player_l)
{
	const void *args[] = {player_l, NULL};
	packet* packet_buf = (packet*) Sharun->OpCodes.Send[S_DESPAWN_NPC](args);

	player_l->Spawn->is = 0;

	if (packet_buf) {
		packet_buf->BC_Type = (BROADCAST_TYPE) (BC_TYPE_ARROUND | BC_TYPE_NOT_ME | BC_TYPE_FORCE);
		packet_buf->sender = player_l;
		BroadcastD_Add(packet_buf);
	}
	player_l->Spawn->clean();
}

void World_Exit(player* player_l)
{
	player_l->Save();

	player_l->loged = 0;
	player_l->Spawn->is = 0;

	World_UnSpam(player_l);

	Sharun->Settings.PLAYER_COUNT--;
	DB_Query_Fast(0, "UPDATE `Server_Stats` SET `Player_Count`=`Player_Count`-1 WHERE `Server_ID`='%i';", Sharun->Settings.Server_ID);
	DB_Query_Fast(0, "DELETE FROM `Server_Used_Character` WHERE `Character_ID`='%i' AND `Server_ID`='%i';", player_l->Id, Sharun->Settings.Server_ID);
}

void World_PlayerMove(player* player_l, ushort type)
{
	const void *args[] = {player_l, NULL, NULL};
	packet* packet_buf = NULL;

	World_Friendly_Spawn(player_l);
	World_Monsters_Spawn(player_l);

	RegenD_ReWait(player_l);

	BroadcastD_Greet(player_l, S_SPAWN_USER, (BROADCAST_TYPE) (BC_TYPE_ARROUND | BC_TYPE_NOT_ME));

	packet_buf = (packet*) Sharun->OpCodes.Send[S_SPAWN_USER](args);
	if (packet_buf) {
		packet_buf->BC_Type = (BROADCAST_TYPE) (BC_TYPE_ARROUND | BC_TYPE_NOT_ME);
		packet_buf->sender = player_l;
		BroadcastD_Add(packet_buf);
	}

	args[2] = &type;
	packet_buf = (packet*) Sharun->OpCodes.Send[S_NPC_LOCATION](args);
	if (packet_buf) {
		packet_buf->BC_Type = (BROADCAST_TYPE) (BC_TYPE_ARROUND | BC_TYPE_NOT_ME);
		packet_buf->sender = player_l;
		BroadcastD_Add(packet_buf);
	}
}

void World_PlayerSocial(player* player_l, bool ext, int id)
{
	const void *args[] = {&player_l->Id, &player_l->SUBID, &id};
	packet* packet_buf = NULL;

//	if (ext && player_l->Mount)
//		return;

	switch (id) {
		case EMOTE_TYPE_SIT_DOWN:
		case EMOTE_TYPE_SIT_DOWN2:
		case EMOTE_TYPE_DANCE:
		case EMOTE_TYPE_DANCE2:
			RegenD_DontWait(player_l);
			break;
		default:
			RegenD_ReWait(player_l);
	}

	if (id < 0)
		packet_buf = (packet*) Sharun->OpCodes.Send[S_SOCIAL_CANCEL](args);
	else
		packet_buf = (packet*) Sharun->OpCodes.Send[S_SOCIAL](args);

	if (packet_buf) {
		packet_buf->BC_Type = BC_TYPE_ARROUND;
		packet_buf->sender = player_l;
		BroadcastD_Add(packet_buf);
	}
}

void World_PlayerMount(player* player_l, bool mounting, uint Skill_Id)
{
	uint cooldown = 1000;
	const void *args[] = {player_l, &Skill_Id, &cooldown};
	packet* packet_buf = NULL;

	if (mounting && !player_l->Mount)
		player_l->Mount = get_Mount(Skill_Id);

	if (!player_l->Mount)
		return;

	RegenD_ReWait(player_l);

	Skill_Id = player_l->Mount->Skill_Id;

	Sharun->OpCodes.Send[S_START_COOLTIME_SKILL](args);

	if (!mounting) {
		packet_buf = (packet*) Sharun->OpCodes.Send[S_UNMOUNT_VEHICLE](args);
		player_l->Mount = NULL;
	} else
		packet_buf = (packet*) Sharun->OpCodes.Send[S_MOUNT_VEHICLE](args);

	if (packet_buf) {
		packet_buf->BC_Type = BC_TYPE_ARROUND;
		packet_buf->sender = player_l;
		BroadcastD_Add(packet_buf);
		Sharun->OpCodes.Send[S_PLAYER_STAT_UPDATE](args);
	}
}

void World_PlayerSkill(player* player_l, player* target, uint Skill_Id, ushort heading, float* Pos, float* TargetPos)
{
	if (is_Mount(Skill_Id)) {
		if (player_l->Mount)
			World_PlayerMount(player_l, 0, Skill_Id);
		else {
			player_l->Mount = get_Mount(Skill_Id);
			World_PlayerMount(player_l, 1, Skill_Id);
		}
	}

//	RegenD_ReWait(player_l);
}

void World_Chat(player* player_l, CHAT_TYPE type, const char* name, const char *text1, const char16_t *text2)
{
	const void *args[] = {player_l, &type, name, text1, text2};
	packet* packet_buf = NULL;

	char * b1 = NULL;
	char16_t * b2 = NULL;
	if (text1)
		b1 = strstr((char*) text1, ">");
	if (text2)
		b2 = strstr16(text2, u">");
	if ((b1 && b1[1] == '-' && b1[2] == '-') || (b2 && b2[1] == u'-' && b2[2] == u'-')) {
		if (b2)
			b1 = str_str16_8(b2);
//		packet_buf = command(player_l, b);
		if (b2)
			free(b1);
	} else
		packet_buf = (packet*) Sharun->OpCodes.Send[S_CHAT](args);

	if (packet_buf) {
		packet_buf->sender = player_l;
		BroadcastD_Add(packet_buf);
	}
}
