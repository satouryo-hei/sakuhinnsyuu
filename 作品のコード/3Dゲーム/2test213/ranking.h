//=============================================================================
//
// �����L���O�̏��� [ranking.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include"scene.h"

#define PORT_NUMBER (12345)	//�|�[�g�ԍ�

#define RANKING_TEXT "data/TEXT/Ranking.txt"
#define ONLINE_TEXT "data/TEXT/Online.txt"
#define ID_TEXT "data/TEXT/id.txt"
#define MAX_RANKING (5)
#define MAX_DATA (32)
#define MAX_NUM (256)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScore;

//*****************************************************************************
// �����L���O�̃N���X
//*****************************************************************************
class CRanking : public CScene
{
public:																// �N�ł��A�N�Z�X�\
	CRanking(PRIORITY nPriority = PRIORITY_UI);							// �R���X�g���N�^
	~CRanking();													// �f�X�g���N�^
																	// �����o�֐�
	static CRanking *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// �����L���O�̐���
	HRESULT Init(D3DXVECTOR3 pos/*, D3DXVECTOR2 m_Size*/);				// �����L���O�̏������֐�
	void Uninit(void);												// �����L���O�̏I���֐�
	void Update(void);												// �����L���O�̍X�V�֐�
	void Draw(void);												// �����L���O�̕`��֐�
	inline void SetRanking(const int nRanking);						// �����L���O�̐ݒ�֐�
	inline void GetOnlineRanking(void);								// �I�����C���̃����L���O�̎擾�֐�
	inline int SetOnlineRanking(const int nScore);					// �I�����C���̃����L���O�̐ݒ�֐�
	void NewScore(const int nScore);												// ���ԂƃX�R�A�̌v�Z����֐�
	bool GetClear(void) { return m_bGameClear; }					// �Q�[�����N���A�������ǂ����̎擾�֐�
	void SetClear(bool bClear) { m_bGameClear = bClear; }			// �Q�[�����N���A�������ǂ����̐ݒ�֐� 

private:															// �����������A�N�Z�X�\
	inline void LodeRankingUI(void);
	int AddScoreTime(void);											// ���ԂƃX�R�A�̌v�Z����֐�
	inline void LodeScore(void);									// �X�R�A�̓ǂݍ��݊֐�
	inline void LodeOfflineRnking(void);							// �I�t���C�����̃����L���O�̓ǂݍ��݊֐�
	inline bool LodeOnline(void);									// �I�����C���ɂ���̂���ǂݍ��݊֐�
	// �����o�ϐ�
	static const char * m_apUIFlieName;								// ���݂̏���
	static CScore* m_apScore[MAX_RANKING];							// �X�R�A�̃|�C���^�[
	D3DXVECTOR3 m_Pos;												// ���݈ʒu
	D3DXVECTOR2 m_Size;												// �傫��
	int m_aRankScore[MAX_RANKING];									// ���݂̃����L���O�f�[�^�̎擾�p�ϐ�
	int m_nNowScore;												// ���݂̃X�R�A�擾�p�ϐ�
	char m_aRnkingData[MAX_RANKING][MAX_DATA];						// ���݂̏���
	bool m_bGameClear;												// �Q�[���N���A�������ǂ���
	D3DXVECTOR3 m_LodePos[MAX_RANKING];
	D3DXVECTOR2 m_LodeSize[MAX_RANKING];
};

//����ւ�����
template<class T> void swap(T &data0, T &data1)
{
	T dataWk;
	dataWk = data0;
	data0 = data1;
	data1 = dataWk;
}
#endif