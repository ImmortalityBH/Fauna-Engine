#include "Game/Game.h"
#include <string>
#include <vector>
#include <algorithm>
#include <Utility/Error.h>
#include <thread>
#include <cmath>
#include <random>

using namespace DirectX;

Game::Game()
	: wnd(), camera(wnd),
	  randomNum(0), taskNum(0)
{
}

Game::~Game()
{
}

bool Game::init()
{
	//intro = std::make_unique<SoundEffect>(wnd.aud.get() , L"res/audio/intro.wav");
	//outro = std::make_unique<SoundEffect>(wnd.aud.get(), L"res/audio/outro.wav");

	auto loadModel = [this]() {
		dorito = std::make_unique<Model>();
		floorModel = std::make_unique<Model>();
		dogModel = std::make_unique<Model>();
		bagModel = std::make_unique<Model>();
		mtnDewModel = std::make_unique<Model>();
		coinModel = std::make_unique<Model>();
		sunModel = std::make_unique<Model>();
		//DORITO
		std::vector<Vertex> vertices = {
			Vertex(0.0f, 0.5f, 0.0f, 0.5f, 1.0f),
			Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
			Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f),
		};
		//FLOOR
		std::vector<Vertex> floorVertices = {
			Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f),
			Vertex(0.5f, -0.5f, 0.0f, 2.0f, 2.0f),
			Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 2.0f),
			Vertex(0.5f, 0.5f, 0.0f, 2.0f, 0.0f),
		};
		std::vector<Vertex> bagVertices = {
			Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f),
			Vertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f),
			Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f),
			Vertex(0.5f, 0.5f, 0.0f, 1.0f, 0.0f),
		};
		std::vector<DWORD> floorIndices = {
			0, 1, 2,
			3, 1, 0,
		};
		/*td::vector<Vertex> boxVertices = {
			{ -1.0f,  1.0f, -1.0f, },
			{ -1.0f, -1.0f, -1.0f, },
			{1.0f, -1.0f, -1.0f,},
			{1.0f, -1.0f, -1.0f,},
			{1.0f,  1.0f, -1.0f,},
			{-1.0f,  1.0f, -1.0f,},

			{-1.0f, -1.0f,  1.0f,},
			{-1.0f, -1.0f, -1.0f,},
			{-1.0f,  1.0f, -1.0f,},
			{-1.0f,  1.0f, -1.0f,},
			{-1.0f,  1.0f,  1.0f,},
			{-1.0f, -1.0f,  1.0f,},

			{1.0f, -1.0f, -1.0f,},
			{1.0f, -1.0f,  1.0f,},
			{ 1.0f,  1.0f,  1.0f,},
			{1.0f,  1.0f,  1.0f,},
			{1.0f,  1.0f, -1.0f,},
			{1.0f, -1.0f, -1.0f,},

			{-1.0f, -1.0f,  1.0f,},
			{-1.0f,  1.0f,  1.0f,},
			{1.0f,  1.0f,  1.0f,},
			{1.0f,  1.0f,  1.0f,},
			{1.0f, -1.0f,  1.0f,},
			{-1.0f, -1.0f,  1.0f,},

			{-1.0f,  1.0f, -1.0f,},
			{ 1.0f,  1.0f, -1.0f,},
			{ 1.0f,  1.0f,  1.0f,},
			{ 1.0f,  1.0f,  1.0f,},
			{-1.0f,  1.0f,  1.0f,},
			{-1.0f,  1.0f, -1.0f,},

			{-1.0f, -1.0f, -1.0f,},
			{-1.0f, -1.0f,  1.0f,},
			{ 1.0f, -1.0f, -1.0f,},
			{ 1.0f, -1.0f, -1.0f,},
			{-1.0f, -1.0f,  1.0f,},
			{ 1.0f, -1.0f,  1.0f},
		};*/
		dorito->create(wnd.getGraphics().getDevice(), wnd.getGraphics().getContext(), vertices);
		floorModel->create(wnd.getGraphics().getDevice(), wnd.getGraphics().getContext(), floorVertices, floorIndices);
		dogModel->create(wnd.getGraphics().getDevice(), wnd.getGraphics().getContext(), bagVertices, floorIndices);
		bagModel->create(wnd.getGraphics().getDevice(), wnd.getGraphics().getContext(), bagVertices, floorIndices);
		mtnDewModel->create(wnd.getGraphics().getDevice(), wnd.getGraphics().getContext(), bagVertices, floorIndices);
		coinModel->create(wnd.getGraphics().getDevice(), wnd.getGraphics().getContext(), bagVertices, floorIndices);
		sunModel->create(wnd.getGraphics().getDevice(), wnd.getGraphics().getContext(), bagVertices, floorIndices);
		dorito->setPos(0.0f, 0.35f, 1.5f);
		dorito->setScale(1.0f, 1.0f, 1.0f);
		setCoinPos();
	};
	auto loadTex = [this]() { //no need to check return types handling done in class
		dorTex.load(wnd.getGraphics().getDevice(), L"res/img/dorito.dds");
		florTex.load(wnd.getGraphics().getDevice(), L"res/img/floor.dds");
		dogTex.load(wnd.getGraphics().getDevice(), L"res/img/dog.dds");
		bagTex.load(wnd.getGraphics().getDevice(), L"res/img/bag.dds");
		mtnTex.load(wnd.getGraphics().getDevice(), L"res/img/mtndew.dds");
		catTex.load(wnd.getGraphics().getDevice(), L"res/img/winkcat.dds");
		coinTex.load(wnd.getGraphics().getDevice(), L"res/img/coin.dds");
		sunTex.load(wnd.getGraphics().getDevice(), L"res/img/sun.dds");
		coinSound = std::make_unique<DirectX::SoundEffect>(wnd.aud.get(), L"res/audio/coin.wav");
	};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    

	std::thread modelThread(loadModel);
	std::thread texThread(loadTex);

	modelThread.join();
	texThread.join();

	//Sound sound(wnd.audioEngine, "res/audio/poop.wav");

	/*std::vector<std::wstring> fileNames = {
		L"res/audio/amazing.wav",
		L"res/audio/awesome.wav",
		L"res/audio/delicious.wav",
		L"res/audio/good job.wav",
		L"res/audio/incredible.wav",
		L"res/audio/mom.wav",
		L"res/audio/nice one.wav",
		L"res/audio/oh my god.wav",
		L"res/audio/poop.wav",
		L"res/audio/right.wav",
		L"res/audio/un.wav",
		L"res/audio/fire.wav",
		L"res/audio/wow.wav"
	};
	for (std::size_t i = 0; i < fileNames.size(); i++)
	{
		effects[i] = std::make_unique<SoundEffect>(wnd.aud.get(), fileNames[i].c_str());
	}*/
	return true;
}

