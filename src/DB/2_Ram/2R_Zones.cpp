#include <Dream/Dream.hpp>

ZONE_t* Zone;

bool in_ZoneList(uint Zone_Id)
{
	ZONE_t *t_Zone = Zone;
	while (t_Zone) {
		if (t_Zone->Id == Zone_Id) 
			return true;
		t_Zone = t_Zone->next;
	}
	return false;
}


void init_Zone()
{
	Zone = NULL;
	char **row = NULL;
	const char *sql2 = "SELECT `Zones` FROM `Zones_HuntingZone` WHERE `Zones` NOT IN ( SELECT `from` FROM `Zones_Channeling`);";
//	char **row, *sql2 = "SELECT `map_id` FROM `npc_locs` WHERE `map_id`>4 GROUP BY `map_id` ORDER BY `map_id`;";
	void *rslt2 = NULL;

	ZONE_t * t_Zone = NULL;

	std::string filename = DB->DB_Set.RAW_Files + DSlash + "zones.db";
	FILE *fp;
	fopen_s(&fp, filename.c_str(), "rb");
	if (!fp)
		rslt2 = DB_Query_Fast(2, sql2);
	uint i_zone=0;
	while ((fp && !feof(fp)) || (!fp && (row = DB_Next_Row(rslt2)))) {
		uint	Id = 0;
		if (fp)
			fread(&Id, 1, 4, fp);
		else
			Id = atoi(row[0]);
		if (Id && !in_ZoneList(Id)) {
			if (!Zone)
				Zone = t_Zone = new ZONE_t;
			else {
				t_Zone->next = new ZONE_t;
				t_Zone = t_Zone->next;
			}
			t_Zone->Id = Id;
			t_Zone->Friendly = NULL;
			t_Zone->Monsters = NULL;
			t_Zone->next = NULL;
			i_zone++;
		}
	}

	DEBUG("%s (%i) :: %i Zones loaded%s.\n", __func__, __LINE__, i_zone, fp ? " (from file)": "");
	if (rslt2) DB_Result_Clear(rslt2);
	if (fp) fclose(fp);
}

void get_Zone(player *player_l, uint Zone_Id)
{
	player_l->World.Zone = NULL;
	ZONE_t *t_Zone = Zone;
	while (t_Zone) {
		if (t_Zone->Id == Zone_Id) {
			player_l->World.Zone = t_Zone;
			return;
		}
		t_Zone = t_Zone->next;
	}
}

void get_ZoneDJ(player *player_l, uint Zone_Id)
{
	player_l->DJ.Zone = NULL;
	ZONE_t *t_Zone = Zone;
	while (t_Zone) {
		if (t_Zone->Id == Zone_Id) {
			player_l->DJ.Zone = t_Zone;
			return;
		}
		t_Zone = t_Zone->next;
	}
}

void close_Zone()
{
	ZONE_t *t_Zone = NULL;
	while (Zone) {
		t_Zone = Zone;
		Zone = Zone->next;
		delete t_Zone;
	}
}
