//Writed By Inndy <(_ _)>
//---------------------------------------------------------------------------

#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)


#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <queue>
#include <vector>
#include "Pointer.h"
#include "MapList.h"
#include "MapLink.h"
#include "Map.h"
#include <windows.h>
using namespace std;

char linksfile[] = "rglinks.ini";
char linkspath[255] = "";

void InitMapList()
{
	try
	{
		GetTempPathA(255,linkspath);
		strcat(linkspath,linksfile);
		FILE* fp = fopen(linkspath, "wb");
		if( fp != NULL)
		{
			fwrite(mapLinks, sizeof(char), strlen(mapLinks),fp);
			fflush(fp);
			fclose(fp);
		}

	}
	catch (...)
	{
		TerminateProcess(GetCurrentProcess(),0);
	}
}



long GetMapIndex(long id)
{
	long low = 0;
	long high = MapCount - 1;
	while (low <= high)
	{
		long mid = (low + high) / 2;
		if (Maps[mid].id == id)
			return mid;
		else if (Maps[mid].id > id)
			high = mid - 1;
		else if (Maps[mid].id < id)
			low = mid + 1;
	}
	return -1;
}

char* GetMapName(long id)
{
	long index = GetMapIndex(id);
	if (index == -1) {
		return NULL;
	} else {
		return Maps[index].name;
	}
}

long GetMapId(char* name, char * street)
{
	for (int i = 0; i < MapCount; i++) {
		if (strcmp(name, Maps[i].name) == 0 && strcmp(street,Maps[i].st) == 0) {
			return Maps[i].id;
		}
	}
	return -1;
}

long _EnumPossibleMap(long id, MLPROC proc, void *param)
{
	int i = 0;
	while (true)
	{
		char Name[6];
		char IdStr[10];
		sprintf(Name, "Link%d", i++);
		sprintf(IdStr, "%d", id);
		long link = GetPrivateProfileInt(IdStr, Name, -1, linkspath);
		long index = GetMapIndex(link);
		if (link == -1)
			return 1;
		if (MapFlag[index])
			continue;
		MapFlag[index] = 1;
		if( id != link)
		{
			if (proc(Maps[index].name,Maps[index].st, link, param) == 0)
				return 0;
		}
		if (_EnumPossibleMap(link, proc, param) == 0)
			return 0;
	}
}

void EnumPossibleMap(long id, MLPROC proc, void *param)
{
	memset(MapFlag, 0, sizeof(long) * MapCount);
	_EnumPossibleMap(id, proc, param);
}

long* SearchMapPath(long Start, long End)
{
	queue<Node*> unvisited, visited;
	vector<Node*> trash;
	int i;

	Node *n = new Node[1];
	n->father = NULL;
	n->val = Start;
	unvisited.push(n);
	trash.push_back(n);
	memset(MapFlag, 0, sizeof(long) * MapCount);

	while (unvisited.empty() == false)
	{
		Node *current = unvisited.front();
		visited.push(current);
		unvisited.pop();
		if (current->val == End) {
        	n = current;
			break;
		}
		i = 0;
		while (true)
		{
			char Name[6];
			char IdStr[10];
			sprintf(Name, "Link%d", i++);
			sprintf(IdStr, "%d", current->val);
			long link = GetPrivateProfileInt(IdStr, Name, -1, linkspath);
			if (link == -1)
				break;
			if (MapFlag[GetMapIndex(link)])
				continue;
			MapFlag[GetMapIndex(link)] = 1;
			n = new Node[1];
			n->val = link;
			n->father = current;
			unvisited.push(n);
			trash.push_back(n);
		}
	}

	int c = 0;
	Node *tmp = n;
	while (n->father)
	{
		n = n->father;
		c++;
	}
	long *path = new long[c + 2];
	i = c + 1;
	path[c + 1] = 0;
	while (tmp->father)
	{
		path[--i] = tmp->val;
		tmp = tmp->father;
	}
	path[--i] = Start;

	while (trash.empty() == false)
	{
		delete trash.back();
		trash.pop_back();
	}

	return path;
}



bool GetTeleportPoint(long sMap , long eMap, POINT &Point)
{

	try {
        char IdStr[2][10];
		char Tmp[20];
		sprintf(IdStr[0], "%d", sMap);
		sprintf(IdStr[1], "%d", eMap);
		GetPrivateProfileString(IdStr[0], IdStr[1], "", Tmp, 20, linkspath);
		if (strlen(Tmp) > 0) {
			long pt;
			sscanf(Tmp, "%d", &pt);
			Point.x = *(short*)&pt;
			pt >>= 16;
			Point.y = *(short*)&pt;
			return true;
		} else {
			return false;
        }
	} catch (...) { return false;}
}


