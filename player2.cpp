#define _CRT_SECURE_NO_WARNINGS

#include "DxLib.h"
#include "Header.h"
#include "player1.h"
#include "player2.h"

int Laser_dansuu_ = 15;
int Energy_dansuu_ = 30;
int Bomb1_dansuu_ = 5;//1�Ŏ~�߂邽�߂����5�� 

int countC_;//�����[�h�̎��Ԋi�[�p�@�T�b
int i_ = 0;//�ʂ̒e�p�̐���
int shothoukou_ = 0;//�e�̕���
int dansoku_ = 2;//�����e��
int dansokumode_ = 0;//�e���̕ύX
int shotmode_ = 0;//�e�̎�ށ@�����e��F�O
int q_ = 0;

TAMA_ tama_init_;	//�e�̉摜�ǂݍ��݁E�������̂��߂Ɏg���ϐ�
TAMA_ tama_[TAMA_MAX];//�\���̂̔z��

BOOL A_ = FALSE;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�
BOOL B_ = FALSE;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�
BOOL C_ = FALSE;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�

BOOL SHOT_ = FALSE;//�p�b�h�̃{�^���A�ˑ΍�
BOOL HOUKOU_ = FALSE;//�p�b�h�̃{�^���A�ˑ΍�@�E
BOOL SHOTMODE_ = FALSE;//�p�b�h�̃{�^���A�ˑ΍�@�E
BOOL RELOAD_ = FALSE;//�p�b�h�{�^���A�ˑ΍�@�E
BOOL DANSOKU_ = FALSE;
BOOL HOUKOU_1_ = FALSE;//�p�b�h�̃{�^���A�ˑ΍�@��
BOOL SHOTMODE_1_ = FALSE;//�p�b�h�̃{�^���A�ˑ΍�@��

BOOL reload_ = FALSE;//�����[�h�����ۂ�
BOOL DAMAGE_ = FALSE;

BOOL ue_[256];//�e�e����[�ɓ����������ǂ���
BOOL sita_[256];//�e�e�����[�ɓ����������ǂ���

PLAYER_ player_;//�\���̂̕ϐ�

