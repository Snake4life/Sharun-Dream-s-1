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

void init_Monster()
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
	sql2 = "SELECT * FROM `npcs`, `npc_locs` WHERE `class`<>'FRIENDLY' AND `id`=`npc_id` AND `map_id`='%i' AND `huntingZone`=`npc_type` AND `huntingZone` IN (SELECT `HuntingZone` FROM `Zones_HuntingZone` , `Zones_Channeling` WHERE (`Zones` = `from` AND `to` = '%i') OR `Zones` = '%i' GROUP BY `HuntingZone`)";
//	sql2 = "SELECT * FROM `npcs`, `npc_locs` WHERE `class`<>'FRIENDLY' AND `id`=`npc_id` AND `map_id`=13 AND `huntingZone`=`npc_type` AND `huntingZone` IN (SELECT `HuntingZone` FROM `Zones_HuntingZone` , `Zones_Channeling` WHERE (`Zones` = `from` AND `to` = '13') OR `Zones` = '13' GROUP BY `HuntingZone`)";
//	sql2 = "SELECT * FROM `npcs`, `npc_locs` WHERE `class`<>'FRIENDLY' AND `npc_id`=`id` AND `map_id`=13 AND `huntingZone`=`npc_type` AND `huntingZone`=64";

		i2++;
		rslt2 = NULL;
		sprintf_s(filename, 1024, "%s%smob_%i.db", DB->DB_Set.RAW_Files.c_str(), DSlash, t_Zone->Id);
		fopen_s(&fp, filename, "rb");
		if (!fp) rslt2 = DB_Query_Fast(1, sql2, t_Zone->Id, t_Zone->Id, t_Zone->Id);
		else DBFile = true;
		row_monster* Monsters_last = NULL;
		while ((fp && !feof(fp)) || (!fp && (row = DB_Next_Row(rslt2)))) {
			uint	Id = 0;
			if (fp)
				fread(&Id, 1, 4, fp);
			else
				Id = atoi(row[0]);
			if (Id) {
//				printf("Zone %i/%i ; Monsters %i\r", i2, i_zone, i+1);
				/*map_id = atoi(row[18]);
				if (t_Zone && t_Zone->Id != map_id) {
					t_Zone = Zone;
					while (t_Zone->Id != map_id) t_Zone = t_Zone->next;
					Monsters_last->Monster = t_Zone->Monsters;
				}*/
				if (!t_Zone->Monsters)
					t_Zone->Monsters = Monsters_last = new row_monster();
				else {
					Monsters_last->Next = new row_monster();
					Monsters_last = Monsters_last->Next;
				}

				Monsters_last->Monster = new monster;
				Monsters_last->Monster->Id = i;
				Monsters_last->Monster->SUBID = Sharun->Settings.SubID.Monster;
				Monsters_last->Monster->spawned = 1;
				Monsters_last->Monster->skills = NULL;
				Monsters_last->Monster->World.Zone = t_Zone;
				Monsters_last->Monster->npc_id = Id;
				if (fp) {
					fread(&Monsters_last->Monster->npc_id, 1, 4, fp);
					fread(&Monsters_last->Monster->npc_type, 1, 4, fp);
					fread(Monsters_last->Monster->name, 1, 141, fp);
					fread(&Monsters_last->Monster->huntingZone, 1, 4, fp);
					fread(&Monsters_last->Monster->level, 1, 2, fp);
					fread(&Monsters_last->Monster->hpBase, 1, 4, fp);
					fread(&Monsters_last->Monster->attack, 1, 4, fp);
					fread(&Monsters_last->Monster->impact, 1, 4, fp);
					fread(&Monsters_last->Monster->defense, 1, 4, fp);
					fread(&Monsters_last->Monster->balance, 1, 4, fp);
					for (short k=0; k<3; k++)
						fread(&Monsters_last->Monster->World.XYZ[k], 1, 4, fp);
					fread(&Monsters_last->Monster->World.heading, 1, 2, fp);
				} else {
					strcpy_s(Monsters_last->Monster->name, 141, row[1]);
					for (short k=0; k<3; k++)
						Monsters_last->Monster->World.XYZ[k]	= atof2(row[16+k]);
					Monsters_last->Monster->World.heading	= atoi(row[19]);
					Monsters_last->Monster->npc_id		= atoi(row[0]);
					Monsters_last->Monster->npc_type		= atoi(row[2]);
					Monsters_last->Monster->huntingZone	= atoi(row[2]);
					Monsters_last->Monster->level		= atoi(row[4]);
					Monsters_last->Monster->hpBase		= atoi(row[9]);
					Monsters_last->Monster->attack		= atoi(row[5]);
					Monsters_last->Monster->impact		= atoi(row[6]);
					Monsters_last->Monster->defense		= atoi(row[7]);
					Monsters_last->Monster->balance		= atoi(row[8]);
				}
				for (short k=0; k<3; k++)
					Monsters_last->Monster->World.toXYZ[k]	= Monsters_last->Monster->World.XYZ[k];
				Monsters_last->Monster->World.toheading	= Monsters_last->Monster->World.heading;
				i++;
			}
		}

		t_Zone = t_Zone->next;
		if (rslt2) DB_Result_Clear(rslt2);
		if (fp) fclose(fp);
	}
	DEBUG("%s (%i) :: %i Monsters loaded%s.\n", __func__, __LINE__, i, DBFile ? " (from file)": "");
}

void close_Monster()
{
	ZONE_t* t_Zone = Zone;
	while (t_Zone) {
		while (t_Zone->Monsters) {
			row_monster* t_dat = t_Zone->Monsters;
			t_Zone->Monsters = t_Zone->Monsters->Next;
			delete t_dat->Monster;
			delete t_dat;
		}
		t_Zone = t_Zone->next;
	}
}
