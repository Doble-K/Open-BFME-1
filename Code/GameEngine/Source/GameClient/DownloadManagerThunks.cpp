// Two rows were removed from this file. A 5-byte thunk row byte-verifies against
// any incremental-link entry in the image, because every one of them is
// E9 xx xx xx xx and the displacement is a REL32 the verifier fills in from the
// target -- so the name is never tested. Following each thunk to its body showed
// two of the three named the wrong function:
//
//   DownloadManager::OnError        claimed the thunk whose body is the matched
//                                   DownloadManager::getLastLocalFile
//   DownloadManager::OnStatusUpdate claimed the one whose body is the matched
//                                   DownloadManager::OnProgressUpdate
//
// Neither can be a linker fold. Zero Hour's OnError and OnStatusUpdate each
// switch over a code and build a string, while getLastLocalFile takes no
// argument and returns an AsciiString, and OnProgressUpdate takes four.
//
// downloadNextQueuedFile stays: its body is unclaimed, so nothing contradicts
// it. See tools/audit_thunk_rows.py before adding another row here.
class DownloadManager
{
public:
	long downloadNextQueuedFile();
};

class DownloadManagerDownloadNextQueuedFileShim
{
public:
	long downloadNextQueuedFile();
};

long DownloadManager::downloadNextQueuedFile()
{
	return ((DownloadManagerDownloadNextQueuedFileShim *)this)->downloadNextQueuedFile();
}
