#define  _CRT_SECURE_NO_WARNINGS

#include "DxLib.h"
#include <stdio.h>
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
//対戦型にするための複製はどのようにやればいいか
//ALT+SHIFTうまく使え
//コメントアウトで各所、各値の大まかな説明を

//現在装備の表示、装備変更時のアイコン移動はどうしような。←　後回しの方向で。多分やらない
//現在の射撃方向変更時の←表示、弾速のアイコン化？（弾速に関しては未定

//スタート画面でのゲームモード選択
//シングルモード追加
//スコアアタック


int Key[256]; // キーが押されているフレーム数を格納する

int HP;//HPバー画像格納用ハンドル
int yajirusi_2;//自機前方向矢印画像格納用ハンドル
int yajirusi_3;//状態表示方向矢印画像格納用ハンドル

int Redtama1_sound;
int Redtama2_sound;
int Bluebomb_sound;
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
//##################▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ここまで複製▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲########################

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
//##################状態表示の関数########################
VOID JOUTAI_HYOUJI(VOID)
{
	DrawGraph(600, 400, lockon.Handle[(int)lockon1], TRUE);
	DrawGraph(610, 370, lockon.Handle[(int)lockon2], TRUE);
	DrawGraph(610, 442, lockon.Handle[(int)lockon3], TRUE);
	DrawRotaGraph(625, 350, 0.8, 0, lockon.Handle[(int)lockon1], TRUE);

	switch (shotmode)
	{
	case 0:
		DrawRotaFormatString(625, 440, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama1_dansuu);
		DrawRotaFormatString(628, 400, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama2_dansuu);
		DrawRotaFormatString(628, 467, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bluebomb1_dansuu);
		DrawRotaGraph(620, 420, 1.25, 1.0, tama_init.handle[(int)Redtama1], TRUE);
		DrawRotaGraph(625, 385, 1.0, 1.0, tama_init.handle[(int)Redtama2], TRUE);
		DrawRotaGraph(625, 457, 1.0, 1.0, tama_init.handle[(int)Bluebomb1], TRUE);
		break;
	case 1:
		DrawRotaFormatString(628, 467, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama1_dansuu);
		DrawRotaFormatString(625, 440, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama2_dansuu);
		DrawRotaFormatString(628, 400, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bluebomb1_dansuu);
		DrawRotaGraph(625, 457, 1.0, 1.0, tama_init.handle[(int)Redtama1], TRUE);
		DrawRotaGraph(620, 420, 1.25, 1.0, tama_init.handle[(int)Redtama2], TRUE);
		DrawRotaGraph(625, 385, 1.0, 1.0, tama_init.handle[(int)Bluebomb1], TRUE);
		break;
	case 2:
		DrawRotaFormatString(628, 400, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama1_dansuu);
		DrawRotaFormatString(628, 467, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama2_dansuu);
		DrawRotaFormatString(625, 440, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bluebomb1_dansuu);
		DrawRotaGraph(625, 385, 1.0, 1.0, tama_init.handle[(int)Redtama1], TRUE);
		DrawRotaGraph(625, 457, 1.0, 1.0, tama_init.handle[(int)Redtama2], TRUE);
		DrawRotaGraph(620, 420, 1.5, 1.0, tama_init.handle[(int)Bluebomb1], TRUE);
		break;
	}
	int f = player.HP;
	int ff;
	for (ff = 0; ff < player.HP; ff++)
	{
		DrawGraph(620, 150 + ff, HP, TRUE);//HPバー
	}
	if (HOUKOU != FALSE || HOUKOU_1 != FALSE)
	{
		switch (shothoukou)
		{
		case 0:
			DrawRotaGraph(player.x - 8, player.y + 16, 0.5, 3.15, yajirusi_2, TRUE);
			break;
		case 1:
			DrawRotaGraph(player.x - 8, player.y, 0.5, 3.8, yajirusi_2, TRUE);
			break;
		case 2:
			DrawRotaGraph(player.x - 8, player.y + 32, 0.5, 2.5, yajirusi_2, TRUE);
			break;
		}
	}
	if (reload == 1)
	{
		DrawRotaFormatString(player.x - 20, player.y + 55, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "リロード中");
	}
	DrawRotaFormatString(620, 330, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "%s速", dansokuhyouji);

	switch (shothoukou)
	{
	case 0:
		DrawRotaGraph(625, 350, 0.35, 3.15, yajirusi_3, TRUE);
		break;
	case 1:
		DrawRotaGraph(625, 350, 0.35, 3.8, yajirusi_3, TRUE);
		break;
	case 2:
		DrawRotaGraph(625, 350, 0.35, 2.5, yajirusi_3, TRUE);
		break;
	}
	//DrawRotaFormatString(300, 300, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "リロード中");
	//DrawRotaFormatString(300,300, 1.0, 2.0, 0.0, 0.0, 1.0, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "リロード中");
	//DrawFormatString(600, 10, GetColor(0, 255, 0), "%s速", dansokuhyouji);//弾速表示
	//DrawFormatString(590, 25, GetColor(0, 255, 0), "%s方向", houkouhyouji);//弾の方向表示
	//DrawFormatString(590, 40, GetColor(0, 255, 0), "%s弾", modehyouji);//弾の種類表示
	//DrawFormatString(100, 100, GetColor(0, 255, 0), "ゲーム画面");
	//DrawFormatString(10, 10, GetColor(0, 255, 0), "%d", count);//フレ＾ムカウント
	//DrawFormatString(10, 20, GetColor(0, 255, 0), "tamaW%d", tamaW);//フレ＾ムカウント
	//DrawFormatString(10, 30, GetColor(0, 255, 0), "tamaH%d", tamaH);//フレ＾ムカウント
	//DrawFormatString(10, 40, GetColor(0, 255, 0), "%d", i);//フレ＾ムカウント
	//DrawFormatString(10, 50, GetColor(0, 255, 0), "%d", player.HP);//フレ＾ムカウント
	//DrawFormatString(10, 60, GetColor(0, 255, 0), "通常弾:%d", Redtama1_dansuu);//フレ＾ムカウント
	//DrawFormatString(10, 75, GetColor(0, 255, 0), "気弾:%d", Redtama2_dansuu);//フレ＾ムカウント
	//DrawFormatString(10, 90, GetColor(0, 255, 0), "爆発弾:%d", Bluebomb1_dansuu);//フレ＾ムカウント
	//DrawFormatString(10, 105, GetColor(0, 255, 0), "%d", q);//フレ＾ムカウント
	//DrawFormatString(10, 120, GetColor(0, 255, 0), "%d", DAMAGE);//フレ＾ムカウント
}
//##################弾数の関数########################
VOID DANSUU(VOID)//リロード中に撃っても弾を消費するだけで弾は出ないぞ！　←　これを利用して重ねリロードできるｿﾞ
{
	if (reload == TRUE)
	{

		tama[i].IsView = FALSE;
		if (countC < count && Redtama1_dansuu < 1)//5秒たったら
		{
			Redtama1_dansuu = 15;//弾数補充し
			reload = FALSE;//リロードを終了
			A = FALSE;
		}
		if (countC < count && Redtama2_dansuu < 1)//5秒たったら
		{
			Redtama2_dansuu = 30;//弾数補充し
			reload = FALSE;//リロードを終了
			B = FALSE;
		}
		if (countC < count && Bluebomb1_dansuu < 1)//5秒たったら
		{
			Bluebomb1_dansuu = 5;//弾数補充し
			reload = FALSE;//リロードを終了
			C = FALSE;
		}
	}
	if (Key[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0)
	{
		if (RELOAD == FALSE)
		{
			RELOAD = TRUE;
			if (Redtama1_dansuu == 1 && shotmode == (int)Redtama1 && A == FALSE)
			{
				A = TRUE;
				countC = count + 180;
				reload = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}
			if (Redtama2_dansuu == 1 && shotmode == (int)Redtama2 && B == FALSE)
			{
				B = TRUE;
				countC = count + 180;
				reload = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}
			if (Bluebomb1_dansuu == 1 && shotmode == (int)Bluebomb1 && C == FALSE)
			{
				C = TRUE;
				countC = count + 180;
				reload = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}

			switch (shotmode)
			{
			case (int)Redtama1:
				if (Redtama1_dansuu > 0)
				{
					Redtama1_dansuu--;
				}
				break;
			case (int)Redtama2:
				if (Redtama2_dansuu > 0)
				{
					Redtama2_dansuu--;
				}
				break;
			case (int)Bluebomb1:
				if (Bluebomb1_dansuu > 0)
				{
					Bluebomb1_dansuu--;
				}
				break;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) == 0)
	{
		RELOAD = FALSE;
	}
}
//##################移動操作の関数########################
VOID IDOU_SOUSA(VOID)
{
	switch (reload)
	{
	case 0://通常時
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0 || Key[KEY_INPUT_DOWN] !=0) { // 右キーが押されていたら
			player.x += 4;                       // 右へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0 || Key[KEY_INPUT_LEFT] != 0) { // 下キーが押されていたら
				player.y += 4;                       // 下へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0 || Key[KEY_INPUT_UP] != 0) { // 左 キーが押されていたら
			player.x -= 4;                       // 左へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0 || Key[KEY_INPUT_RIGHT] != 0) { // 上キーが押されていたら
			player.y -= 4;                       // 上へ移動
		}
	case 1://リロード中は移動速度半減
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0 || Key[KEY_INPUT_DOWN] != 0) { // 右キーが押されていたら
			player.x += 2;                       // 右へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0 || Key[KEY_INPUT_LEFT] != 0) { // 下キーが押されていたら
			player.y += 2;                       // 下へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0 || Key[KEY_INPUT_UP] != 0) { // 左 キーが押されていたら
			player.x -= 2;                       // 左へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0 || Key[KEY_INPUT_RIGHT] != 0) { // 上キーが押されていたら
			player.y -= 2;                       // 上へ移動
		}
	}
	return;
}
//##################射撃関係の関数########################
VOID SHOT_MODE(VOID)
{
	if (Pad1 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0 || Key[KEY_INPUT_SPACE] == 1)
	{
		if (SHOT == FALSE)
		{
			SHOT = TRUE;
			tama[i].countA = count + 150;
			tama[i].houkou = shothoukou;
			tama[i].x = player.x - 18;
			tama[i].y = player.y + 15;
			tama[i].dansoku = dansoku;
			tama[i].shotmode = shotmode;
			if (reload != TRUE)
			{
				switch (shotmode)
				{
				case (int)Redtama1:
					PlaySoundMem(Redtama1_sound, DX_PLAYTYPE_BACK, TRUE);
					break;
				case (int)Redtama2:
					PlaySoundMem(Redtama2_sound, DX_PLAYTYPE_BACK, TRUE);
					break;
				}
			}
			if (reload == TRUE)
			{
				tama[i].IsView = FALSE;
			}
			else
			{
				tama[i].IsView = TRUE;
			}

			if (i < TAMA_MAX)
			{
				i++;
			}
			else
			{
				i = 0;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) == 0 || Key[KEY_INPUT_SPACE] == 0)
	{
		SHOT = FALSE;
	}
	//方向
	if (Key[KEY_INPUT_ESCAPE] == 1 || ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) != 0))
	{
		if (HOUKOU == FALSE)
		{
			shothoukou++;

			HOUKOU = TRUE;
			if (shothoukou == 3)
			{
				shothoukou = 0;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) == 0)
	{
		HOUKOU = FALSE;
	}

	if (Key[KEY_INPUT_ESCAPE] == 1 || ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0))
	{
		if (HOUKOU_1 == FALSE)
		{
			shothoukou--;
			HOUKOU_1 = TRUE;
			if (shothoukou == -1)
			{
				shothoukou = 2;
			}

			switch (shothoukou)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			}
		}
	}

	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) == 0)
	{
		HOUKOU_1 = FALSE;
	}

	//弾速
	if (Key[KEY_INPUT_F1] == 1 || ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0))
	{
		if (DANSOKU == FALSE)
		{
			dansokumode++;
			DANSOKU = TRUE;
			if (dansokumode == 3)
			{
				dansokumode = 0;
			}
			switch (shotmode)
			{
			case  (int)Redtama1:	//0
				switch (dansokumode)
				{
				case 0:
					dansoku = 3;
					sprintf(dansokuhyouji, "低");
					break;
				case 1:
					dansoku = 6;
					sprintf(dansokuhyouji, "中");
					break;
				case 2:
					dansoku = 9;
					sprintf(dansokuhyouji, "高");
					break;
				}

				break;
			case  (int)Redtama2:	//1
				switch (dansokumode)
				{
				case 0:
					dansoku = 1;
					sprintf(dansokuhyouji, "低");
					break;
				case 1:
					dansoku = 3;
					sprintf(dansokuhyouji, "中");
					break;
				case 2:
					dansoku = 5;
					sprintf(dansokuhyouji, "高");
					break;
				}

				break;
			case  (int)Bluebomb1:	//2
				switch (dansokumode)
				{
				case 0:
					dansoku = 2;
					sprintf(dansokuhyouji, "低");
					break;
				case 1:
					dansoku = 4;
					sprintf(dansokuhyouji, "中");
					break;
				case 2:
					dansoku = 6;
					sprintf(dansokuhyouji, "高");
					break;
				}
				break;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) == 0)
	{
		DANSOKU = FALSE;
	}
	//弾種
	if (Key[KEY_INPUT_F2] == 1 || ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0))
	{
		if (SHOTMODE == FALSE)
		{
			SHOTMODE = TRUE;
			//弾の種類を次にする
			shotmode++;

			if (shotmode > (int)Bluebomb1)
			{
				shotmode = (int)Redtama1;
			}

			switch (shotmode)
			{
			case  (int)Redtama1:	//0
				break;
			case  (int)Redtama2:	//1
				break;
			case  (int)Bluebomb1:	//2
				break;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) == 0)
	{
		SHOTMODE = FALSE;
	}
	if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) != 0))
	{
		if (SHOTMODE_1 == FALSE)
		{
			SHOTMODE_1 = TRUE;
			//弾の種類を次にする
			shotmode--;

			if (shotmode < (int)Redtama1)
			{
				shotmode = (int)Bluebomb1;
			}

			switch (shotmode)
			{
			case  (int)Redtama1:	//0
				break;
			case  (int)Redtama2:	//1
				break;
			case  (int)Bluebomb1:	//2
				break;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) == 0)
	{
		SHOTMODE_1 = FALSE;
	}
}
//##################弾の挙動の関数########################
VOID SHOT_KYODOU(VOID)
{
	//####################弾の挙動###########################
	for (int cnt = 0; cnt < 256; cnt++)
	{
		if (tama[cnt].IsView == TRUE)
		{
			switch (tama[cnt].houkou)
			{
			case 0:
				tama[cnt].x -= tama[cnt].dansoku;
				break;
			case 1:
				tama[cnt].x -= tama[cnt].dansoku;

				if (tama[cnt].y <= 0)//画面上端にぶつっかったら
				{
					ue[cnt] = TRUE;
				}

				if (ue[cnt] == TRUE)
				{
					tama[cnt].y += 2;//弾の向き反転
				}
				else
				{
					tama[cnt].y -= 2;
				}
				break;
			case 2:

				tama[cnt].x -= tama[cnt].dansoku;

				if (tama[cnt].y >= 465)
				{
					sita[cnt] = TRUE;//画面下端にぶつかったら
				}

				if (sita[cnt] == TRUE)
				{
					tama[cnt].y -= 2;//弾の向き反転
				}
				else
				{
					tama[cnt].y += 2;
				}
				break;
			}
	//####################弾の種類###########################

			int bomb = 2;
			switch (tama[cnt].shotmode)
			{
			case (int)Redtama1:
				DrawGraph(tama[cnt].x, tama[cnt].y, tama[cnt].handle[(int)Redtama1], TRUE); // レーザー			
				break;
			case (int)Redtama2:
				DrawGraph(tama[cnt].x, tama[cnt].y - 3, tama[cnt].handle[(int)Redtama2], TRUE); // 気弾
				break;
			case (int)Bluebomb1:
				
				if (tama[cnt].x < 100)
				{
						DrawGraph(tama[cnt].x, tama[cnt].y - 3, tama[cnt].handle[bomb], TRUE); // x,y の位置にキャラを描画

						bomb++;
				}
				else
				{
					DrawGraph(tama[cnt].x, tama[cnt].y - 3, tama[cnt].handle[bomb], TRUE); // x,y の位置にキャラを描画
				}
			}
			//弾を消すタイミング
			if (tama[cnt].x < 0 || tama[cnt].IsView == FALSE)
			{
				if (tama[cnt].shotmode >= (int)Bluebomb1)	//爆発弾ならば
				{
					if (tama[cnt].countB == 0)//爆発エフェクト
					{
						tama[cnt].IsView = FALSE;
					}
				}
				else//爆発弾じゃないなら
				{
					tama[cnt].IsView = FALSE;//弾を消す
				}
			}
		}
		//######################当たり判定###############################
		if (tama[cnt].IsView == TRUE)
		{
			/*
			if (tama[cnt].x < player.x + player.Width &&
				tama[cnt].y < player.y + player.Height &&
				tama[cnt].x + tamaW > player.x &&
				tama[cnt].y + tamaH > player.y)
			{
			}*/
			RECT rect_tama;		//RECTは四角の左、上、幅、高さの構造体
			rect_tama.left = tama[cnt].x;
			rect_tama.top = tama[cnt].y;
			RECT rect_player;	//RECTは四角の左、上、幅、高さの構造体
			rect_player.left = player.x;
			rect_player.top = player.y;
			rect_player.right = player.x + player.Width;
			rect_player.bottom = player.y + player.Height;
			RECT rect_tama_;		//RECTは四角の左、上、幅、高さの構造体
			rect_tama_.left = tama_[cnt].x;
			rect_tama_.top = tama_[cnt].y;
			RECT rect_player_;	//RECTは四角の左、上、幅、高さの構造体
			rect_player_.left = player_.x;
			rect_player_.top = player_.y;
			rect_player_.right = player_.x + player_.Width;
			rect_player_.bottom = player_.y + player_.Height;

			switch (tama[cnt].shotmode)
			{
			case (int)Redtama1:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Redtama1];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Redtama1];
				break;
			case (int)Redtama2:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Redtama2];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Redtama2];
				break;
			case (int)Bluebomb1:
				if (tama[cnt].countB <= 11)//爆発エフェクト
				{
					switch (tama[cnt].countB)
					{
					case 11:
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb1];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb1];
						break;
					case 10:
						tama[cnt].shotmode = (int)Bluebomb2;
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb2];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb2];
						break;
					case 9:
						tama[cnt].shotmode = (int)Bluebomb3;
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb3];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb3];
						break;
					case 8:
						tama[cnt].shotmode = (int)Bluebomb4;
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb4];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb4];
						break;
					case 7:
						tama[cnt].shotmode = (int)Bluebomb5;
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb5];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb5];
						break;
					case 6:
						tama[cnt].shotmode = (int)Bluebomb6;
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb6];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb6];
						break;
					case 5:
						tama[cnt].shotmode = (int)Bluebomb7;
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb7];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb7];
						break;
					case 4:
						tama[cnt].shotmode = (int)Bluebomb8;
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb8];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb8];
						break;
					case 3:
						tama[cnt].shotmode = (int)Bluebomb9;
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb9];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb9];
						break;
					case 2:
						tama[cnt].shotmode = (int)Bluebomb10;
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb10];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb10];
						break;
					case 1:
						tama[cnt].shotmode = (int)Bluebomb11;
						rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Bluebomb11];
						rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Bluebomb11];
						break;
					}
				}
				break;
			}

			if (ATARI_HANTEI(rect_tama, rect_player) == TRUE)//弾とプレイヤーが重なったとき
			{
				if (q < 100)//点滅させたい
				{
					if (q > 40 && q < 80)
					{
						DAMAGE = TRUE;
					}
					q++;
				}
				else
				{
					DAMAGE = FALSE;
					q = 0;
				}
				switch (tama[cnt].shotmode)
				{
				case  (int)Redtama1:	//0
					tama[cnt].IsView = FALSE;
					player.HP -= 10;
					break;
				case  (int)Redtama2:	//1
					tama[cnt].IsView = FALSE;
					player.HP -= 5;
					break;
				case  (int)Bluebomb1:	//2
					player.HP -= 15;
					tama[cnt].IsView = FALSE;

				case (int)Bluebomb2:
					player.HP -= 5;
				case (int)Bluebomb3:
					player.HP -= 5;
				case (int)Bluebomb4:
					player.HP -= 5;
				case (int)Bluebomb5:
					player.HP -= 5;
				case (int)Bluebomb6:
					player.HP -= 5;
				case (int)Bluebomb7:
					player.HP -= 5;
				case (int)Bluebomb8:
					player.HP -= 5;
				case (int)Bluebomb9:
					player.HP -= 5;
				case (int)Bluebomb10:
					player.HP -= 5;
				case (int)Bluebomb11:
					player.HP -= 5;
					tama[cnt].IsView = FALSE;
					break;
				}
				if (ATARI_HANTEI2(rect_tama_, rect_player) == TRUE)//弾とプレイヤーが重なったとき
				{
					switch (tama_[cnt].shotmode)
					{
					case  (int)Redtama1:	//0
						tama_[cnt].IsView = FALSE;
						player.HP -= 10;
						break;
					case  (int)Redtama2:	//1
						tama_[cnt].IsView = FALSE;
						player.HP -= 5;
						break;
					case  (int)Bluebomb1:	//2
						player.HP -= 15;
						tama_[cnt].IsView = FALSE;

					case (int)Bluebomb2:
						player.HP -= 5;
					case (int)Bluebomb3:
						player.HP -= 5;
					case (int)Bluebomb4:
						player.HP -= 5;
					case (int)Bluebomb5:
						player.HP -= 5;
					case (int)Bluebomb6:
						player.HP -= 5;
					case (int)Bluebomb7:
						player.HP -= 5;
					case (int)Bluebomb8:
						player.HP -= 5;
					case (int)Bluebomb9:
						player.HP -= 5;
					case (int)Bluebomb10:
						player.HP -= 5;
					case (int)Bluebomb11:
						player.HP -= 5;
						tama_[cnt].IsView = FALSE;
						break;
					}

					if (player.HP <= 0)
					{
						//体力が０ならばエンド画面
						mode = (int)scene_end;
						player.HP = 100;
					}
				}
			}
		}
	}
}
//##################画像読み込み関数########################
VOID GAZOU_YOMIKOMI(VOID)
{
	//####################画像読み込み#############################
	player.Handle = LoadGraph("画像/キャラクタ00.png"); // プレイヤー画像のロード
	tama_init.handle[(int)Redtama1] = LoadGraph("画像/赤レーザー.png");
	tama_init.handle[(int)Redtama2] = LoadGraph("画像/赤強弾.png");
	tama_init.handle[(int)Redtama3] = LoadGraph("画像/赤三角弾.png");
	tama_init.handle[(int)Bluebomb1] = LoadGraph("画像/青爆発/青爆発1.png");
	tama_init.handle[(int)Bluebomb2] = LoadGraph("画像/青爆発/青爆発2.png");
	tama_init.handle[(int)Bluebomb3] = LoadGraph("画像/青爆発/青爆発3.png");
	tama_init.handle[(int)Bluebomb4] = LoadGraph("画像/青爆発/青爆発4.png");
	tama_init.handle[(int)Bluebomb5] = LoadGraph("画像/青爆発/青爆発5.png");
	tama_init.handle[(int)Bluebomb6] = LoadGraph("画像/青爆発/青爆発6.png");
	tama_init.handle[(int)Bluebomb7] = LoadGraph("画像/青爆発/青爆発7.png");
	tama_init.handle[(int)Bluebomb8] = LoadGraph("画像/青爆発/青爆発8.png");
	tama_init.handle[(int)Bluebomb9] = LoadGraph("画像/青爆発/青爆発9.png");
	tama_init.handle[(int)Bluebomb10] = LoadGraph("画像/青爆発/青爆発10.png");
	tama_init.handle[(int)Bluebomb11] = LoadGraph("画像/青爆発/青爆発11.png");
	lockon.Handle[(int)lockon1] = LoadGraph("画像/ロックオン/ロックオン1.jpg");
	lockon.Handle[(int)lockon2] = LoadGraph("画像/ロックオン/ロックオン2.jpg");
	lockon.Handle[(int)lockon3] = LoadGraph("画像/ロックオン/ロックオン3.jpg");
	HP = LoadGraph("画像/HP.png");
	yajirusi_2 = LoadGraph("画像/矢印2.jpg");
	yajirusi_3 = LoadGraph("画像/矢印3.jpg");
	Redtama1_sound = (LoadSoundMem("画像/効果音/レーザー.mp3"));
	Redtama2_sound = (LoadSoundMem("画像/効果音/気弾.wav"));
	Bluebomb_sound = (LoadSoundMem("画像/効果音/爆発弾.wav"));
	reload_sound = (LoadSoundMem("画像/効果音/リロード.mp3"));
	//####################画像サイズ取得###########################
	GetGraphSize(player.Handle, &player.Width, &player.Height);
	GetGraphSize(tama_init.handle[(int)Redtama1], &tama_init.Width[(int)Redtama1], &tama_init.Height[(int)Redtama1]);
	GetGraphSize(tama_init.handle[(int)Redtama2], &tama_init.Width[(int)Redtama2], &tama_init.Height[(int)Redtama2]);
	GetGraphSize(tama_init.handle[(int)Redtama3], &tama_init.Width[(int)Redtama3], &tama_init.Height[(int)Redtama3]);
	GetGraphSize(tama_init.handle[(int)Bluebomb1], &tama_init.Width[(int)Bluebomb1], &tama_init.Height[(int)Bluebomb1]);
	GetGraphSize(tama_init.handle[(int)Bluebomb2], &tama_init.Width[(int)Bluebomb2], &tama_init.Height[(int)Bluebomb2]);
	GetGraphSize(tama_init.handle[(int)Bluebomb3], &tama_init.Width[(int)Bluebomb3], &tama_init.Height[(int)Bluebomb3]);
	GetGraphSize(tama_init.handle[(int)Bluebomb4], &tama_init.Width[(int)Bluebomb4], &tama_init.Height[(int)Bluebomb4]);
	GetGraphSize(tama_init.handle[(int)Bluebomb5], &tama_init.Width[(int)Bluebomb5], &tama_init.Height[(int)Bluebomb5]);
	GetGraphSize(tama_init.handle[(int)Bluebomb6], &tama_init.Width[(int)Bluebomb6], &tama_init.Height[(int)Bluebomb6]);
	GetGraphSize(tama_init.handle[(int)Bluebomb7], &tama_init.Width[(int)Bluebomb7], &tama_init.Height[(int)Bluebomb7]);
	GetGraphSize(tama_init.handle[(int)Bluebomb8], &tama_init.Width[(int)Bluebomb8], &tama_init.Height[(int)Bluebomb8]);
	GetGraphSize(tama_init.handle[(int)Bluebomb9], &tama_init.Width[(int)Bluebomb9], &tama_init.Height[(int)Bluebomb9]);
	GetGraphSize(tama_init.handle[(int)Bluebomb10], &tama_init.Width[(int)Bluebomb10], &tama_init.Height[(int)Bluebomb10]);
	GetGraphSize(tama_init.handle[(int)Bluebomb11], &tama_init.Width[(int)Bluebomb11], &tama_init.Height[(int)Bluebomb11]);
	//	GetGraphSize(lockon.Handle[(int)lockon1],&lockon.Width[(int)lockon1],&lockon.Height[(int)lockon1]);当たり判定考えないし画像サイズ取る必要なし
	//  GetGraphSize(lockon.Handle[(int)lockon2], &lockon.Width[(int)lockon2], &lockon.Height[(int)lockon2]);
	//	GetGraphSize(lockon.Handle[(int)lockon3], &lockon.Width[(int)lockon3], &lockon.Height[(int)lockon3]);

		//弾の初期化情報を基に、２５６個の弾に情報をコピー
	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		tama[cnt] = tama_init;
	}
	//####################初期プレイヤー位置###########################
	player.x = 320;
	player.y = 240;
	return;
}
VOID PLAYER_HYOUJI(VOID)
{
	if (DAMAGE != TRUE)//ダメージを食らっていないとき
	{
		DrawGraph(player.x, player.y, player.Handle, TRUE);
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
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ここから複製▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼########################
//##################状態表示の関数########################
VOID JOUTAI_HYOUJI_(VOID)
{
	DrawGraph(0, 30, lockon.Handle[(int)lockon1], TRUE);
	DrawGraph(0, 0, lockon.Handle[(int)lockon2], TRUE);
	DrawGraph(0, 72, lockon.Handle[(int)lockon3], TRUE);
	DrawRotaGraph(17, 123, 0.8, 0, lockon.Handle[(int)lockon1], TRUE);

	switch (shotmode_)
	{
	case 0:
		DrawRotaFormatString(16, 31, 1.0, 1.0, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama1_dansuu_);
		DrawRotaFormatString(12, 5, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama2_dansuu_);
		DrawRotaFormatString(13, 75, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bluebomb1_dansuu_);
		DrawRotaGraph(20, 50, 1.25, 4.0, tama_init_.handle[(int)Redtama1], TRUE);
		DrawRotaGraph(15, 15, 1.0, 4.0, tama_init_.handle[(int)Redtama2], TRUE);
		DrawRotaGraph(17, 87, 1.0, 4.0, tama_init_.handle[(int)Bluebomb1], TRUE);
		break;
	case 1:
		DrawRotaFormatString(13, 75, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama1_dansuu_);
		DrawRotaFormatString(16, 31, 1.0, 1.0, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama2_dansuu_);
		DrawRotaFormatString(12, 5, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bluebomb1_dansuu_);
		DrawRotaGraph(17, 87, 1.0, 4.0, tama_init_.handle[(int)Redtama1], TRUE);
		DrawRotaGraph(20, 50, 1.5, 4.0, tama_init_.handle[(int)Redtama2], TRUE);
		DrawRotaGraph(15, 15, 1.0, 4.0, tama_init_.handle[(int)Bluebomb1], TRUE);
		break;
	case 2:
		DrawRotaFormatString(12, 5, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama1_dansuu_);
		DrawRotaFormatString(13, 75, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Redtama2_dansuu_);
		DrawRotaFormatString(16, 31, 1.0, 1.0, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bluebomb1_dansuu_);
		DrawRotaGraph(15, 15, 1.0, 4.0, tama_init_.handle[(int)Redtama1], TRUE);
		DrawRotaGraph(17, 87, 1.0, 4.0, tama_init_.handle[(int)Redtama2], TRUE);
		DrawRotaGraph(20, 50, 1.25, 4.0, tama_init_.handle[(int)Bluebomb1], TRUE);
		break;
	}
	int f = player_.HP;
	int ff;
	for (ff = 0; ff < player_.HP; ff++)
	{
		DrawGraph(5, 330 - ff, HP, TRUE);//HPバー
	}
	if (HOUKOU_ != FALSE || HOUKOU_1_ != FALSE)
	{
		switch (shothoukou_)
		{
		case 0:
			DrawRotaGraph(player_.x + 40, player_.y + 16, 0.5, 0, yajirusi_2, TRUE);
			break;
		case 1:
			DrawRotaGraph(player_.x + 40, player_.y + 32, 0.5, 0.65, yajirusi_2, TRUE);
			break;
		case 2:
			DrawRotaGraph(player_.x + 40, player_.y, 0.5, -0.65, yajirusi_2, TRUE);
			break;
		}
	}
	if (reload_ == 1)
	{
		DrawRotaFormatString(player_.x - 20, player_.y + 55, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "リロード中");
	}
	DrawRotaFormatString(620, 330, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "%s速", dansokuhyouji);

	switch (shothoukou_)
	{
	case 0:
		DrawRotaGraph(17, 123, 0.35, 0, yajirusi_3, TRUE);
		break;
	case 1:
		DrawRotaGraph(17, 123, 0.35, 0.65, yajirusi_3, TRUE);
		break;
	case 2:
		DrawRotaGraph(17, 123, 0.35, -0.65, yajirusi_3, TRUE);
		break;
	}
	//DrawRotaFormatString(300, 300, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "リロード中");
	//DrawRotaFormatString(300,300, 1.0, 2.0, 0.0, 0.0, 1.0, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "リロード中");
	//DrawFormatString(600, 10, GetColor(0, 255, 0), "%s速", dansokuhyouji);//弾速表示
	//DrawFormatString(590, 25, GetColor(0, 255, 0), "%s方向", houkouhyouji);//弾の方向表示
	//DrawFormatString(590, 40, GetColor(0, 255, 0), "%s弾", modehyouji);//弾の種類表示
	//DrawFormatString(100, 100, GetColor(0, 255, 0), "ゲーム画面");
	//DrawFormatString(10, 10, GetColor(0, 255, 0), "%d", count);//フレ＾ムカウント
	//DrawFormatString(10, 20, GetColor(0, 255, 0), "tama_W%d", tama_W);//フレ＾ムカウント
	//DrawFormatString(10, 30, GetColor(0, 255, 0), "tama_H%d", tama_H);//フレ＾ムカウント
	//DrawFormatString(10, 40, GetColor(0, 255, 0), "%d", i);//フレ＾ムカウント
	//DrawFormatString(10, 50, GetColor(0, 255, 0), "%d", player_.HP);//フレ＾ムカウント
	//DrawFormatString(10, 60, GetColor(0, 255, 0), "通常弾:%d", Redtama1_dansuu_);//フレ＾ムカウント
	//DrawFormatString(10, 75, GetColor(0, 255, 0), "気弾:%d", Redtama2_dansuu_);//フレ＾ムカウント
	//DrawFormatString(10, 90, GetColor(0, 255, 0), "爆発弾:%d", Bluebomb1_dansuu_);//フレ＾ムカウント
	//DrawFormatString(10, 105, GetColor(0, 255, 0), "%d", q);//フレ＾ムカウント
	//DrawFormatString(10, 120, GetColor(0, 255, 0), "%d", DAMAGE);//フレ＾ムカウント
}
//##################弾数の関数########################
VOID DANSUU_(VOID)//リロード中に撃っても弾を消費するだけで弾は出ないぞ！　←　これを利用して重ねリロードできるｿﾞ
{
	if (reload_ == TRUE)
	{
		tama_[i_].IsView = FALSE;
		if (countC_ < count && Redtama1_dansuu_ < 1)//5秒たったら
		{
			Redtama1_dansuu_ = 15;//弾数補充し
			reload_ = FALSE;//リロードを終了
			A_ = FALSE;
		}
		if (countC_ < count && Redtama2_dansuu_ < 1)//5秒たったら
		{
			Redtama2_dansuu_ = 30;//弾数補充し
			reload_ = FALSE;//リロードを終了
			B_ = FALSE;
		}
		if (countC_ < count && Bluebomb1_dansuu_ < 1)//5秒たったら
		{
			Bluebomb1_dansuu_ = 5;//弾数補充し
			reload_ = FALSE;//リロードを終了
			C_ = FALSE;
		}
	}
	if (Key[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_3) != 0)
	{
		if (RELOAD_ == FALSE)
		{
			RELOAD_ = TRUE;
			if (Redtama1_dansuu_ == 1 && shotmode_ == (int)Redtama1 && A_ == FALSE)
			{
				A_ = TRUE;
				countC_ = count + 180;
				reload_ = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}
			if (Redtama2_dansuu_ == 1 && shotmode_ == (int)Redtama2 && B_ == FALSE)
			{
				B_ = TRUE;
				countC_ = count + 180;
				reload_ = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}
			if (Bluebomb1_dansuu_ == 1 && shotmode_ == (int)Bluebomb1 && C_ == FALSE)
			{
				C_ = TRUE;
				countC_ = count + 180;
				reload_ = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}

			switch (shotmode_)
			{
			case (int)Redtama1:
				if (Redtama1_dansuu_ > 0)
				{
					Redtama1_dansuu_--;
				}
				break;
			case (int)Redtama2:
				if (Redtama2_dansuu_ > 0)
				{
					Redtama2_dansuu_--;
				}
				break;
			case (int)Bluebomb1:
				if (Bluebomb1_dansuu_ > 0)
				{
					Bluebomb1_dansuu_--;
				}
				break;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_3) == 0)
	{
		RELOAD_ = FALSE;
	}
}


//##################移動操作の関数########################
VOID IDOU_SOUSA_(VOID)
{
	switch (reload_)
	{
	case 0://通常時
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_UP) != 0) { // 右キーが押されていたら
			player_.x += 4;                       // 右へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_RIGHT) != 0) { // 下キーが押されていたら
			player_.y += 4;                       // 下へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_DOWN) != 0) { // 左 キーが押されていたら
			player_.x -= 4;                       // 左へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_LEFT) != 0) { // 上キーが押されていたら
			player_.y -= 4;                       // 上へ移動
		}
	case 1://リロード中は移動速度半減
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_UP) != 0) { // 右キーが押されていたら
			player_.x += 2;                       // 右へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_RIGHT) != 0) { // 下キーが押されていたら
			player_.y += 2;                       // 下へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_DOWN) != 0) { // 左 キーが押されていたら
			player_.x -= 2;                       // 左へ移動
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_LEFT) != 0) { // 上キーが押されていたら
			player_.y -= 2;                       // 上へ移動
		}
	}
	return;
}
//##################射撃関係の関数########################
VOID SHOT_MODE_(VOID)
{
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_3) != 0)
	{
		if (SHOT_ == FALSE)
		{
			SHOT_ = TRUE;
			tama_[i_].countA = count + 150;
			tama_[i_].houkou = shothoukou_;
			tama_[i_].x = player_.x + 30;
			tama_[i_].y = player_.y + 15;
			tama_[i_].dansoku = dansoku_;
			tama_[i_].shotmode = shotmode_;
			if (reload_ != TRUE)
			{
				switch (shotmode_)
				{
				case (int)Redtama1:
					PlaySoundMem(Redtama1_sound, DX_PLAYTYPE_BACK, TRUE);
					break;
				case (int)Redtama2:
					PlaySoundMem(Redtama2_sound, DX_PLAYTYPE_BACK, TRUE);
					break;
				}
			}
			if (reload_ == TRUE)
			{
				tama_[i_].IsView = FALSE;
			}
			else
			{
				tama_[i_].IsView = TRUE;
			}

			if (i_ < TAMA_MAX)
			{
				i_++;
			}
			else
			{
				i_ = 0;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_3) == 0)
	{
		SHOT_ = FALSE;
	}
	//方向
	if (Key[KEY_INPUT_ESCAPE] == 1 || ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_6) != 0))
	{
		if (HOUKOU_ == FALSE)
		{
			shothoukou_++;

			HOUKOU_ = TRUE;
			if (shothoukou_ == 3)
			{
				shothoukou_ = 0;
			}

		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_6) == 0)
	{
		HOUKOU_ = FALSE;
	}

	if (Key[KEY_INPUT_ESCAPE] == 1 || ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_5) != 0))
	{
		if (HOUKOU_1_ == FALSE)
		{

			shothoukou_--;
			HOUKOU_1_ = TRUE;
			if (shothoukou_ == -1)
			{
				shothoukou_ = 2;
			}

			switch (shothoukou_)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			}
		}
	}

	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_5) == 0)
	{
		HOUKOU_1_ = FALSE;
	}

	//弾速
	if (Key[KEY_INPUT_F1] == 1 || ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_4) != 0))
	{
		if (DANSOKU_ == FALSE)
		{
			dansokumode_++;
			DANSOKU_ = TRUE;
			if (dansokumode_ == 3)
			{
				dansokumode_ = 0;
			}
			switch (shotmode_)
			{
			case  (int)Redtama1:	//0
				switch (dansokumode_)
				{
				case 0:
					dansoku_ = 3;
					sprintf(dansokuhyouji, "低");
					break;
				case 1:
					dansoku_ = 6;
					sprintf(dansokuhyouji, "中");
					break;
				case 2:
					dansoku_ = 9;
					sprintf(dansokuhyouji, "高");
					break;
				}

				break;
			case  (int)Redtama2:	//1
				switch (dansokumode_)
				{
				case 0:
					dansoku_ = 1;
					sprintf(dansokuhyouji, "低");
					break;
				case 1:
					dansoku_ = 3;
					sprintf(dansokuhyouji, "中");
					break;
				case 2:
					dansoku_ = 5;
					sprintf(dansokuhyouji, "高");
					break;
				}

				break;
			case  (int)Bluebomb1:	//2
				switch (dansokumode_)
				{
				case 0:
					dansoku_ = 2;
					sprintf(dansokuhyouji, "低");
					break;
				case 1:
					dansoku_ = 4;
					sprintf(dansokuhyouji, "中");
					break;
				case 2:
					dansoku_ = 6;
					sprintf(dansokuhyouji, "高");
					break;
				}
				break;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_4) == 0)
	{
		DANSOKU_ = FALSE;
	}
	//弾種
	if (Key[KEY_INPUT_F2] == 1 || ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_8) != 0))
	{
		if (SHOTMODE_ == FALSE)
		{
			SHOTMODE_ = TRUE;
			//弾の種類を次にする
			shotmode_++;

			if (shotmode_ > (int)Bluebomb1)
			{
				shotmode_ = (int)Redtama1;
			}

			switch (shotmode_)
			{
			case  (int)Redtama1:	//0
				break;
			case  (int)Redtama2:	//1
				break;
			case  (int)Bluebomb1:	//2
				break;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_8) == 0)
	{
		SHOTMODE_ = FALSE;
	}
	if (Key[KEY_INPUT_F2] == 1 || ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_7) != 0))
	{
		if (SHOTMODE_1_ == FALSE)
		{
			SHOTMODE_1_ = TRUE;
			//弾の種類を次にする
			shotmode_--;

			if (shotmode_ < (int)Redtama1)
			{
				shotmode_ = (int)Bluebomb1;
			}

			switch (shotmode_)
			{
			case  (int)Redtama1:	//0
				break;
			case  (int)Redtama2:	//1
				break;
			case  (int)Bluebomb1:	//2
				break;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_7) == 0)
	{
		SHOTMODE_1_ = FALSE;
	}
}
//##################弾の挙動の関数########################
VOID SHOT_KYODOU_(VOID)
{
	//####################弾の挙動###########################
	for (int cnt = 0; cnt < 256; cnt++)
	{
		if (tama_[cnt].IsView == TRUE)
		{
			switch (tama_[cnt].houkou)
			{
			case 0:
				tama_[cnt].x += tama_[cnt].dansoku;
				break;
			case 1:
				tama_[cnt].x += tama_[cnt].dansoku;

				if (tama_[cnt].y <= 0)//画面上端にぶつっかったら
				{
					ue_[cnt] = TRUE;
				}

				if (ue_[cnt] == TRUE)
				{
					tama_[cnt].y += 2;//弾の向き反転
				}
				else
				{
					tama_[cnt].y -= 2;
				}
				break;
			case 2:

				tama_[cnt].x += tama_[cnt].dansoku;

				if (tama_[cnt].y >= 465)
				{
					sita_[cnt] = TRUE;//画面下端にぶつかったら
				}

				if (sita_[cnt] == TRUE)
				{
					tama_[cnt].y -= 2;//弾の向き反転
				}
				else
				{
					tama_[cnt].y += 2;
				}
				break;
			}
			//####################弾の種類###########################
			switch (tama_[cnt].shotmode)
			{
			case (int)Redtama1:
				DrawGraph(tama_[cnt].x, tama_[cnt].y, tama_[cnt].handle[(int)Redtama1], TRUE); // レーザー			
				break;
			case (int)Redtama2:
				DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Redtama2], TRUE); // 気弾
				break;
			case (int)Bluebomb1:
				DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Bluebomb1], TRUE); // x,y の位置にキャラを描画
				break;
			}
			//弾を消すタイミング
			if (tama_[cnt].IsView == FALSE)//弾が消えたとき
			{
				if (tama_[cnt].shotmode == (int)Bluebomb1)	//爆発弾ならば
				{
					if (tama_[cnt].countB <= 11)//爆発エフェクト
					{
						switch (tama_[cnt].countB)
						{
						case 11:
							DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Bluebomb1], TRUE); // x,y の位置にキャラを描画
							break;
						case 10:
							DrawGraph(tama_[cnt].x - 2, tama_[cnt].y - 5, tama_[cnt].handle[(int)Bluebomb2], TRUE); // x,y の位置にキャラを描画
							break;
						case 9:
							DrawGraph(tama_[cnt].x - 2, tama_[cnt].y - 3, tama_[cnt].handle[(int)Bluebomb3], TRUE); // x,y の位置にキャラを描画
							break;
						case 8:
							DrawGraph(tama_[cnt].x + 1, tama_[cnt].y - 2, tama_[cnt].handle[(int)Bluebomb4], TRUE); // x,y の位置にキャラを描画
							break;
						case 7:
							DrawGraph(tama_[cnt].x - 2, tama_[cnt].y - 5, tama_[cnt].handle[(int)Bluebomb5], TRUE); // x,y の位置にキャラを描画
							break;
						case 6:
							DrawGraph(tama_[cnt].x - 4, tama_[cnt].y - 7, tama_[cnt].handle[(int)Bluebomb6], TRUE); // x,y の位置にキャラを描画
							break;
						case 5:
							DrawGraph(tama_[cnt].x - 8, tama_[cnt].y - 11, tama_[cnt].handle[(int)Bluebomb7], TRUE); // x,y の位置にキャラを描画
							break;
						case 4:
							DrawGraph(tama_[cnt].x - 13, tama_[cnt].y - 15, tama_[cnt].handle[(int)Bluebomb8], TRUE); // x,y の位置にキャラを描画
							break;
						case 3:
							DrawGraph(tama_[cnt].x - 19, tama_[cnt].y - 21, tama_[cnt].handle[(int)Bluebomb9], TRUE); // x,y の位置にキャラを描画
							break;
						case 2:
							DrawGraph(tama_[cnt].x - 25, tama_[cnt].y - 26.5, tama_[cnt].handle[(int)Bluebomb10], TRUE); // x,y の位置にキャラを描画
							break;
						case 1:
							DrawGraph(tama_[cnt].x - 30, tama_[cnt].y - 32, tama_[cnt].handle[(int)Bluebomb11], TRUE); // x,y の位置にキャラを描画
							PlaySoundMem(Bluebomb_sound, DX_PLAYTYPE_BACK, TRUE);
							break;
						}
						tama_[cnt].countB--;
					}
					if (tama_[cnt].countB == 0)//爆発エフェクト
					{
						tama_[cnt].IsView = FALSE;
					}
				}
				else
				{
					tama_[cnt].IsView = FALSE;
				}
			}
		}
		//######################当たり判定###############################
		if (tama_[cnt].IsView == TRUE)
		{
			/*
			if (tama_[cnt].x < player_.x + player_.Width &&
				tama_[cnt].y < player_.y + player_.Height &&
				tama_[cnt].x + tama_W > player_.x &&
				tama_[cnt].y + tama_H > player_.y)
			{
			}*/
			RECT rect_tama;		//RECTは四角の左、上、幅、高さの構造体
			rect_tama.left = tama[cnt].x;
			rect_tama.top = tama[cnt].y;
			RECT rect_player;	//RECTは四角の左、上、幅、高さの構造体
			rect_player.left = player.x;
			rect_player.top = player.y;
			rect_player.right = player.x + player.Width;
			rect_player.bottom = player.y + player.Height;

			RECT rect_tama_;		//RECTは四角の左、上、幅、高さの構造体
			rect_tama_.left = tama_[cnt].x;
			rect_tama_.top = tama_[cnt].y;
			RECT rect_player_;	//RECTは四角の左、上、幅、高さの構造体
			rect_player_.left = player_.x;
			rect_player_.top = player_.y;
			rect_player_.right = player_.x + player_.Width;
			rect_player_.bottom = player_.y + player_.Height;


			switch (tama_[cnt].shotmode)
			{
			case (int)Redtama1:
				rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Redtama1];
				rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Redtama1];
				break;
			case (int)Redtama2:
				rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Redtama2];
				rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Redtama2];
				break;
			case (int)Bluebomb1:
				if (tama_[cnt].countB <= 11)//爆発エフェクト
				{
					switch (tama_[cnt].countB)
					{
					case 11:
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb1];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb1];
						break;
					case 10:
						tama_[cnt].shotmode = (int)Bluebomb2;
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb2];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb2];
						break;
					case 9:
						tama_[cnt].shotmode = (int)Bluebomb3;
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb3];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb3];
						break;
					case 8:
						tama_[cnt].shotmode = (int)Bluebomb4;
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb4];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb4];
						break;
					case 7:
						tama_[cnt].shotmode = (int)Bluebomb5;
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb5];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb5];
						break;
					case 6:
						tama_[cnt].shotmode = (int)Bluebomb6;
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb6];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb6];
						break;
					case 5:
						tama_[cnt].shotmode = (int)Bluebomb7;
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb7];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb7];
						break;
					case 4:
						tama_[cnt].shotmode = (int)Bluebomb8;
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb8];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb8];
						break;
					case 3:
						tama_[cnt].shotmode = (int)Bluebomb9;
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb9];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb9];
						break;
					case 2:
						tama_[cnt].shotmode = (int)Bluebomb10;
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb10];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb10];
						break;
					case 1:
						tama_[cnt].shotmode = (int)Bluebomb11;
						rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bluebomb11];
						rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bluebomb11];
						break;
					}
				}
				break;
			}
			if (ATARI_HANTEI_(rect_tama_, rect_player_) == TRUE)//弾とプレイヤーが重なったとき
			{
				switch (tama_[cnt].shotmode)
				{
				case  (int)Redtama1:	//0
					tama_[cnt].IsView = FALSE;
					player_.HP -= 10;
					break;
				case  (int)Redtama2:	//1
					tama_[cnt].IsView = FALSE;
					player_.HP -= 5;
					break;
				case  (int)Bluebomb1:	//2
					player_.HP -= 15;
					tama_[cnt].IsView = FALSE;

				case (int)Bluebomb2:
					player_.HP -= 5;
				case (int)Bluebomb3:
					player_.HP -= 5;
				case (int)Bluebomb4:
					player_.HP -= 5;
				case (int)Bluebomb5:
					player_.HP -= 5;
				case (int)Bluebomb6:
					player_.HP -= 5;
				case (int)Bluebomb7:
					player_.HP -= 5;
				case (int)Bluebomb8:
					player_.HP -= 5;
				case (int)Bluebomb9:
					player_.HP -= 5;
				case (int)Bluebomb10:
					player_.HP -= 5;
				case (int)Bluebomb11:
					player_.HP -= 5;
					tama_[cnt].IsView = FALSE;
					break;
				}
				if (ATARI_HANTEI_2(rect_tama, rect_player_) == TRUE)//弾とプレイヤーが重なったとき
				{
					switch (tama[cnt].shotmode)
					{
					case  (int)Redtama1:	//0
						tama[cnt].IsView = FALSE;
						player_.HP -= 10;
						break;
					case  (int)Redtama2:	//1
						tama[cnt].IsView = FALSE;
						player_.HP -= 5;
						break;
					case  (int)Bluebomb1:	//2
						player_.HP -= 15;
						tama[cnt].IsView = FALSE;

					case (int)Bluebomb2:
						player_.HP -= 5;
					case (int)Bluebomb3:
						player_.HP -= 5;
					case (int)Bluebomb4:
						player_.HP -= 5;
					case (int)Bluebomb5:
						player_.HP -= 5;
					case (int)Bluebomb6:
						player_.HP -= 5;
					case (int)Bluebomb7:
						player_.HP -= 5;
					case (int)Bluebomb8:
						player_.HP -= 5;
					case (int)Bluebomb9:
						player_.HP -= 5;
					case (int)Bluebomb10:
						player_.HP -= 5;
					case (int)Bluebomb11:
						player_.HP -= 5;
						tama[cnt].IsView = FALSE;
						break;
					}

					if (player_.HP <= 0)
					{
						//体力が０ならばエンド画面
						mode = (int)scene_end;
						player_.HP = 100;
					}
				}
			}
		}
	}
}
//##################画像読み込み関数########################
VOID GAZOU_YOMIKOMI_(VOID)
{
	//####################画像読み込み#############################
	player_.Handle = LoadGraph("画像/キャラクタ02.png"); // プレイヤー画像のロード
	tama_init_.handle[(int)Redtama1] = LoadGraph("画像/赤レーザー.png");
	tama_init_.handle[(int)Redtama2] = LoadGraph("画像/赤強弾.png");
	tama_init_.handle[(int)Redtama3] = LoadGraph("画像/赤三角弾.png");
	tama_init_.handle[(int)Bluebomb1] = LoadGraph("画像/青爆発/青爆発1.png");
	tama_init_.handle[(int)Bluebomb2] = LoadGraph("画像/青爆発/青爆発2.png");
	tama_init_.handle[(int)Bluebomb3] = LoadGraph("画像/青爆発/青爆発3.png");
	tama_init_.handle[(int)Bluebomb4] = LoadGraph("画像/青爆発/青爆発4.png");
	tama_init_.handle[(int)Bluebomb5] = LoadGraph("画像/青爆発/青爆発5.png");
	tama_init_.handle[(int)Bluebomb6] = LoadGraph("画像/青爆発/青爆発6.png");
	tama_init_.handle[(int)Bluebomb7] = LoadGraph("画像/青爆発/青爆発7.png");
	tama_init_.handle[(int)Bluebomb8] = LoadGraph("画像/青爆発/青爆発8.png");
	tama_init_.handle[(int)Bluebomb9] = LoadGraph("画像/青爆発/青爆発9.png");
	tama_init_.handle[(int)Bluebomb10] = LoadGraph("画像/青爆発/青爆発10.png");
	tama_init_.handle[(int)Bluebomb11] = LoadGraph("画像/青爆発/青爆発11.png");
	lockon.Handle[(int)lockon1] = LoadGraph("画像/ロックオン/ロックオン1.jpg");
	lockon.Handle[(int)lockon2] = LoadGraph("画像/ロックオン/ロックオン2.jpg");
	lockon.Handle[(int)lockon3] = LoadGraph("画像/ロックオン/ロックオン3.jpg");
	HP = LoadGraph("画像/HP.png");
	yajirusi_2 = LoadGraph("画像/矢印2.jpg");
	yajirusi_3 = LoadGraph("画像/矢印3.jpg");
	Redtama1_sound = (LoadSoundMem("画像/効果音/レーザー.mp3"));
	Redtama2_sound = (LoadSoundMem("画像/効果音/気弾.wav"));
	Bluebomb_sound = (LoadSoundMem("画像/効果音/爆発弾.wav"));
	reload_sound = (LoadSoundMem("画像/効果音/リロード.mp3"));
	//####################画像サイズ取得###########################
	GetGraphSize(player_.Handle, &player_.Width, &player_.Height);
	GetGraphSize(tama_init_.handle[(int)Redtama1], &tama_init_.Width[(int)Redtama1], &tama_init_.Height[(int)Redtama1]);
	GetGraphSize(tama_init_.handle[(int)Redtama2], &tama_init_.Width[(int)Redtama2], &tama_init_.Height[(int)Redtama2]);
	GetGraphSize(tama_init_.handle[(int)Redtama3], &tama_init_.Width[(int)Redtama3], &tama_init_.Height[(int)Redtama3]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb1], &tama_init_.Width[(int)Bluebomb1], &tama_init_.Height[(int)Bluebomb1]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb2], &tama_init_.Width[(int)Bluebomb2], &tama_init_.Height[(int)Bluebomb2]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb3], &tama_init_.Width[(int)Bluebomb3], &tama_init_.Height[(int)Bluebomb3]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb4], &tama_init_.Width[(int)Bluebomb4], &tama_init_.Height[(int)Bluebomb4]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb5], &tama_init_.Width[(int)Bluebomb5], &tama_init_.Height[(int)Bluebomb5]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb6], &tama_init_.Width[(int)Bluebomb6], &tama_init_.Height[(int)Bluebomb6]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb7], &tama_init_.Width[(int)Bluebomb7], &tama_init_.Height[(int)Bluebomb7]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb8], &tama_init_.Width[(int)Bluebomb8], &tama_init_.Height[(int)Bluebomb8]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb9], &tama_init_.Width[(int)Bluebomb9], &tama_init_.Height[(int)Bluebomb9]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb10], &tama_init_.Width[(int)Bluebomb10], &tama_init_.Height[(int)Bluebomb10]);
	GetGraphSize(tama_init_.handle[(int)Bluebomb11], &tama_init_.Width[(int)Bluebomb11], &tama_init_.Height[(int)Bluebomb11]);
	//	GetGraphSize(lockon_.Handle[(int)lockon_1],&lockon_.Width[(int)lockon_1],&lockon_.Height[(int)lockon_1]);当たり判定考えないし画像サイズ取る必要なし
	//  GetGraphSize(lockon_.Handle[(int)lockon_2], &lockon_.Width[(int)lockon_2], &lockon_.Height[(int)lockon_2]);
	//	GetGraphSize(lockon_.Handle[(int)lockon_3], &lockon_.Width[(int)lockon_3], &lockon_.Height[(int)lockon_3]);

		//弾の初期化情報を基に、２５６個の弾に情報をコピー
	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		tama_[cnt] = tama_init_;
	}
	//####################初期プレイヤー位置###########################
	player_.x = 220;
	player_.y = 240;
	return;
}

