#define _CRT_SECURE_NO_WARNINGS

#include "DxLib.h"
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
//�֐��ɂł���Ƃ���͊֐���(�����蔻��̂Ƃ�)�@
//�֐��ɂł���Ƃ���͊֐���(�����蔻��̂Ƃ�)�@
//�֐��ɂł���Ƃ���͊֐���(�����蔻��̂Ƃ�)�@
//�ΐ�^�ɂ��邽�߂̕����͂ǂ̂悤�ɂ��΂�����
//ALT+SHIFT���܂��g��
//�R�����g�A�E�g�Ŋe���A�e�l�̑�܂��Ȑ�����

//���ݑ����̕\���A�����ύX���̃A�C�R���ړ��͂ǂ����悤�ȁB���@��񂵂̕����ŁB�������Ȃ�
//���݂̎ˌ������ύX���́��\���A�e���̃A�C�R�����H�i�e���Ɋւ��Ă͖���

//�ʈ�
//��u���˒n�_�ɗ��܂�x��Ĕ��˂���e
//�G��y���ɓ��B����Ɛ^�����y�􂷂�T���̂悤�ȋ�
//�G��y���ɓ��B������y�􂷂鎞�@�O����X�̂悤�Ȓe
//�G�ւ܂��������ł������@�_���e
//�������y���ɓ��B������y�􂷂�Y���^�̒e
//�������u�Ԃ̓G��y���ɓ��B����Ƃ��̏�Ɉ�莞�ԗ��܂�e
//��u�\�������o�Ē���Ɉ�u�ŕ������r�[��

//�e�͂��ׂĎg����ł��������H
//�R���g���[���̂���{�^���{���X�e�B�b�N��10�̒e���g��������݂����ȁiMHW��APEX�̃V���[�g�J�b�g�݂����ȁj

//�K�E�Z��
//�K�E�Z�Q�[�W�͉���200�ɂ���
//�K�E�Z���ƂɕK�v�Q�[�W�ʂ��ω�
//���߂Ă����ΒZ�����Ԃŕ����̕K�E�Z���g����A�K�E�Z�̑g�ݍ��킹�Ȃ񂩂�
//���˂̓n�C���X�N�n�C���^�[���ɂ������̂ň�u�����K�E�Z�����˕Ԃ��݂�����
//���̃n�C���X�N�n�C���^�[���͒�R�X�g�ō��R�X�g��������y���˃^�C�v������
//��莞�Ԕ��肪�c�鑾�߂̃r�[���A�R�X�g�ƈЗ͂Ƒ�����}�����o�[�W�������r�[���̓���A��
//�����З́A���߂̋ɑ�R�X�g�Z

//�e�𑝂₷�ɂ������ė񋓌^�̏��Ԃ�ς��˂΂Ȃ�Ȃ����O����̒e���ƂɈ�I��
//�e�̊֐����G�Ȃ̂�
//shotmode������Ƃ��傫����蒼���ׂ������@10�̒e�𓯎��Ɏg���Ă̕��j��

//���ň�x�擾�����摜�T�C�Y��������x�ʂ̕ϐ��œ����摜�̃T�C�Y���擾����Ƃ��������Ȃ�H

//�����̒e�Ɏ����œ�����Ȃ��悤�ɂ���
//�����̒e���B���e�N�j�b�N,�����B���΂��̕����X�N���オ��

LOCKON lockon;

int Key[256]; // �L�[��������Ă���t���[�������i�[����

int HP;//HP�o�[�摜�i�[�p�n���h��
int yajirusi_2;//���@�O�������摜�i�[�p�n���h��
int yajirusi_3;//��ԕ\���������摜�i�[�p�n���h��

int Laser_sound;
int Energy_sound;
int Bomb_sound;
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
//##################�����������������������������������������܂ŕ�������������������������������������������########################2

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


