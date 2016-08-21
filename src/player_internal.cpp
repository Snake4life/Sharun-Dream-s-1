#include <Dream/Dream.hpp>

void regen_hp(player*);
void regen_mp(player*);
void regen_sp(player*);

void	free_player(player *player_l)
{
	delete player_l;
}

player::player(connexion_list* connex_t)
{
	connex = connex_t;
	connex->Player = this;
	Op_GID = -1;
	Client_Version = 0.0;

	Account_Id = 0;
	Id = 0;
	Characters_Count = 0;
	Characters_Max = Sharun->Settings.Charcters_Max_Per_Account;
	SUBID = 1000;
	Class_Id = 0;
	Race_Id = 0;
	Sex = 0;
	Level = 1;
	exp = 0;
	money = 0;

	memset(collect, 0, 3);
	memset(name, 0, sizeof(char16_t)*51);
	memset(title, 0, sizeof(char16_t)*51);

	Spawn = new spawn();

	loged = 0;
	exit_type = 0;
	exit_time = 0;
	Right = 0;
	end_pay = 0;
}

player::~player()
{
	delete Spawn;
	if(connex) {
		connex->Player = NULL;
		delete connex;
		connex = NULL;
	}
}

int Send_Packet(player* player_l, packet* packet_l)
{
	if (!player_l || !packet_l)
		return 0;
	packet_l->set_header(Sharun->OpCodes.list[player_l->Op_GID].Send[packet_l->Op_ID]);
	return player_l->connex->Send(packet_l);
}

int player::Send_Direct(char* raw)
{
	if (!raw)
		return 0;
	ushort Op_ID = OPC_MAX;
	ushort size = 0;
	memcpy(&size, raw, 2);
	memcpy(&Op_ID, raw + 2, 2);
	memcpy(raw + 2, &Sharun->OpCodes.list[Op_GID].Send[Op_ID], 2);
	return connex->Send_Direct(raw, size);
}

void player::start(void* thread_args)
{
	thread_list* my_thread = (thread_list*) thread_args;
	packet* packet_l = NULL;
	const void *args[] = {this, &var_NBR[1], NULL};
	// Send "ready to play"
	Sharun->OpCodes.Send[S_LOADING_SCREEN_CONTROL_INFO](args);
	Sharun->OpCodes.Send[S_REMAIN_PLAY_TIME](args);
	Sharun->OpCodes.Send[S_LOGIN_ARBITER](args);
//Sharun->OpCodes.Send[S_WAITING_LIST](args);
	Sharun->OpCodes.Send[S_LOGIN_ACCOUNT_INFO](args);
	Sharun->OpCodes.Send[S_LOAD_CLIENT_ACCOUNT_SETTING](args);
	// Let's Play !
	while (my_thread->run && connex && connex->sock != INVALID_SOCKET) {
		packet_l = new packet(0);
		connex->Recv(packet_l);
		if (my_thread->run && connex && connex->sock != INVALID_SOCKET && packet_l->size > 3) {
const char * fcn_name = Sharun->OpCodes.Recv_name(this, packet_l);
if ( strcmp(fcn_name, "C_SIMPLE_TIP_REPEAT_CHECK")
  && strcmp(fcn_name, "C_REQUEST_GAMESTAT_PING") )
	hexdump("player::recv", fcn_name, packet_l->raw, packet_l->size);
			Sharun->OpCodes.Recv(this, packet_l);
		}
		delete packet_l;
	}
}

void player::regen(void* thread_args)
{
	thread_list* my_thread = (thread_list*) thread_args;
	const void *args[] = {this, NULL, NULL, NULL, NULL};
	char regen_time = 0;
	while (my_thread->run && connex && connex->sock != INVALID_SOCKET) {
		ulong l_time = millisec();
		if (loged) {
			if (exit_type && exit_time < (ulong) time(NULL)) {
				if (exit_type == 1)
					Sharun->OpCodes.Send[S_EXIT](args);
				else
					Sharun->OpCodes.Send[S_RETURN_TO_LOBBY](args);
				exit_type = 0;
			} else {
				if (Last_Move < (ulong) time(NULL)) {
					int emote = rand() % 3 + EMOTE_TYPE_INSPECT;
					World_PlayerSocial(this, false, emote);
				}
				if (regen_time > 2) {
					regen_hp(this);
					regen_mp(this);
					regen_sp(this);
					regen_time = 0;
				} else regen_time++;
				if (Saved_Time + 60 < (ulong) time(NULL)) {
					Save();
					Saved_Time = time(NULL);
				}
			}
		}
		Sleep((l_time + 100 - millisec()));
	}
}

