#define _CRT_SECURE_NO_WARNINGS
//�e�̎�ނ���肫��
#include "DxLib.h"
#include "Header.h"
#include "player1.h"
#include "player2.h"

int Laser_dansuu = 15;
int Energy_dansuu = 30;
int Bomb1_dansuu = 5;//1�Ŏ~�߂邽�߂����5�� 

int countC;//�����[�h�̎��Ԋi�[�p�@�T�b
int i = 0;//�ʂ̒e�p�̐���
int shothoukou = 0;//�e�̕���
int dansoku = 2;//�����e��
int dansokumode = 0;//�e���̕ύX
int shotmode = 0;//�e�̎�ށ@�����e��F�O
int q = 0;
int cnt = 0;

TAMA tama_init;	//�e�̉摜�ǂݍ��݁E�������̂��߂Ɏg���ϐ�
TAMA tama[TAMA_MAX];//�\���̂̔z��

BOOL A = FALSE;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�
BOOL B = FALSE;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�
BOOL C = FALSE;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�

BOOL SHOT = FALSE;//�p�b�h�̃{�^���A�ˑ΍�
BOOL HOUKOU = FALSE;//�p�b�h�̃{�^���A�ˑ΍�@�E
BOOL SHOTMODE = FALSE;//�p�b�h�̃{�^���A�ˑ΍�@�E
BOOL RELOAD = FALSE;//�p�b�h�{�^���A�ˑ΍�@�E
BOOL DANSOKU = FALSE;
BOOL HOUKOU_1 = FALSE;//�p�b�h�̃{�^���A�ˑ΍�@��
BOOL SHOTMODE_1 = FALSE;//�p�b�h�̃{�^���A�ˑ΍�@��

BOOL reload = FALSE;//�����[�h�����ۂ�
BOOL DAMAGE = FALSE;

BOOL ue[256];//�e�e����[�ɓ����������ǂ���
BOOL sita[256];//�e�e�����[�ɓ����������ǂ���
PLAYER player;	//�\���̂̕ϐ�

//##################��ԕ\���̊֐�########################
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
		DrawGraph(620, 150 + ff, HP, TRUE);//HP�o�[
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
		DrawRotaFormatString(player.x - 20, player.y + 55, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "�����[�h��");
	}
	DrawRotaFormatString(620, 330, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "%s��", dansokuhyouji);

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
	//DrawRotaFormatString(300, 300, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "�����[�h��");
	//DrawRotaFormatString(300,300, 1.0, 2.0, 0.0, 0.0, 1.0, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "�����[�h��");
	//DrawFormatString(600, 10, GetColor(0, 255, 0), "%s��", dansokuhyouji);//�e���\��
	DrawFormatString(590, 25, GetColor(0, 255, 0), "%d", shotmode);//�e�̕����\��
	//DrawFormatString(590, 40, GetColor(0, 255, 0), "%s�e", modehyouji);//�e�̎�ޕ\��
	//DrawFormatString(100, 100, GetColor(0, 255, 0), "�Q�[�����");
	//DrawFormatString(10, 10, GetColor(0, 255, 0), "%d", count);//�t���O���J�E���g
	//DrawFormatString(10, 20, GetColor(0, 255, 0), "tamaW%d", tamaW);//�t���O���J�E���g
	//DrawFormatString(10, 30, GetColor(0, 255, 0), "tamaH%d", tamaH);//�t���O���J�E���g
	//DrawFormatString(10, 40, GetColor(0, 255, 0), "%d", i);//�t���O���J�E���g
	//DrawFormatString(10, 50, GetColor(0, 255, 0), "%d", player.HP);//�t���O���J�E���g
	//DrawFormatString(10, 60, GetColor(0, 255, 0), "�ʏ�e:%d", Laser_dansuu);//�t���O���J�E���g
	//DrawFormatString(10, 75, GetColor(0, 255, 0), "�C�e:%d", Energy_dansuu);//�t���O���J�E���g
	//DrawFormatString(10, 90, GetColor(0, 255, 0), "�����e:%d", Bomb1_dansuu);//�t���O���J�E���g
	//DrawFormatString(10, 105, GetColor(0, 255, 0), "%d", q);//�t���O���J�E���g
	//DrawFormatString(10, 120, GetColor(0, 255, 0), "%d", DAMAGE);//�t���O���J�E���g
}
//##################�e���̊֐�########################
VOID DANSUU(VOID)//�����[�h���Ɍ����Ă��e������邾���Œe�͏o�Ȃ����I�@���@����𗘗p���ďd�˃����[�h�ł����
{
	if (reload == TRUE)
	{
		tama[i].IsView = FALSE;
		if (countC < count && Laser_dansuu < 1)//5�b��������
		{
			Laser_dansuu = 15;//�e����[��
			reload = FALSE;//�����[�h���I��
			A = FALSE;
		}
		if (countC < count && Energy_dansuu < 1)//5�b��������
		{
			Energy_dansuu = 30;//�e����[��
			reload = FALSE;//�����[�h���I��
			B = FALSE;
		}
		if (countC < count && Bomb1_dansuu < 1)//5�b��������
		{
			Bomb1_dansuu = 5;//�e����[��
			reload = FALSE;//�����[�h���I��
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
//##################�ړ�����̊֐�########################
VOID IDOU_SOUSA(VOID)
{
	switch (reload)
	{
	case 0://�ʏ펞
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0 || Key[KEY_INPUT_DOWN] != 0) { // �E�L�[��������Ă�����
			player.x += 4;                       // �E�ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0 || Key[KEY_INPUT_LEFT] != 0) { // ���L�[��������Ă�����
			player.y += 4;                       // ���ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0 || Key[KEY_INPUT_UP] != 0) { // �� �L�[��������Ă�����
			player.x -= 4;                       // ���ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0 || Key[KEY_INPUT_RIGHT] != 0) { // ��L�[��������Ă�����
			player.y -= 4;                       // ��ֈړ�
		}
	case 1://�����[�h���͈ړ����x����
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0 || Key[KEY_INPUT_DOWN] != 0) { // �E�L�[��������Ă�����
			player.x += 2;                       // �E�ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0 || Key[KEY_INPUT_LEFT] != 0) { // ���L�[��������Ă�����
			player.y += 2;                       // ���ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0 || Key[KEY_INPUT_UP] != 0) { // �� �L�[��������Ă�����
			player.x -= 2;                       // ���ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0 || Key[KEY_INPUT_RIGHT] != 0) { // ��L�[��������Ă�����
			player.y -= 2;                       // ��ֈړ�
		}
	}
	return;
}
//##################�ˌ��֌W�̊֐�########################
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
			if (reload == TRUE)//�����[�h���͌����Ă��e�����邾���@�������ƕs������t����
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
	//����
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

	//�e��
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
					sprintf(dansokuhyouji, "��");
					break;
				case 1:
					dansoku = 6;
					sprintf(dansokuhyouji, "��");
					break;
				case 2:
					dansoku = 9;
					sprintf(dansokuhyouji, "��");
					break;
				}

				break;
			case  (int)Energy:	//1
				switch (dansokumode)
				{
				case 0:
					dansoku = 1;
					sprintf(dansokuhyouji, "��");
					break;
				case 1:
					dansoku = 3;
					sprintf(dansokuhyouji, "��");
					break;
				case 2:
					dansoku = 5;
					sprintf(dansokuhyouji, "��");
					break;
				}

				break;
			case  (int)Bomb1:	//2
				switch (dansokumode)
				{
				case 0:
					dansoku = 2;
					sprintf(dansokuhyouji, "��");
					break;
				case 1:
					dansoku = 4;
					sprintf(dansokuhyouji, "��");
					break;
				case 2:
					dansoku = 6;
					sprintf(dansokuhyouji, "��");
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
	//�e��
	if (Key[KEY_INPUT_F2] == 1 || ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0))
	{
		if (SHOTMODE == FALSE)
		{
			SHOTMODE = TRUE;
			//�e�̎�ނ����ɂ���
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
			//�e�̎�ނ����ɂ���
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
//##################�e�̋����̊֐�########################
VOID SHOT_KYODOU(VOID)
{
	//####################�e�̋���###########################
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

				if (tama[cnt].y <= 0)//��ʏ�[�ɂԂ���������
				{
					ue[cnt] = TRUE;
				}

				if (ue[cnt] == TRUE)
				{
					tama[cnt].y += 2;//�e�̌������]
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
					sita[cnt] = TRUE;//��ʉ��[�ɂԂ�������
				}

				if (sita[cnt] == TRUE)
				{
					tama[cnt].y -= 2;//�e�̌������]
				}
				else
				{
					tama[cnt].y += 2;
				}
				break;
			}
			//####################�e�̎��###########################

			switch (tama[cnt].shotmode)
			{
			case (int)Laser:
				DrawGraph(tama[cnt].x, tama[cnt].y, tama[cnt].handle[(int)Laser], TRUE); // ���[�U�[			
				break;
			case (int)Energy:
				DrawGraph(tama[cnt].x, tama[cnt].y - 3, tama[cnt].handle[(int)Energy], TRUE); // �C�e
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

			//�e�������^�C�~���O
			if (tama[cnt].x < 0 || tama[cnt].IsView == FALSE)
			{
				if (tama[cnt].shotmode >= (int)Bomb1)	//�����e�Ȃ��
				{
					if (tama[cnt].countB == 0)//�����G�t�F�N�g
					{
						tama[cnt].IsView = FALSE;
					}
				}
				else//�����e����Ȃ��Ȃ�
				{
					tama[cnt].IsView = FALSE;//�e������
				}
			}
		}
		//######################�����蔻��###############################
		if (tama[cnt].IsView == TRUE)
		{
			/*
			if (tama[cnt].x < player.x + player.Width &&
				tama[cnt].y < player.y + player.Height &&
				tama[cnt].x + tamaW > player.x &&
				tama[cnt].y + tamaH > player.y)
			{
			}*/
			RECT rect_tama;		//RECT�͎l�p�̍��A��A���A�����̍\����
			rect_tama.left = tama[cnt].x;
			rect_tama.top = tama[cnt].y;//�摜�̑傫���ɂ��A�T�C�Y�����ŕ���
			RECT rect_player;	//RECT�͎l�p�̍��A��A���A�����̍\����
			rect_player.left = player.x;
			rect_player.top = player.y;//�����蔻�菬��������Ƃ���x.y��+ width height ��-����B
			rect_player.right = player.x + player.Width;
			rect_player.bottom = player.y + player.Height;

			RECT rect_tama_;		//RECT�͎l�p�̍��A��A���A�����̍\����
			rect_tama_.left = tama_[cnt].x;
			rect_tama_.top = tama_[cnt].y;

			RECT rect_player_;	//RECT�͎l�p�̍��A��A���A�����̍\����
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

			//�����̒e�Ǝ��@���������Ƃ�
			/*
			if (ATARI_HANTEI(rect_tama, rect_player) == TRUE)//�e�ƃv���C���[���d�Ȃ����Ƃ�
			{

				//���������e���\���ɂ���
				//tama[cnt].IsView = FALSE;

				//HP�����炷
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

			//����̒e�Ǝ��@���������Ƃ�
			if (ATARI_HANTEI(rect_tama, rect_player_) == TRUE)//�A���_�[�o�[�t���ւ��Y����
			{
				//���������e���\���ɂ���
				tama[cnt].IsView = FALSE;

				//HP�����炷
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
				//�̗͂��O�Ȃ�΃G���h���
				mode = (int)scene_end;
				player.HP = 100;
			}

		}
	}
}

//##################�����蔻��̊֐�########################
BOOL ATARI_HANTEI(RECT tama_, RECT player)//()�̒��͂��̍\���̂̕ϐ����g����A�I�� 
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

//##################�摜�ǂݍ��݊֐�########################
VOID GAZOU_YOMIKOMI(VOID)
{
	//####################�摜�ǂݍ���#############################
	player.Handle = LoadGraph("�摜/�L�����N�^00.png"); // �v���C���[�摜�̃��[�h
	tama_init.handle[(int)Laser] = LoadGraph("�摜/�e/�ԃ��[�U�[.png");
	tama_init.handle[(int)Energy] = LoadGraph("�摜/�e/�ԋ��e.png");
	tama_init.handle[(int)Bomb1] = LoadGraph("�摜/����/����1.png");
	tama_init.handle[(int)Bomb2] = LoadGraph("�摜/����/����2.png");
	tama_init.handle[(int)Bomb3] = LoadGraph("�摜/����/����3.png");
	tama_init.handle[(int)Bomb4] = LoadGraph("�摜/����/����4.png");
	tama_init.handle[(int)Bomb5] = LoadGraph("�摜/����/����5.png");
	tama_init.handle[(int)Bomb6] = LoadGraph("�摜/����/����6.png");
	tama_init.handle[(int)Bomb7] = LoadGraph("�摜/����/����7.png");
	tama_init.handle[(int)Bomb8] = LoadGraph("�摜/����/����8.png");
	tama_init.handle[(int)Bomb9] = LoadGraph("�摜/����/����9.png");
	tama_init.handle[(int)Bomb10] = LoadGraph("�摜/����/����10.png");
	tama_init.handle[(int)Bomb11] = LoadGraph("�摜/����/����11.png");
	tama_init.handle[(int)Delay] = LoadGraph("�摜/�e/�����[�U�[.png");
	tama_init.handle[(int)Ycha] = LoadGraph("�摜/�e/�ԎO�p�e.png");
	tama_init.handle[(int)Xcha] = LoadGraph("�摜/�e/X�e.png");

	tama_init.handle[(int)XchaLu] = LoadGraph("�摜/�e/�ԎO�p�e.png");
	tama_init.handle[(int)XchaLd] = LoadGraph("�摜/�e/�ԎO�p�e.png");
	tama_init.handle[(int)XchaRu] = LoadGraph("�摜/�e/�ԎO�p�e.png");
	tama_init.handle[(int)XchaRd] = LoadGraph("�摜/�e/�ԎO�p�e.png");

	tama_init.handle[(int)Tcha] = LoadGraph("�摜/�e/�{�e.png");
	tama_init.handle[(int)Snipe] = LoadGraph("�摜/�e/Snipe�e.png");

	tama_init.handle[(int)Stay] = LoadGraph("�摜/�e/Stay�e.png");

	tama_init.handle[(int)Test] = LoadGraph("�摜/����/����11.png");

	lockon.Handle[(int)lockon1] = LoadGraph("�摜/���b�N�I��/���b�N�I��1.jpg");
	lockon.Handle[(int)lockon2] = LoadGraph("�摜/���b�N�I��/���b�N�I��2.jpg");
	lockon.Handle[(int)lockon3] = LoadGraph("�摜/���b�N�I��/���b�N�I��3.jpg");
	HP = LoadGraph("�摜/HP.png");
	yajirusi_2 = LoadGraph("�摜/���2.jpg");
	yajirusi_3 = LoadGraph("�摜/���3.jpg");
	Laser_sound = (LoadSoundMem("�摜/���ʉ�/���[�U�[.mp3"));
	Energy_sound = (LoadSoundMem("�摜/���ʉ�/�C�e.wav"));
	Bomb_sound = (LoadSoundMem("�摜/���ʉ�/�����e.wav"));
	reload_sound = (LoadSoundMem("�摜/���ʉ�/�����[�h.mp3"));
	//####################�摜�T�C�Y�擾###########################
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

	//	GetGraphSize(lockon.Handle[(int)lockon1],&lockon.Width[(int)lockon1],&lockon.Height[(int)lockon1]);�����蔻��l���Ȃ����摜�T�C�Y���K�v�Ȃ�
	//  GetGraphSize(lockon.Handle[(int)lockon2], &lockon.Width[(int)lockon2], &lockon.Height[(int)lockon2]);
	//	GetGraphSize(lockon.Handle[(int)lockon3], &lockon.Width[(int)lockon3], &lockon.Height[(int)lockon3]);

		//�e�̏�����������ɁA�Q�T�U�̒e�ɏ����R�s�[
	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		tama[cnt] = tama_init;
	}
	//####################�����v���C���[�ʒu###########################
	player.x = 320;
	player.y = 240;
	return;
}
//##################�v���C���[�\���̊֐�########################
VOID PLAYER_HYOUJI(VOID)
{
	if (DAMAGE != TRUE)//�_���[�W��H����Ă��Ȃ��Ƃ�
	{
		DrawGraph(player.x, player.y, player.Handle, TRUE);
	}
}
//���e�̔����`��
VOID BLUE_BOMB(TAMA* t)
{
	//�����̈ʒu���v�Z
	int bakuX = t->x - t->Width[t->BombKind] / 2;
	int bakuY = t->y - t->Height[t->BombKind] / 2;

	//�����̉摜��`��

	if (t->x < 100)
	{
		DrawGraph(bakuX, bakuY, t->handle[t->BombKind], TRUE);

		//�����̃A�j���[�V��������
		if (t->BombCnt < t->BombCntMax)
		{
			t->BombCnt++;
		}
		else
		{
			t->BombCnt = 0;

			if (t->BombKind < t->BombKindMax)
			{
				t->BombKind++;	//���̔����摜��
			}
		}
	}
	else
	{
		DrawGraph(t->x, t->y - 3, t->handle[t->BombKind], TRUE); // x,y �̈ʒu�ɃL������`��
	}

	return;
}
VOID DELAY(TAMA* t)
{
	if (t->PinkCnt == t->PinkCntMax)
	{
		t->Pinkdansoku = t->dansoku;//�e�����ꎞ�ޔ������ĕۊǂ���
		t->dansoku = 0;//�e�����Ȃ���
	}

	if (t->PinkCnt > 0)//�J�E���g���O����Ȃ��Ȃ�
	{
		DrawGraph(t->x, t->y - 3, t->handle[(int)Delay], TRUE); //�e��\������
		t->PinkCnt--;//�J�E���g�����炷
	}
	else//�O�ɂȂ�����
	{
		t->dansoku = t->Pinkdansoku;//�ۊǂ��Ă����e�������ɖ߂��Ēe�𓮂���
		DrawGraph(t->x, t->y - 3, t->handle[(int)Delay], TRUE);
	}
}
VOID YCHA(TAMA* t)
{

	if (t->x < 250)
	{
		DrawGraph(t->x, t->Ly, t->handle[(int)Ycha], TRUE); //�e��\������
		t->Ly--;
		DrawGraph(t->x, t->Ry, t->handle[(int)Ycha], TRUE); //�e��\������
		t->Ry++;
	}
	else
	{
		DrawGraph(t->x, t->y - 3, t->handle[(int)Ycha], TRUE); //�e��\������
		t->Ly = t->y;
		t->Ry = t->y;
	}
}
VOID XCHA(TAMA* t)
{
	if (t->Same == TRUE)
	{
		DrawGraph(t->Lu, t->Ly, t->handle[(int)XchaLu], TRUE); //�e��\������
		t->Lu++;
		DrawGraph(t->Ru, t->Ry, t->handle[(int)XchaRu], TRUE); //�e��\������
		t->Ru++;
		DrawGraph(t->Ld, t->Ly, t->handle[(int)XchaLd], TRUE); //�e��\������
		t->Ld--;
		DrawGraph(t->Rd, t->Ry, t->handle[(int)XchaLd], TRUE); //�e��\������
		t->Rd--;

		t->Ly -= 2;
		t->Ry += 2;
	}
	else
	{
		DrawGraph(t->x, t->y - 3, t->handle[(int)XchaLu], TRUE); //�e��\������
		DrawGraph(t->x, t->y - 3, t->handle[(int)XchaLd], TRUE); //�e��\������
		DrawGraph(t->x, t->y - 3, t->handle[(int)XchaRu], TRUE); //�e��\������
		DrawGraph(t->x, t->y - 3, t->handle[(int)XchaRd], TRUE); //�e��\������

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
		DrawGraph(t->x, t->Ly, t->handle[(int)Tcha], TRUE); //�e��\������
		t->Ly--;
		DrawGraph(t->x, t->Ry, t->handle[(int)Tcha], TRUE); //�e��\������
		t->Ry++;
	}
	else
	{
		DrawGraph(t->x, t->y - 3, t->handle[(int)Tcha], TRUE); //�e��\������
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
		DrawGraph(t->x, t->y, t->handle[(int)Snipe], TRUE); //�e��\������
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
			DrawGraph(t->x, t->Ly, t->handle[(int)Stay], TRUE); //�e��\������
			t->stay--;
		}
	}
	else
	{
		DrawGraph(t->x, t->y - 3, t->handle[(int)Stay], TRUE); //�e��\������
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
	DrawGraph(t->x, t->y - 3, t->handle[(int)Test], TRUE); //�e��\������

}
VOID BEAM(TAMA* t)
{

}
//�����Ă�ԕK�E�Z��I�ԃ��[�h�ɂȂ�{�^��
//����{�^���������Ȃ���X�e�B�b�N���X����ƑO��180�x�Ɍ���K�E�Z�̌������w��ł���
//���O�ɕ��������߂��̂��K�E�Z���T�b�Ǝw�肵�Č����Ƃ�
//�r�[���œG�̒e�A�G���������̒e�������Ă��ǂ�����
//if�����Q�[�W������Ƃ��ɂ���{�^������������E
//BOOL atarihantei(int )
//{
//	
//	
//}