#define  _CRT_SECURE_NO_WARNINGS

#include "DxLib.h"
#include <stdio.h>
#include "Header.h"
#include "player1.h"
#include "player2.h"

//#####################�o�����炢���ȃ��X�g#################################
//�܂��͏㉺�̂ݓ������鉡�X�y�[�X�C���x�[�_�[
//��Q���A���˂���e�A��莞�ԂƂǂ܂�e�A�e�������e�A���˕Ԃ��e
//�e�e�ł��؂����烊���[�h���A���b�e��[���A�P�����N�[���^�C�����I�ׂ�悤�ɂȂ��
//�����[�h���ړ����x�ቺ��_�������@�e����USF4�݂����ɕK�E�Z�Q�[�W�����܂�
//�̗͂ƒe�̈З́A�_�b�V���A�_�b�V���㎸��
//�e�̎�ނƂ͕ʂɓ����悤�ȓ������������V�[���h��ݒu���A�r�[���I�Ȃ̂�
//���݂̒e�A��ށA�N�[���^�C���𕪂���₷���\���A�ɂ�񂱑�푈�݂�����

//##########���݂̏�####################
//�e�̋����I��
//�搶�Ɋȗ�������ׂ��ꏊ�𕷂��@�@�@�����R�R�I
//�����蔻��ƃ_���[�W(�Ƃ��ɔ����e)&tamaH.tamaW�������
//���ꂼ��̒e����З͂̒���
//���Ƃ̂b�c,�e�̃A�C�R��

//�c��20�R�}(1/17���_)���܂�I���ɂ���Ă���ɂ͂Ȃ�
//���ڂł���Ƃ���͐��ڂ���
//�֐��ɂł���Ƃ���͊֐���(�����蔻��̂Ƃ�)�@
//�ΐ�^�ɂ��邽�߂̕����͂ǂ̂悤�ɂ��΂�����
//ALT+SHIFT���܂��g��
//�R�����g�A�E�g�Ŋe���A�e�l�̑�܂��Ȑ�����

//���ݑ����̕\���A�����ύX���̃A�C�R���ړ��͂ǂ����悤�ȁB���@��񂵂̕����ŁB�������Ȃ�
//���݂̎ˌ������ύX���́��\���A�e���̃A�C�R�����H�i�e���Ɋւ��Ă͖���

//�X�^�[�g��ʂł̃Q�[�����[�h�I��
//�V���O�����[�h�ǉ�
//�X�R�A�A�^�b�N


int Key[256]; // �L�[��������Ă���t���[�������i�[����

int HP;//HP�o�[�摜�i�[�p�n���h��
int yajirusi_2;//���@�O�������摜�i�[�p�n���h��
int yajirusi_3;//��ԕ\���������摜�i�[�p�n���h��

int Redtama1_sound;
int Redtama2_sound;
int Bluebomb_sound;
int reload_sound;

int Pad1;        //�W���C�p�b�h�̓��͏�Ԋi�[�p�ϐ�
int Pad2;        //�W���C�p�b�h�̓��͏�Ԋi�[�p�ϐ�

//�ϐ��̐錾
int mode = (int)scene_start;//��ʑJ��
int count = 0;//���t���[��

char dansokuhyouji[3] = "��";//��ʂɒᒆ������\�����邽�߂� �����e���F��

//char modehyouji[5] = "�ʏ�";
//char houkouhyouji[3] = "��";//��ʂɕ�����\�����邽�߂́@���������F��

//##################���������������������������������������������畡������������������������������������������########################
//##################�����������������������������������������܂ŕ�������������������������������������������########################

