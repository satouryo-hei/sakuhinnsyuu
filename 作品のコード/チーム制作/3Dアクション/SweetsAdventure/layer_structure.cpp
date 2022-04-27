//---------------------------------------------------
//�w�i�̏���
//---------------------------------------------------
#include "layer_structure.h"
#include "model.h"


//--------------------------
//�R���X�g���N�g
//----------------------------

CLayer_Structure::CLayer_Structure()
{
}

//--------------------------
//�f�X�g���N�g
//----------------------------
CLayer_Structure::~CLayer_Structure()
{

}

//-----------------------------------------------------------
//���[�V�����f�[�^�̓ǂݍ���
//-----------------------------------------------------------
void CLayer_Structure::SetLayer_Structure(const char *sFileName, CModel **apModel)
{
	int nIndex = 0;						//�p�[�c�̔ԍ�
	int nParent = 0;				//�e�q�֌W
	char string[6][255];
	char pPartsFileName[20][255];	//���f���p�[�c�̃t�@�C���l�[��
	memset(&pPartsFileName, NULL, sizeof(pPartsFileName));
	D3DXVECTOR3 PartsPos, PartsRot;	//�e�p�[�c�̈ʒu�ƌ���
	int nCntModel = 0;
	int nNumModel = 0;
									//text�t�@�C���ǂݍ���
	FILE *pfile = fopen(sFileName, "r");
	//�k���`�F�b�N
	if (pfile != NULL)
	{
		while (1)
		{
			//��P���ǂݍ���
			fscanf(pfile, "%s", &string[0]);

			//���f����
			if (strcmp(string[0], "NUM_MODEL") == 0)
			{
				fscanf(pfile, "%s", &string[1]);
				fscanf(pfile, "%d", &nNumModel);
				m_MaxParts = nNumModel;
			}

			//���f���̃t�@�C���̂Ȃ܂�
			if (strcmp(string[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pfile, "%s", &string[1]);
 				fscanf(pfile, "%s", &pPartsFileName[nCntModel]);
				nCntModel++;
			}

			//--------------------------------------
			//���f���̊K�w�\���̐ݒ�
			//--------------------------------------
			while (strcmp(string[0], "CHARACTERSET") == 0)
			{
				fscanf(pfile, "%s", &string[1]);

				//�p�[�c�̐ݒ�
				while (strcmp(string[1], "PARTSSET") == 0)
				{
					fscanf(pfile, "%s", &string[2]);
					//���f���p�[�c�̔ԍ�
					if (strcmp(string[2], "INDEX") == 0)
					{
						fscanf(pfile, "%s", &string[2]);
						fscanf(pfile, "%d", &nIndex);
					}
					//�e�̔ԍ�
					if (strcmp(string[2], "PARENT") == 0)
					{
						fscanf(pfile, "%s", &string[2]);
						fscanf(pfile, "%d", &nParent);
					}
					//�ʒu
					if (strcmp(string[2], "POS") == 0)
					{
						fscanf(pfile, "%s", &string[2]);
						fscanf(pfile, "%f %f %f", &PartsPos.x, &PartsPos.y, &PartsPos.z);
					}
					//����
					if (strcmp(string[2], "ROT") == 0)
					{
						fscanf(pfile, "%s", &string[2]);
						fscanf(pfile, "%f %f %f", &PartsRot.x, &PartsRot.y, &PartsRot.z);
					}
					//���f���̐���
					if (strcmp(string[2], "END_PARTSSET") == 0)
					{
						apModel[nIndex] = CModel::Create(PartsPos, PartsRot, pPartsFileName[nIndex]);
						apModel[nIndex]->SetLayerPos(PartsPos);
						apModel[nIndex]->SetLayerRot(PartsRot);

						//�e�q�֌W��t����
						if (nParent != -1)
						{
							apModel[nIndex]->SetParent(apModel[nParent]);
							apModel[nIndex]->SetNumParent(nParent);
						}
						else
						{
							apModel[nIndex]->SetParent(NULL);
							apModel[nIndex]->SetNumParent(-1);
						}
						break;
					}

				}
				//�I��
				if (strcmp(string[1], "END_CHARACTERSET") == 0)
				{
					break;
				}

			}

			//�X�N���v�g�Ǎ��̏I��
			if (strcmp(string[0], "END_SCRIPT") == 0)
			{
				break;
			}

		}
	}
}