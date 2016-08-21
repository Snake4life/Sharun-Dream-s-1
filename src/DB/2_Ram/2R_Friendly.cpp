#include <Dream/Dream.hpp>

extern ZONE_t* Zone;

/*
00 id
01 name
02 huntingZone
03 class
04 level
05 attack
06 impact
07 defense
08 balance
09 hpBase
10 size
11 scale
12 skills
13 npc_id
14 npc_type
15 x
16 y
17 z
18 map_id
19 heading
*/

void init_Friendly()
{
	char **row = NULL;
	const char *sql2;
	void *rslt2 = NULL;

	FILE *fp = NULL;
	char filename[1024];

	ZONE_t * t_Zone = NULL;

	int i = 0, i2=0;
	//uint map_id = 0;
	bool DBFile = false;
	t_Zone = Zone;
	while (t_Zone) {
		sql2 = "SELECT * FROM `npcs`, `npc_locs` WHERE `class`='FRIENDLY' AND `id`=`npc_id` AND `map_id`='%i' AND `huntingZone`=`npc_type` AND `huntingZone` IN (SELECT `HuntingZone` FROM `Zones_HuntingZone` , `Zones_Channeling` WHERE (`Zones` = `from` AND `to` = '%i') OR `Zones` = '%i' GROUP BY `HuntingZone`)";
	//	sql2 = "SELECT * FROM `npcs`, `npc_locs` WHERE `class`='FRIENDLY' AND `id`=`npc_id` AND `map_id`=13 AND `huntingZone`=`npc_type` AND `huntingZone` IN (SELECT `HuntingZone` FROM `Zones_HuntingZone` , `Zones_Channeling` WHERE (`Zones` = `from` AND `to` = '13') OR `Zones` = '13' GROUP BY `HuntingZone`)";
	//	sql2 = "SELECT * FROM `npcs`, `npc_locs` WHERE `class`='FRIENDLY' AND `npc_id`=`id` AND `map_id`=13 AND `huntingZone`=`npc_type` AND `huntingZone`=64";

		i2++;
		rslt2 = NULL;
		sprintf_s(filename, 1024, "%s%snpc_%i.db", DB->DB_Set.RAW_Files.c_str(), DSlash, t_Zone->Id);
		fopen_s(&fp, filename, "rb");		
		if (!fp) rslt2 = DB_Query_Fast(1, sql2, t_Zone->Id, t_Zone->Id, t_Zone->Id);
		else DBFile = true;
		row_npc* Friendly_last = NULL;
		while ((fp && !feof(fp)) || (!fp && (row = DB_Next_Row(rslt2)))) {
			uint	Id = 0;
			if (fp)
				fread(&Id, 1, 4, fp);
			else
				Id = atoi(row[0]);
			if (Id) {
//				printf("Zone %i/%i ; NPCs %i\r", i2, i_zone, i+1);
				/*map_id = atoi(row[18]);
				if (t_Zone && t_Zone->Id != map_id) {
					t_Zone = Zone;
					while (t_Zone->Id != map_id) t_Zone = t_Zone->next;
					Friendly_last->NPC = t_Zone->Friendly;
				}*/
				if (!t_Zone->Friendly) {
					t_Zone->Friendly = Friendly_last = new row_npc();
				} else {
					Friendly_last->Next = new row_npc();
					Friendly_last = Friendly_last->Next;
				}

				Friendly_last->NPC = new npc;
				Friendly_last->NPC->Id = i;
				Friendly_last->NPC->SUBID = Sharun->Settings.SubID.NPC;
				Friendly_last->NPC->spawned = 1;
				Friendly_last->NPC->skills = NULL;
				Friendly_last->NPC->World.Zone = t_Zone;
				Friendly_last->NPC->npc_id = Id;
				if (fp) {
					fread(&Friendly_last->NPC->npc_type, 1, 4, fp);
					fread(Friendly_last->NPC->name, 1, 141, fp);
					fread(&Friendly_last->NPC->huntingZone, 1, 4, fp);
					fread(&Friendly_last->NPC->level, 1, 2, fp);
					fread(&Friendly_last->NPC->hpBase, 1, 4, fp);
					fread(&Friendly_last->NPC->attack, 1, 4, fp);
					fread(&Friendly_last->NPC->impact, 1, 4, fp);
					fread(&Friendly_last->NPC->defense, 1, 4, fp);
					fread(&Friendly_last->NPC->balance, 1, 4, fp);
					for (short k=0; k<3; k++)
						fread(&Friendly_last->NPC->World.XYZ[k], 1, 4, fp);
					fread(&Friendly_last->NPC->World.heading, 1, 2, fp);
				} else {
					strcpy_s(Friendly_last->NPC->name, 141, row[1]);
					for (short k=0; k<3; k++)
						Friendly_last->NPC->World.XYZ[k]	= atof2(row[16+k]);
					Friendly_last->NPC->World.heading	= atoi(row[19]);
					Friendly_last->NPC->npc_type		= atoi(row[2]);
					Friendly_last->NPC->huntingZone	= atoi(row[2]);
					Friendly_last->NPC->level		= atoi(row[4]);
					Friendly_last->NPC->hpBase		= atoi(row[9]);
					Friendly_last->NPC->attack		= atoi(row[5]);
					Friendly_last->NPC->impact		= atoi(row[6]);
					Friendly_last->NPC->defense		= atoi(row[7]);
					Friendly_last->NPC->balance		= atoi(row[8]);
				}
				for (short k=0; k<3; k++)
					Friendly_last->NPC->World.toXYZ[k]	= Friendly_last->NPC->World.XYZ[k];
				Friendly_last->NPC->World.toheading	= Friendly_last->NPC->World.heading;
				i++;
			}
		}

		t_Zone = t_Zone->next;
		if (rslt2) DB_Result_Clear(rslt2);
		if (fp) fclose(fp);
	}
	DEBUG("%s (%i) :: %i NPCs loaded%s.\n", __func__, __LINE__, i, DBFile ? " (from file)": "");
}

void close_Friendly()
{
	ZONE_t* t_Zone = Zone;
	while (t_Zone) {
		while (t_Zone->Friendly) {
			row_npc* t_dat = t_Zone->Friendly;
			t_Zone->Friendly = t_Zone->Friendly->Next;
			delete t_dat->NPC;
			delete t_dat;
		}
		t_Zone = t_Zone->next;
	}
}