int Game::run(HINSTANCE hInst)
{
	wnd.init(hInst);
	this->init();
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			this->update();
			this->draw();
		}
	}
	return static_cast<int>(msg.wParam);
}

void Game::update()
{
	float dTime = timer.getElapsed();
	float eTime = elapsedTimer.getElapsed();
	timer.Reset();

	if (!wnd.aud->Update())
	{

	}
	//std::wstring title = L"Mouse Pos (" + std::to_wstring(wnd.mouse.getPos().x) + L", " + 
		//std::to_wstring(wnd.mouse.getPos().y) + L", Wheel: " + std::to_wstring(wnd.mouse.getWheelDelta()) + L")";
	//if (elapsedTimer.Peek() > 10.0f)
	//{
	//	wnd.setTitle(wnd.kbd.getCharAsString().c_str());
	//}
	//std::wstring title =  L"Elapsed Time: " + std::to_wstring(elapsedTimer.Peek()) + L", Delta Time: " + std::to_wstring(dTime);
	//std::wstring forito = L"X: " + std::to_wstring(dorito->transform.position.x) + L", Y:" + std::to_wstring(dorito->transform.position.y);
	//wnd.setTitle(forito.c_str());
	std::wstring title = L"Time elapsed: ";
	title.append(std::to_wstring(elapsedTimer.getElapsed()));
	//wnd.setTitle(title.c_str());

	camera.update(dTime, wnd);
	//model->resetMatrix();
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_W) || wnd.kbd.isKeyPressed(VK_UP))
	{
		dorito->adjustPos(0.0f, dTime * 0.85f, 0.0f);
	} 
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_S) || wnd.kbd.isKeyPressed(VK_DOWN))
	{
		dorito->adjustPos(0.0f, -(dTime * 0.85f), 0.0f);
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_A) || wnd.kbd.isKeyPressed(VK_LEFT))
	{
		dorito->adjustPos(-(dTime * 0.85f), 0.0f, 0.0f);
	}
	if (wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_D) || wnd.kbd.isKeyPressed(VK_RIGHT))
	{
		dorito->adjustPos(dTime * 0.85f, 0.0f, 0.0f);
	}

