// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the retail adaptive-delta cache path to C++.

#include <string.h>

class AdaptiveDeltaMotionChannelClass
{
private:
	unsigned long m_pivotIndex;
	unsigned long m_type;
	int m_vectorLength;
	unsigned long m_numFrames;
	float m_scale;
	float m_bfmeScale2;
	unsigned long *m_data;
	unsigned long m_cacheFrame;
	float *m_cacheData;

	void decompress(unsigned long frame, float *data);
	void decompress(unsigned long sourceFrame, float *sourceData,
		unsigned long frame, float *data);
	float getframe(unsigned long frame, unsigned long vectorIndex);
};

// ?getframe@AdaptiveDeltaMotionChannelClass@@AAEMKK@Z
float AdaptiveDeltaMotionChannelClass::getframe(unsigned long frame, unsigned long vectorIndex)
{
	if (frame >= m_numFrames)
		frame = m_numFrames - 1;

	if (m_cacheFrame == frame)
		return m_cacheData[vectorIndex];

	if (m_cacheFrame + 1 == frame)
		return m_cacheData[vectorIndex + m_vectorLength];

	if (frame < m_cacheFrame) {
		decompress(frame, m_cacheData);
		if (frame != m_numFrames - 1)
			decompress(frame, m_cacheData, frame + 1, m_cacheData + m_vectorLength);
		m_cacheFrame = frame;
		return m_cacheData[vectorIndex];
	}

	if (frame == m_cacheFrame + 2) {
		memcpy(m_cacheData, m_cacheData + m_vectorLength, m_vectorLength * sizeof(float));
		++m_cacheFrame;
		decompress(m_cacheFrame, m_cacheData, frame, m_cacheData + m_vectorLength);
		return m_cacheData[m_vectorLength + vectorIndex];
	}

	float temp[4];
	memcpy(temp, m_cacheData + m_vectorLength, m_vectorLength * sizeof(float));
	decompress(m_cacheFrame, temp, frame, m_cacheData);
	m_cacheFrame = frame;
	if (frame != m_numFrames - 1)
		decompress(m_cacheFrame, m_cacheData, frame + 1, m_cacheData + m_vectorLength);
	return m_cacheData[vectorIndex];
}
