#include <Dream/Dream.hpp>

void init_HP_Mod();

STUFF class_mat_l[CLASS_MAX] = {
	LEATHER,
	METAL,
	LEATHER,
	METAL,
	CLOTH,
	LEATHER,
	CLOTH,
	CLOTH,
	LEATHER,
	METAL,
	METAL,
	CLOTH,
};

float HP_CLASS_MOD[CLASS_MAX] = {
	1.057F,
	1.057F,
	1.057F,
	1.0575F,
	1.058F,
	1.057F,
	1.0581F,
	1.0581F,
	1.057F,
	1.0575F,
	1.0575F,
	1.057F,
};

ulong Experience_LEVEL[LV_Max+2] = {
	0,
	840,// lv 1
	2686,
	4800,
	8300,
	12000,
	18600,
	25000,
	46000,
	64000,
	83795, //lv 10
	107904,
	137844,
	173664,
	217412,
	270045,
	332904,
	411478,
	509555,
	624045,
	767158, //lv 20
	946049,
	1169663,
	1444708,
	1780263,
	2199707,
	2714012,
	3356893,
	4104477,
	4943952,
	5898783, //lv 30
	7021426,
	8275585,
	9730408,
	11450277,
	13544471,
	16137427,
	19167071,
	22590568,
	26459120,
	30907955, //lv 40
	36335533,
	43011454,
	51356356,
	61787484,
	74722083,
	90114255,
	107815253,
	127819509,
	149819509,
	174770163, //lv 50
	202477270,
	233242615,
	267400774,
	305322656,
	347419424,
	394146836,
	446010054,
	541343794,
	692902622,
	1855567467, //lv 60
	3117029930,
	4495199471,
	6016452207,
	7701537916,
	9616157695, //lv 65
	0
};

settings::~settings()
{
	delete Server_Name;
	delete SERVER_SIGN;
	delete SERVER_COPYRIGHT;
	if (DB->DB_Set.Login)
		delete DB->DB_Set.Login;
	if (DB->DB_Set.Pass)
		delete DB->DB_Set.Pass;
	if (DB->DB_Set.Name)
		delete DB->DB_Set.Name;
	Free_teraCrypt_version();
}

