#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Song; // Forward Declaration

class PlayList {
private:
	string name;
	vector<Song *> tracks;

public:
	PlayList() = default;
	PlayList(string str);
	string get_name();

	void add_song(Song *song); // 하나의 Song을 tracks에 추가
	void print(ostream &out); // Playlist 전체 출력

	vector<Song *> find_songs_by_keyword(string keyword); // 특정 keyword에 match 되는 song 찾기
	Song *find_song_by_id(int sid); // ID에 해당하는 song 찾기

	void delete_song_by_id(int songId);
	void clear_songs();
	int size();
};