//##################��ԕ\���̊֐�*########################
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
		DrawGraph(5, 330 - ff, HP, TRUE);//HP�o�[
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
		DrawRotaFormatString(player_.x - 20, player_.y + 55, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "�����[�h��");
	}
	DrawRotaFormatString(620, 330, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "%s��", dansokuhyouji);

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
	//DrawRotaFormatString(300, 300, 1.0, 1.0, 1.0, 1.0, PI, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "�����[�h��");
	//DrawRotaFormatString(300,300, 1.0, 2.0, 0.0, 0.0, 1.0, GetColor(0, 255, 0), GetColor(0, 255, 255), TRUE, "�����[�h��");
	//DrawFormatString(600, 10, GetColor(0, 255, 0), "%s��", dansokuhyouji);//�e���\��
	//DrawFormatString(590, 25, GetColor(0, 255, 0), "%s����", houkouhyouji);//�e�̕����\��
	//DrawFormatString(590, 40, GetColor(0, 255, 0), "%s�e", modehyouji);//�e�̎�ޕ\��
	//DrawFormatString(100, 100, GetColor(0, 255, 0), "�Q�[�����");
	//DrawFormatString(10, 10, GetColor(0, 255, 0), "%d", count);//�t���O���J�E���g
	//DrawFormatString(10, 20, GetColor(0, 255, 0), "tama_W%d", tama_W);//�t���O���J�E���g
	//DrawFormatString(10, 30, GetColor(0, 255, 0), "tama_H%d", tama_H);//�t���O���J�E���g
	//DrawFormatString(10, 40, GetColor(0, 255, 0), "%d", i);//�t���O���J�E���g
	//DrawFormatString(10, 50, GetColor(0, 255, 0), "%d", player_.HP);//�t���O���J�E���g
	//DrawFormatString(10, 60, GetColor(0, 255, 0), "�ʏ�e:%d", Laser_dansuu_);//�t���O���J�E���g
	//DrawFormatString(10, 75, GetColor(0, 255, 0), "�C�e:%d", Energy_dansuu_);//�t���O���J�E���g
	//DrawFormatString(10, 90, GetColor(0, 255, 0), "�����e:%d", Bomb1_dansuu_);//�t���O���J�E���g
	//DrawFormatString(10, 105, GetColor(0, 255, 0), "%d", q);//�t���O���J�E���g
	//DrawFormatString(10, 120, GetColor(0, 255, 0), "%d", DAMAGE);//�t���O���J�E���g
}
//##################�e���̊֐�*########################
VOID DANSUU_(VOID)//�����[�h���Ɍ����Ă��e������邾���Œe�͏o�Ȃ����I�@���@����𗘗p���ďd�˃����[�h�ł����
{
	if (reload_ == TRUE)
	{
		tama_[i_].IsView = FALSE;
		if (countC_ < count && Laser_dansuu_ < 1)//5�b��������
		{
			Laser_dansuu_ = 15;//�e����[��
			reload_ = FALSE;//�����[�h���I��
			A_ = FALSE;
		}
		if (countC_ < count && Energy_dansuu_ < 1)//5�b��������
		{
			Energy_dansuu_ = 30;//�e����[��
			reload_ = FALSE;//�����[�h���I��
			B_ = FALSE;
		}
		if (countC_ < count && Bomb1_dansuu_ < 1)//5�b��������
		{
			Bomb1_dansuu_ = 5;//�e����[��
			reload_ = FALSE;//�����[�h���I��
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
//##################�ړ�����̊֐�*########################
VOID IDOU_SOUSA_(VOID)
{
	switch (reload_)
	{
	case 0://�ʏ펞
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_UP) != 0) { // �E�L�[��������Ă�����
			player_.x += 4;                       // �E�ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_RIGHT) != 0) { // ���L�[��������Ă�����
			player_.y += 4;                       // ���ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_DOWN) != 0) { // �� �L�[��������Ă�����
			player_.x -= 4;                       // ���ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_LEFT) != 0) { // ��L�[��������Ă�����
			player_.y -= 4;                       // ��ֈړ�
		}
	case 1://�����[�h���͈ړ����x����
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_UP) != 0) { // �E�L�[��������Ă�����
			player_.x += 2;                       // �E�ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_RIGHT) != 0) { // ���L�[��������Ă�����
			player_.y += 2;                       // ���ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_DOWN) != 0) { // �� �L�[��������Ă�����
			player_.x -= 2;                       // ���ֈړ�
		}
		if ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_LEFT) != 0) { // ��L�[��������Ă�����
			player_.y -= 2;                       // ��ֈړ�
		}
	}
	return;
}
//##################�ˌ��֌W�̊֐�*########################
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
	//����
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

	//�e��
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
					sprintf(dansokuhyouji, "��");
					break;
				case 1:
					dansoku_ = 6;
					sprintf(dansokuhyouji, "��");
					break;
				case 2:
					dansoku_ = 9;
					sprintf(dansokuhyouji, "��");
					break;
				}

				break;
			case  (int)Energy:	//1
				switch (dansokumode_)
				{
				case 0:
					dansoku_ = 1;
					sprintf(dansokuhyouji, "��");
					break;
				case 1:
					dansoku_ = 3;
					sprintf(dansokuhyouji, "��");
					break;
				case 2:
					dansoku_ = 5;
					sprintf(dansokuhyouji, "��");
					break;
				}

				break;
			case  (int)Bomb1:	//2
				switch (dansokumode_)
				{
				case 0:
					dansoku_ = 2;
					sprintf(dansokuhyouji, "��");
					break;
				case 1:
					dansoku_ = 4;
					sprintf(dansokuhyouji, "��");
					break;
				case 2:
					dansoku_ = 6;
					sprintf(dansokuhyouji, "��");
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
	//�e��
	if (Key[KEY_INPUT_F2] == 1 || ((GetJoypadInputState(DX_INPUT_PAD2) & PAD_INPUT_8) != 0))
	{
		if (SHOTMODE_ == FALSE)
		{
			SHOTMODE_ = TRUE;
			//�e�̎�ނ����ɂ���
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
			//�e�̎�ނ����ɂ���
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
//##################�e�̋����̊֐�*########################
VOID SHOT_KYODOU_(VOID)
{
	//####################�e�̋���###########################
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

				if (tama_[cnt].y <= 0)//��ʏ�[�ɂԂ���������
				{
					ue_[cnt] = TRUE;
				}

				if (ue_[cnt] == TRUE)
				{
					tama_[cnt].y += 2;//�e�̌������]
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
					sita_[cnt] = TRUE;//��ʉ��[�ɂԂ�������
				}

				if (sita_[cnt] == TRUE)
				{
					tama_[cnt].y -= 2;//�e�̌������]
				}
				else
				{
					tama_[cnt].y += 2;
				}
				break;
			}
			//####################�e�̎��###########################
			switch (tama_[cnt].shotmode)
			{
			case (int)Laser:
				DrawGraph(tama_[cnt].x, tama_[cnt].y, tama_[cnt].handle[(int)Laser], TRUE); // ���[�U�[			
				break;
			case (int)Energy:
				DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Energy], TRUE); // �C�e
				break;
			case (int)Bomb1:
				DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Bomb1], TRUE); // x,y �̈ʒu�ɃL������`��
				break;
			}
			//�e�������^�C�~���O
			if (tama_[cnt].IsView == FALSE)//�e���������Ƃ�
			{
				if (tama_[cnt].shotmode == (int)Bomb1)	//�����e�Ȃ��
				{
					if (tama_[cnt].countB <= 11)//�����G�t�F�N�g
					{
						switch (tama_[cnt].countB)
						{
						case 11:
							DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Bomb1], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						}
						tama_[cnt].countB--;
					}
					if (tama_[cnt].countB == 0)//�����G�t�F�N�g
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
		//######################�����蔻��###############################
		if (tama_[cnt].IsView == TRUE)
		{
			/*
			if (tama_[cnt].x < player_.x + player_.Width &&
				tama_[cnt].y < player_.y + player_.Height &&
				tama_[cnt].x + tama_W > player_.x &&
				tama_[cnt].y + tama_H > player_.y)
			{
			}*/
			RECT rect_tama;		//RECT�͎l�p�̍��A��A���A�����̍\����
			rect_tama.left = tama[cnt].x;
			rect_tama.top = tama[cnt].y;
			RECT rect_player;	//RECT�͎l�p�̍��A��A���A�����̍\����
			rect_player.left = player.x;
			rect_player.top = player.y;
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
				//if (tama_[cnt].countB <= 11)//�����G�t�F�N�g
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
			if (ATARI_HANTEI_(rect_tama_, rect_player_) == TRUE)//�e�ƃv���C���[���d�Ȃ����Ƃ�
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
				if (ATARI_HANTEI_2(rect_tama, rect_player_) == TRUE)//�e�ƃv���C���[���d�Ȃ����Ƃ�
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
						//�̗͂��O�Ȃ�΃G���h���
						mode = (int)scene_end;
						player_.HP = 100;
					}
				}
			}
		}
	}
}
//##################�摜�ǂݍ��݊֐�*########################
VOID GAZOU_YOMIKOMI_(VOID)
{
	//####################�摜�ǂݍ���#############################
	player_.Handle = LoadGraph("�摜/�L�����N�^02.png"); // �v���C���[�摜�̃��[�h
	tama_init_.handle[(int)Laser] = LoadGraph("�摜/�ԃ��[�U�[.png");
	tama_init_.handle[(int)Energy] = LoadGraph("�摜/�ԋ��e.png");
	//tama_init_.handle[(int)Redtama3] = LoadGraph("�摜/�ԎO�p�e.png");
	tama_init_.handle[(int)Bomb1] = LoadGraph("�摜/����/����1.png");
	//tama_init_.handle[(int)Bomb2] = LoadGraph("�摜/����/����2.png");
	//tama_init_.handle[(int)Bomb3] = LoadGraph("�摜/����/����3.png");
	//tama_init_.handle[(int)Bomb4] = LoadGraph("�摜/����/����4.png");
	//tama_init_.handle[(int)Bomb5] = LoadGraph("�摜/����/����5.png");
	//tama_init_.handle[(int)Bomb6] = LoadGraph("�摜/����/����6.png");
	//tama_init_.handle[(int)Bomb7] = LoadGraph("�摜/����/����7.png");
	//tama_init_.handle[(int)Bomb8] = LoadGraph("�摜/����/����8.png");
	//tama_init_.handle[(int)Bomb9] = LoadGraph("�摜/����/����9.png");
	//tama_init_.handle[(int)Bomb10] = LoadGraph("�摜/����/����10.png");
	//tama_init_.handle[(int)Bomb11] = LoadGraph("�摜/����/����11.png");
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
	//	GetGraphSize(lockon_.Handle[(int)lockon_1],&lockon_.Width[(int)lockon_1],&lockon_.Height[(int)lockon_1]);�����蔻��l���Ȃ����摜�T�C�Y���K�v�Ȃ�
	//  GetGraphSize(lockon_.Handle[(int)lockon_2], &lockon_.Width[(int)lockon_2], &lockon_.Height[(int)lockon_2]);
	//	GetGraphSize(lockon_.Handle[(int)lockon_3], &lockon_.Width[(int)lockon_3], &lockon_.Height[(int)lockon_3]);

		//�e�̏�����������ɁA�Q�T�U�̒e�ɏ����R�s�[
	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		tama_[cnt] = tama_init_;
	}
	//####################�����v���C���[�ʒu###########################
	player_.x = 220;
	player_.y = 240;
	return;
}
//##################�v���C���[�\���̊֐�*########################
VOID PLAYER_HYOUJI_(VOID)
{
	if (DAMAGE != TRUE)//�_���[�W��H����Ă��Ȃ��Ƃ�
	{
		DrawGraph(player_.x, player_.y, player_.Handle, TRUE);
	}
}
//##################�����蔻��̊֐�*########################
BOOL ATARI_HANTEI_(RECT tama_, RECT player_)//()�̒��͂��̍\���̂̕ϐ����g����A�I�� 
{
	if (tama_.left < player_.right &&
		tama_.top < player_.bottom &&
		tama_.right > player_.left &&
		tama_.bottom > player_.top)
	{
		return TRUE;
	}
	return FALSE;
}//BOOL�֐���VOID�Ƃ͎g���ǂ��낪�Ⴄ�݂���
BOOL ATARI_HANTEI_2(RECT tama, RECT player_)//()�̒��͂��̍\���̂̕ϐ����g����A�I�� 
{
	if (tama.left < player_.right &&
		tama.top < player_.bottom &&
		tama.right > player_.left &&
		tama.bottom > player_.top)
	{
		return TRUE;
	}
	return FALSE;
}//BOOL�֐���VOID�Ƃ͎g���ǂ��낪�Ⴄ�݂���

//���e�̔����`��
VOID BLUE_BOMB(TAMA_ *t)
{
	//�����̈ʒu���v�Z
	int bakuX = t->x - t->Width[t->BombKind] / 2;
	int bakuY = t->y - t->Height[t->BombKind] / 2;

	//�����̉摜��`��
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

	return;
}