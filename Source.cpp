#define _CRT_SECURE_NO_WARNINGS

#include "DxLib.h"
#include "Header.h"
#include "player1.h"
#include "player2.h"

//#####################出来たらいいなリスト#################################
//まずは上下のみ動かせる横スペースインベーダー
//障害物、反射する弾、一定時間とどまる弾、弾を消す弾、跳ね返す弾
//各弾打ち切ったらリロード制、毎秒弾補充制、単発毎クールタイム制選べるようになれば
//リロード中移動速度低下被ダメ増加　弾撃つとUSF4みたいに必殺技ゲージがたまる
//体力と弾の威力、ダッシュ、ダッシュ後失速
//弾の種類とは別に同じような特性を持ったシールドや設置物、ビーム的なのも
//現在の弾、種類、クールタイムを分かりやすく表示、にゃんこ大戦争みたいな

//##########現在の状況####################
//弾の挙動終了
//先生に簡略化するべき場所を聞く　　　←今ココ！
//当たり判定とダメージ(とくに爆発弾)&tamaH.tamaWあたりの
//それぞれの弾速や威力の調整
//卵とのＣＤ,弾のアイコン

//残り20コマ(1/17時点)あまり悠長にやっている暇はない
//整頓できるところは整頓する
//関数にできるところは関数に(当たり判定のとか)　
//関数にできるところは関数に(当たり判定のとか)　
//関数にできるところは関数に(当たり判定のとか)　
//関数にできるところは関数に(当たり判定のとか)　
//対戦型にするための複製はどのようにやればいいか
//ALT+SHIFTうまく使え
//コメントアウトで各所、各値の大まかな説明を

//現在装備の表示、装備変更時のアイコン移動はどうしような。←　後回しの方向で。多分やらない
//現在の射撃方向変更時の←表示、弾速のアイコン化？（弾速に関しては未定

//玉案
//一瞬発射地点に留まり遅れて発射する弾
//敵のy軸に到達すると真横に炸裂するT字のような球
//敵のy軸に到達すると炸裂する時機外しのXのような弾
//敵へまっすぐ飛んでいく自機狙い弾
//ある一定のy軸に到達すると炸裂するY字型の弾
//撃った瞬間の敵のy軸に到達するとその場に一定時間留まる弾
//一瞬予測線が出て直後に一瞬で放たれるビーム

//弾はすべて使えるでいいかも？
//コントローラのあるボタン＋左スティックで10個の弾を使い分けるみたいな（MHWやAPEXのショートカットみたいな）

//必殺技案
//必殺技ゲージは仮に200にして
//必殺技ごとに必要ゲージ量が変化
//ためておけば短い時間で複数の必殺技を使える、必殺技の組み合わせなんかも
//反射はハイリスクハイリターンにしたいので一瞬だが必殺技も跳ね返すみたいな
//↑のハイリスクハイリターンは低コストで高コストだがお手軽反射タイプもあり
//一定時間判定が残る太めのビーム、コストと威力と太さを抑えたバージョンもビームの動作アリ
//超高威力、速めの極大コスト技

//弾を増やすにあたって列挙型の順番を変えねばならない名前も一つの弾ごとに一つ的な
//弾の関数化敵なのも
//shotmode当たりとか大きく作り直すべきかも　10個の弾を同時に使う案の方針で

//他で一度取得した画像サイズをもう一度別の変数で同じ画像のサイズを取得するとおかしくなる？

//自分の弾に自分で当たらないようにした
//自分の弾を隠すテクニック,長く隠せばその分リスクも上がる

LOCKON lockon;

int Key[256]; // キーが押されているフレーム数を格納する

int HP;//HPバー画像格納用ハンドル
int yajirusi_2;//自機前方向矢印画像格納用ハンドル
int yajirusi_3;//状態表示方向矢印画像格納用ハンドル

int Laser_sound;
int Energy_sound;
int Bomb_sound;
int reload_sound;

int Pad1;        //ジョイパッドの入力状態格納用変数
int Pad2;        //ジョイパッドの入力状態格納用変数

//変数の宣言
int mode = (int)scene_start;//画面遷移
int count = 0;//毎フレーム

char dansokuhyouji[3] = "低";//画面に低中高速を表示するための 初期弾速：艇

//char modehyouji[5] = "通常";
//char houkouhyouji[3] = "中";//画面に方向を表示するための　初期方向：中

//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ここまで複製▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲########################2

//キーの入力状態を更新する
int gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	//画像の読み込み
	GAZOU_YOMIKOMI();
	GAZOU_YOMIKOMI_();

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア, キーの状態更新)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0)
	{
		count++;
		switch (mode)
		{
		case (int)scene_start:
			START_GAMEN();
			break;
		case (int)scene_ready:
			READY_GAMEN();
			break;
		case (int)scene_game:
			GAME_GAMEN();
			break;
		case (int)scene_end:
			END_GAMEN();
			break;
		}
	}
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}
//##################スタート画面の関数########################
VOID START_GAMEN(VOID)
{
	PAD_SOUSA();
	DrawFormatString(100, 100, GetColor(0, 255, 0), "スタート画面");
	DrawFormatString(250, 250, GetColor(0, 255, 255), "PUSH TO ENTER");

	if (Key[KEY_INPUT_RETURN] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0)//エンターキー
	{
		mode = (int)scene_ready;
	}
}
VOID READY_GAMEN(VOID)
{
	DrawFormatString(100, 100, GetColor(0, 255, 0), "準備画面");
	if (Key[KEY_INPUT_RETURN] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0)//エンターキー
	{
		mode = (int)scene_game;
	}
}
//##################ゲーム画面の関数########################
VOID GAME_GAMEN(VOID)
{
	PAD_SOUSA();
	JOUTAI_HYOUJI();
	DANSUU();
	IDOU_SOUSA();
	SHOT_MODE();
	SHOT_KYODOU();
	PLAYER_HYOUJI();

	JOUTAI_HYOUJI_();
	DANSUU_();
	IDOU_SOUSA_();
	SHOT_MODE_();
	SHOT_KYODOU_();
	PLAYER_HYOUJI_();

	if (Key[KEY_INPUT_RETURN] == 1)//エンターキー
	{
		mode = (int)scene_end;
	}
}
//##################エンド画面の関数########################
VOID END_GAMEN(VOID)
{
	DrawFormatString(100, 100, GetColor(0, 255, 0), "エンド画面");
	if (Key[KEY_INPUT_RETURN] == 1)
	{
		mode = (int)scene_start;
	}
}

VOID PAD_SOUSA(VOID)
{
	Pad1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //入力状態をPadに格納
	for (int i = 0; i < 28; i++)
	{      //ボタン28個分ループ
		if (Pad1 & (1 << i))
		{             //ボタンiの入力フラグが立っていたら
			DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%dのキーが押されています", i);
		}
	}

	Pad2 = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //入力状態をPadに格納
	for (int i = 0; i < 28; i++)
	{      //ボタン28個分ループ
		if (Pad2 & (1 << i))
		{             //ボタンiの入力フラグが立っていたら
			DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%dのキーが押されています", i);
		}
	}
}


