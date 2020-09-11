#define _CRT_SECURE_NO_WARNINGS
//弾の種類を作りきる
#include "DxLib.h"
#include "Header.h"
#include "player1.h"
#include "player2.h"

int Laser_dansuu = 15;
int Energy_dansuu = 30;
int Bomb1_dansuu = 5;//1で止めるためこれで5発 

int countC;//リロードの時間格納用　５秒
int i = 0;//個別の弾用の数字
int shothoukou = 0;//弾の方向
int dansoku = 2;//初期弾速
int dansokumode = 0;//弾速の変更
int shotmode = 0;//弾の種類　初期弾種：０
int q = 0;
int cnt = 0;

TAMA tama_init;	//弾の画像読み込み・初期化のために使う変数
TAMA tama[TAMA_MAX];//構造体の配列

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
PLAYER player;	//構造体の変数

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
		DrawRotaFormatString(625, 440, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Laser_dansuu);
		DrawRotaFormatString(628, 400, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Energy_dansuu);
		DrawRotaFormatString(628, 467, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bomb1_dansuu);
		DrawRotaGraph(620, 420, 1.25, 1.0, tama_init.handle[(int)Laser], TRUE);
		DrawRotaGraph(625, 385, 1.0, 1.0, tama_init.handle[(int)Energy], TRUE);
		DrawRotaGraph(625, 457, 1.0, 1.0, tama_init.handle[(int)Bomb1], TRUE);
		break;
	case 1:
		DrawRotaFormatString(628, 467, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Laser_dansuu);
		DrawRotaFormatString(625, 440, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Energy_dansuu);
		DrawRotaFormatString(628, 400, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bomb1_dansuu);
		DrawRotaGraph(625, 457, 1.0, 1.0, tama_init.handle[(int)Laser], TRUE);
		DrawRotaGraph(620, 420, 1.25, 1.0, tama_init.handle[(int)Energy], TRUE);
		DrawRotaGraph(625, 385, 1.0, 1.0, tama_init.handle[(int)Bomb1], TRUE);
		break;
	case 2:
		DrawRotaFormatString(628, 400, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Laser_dansuu);
		DrawRotaFormatString(628, 467, 0.75, 0.75, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Energy_dansuu);
		DrawRotaFormatString(625, 440, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bomb1_dansuu);
		DrawRotaGraph(625, 385, 1.0, 1.0, tama_init.handle[(int)Laser], TRUE);
		DrawRotaGraph(625, 457, 1.0, 1.0, tama_init.handle[(int)Energy], TRUE);
		DrawRotaGraph(620, 420, 1.5, 1.0, tama_init.handle[(int)Bomb1], TRUE);
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
	DrawFormatString(590, 25, GetColor(0, 255, 0), "%d", shotmode);//弾の方向表示
	//DrawFormatString(590, 40, GetColor(0, 255, 0), "%s弾", modehyouji);//弾の種類表示
	//DrawFormatString(100, 100, GetColor(0, 255, 0), "ゲーム画面");
	//DrawFormatString(10, 10, GetColor(0, 255, 0), "%d", count);//フレ＾ムカウント
	//DrawFormatString(10, 20, GetColor(0, 255, 0), "tamaW%d", tamaW);//フレ＾ムカウント
	//DrawFormatString(10, 30, GetColor(0, 255, 0), "tamaH%d", tamaH);//フレ＾ムカウント
	//DrawFormatString(10, 40, GetColor(0, 255, 0), "%d", i);//フレ＾ムカウント
	//DrawFormatString(10, 50, GetColor(0, 255, 0), "%d", player.HP);//フレ＾ムカウント
	//DrawFormatString(10, 60, GetColor(0, 255, 0), "通常弾:%d", Laser_dansuu);//フレ＾ムカウント
	//DrawFormatString(10, 75, GetColor(0, 255, 0), "気弾:%d", Energy_dansuu);//フレ＾ムカウント
	//DrawFormatString(10, 90, GetColor(0, 255, 0), "爆発弾:%d", Bomb1_dansuu);//フレ＾ムカウント
	//DrawFormatString(10, 105, GetColor(0, 255, 0), "%d", q);//フレ＾ムカウント
	//DrawFormatString(10, 120, GetColor(0, 255, 0), "%d", DAMAGE);//フレ＾ムカウント
}
//##################弾数の関数########################
VOID DANSUU(VOID)//リロード中に撃っても弾を消費するだけで弾は出ないぞ！　←　これを利用して重ねリロードできるｿﾞ
{
	if (reload == TRUE)
	{
		tama[i].IsView = FALSE;
		if (countC < count && Laser_dansuu < 1)//5秒たったら
		{
			Laser_dansuu = 15;//弾数補充し
			reload = FALSE;//リロードを終了
			A = FALSE;
		}
		if (countC < count && Energy_dansuu < 1)//5秒たったら
		{
			Energy_dansuu = 30;//弾数補充し
			reload = FALSE;//リロードを終了
			B = FALSE;
		}
		if (countC < count && Bomb1_dansuu < 1)//5秒たったら
		{
			Bomb1_dansuu = 5;//弾数補充し
			reload = FALSE;//リロードを終了
			C = FALSE;
		}
	}
	if (Key[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0)
	{
		if (RELOAD == FALSE)
		{
			RELOAD = TRUE;
			if (Laser_dansuu == 1 && shotmode == (int)Laser && A == FALSE)
			{
				A = TRUE;
				countC = count + 180;
				reload = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}
			if (Energy_dansuu == 1 && shotmode == (int)Energy && B == FALSE)
			{
				B = TRUE;
				countC = count + 180;
				reload = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}
			if (Bomb1_dansuu == 1 && shotmode == (int)Bomb1 && C == FALSE)
			{
				C = TRUE;
				countC = count + 180;
				reload = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}

			switch (shotmode)
			{
			case (int)Laser:
				if (Laser_dansuu > 0)
				{
					Laser_dansuu--;
				}
				break;
			case (int)Energy:
				if (Energy_dansuu > 0)
				{
					Energy_dansuu--;
				}
				break;
			case (int)Bomb1:
				if (Bomb1_dansuu > 0)
				{
					Bomb1_dansuu--;
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
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0 || Key[KEY_INPUT_DOWN] != 0) { // 右キーが押されていたら
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
			tama[i].houkou = shothoukou;
			tama[i].x = player.x - 18;
			tama[i].y = player.y + 15;
			tama[i].dansoku = dansoku;
			tama[i].shotmode = shotmode;
			if (reload != TRUE)
			{
				switch (shotmode)
				{
				case (int)Laser:
					PlaySoundMem(Laser_sound, DX_PLAYTYPE_BACK, TRUE);
					break;
				case (int)Energy:
					PlaySoundMem(Energy_sound, DX_PLAYTYPE_BACK, TRUE);
					break;
				}
			}
			if (reload == TRUE)//リロード中は撃っても弾が減るだけ　ｶﾁｶﾁっと不発音を付ける
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
			case  (int)Laser:	//0
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
			case  (int)Energy:	//1
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
			case  (int)Bomb1:	//2
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
			if (shotmode == (int)Bomb2)
			{
				shotmode = (int)Delay;
			}

			if (shotmode == (int)XchaLu)
			{
				shotmode = (int)Tcha;
			}

			if (shotmode == (int)TAMA_KIND_END)
			{
				shotmode = (int)Laser;
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

			if (shotmode < (int)Laser)
			{
				shotmode = (int)Bomb1;
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
	for (cnt = 0; cnt < 256; cnt++)
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

			switch (tama[cnt].shotmode)
			{
			case (int)Laser:
				DrawGraph(tama[cnt].x, tama[cnt].y, tama[cnt].handle[(int)Laser], TRUE); // レーザー			
				break;
			case (int)Energy:
				DrawGraph(tama[cnt].x, tama[cnt].y - 3, tama[cnt].handle[(int)Energy], TRUE); // 気弾
				break;
			case (int)Bomb1:
				BLUE_BOMB(&tama[cnt]);
				break;
			case (int)Delay:
				DELAY(&tama[cnt]);
				break;
			case (int)Ycha:
				YCHA(&tama[cnt]);
				break;
			case (int)Xcha:
				XCHA(&tama[cnt]);
				break;
			case (int)Tcha:
				TCHA(&tama[cnt]);
				break;
			case (int)Snipe:
				SNIPE(&tama[cnt]);
				break;
			case (int)Stay:
				STAY(&tama[cnt]);
				break;
			case (int)Test:
				TEST(&tama[cnt]);
				break;
			}

			//弾を消すタイミング
			if (tama[cnt].x < 0 || tama[cnt].IsView == FALSE)
			{
				if (tama[cnt].shotmode >= (int)Bomb1)	//爆発弾ならば
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
			rect_tama.top = tama[cnt].y;//画像の大きさにより、サイズを下で分岐
			RECT rect_player;	//RECTは四角の左、上、幅、高さの構造体
			rect_player.left = player.x;
			rect_player.top = player.y;//当たり判定小さくするときはx.yを+ width height を-する。
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
			case (int)Laser:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Laser];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Laser];
				break;
			case (int)Energy:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Energy];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Energy];
				break;
			case (int)Bomb1:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[tama[cnt].BombKind];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[tama[cnt].BombKind];
				break;
			case (int)Delay:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Delay];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Delay];
				break;
			case (int)Ycha:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Ycha];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Ycha];
				break;
			case (int)Xcha:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Xcha];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Xcha];
				break;
			case (int)Tcha:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Tcha];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Tcha];
				break;
			case (int)Snipe:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Snipe];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Snipe];
				break;
			case (int)Stay:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Stay];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Stay];
				break;
			case (int)Test:
				rect_tama.right = tama[cnt].x + tama[cnt].Width[(int)Test];
				rect_tama.bottom = tama[cnt].y + tama[cnt].Height[(int)Test];
				break;
			}

			//自分の弾と自機があったとき
			/*
			if (ATARI_HANTEI(rect_tama, rect_player) == TRUE)//弾とプレイヤーが重なったとき
			{

				//当たった弾を非表示にする
				//tama[cnt].IsView = FALSE;

				//HPを減らす
				switch (tama[cnt].shotmode)
				{
				case (int)Laser:
					player.HP -= 10;
					break;
				case (int)Energy:
					player.HP -= 5;
					break;
				case (int)Bomb1:

					break;
				case (int)Bomb2:

					break;
				case (int)Bomb3:

					break;
				case (int)Bomb4:

					break;
				case (int)Bomb5:

					break;
				case (int)Bomb6:

					break;
				case (int)Bomb7:

					break;
				case (int)Bomb8:

					break;
				case (int)Bomb9:

					break;
				case (int)Bomb10:

					break;
				case (int)Bomb11:

					break;
				case (int)Delay:

					break;
				case (int)Ycha:

					break;
				case (int)Xcha:

					break;
				case (int)XchaLu:

					break;
				case (int)XchaLd:

					break;
				case (int)XchaRu:

					break;
				case (int)XchaRd:

					break;
				case (int)Tcha:

					break;
				case (int)Snipe:

					break;
				case (int)Stay:

					break;

				}
			}
			*/

			//相手の弾と自機があったとき
			if (ATARI_HANTEI(rect_tama, rect_player_) == TRUE)//アンダーバー付け替え忘れるな
			{
				//当たった弾を非表示にする
				tama[cnt].IsView = FALSE;

				//HPを減らす
				switch (tama_[cnt].shotmode)
				{
				case (int)Laser:
					player_.HP -= 10;
					break;
				case (int)Energy:
					player_.HP -= 5;
					break;
				case (int)Bomb1:

					break;
				case (int)Bomb2:

					break;
				case (int)Bomb3:

					break;
				case (int)Bomb4:

					break;
				case (int)Bomb5:

					break;
				case (int)Bomb6:

					break;
				case (int)Bomb7:

					break;
				case (int)Bomb8:

					break;
				case (int)Bomb9:

					break;
				case (int)Bomb10:

					break;
				case (int)Bomb11:

					break;
				case (int)Delay:

					break;
				case (int)Ycha:

					break;
				case (int)Xcha:

					break;
				case (int)XchaLu:

					break;
				case (int)XchaLd:

					break;
				case (int)XchaRu:

					break;
				case (int)XchaRd:

					break;
				case (int)Tcha:

					break;
				case (int)Snipe:

					break;
				case (int)Stay:

					break;

				}
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

//##################当たり判定の関数########################
BOOL ATARI_HANTEI(RECT tama_, RECT player)//()の中はこの構造体の変数を使うよ、的な 
{
	if (tama_.left < player.right &&
		tama_.top < player.bottom &&
		tama_.right > player.left &&
		tama_.bottom > player.top)
	{
		return TRUE;
	}
	return FALSE;
}

//##################画像読み込み関数########################
VOID GAZOU_YOMIKOMI(VOID)
{
	//####################画像読み込み#############################
	player.Handle = LoadGraph("画像/キャラクタ00.png"); // プレイヤー画像のロード
	tama_init.handle[(int)Laser] = LoadGraph("画像/弾/赤レーザー.png");
	tama_init.handle[(int)Energy] = LoadGraph("画像/弾/赤強弾.png");
	tama_init.handle[(int)Bomb1] = LoadGraph("画像/青爆発/青爆発1.png");
	tama_init.handle[(int)Bomb2] = LoadGraph("画像/青爆発/青爆発2.png");
	tama_init.handle[(int)Bomb3] = LoadGraph("画像/青爆発/青爆発3.png");
	tama_init.handle[(int)Bomb4] = LoadGraph("画像/青爆発/青爆発4.png");
	tama_init.handle[(int)Bomb5] = LoadGraph("画像/青爆発/青爆発5.png");
	tama_init.handle[(int)Bomb6] = LoadGraph("画像/青爆発/青爆発6.png");
	tama_init.handle[(int)Bomb7] = LoadGraph("画像/青爆発/青爆発7.png");
	tama_init.handle[(int)Bomb8] = LoadGraph("画像/青爆発/青爆発8.png");
	tama_init.handle[(int)Bomb9] = LoadGraph("画像/青爆発/青爆発9.png");
	tama_init.handle[(int)Bomb10] = LoadGraph("画像/青爆発/青爆発10.png");
	tama_init.handle[(int)Bomb11] = LoadGraph("画像/青爆発/青爆発11.png");
	tama_init.handle[(int)Delay] = LoadGraph("画像/弾/桃レーザー.png");
	tama_init.handle[(int)Ycha] = LoadGraph("画像/弾/赤三角弾.png");
	tama_init.handle[(int)Xcha] = LoadGraph("画像/弾/X弾.png");

	tama_init.handle[(int)XchaLu] = LoadGraph("画像/弾/赤三角弾.png");
	tama_init.handle[(int)XchaLd] = LoadGraph("画像/弾/赤三角弾.png");
	tama_init.handle[(int)XchaRu] = LoadGraph("画像/弾/赤三角弾.png");
	tama_init.handle[(int)XchaRd] = LoadGraph("画像/弾/赤三角弾.png");

	tama_init.handle[(int)Tcha] = LoadGraph("画像/弾/＋弾.png");
	tama_init.handle[(int)Snipe] = LoadGraph("画像/弾/Snipe弾.png");

	tama_init.handle[(int)Stay] = LoadGraph("画像/弾/Stay弾.png");

	tama_init.handle[(int)Test] = LoadGraph("画像/青爆発/青爆発11.png");

	lockon.Handle[(int)lockon1] = LoadGraph("画像/ロックオン/ロックオン1.jpg");
	lockon.Handle[(int)lockon2] = LoadGraph("画像/ロックオン/ロックオン2.jpg");
	lockon.Handle[(int)lockon3] = LoadGraph("画像/ロックオン/ロックオン3.jpg");
	HP = LoadGraph("画像/HP.png");
	yajirusi_2 = LoadGraph("画像/矢印2.jpg");
	yajirusi_3 = LoadGraph("画像/矢印3.jpg");
	Laser_sound = (LoadSoundMem("画像/効果音/レーザー.mp3"));
	Energy_sound = (LoadSoundMem("画像/効果音/気弾.wav"));
	Bomb_sound = (LoadSoundMem("画像/効果音/爆発弾.wav"));
	reload_sound = (LoadSoundMem("画像/効果音/リロード.mp3"));
	//####################画像サイズ取得###########################
	GetGraphSize(player.Handle, &player.Width, &player.Height);
	GetGraphSize(tama_init.handle[(int)Laser], &tama_init.Width[(int)Laser], &tama_init.Height[(int)Laser]);
	GetGraphSize(tama_init.handle[(int)Energy], &tama_init.Width[(int)Energy], &tama_init.Height[(int)Energy]);
	GetGraphSize(tama_init.handle[(int)Bomb1], &tama_init.Width[(int)Bomb1], &tama_init.Height[(int)Bomb1]);
	GetGraphSize(tama_init.handle[(int)Bomb2], &tama_init.Width[(int)Bomb2], &tama_init.Height[(int)Bomb2]);
	GetGraphSize(tama_init.handle[(int)Bomb3], &tama_init.Width[(int)Bomb3], &tama_init.Height[(int)Bomb3]);
	GetGraphSize(tama_init.handle[(int)Bomb4], &tama_init.Width[(int)Bomb4], &tama_init.Height[(int)Bomb4]);
	GetGraphSize(tama_init.handle[(int)Bomb5], &tama_init.Width[(int)Bomb5], &tama_init.Height[(int)Bomb5]);
	GetGraphSize(tama_init.handle[(int)Bomb6], &tama_init.Width[(int)Bomb6], &tama_init.Height[(int)Bomb6]);
	GetGraphSize(tama_init.handle[(int)Bomb7], &tama_init.Width[(int)Bomb7], &tama_init.Height[(int)Bomb7]);
	GetGraphSize(tama_init.handle[(int)Bomb8], &tama_init.Width[(int)Bomb8], &tama_init.Height[(int)Bomb8]);
	GetGraphSize(tama_init.handle[(int)Bomb9], &tama_init.Width[(int)Bomb9], &tama_init.Height[(int)Bomb9]);
	GetGraphSize(tama_init.handle[(int)Bomb10], &tama_init.Width[(int)Bomb10], &tama_init.Height[(int)Bomb10]);
	GetGraphSize(tama_init.handle[(int)Bomb11], &tama_init.Width[(int)Bomb11], &tama_init.Height[(int)Bomb11]);
	GetGraphSize(tama_init.handle[(int)Delay], &tama_init.Width[(int)Delay], &tama_init.Height[(int)Delay]);
	GetGraphSize(tama_init.handle[(int)Ycha], &tama_init.Width[(int)Ycha], &tama_init.Height[(int)Ycha]);
	GetGraphSize(tama_init.handle[(int)Xcha], &tama_init.Width[(int)Xcha], &tama_init.Height[(int)Xcha]);

	GetGraphSize(tama_init.handle[(int)XchaLu], &tama_init.Width[(int)XchaLu], &tama_init.Height[(int)XchaLu]);
	GetGraphSize(tama_init.handle[(int)XchaLd], &tama_init.Width[(int)XchaLd], &tama_init.Height[(int)XchaLd]);
	GetGraphSize(tama_init.handle[(int)XchaRu], &tama_init.Width[(int)XchaRu], &tama_init.Height[(int)XchaRu]);
	GetGraphSize(tama_init.handle[(int)XchaRd], &tama_init.Width[(int)XchaRd], &tama_init.Height[(int)XchaRd]);

	GetGraphSize(tama_init.handle[(int)Tcha], &tama_init.Width[(int)Tcha], &tama_init.Height[(int)Tcha]);
	GetGraphSize(tama_init.handle[(int)Snipe], &tama_init.Width[(int)Snipe], &tama_init.Height[(int)Snipe]);
	GetGraphSize(tama_init.handle[(int)Stay], &tama_init.Width[(int)Stay], &tama_init.Height[(int)Stay]);

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
//##################プレイヤー表示の関数########################
VOID PLAYER_HYOUJI(VOID)
{
	if (DAMAGE != TRUE)//ダメージを食らっていないとき
	{
		DrawGraph(player.x, player.y, player.Handle, TRUE);
	}
}
//青い弾の爆発描画
VOID BLUE_BOMB(TAMA* t)
{
	//爆発の位置を計算
	int bakuX = t->x - t->Width[t->BombKind] / 2;
	int bakuY = t->y - t->Height[t->BombKind] / 2;

	//爆発の画像を描画

	if (t->x < 100)
	{
		DrawGraph(bakuX, bakuY, t->handle[t->BombKind], TRUE);

		//爆発のアニメーション処理
		if (t->BombCnt < t->BombCntMax)
		{
			t->BombCnt++;
		}
		else
		{
			t->BombCnt = 0;

			if (t->BombKind < t->BombKindMax)
			{
				t->BombKind++;	//次の爆発画像へ
			}
		}
	}
	else
	{
		DrawGraph(t->x, t->y - 3, t->handle[t->BombKind], TRUE); // x,y の位置にキャラを描画
	}

	return;
}
VOID DELAY(TAMA* t)
{
	if (t->PinkCnt == t->PinkCntMax)
	{
		t->Pinkdansoku = t->dansoku;//弾速を一時退避させて保管する
		t->dansoku = 0;//弾速をなくす
	}

	if (t->PinkCnt > 0)//カウントが０じゃないなら
	{
		DrawGraph(t->x, t->y - 3, t->handle[(int)Delay], TRUE); //弾を表示して
		t->PinkCnt--;//カウントを減らす
	}
	else//０になったら
	{
		t->dansoku = t->Pinkdansoku;//保管していた弾速を元に戻して弾を動かす
		DrawGraph(t->x, t->y - 3, t->handle[(int)Delay], TRUE);
	}
}
VOID YCHA(TAMA* t)
{

	if (t->x < 250)
	{
		DrawGraph(t->x, t->Ly, t->handle[(int)Ycha], TRUE); //弾を表示して
		t->Ly--;
		DrawGraph(t->x, t->Ry, t->handle[(int)Ycha], TRUE); //弾を表示して
		t->Ry++;
	}
	else
	{
		DrawGraph(t->x, t->y - 3, t->handle[(int)Ycha], TRUE); //弾を表示して
		t->Ly = t->y;
		t->Ry = t->y;
	}
}
VOID XCHA(TAMA* t)
{
	if (t->Same == TRUE)
	{
		DrawGraph(t->Lu, t->Ly, t->handle[(int)XchaLu], TRUE); //弾を表示して
		t->Lu++;
		DrawGraph(t->Ru, t->Ry, t->handle[(int)XchaRu], TRUE); //弾を表示して
		t->Ru++;
		DrawGraph(t->Ld, t->Ly, t->handle[(int)XchaLd], TRUE); //弾を表示して
		t->Ld--;
		DrawGraph(t->Rd, t->Ry, t->handle[(int)XchaLd], TRUE); //弾を表示して
		t->Rd--;

		t->Ly -= 2;
		t->Ry += 2;
	}
	else
	{
		DrawGraph(t->x, t->y - 3, t->handle[(int)XchaLu], TRUE); //弾を表示して
		DrawGraph(t->x, t->y - 3, t->handle[(int)XchaLd], TRUE); //弾を表示して
		DrawGraph(t->x, t->y - 3, t->handle[(int)XchaRu], TRUE); //弾を表示して
		DrawGraph(t->x, t->y - 3, t->handle[(int)XchaRd], TRUE); //弾を表示して

		if (t->x <= player_.x)
		{
			t->Same = TRUE;
		}
		if (t->Same == TRUE)
		{
			t->dansoku = 2;

			t->Lu = t->x;
			t->Ru = t->x;
			t->Ld = t->x;
			t->Rd = t->x;

			t->Ly = t->y;
			t->Ry = t->y;
		}
	}
}
VOID TCHA(TAMA* t)
{
	if (t->Same == TRUE)
	{
		DrawGraph(t->x, t->Ly, t->handle[(int)Tcha], TRUE); //弾を表示して
		t->Ly--;
		DrawGraph(t->x, t->Ry, t->handle[(int)Tcha], TRUE); //弾を表示して
		t->Ry++;
	}
	else
	{
		DrawGraph(t->x, t->y - 3, t->handle[(int)Tcha], TRUE); //弾を表示して
		if (t->x <= player_.x)
		{
			t->Same = TRUE;
		}
		if (t->Same == TRUE)
		{
			t->dansoku = 0;
			t->Ly = t->y;
			t->Ry = t->y;
		}
	}
}
VOID SNIPE(TAMA* t)
{
	if (t->Snipe == FALSE)
	{
		t->dansoku = 0;
		t->SnX = t->x - player_.x;
		t->SnY = t->y - player_.y;
		t->Snipe = TRUE;
	}
	else
	{
		DrawGraph(t->x, t->y, t->handle[(int)Snipe], TRUE); //弾を表示して
		t->x -= t->SnX / 50;
		t->y -= t->SnY / 50;
	}

}
VOID STAY(TAMA* t)
{
	if (t->Same == TRUE)
	{
		if (t->stay > 0)
		{
			DrawGraph(t->x, t->Ly, t->handle[(int)Stay], TRUE); //弾を表示して
			t->stay--;
		}
	}
	else
	{
		DrawGraph(t->x, t->y - 3, t->handle[(int)Stay], TRUE); //弾を表示して
		if (t->x <= player_.x)
		{
			t->Same = TRUE;
		}
		if (t->Same == TRUE)
		{
			t->dansoku = 0;
			t->Ly = t->y;
			t->Ry = t->y;
		}
	}

}
VOID TEST(TAMA* t)
{
	DrawGraph(t->x, t->y - 3, t->handle[(int)Test], TRUE); //弾を表示して

}
VOID BEAM(TAMA* t)
{

}
//押してる間必殺技を選ぶモードになるボタン
//あるボタンを押しながらスティックを傾けると前方180度に限り必殺技の向きを指定できる
//事前に方向を決めたのち必殺技撃つサッと指定して撃つことも
//ビームで敵の弾、敵味方両方の弾を消せても良いかも
//ifもしゲージがあるときにあるボタンを押したら・
//BOOL atarihantei(int )
//{
//	
//	
//}