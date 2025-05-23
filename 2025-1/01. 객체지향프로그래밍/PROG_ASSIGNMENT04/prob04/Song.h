#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PlayList;

class Song {
private:
	int id;
	string title;
	string artist;
	string album;
	string mv_url;
	vector<PlayList *> playlists;
	static int id_counter; // ��� Song ��ü�鿡�� ������ id�� �ο��ϱ� ���ؼ� static ����� �̿�

public:
	Song();
	Song(string ti, string ar, string al, string mv);
	~Song();

	// Member Method
	int get_id();
	string get_title();
	string get_artist();

	// �뷡�� ������ ȭ�鿡 ����ϴ� Method
	void print(ostream &out);

	// �ش� �뷡�� Playlist�� �߰� & ���� & MV ���
	void register_playlist(PlayList *ptr_plist);
	void unregister_playlist(string plist_name);
	void play();
};