#include "..\ZFXRenderer\ZFXRenderDevice.h"
#define  MAX_3DHWND 8;

class ZFXD3D:public ZFXRenderDevice{
public: 
	ZFXD3D(HINSTANCE hinst);
	~ZFXD3D();

	// initialize the engine stuff
	HRESULT Init(HWND, const HWND*, int, int, int, bool);
	HRESULT InitWindowed(HWND, const HWND*, int, bool);
	BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


	// Interface functions
	HRESULT UseWindow(UINT nHwnd);
	void    Release(void);
	bool    IsRunning(void) { return m_bRunning; }
	HRESULT BeginRendering(bool,bool,bool);
	HRESULT Clear(bool, bool, bool);
	void    EndRendering(void);
	void    SetClearColor(float, float, float);


private:
	ZFXD3DEnum           *m_pEnum;
	LPDIRECT3D9           m_pD3D;
	LPDIRECT3DDEVICE9     m_pDevice;
	LPDIRECT3DSWAPCHAIN9  m_pChain[MAX_3DHWND];
	D3DPRESENT_PARAMETERS m_d3dpp;
	D3DCOLOR              m_ClearColor;
	bool                  m_bIsSceneRunning;
	bool                  m_bStencil;

	// start api with values from dialog box
	HRESULT Go(void);

	// write to log file
	void Log(char *, ...);

};