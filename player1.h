#pragma once

struct TAMA//�e�̍\����
{
	int x;
	int y;
	int houkou;//����
	int countA;//���Ԃ̕ۑ���
	int countB;//�����G�t�F�N�g�̐���
	BOOL IsView;//�e�̕\����\��
	int dansoku;//�e��
	int shotmode;//�e���Ƃ̒e��f�[�^
	int Angle;

	int handle[(int)TAMA_KIND_END];	//�e�̉摜�̃n���h��
	int Width[(int)TAMA_KIND_END];	//�e�̕�
	int Height[(int)TAMA_KIND_END];	//�e�̍���

	int BombKind = 101;		//�����̉摜�̌��݂̎��
	int BombKindMax = 110;	//�����̉摜�̍ő吔

	int BombCnt = 0;    //�����̋����̂��߂̐��l
	int BombCntMax = 3;	//�����̃R�}����̃t���[����
	int PinkCnt = 20;
};

struct PLAYER//���@�̍\����
{
	int HP;
	int Handle;	//�摜�i�[�p�n���h��
	int x;
	int y;
	int Width;
	int Height;
};

VOID JOUTAI_HYOUJI(VOID);//��ԕ\��
VOID DANSUU(VOID);//�e��
VOID IDOU_SOUSA(VOID);//�ړ�����
VOID SHOT_MODE(VOID);//�e��
VOID SHOT_KYODOU(VOID);//�e�̋���
VOID PLAYER_HYOUJI(VOID);
VOID GAZOU_YOMIKOMI(VOID);
VOID PAD_SOUSA(VOID);

VOID BLUE_BOMB(TAMA *);	//���e�̔����`��

BOOL ATARI_HANTEI(RECT, RECT);
BOOL ATARI_HANTEI2(RECT, RECT);

extern BOOL A;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�
extern BOOL B;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�
extern BOOL C;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�
 
extern BOOL SHOT;//�p�b�h�̃{�^���A�ˑ΍�
extern BOOL HOUKOU;//�p�b�h�̃{�^���A�ˑ΍�@�E
extern BOOL SHOTMODE;//�p�b�h�̃{�^���A�ˑ΍�@�E
extern BOOL RELOAD;//�p�b�h�{�^���A�ˑ΍�@�E
extern BOOL DANSOKU;
extern BOOL HOUKOU_1;//�p�b�h�̃{�^���A�ˑ΍�@��
extern BOOL SHOTMODE_1;//�p�b�h�̃{�^���A�ˑ΍�@��
 
extern BOOL reload;//�����[�h�����ۂ�
extern BOOL DAMAGE;

extern BOOL ue[256];//�e�e����[�ɓ����������ǂ���
extern BOOL sita[256];//�e�e�����[�ɓ����������ǂ���

extern int Laser_dansuu;
extern int Energy_dansuu;
extern int Bomb1_dansuu;//1�Ŏ~�߂邽�߂����5�� 

extern int countC;//�����[�h�̎��Ԋi�[�p�@�T�b
extern int i;//�ʂ̒e�p�̐���
extern int shothoukou;//�e�̕���
extern int dansoku;//�����e��
extern int dansokumode;//�e���̕ύX
extern int shotmode;//�e�̎�ށ@�����e��F�O
extern int q;

extern TAMA tama_init;	//�e�̉摜�ǂݍ��݁E�������̂��߂Ɏg���ϐ�
extern TAMA tama[TAMA_MAX];//�\���̂̔z��

extern PLAYER player;	//�\���̂̕ϐ