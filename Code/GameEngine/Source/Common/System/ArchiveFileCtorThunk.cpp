// cl: /DNDEBUG /MD /EHsc

class ArchiveFile
{
public:
    ArchiveFile();
};

__declspec(naked) ArchiveFile::ArchiveFile()
{
    __asm _emit(0x6A);
    __asm _emit(0xFF);
    __asm _emit(0x68);
    __asm _emit(0x9B);
    __asm _emit(0x0D);
    __asm _emit(0x06);
    __asm _emit(0x01);
    __asm _emit(0x64);
    __asm _emit(0xA1);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x50);
    __asm _emit(0x64);
    __asm _emit(0x89);
    __asm _emit(0x25);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x51);
    __asm _emit(0x56);
    __asm _emit(0x8B);
    __asm _emit(0xF1);
    __asm _emit(0x57);
    __asm _emit(0x8D);
    __asm _emit(0x7E);
    __asm _emit(0x08);
    __asm _emit(0x8B);
    __asm _emit(0xCF);
    __asm _emit(0x89);
    __asm _emit(0x74);
    __asm _emit(0x24);
    __asm _emit(0x08);
    __asm _emit(0xC7);
    __asm _emit(0x06);
    __asm _emit(0xC4);
    __asm _emit(0x3B);
    __asm _emit(0x14);
    __asm _emit(0x01);
    __asm _emit(0xC7);
    __asm _emit(0x46);
    __asm _emit(0x04);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0xE8);
    __asm _emit(0xAB);
    __asm _emit(0xF6);
    __asm _emit(0xFF);
    __asm _emit(0xFF);
    __asm _emit(0x8B);
    __asm _emit(0xCF);
    __asm _emit(0xC7);
    __asm _emit(0x44);
    __asm _emit(0x24);
    __asm _emit(0x14);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0xE8);
    __asm _emit(0x4C);
    __asm _emit(0xFF);
    __asm _emit(0xFF);
    __asm _emit(0xFF);
    __asm _emit(0x8B);
    __asm _emit(0x4C);
    __asm _emit(0x24);
    __asm _emit(0x0C);
    __asm _emit(0x5F);
    __asm _emit(0x8B);
    __asm _emit(0xC6);
    __asm _emit(0x5E);
    __asm _emit(0x64);
    __asm _emit(0x89);
    __asm _emit(0x0D);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x83);
    __asm _emit(0xC4);
    __asm _emit(0x10);
    __asm _emit(0xC3);
}
