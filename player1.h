#pragma once

//�v���g�^�C�v�錾
VOID START_GAMEN(VOID);//�X�^�[�g���
VOID READY_GAMEN(VOID);//�������
VOID GAME_GAMEN(VOID);//�Q�[�����
VOID END_GAMEN(VOID);//�G���h���

VOID JOUTAI_HYOUJI(VOID);//��ԕ\��
VOID DANSUU(VOID);//�e��
VOID IDOU_SOUSA(VOID);//�ړ�����
VOID SHOT_MODE(VOID);//�e��
VOID SHOT_KYODOU(VOID);//�e�̋���
VOID PLAYER_HYOUJI(VOID);
VOID GAZOU_YOMIKOMI(VOID);
VOID PAD_SOUSA(VOID);

BOOL ATARI_HANTEI(RECT, RECT);
BOOL ATARI_HANTEI2(RECT, RECT);


TAMA tama_init;	//�e�̉摜�ǂݍ��݁E�������̂��߂Ɏg���ϐ�
TAMA tama[TAMA_MAX];//�\���̂̔z��

int Redtama1_dansuu = 15;
int Redtama2_dansuu = 30;
int Bluebomb1_dansuu = 5;//1�Ŏ~�߂邽�߂����5�� 

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

int countC;//�����[�h�̎��Ԋi�[�p�@�T�b
int i = 0;//�ʂ̒e�p�̐���
int shothoukou = 0;//�e�̕���
int dansoku = 2;//�����e��
int dansokumode = 0;//�e���̕ύX
int shotmode = 0;//�e�̎�ށ@�����e��F�O
int q = 0;