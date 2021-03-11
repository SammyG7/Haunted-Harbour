// Haunted Harbour SG.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Haunted Harbour SG.h"
#include "GraphicsObject.h"
#include "PlayerObject.h"
#include "BackgrondObject.h"
#include "BlockObject.h"
#include "GroundEnemy.h"
#include "SeaHag.h"
#include "HealthBar.h"
#include "Jellyfish.h"
#include "Level.h"
#include "SpecialObject.h"
#include "HungrySailor.h"
#include "LighthouseKeeper.h"
#include "soundclass.h"
#include "Explosion.h"
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#define MAX_LOADSTRING 100

enum class Gamestate{
	start,
	play,
	dead,
	restart,
	endlevel,
	pause,
	win
} gamestate = Gamestate::start;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
SoundClass m_sound;
UINT_PTR timerid;
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void shouldEndLevel(HitObject*);
void drawScreen(HWND);
void loadMap(Level level);
void removeEnemies();
void nextLevel(HitObject*);
void collectedKey(HitObject*);
void collectedPower(HitObject*);
void restartFunc();
void playFunc();
void playDraw();
// create game objects
PlayerObject victor;
//BlockObject block("../Pics/Crate.bmp", 200, );
BackgrondObject background("../Pics/Background3.jpg", 0, 0, 5118, 800, 0.25);
BackgrondObject ground("../Pics/ground.bmp", 0, GROUND, 774, 128, 1);
GraphicsObject keyicon("../Pics/KeyIcon.bmp", 650, 10, 32, 11);
BackgrondObject startscreen("../Pics/TitleScreen.jpg", 0, 0, 700, 550, 0);
BackgrondObject deathscreen("../Pics/DeathScreen.png", 0, 0, 703, 549, 0);
BackgrondObject pausescreen("../Pics/Pause.jpg", 0, 0, 700, 550, 0);
BackgrondObject winscreen("../Pics/winscreen.jpg", 0, 0, 732, 550, 20);
int curlevel = 0;
int haskey = true;
HealthBar life(&victor);
std::vector<std::unique_ptr<BlockObject>> blockArray;
std::vector<std::unique_ptr<EnemyObject>> enemyArray;
std::vector<std::unique_ptr<SpecialObject>> specialArray;
std::array <Level, 6> levelArray;
CImage blockimage;
CImage skullcrabimage;
CImage seahagimage;
CImage smallblockimage;
CImage jellyimage;
CImage hungryimage;
CImage keeperimage;
CImage treasureimage;
CImage unlockedimage;
CImage keyimage;
CImage powerimage;
CImage grenadeimage;
CImage explosionimage;
int mapPosition = 0;
HDC offScreenDC;

void SetScreen()
{
	HDC hTempDc;
	HBITMAP offScreenBMP;
	hTempDc = GetDC(0);
	//Initilize buffer image;
	offScreenDC = CreateCompatibleDC(hTempDc);
	offScreenBMP=CreateCompatibleBitmap(hTempDc, 800, 600);
	SelectObject(offScreenDC, offScreenBMP);
	ReleaseDC(0, hTempDc);

}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)

