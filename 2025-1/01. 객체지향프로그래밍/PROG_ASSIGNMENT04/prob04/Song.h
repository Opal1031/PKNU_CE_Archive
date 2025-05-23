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
	static int id_counter; // 모든 Song 객체들에게 유일한 id를 부여하기 위해서 static 멤버를 이용

public:
	Song();
	Song(string ti, string ar, string al, string mv);
	~Song();

	// Member Method
	int get_id();
	string get_title();
	string get_artist();

	// 노래의 정보를 화면에 출력하는 Method
	void print(ostream &out);

	// 해당 노래를 Playlist에 추가 & 제거 & MV 재생
	void register_playlist(PlayList *ptr_plist);
	void unregister_playlist(string plist_name);
	void play();
};