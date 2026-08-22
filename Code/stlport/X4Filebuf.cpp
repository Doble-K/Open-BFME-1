// stlport
// STLport 4.5.3 Win32 file-buffer implementation.

#include <fstream>
#include <windows.h>

#define _STLP_LF 10
#define _STLP_CR 13
#define _STLP_CTRLZ 26

_STLP_BEGIN_NAMESPACE

ptrdiff_t _Filebuf_base::_M_read(char *buf, ptrdiff_t n)
{
  DWORD NumberOfBytesRead;
  ReadFile(_M_file_id, (LPVOID)buf, (DWORD)n,
           &NumberOfBytesRead, 0);

  if ((! (_M_openmode & ios_base::binary)) && NumberOfBytesRead) {
    // translate CR-LFs to LFs in the buffer
    char * to = buf, * last = buf + NumberOfBytesRead - 1;
    char * from;
    for (from = buf; from <= last && * from != _STLP_CTRLZ; ++ from ) {
      if (* from != _STLP_CR)
        * to ++ = * from;
      else { // found CR
        if (from < last) { // not at buffer end
          if (* (from + 1) != _STLP_LF)
            * to ++ = _STLP_CR;
        }
        else { // last char is CR, peek for LF
          char peek = ' ';
          DWORD NumberOfBytesPeeked;
          ReadFile(_M_file_id, (LPVOID)&peek,
                   1, &NumberOfBytesPeeked, 0);
          if (NumberOfBytesPeeked) {
            if (peek != _STLP_LF) {
              * to ++ = _STLP_CR;
              SetFilePointer(_M_file_id,(LONG)-1,0,FILE_CURRENT);
            }
            else
              SetFilePointer(_M_file_id,(LONG)-2,0,FILE_CURRENT);
          }
        }
      } // found CR
    } // for
    // seek back to TEXT end of file if hit CTRL-Z
    if (from <= last) // terminated due to CTRLZ
      SetFilePointer(_M_file_id,(LONG)((last+1) - from),0,FILE_CURRENT);
    NumberOfBytesRead = to - buf;
  }
  return (ptrdiff_t)NumberOfBytesRead;
}

_STLP_END_NAMESPACE
