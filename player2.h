#pragma once

VOID JOUTAI_HYOUJI_(VOID);//��ԕ\��
VOID DANSUU_(VOID);//�e��
VOID IDOU_SOUSA_(VOID);//�ړ�����
VOID SHOT_MODE_(VOID);//�e��
VOID SHOT_KYODOU_(VOID);//�e�̋���
VOID PLAYER_HYOUJI_(VOID);
VOID GAZOU_YOMIKOMI_(VOID);
VOID PAD_SOUSA(VOID);

BOOL ATARI_HANTEI_(RECT, RECT);
BOOL ATARI_HANTEI_2(RECT, RECT);

TAMA_ tama_init_;	//�e�̉摜�ǂݍ��݁E�������̂��߂Ɏg���ϐ�
TAMA_ tama_[TAMA_MAX];//�\���̂̔z��

int Redtama1_dansuu_ = 15;
int Redtama2_dansuu_ = 30;
int Bluebomb1_dansuu_ = 5;//1�Ŏ~�߂邽�߂����5�� 

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

int countC_;//�����[�h�̎��Ԋi�[�p�@�T�b
int i_ = 0;//�ʂ̒e�p�̐���
int shothoukou_ = 0;//�e�̕���
int dansoku_ = 2;//�����e��
int dansokumode_ = 0;//�e���̕ύX
int shotmode_ = 0;//�e�̎�ށ@�����e��F�O
int q_ = 0;