void player::Load(uint id_l)
{
	if (id_l)
		Id = id_l;

	char **row, **row2, **row3;
	const char *sql = "SELECT * FROM `characters`, `character_appearances`, `character_detail_2` WHERE `character_appearances`.`object_id`=`characters`.`object_id` AND `character_detail_2`.`object_id`=`characters`.`object_id` AND `characters`.`object_id`='%i';";
	void *rslt = DB_Query_Fast(1, sql, Id);
	row = DB_Next_Row(rslt);

	Class_Id = atoi(row[DB_characters_class_id]);
	Race_Id = atoi(row[DB_characters_race_id]);
	Sex = atoi(row[DB_characters_sex]);
	Level = atoi(row[DB_characters_level]);
	exp = atol(row[DB_characters_exp]);

	country = atoi(row[DB_characters_country]);
	lander = atoi(row[DB_characters_lander]);
	aera = atoi(row[DB_characters_aera]);

	get_Zone(this, atoi(row[DB_characters_zone]));
	if (!World.Zone) {
		get_Zone(this, 5);
	}
	World.heading = atoi(row[DB_characters_heading]);
	for (int i=0; i<3; i++) {
		World.XYZ[i] = atof2(row[DB_characters_x+i]);
		World.toXYZ[i] = atof2(row[DB_characters_x+i]);
	}
	DjW = &World;

	DJ.Zone = NULL;
	get_ZoneDJ(this, atoi(row[DB_characters_DJ_zone]));
	if (DJ.Zone) {
		DJ.heading = atoi(row[DB_characters_DJ_heading]);
		for (int i=0; i<3; i++) {
			DJ.XYZ[i] = atof2(row[DB_characters_DJ_x+i]);
			DJ.toXYZ[i] = atof2(row[DB_characters_DJ_x+i]);
		}
		DjW = &DJ;
	}

	if (Characters_Max > Sharun->Settings.Charcters_Max_Per_Account)
		Characters_Max = Sharun->Settings.Charcters_Max_Per_Account;

/**
 * LOAD ITEMS
 **/
	const char *sql2 = "SELECT `character_items`.*, `characters`.`char_name` FROM `character_items`, `characters` WHERE `characters`.`object_id`=`character_items`.`binded` AND `owner_id` = '%i'";
	void *rslt2 = DB_Query_Fast(1, sql2, Id);
	money = 0;
	Items.slot_count = 5;
	for (short index=0; index<39+20*8; index++)
		Items.slot[index].Item = NULL;
	while ((row2 = DB_Next_Row(rslt2))) {
		if (atoi(row2[DB_character_items_index]) >= 0) {
			short index = atoi(row2[DB_character_items_index]);
			Items.slot[index].id = 0;
			Items.slot[index].Item = get_Item(	  atoi(row2[DB_character_items_item_id]));
			if (Items.slot[index].Item) {
				Items.slot[index].id		= atol(row2[DB_character_items_object_id]);
				Items.slot[index].count		= atoi(row2[DB_character_items_item_count]);
				Items.slot[index].enchant[0]	= atoi(row2[DB_character_items_enchant_level]);
				Items.slot[index].enchant[1]	= atoi(row2[DB_character_items_enchant_max]);
				for (int i=0; i<4; i++)
					Items.slot[index].crystal[i] = atoi(row2[DB_character_items_crystal1+i]);
				Items.slot[index].binded		= atoi(row2[DB_character_items_binded]);
				strcpy_s(Items.slot[index].binder, 141,  row2[DB_character_items_binded+1]);
				strcpy8_16(Items.slot[index].binder_S,   row2[DB_character_items_binded+1]);
			} else
				printf("Item not found : \"%s\" on %i\n", row2[DB_character_items_item_id], index);
		} else {
			uint ID = atoi(row2[DB_character_items_item_id]);
			switch (ID) {
				case 20000000:
					money = atol(row2[DB_character_items_item_count]);
					break;
				case 90000000:
					Items.slot_count = atoi(row2[DB_character_items_item_count]);
					break;
			}
		}
	}
	DB_Result_Clear(rslt2);

/**
 * LOAD SKILL 1
 ****
    owner_id
    skill_id
    type
    lv
    **/
	for (int j=0; j<50; j++) {
		skill[j].id = j;
		skill[j].type = 0;
		skill[j].level = 0;
	}
	sql2 = "SELECT * FROM `character_skill` WHERE `owner_id` = '%i'";
	rslt2 = DB_Query_Fast(1, sql2, Id);
	while ((row2 = DB_Next_Row(rslt2)))
	{
		short ji = atoi(row2[DB_character_skill_skill_id]);
		skill[ji].type = atoi(row2[DB_character_skill_type]);
		skill[ji].level = atoi(row2[DB_character_skill_lv]);
	}
	DB_Result_Clear(rslt2);

/**
 * LOAD SKILL 2
 ***
    owner_id
    skill_id
    **/
	skill2 = NULL;
	sql2 = "SELECT * FROM `character_skill2` WHERE `owner_id` = '%i' ORDER BY `skill_id`";
	rslt2 = DB_Query_Fast(1, sql2, Id);
	skill_2_t *skill2_tmp = NULL;
	while ((row2 = DB_Next_Row(rslt2)))
	{
		if (!skill2) {
			skill2 = new skill_2_t;
			skill2_tmp = skill2;
		} else {
			skill2_tmp->next = new skill_2_t;
			skill2_tmp= skill2_tmp->next;
		}
		skill2_tmp->next = NULL;
		skill2_tmp->id = atol(row2[DB_character_skill2_skill_id]);
		skill2_tmp->type = 1; //atoi(row2[DB_character_skill2_type]);
	}
	DB_Result_Clear(rslt2);

	memset(name, 0, 51);
	strncpy_s(name, 51, row[DB_characters_char_name], 50);
	memset(name_S, 0, 40 * sizeof(char16_t));
	strncpy8_16(name_S, name, 40);

	memset(title, 0, 51);
	strncpy_s(title, 51, row[DB_characters_title], 50);
	memset(title_S, 0, 40 * sizeof(char16_t));
	strncpy8_16(title_S, title, 40);

	memset(friend_note, 0, 151);
	strncpy_s(friend_note, 151, row[DB_characters_friend_note], 150);
	memset(friend_note_S, 0, 51 * sizeof(char16_t));
	strncpy8_16(friend_note_S, friend_note, 50);

	memset(guild_note, 0, 106);
	strncpy_s(guild_note, 106, row[DB_characters_guild_note], 105);
	memset(guild_note_S, 0, 36 * sizeof(char16_t));
	strncpy8_16(guild_note_S, guild_note, 35);

	for (int j = DB_character_appearances_face_color; j<DB_character_appearances_MAXI; j++)
		appearance[j - DB_character_appearances_face_color] = atoi(row[DB_characters_MAXI + j]);

	for (int j = DB_character_detail_2_temp1; j < DB_character_detail_2_MAXI; j++)
		appearance[DB_character_appearances_MAXI - DB_character_appearances_face_color - 1 + j] = atoi(row[DB_characters_MAXI + DB_character_appearances_MAXI + j]);

	const char *sql3 = "SELECT * FROM `template` WHERE `Server_ID` IN (0, %i) AND (`Class_ID` = %i OR (`Class_ID` = -1 AND `Race_ID` IN (-1, %i) AND `Sex` IN ( -1, %i))) ORDER BY `Server_ID` DESC";
	void *rslt3 = DB_Query_Fast(1, sql3, Sharun->Settings.Server_ID, Class_Id, Race_Id, Sex);

	Stats.Stamina[1] = atoi(row[DB_characters_heart]);
	Stats.Stamina[0] = Stats.Stamina[1];
	Stats.maxStamina = 120;
	Stats.HP = atoi(row[DB_characters_hp]);
	Stats.MP = atoi(row[DB_characters_mp]);
	for (int i=0; i<3; i++)
		collect[i] = atoi(row[DB_characters_collect_mining+i]);

	SUBID = Sharun->Settings.SubID.PLayer;

	for (int i=0; i<STAT_NAME_MAX; i++)
		for (int j=0; j<2; j++)
			Stats.stat_detail[j][i] = j ? 1 : 0;

	for (int i=0; (row3 = DB_Next_Row(rslt3)); i++) {
		Stats.stat_detail[atoi(row3[DB_template_Mod])][atoi(row3[DB_template_Name])] = atof2(row3[DB_template_Value]);
}

	if (Sharun->Settings.newHP)
		Stats.stat_detail[0][maxHP] *= 1.588;


	for (int i=0; i<STAT_NAME_MAX; i++) {
		Stats.stat_detail[2][i] = Stats.stat_detail[0][i] * Stats.stat_detail[1][i];
	}

	DB_Result_Clear(rslt3);
	DB_Result_Clear(rslt);
}