//�L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	//�摜�̓ǂݍ���
	GAZOU_YOMIKOMI();
	GAZOU_YOMIKOMI_();

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �L�[�̏�ԍX�V)
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
	DxLib_End(); // DX���C�u�����I������
	return 0;
}
//##################�X�^�[�g��ʂ̊֐�########################
VOID START_GAMEN(VOID)
{
	PAD_SOUSA();
	DrawFormatString(100, 100, GetColor(0, 255, 0), "�X�^�[�g���");
	DrawFormatString(250, 250, GetColor(0, 255, 255), "PUSH TO ENTER");

	if (Key[KEY_INPUT_RETURN] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0)//�G���^�[�L�[
	{
		mode = (int)scene_ready;
	}
}
VOID READY_GAMEN(VOID)
{
	DrawFormatString(100, 100, GetColor(0, 255, 0), "�������");
	if (Key[KEY_INPUT_RETURN] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0)//�G���^�[�L�[
	{
		mode = (int)scene_game;
	}
}

//##################�Q�[����ʂ̊֐�########################
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

	if (Key[KEY_INPUT_RETURN] == 1)//�G���^�[�L�[
	{
		mode = (int)scene_end;
	}
}
//##################�G���h��ʂ̊֐�########################
VOID END_GAMEN(VOID)
{
	DrawFormatString(100, 100, GetColor(0, 255, 0), "�G���h���");
	if (Key[KEY_INPUT_RETURN] == 1)
	{
		mode = (int)scene_start;
	}
}
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
	//DrawFormatString(590, 25, GetColor(0, 255, 0), "%s����", houkouhyouji);//�e�̕����\��
	//DrawFormatString(590, 40, GetColor(0, 255, 0), "%s�e", modehyouji);//�e�̎�ޕ\��
	//DrawFormatString(100, 100, GetColor(0, 255, 0), "�Q�[�����");
	//DrawFormatString(10, 10, GetColor(0, 255, 0), "%d", count);//�t���O���J�E���g
	//DrawFormatString(10, 20, GetColor(0, 255, 0), "tamaW%d", tamaW);//�t���O���J�E���g
	//DrawFormatString(10, 30, GetColor(0, 255, 0), "tamaH%d", tamaH);//�t���O���J�E���g
	//DrawFormatString(10, 40, GetColor(0, 255, 0), "%d", i);//�t���O���J�E���g
	//DrawFormatString(10, 50, GetColor(0, 255, 0), "%d", player.HP);//�t���O���J�E���g
	//DrawFormatString(10, 60, GetColor(0, 255, 0), "�ʏ�e:%d", Redtama1_dansuu);//�t���O���J�E���g
	//DrawFormatString(10, 75, GetColor(0, 255, 0), "�C�e:%d", Redtama2_dansuu);//�t���O���J�E���g
	//DrawFormatString(10, 90, GetColor(0, 255, 0), "�����e:%d", Bluebomb1_dansuu);//�t���O���J�E���g
	//DrawFormatString(10, 105, GetColor(0, 255, 0), "%d", q);//�t���O���J�E���g
	//DrawFormatString(10, 120, GetColor(0, 255, 0), "%d", DAMAGE);//�t���O���J�E���g
}
//##################�e���̊֐�########################
VOID DANSUU(VOID)//�����[�h���Ɍ����Ă��e������邾���Œe�͏o�Ȃ����I�@���@����𗘗p���ďd�˃����[�h�ł����
{
	if (reload == TRUE)
	{

		tama[i].IsView = FALSE;
		if (countC < count && Redtama1_dansuu < 1)//5�b��������
		{
			Redtama1_dansuu = 15;//�e����[��
			reload = FALSE;//�����[�h���I��
			A = FALSE;
		}
		if (countC < count && Redtama2_dansuu < 1)//5�b��������
		{
			Redtama2_dansuu = 30;//�e����[��
			reload = FALSE;//�����[�h���I��
			B = FALSE;
		}
		if (countC < count && Bluebomb1_dansuu < 1)//5�b��������
		{
			Bluebomb1_dansuu = 5;//�e����[��
			reload = FALSE;//�����[�h���I��
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
//##################�ړ�����̊֐�########################
VOID IDOU_SOUSA(VOID)
{
	switch (reload)
	{
	case 0://�ʏ펞
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0 || Key[KEY_INPUT_DOWN] !=0) { // �E�L�[��������Ă�����
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
			case  (int)Redtama1:	//0
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
			case  (int)Redtama2:	//1
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
			case  (int)Bluebomb1:	//2
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
			//�e�̎�ނ����ɂ���
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
//##################�e�̋����̊֐�########################
VOID SHOT_KYODOU(VOID)
{
	//####################�e�̋���###########################
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

			int bomb = 2;
			switch (tama[cnt].shotmode)
			{
			case (int)Redtama1:
				DrawGraph(tama[cnt].x, tama[cnt].y, tama[cnt].handle[(int)Redtama1], TRUE); // ���[�U�[			
				break;
			case (int)Redtama2:
				DrawGraph(tama[cnt].x, tama[cnt].y - 3, tama[cnt].handle[(int)Redtama2], TRUE); // �C�e
				break;
			case (int)Bluebomb1:
				
				if (tama[cnt].x < 100)
				{
						DrawGraph(tama[cnt].x, tama[cnt].y - 3, tama[cnt].handle[bomb], TRUE); // x,y �̈ʒu�ɃL������`��

						bomb++;
				}
				else
				{
					DrawGraph(tama[cnt].x, tama[cnt].y - 3, tama[cnt].handle[bomb], TRUE); // x,y �̈ʒu�ɃL������`��
				}
			}
			//�e�������^�C�~���O
			if (tama[cnt].x < 0 || tama[cnt].IsView == FALSE)
			{
				if (tama[cnt].shotmode >= (int)Bluebomb1)	//�����e�Ȃ��
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
				if (tama[cnt].countB <= 11)//�����G�t�F�N�g
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

			if (ATARI_HANTEI(rect_tama, rect_player) == TRUE)//�e�ƃv���C���[���d�Ȃ����Ƃ�
			{
				if (q < 100)//�_�ł�������
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
				if (ATARI_HANTEI2(rect_tama_, rect_player) == TRUE)//�e�ƃv���C���[���d�Ȃ����Ƃ�
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
						//�̗͂��O�Ȃ�΃G���h���
						mode = (int)scene_end;
						player.HP = 100;
					}
				}
			}
		}
	}
}
//##################�摜�ǂݍ��݊֐�########################
VOID GAZOU_YOMIKOMI(VOID)
{
	//####################�摜�ǂݍ���#############################
	player.Handle = LoadGraph("�摜/�L�����N�^00.png"); // �v���C���[�摜�̃��[�h
	tama_init.handle[(int)Redtama1] = LoadGraph("�摜/�ԃ��[�U�[.png");
	tama_init.handle[(int)Redtama2] = LoadGraph("�摜/�ԋ��e.png");
	tama_init.handle[(int)Redtama3] = LoadGraph("�摜/�ԎO�p�e.png");
	tama_init.handle[(int)Bluebomb1] = LoadGraph("�摜/����/����1.png");
	tama_init.handle[(int)Bluebomb2] = LoadGraph("�摜/����/����2.png");
	tama_init.handle[(int)Bluebomb3] = LoadGraph("�摜/����/����3.png");
	tama_init.handle[(int)Bluebomb4] = LoadGraph("�摜/����/����4.png");
	tama_init.handle[(int)Bluebomb5] = LoadGraph("�摜/����/����5.png");
	tama_init.handle[(int)Bluebomb6] = LoadGraph("�摜/����/����6.png");
	tama_init.handle[(int)Bluebomb7] = LoadGraph("�摜/����/����7.png");
	tama_init.handle[(int)Bluebomb8] = LoadGraph("�摜/����/����8.png");
	tama_init.handle[(int)Bluebomb9] = LoadGraph("�摜/����/����9.png");
	tama_init.handle[(int)Bluebomb10] = LoadGraph("�摜/����/����10.png");
	tama_init.handle[(int)Bluebomb11] = LoadGraph("�摜/����/����11.png");
	lockon.Handle[(int)lockon1] = LoadGraph("�摜/���b�N�I��/���b�N�I��1.jpg");
	lockon.Handle[(int)lockon2] = LoadGraph("�摜/���b�N�I��/���b�N�I��2.jpg");
	lockon.Handle[(int)lockon3] = LoadGraph("�摜/���b�N�I��/���b�N�I��3.jpg");
	HP = LoadGraph("�摜/HP.png");
	yajirusi_2 = LoadGraph("�摜/���2.jpg");
	yajirusi_3 = LoadGraph("�摜/���3.jpg");
	Redtama1_sound = (LoadSoundMem("�摜/���ʉ�/���[�U�[.mp3"));
	Redtama2_sound = (LoadSoundMem("�摜/���ʉ�/�C�e.wav"));
	Bluebomb_sound = (LoadSoundMem("�摜/���ʉ�/�����e.wav"));
	reload_sound = (LoadSoundMem("�摜/���ʉ�/�����[�h.mp3"));
	//####################�摜�T�C�Y�擾###########################
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
VOID PLAYER_HYOUJI(VOID)
{
	if (DAMAGE != TRUE)//�_���[�W��H����Ă��Ȃ��Ƃ�
	{
		DrawGraph(player.x, player.y, player.Handle, TRUE);
	}
}
VOID PAD_SOUSA(VOID)
{
	Pad1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //���͏�Ԃ�Pad�Ɋi�[
	for (int i = 0; i < 28; i++)
	{      //�{�^��28�����[�v
		if (Pad1 & (1 << i))
		{             //�{�^��i�̓��̓t���O�������Ă�����
			DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%d�̃L�[��������Ă��܂�", i);
		}
	}
	Pad2 = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //���͏�Ԃ�Pad�Ɋi�[
	for (int i = 0; i < 28; i++)
	{      //�{�^��28�����[�v
		if (Pad2 & (1 << i))
		{             //�{�^��i�̓��̓t���O�������Ă�����
			DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%d�̃L�[��������Ă��܂�", i);
		}
	}
}
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################���������������������������������������������畡������������������������������������������########################
//##################��ԕ\���̊֐�########################
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
	//DrawFormatString(10, 60, GetColor(0, 255, 0), "�ʏ�e:%d", Redtama1_dansuu_);//�t���O���J�E���g
	//DrawFormatString(10, 75, GetColor(0, 255, 0), "�C�e:%d", Redtama2_dansuu_);//�t���O���J�E���g
	//DrawFormatString(10, 90, GetColor(0, 255, 0), "�����e:%d", Bluebomb1_dansuu_);//�t���O���J�E���g
	//DrawFormatString(10, 105, GetColor(0, 255, 0), "%d", q);//�t���O���J�E���g
	//DrawFormatString(10, 120, GetColor(0, 255, 0), "%d", DAMAGE);//�t���O���J�E���g
}
//##################�e���̊֐�########################
VOID DANSUU_(VOID)//�����[�h���Ɍ����Ă��e������邾���Œe�͏o�Ȃ����I�@���@����𗘗p���ďd�˃����[�h�ł����
{
	if (reload_ == TRUE)
	{
		tama_[i_].IsView = FALSE;
		if (countC_ < count && Redtama1_dansuu_ < 1)//5�b��������
		{
			Redtama1_dansuu_ = 15;//�e����[��
			reload_ = FALSE;//�����[�h���I��
			A_ = FALSE;
		}
		if (countC_ < count && Redtama2_dansuu_ < 1)//5�b��������
		{
			Redtama2_dansuu_ = 30;//�e����[��
			reload_ = FALSE;//�����[�h���I��
			B_ = FALSE;
		}
		if (countC_ < count && Bluebomb1_dansuu_ < 1)//5�b��������
		{
			Bluebomb1_dansuu_ = 5;//�e����[��
			reload_ = FALSE;//�����[�h���I��
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


//##################�ړ�����̊֐�########################
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
//##################�ˌ��֌W�̊֐�########################
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
			case  (int)Redtama1:	//0
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
			case  (int)Redtama2:	//1
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
			case  (int)Bluebomb1:	//2
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
			//�e�̎�ނ����ɂ���
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
//##################�e�̋����̊֐�########################
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
			case (int)Redtama1:
				DrawGraph(tama_[cnt].x, tama_[cnt].y, tama_[cnt].handle[(int)Redtama1], TRUE); // ���[�U�[			
				break;
			case (int)Redtama2:
				DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Redtama2], TRUE); // �C�e
				break;
			case (int)Bluebomb1:
				DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Bluebomb1], TRUE); // x,y �̈ʒu�ɃL������`��
				break;
			}
			//�e�������^�C�~���O
			if (tama_[cnt].IsView == FALSE)//�e���������Ƃ�
			{
				if (tama_[cnt].shotmode == (int)Bluebomb1)	//�����e�Ȃ��
				{
					if (tama_[cnt].countB <= 11)//�����G�t�F�N�g
					{
						switch (tama_[cnt].countB)
						{
						case 11:
							DrawGraph(tama_[cnt].x, tama_[cnt].y - 3, tama_[cnt].handle[(int)Bluebomb1], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						case 10:
							DrawGraph(tama_[cnt].x - 2, tama_[cnt].y - 5, tama_[cnt].handle[(int)Bluebomb2], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						case 9:
							DrawGraph(tama_[cnt].x - 2, tama_[cnt].y - 3, tama_[cnt].handle[(int)Bluebomb3], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						case 8:
							DrawGraph(tama_[cnt].x + 1, tama_[cnt].y - 2, tama_[cnt].handle[(int)Bluebomb4], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						case 7:
							DrawGraph(tama_[cnt].x - 2, tama_[cnt].y - 5, tama_[cnt].handle[(int)Bluebomb5], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						case 6:
							DrawGraph(tama_[cnt].x - 4, tama_[cnt].y - 7, tama_[cnt].handle[(int)Bluebomb6], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						case 5:
							DrawGraph(tama_[cnt].x - 8, tama_[cnt].y - 11, tama_[cnt].handle[(int)Bluebomb7], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						case 4:
							DrawGraph(tama_[cnt].x - 13, tama_[cnt].y - 15, tama_[cnt].handle[(int)Bluebomb8], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						case 3:
							DrawGraph(tama_[cnt].x - 19, tama_[cnt].y - 21, tama_[cnt].handle[(int)Bluebomb9], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						case 2:
							DrawGraph(tama_[cnt].x - 25, tama_[cnt].y - 26.5, tama_[cnt].handle[(int)Bluebomb10], TRUE); // x,y �̈ʒu�ɃL������`��
							break;
						case 1:
							DrawGraph(tama_[cnt].x - 30, tama_[cnt].y - 32, tama_[cnt].handle[(int)Bluebomb11], TRUE); // x,y �̈ʒu�ɃL������`��
							PlaySoundMem(Bluebomb_sound, DX_PLAYTYPE_BACK, TRUE);
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
			case (int)Redtama1:
				rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Redtama1];
				rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Redtama1];
				break;
			case (int)Redtama2:
				rect_tama_.right = tama_[cnt].x + tama_[cnt].Width[(int)Redtama2];
				rect_tama_.bottom = tama_[cnt].y + tama_[cnt].Height[(int)Redtama2];
				break;
			case (int)Bluebomb1:
				if (tama_[cnt].countB <= 11)//�����G�t�F�N�g
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
			if (ATARI_HANTEI_(rect_tama_, rect_player_) == TRUE)//�e�ƃv���C���[���d�Ȃ����Ƃ�
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
				if (ATARI_HANTEI_2(rect_tama, rect_player_) == TRUE)//�e�ƃv���C���[���d�Ȃ����Ƃ�
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
						//�̗͂��O�Ȃ�΃G���h���
						mode = (int)scene_end;
						player_.HP = 100;
					}
				}
			}
		}
	}
}
//##################�摜�ǂݍ��݊֐�########################
VOID GAZOU_YOMIKOMI_(VOID)
{
	//####################�摜�ǂݍ���#############################
	player_.Handle = LoadGraph("�摜/�L�����N�^02.png"); // �v���C���[�摜�̃��[�h
	tama_init_.handle[(int)Redtama1] = LoadGraph("�摜/�ԃ��[�U�[.png");
	tama_init_.handle[(int)Redtama2] = LoadGraph("�摜/�ԋ��e.png");
	tama_init_.handle[(int)Redtama3] = LoadGraph("�摜/�ԎO�p�e.png");
	tama_init_.handle[(int)Bluebomb1] = LoadGraph("�摜/����/����1.png");
	tama_init_.handle[(int)Bluebomb2] = LoadGraph("�摜/����/����2.png");
	tama_init_.handle[(int)Bluebomb3] = LoadGraph("�摜/����/����3.png");
	tama_init_.handle[(int)Bluebomb4] = LoadGraph("�摜/����/����4.png");
	tama_init_.handle[(int)Bluebomb5] = LoadGraph("�摜/����/����5.png");
	tama_init_.handle[(int)Bluebomb6] = LoadGraph("�摜/����/����6.png");
	tama_init_.handle[(int)Bluebomb7] = LoadGraph("�摜/����/����7.png");
	tama_init_.handle[(int)Bluebomb8] = LoadGraph("�摜/����/����8.png");
	tama_init_.handle[(int)Bluebomb9] = LoadGraph("�摜/����/����9.png");
	tama_init_.handle[(int)Bluebomb10] = LoadGraph("�摜/����/����10.png");
	tama_init_.handle[(int)Bluebomb11] = LoadGraph("�摜/����/����11.png");
	lockon.Handle[(int)lockon1] = LoadGraph("�摜/���b�N�I��/���b�N�I��1.jpg");
	lockon.Handle[(int)lockon2] = LoadGraph("�摜/���b�N�I��/���b�N�I��2.jpg");
	lockon.Handle[(int)lockon3] = LoadGraph("�摜/���b�N�I��/���b�N�I��3.jpg");
	HP = LoadGraph("�摜/HP.png");
	yajirusi_2 = LoadGraph("�摜/���2.jpg");
	yajirusi_3 = LoadGraph("�摜/���3.jpg");
	Redtama1_sound = (LoadSoundMem("�摜/���ʉ�/���[�U�[.mp3"));
	Redtama2_sound = (LoadSoundMem("�摜/���ʉ�/�C�e.wav"));
	Bluebomb_sound = (LoadSoundMem("�摜/���ʉ�/�����e.wav"));
	reload_sound = (LoadSoundMem("�摜/���ʉ�/�����[�h.mp3"));
	//####################�摜�T�C�Y�擾###########################
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

//##################�����蔻��̊֐�########################
BOOL ATARI_HANTEI(RECT tama, RECT player)//()�̒��͂��̍\���̂̕ϐ����g����A�I�� 
{
	if (tama.left < player.right &&
		tama.top < player.bottom &&
		tama.right > player.left &&
		tama.bottom > player.top)
	{
		return TRUE;
	}
	return FALSE;
}//BOOL�֐���VOID�Ƃ͎g���ǂ��낪�Ⴄ�݂���
BOOL ATARI_HANTEI2(RECT tama_, RECT player)//()�̒��͂��̍\���̂̕ϐ����g����A�I�� 
{
	if (tama_.left < player.right &&
		tama_.top < player.bottom &&
		tama_.right > player.left &&
		tama_.bottom > player.top)
	{
		return TRUE;
	}
	return FALSE;
}//BOOL�֐���VOID�Ƃ͎g���ǂ��낪�Ⴄ�݂���
//##################�����蔻��̊֐�########################
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

VOID PLAYER_HYOUJI_(VOID)
{
	if (DAMAGE != TRUE)//�_���[�W��H����Ă��Ȃ��Ƃ�
	{
		DrawGraph(player_.x, player_.y, player_.Handle, TRUE);
	}
}
