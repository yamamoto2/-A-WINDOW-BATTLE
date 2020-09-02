#pragma once

#define PI			3.141592654
#define TAMA_MAX	256

//�Q�[�����
enum GAME_SCENE {
	scene_start,	//�X�^�[�g��� 0
	scene_ready,	//�����I����� 1
	scene_game,		//�Q�[����� 2
	scene_end		//�G���h��� 3
};

//�e�̎�ނ𔻕�
enum TAMA_KIND {//�񋓌^�A�ォ�珇��0.1.2.3.4...�Ɛ�����^������@�r������ʂ̐����������邱�Ƃ��\
	Laser,
	Energy,
	Bomb1,
	Bomb2,
	Bomb3,
	Bomb4,
	Bomb5,
	Bomb6,
	Bomb7,
	Bomb8,
	Bomb9,
	Bomb10,
	Bomb11,
	Delay,
	Ycha,
	Xcha,
	XchaLu,
	XchaLd,
	XchaRu,
	XchaRd,
	Tcha,
	Snipe,
	Stay,
	Test,
	TAMA_KIND_END	//�e�̎�ނ̍ő�l
};
enum LOCK_ON//���b�N�I���摜��
{
	lockon1,
	lockon2,
	lockon3
};

struct LOCKON//���b�N�I���摜��
{
	int Handle[3];
	int Width[3];
	int Height[3];
};


extern int Key[256]; // �L�[��������Ă���t���[�������i�[����

extern int HP;//HP�o�[�摜�i�[�p�n���h��
extern int yajirusi_2;//���@�O�������摜�i�[�p�n���h��
extern int yajirusi_3;//��ԕ\���������摜�i�[�p�n���h��

extern int Laser_sound;
extern int Energy_sound;
extern int Bomb_sound;
extern int reload_sound;

extern int Pad1;        //�W���C�p�b�h�̓��͏�Ԋi�[�p�ϐ�
extern int Pad2;        //�W���C�p�b�h�̓��͏�Ԋi�[�p�ϐ�

//�ϐ��̐錾
extern int mode;//��ʑJ��
extern int count;//���t���[��

extern char dansokuhyouji[3];//��ʂɒᒆ������\�����邽�߂� �����e���F��

extern LOCKON lockon;

//�v���g�^�C�v�錾
VOID START_GAMEN(VOID);//�X�^�[�g���
VOID READY_GAMEN(VOID);//�������
VOID GAME_GAMEN(VOID);//�Q�[�����
VOID END_GAMEN(VOID);//�G���h���
