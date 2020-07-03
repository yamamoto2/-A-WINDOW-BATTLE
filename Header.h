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
	Redtama1,
	Redtama2,
	Bluebomb1,
	Bluebomb2,
	Bluebomb3,
	Bluebomb4,
	Bluebomb5,
	Bluebomb6,
	Bluebomb7,
	Bluebomb8,
	Bluebomb9,
	Bluebomb10,
	Bluebomb11,
	Redtama3,
	TAMA_KIND_END	//弾の種類の最大値
};

enum LOCK_ON//ロックオン画像の
{
	lockon1,
	lockon2,
	lockon3
};
struct TAMA//弾の構造体
{
	int x;
	int y;
	int houkou;//方向
	int countA;//時間の保存先
	int countB = 11;//爆発エフェクトの数字
	BOOL IsView;//弾の表示非表示
	int dansoku;//弾速
	int shotmode;//弾ごとの弾種データ
	int Angle;

	int handle[(int)TAMA_KIND_END];	//弾の画像のハンドル
	int Width[(int)TAMA_KIND_END];	//弾の幅
	int Height[(int)TAMA_KIND_END];	//弾の高さ
};

struct PLAYER//自機の構造体
{
	int HP = 100;
	int Handle;	//画像格納用ハンドル
	int x;
	int y;
	int Width;
	int Height;
};
PLAYER player;//構造体の変数

struct LOCKON//ロックオン画像の
{
	int Handle[3];
	int Width[3];
	int Height[3];
};
LOCKON lockon;

struct TAMA_//弾の構造体
{
	int x;
	int y;
	int houkou;//方向
	int countA;//時間の保存先
	int countB = 11;//爆発エフェクトの数字
	BOOL IsView;//弾の表示非表示
	int dansoku;//弾速
	int shotmode;//弾ごとの弾種データ
	int Angle;

	int handle[(int)TAMA_KIND_END];	//弾の画像のハンドル
	int Width[(int)TAMA_KIND_END];	//弾の幅
	int Height[(int)TAMA_KIND_END];	//弾の高さ
};

struct PLAYER_//自機の構造体
{
	int HP = 100;
	int Handle;	//画像格納用ハンドル
	int x;
	int y;
	int Width;
	int Height;
};
PLAYER_ player_;//構造体の変数