{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_HAUNTEDHARBOURSG, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HAUNTEDHARBOURSG));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HAUNTEDHARBOURSG));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_HAUNTEDHARBOURSG);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	blockimage.Load(CString("../Pics/Crate.bmp"));
	smallblockimage.Load(CString("../Pics/SmallCrate.bmp"));
	hInst = hInstance; // Store instance handle in our global variable
	levelArray[0].levelname = "The Boardwalk";
	levelArray[0].filename = "Level1.txt";
	levelArray[1].levelname = "Jump";
	levelArray[1].filename = "Level2.txt";
	levelArray[2].filename = "Level3.txt";
	levelArray[2].levelname = "Leap";
	levelArray[3].filename = "Level4.txt";
	levelArray[3].levelname = "The Maze";
	levelArray[5].filename = "Test.txt";
	levelArray[5].levelname = "TestingGround";
	levelArray[4].levelname = "Run";
	levelArray[4].filename = "Level5.txt";
	skullcrabimage.Load(CString("../Pics/SkullCrab.bmp"));
	seahagimage.Load(CString("../Pics/SeaHag.bmp"));
	jellyimage.Load(CString("../Pics/JellyFish.bmp"));
	hungryimage.Load(CString("../Pics/HungrySailor.bmp"));
	keeperimage.Load(CString("../Pics/LighthouseKeeper.bmp"));
	keyimage.Load(CString ("../Pics/Key.bmp"));
	unlockedimage.Load(CString("../Pics/UnlockedChest.bmp"));
	treasureimage.Load(CString("../Pics/LockedChest.bmp"));
	powerimage.Load(CString("../Pics/Star.png"));
	grenadeimage.Load(CString("../Pics/grenade2.bmp"));
	explosionimage.Load(CString("../Pics/grenadeExplosion.bmp"));
	//grenadeimage.Load(CString("../Pics/grenade.png"));
	WeaponsObject::m_sound = &m_sound;


	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 700, 580, NULL, NULL, hInstance, NULL);



	SetScreen();
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (!m_sound.Initialize(hWnd)){
		MessageBox(hWnd, L"Could not Initialize Direct Sound", L"Error", MB_OK);
		return FALSE;
	}

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			if (victor.isJumping()){
				victor.picY = 86;
				victor.xspeed = 10;
				victor.state = JUMPRIGHT;
			}else{
				victor.setMoveRight();		
			}
			victor.stopright = false;
			break;
		case VK_LEFT:
			if (victor.isJumping()){
				victor.picY = 146;
				victor.xspeed = -10;
				victor.state = JUMPLEFT;
			}else{
				victor.setMoveLeft();}
			victor.stopleft = false;
			break;
		case VK_RETURN:
		case VK_SPACE:
			switch(gamestate){
			case Gamestate::start:
				loadMap(levelArray[0]);
				timerid = SetTimer(hWnd, 1, 50, NULL);
				m_sound.changeVolume(Sounds::shoot, -1000);
				gamestate = Gamestate::play;
				break;
			case Gamestate::play:
				if (victor.shoottimer < 1){
					m_sound.PlayWaveFile(Sounds::shoot);
					if (victor.state == STANDRIGHT){
						victor.setShootRight();
					}else if (victor.state == STANDLEFT){
						victor.setShootLeft();
					}
					if (victor.state == SHOOTRIGHT || victor.state == MOVERIGHT || victor.state == JUMPRIGHT){
						victor.fireBullet(victor.x + victor.width - 15, victor.y + 10,victor.xspeed +20, 0);
					}else{victor.fireBullet(victor.x, victor.y + 10, victor.xspeed - 20, 0);}
					if (!victor.godmode){
						victor.shoottimer = 4;
					}
				}
				break;
			case Gamestate::win:
				PostMessage(hWnd,WM_CLOSE, 0, 0);
				break;			
			case Gamestate::dead:
				gamestate = Gamestate::restart;
				break;
			}
			break;
		case VK_ESCAPE:
			PostMessage(hWnd,WM_CLOSE, 0, 0);
			break;
		case VK_UP:	
			if (victor.state == MOVELEFT || victor.state == STANDLEFT){
				victor.setJumpLeft();
			}else if (victor.state == MOVERIGHT || victor.state == STANDRIGHT){
				victor.setJumpRight();
			}



			break;

		case VK_F1:
		if (gamestate == Gamestate::play){
			victor.isdead = true;
			nextLevel(&victor);
		}
			break;

		case VK_SHIFT:
			victor.godmode = true;
			break;

			//P Key
		case 0x50: 
			switch (gamestate){
			case Gamestate::play:
				gamestate = Gamestate::pause;
				break;
			case Gamestate::pause:
				//timerid = SetTimer(hWnd, 1, 50, NULL);
				gamestate = Gamestate::play;
				break;
			}
			break;
      case 0x47: 
		  switch (gamestate){
			case Gamestate::play:
				int xs = victor.facing ? 23 : -23;				
				victor.throwGrenade(victor.x, victor.y, victor.xspeed + xs, victor.yspeed - 10);
				break;
		  }
	        break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_RIGHT:
			if (victor.isJumping() == false){
				victor.setStandRight();
			}
			victor.stopright = true;
			break;
		case VK_LEFT:
			if (victor.isJumping() == false){
				victor.setStandLeft();
			}
			victor.stopleft = true;
			break;
		case VK_RETURN:
		case VK_SPACE:
			if (victor.state == SHOOTRIGHT){
				victor.setStandRight();
			}else if (victor.state == SHOOTLEFT){
				victor.setStandLeft();
			}

			break;
		}

		break;
	case WM_TIMER:		
		switch(gamestate){
		case Gamestate::play:
			playFunc();
			if (victor.isdead) gamestate = Gamestate::dead;
			break;
		case Gamestate::restart:
			restartFunc();
			break;
		case Gamestate::endlevel:
			nextLevel(&victor);
			break;
			case Gamestate::win:
				mapPosition++;
				break;
		}	
		PostMessage(hWnd,WM_PAINT, 0, 0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		switch(gamestate){
		case Gamestate::start:
			startscreen.draw(offScreenDC);
			break;
		case Gamestate::play:
			playDraw();
			break;
		case Gamestate::dead:
			deathscreen.draw(offScreenDC);
			break;
		case Gamestate::win:
			winscreen.draw(offScreenDC);
			break;
		case Gamestate::pause:
			pausescreen.draw(offScreenDC);
			break;
			//KillTimer(hWnd, timerid);
		}
		drawScreen(hWnd);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


void drawScreen(HWND hWnd)
{
	HDC ScreenDC;
	ScreenDC = GetDC(hWnd);
	TransparentBlt(ScreenDC, 0, 0, 700, 550, offScreenDC, 0, 0, 700, 550, RGB(255,174, 201));
	DeleteDC(ScreenDC);
}

void loadMap(Level level)
{
	bool hasposition = false;
	haskey = false;
	std::string line;
	int y=0;
	int x=0;
	std::unique_ptr<BlockObject> block;
	std::unique_ptr<EnemyObject> enemy; 
	std::unique_ptr<SpecialObject> special;
	std::ifstream Level1 ("Levels/"+level.filename);
	blockArray.clear();
	enemyArray.clear();
	specialArray.clear();
	if(Level1.is_open()){
		while(std::getline(Level1, line)){
			for(auto&& pos:line){
				switch(pos){
				case 'O':
				case '0':
					block.reset(new BlockObject(x*32, y*32, 64, 64));
					block->type = blockType::bigblock;
					blockArray.push_back(std::move(block)); 
					break;
				case 'L':
				case 'l':
					block.reset(new BlockObject(x*32, y*32, 32, 32));
					block->type = blockType::smallblock;
					blockArray.push_back(std::move(block)); 
					break;
				case 'S':	
				case 's':
					enemy.reset(new SeaHag(&victor, x*32, y*32));
					enemyArray.push_back(std::move(enemy));
					break;
				case 'C':
				case 'c':
					enemy.reset(new GroundEnemy(x*32, y*32));
					enemyArray.push_back(std::move(enemy));
					break;
				case '\t':
					x = (x+9)-(x+9)%8-1;
					break;
				case 'J':
				case 'j':
					enemy.reset(new Jellyfish(x*32, y*32));
					enemyArray.push_back(std::move(enemy));
					break;
				case 'p':
				case 'P':
					hasposition = true;
					victor.x = victor.startx = x*32;
					victor.y = victor.starty = y*32;

					break;
				case 'W':
				case 'w':
					special.reset(new SpecialObject(SpecialType::lChest, x*32, y*32, 159, 64));				
					special->callback = std::bind(shouldEndLevel, std::placeholders::_1);				
					specialArray.push_back(std::move(special));
					break;
				case 'U':
				case 'u':
					special.reset(new SpecialObject(SpecialType::uChest, x*32, y*32, 66, 64));
					special->callback = std::bind(shouldEndLevel, std::placeholders::_1);
					specialArray.push_back(std::move(special));
					break;
				case 'k':
				case 'K':
					special.reset(new SpecialObject(SpecialType::key, x*32, y*32, 64, 21));
					special->callback = std::bind(collectedKey, std::placeholders::_1);
					specialArray.push_back(std::move(special));
					haskey = false;
					break;
				case 'H':
				case 'h':
					enemy.reset(new HungrySailor(&victor, x*32, y*32));
					enemyArray.push_back(std::move(enemy));
					break;
				case 'i':
				case 'I':
					enemy.reset(new LighthouseKeeper(&victor, x*32, y*32));
					enemyArray.push_back(std::move(enemy));
					break;
				case 'R':
				case 'r':
					special.reset(new SpecialObject(SpecialType::powerup, x*32, y*32, 60, 59));
					special->callback = std::bind(collectedPower, std::placeholders::_1);
					specialArray.push_back(std::move(special));
					break;
				}
				x += 1;
			}
			x = 0;
			y += 1;
		} 
		if(hasposition == false){
			victor.x = victor.startx = 100;
			victor.y = victor.starty = 0;
		}
		Level1.close();
	}
	victor.resetPlayer();
}

bool checkIfDead(const std::unique_ptr<EnemyObject>& enemy){
	return enemy->deathtimer < 1;
}

void removeEnemies()
{
	for (auto&& enemy : enemyArray){
		if (enemy->isdead){
			enemy->deathtimer -=1;
		}
	}
	enemyArray.erase(std::remove_if(enemyArray.begin(), enemyArray.end(),checkIfDead), enemyArray.end());
}

void nextLevel(HitObject*)
{
	curlevel++;
	if (curlevel == levelArray.size())
	{
		gamestate = Gamestate::win;
	}else{
	loadMap(levelArray[curlevel]);
	gamestate = Gamestate::play;
	}
}

void shouldEndLevel(HitObject*)
{
	gamestate = Gamestate::endlevel;
}

void collectedKey(HitObject*)
{
	haskey = true;
}

void collectedPower(HitObject*)
{
	victor.y -= 20;
}

void restartFunc()
{
		loadMap(levelArray[curlevel]);
		victor.resetPlayer();
        gamestate = Gamestate::play;	
}

void playFunc()
{
	LighthouseKeeper::shouldplaysound = false;
	m_sound.PlayWaveFile(Sounds::theme);
	victor.move();

	for (auto&& block : blockArray){
		victor.checkCollisionWithBlock(block.get());
		victor.checkBulletCollisionWithBlock(block.get());	
		victor.checkGrenadeCollisionWithBlock(block.get());
	}	
	victor.animate();
	victor.shoottimer -= 1;
	removeEnemies();
	for (auto&& special : specialArray){
		if (special->type != SpecialType::lChest || haskey){
			special->checkPlayerCollisionWithSpecial(&victor);
		}
	}	

	for (auto&& enemy : enemyArray){
		enemy->move();
		for (auto&& block : blockArray){
			enemy->checkBulletCollisionWithBlock(block.get());
			enemy->checkEnemyCollisionWithBlock(block.get());
		}
		enemy->moveBullets();
		if (!enemy->isdead){
			victor.checkBulletCollisionWithObject(enemy.get());
			victor.checkExplosionCollisionWithObject(enemy.get());
			enemy->checkEnemyCollisionWithPlayer(&victor);
		}
		enemy->checkBulletCollisionWithObject(&victor);
	}

	victor.moveBullets();	
	victor.explodeGrenades();
	if (LighthouseKeeper::shouldplaysound)
		m_sound.PlayWaveFile(Sounds::skeleton);
	else 
		m_sound.stopSound(Sounds::skeleton);
	
}

void playDraw()
{
	background.draw(offScreenDC);
	ground.draw(offScreenDC);
		
	victor.draw(offScreenDC);

	if (haskey){
		keyicon.drawStatic(offScreenDC);
	}
	for (auto&& block : blockArray){				
		switch(block->type){
		case blockType::bigblock:
			block->draw(offScreenDC, blockimage);
			break;
		case blockType::smallblock:
			block->draw(offScreenDC, smallblockimage);
			break;
		}
	}

	for (auto&& special : specialArray){ 
		switch(special->type){
		case SpecialType::key:			
			if(!haskey) special->draw(offScreenDC, keyimage);				
			break;
		case SpecialType::uChest:
			special->draw(offScreenDC, unlockedimage);
			break;
		case SpecialType::lChest:
			special->draw(offScreenDC, treasureimage);
			break;
		case SpecialType::powerup:
			special->draw(offScreenDC, powerimage);
			break;
		}
	}

	victor.drawBullets(offScreenDC);
	victor.drawGrenades(offScreenDC, grenadeimage, explosionimage);
	for (auto&& enemy : enemyArray){
		switch (enemy->type){
		case enemyType::hag:
			enemy->draw(offScreenDC, seahagimage);
			break;
		case enemyType::crab:
			enemy->draw(offScreenDC, skullcrabimage);
			break;
		case enemyType::jelly:
			enemy->draw(offScreenDC,jellyimage);
			break;
		case enemyType::sailor:
			enemy->draw(offScreenDC,hungryimage);
			break;
		case enemyType::keeper:
			enemy->draw(offScreenDC,keeperimage);
			break;
		}
		enemy->drawBullets(offScreenDC);
	}
	life.draw(offScreenDC);

}