void player_Load(player* player_l, uint id_l)
{
	player_l->Load(id_l);
}

void player::Save()
{/*
	const char *sql = "UPDATE `characters` SET `x`='%s', `y`='%s', `z`='%s', `heading`='%i', `zone_id`='%i', `hp`='%i', `mp`='%i', `heart`='%i', `last_online`='%ld', `online_time`=`online_time`+'%ld' WHERE `object_id`='%i';";
	char XYZ[3][30];
	for (int i=0; i<3; i++) {
		sprintf(XYZ[i], "%f", World.XYZ[i]);
		SQL_toFloat(XYZ[i]);
	}
	ulong l_time = time(NULL) - loged;
	loged += l_time;
	DB_Query_Slow(sql, XYZ[0], XYZ[1], XYZ[2], World.heading, World.Zone->Id, Stats.HP, Stats.MP, Stats.Stamina[1], time(NULL), l_time, Id);
*/}

void player_Save(player* player_l)
{
	player_l->Save();
}

void Stats_Update(player *player_l)
{
	float stamina_factor = Stamina(player_l);

	player_l->Stats.attack[0] = 4;
	player_l->Stats.defense[0] = 2;
	player_l->Stats.impact[0] = 0;
	player_l->Stats.balance[0] = 0;


	player_l->Stats.maxHP[0] = player_l->Stats.stat_detail[2][maxHP] * HP_MOD[player_l->Class_Id][player_l->Level];

	player_l->Stats.maxMP[0] = player_l->Stats.stat_detail[2][maxMP];

	player_l->Stats.maxHP[1] = player_l->Stats.stat_detail[2][maxHP] * HP_MOD[player_l->Class_Id][player_l->Level] * stamina_factor;
	player_l->Stats.maxMP[1] = player_l->Stats.stat_detail[2][maxMP] * stamina_factor;

	player_l->Stats.atkSpeed[0] = player_l->Stats.stat_detail[2][atkSpd];
	player_l->Stats.runSpeed[0] = player_l->Stats.stat_detail[2][runSpd];
	if (Sharun->Settings.Stamina4Speed) {
		player_l->Stats.atkSpeed[0] *= stamina_factor;
		player_l->Stats.runSpeed[0] *= stamina_factor;
	}

	player_l->Stats.atkSpeed[1] = player_l->Stats.atkSpeed[0];
	player_l->Stats.runSpeed[1] = player_l->Stats.runSpeed[0];

	// ADD WEAPON + CRISTAL MODDER

	player_l->Stats.attack[1] = player_l->Stats.attack[0] = 4;
	player_l->Stats.defense[1] = player_l->Stats.defense[0] = 2;
	player_l->Stats.impact[1] = player_l->Stats.impact[0] = 0;
	player_l->Stats.balance[1] = player_l->Stats.balance[0] = 0;

	for (int i=0; i<STAT_NAME_MAX; i++)
		player_l->Stats.stat_detail[3][i] = player_l->Stats.stat_detail[2][i];

	// ADD BUFF MODDER
}

row_player::row_player()
{
	Player	= NULL;
	Next	= NULL;
	Prev	= NULL;
}
