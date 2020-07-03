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
	Redtama1,
	Redtama2,
	Bluebomb1,
	Bluebomb2,
	Bluebomb3,
	Bluebomb4,
	Bluebomb5,
	Bluebomb6,
	Bluebomb7,
	Bluebomb8,
	Bluebomb9,
	Bluebomb10,
	Bluebomb11,
	Redtama3,
	TAMA_KIND_END	//�e�̎�ނ̍ő�l
};

enum LOCK_ON//���b�N�I���摜��
{
	lockon1,
	lockon2,
	lockon3
};
struct TAMA//�e�̍\����
{
	int x;
	int y;
	int houkou;//����
	int countA;//���Ԃ̕ۑ���
	int countB = 11;//�����G�t�F�N�g�̐���
	BOOL IsView;//�e�̕\����\��
	int dansoku;//�e��
	int shotmode;//�e���Ƃ̒e��f�[�^
	int Angle;

	int handle[(int)TAMA_KIND_END];	//�e�̉摜�̃n���h��
	int Width[(int)TAMA_KIND_END];	//�e�̕�
	int Height[(int)TAMA_KIND_END];	//�e�̍���
};

struct PLAYER//���@�̍\����
{
	int HP = 100;
	int Handle;	//�摜�i�[�p�n���h��
	int x;
	int y;
	int Width;
	int Height;
};
PLAYER player;//�\���̂̕ϐ�

struct LOCKON//���b�N�I���摜��
{
	int Handle[3];
	int Width[3];
	int Height[3];
};
LOCKON lockon;

struct TAMA_//�e�̍\����
{
	int x;
	int y;
	int houkou;//����
	int countA;//���Ԃ̕ۑ���
	int countB = 11;//�����G�t�F�N�g�̐���
	BOOL IsView;//�e�̕\����\��
	int dansoku;//�e��
	int shotmode;//�e���Ƃ̒e��f�[�^
	int Angle;

	int handle[(int)TAMA_KIND_END];	//�e�̉摜�̃n���h��
	int Width[(int)TAMA_KIND_END];	//�e�̕�
	int Height[(int)TAMA_KIND_END];	//�e�̍���
};

struct PLAYER_//���@�̍\����
{
	int HP = 100;
	int Handle;	//�摜�i�[�p�n���h��
	int x;
	int y;
	int Width;
	int Height;
};
PLAYER_ player_;//�\���̂̕ϐ�





