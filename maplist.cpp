
#include "maplist.h"

#include <stdlib.h>

//pro cteni adresaru
#include <sys/types.h>
#include <dirent.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> mapnames;

//funkce na zjisteni poctu map
int maplist_count() {
	return mapnames.size();
}

//funkce pro overeni nazvu mapy a pridani do vectoru
void process_filename(string n) {
	int l=n.length();
	if(l<=4) return;
	if(n.substr(l-4)!=".mtx") return;
	mapnames.push_back(n);
}

//funkce pro zjisteni nazvu mapy s priponou a cestou
string maplist_get_file_name(int mapid) {
	return "maps/"+mapnames[mapid];
}

//funkce pro zjisteni nazvu mapy samotneho
string maplist_get_name(int mapid) {
	return mapnames[mapid].substr(0,mapnames[mapid].length()-4);
}

//funkce pripravujici adresar map
void maplist_init() {
	DIR* dirp;
	struct dirent* dp;
	dirp = opendir("maps/");
	if(!dirp) return;
	while (1) {
		dp=readdir(dirp);
		if (dp) {
			process_filename(dp->d_name);
		}
		else break;
	}
	closedir(dirp);
}
