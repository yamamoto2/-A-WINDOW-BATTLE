#pragma once

VOID JOUTAI_HYOUJI_(VOID);//状態表示
VOID DANSUU_(VOID);//弾数
VOID IDOU_SOUSA_(VOID);//移動操作
VOID SHOT_MODE_(VOID);//弾種
VOID SHOT_KYODOU_(VOID);//弾の挙動
VOID PLAYER_HYOUJI_(VOID);
VOID GAZOU_YOMIKOMI_(VOID);
VOID PAD_SOUSA(VOID);

BOOL ATARI_HANTEI_(RECT, RECT);
BOOL ATARI_HANTEI_2(RECT, RECT);

TAMA_ tama_init_;	//弾の画像読み込み・初期化のために使う変数
TAMA_ tama_[TAMA_MAX];//構造体の配列

int Redtama1_dansuu_ = 15;
int Redtama2_dansuu_ = 30;
int Bluebomb1_dansuu_ = 5;//1で止めるためこれで5発 

BOOL A_ = FALSE;//弾が０の時射撃キーを押すたびにリロードに対する対策
BOOL B_ = FALSE;//弾が０の時射撃キーを押すたびにリロードに対する対策
BOOL C_ = FALSE;//弾が０の時射撃キーを押すたびにリロードに対する対策

BOOL SHOT_ = FALSE;//パッドのボタン連射対策
BOOL HOUKOU_ = FALSE;//パッドのボタン連射対策　右
BOOL SHOTMODE_ = FALSE;//パッドのボタン連射対策　右
BOOL RELOAD_ = FALSE;//パッドボタン連射対策　右
BOOL DANSOKU_ = FALSE;
BOOL HOUKOU_1_ = FALSE;//パッドのボタン連射対策　左
BOOL SHOTMODE_1_ = FALSE;//パッドのボタン連射対策　左

BOOL reload_ = FALSE;//リロード中か否か
BOOL DAMAGE_ = FALSE;

BOOL ue_[256];//各弾が上端に当たったかどうか
BOOL sita_[256];//各弾が下端に当たったかどうか

int countC_;//リロードの時間格納用　５秒
int i_ = 0;//個別の弾用の数字
int shothoukou_ = 0;//弾の方向
int dansoku_ = 2;//初期弾速
int dansokumode_ = 0;//弾速の変更
int shotmode_ = 0;//弾の種類　初期弾種：０
int q_ = 0;
