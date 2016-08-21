#include <Dream/Dream.hpp>
//*******************************************************************************************
//#include <unistd.h>
#include <csignal>
#include <string>
//*******************************************************************************************
network*	Network = NULL;
sharun_t*	Sharun = NULL;
database*	DB = NULL;
ushort		var_NBR[0xffff];

pthread_pause_t main_pause;
//*******************************************************************************************
void Plugin_Init();

#ifdef WIN32
void win32_unNOTIFYICON();
int win32_NOTIFYICON();
#endif
//*******************************************************************************************
void intHandler(int useless)
{
	Sharun->Settings.main_run = false;
	pthread_pause_signal(&main_pause);
}

/*#ifdef _MSC_VER
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);
#else*/
int main(int argc, const char *argv[])
{
//#endif
	for (ushort j=0; j < 0xffff; j++)
		var_NBR[j] = j;

	Network = new network();
	DB = new database;
	Sharun = new sharun_t;
	DB->start();

	pthread_mutex_init(&Sharun->Players.mtx, NULL);
	Sharun->Players.Lists = new player*[Sharun->Settings.Player_Max];
	for (ushort i = 0; i < Sharun->Settings.Player_Max; i++)
		Sharun->Players.Lists[i] = NULL;

	pthread_pause_init(&main_pause, NULL);
	DEBUG("Main sizeof(sharun_t)=%ld.\n", sizeof(sharun_t));

	signal(SIGINT, intHandler);

	if (!Sharun->OpCodes.load()) {
		DEBUG("ERROR: No OpCode was found ! Exiting...\n");
		goto Main_EXITER;
	}

	DB_Query_Fast(0, "UPDATE `Server_Stats` SET `Start_Count`=`Start_Count`+1, `Player_Count`=0 WHERE `Server_ID`='%i';", Sharun->Settings.Server_ID);
	DB_Query_Fast(0, "DELETE FROM `Server_Used_Character` WHERE `Server_ID`='%i';", Sharun->Settings.Server_ID);
	Sharun->Settings.Start_Count = DB_Query_int(NULL, "SELECT `Start_Count` FROM `Server_Stats` WHERE `Server_ID`='%i';", Sharun->Settings.Server_ID);

	Network->start();

	Plugin_Init();

	DEBUG("\n-------------------\n");
	DEBUG("> READY TO WORK ! <\n");
	DEBUG("  ===============\n\n");

#ifdef WIN32
	win32_NOTIFYICON();
#else
//	pthread_pause_wait(&main_pause);
#endif

	while (Sharun->Settings.main_run) {
		char Input_Key[1024];
		memset(Input_Key, 0, 1024);
#ifdef _MSC_VER
		scanf_s(" %[^\n]s\n", Input_Key, 1024);
#else
		scanf(" %[^\n]s\n", Input_Key);
#endif
		for (size_t i=0; i<strlen(Input_Key); i++)
			Input_Key[i] = toupper(Input_Key[i]);
		if ( !strcmp(Input_Key, "BYE")
		  || !strcmp(Input_Key, "QUIT")
		  || !strcmp(Input_Key, "STOP")
		  || !strcmp(Input_Key, "EXIT") )
			break;
	}
	Sharun->Settings.main_run = false;

Main_EXITER:
	Network->stop();
	delete DB;
	delete Network;
	Fixed_thread_Close();
	thread_L_cleanup();
	pthread_mutex_destroy(&Sharun->Players.mtx);
	delete Sharun->Players.Lists;
	delete Sharun;
	pthread_pause_destroy(&main_pause);
#ifdef WIN32
	win32_unNOTIFYICON();
#endif
	DEBUG("%s (%i) :: Bye. ~\n", __func__, __LINE__);
	return 0;
}
