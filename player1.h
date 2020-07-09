#pragma once

//プロトタイプ宣言
VOID START_GAMEN(VOID);//スタート画面
VOID READY_GAMEN(VOID);//準備画面
VOID GAME_GAMEN(VOID);//ゲーム画面
VOID END_GAMEN(VOID);//エンド画面

VOID JOUTAI_HYOUJI(VOID);//状態表示
VOID DANSUU(VOID);//弾数
VOID IDOU_SOUSA(VOID);//移動操作
VOID SHOT_MODE(VOID);//弾種
VOID SHOT_KYODOU(VOID);//弾の挙動
VOID PLAYER_HYOUJI(VOID);
VOID GAZOU_YOMIKOMI(VOID);
VOID PAD_SOUSA(VOID);

BOOL ATARI_HANTEI(RECT, RECT);
BOOL ATARI_HANTEI2(RECT, RECT);


TAMA tama_init;	//弾の画像読み込み・初期化のために使う変数
TAMA tama[TAMA_MAX];//構造体の配列

int Redtama1_dansuu = 15;
int Redtama2_dansuu = 30;
int Bluebomb1_dansuu = 5;//1で止めるためこれで5発 

BOOL A = FALSE;//弾が０の時射撃キーを押すたびにリロードに対する対策
BOOL B = FALSE;//弾が０の時射撃キーを押すたびにリロードに対する対策
BOOL C = FALSE;//弾が０の時射撃キーを押すたびにリロードに対する対策

BOOL SHOT = FALSE;//パッドのボタン連射対策
BOOL HOUKOU = FALSE;//パッドのボタン連射対策　右
BOOL SHOTMODE = FALSE;//パッドのボタン連射対策　右
BOOL RELOAD = FALSE;//パッドボタン連射対策　右
BOOL DANSOKU = FALSE;
BOOL HOUKOU_1 = FALSE;//パッドのボタン連射対策　左
BOOL SHOTMODE_1 = FALSE;//パッドのボタン連射対策　左

BOOL reload = FALSE;//リロード中か否か
BOOL DAMAGE = FALSE;

BOOL ue[256];//各弾が上端に当たったかどうか
BOOL sita[256];//各弾が下端に当たったかどうか

int countC;//リロードの時間格納用　５秒
int i = 0;//個別の弾用の数字
int shothoukou = 0;//弾の方向
int dansoku = 2;//初期弾速
int dansokumode = 0;//弾速の変更
int shotmode = 0;//弾の種類　初期弾種：０
int q = 0;