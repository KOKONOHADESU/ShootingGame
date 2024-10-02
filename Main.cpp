
#include "Scene/SceneManager.h"

#include "Util/DxLibSystem.h"
#include "Util/MTRandom.h"

#include <DxLib.h>
#include <crtdbg.h>

// プログラムはWinMainから始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

#if _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    // windowモード設定
    ChangeWindowMode(DxLibSystem::kWindowMode);

    // ウインドウ名設定
    SetMainWindowText(DxLibSystem::kTitleText);

    // 画面サイズの設定
    SetGraphMode(DxLibSystem::kScreenWidth, DxLibSystem::kScreenHeight, DxLibSystem::kColorDepth);

    // ログ出力を行うか否か
    SetOutApplicationLogValidFlag(DxLibSystem::kCreateLogText);

    // ダブルバッファモード
    SetDrawScreen(DX_SCREEN_BACK);

    // ＤＸライブラリ初期化処理
    if (DxLib_Init() == -1)
    {
        // エラーが起きたら直ちに終了
        return -1;
    }

    // シーンのインスタンス生成
    SceneManager* pScene = new SceneManager();

    // 初期化
    pScene->Init();

    // 乱数生成クラスのインスタンスを生成
    MTRandom::GetInstance();

    while (ProcessMessage() == 0)
    {
        LONGLONG  time = GetNowHiPerformanceCount();

        // 画面のクリア
        ClearDrawScreen();

        // 更新
        pScene->Update();
        // 描画
        pScene->Draw();

        // 裏画面を表画面を入れ替える
        ScreenFlip();

        // escキーを押したら終了する
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        // fpsを60に固定
        while (GetNowHiPerformanceCount() - time < 16667)
        {
        }
    }

    // メモリ解放
    pScene->End();
    delete pScene;
    pScene = nullptr;

    MTRandom::GetInstance()->Destroy();

    // ＤＸライブラリ使用の終了処理
    DxLib_End();

    // ソフトの終了 
    return 0;
}