//##################当たり判定の関数########################
BOOL ATARI_HANTEI(RECT tama, RECT player)//()の中はこの構造体の変数を使うよ、的な 
{
	if (tama.left < player.right &&
		tama.top < player.bottom &&
		tama.right > player.left &&
		tama.bottom > player.top)
	{
		return TRUE;
	}
	return FALSE;
}//BOOL関数はVOIDとは使いどころが違うみたい
BOOL ATARI_HANTEI2(RECT tama_, RECT player)//()の中はこの構造体の変数を使うよ、的な 
{
	if (tama_.left < player.right &&
		tama_.top < player.bottom &&
		tama_.right > player.left &&
		tama_.bottom > player.top)
	{
		return TRUE;
	}
	return FALSE;
}//BOOL関数はVOIDとは使いどころが違うみたい
//##################当たり判定の関数########################
BOOL ATARI_HANTEI_(RECT tama_, RECT player_)//()の中はこの構造体の変数を使うよ、的な 
{
	if (tama_.left < player_.right &&
		tama_.top < player_.bottom &&
		tama_.right > player_.left &&
		tama_.bottom > player_.top)
	{
		return TRUE;
	}
	return FALSE;
}//BOOL関数はVOIDとは使いどころが違うみたい
BOOL ATARI_HANTEI_2(RECT tama, RECT player_)//()の中はこの構造体の変数を使うよ、的な 
{
	if (tama.left < player_.right &&
		tama.top < player_.bottom &&
		tama.right > player_.left &&
		tama.bottom > player_.top)
	{
		return TRUE;
	}
	return FALSE;
}//BOOL関数はVOIDとは使いどころが違うみたい

VOID PLAYER_HYOUJI_(VOID)
{
	if (DAMAGE != TRUE)//ダメージを食らっていないとき
	{
		DrawGraph(player_.x, player_.y, player_.Handle, TRUE);
	}
}
