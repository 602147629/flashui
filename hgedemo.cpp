#include "FlashSprite.h"

HGE *hge=0;


FlashSprite* pFlashSprite=NULL;

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();

	// 更新flash精灵帧
	pFlashSprite->Update(dt);

	return false;
}

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0xff707070);

	// 绘制flash到指定坐标
	pFlashSprite->Render(10,10);

	hge->Gfx_EndScene();

	Sleep(1);

	return false;
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

	if(hge->System_Initiate())
	{
		// 创建flash精灵
		pFlashSprite = new FlashSprite;
		// 加载flash文件
		//pFlashSprite->StartFlash("startup.swf",720,576);
		pFlashSprite->StartFlash("FLASH_001.swf",720,576);

		hge->System_Start();

		// 销毁flash精灵
		if (pFlashSprite)
			delete pFlashSprite;
	}
	else
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	hge->System_Shutdown();
	hge->Release();
	return 0;
}
