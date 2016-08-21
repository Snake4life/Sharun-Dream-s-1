#include <Dream/Dream.hpp>

row_mount * Mounts;

void init_Mounts()
{
	Mounts = NULL;
	char **row = NULL;
	const char *sql2 = "SELECT * FROM `mounts` ORDER BY `Skill_Id`";
	void *rslt2 = NULL;

	row_mount * M_tmp = NULL;
	int i=0;
	std::string filename = DB->DB_Set.RAW_Files + DSlash + "mounts.db"; 
	FILE *fp;
	fopen_s(&fp, filename.c_str(), "rb");
	if (!fp) rslt2 = DB_Query_Fast(2, sql2);
	while ((fp && !feof(fp)) || (!fp && (row = DB_Next_Row(rslt2)))) {
		uint	Id = 0;
		if (fp)
			fread(&Id, 1, 4, fp);
		else
			Id = atol(row[0]);
		if (Id) {
			if (!Mounts)
				Mounts = M_tmp = new row_mount;
			else {
				M_tmp->Next = new row_mount;
				M_tmp = M_tmp->Next;
			}
			M_tmp->Mount = new mount;
			M_tmp->Mount->Skill_Id = Id;
			if (fp) {
				fread(&M_tmp->Mount->Mount_Id, 1, 2, fp);
				fread(&M_tmp->Mount->Speed, 1, 2, fp);
				fread(&M_tmp->Mount->R_Stamina, 1, 1, fp);
				fread(&M_tmp->Mount->R_HP, 1, 1, fp);
				fread(&M_tmp->Mount->R_MP, 1, 1, fp);
			} else {
				M_tmp->Mount->Mount_Id =	atoi(row[1]);
				M_tmp->Mount->Speed =		atoi(row[2]);
				M_tmp->Mount->R_Stamina =	atoi(row[2]);
				M_tmp->Mount->R_HP =		atoi(row[3]);
				M_tmp->Mount->R_MP =		atoi(row[4]);
			}
			i++;
		}
	}

	DEBUG("%s (%i) :: %i Mounts loaded%s.\n", __func__, __LINE__, i, fp ? " (from file)": "");
	if (rslt2) DB_Result_Clear(rslt2);
	if (fp) fclose(fp);
}

mount * get_Mount(uint Skill_Id)
{
	row_mount * M_tmp = Mounts;
	while (M_tmp && M_tmp->Mount->Skill_Id != Skill_Id && M_tmp->Mount->Skill_Id <= Skill_Id)
		M_tmp = M_tmp->Next;
	if (M_tmp && M_tmp->Mount->Skill_Id <= Skill_Id)
		return  M_tmp->Mount;
	return NULL;
}

void close_Mounts()
{
	row_mount * M_tmp;
	while (Mounts) {
		M_tmp = Mounts;
		Mounts = Mounts->Next;
		delete M_tmp->Mount;
		delete M_tmp;
	}
}

bool is_Mount(uint Skill_Id)
{
	if (between(Skill_Id, true, 111111, 111302))
		return true;
	if (Skill_Id == 116001)
		return true;
	if (between(Skill_Id, true, 211141, 211150))
		return true;
	if (between(Skill_Id, true, 1111231, 1112004))
		return true;
	if (between(Skill_Id, true, 1701270, 1701295))
		return true;
	if (between(Skill_Id, true, 2222537, 2222711))
		return true;
	if (between(Skill_Id, true, 8400020, 8500011))
		return true;
	if (Skill_Id == 11117100)
		return true;
	if (between(Skill_Id, true, 12000000, 12000013))
		return true;
	if (between(Skill_Id, true, 13000000, 13600069))
		return true;
	if (between(Skill_Id, true, 14000001, 14100210))
		return true;
	if (between(Skill_Id, true, 15300000, 15300001))
		return true;
	if (between(Skill_Id, true, 61900007, 61900010))
		return true;
	return false;
}
