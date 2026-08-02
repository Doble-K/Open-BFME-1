class DownloadManager
{
public:
	virtual long OnError(int);
	virtual long OnStatusUpdate(int);
	long downloadNextQueuedFile();
};

class DownloadManagerOnErrorShim
{
public:
	long OnError(int a0);
};

class DownloadManagerOnStatusUpdateShim
{
public:
	long OnStatusUpdate(int a0);
};

class DownloadManagerDownloadNextQueuedFileShim
{
public:
	long downloadNextQueuedFile();
};

long DownloadManager::OnError(int a0)
{
	return ((DownloadManagerOnErrorShim *)this)->OnError(a0);
}

long DownloadManager::OnStatusUpdate(int a0)
{
	return ((DownloadManagerOnStatusUpdateShim *)this)->OnStatusUpdate(a0);
}

long DownloadManager::downloadNextQueuedFile()
{
	return ((DownloadManagerDownloadNextQueuedFileShim *)this)->downloadNextQueuedFile();
}