settings::settings()
{
	Add_teraCrypt_version(-1, -1, -1);
	class_mat = class_mat_l;
	init_HP_Mod();
// Server common's defaults
	Player_Max	= 5;
	Server_ID	= 1;
	Charcters_Max_Per_Account	= 15;
	Confirm_Time	= 10;

	Packets_Fill_Size = false;
	Server_Name	= strdump(DEFAULT_SERVER_NAME);
	SERVER_SIGN	= strdump("<!-- Signature from team of this server -->");
	SERVER_COPYRIGHT = strdump("<!-- Copyright from team of this server -->");
	AutoAccount	= false;
	HardwareHistory	= false;
	newHP		= true;
	Stamina4Speed	= false;
	main_run	= true;

	Net.localhost	= false;
	memset(Net.IP, 0, 16);

// Database
	strcpy_s(DB->DB_Set.IP, 8*4+7+1, "127.0.0.1");
	DB->DB_Set.Port 	= 3306;
	DB->DB_Set.Login	= NULL;
	DB->DB_Set.Pass 	= NULL;
	DB->DB_Set.Name 	= NULL;

// Thread
	Thread.DataBase.Fast	= 1;
	Thread.DataBase.Slow	= 0;
	Thread.Broadcast	= 1;
	Thread.Httpd		= 1;

// Ports defaults
	Net.Ports.Game	 = 14752;
	Net.Ports.Httpd	 = 8080;
	Net.Ports.Bridge = 0;//14750;

// Directory defaults path
	Dirs.Saves	= "Sharun_Saves";
	Dirs.Plugins	= Dirs.Saves + DSlash + "Plugins";

// SUBID
	SubID.PLayer	= 1000;
	SubID.NPC	= 2000;
	SubID.Monster	= 3000;
	SubID.Shot	= 4000;
	SubID.Collect	= 5000;
	SubID.Drop	= 6000;

// Load From File...
	FILE *fp;
	fopen_s(&fp, "config.ini", "r");
	while (fp && !feof(fp)) {
		char lib[126] = {0}, val[126] = {0}, *p = NULL;
#ifdef _MSC_VER
		fscanf_s(fp, " %s = %[^\n]s", lib, 126, val, 126);
#else
		fscanf(fp, " %s = %[^\n]s", lib, val);
#endif
		p = strchr(lib, '\r');
		if (p) p[0] = 0;
		p = strchr(val, '\r');
		if (p) p[0] = 0;

		if (!strcmp(lib, "Player_Max"))		Player_Max	= atoi(val);
		if (!strcmp(lib, "Charcters_Max_Per_Account"))	Charcters_Max_Per_Account	= atoi(val);
		if (!strcmp(lib, "Confirm_Time"))	Confirm_Time	= atoi(val);

		if (!strcmp(lib, "Server_ID"))		Server_ID	= atoi(val);
		if (!strcmp(lib, "Server_Name"))	strupdate(&Server_Name, val);

		if (!strcmp(lib, "AutoAccount"))	AutoAccount	= atob(val);
		if (!strcmp(lib, "newHP"))		newHP	= atob(val);
		if (!strcmp(lib, "Stamina4Speed"))	Stamina4Speed	= atob(val);
		if (!strcmp(lib, "HardwareHistory"))	HardwareHistory	= atob(val);
		if (!strcmp(lib, "SERVER_SIGN"))	strupdate(&SERVER_SIGN, val);
		if (!strcmp(lib, "SERVER_COPYRIGHT"))	strupdate(&SERVER_COPYRIGHT, val);
		if (!strcmp(lib, "Packets_Fill_Size"))	Packets_Fill_Size = atob(val);

		if (!strcmp(lib, "DataBase.IP"))	strcpy_s(DB->DB_Set.IP, 8*4+7+1, val);
		if (!strcmp(lib, "DataBase.Port"))	DB->DB_Set.Port	= atoi(val);
		if (!strcmp(lib, "DataBase.Login"))	strupdate(&DB->DB_Set.Login, val);
		if (!strcmp(lib, "DataBase.Pass"))	strupdate(&DB->DB_Set.Pass, val);
		if (!strcmp(lib, "DataBase.Name"))	strupdate(&DB->DB_Set.Name, val);

		if (!strcmp(lib, "Thread.DataBase.Fast")) Thread.DataBase.Fast	= atoi(val);
		if (!strcmp(lib, "Thread.DataBase.Slow")) Thread.DataBase.Slow	= atoi(val);
		if (!strcmp(lib, "Thread.Broadcast"))	Thread.Broadcast	= atoi(val);
		if (!strcmp(lib, "Thread.Httpd"))	Thread.Httpd	= atoi(val);

		if (!strcmp(lib, "Net.localhost"))	Net.localhost	= atob(val);
		if (!strcmp(lib, "Net.IP"))	strcpy_s(Net.IP, 16, val);
		if (!strcmp(lib, "Net.Ports.Game"))	Net.Ports.Game	= atoi(val);
		if (!strcmp(lib, "Net.Ports.Httpd"))	Net.Ports.Httpd	= atoi(val);
		if (!strcmp(lib, "Net.Ports.Bridge"))	Net.Ports.Bridge	= atoi(val);

		if (!strcmp(lib, "Dirs.Saves"))		Dirs.Saves = val;
		if (!strcmp(lib, "Dirs.Plugins"))	Dirs.Plugins = val;

		if (!strcmp(lib, "SubID.PLayer"))	SubID.PLayer = atol(val);
		if (!strcmp(lib, "SubID.NPC"))	SubID.NPC = atol(val);
		if (!strcmp(lib, "SubID.Monster"))	SubID.Monster = atol(val);
		if (!strcmp(lib, "SubID.Shot"))	SubID.Shot = atol(val);
		if (!strcmp(lib, "SubID.Collect"))	SubID.Collect = atol(val);
		if (!strcmp(lib, "SubID.Drop"))	SubID.Drop = atol(val);

		if (!strcmp(lib, "teraCrypt")) {
			char *p_t = NULL, *s_t = val;
			ushort k[3];
			for (short i=0; i<3; i++)
				k[i] = -1;
			for (short i=0; i<3 && s_t  && s_t[0]; i++) {
				p_t = strchr(s_t, ',');
				if (p_t)
					p_t[0] = 0;
				k[i] = atoi(s_t);
				s_t = p_t;
				if (s_t)
					s_t++;
			}
			Add_teraCrypt_version(k[0], k[1], k[2]);
		}

	}
	if (fp)
		fclose(fp);

// Set other directories...
	Dirs.Logs	= Dirs.Saves + DSlash + "Logs";
	Dirs.WWW	= Dirs.Saves + DSlash + "www";
	Dirs.OpCodes	= Dirs.Saves + DSlash + "OpCodes";
	Dirs.Guild_Logo	= Dirs.Saves + DSlash + "Guild_Logo";
	Dirs.Settings.Account	= Dirs.Saves + DSlash + "Settings" + DSlash + "Account";
	Dirs.Settings.Chat	= Dirs.Saves + DSlash + "Settings" + DSlash + "Chat";
	Dirs.Settings.User	= Dirs.Saves + DSlash + "Settings" + DSlash + "User";

	DB->DB_Set.SQLite 	= Dirs.Saves + DSlash + "Tera.db3";
	DB->DB_Set.RAW_Files 	= Dirs.Saves + DSlash + "DB";

// DON'T TOUCH !
	PLAYER_COUNT = 0;
	Start_Count = 0;

	time_t rawtime;
	time ( &rawtime );
#ifdef _MSC_VER
	struct tm t_info;
	localtime_s(&t_info, &rawtime);
	sprintf_s(Start_Time, 20, "%04i-%02i-%02i %02i:%02i:%02i", t_info.tm_year+1900, t_info.tm_mon+1, t_info.tm_mday, t_info.tm_hour, t_info.tm_min, t_info.tm_sec);
#else
	struct tm* t_info;
	t_info = localtime(&rawtime);
	sprintf_s(Start_Time, 20, "%04i-%02i-%02i %02i:%02i:%02i", t_info->tm_year+1900, t_info->tm_mon+1, t_info->tm_mday, t_info->tm_hour, t_info->tm_min, t_info->tm_sec);
#endif
	srand((uint) rawtime);

	if (Player_Max < 1)
		Player_Max = 1;
	if (Thread.Broadcast < 1)
		Thread.Broadcast = 1;
	if (Thread.DataBase.Fast < 1)
		Thread.DataBase.Fast = 1;

	DEBUG("%s (%i) :: Configure loaded. ~\n", __FILE__, __LINE__);
}

ulong get_Experience_LEVEL(ushort LV)
{
	return Experience_LEVEL[LV];
}
