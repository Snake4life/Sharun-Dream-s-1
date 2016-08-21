#include <Dream/Dream.hpp>

extern row_item* Items;
row_item* Equipments;

/*
00 id
01 category
02 level
03 type
04 cooldown
05 rank
06 rareGrade
07 slotLimit
08 maxStack
09 crystal_slots
10 atk
11 def
12 balance
13 impact
14 tradable
15 destroyable
16 bankStorable
17 guildStorable
18 buyPrice
19 sellPrice
20 bind
*/


void init_Equipments()
{
	Equipments = Items;
	while (Equipments && Equipments->Next)
		Equipments = Equipments->Next;
	char **row = NULL;
	const char *sql2 = "SELECT * FROM `common_items` ORDER BY `type`, `category`;";
	void *rslt2 = NULL;
	
	int i_item = 0;
	sql2 = "SELECT * FROM `equipment_items` ORDER BY `type`, `category`;";
	rslt2 = NULL;
	i_item = 0;
	std::string filename = DB->DB_Set.RAW_Files + DSlash + "equipment_items.db";
	FILE *fp;
	fopen_s(&fp, filename.c_str(), "rb");
	if (!fp) rslt2 = DB_Query_Fast(2, sql2);
	row_item* t_Item = Equipments;
	while ((fp && !feof(fp)) || (!fp && (row = DB_Next_Row(rslt2)))) {
		uint	Id = 0;
		if (fp)
			fread(&Id, 1, 4, fp);
		else
			Id = atoi(row[ 0]);
		if (Id) {
			if (!Items) {
				Equipments = Items = t_Item = new row_item;
				i_item++;
			} else {
				if (!Equipments)
					Equipments = t_Item = new row_item;
				else {
					t_Item->Next = new row_item;
					t_Item = t_Item->Next;
				}
				i_item++;
			}

			t_Item->Item = new item;
			t_Item->Item->id = Id;
			if (fp) {
				fread(t_Item->Item->category, 1, 30, fp);
				fread(&t_Item->Item->level, 1, 1, fp);
				fread(t_Item->Item->type, 1, 30, fp);
				fread(&t_Item->Item->cooldown, 1, 2, fp);
				fread(&t_Item->Item->rank, 1, 2, fp);
				fread(t_Item->Item->rareGrade, 1, 10, fp);
				fread(&t_Item->Item->slotLimit, 1, 1, fp);
				fread(&t_Item->Item->maxStack, 1, 2, fp);

				fread(&t_Item->Item->ability, 1, 1, fp);

				fread(&t_Item->Item->buyPrice, 1, 4, fp);
				fread(&t_Item->Item->sellPrice, 1, 4, fp);
				fread(&t_Item->Item->skill_id, 1, 4, fp);
				fread(&t_Item->Item->c_slots, 1, 1, fp);
				fread(&t_Item->Item->atk, 1, 2, fp);
				fread(&t_Item->Item->def, 1, 2, fp);
				fread(&t_Item->Item->bal, 1, 2, fp);
				fread(&t_Item->Item->ipt, 1, 2, fp);
				fread(&t_Item->Item->bind, 1, 1, fp);
			} else {
				strcpy_s(t_Item->Item->category, 30, row[ 1]);
				t_Item->Item->level	  = atoi(row[ 2]);
				strcpy_s(t_Item->Item->type, 30, row[ 3]);
				t_Item->Item->cooldown  = atoi(row[ 4]);
				t_Item->Item->rank	  = atoi(row[ 5]);
				strcpy_s(t_Item->Item->rareGrade,10, row[ 6]);
				t_Item->Item->slotLimit = atoi(row[ 7]);
				t_Item->Item->maxStack  = atoi(row[ 8]);

				t_Item->Item->c_slots   = atoi(row[ 9]);
				t_Item->Item->atk	  = atoi(row[10]);
				t_Item->Item->def	  = atoi(row[11]);
				t_Item->Item->bal	  = atoi(row[12]);
				t_Item->Item->ipt	  = atoi(row[13]);

				t_Item->Item->ability   = 0;
				if (atoi(row[14])) t_Item->Item->ability   |= ITEM_CAN_TRADE;
				if (atoi(row[15])) t_Item->Item->ability   |= ITEM_CAN_DESTROY;
				if (atoi(row[16])) t_Item->Item->ability   |= ITEM_CAN_BANK;
				if (atoi(row[17])) t_Item->Item->ability   |= ITEM_CAN_GUILD;

				t_Item->Item->buyPrice  = atoi(row[18]);
				t_Item->Item->sellPrice = atoi(row[19]);
				t_Item->Item->skill_id  = 0;//row[16] ? atoi(row[16]) : 0;
				t_Item->Item->bind	  = atoi(row[20]);
			}
		}
	}
	DEBUG("%s (%i) :: %i Equipments Items loaded%s.\n", __func__, __LINE__, i_item, fp ? " (from file)": "");
	if (rslt2) DB_Result_Clear(rslt2);
	if (fp) fclose(fp);
}

item * get_Equipment(uint Item_Id)
{
	row_item * t_Item = Equipments;
	while (t_Item && t_Item->Item->id != Item_Id)
		t_Item = t_Item->Next;
	if (t_Item)
		return t_Item->Item;
	return NULL;
}

void close_Equipments()
{
	Equipments = NULL;
}
