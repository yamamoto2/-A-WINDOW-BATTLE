#pragma once


struct TAMA_//�e�̍\����
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

	int BombKind = 2;		//�����̉摜�̌��݂̎��
	int BombKindMax = 11;	//�����̉摜�̍ő吔
	int BombCnt = 0;    //�����̋����̂��߂̐��l
	int BombCntMax = 3;	//�����̃R�}����̃t���[����

	int PinkCnt = 20, PinkCntMax = 20;
	int Pinkdansoku = 0; //���炵���e���̕ۑ���

	int Ly = 0;
	int Ry = 0;

	int Lu = 0;
	int Ld = 0;
	int Ru = 0;
	int Rd = 0;

	int SnY = 0;
	int SnX = 0;

	int stay = 600;

	BOOL Snipe = FALSE;

	BOOL Same = FALSE;

};

struct PLAYER_//���@�̍\����
{
	int HP=100;
	int Handle;	//�摜�i�[�p�n���h��
	int x;
	int y;
	int Width;
	int Height;
};

VOID JOUTAI_HYOUJI_(VOID);//��ԕ\��
VOID DANSUU_(VOID);//�e��
VOID IDOU_SOUSA_(VOID);//�ړ�����
VOID SHOT_MODE_(VOID);//�e��
VOID SHOT_KYODOU_(VOID);//�e�̋���
VOID PLAYER_HYOUJI_(VOID);
VOID GAZOU_YOMIKOMI_(VOID);
VOID PAD_SOUSA(VOID);

VOID BLUE_BOMB(TAMA_ *);	//���e�̔����`��
VOID DELAY(TAMA_*);
VOID YCHA(TAMA_*);
VOID XCHA(TAMA_*);
VOID TCHA(TAMA_*);
VOID STAY(TAMA_*);
VOID SNIPE(TAMA_*);
VOID TEST(TAMA_*);


BOOL ATARI_HANTEI_(RECT, RECT);

extern int Laser_dansuu_;
extern int Energy_dansuu_;
extern int Bomb1_dansuu_;//1�Ŏ~�߂邽�߂����5�� 

extern BOOL A_;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�
extern BOOL B_;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�
extern BOOL C_;//�e���O�̎��ˌ��L�[���������тɃ����[�h�ɑ΂���΍�

extern BOOL SHOT_;//�p�b�h�̃{�^���A�ˑ΍�
extern BOOL HOUKOU_;//�p�b�h�̃{�^���A�ˑ΍�@�E
extern BOOL SHOTMODE_;//�p�b�h�̃{�^���A�ˑ΍�@�E
extern BOOL RELOAD_;//�p�b�h�{�^���A�ˑ΍�@�E
extern BOOL DANSOKU_;
extern BOOL HOUKOU_1_;//�p�b�h�̃{�^���A�ˑ΍�@��
extern BOOL SHOTMODE_1_;//�p�b�h�̃{�^���A�ˑ΍�@��

extern BOOL reload_;//�����[�h�����ۂ�
extern BOOL DAMAGE_;

extern BOOL ue_[256];//�e�e����[�ɓ����������ǂ���
extern BOOL sita_[256];//�e�e�����[�ɓ����������ǂ���

extern int countC_;//�����[�h�̎��Ԋi�[�p�@�T�b
extern int i_;//�ʂ̒e�p�̐���
extern int shothoukou_;//�e�̕���
extern int dansoku_ ;//�����e��
extern int dansokumode_;//�e���̕ύX
extern int shotmode_;//�e�̎�ށ@�����e��F�O
extern int q_;

extern TAMA_ tama_init_;	//�e�̉摜�ǂݍ��݁E�������̂��߂Ɏg���ϐ�
extern TAMA_ tama_[TAMA_MAX];//�\���̂̔z��

extern PLAYER_ player_;//�\���̂̕ϐ