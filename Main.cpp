
#include "Scene/SceneManager.h"

#include "Util/System.h"

#include <DxLib.h>
#include <crtdbg.h>

// �v���O������WinMain����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

#if _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    // window���[�h�ݒ�
    ChangeWindowMode(true);

    // �E�C���h�E���ݒ�
    SetMainWindowText("Shooting");

    // ��ʃT�C�Y�̐ݒ�
    SetGraphMode(System::ScreenSizeX, System::ScreenSizeY, 32);

    // ���O�o�͂��s�����ۂ�
    SetOutApplicationLogValidFlag(false);

    // �_�u���o�b�t�@���[�h
    SetDrawScreen(DX_SCREEN_BACK);

    // �c�w���C�u��������������
    if (DxLib_Init() == -1)
    {
        // �G���[���N�����璼���ɏI��
        return -1;
    }

    // �V�[���̃C���X�^���X����
    SceneManager* pScene = new SceneManager();

    // ������
    pScene->Init();

    while (ProcessMessage() == 0)
    {
        LONGLONG  time = GetNowHiPerformanceCount();

        // ��ʂ̃N���A
        ClearDrawScreen();

        // �X�V
        pScene->Update();
        // �`��
        pScene->Draw();

        // ����ʂ�\��ʂ����ւ���
        ScreenFlip();

        // esc�L�[����������I������
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        // fps��60�ɌŒ�
        while (GetNowHiPerformanceCount() - time < 16667)
        {
        }
    }

    // ���������
    pScene->End();
    delete pScene;
    pScene = nullptr;

    // �c�w���C�u�����g�p�̏I������
    DxLib_End();

    // �\�t�g�̏I�� 
    return 0;
}