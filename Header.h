#pragma once

#define PI			3.141592654
#define TAMA_MAX	256

//ゲーム画面
enum GAME_SCENE {
	scene_start,	//スタート画面 0
	scene_ready,	//装備選択画面 1
	scene_game,		//ゲーム画面 2
	scene_end		//エンド画面 3
};

//弾の種類を判別
enum TAMA_KIND {//列挙型、上から順に0.1.2.3.4...と数字を与えられる　途中から別の数字を代入することも可能
	Laser,
	Energy,
	Bomb1,
	Bomb2,
	Bomb3,
	Bomb4,
	Bomb5,
	Bomb6,
	Bomb7,
	Bomb8,
	Bomb9,
	Bomb10,
	Bomb11,
	Delay,
	Ycha,
	Xcha,
	XchaLu,
	XchaLd,
	XchaRu,
	XchaRd,
	Tcha,
	Snipe,
	Stay,
	Test,
	TAMA_KIND_END	//弾の種類の最大値
};
enum LOCK_ON//ロックオン画像の
{
	lockon1,
	lockon2,
	lockon3
};

struct LOCKON//ロックオン画像の
{
	int Handle[3];
	int Width[3];
	int Height[3];
};


extern int Key[256]; // キーが押されているフレーム数を格納する

extern int HP;//HPバー画像格納用ハンドル
extern int yajirusi_2;//自機前方向矢印画像格納用ハンドル
extern int yajirusi_3;//状態表示方向矢印画像格納用ハンドル

extern int Laser_sound;
extern int Energy_sound;
extern int Bomb_sound;
extern int reload_sound;

extern int Pad1;        //ジョイパッドの入力状態格納用変数
extern int Pad2;        //ジョイパッドの入力状態格納用変数

//変数の宣言
extern int mode;//画面遷移
extern int count;//毎フレーム

extern char dansokuhyouji[3];//画面に低中高速を表示するための 初期弾速：艇

extern LOCKON lockon;

//プロトタイプ宣言
VOID START_GAMEN(VOID);//スタート画面
VOID READY_GAMEN(VOID);//準備画面
VOID GAME_GAMEN(VOID);//ゲーム画面
VOID END_GAMEN(VOID);//エンド画面
