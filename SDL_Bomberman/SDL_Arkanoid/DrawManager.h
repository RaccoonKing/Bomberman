#pragma once

class Sprite;

class DrawManager
{
public:
	DrawManager();
	~DrawManager();


	/**
	* Initializes the DrawManager and creates an SDL_Renderer connected to an SDL_Window with the specified Width and Height defined in params.
	*/
	bool Initialize(int p_iWidth, int p_iHeight);
	void Shutdown();
	void Clear();
	void Present();
	void Draw(Sprite* p_pxSprite, int p_iX, int p_iY);
	void DebugDraw(int p_iX, int p_iY, int p_iW, int p_iH);
	SDL_Renderer* GetRenderer();
private:
	SDL_Window* m_pxWindow = nullptr;
	SDL_Renderer* m_pxRenderer = nullptr;
};
