#include "ZFXRenderer.h"
ZFXRenderer::ZFXRenderer(HINSTANCE hinst){
	this->m_hinst = hinst;
	this->m_hDll = NULL;
	this->m_pDevice = NULL;
}

ZFXRenderer::~ZFXRenderer(){
	this->Realease();
}

HRESULT ZFXRenderer::CreateDevice(char *chAPI){
	std::string name;
	name.assign(chAPI);
	if(name == "Direct3D"){
		m_hDll = LoadLibrary("ZFXD3D.dll");
		if(!m_hDll){
			MessageBox(NULL,"ZFXD3D.dll load failed","engine-error",MB_OK|MB_ICONERROR);
			return E_FAIL;
		}
	}else{
		std::string info;
		info = "API" + name + "not supported.";
		MessageBox(NULL,info.c_str(),"engine-error",MB_OK|MB_ICONERROR);
		return E_FAIL;
	}

	CREATERENDERDEVICE _CreateRenderDevice = 0;
	HRESULT hr;
	_CreateRenderDevice = (CREATERENDERDEVICE)GetProcAddress(m_hDll,"CreateRenderDevice");
	if(!_CreateRenderDevice){
		return E_FAIL;
	}
	hr = _CreateRenderDevice(m_hDll,&m_pDevice);
	if(FAILED(hr)){
		MessageBox(NULL,"creating device failed","engine-error",MB_OK|MB_ICONERROR);
		return E_FAIL;
	}
	return S_OK;

}

void ZFXRenderer::Realease() {
	RELEASERENDERDEVICE _ReleaseRenderDevice = 0;
	HRESULT hr;

	if (m_hDll) {
		// function pointer to dll 'ReleaseRenderDevice' function
		_ReleaseRenderDevice = (RELEASERENDERDEVICE)
			GetProcAddress(m_hDll, "ReleaseRenderDevice");
	}
	// call dll's release function
	if (m_pDevice) {
		hr = _ReleaseRenderDevice(&m_pDevice);
		if(FAILED(hr)){
			m_pDevice = NULL;
		}
	}
} // Release