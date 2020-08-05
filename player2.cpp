#define _CRT_SECURE_NO_WARNINGS

#include "DxLib.h"
#include "Header.h"
#include "player1.h"
#include "player2.h"

int Laser_dansuu_ = 15;
int Energy_dansuu_ = 30;
int Bomb1_dansuu_ = 5;//1で止めるためこれで5発 

int countC_;//リロードの時間格納用　５秒
int i_ = 0;//個別の弾用の数字
int shothoukou_ = 0;//弾の方向
int dansoku_ = 2;//初期弾速
int dansokumode_ = 0;//弾速の変更
int shotmode_ = 0;//弾の種類　初期弾種：０
int q_ = 0;

TAMA_ tama_init_;	//弾の画像読み込み・初期化のために使う変数
TAMA_ tama_[TAMA_MAX];//構造体の配列

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

PLAYER_ player_;//構造体の変数

//##################状態表示の関数*########################
VOID JOUTAI_HYOUJI_(VOID)
{
	DrawGraph(0, 30, lockon.Handle[(int)lockon1], TRUE);
	DrawGraph(0, 0, lockon.Handle[(int)lockon2], TRUE);
	DrawGraph(0, 72, lockon.Handle[(int)lockon3], TRUE);
	DrawRotaGraph(17, 123, 0.8, 0, lockon.Handle[(int)lockon1], TRUE);

	switch (shotmode_)
	{
	case 0:
		DrawRotaFormatString(16, 31, 1.0, 1.0, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Laser_dansuu_);
		DrawRotaFormatString(12, 5, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Energy_dansuu_);
		DrawRotaFormatString(13, 75, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bomb1_dansuu_);
		DrawRotaGraph(20, 50, 1.25, 4.0, tama_init_.handle[(int)Laser], TRUE);
		DrawRotaGraph(15, 15, 1.0, 4.0, tama_init_.handle[(int)Energy], TRUE);
		DrawRotaGraph(17, 87, 1.0, 4.0, tama_init_.handle[(int)Bomb1], TRUE);
		break;
	case 1:
		DrawRotaFormatString(13, 75, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Laser_dansuu_);
		DrawRotaFormatString(16, 31, 1.0, 1.0, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Energy_dansuu_);
		DrawRotaFormatString(12, 5, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bomb1_dansuu_);
		DrawRotaGraph(17, 87, 1.0, 4.0, tama_init_.handle[(int)Laser], TRUE);
		DrawRotaGraph(20, 50, 1.5, 4.0, tama_init_.handle[(int)Energy], TRUE);
		DrawRotaGraph(15, 15, 1.0, 4.0, tama_init_.handle[(int)Bomb1], TRUE);
		break;
	case 2:
		DrawRotaFormatString(12, 5, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Laser_dansuu_);
		DrawRotaFormatString(13, 75, 0.75, 0.75, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Energy_dansuu_);
		DrawRotaFormatString(16, 31, 1.0, 1.0, 1.0, 1.0, PI * 2, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE, "%d", Bomb1_dansuu_);
		DrawRotaGraph(15, 15, 1.0, 4.0, tama_init_.handle[(int)Laser], TRUE);
		DrawRotaGraph(17, 87, 1.0, 4.0, tama_init_.handle[(int)Energy], TRUE);
		DrawRotaGraph(20, 50, 1.25, 4.0, tama_init_.handle[(int)Bomb1], TRUE);
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
	//DrawFormatString(10, 60, GetColor(0, 255, 0), "通常弾:%d", Laser_dansuu_);//フレ＾ムカウント
	//DrawFormatString(10, 75, GetColor(0, 255, 0), "気弾:%d", Energy_dansuu_);//フレ＾ムカウント
	//DrawFormatString(10, 90, GetColor(0, 255, 0), "爆発弾:%d", Bomb1_dansuu_);//フレ＾ムカウント
	//DrawFormatString(10, 105, GetColor(0, 255, 0), "%d", q);//フレ＾ムカウント
	//DrawFormatString(10, 120, GetColor(0, 255, 0), "%d", DAMAGE);//フレ＾ムカウント
}
//##################弾数の関数*########################
VOID DANSUU_(VOID)//リロード中に撃っても弾を消費するだけで弾は出ないぞ！　←　これを利用して重ねリロードできるｿﾞ
{
	if (reload_ == TRUE)
	{
		tama_[i_].IsView = FALSE;
		if (countC_ < count && Laser_dansuu_ < 1)//5秒たったら
		{
			Laser_dansuu_ = 15;//弾数補充し
			reload_ = FALSE;//リロードを終了
			A_ = FALSE;
		}
		if (countC_ < count && Energy_dansuu_ < 1)//5秒たったら
		{
			Energy_dansuu_ = 30;//弾数補充し
			reload_ = FALSE;//リロードを終了
			B_ = FALSE;
		}
		if (countC_ < count && Bomb1_dansuu_ < 1)//5秒たったら
		{
			Bomb1_dansuu_ = 5;//弾数補充し
			reload_ = FALSE;//リロードを終了
			C_ = FALSE;
		}
	}
	if (Key[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_3) != 0)
	{
		if (RELOAD_ == FALSE)
		{
			RELOAD_ = TRUE;
			if (Laser_dansuu_ == 1 && shotmode_ == (int)Laser && A_ == FALSE)
			{
				A_ = TRUE;
				countC_ = count + 180;
				reload_ = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}
			if (Energy_dansuu_ == 1 && shotmode_ == (int)Energy && B_ == FALSE)
			{
				B_ = TRUE;
				countC_ = count + 180;
				reload_ = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}
			if (Bomb1_dansuu_ == 1 && shotmode_ == (int)Bomb1 && C_ == FALSE)
			{
				C_ = TRUE;
				countC_ = count + 180;
				reload_ = TRUE;
				PlaySoundMem(reload_sound, DX_PLAYTYPE_BACK, TRUE);
			}

			switch (shotmode_)
			{
			case (int)Laser:
				if (Laser_dansuu_ > 0)
				{
					Laser_dansuu_--;
				}
				break;
			case (int)Energy:
				if (Energy_dansuu_ > 0)
				{
					Energy_dansuu_--;
				}
				break;
			case (int)Bomb1:
				if (Bomb1_dansuu_ > 0)
				{
					Bomb1_dansuu_--;
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
//##################移動操作の関数*########################
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
//##################射撃関係の関数*########################
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
				case (int)Laser:
					PlaySoundMem(Laser_sound, DX_PLAYTYPE_BACK, TRUE);
					break;
				case (int)Energy:
					PlaySoundMem(Energy_sound, DX_PLAYTYPE_BACK, TRUE);
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
			case  (int)Laser:	//0
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
			case  (int)Energy:	//1
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
			case  (int)Bomb1:	//2
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

			if (shotmode_ > (int)Bomb1)
			{
				shotmode_ = (int)Laser;
			}

			switch (shotmode_)
			{
			case  (int)Laser:	//0
				break;
			case  (int)Energy:	//1
				break;
			case  (int)Bomb1:	//2
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

			if (shotmode_ < (int)Laser)
			{
				shotmode_ = (int)Bomb1;
			}

			switch (shotmode_)
			{
			case  (int)Laser:	//0
				break;
			case  (int)Energy:	//1
				break;
			case  (int)Bomb1:	//2
				break;
			}
		}
	}
	if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_7) == 0)
	{
		SHOTMODE_1_ = FALSE;
	}
}
//##################弾の挙動の関数*########################
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
			case (int)Laser:
				DrawGraph(tama_[cnt].x, tama_[cnt].y, tama_[cnt].handle[(int)Laser], TRUE); // レーザー			
				break;
			case (int)Energy:
				DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Energy], TRUE); // 気弾
				break;
			case (int)Bomb1:
				DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Bomb1], TRUE); // x,y の位置にキャラを描画
				break;
			}
			//弾を消すタイミング
			if (tama_[cnt].IsView == FALSE)//弾が消えたとき
			{
				if (tama_[cnt].shotmode == (int)Bomb1)	//爆発弾ならば
				{
					if (tama_[cnt].countB <= 11)//爆発エフェクト
					{
						switch (tama_[cnt].countB)
						{
						case 11:
							DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Bomb1], TRUE); // x,y の位置にキャラを描画
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
			case (int)Laser:
				rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Laser];
				rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Laser];
				break;
			case (int)Energy:
				rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Energy];
				rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Energy];
				break;
			case (int)Bomb1:
				//if (tama_[cnt].countB <= 11)//爆発エフェクト
				//{
				//	switch (tama_[cnt].countB)
				//	{
				//	case 11:
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb1];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb1];
				//		break;
				//	case 10:
				//		tama_[cnt].shotmode = (int)Bomb2;
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb2];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb2];
				//		break;
				//	case 9:
				//		tama_[cnt].shotmode = (int)Bomb3;
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb3];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb3];
				//		break;
				//	case 8:
				//		tama_[cnt].shotmode = (int)Bomb4;
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb4];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb4];
				//		break;
				//	case 7:
				//		tama_[cnt].shotmode = (int)Bomb5;
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb5];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb5];
				//		break;
				//	case 6:
				//		tama_[cnt].shotmode = (int)Bomb6;
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb6];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb6];
				//		break;
				//	case 5:
				//		tama_[cnt].shotmode = (int)Bomb7;
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb7];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb7];
				//		break;
				//	case 4:
				//		tama_[cnt].shotmode = (int)Bomb8;
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb8];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb8];
				//		break;
				//	case 3:
				//		tama_[cnt].shotmode = (int)Bomb9;
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb9];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb9];
				//		break;
				//	case 2:
				//		tama_[cnt].shotmode = (int)Bomb10;
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb10];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb10];
				//		break;
				//	case 1:
				//		tama_[cnt].shotmode = (int)Bomb11;
				//		rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Bomb11];
				//		rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Bomb11];
				//		break;
				//	}
				//}
				break;
			}
			if (ATARI_HANTEI_(rect_tama_, rect_player_) == TRUE)//弾とプレイヤーが重なったとき
			{
				switch (tama_[cnt].shotmode)
				{
				case  (int)Laser:	//0
					tama_[cnt].IsView = FALSE;
					player_.HP -= 10;
					break;
				case  (int)Energy:	//1
					tama_[cnt].IsView = FALSE;
					player_.HP -= 5;
					break;
				case  (int)Bomb1:	//2
					player_.HP -= 15;
					tama_[cnt].IsView = FALSE;

				//case (int)Bomb2:
				//	player_.HP -= 5;
				//case (int)Bomb3:
				//	player_.HP -= 5;
				//case (int)Bomb4:
				//	player_.HP -= 5;
				//case (int)Bomb5:
				//	player_.HP -= 5;
				//case (int)Bomb6:
				//	player_.HP -= 5;
				//case (int)Bomb7:
				//	player_.HP -= 5;
				//case (int)Bomb8:
				//	player_.HP -= 5;
				//case (int)Bomb9:
				//	player_.HP -= 5;
				//case (int)Bomb10:
				//	player_.HP -= 5;
				//case (int)Bomb11:
				//	player_.HP -= 5;
				//	tama_[cnt].IsView = FALSE;
				//	break;
				}
				if (ATARI_HANTEI_2(rect_tama, rect_player_) == TRUE)//弾とプレイヤーが重なったとき
				{
					switch (tama[cnt].shotmode)
					{
					case  (int)Laser:	//0
						tama[cnt].IsView = FALSE;
						player_.HP -= 10;
						break;
					case  (int)Energy:	//1
						tama[cnt].IsView = FALSE;
						player_.HP -= 5;
						break;
					case  (int)Bomb1:	//2
						player_.HP -= 15;
						tama[cnt].IsView = FALSE;

					//case (int)Bomb2:
					//	player_.HP -= 5;
					//case (int)Bomb3:
					//	player_.HP -= 5;
					//case (int)Bomb4:
					//	player_.HP -= 5;
					//case (int)Bomb5:
					//	player_.HP -= 5;
					//case (int)Bomb6:
					//	player_.HP -= 5;
					//case (int)Bomb7:
					//	player_.HP -= 5;
					//case (int)Bomb8:
					//	player_.HP -= 5;
					//case (int)Bomb9:
					//	player_.HP -= 5;
					//case (int)Bomb10:
					//	player_.HP -= 5;
					//case (int)Bomb11:
					//	player_.HP -= 5;
					//	tama[cnt].IsView = FALSE;
					//	break;
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
//##################画像読み込み関数*########################
VOID GAZOU_YOMIKOMI_(VOID)
{
	//####################画像読み込み#############################
	player_.Handle = LoadGraph("画像/キャラクタ02.png"); // プレイヤー画像のロード
	tama_init_.handle[(int)Laser] = LoadGraph("画像/赤レーザー.png");
	tama_init_.handle[(int)Energy] = LoadGraph("画像/赤強弾.png");
	//tama_init_.handle[(int)Redtama3] = LoadGraph("画像/赤三角弾.png");
	tama_init_.handle[(int)Bomb1] = LoadGraph("画像/青爆発/青爆発1.png");
	//tama_init_.handle[(int)Bomb2] = LoadGraph("画像/青爆発/青爆発2.png");
	//tama_init_.handle[(int)Bomb3] = LoadGraph("画像/青爆発/青爆発3.png");
	//tama_init_.handle[(int)Bomb4] = LoadGraph("画像/青爆発/青爆発4.png");
	//tama_init_.handle[(int)Bomb5] = LoadGraph("画像/青爆発/青爆発5.png");
	//tama_init_.handle[(int)Bomb6] = LoadGraph("画像/青爆発/青爆発6.png");
	//tama_init_.handle[(int)Bomb7] = LoadGraph("画像/青爆発/青爆発7.png");
	//tama_init_.handle[(int)Bomb8] = LoadGraph("画像/青爆発/青爆発8.png");
	//tama_init_.handle[(int)Bomb9] = LoadGraph("画像/青爆発/青爆発9.png");
	//tama_init_.handle[(int)Bomb10] = LoadGraph("画像/青爆発/青爆発10.png");
	//tama_init_.handle[(int)Bomb11] = LoadGraph("画像/青爆発/青爆発11.png");
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
	GetGraphSize(player_.Handle, &player_.Width, &player_.Height);
	GetGraphSize(tama_init_.handle[(int)Laser], &tama_init_.Width[(int)Laser], &tama_init_.Height[(int)Laser]);
	GetGraphSize(tama_init_.handle[(int)Energy], &tama_init_.Width[(int)Energy], &tama_init_.Height[(int)Energy]);
	//GetGraphSize(tama_init_.handle[(int)Redtama3], &tama_init_.Width[(int)Redtama3], &tama_init_.Height[(int)Redtama3]);
	GetGraphSize(tama_init_.handle[(int)Bomb1], &tama_init_.Width[(int)Bomb1], &tama_init_.Height[(int)Bomb1]);
	//GetGraphSize(tama_init_.handle[(int)Bomb2], &tama_init_.Width[(int)Bomb2], &tama_init_.Height[(int)Bomb2]);
	//GetGraphSize(tama_init_.handle[(int)Bomb3], &tama_init_.Width[(int)Bomb3], &tama_init_.Height[(int)Bomb3]);
	//GetGraphSize(tama_init_.handle[(int)Bomb4], &tama_init_.Width[(int)Bomb4], &tama_init_.Height[(int)Bomb4]);
	//GetGraphSize(tama_init_.handle[(int)Bomb5], &tama_init_.Width[(int)Bomb5], &tama_init_.Height[(int)Bomb5]);
	//GetGraphSize(tama_init_.handle[(int)Bomb6], &tama_init_.Width[(int)Bomb6], &tama_init_.Height[(int)Bomb6]);
	//GetGraphSize(tama_init_.handle[(int)Bomb7], &tama_init_.Width[(int)Bomb7], &tama_init_.Height[(int)Bomb7]);
	//GetGraphSize(tama_init_.handle[(int)Bomb8], &tama_init_.Width[(int)Bomb8], &tama_init_.Height[(int)Bomb8]);
	//GetGraphSize(tama_init_.handle[(int)Bomb9], &tama_init_.Width[(int)Bomb9], &tama_init_.Height[(int)Bomb9]);
	//GetGraphSize(tama_init_.handle[(int)Bomb10], &tama_init_.Width[(int)Bomb10], &tama_init_.Height[(int)Bomb10]);
	//GetGraphSize(tama_init_.handle[(int)Bomb11], &tama_init_.Width[(int)Bomb11], &tama_init_.Height[(int)Bomb11]);
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
//##################プレイヤー表示の関数*########################
VOID PLAYER_HYOUJI_(VOID)
{
	if (DAMAGE != TRUE)//ダメージを食らっていないとき
	{
		DrawGraph(player_.x, player_.y, player_.Handle, TRUE);
	}
}
//##################当たり判定の関数*########################
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

//青い弾の爆発描画
VOID BLUE_BOMB(TAMA_ *t)
{
	//爆発の位置を計算
	int bakuX = t->x - t->Width[t->BombKind] / 2;
	int bakuY = t->y - t->Height[t->BombKind] / 2;

	//爆発の画像を描画
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

	return;
}