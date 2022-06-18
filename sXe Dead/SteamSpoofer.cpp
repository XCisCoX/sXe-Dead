#include "SteamSpoofer.h"
#include "Memory.h"
bool is_digit(char*text)
{
	for (int i = 0; i < strlen(text); i++) {
		if (!isdigit(text[i]))
			return false;
	}
	return true;
}

char* decToHexa(unsigned  int n)
{
	static  char hexaDeciNum[9];
	sprintf_s(hexaDeciNum, "%08x", n);
	hexaDeciNum[0] = toupper(hexaDeciNum[0]);
	hexaDeciNum[1] = toupper(hexaDeciNum[1]);
	hexaDeciNum[2] = toupper(hexaDeciNum[2]);
	hexaDeciNum[3] = toupper(hexaDeciNum[3]);
	hexaDeciNum[4] = toupper(hexaDeciNum[4]);
	hexaDeciNum[5] = toupper(hexaDeciNum[5]);
	hexaDeciNum[6] = toupper(hexaDeciNum[6]);
	hexaDeciNum[7] = toupper(hexaDeciNum[7]);
	return hexaDeciNum;
}
bool setsteam(char h1, char h2, char h3, char h4, char h5, char h6, char h7,
	char h8,HANDLE process,DWORD addr)
{
	bool failed = false;
#define ProtectMemWrites(p,a,b,s) ProtectMemWrite(p,a,b,1)
	if (!(ProtectMemWrites(process, ((addr) + 1) - 1, &h1)))
		failed = true;
	if (!(ProtectMemWrites(process, ((addr) + 2) - 1, &h2)))
		failed = true;
	if (!(ProtectMemWrites(process, ((addr) + 3) - 1, &h3)))
		failed = true;
	if (!(ProtectMemWrites(process, ((addr) + 4) - 1, &h4)))
		failed = true;
	if (!(ProtectMemWrites(process, ((addr) + 5) - 1, &h5)))
		failed = true;
	if (!(ProtectMemWrites(process, ((addr) + 6) - 1, &h6)))
		failed = true;
	if (!(ProtectMemWrites(process, ((addr) + 7) - 1, &h7)))
		failed = true;
	if (!(ProtectMemWrites(process, ((addr) + 8) - 1, &h8)))
		failed = true;
	if (failed)
	{
		return false;
	}
	return true;

}
int SteamChanger(DWORD pId,DWORD BaseAddress, char *newSteam)
{
	HANDLE hProcess = OpenProcess(
		PROCESS_ALL_ACCESS,
		FALSE,
		pId
	);
	if (!hProcess) 
		return CANT_FIND_CS_HANDLE;
	if (strlen(newSteam) == 0)
	{
		return IS_EMPTY_STRING;
	}

	
	else if (!is_digit(newSteam)) {
		return IS_NOT_NUMBER;
	}
	char* xstr;
	xstr = decToHexa(strtoul(newSteam, NULL, 0));
	if (!setsteam(xstr[0], xstr[1], xstr[2]
		, xstr[3], xstr[4], xstr[5], xstr[6],
		xstr[7], hProcess,BaseAddress))
		return CANT_WRITE_PROCESS;
	return SECCUSS_SET_STEAM;
}
HANDLE MapFileToMemory(LPCSTR filename)
{
	std::streampos size;
	std::fstream file(filename, std::ios::in | std::ios::binary
		| std::ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		char* Memblock = new char[size]();
		file.seekg(0, std::ios::beg);
		file.read(Memblock, size);
		file.close();

		return Memblock;
	}
	return 0;
}