// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: VideoPlayer destructor ? clear global singleton then chain bases

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class VideoPlayerBase : public SubsystemInterface
{
public:
	virtual ~VideoPlayerBase();
};

class VideoPlayer : public VideoPlayerBase
{
public:
	virtual ~VideoPlayer();
};

extern VideoPlayer *TheVideoPlayer;

// empty intermediate so MSVC emits its vtbl store then jumps to SubsystemInterface
VideoPlayerBase::~VideoPlayerBase()
{
}

// ??1VideoPlayer@@UAE@XZ
VideoPlayer::~VideoPlayer()
{
	if (this == TheVideoPlayer)
		TheVideoPlayer = 0;
}
