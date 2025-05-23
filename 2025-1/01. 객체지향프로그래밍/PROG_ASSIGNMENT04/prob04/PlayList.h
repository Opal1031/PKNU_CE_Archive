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

	void add_song(Song *song); // �ϳ��� Song�� tracks�� �߰�
	void print(ostream &out); // Playlist ��ü ���

	vector<Song *> find_songs_by_keyword(string keyword); // Ư�� keyword�� match �Ǵ� song ã��
	Song *find_song_by_id(int sid); // ID�� �ش��ϴ� song ã��

	void delete_song_by_id(int songId);
	void clear_songs();
	int size();
};