#ifndef IDV_SCENEPROPS_H
#define IDV_SCENEPROPS_H

#include <d3dx9math.h>
#include <IDVMath.h>

#include <vector>

struct IDVLight{
	/*D3DXVECTOR3*/XVECTOR3 Position;
	/*D3DXVECTOR3*/XVECTOR3 Color;
	int		 Type;
	int		 Enabled;
};

struct IDVSceneProps{
	IDVSceneProps() : ActiveCamera(0) , ActiveLights(1), ActiveLightCamera(0), ActiveGaussKernel(0), Exposure(0.3f) , BloomFactor(1.1f) {}

	void	AddLight(/*D3DXVECTOR3*/XVECTOR3 Pos, /*D3DXVECTOR3*/XVECTOR3 Color,bool enabled);
	void	RemoveLight(unsigned int index);
	void	SetLightPos(unsigned int index, /*D3DXVECTOR3*/XVECTOR3);

	std::vector<IDVLight>	   Lights;

	/*D3DXVECTOR3*/XVECTOR3			AmbientColor;

	int ActiveCamera;
	int	ActiveLights;
	int ActiveLightCamera;
	int ActiveGaussKernel;
	
	// HDR
	float	Exposure;
	float	BloomFactor;
};

#endif
