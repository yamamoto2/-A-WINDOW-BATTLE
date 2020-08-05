#pragma once


struct TAMA_//弾の構造体
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

	int BombKind = 2;		//爆発の画像の現在の種類
	int BombKindMax = 11;	//爆発の画像の最大数
	int BombCnt = 0;//爆発の挙動のための数値
	int BombCntMax = 3;	//爆発のコマ送りのフレーム数
};

struct PLAYER_//自機の構造体
{
	int HP;
	int Handle;	//画像格納用ハンドル
	int x;
	int y;
	int Width;
	int Height;
};

VOID JOUTAI_HYOUJI_(VOID);//状態表示
VOID DANSUU_(VOID);//弾数
VOID IDOU_SOUSA_(VOID);//移動操作
VOID SHOT_MODE_(VOID);//弾種
VOID SHOT_KYODOU_(VOID);//弾の挙動
VOID PLAYER_HYOUJI_(VOID);
VOID GAZOU_YOMIKOMI_(VOID);
VOID PAD_SOUSA(VOID);

VOID BLUE_BOMB(TAMA_ *);	//青い弾の爆発描画

BOOL ATARI_HANTEI_(RECT, RECT);
BOOL ATARI_HANTEI_2(RECT, RECT);

extern int Laser_dansuu_;
extern int Energy_dansuu_;
extern int Bomb1_dansuu_;//1で止めるためこれで5発 

extern BOOL A_;//弾が０の時射撃キーを押すたびにリロードに対する対策
extern BOOL B_;//弾が０の時射撃キーを押すたびにリロードに対する対策
extern BOOL C_;//弾が０の時射撃キーを押すたびにリロードに対する対策

extern BOOL SHOT_;//パッドのボタン連射対策
extern BOOL HOUKOU_;//パッドのボタン連射対策　右
extern BOOL SHOTMODE_;//パッドのボタン連射対策　右
extern BOOL RELOAD_;//パッドボタン連射対策　右
extern BOOL DANSOKU_;
extern BOOL HOUKOU_1_;//パッドのボタン連射対策　左
extern BOOL SHOTMODE_1_;//パッドのボタン連射対策　左

extern BOOL reload_;//リロード中か否か
extern BOOL DAMAGE_;

extern BOOL ue_[256];//各弾が上端に当たったかどうか
extern BOOL sita_[256];//各弾が下端に当たったかどうか

extern int countC_;//リロードの時間格納用　５秒
extern int i_;//個別の弾用の数字
extern int shothoukou_;//弾の方向
extern int dansoku_ ;//初期弾速
extern int dansokumode_;//弾速の変更
extern int shotmode_;//弾の種類　初期弾種：０
extern int q_;

extern TAMA_ tama_init_;	//弾の画像読み込み・初期化のために使う変数
extern TAMA_ tama_[TAMA_MAX];//構造体の配列

extern PLAYER_ player_;//構造体の変数