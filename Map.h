//---------------------------------------------------------------------------

#ifndef MapH
#define MapH
#include <windows.h>
//---------------------------------------------------------------------------
typedef struct
{
	long id;
	char st[28];
	char name[32];
} Map;

struct Node
{
	Node* father;
	long val;
};
typedef struct {
int Unknow1;
char *PortalName;
int PortalType; // 地圖傳送點 PortalType == 2
int x;
int y;
int Unknow2;
char *TargetName;
int TargetMap; // 此傳點的地圖ID
} PORTAL;
typedef long (*MLPROC)(char*, char* , long, void*);
void InitMapList();
void EnumPossibleMap(long id, MLPROC proc, void *param);
long GetMapIndex(long id);
char* GetMapName(long id);
long GetMapId(char* name, char * street);
long* SearchMapPath(long Start, long End);
bool GetTeleportPoint(long sMap , long eMap, POINT &Point);
#endif
