#include"DKHP.h"
int main()
{
	SV sv;
	//Input(sv);
	sv.fal = "CNTT";
	sv.id = 20120386;
	sv.name = "Le Phuoc Toan";
	string folder = ".\\Register for the course\\";
	string filename = Int_ToString(sv.id) + "_" + sv.name;
	string path = Make_Path(folder, filename);
	if (!File_Exist1(path))
	{
		File_Create(path);
	}
	bool run = true;
	while (run)
	{
		run = DKHP_MenuMainProc(DHKP_MenuMainDis(sv), sv);
	}
	return 0;
}