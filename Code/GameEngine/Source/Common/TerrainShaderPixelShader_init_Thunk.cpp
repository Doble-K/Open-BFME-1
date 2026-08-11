// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail three-variant terrain pixel-shader setup in C++.

typedef unsigned long DWORD;
typedef long HRESULT;

enum ChipsetType
{
	DC_UNKNOWN = 0,
	DC_GENERIC_PIXEL_SHADER_1_1 = 3
};

class W3DShaderInterface
{
public:
	virtual int set(int) = 0;
	virtual int init() = 0;
private:
	DWORD m_pad;
};

class TerrainShaderPixelShader : public W3DShaderInterface
{
public:
	virtual int set(int);
private:
	virtual int init();
	DWORD m_dwBasePixelShader;
	DWORD m_dwBaseNoise1PixelShader;
	DWORD m_dwBaseNoise2PixelShader;
};

class TerrainShader2Stage
{
public:
	int init();
};

class W3DShaderManager
{
public:
	static ChipsetType getChipset();
	static HRESULT LoadAndCreateD3DShader(const char *filename, DWORD *shader);
};

extern TerrainShader2Stage OpenBFME5_terrainShader2Stage;
extern W3DShaderInterface *OpenBFME5_W3DShaders[4];
extern DWORD OpenBFME5_W3DShadersPassCount[4];
extern TerrainShaderPixelShader OpenBFME5_terrainShaderPixelShader;

int TerrainShaderPixelShader::init()
{
	int res;
	if (OpenBFME5_terrainShader2Stage.init() &&
		(res = W3DShaderManager::getChipset()) >= DC_GENERIC_PIXEL_SHADER_1_1) {
		if (res >= DC_GENERIC_PIXEL_SHADER_1_1) {
			HRESULT hr = W3DShaderManager::LoadAndCreateD3DShader("shaders\\terrain.pso", &m_dwBasePixelShader);
			if (hr < 0) return 0;
			hr = W3DShaderManager::LoadAndCreateD3DShader("shaders\\terrainnoise.pso", &m_dwBaseNoise1PixelShader);
			if (hr < 0) return 0;
			hr = W3DShaderManager::LoadAndCreateD3DShader("shaders\\terrainnoise2.pso", &m_dwBaseNoise2PixelShader);
			if (hr < 0) return 0;

			OpenBFME5_W3DShaders[0] = &OpenBFME5_terrainShaderPixelShader;
			OpenBFME5_W3DShaders[1] = &OpenBFME5_terrainShaderPixelShader;
			OpenBFME5_W3DShaders[2] = &OpenBFME5_terrainShaderPixelShader;
			OpenBFME5_W3DShaders[3] = &OpenBFME5_terrainShaderPixelShader;
			OpenBFME5_W3DShadersPassCount[0] = 1;
			OpenBFME5_W3DShadersPassCount[1] = 1;
			OpenBFME5_W3DShadersPassCount[2] = 1;
			OpenBFME5_W3DShadersPassCount[3] = 1;
			return 1;
		}
	}
	return 0;
}