#pragma region Game code
/*
	if (kb.Q)
	{
		if (randomNum == 0)
		{
			didRequest = true;
		}
	}
	else if (kb.E)
	{
		if (randomNum == 1)
		{
			didRequest = true;
		}
	}
	else if (kb.W)
	{
		if (randomNum == 2)
		{
			didRequest = true;
		}
	}
	else if (kb.S)
	{
		if (randomNum == 3)
		{
			didRequest = true;
		}
	}
	else if (kb.A)
	{
		if (randomNum == 4)
		{
			didRequest = true;
		}
	}
	else if (kb.D)
	{
		if (randomNum == 5)
		{
			didRequest = true;
		}
	}

	if (timer.Peek() > 2.5f)
	{
		randomNum = rand() % 6;
		switch (randomNum)
		{
		case 0:
		{
			std::wstring title = L"Dorito Says Rotate Left, Task Number:" + std::to_wstring(taskNum);
			wnd.setTitle(title.c_str());
		}
		break;
		case 1:
		{
			std::wstring title = L"Dorito Says Rotate Right, Task Number:" + std::to_wstring(taskNum);
			wnd.setTitle(title.c_str());
		}
		break;
		case 2:
		{
			std::wstring title = L"Dorito Says Scale Up, Task Number:" + std::to_wstring(taskNum);
			wnd.setTitle(title.c_str());
		}
		break;
		case 3:
		{
			std::wstring title = L"Dorito Says Scale Down, Task Number:" + std::to_wstring(taskNum);
			wnd.setTitle(title.c_str());
		}
		break;
		case 4:
		{
			std::wstring title = L"Dorito Says Move Left, Task Number:" + std::to_wstring(taskNum);
			wnd.setTitle(title.c_str());
		}
		break;
		case 5:
		{
			std::wstring title = L"Dorito Says Move Right, Task Number:" + std::to_wstring(taskNum);
			wnd.setTitle(title.c_str());
		}
		break;
		}
		if (didRequest == false)
		{
			wnd.setTitle(L"YOU FAILED");
			didRequest = true;
		}
		else
		{
			didRequest = false;
			taskNum++;
		}

		timer.Mark();
	}
*/
#pragma endregion

	dorito->transform.position.x = std::clamp(dorito->transform.position.x, -1.5f, 1.5f);
	dorito->transform.position.y = std::clamp(dorito->transform.position.y, -0.30f, 1.15f);

	if (wnd.gamepad.Update())
	{
		float joyX = wnd.gamepad.leftStickX;
		float joyY = wnd.gamepad.leftStickY;
		dorito->adjustPos(0.0f, joyY * dTime * 0.85f, 0.0f);
		dorito->adjustPos(joyX * dTime * 0.85f, 0.0f, 0.0f);
	}
	dorito->adjustRot(0.0f, 1.0f, 0.0f, sin(eTime) * 35.0f);
	dorito->setScale(1.0f, 1.0f, 1.0f);

	dorito->updateMatrix(camera);

	//coinModel->resetMatrix();
	//coinModel->setPos(-0.6f, 0.35f, 1.55f);
	coinModel->adjustRot(0.0f, 1.0f, 0.0f, sin(eTime) * 15.0f);
	coinModel->setScale(1.0f, 1.0f, 1.0f);
	coinModel->updateMatrix(camera);

	//sunModel->setPos(1.0f, 1.0f, 3.0f);
	sunModel->setPos(cos(eTime/2.f) * 5.0f, 2.0f, sin(eTime/2.f) * 5.0f);
	//XMVECTOR vec = XMVectorSet(sunModel->transform.position.x, sunModel->transform.position.y,
		//sunModel->transform.position.z, sunModel->transform.position.w);
	//XMVECTOR zeroVec = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	//XMVECTOR upVec = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	//sunModel->rotation = XMMatrixLookAtLH(vec, zeroVec, upVec);
	sunModel->adjustRot(0.0f, 1.0f, 0.0f, 0.0f);
	sunModel->setScale(2.0f, 2.0f, 2.0f);
	sunModel->updateMatrix(camera);

	floorModel->resetMatrix();

	floorModel->setPos(0.0f, -0.75f, 3.0f);
	floorModel->adjustRot(1.0f, 0.0f, 0.0f, 85.0f);
	floorModel->setScale(4.0f, 4.0f, 1.0f);

	floorModel->updateMatrix(camera);

	dogModel->resetMatrix();

	dogModel->setPos(-3.0f, .45f, 5.0f); 
	dogModel->adjustRot(0.0f, 1.0f, 0.0f, -25.0f);
	dogModel->setScale(sin(eTime) * 5, sin(eTime) * 5, 0.0f);

	dogModel->updateMatrix(camera);

	bagModel->resetMatrix();

	bagModel->setPos(3.0f, .45f, 5.0f);
	bagModel->adjustRot(0.0f, 1.0f, 0.0f, 25.0f);
	bagModel->setScale(4.0f, 4.0f, 1.0f);

	bagModel->updateMatrix(camera);

	mtnDewModel->resetMatrix();
	
	mtnDewModel->setPos(sin(eTime) / 1.0f, 2.0f, 8.0f);
	mtnDewModel->adjustRot(0.0, 0.0f, 1.0f, eTime * 35.0f);
	//mtnDewModel->rotate(0.0, 1.0f, 0.0f, sin(eTime) * 35.0f);
	mtnDewModel->setScale(3.0f, 4.0f, 1.0f);

	mtnDewModel->updateMatrix(camera);
	
	if (dorito->isColliding(*coinModel))
	{
		//if (wnd.gamepad.isButtonPressed(XINPUT_GAMEPAD_A) /*|| wnd.kbd.isKeyPressed(Keyboard::KeyCode::VK_X)*/);
		//{
			wnd.setTitle(L"YOU PICKED UP A COIN");
			if (!doOnce)
			{
				coinSound->Play();
				doOnce = true;
				setCoinPos();
			}
		//}
	}
	else
	{
		doOnce = false;
	}
 }

