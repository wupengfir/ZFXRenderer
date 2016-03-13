#include "ZFXRenderDevice.h"

class ZFXRenderer{
public:
	ZFXRenderer(HINSTANCE hinst);
	~ZFXRenderer();

	HRESULT CreateDevice(char *chAPI);
	void    Realease();
	LPZFXRENDERDEVICE GetDevice(){
		return m_pDevice;
	};
	HMODULE GetModule(){
		return m_hDll;
	}

private:
	LPZFXRENDERDEVICE m_pDevice;
	HINSTANCE         m_hinst;
	HMODULE           m_hDll;
};
typedef class ZFXRenderer* LPZFXRENDERDER;