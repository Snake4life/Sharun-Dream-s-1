#include <Dream/Dream.hpp>

row_item* Items;

/*
00 id
01 category
02 name
03 level
04 type
05 cooldown
06 rank
07 rareGrade
08 slotLimit
09 maxStack
10 tradable
11 destroyable
12 bankStorable
13 guildStorable
14 buyPrice
15 sellPrice
16 skill_id
17 bind
*/

void init_Items()
{
	Items = NULL;
	char **row = NULL;
	const char *sql2 = "SELECT * FROM `common_items` ORDER BY `type`, `category`;";
	void *rslt2 = NULL;
	
	int i_item = 0;
	std::string filename = DB->DB_Set.RAW_Files + DSlash + "common_items.db";
	FILE *fp;
	fopen_s(&fp, filename.c_str(), "rb");
	if (!fp) rslt2 = DB_Query_Fast(2, sql2);
	row_item * t_Item = NULL;
	while ((fp && !feof(fp)) || (!fp && (row = DB_Next_Row(rslt2)))) {
		uint	Id = 0;
		if (fp)
			fread(&Id, 1, 4, fp);
		else
			Id = atoi(row[ 0]);
		if (Id) {
			if (!Items) {
				Items = t_Item = new row_item;
				i_item++;
			} else {
				t_Item->Next = new row_item;
				t_Item = t_Item->Next;
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
				fseek(fp, 1+2*4, SEEK_CUR);
				fread(&t_Item->Item->bind, 1, 1, fp);
			} else {
				strcpy_s(t_Item->Item->category, 30, row[ 1]);
				t_Item->Item->level	  = atoi(row[ 3]);
				strcpy_s(t_Item->Item->type, 30, row[ 4]);
				t_Item->Item->cooldown  = atoi(row[ 5]);
				t_Item->Item->rank	  = atoi(row[ 6]);
				strcpy_s(t_Item->Item->rareGrade, 10, row[ 7]);
				t_Item->Item->slotLimit = atoi(row[ 8]);
				t_Item->Item->maxStack  = atoi(row[ 9]);

				t_Item->Item->ability   = 0;
				if (atoi(row[10])) t_Item->Item->ability   |= ITEM_CAN_TRADE;
				if (atoi(row[11])) t_Item->Item->ability   |= ITEM_CAN_DESTROY;
				if (atoi(row[12])) t_Item->Item->ability   |= ITEM_CAN_BANK;
				if (atoi(row[13])) t_Item->Item->ability   |= ITEM_CAN_GUILD;

				t_Item->Item->buyPrice  = atoi(row[14]);
				t_Item->Item->sellPrice = atoi(row[15]);
				t_Item->Item->skill_id  = row[16] ? atoi(row[16]) : 0;
				t_Item->Item->bind	  = atoi(row[17]);
			}

			t_Item->Item->c_slots   = 0;
			t_Item->Item->atk	  = 0;
			t_Item->Item->def	  = 0;
			t_Item->Item->bal	  = 0;
			t_Item->Item->ipt	  = 0;
		}
	}
	DEBUG("%s (%i) :: %i Commons Items loaded%s.\n", __func__, __LINE__, i_item, fp ? " (from file)": "");
	if (rslt2) DB_Result_Clear(rslt2);
	if (fp) fclose(fp);
}

item * get_Item(uint Item_Id)
{
	row_item * t_Item = Items;
	while (t_Item && t_Item->Item->id != Item_Id)
		t_Item = t_Item->Next;
	if (t_Item)
		return t_Item->Item;
	return NULL;
}

void close_Items()
{
	row_item * t_Item = NULL;
	while (Items) {
		t_Item = Items;
		Items = Items->Next;
		delete t_Item->Item;
		delete t_Item;
	}
}
