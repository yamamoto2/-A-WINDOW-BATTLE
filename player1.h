#pragma once

struct TAMA//弾の構造体
{
	int x;
	int y;
	int houkou;//方向
	int countA;//時間の保存先
	int countB;//爆発エフェクトの数字
	BOOL IsView;//弾の表示非表示
	int dansoku;//弾速
	int shotmode;//弾ごとの弾種データ
	int Angle;

	int handle[(int)TAMA_KIND_END];	//弾の画像のハンドル
	int Width[(int)TAMA_KIND_END];	//弾の幅
	int Height[(int)TAMA_KIND_END];	//弾の高さ

	int BombKind = 101;		//爆発の画像の現在の種類
	int BombKindMax = 110;	//爆発の画像の最大数

	int BombCnt = 0;    //爆発の挙動のための数値
	int BombCntMax = 3;	//爆発のコマ送りのフレーム数
	int PinkCnt = 20;
};

struct PLAYER//自機の構造体
{
	int HP;
	int Handle;	//画像格納用ハンドル
	int x;
	int y;
	int Width;
	int Height;
};

VOID JOUTAI_HYOUJI(VOID);//状態表示
VOID DANSUU(VOID);//弾数
VOID IDOU_SOUSA(VOID);//移動操作
VOID SHOT_MODE(VOID);//弾種
VOID SHOT_KYODOU(VOID);//弾の挙動
VOID PLAYER_HYOUJI(VOID);
VOID GAZOU_YOMIKOMI(VOID);
VOID PAD_SOUSA(VOID);

VOID BLUE_BOMB(TAMA *);	//青い弾の爆発描画

BOOL ATARI_HANTEI(RECT, RECT);
BOOL ATARI_HANTEI2(RECT, RECT);

extern BOOL A;//弾が０の時射撃キーを押すたびにリロードに対する対策
extern BOOL B;//弾が０の時射撃キーを押すたびにリロードに対する対策
extern BOOL C;//弾が０の時射撃キーを押すたびにリロードに対する対策
 
extern BOOL SHOT;//パッドのボタン連射対策
extern BOOL HOUKOU;//パッドのボタン連射対策　右
extern BOOL SHOTMODE;//パッドのボタン連射対策　右
extern BOOL RELOAD;//パッドボタン連射対策　右
extern BOOL DANSOKU;
extern BOOL HOUKOU_1;//パッドのボタン連射対策　左
extern BOOL SHOTMODE_1;//パッドのボタン連射対策　左
 
extern BOOL reload;//リロード中か否か
extern BOOL DAMAGE;

extern BOOL ue[256];//各弾が上端に当たったかどうか
extern BOOL sita[256];//各弾が下端に当たったかどうか

extern int Laser_dansuu;
extern int Energy_dansuu;
extern int Bomb1_dansuu;//1で止めるためこれで5発 

extern int countC;//リロードの時間格納用　５秒
extern int i;//個別の弾用の数字
extern int shothoukou;//弾の方向
extern int dansoku;//初期弾速
extern int dansokumode;//弾速の変更
extern int shotmode;//弾の種類　初期弾種：０
extern int q;

extern TAMA tama_init;	//弾の画像読み込み・初期化のために使う変数
extern TAMA tama[TAMA_MAX];//構造体の配列

extern PLAYER player;	//構造体の変数