void Game::draw()
{
	wnd.getGraphics().Begin(0.0f, 0.0f, 0.5f);

	dogModel->bind(wnd.getGraphics().vertexShader, wnd.getGraphics().pixelShader, catTex);
	dogModel->draw();
	dogModel->unbind();

	bagModel->bind(wnd.getGraphics().vertexShader, wnd.getGraphics().pixelShader, bagTex);
	bagModel->draw();
	bagModel->unbind();
	
	dorito->bind(wnd.getGraphics().vertexShader, wnd.getGraphics().pixelShader, dorTex);
	dorito->draw();
	dorito->unbind();

	coinModel->bind(wnd.getGraphics().vertexShader, wnd.getGraphics().pixelShader, coinTex);
	coinModel->draw();
	coinModel->unbind();

	floorModel->bind(wnd.getGraphics().vertexShader, wnd.getGraphics().pixelShader, florTex);
	floorModel->draw();
	floorModel->unbind();

	mtnDewModel->bind(wnd.getGraphics().vertexShader, wnd.getGraphics().pixelShader, mtnTex);
	mtnDewModel->draw();
	mtnDewModel->unbind();

	sunModel->bind(wnd.getGraphics().vertexShader, wnd.getGraphics().pixelShader, sunTex);
	sunModel->draw();
	sunModel->unbind();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	/*ImGui::Begin("Debug");
	ImGui::Text("Fauna Engine: Deluxe Edition debug menu");
	float* pos[3] = { &dorito->transform.position.x, &dorito->transform.position.y, &dorito->transform.position.z };
	ImGui::SliderFloat3("Position", *pos, -1.0, 10.0);
	float* scale[3] = { &dorito->transform.scale.x, &dorito->transform.scale.y, &dorito->transform.scale.z };
	ImGui::SliderFloat3("Scale", *scale, -5.0f, 5.0f);
	float* rotation[3] = { &dorito->transform.rotation.x, &dorito->transform.rotation.y, &dorito->transform.rotation.z };
	ImGui::InputFloat3("Rotation", *rotation, 0);
	ImGui::Button("HOWDY");
	ImGui::End();*/
	
	ImGui::Begin("Debug");
	
	float currentTime = fpsTimer.Reset();
	float framerate = 1.0f / currentTime;
	ImGui::Text(std::to_string(std::stoi(std::to_string(round((framerate))))).c_str());
	ImGui::InputText("Window Title", title, IM_ARRAYSIZE(title));
	if (ImGui::Button("Set Window Title"))
	{
		wnd.setTitle(string_to_wstring(std::string(title)).c_str());
	}
	ImGui::End();


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	wnd.getGraphics().End();
}

float random_num(const float& min, const float& max)
{
	return (rand() / (float)RAND_MAX * max) + min;
}

void Game::setCoinPos()
{
	coinModel->transform.position.x = random_num(minX, maxX);
	coinModel->transform.position.y = random_num(minY, maxY);
	coinModel->transform.position.z = 1.55f;
}

