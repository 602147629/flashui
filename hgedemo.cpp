#include "FlashSprite.h"

HGE *hge=0;


FlashSprite* pFlashSprite=NULL;

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();

	// ����flash����֡
	pFlashSprite->Update(dt);

	return false;
}

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0xFF707070);

	// ����flash��ָ������
	pFlashSprite->Render(10,10);

	hge->Gfx_EndScene();

	Sleep(1);

	return false;
}

LRESULT myWinMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	pFlashSprite->OnWinMsgProc(message, wParam, lParam);
	return 0;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_LOGFILE, "hgedemo.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Play Flash In HGE");
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_HIDEMOUSE, false);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_FPS,60);
	hge->System_SetWinMsgFunc(myWinMsgProc);

	if(hge->System_Initiate())
	{
		// ����flash����
		pFlashSprite = new FlashSprite;
		// ����flash�ļ�
		pFlashSprite->StartFlash("Tab.swf",800,600);
		//pFlashSprite->StartFlash("FLASH_001.swf",720,576);

		hge->System_Start();

		// ����flash����
		if (pFlashSprite)
			delete pFlashSprite;
	}
	else
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	hge->System_Shutdown();
	hge->Release();
	return 0;
}
