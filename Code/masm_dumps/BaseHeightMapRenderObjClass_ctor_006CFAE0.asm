.386
.model flat

; ??0BaseHeightMapRenderObjClass@@QAE@XZ
; Exact 1304 retail bytes @ 0x006CFAE0
; True body of BaseHeightMapRenderObjClass default ctor (SEH + base RenderObjClass
; + multi-vtbl + TheTerrainRenderObject + buffer news). Ledger twin at this RVA/size
; is mislabeled ??0LightMapTerrainTextureClass@@QAE@XZ (ZH LightMap is 2-arg TextureClass).
; Ghidra FUN_00acfae0; full epilogue ret is +1306 (size 1307) — claimed size matches owner.
_TEXT SEGMENT
public ??0BaseHeightMapRenderObjClass@@QAE@XZ
??0BaseHeightMapRenderObjClass@@QAE@XZ PROC
    db 06Ah, 0FFh, 068h, 099h, 0A5h, 004h, 001h, 064h, 0A1h, 000h, 000h, 000h, 000h, 050h, 064h, 089h
    db 025h, 000h, 000h, 000h, 000h, 083h, 0ECh, 00Ch, 053h, 055h, 056h, 08Bh, 0F1h, 057h, 089h, 074h
    db 024h, 010h, 0E8h, 0A9h, 009h, 025h, 000h, 08Dh, 0BEh, 0C8h, 000h, 000h, 000h, 033h, 0DBh, 0C7h
    db 007h, 068h, 0D8h, 011h, 001h, 089h, 05Ch, 024h, 024h, 0C7h, 086h, 0CCh, 000h, 000h, 000h, 044h
    db 037h, 007h, 001h, 0C7h, 006h, 0B8h, 0D8h, 011h, 001h, 0C7h, 046h, 008h, 0B0h, 0D8h, 011h, 001h
    db 0C7h, 007h, 0A4h, 0D8h, 011h, 001h, 0C7h, 086h, 0CCh, 000h, 000h, 000h, 090h, 0D8h, 011h, 001h
    db 089h, 09Eh, 0D8h, 000h, 000h, 000h, 089h, 09Eh, 020h, 030h, 000h, 000h, 089h, 09Eh, 024h, 030h
    db 000h, 000h, 089h, 09Eh, 028h, 030h, 000h, 000h, 089h, 09Eh, 02Ch, 030h, 000h, 000h, 089h, 09Eh
    db 030h, 030h, 000h, 000h, 089h, 09Eh, 034h, 030h, 000h, 000h, 089h, 09Eh, 038h, 030h, 000h, 000h
    db 089h, 09Eh, 03Ch, 030h, 000h, 000h, 089h, 09Eh, 040h, 030h, 000h, 000h, 089h, 09Eh, 044h, 030h
    db 000h, 000h, 0C7h, 086h, 048h, 030h, 000h, 000h, 01Bh, 044h, 010h, 000h, 089h, 09Eh, 050h, 030h
    db 000h, 000h, 089h, 09Eh, 054h, 030h, 000h, 000h, 089h, 09Eh, 058h, 030h, 000h, 000h, 089h, 09Eh
    db 05Ch, 030h, 000h, 000h, 089h, 09Eh, 060h, 030h, 000h, 000h, 089h, 09Eh, 064h, 030h, 000h, 000h
    db 089h, 09Eh, 068h, 030h, 000h, 000h, 089h, 09Eh, 070h, 030h, 000h, 000h, 089h, 09Eh, 074h, 030h
    db 000h, 000h, 089h, 09Eh, 078h, 030h, 000h, 000h, 089h, 09Eh, 07Ch, 030h, 000h, 000h, 08Dh, 0AEh
    db 080h, 030h, 000h, 000h, 089h, 05Dh, 000h, 089h, 09Eh, 084h, 030h, 000h, 000h, 089h, 09Eh, 088h
    db 030h, 000h, 000h, 089h, 09Eh, 08Ch, 030h, 000h, 000h, 089h, 09Eh, 090h, 030h, 000h, 000h, 0DDh
    db 005h, 010h, 0DCh, 011h, 001h, 0DDh, 005h, 040h, 0C6h, 007h, 001h, 0C6h, 044h, 024h, 024h, 014h
    db 0DDh, 054h, 024h, 014h, 088h, 09Eh, 009h, 030h, 000h, 000h, 088h, 09Eh, 014h, 030h, 000h, 000h
    db 088h, 09Eh, 0F9h, 02Fh, 000h, 000h, 0B8h, 002h, 000h, 000h, 000h, 0EBh, 003h, 08Dh, 049h, 000h
    db 0A8h, 001h, 074h, 002h, 0D8h, 0C9h, 0D1h, 0E8h, 03Bh, 0C3h, 074h, 006h, 0D9h, 0C1h, 0DEh, 0CAh
    db 0EBh, 0EEh, 0DDh, 05Ch, 024h, 014h, 089h, 09Eh, 00Ch, 030h, 000h, 000h, 089h, 09Eh, 0C0h, 030h
    db 000h, 000h, 0DDh, 0D8h, 089h, 09Eh, 0C4h, 030h, 000h, 000h, 0DDh, 044h, 024h, 014h, 089h, 09Eh
    db 0C8h, 030h, 000h, 000h, 0DCh, 025h, 040h, 0C6h, 007h, 001h, 0C7h, 086h, 0CCh, 030h, 000h, 000h
    db 000h, 000h, 080h, 0BFh, 089h, 09Eh, 04Ch, 030h, 000h, 000h, 089h, 09Eh, 0F4h, 02Fh, 000h, 000h
    db 0DCh, 00Dh, 000h, 0DCh, 011h, 001h, 089h, 09Eh, 0FCh, 02Fh, 000h, 000h, 089h, 09Eh, 000h, 030h
    db 000h, 000h, 0D9h, 09Eh, 010h, 030h, 000h, 000h, 089h, 09Eh, 004h, 030h, 000h, 000h, 088h, 09Eh
    db 0F8h, 02Fh, 000h, 000h, 088h, 09Eh, 008h, 030h, 000h, 000h, 089h, 035h, 0E0h, 07Fh, 02Fh, 001h
    db 068h, 010h, 099h, 02Ah, 000h, 089h, 09Eh, 094h, 030h, 000h, 000h, 0E8h, 080h, 022h, 01Bh, 000h
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 014h, 03Bh, 0C3h, 0C6h, 044h, 024h, 024h, 015h, 074h, 018h
    db 08Bh, 00Dh, 0C8h, 0D5h, 02Eh, 001h, 033h, 0D2h, 08Ah, 091h, 0CDh, 00Dh, 000h, 000h, 08Bh, 0C8h
    db 052h, 0E8h, 09Eh, 08Ch, 096h, 0FFh, 0EBh, 002h, 033h, 0C0h, 068h, 028h, 039h, 01Eh, 000h, 0C6h
    db 044h, 024h, 028h, 014h, 089h, 086h, 094h, 030h, 000h, 000h, 089h, 09Eh, 098h, 030h, 000h, 000h
    db 0E8h, 03Bh, 022h, 01Bh, 000h, 083h, 0C4h, 004h, 089h, 044h, 024h, 014h, 03Bh, 0C3h, 0C6h, 044h
    db 024h, 024h, 016h, 074h, 018h, 08Bh, 00Dh, 0C8h, 0D5h, 02Eh, 001h, 033h, 0D2h, 08Ah, 091h, 0CDh
    db 00Dh, 000h, 000h, 08Bh, 0C8h, 052h, 0E8h, 02Eh, 03Bh, 095h, 0FFh, 0EBh, 002h, 033h, 0C0h, 068h
    db 01Ch, 0F7h, 002h, 000h, 0C6h, 044h, 024h, 028h, 014h, 089h, 086h, 098h, 030h, 000h, 000h, 089h
    db 09Eh, 09Ch, 030h, 000h, 000h, 0E8h, 0F6h, 021h, 01Bh, 000h, 083h, 0C4h, 004h, 089h, 044h, 024h
    db 014h, 03Bh, 0C3h, 0C6h, 044h, 024h, 024h, 017h, 074h, 009h, 08Bh, 0C8h, 0E8h, 046h, 023h, 096h
    db 0FFh, 0EBh, 002h, 033h, 0C0h, 068h, 0D0h, 009h, 001h, 000h, 0C6h, 044h, 024h, 028h, 014h, 089h
    db 086h, 09Ch, 030h, 000h, 000h, 089h, 09Eh, 0A0h, 030h, 000h, 000h, 0E8h, 0C0h, 021h, 01Bh, 000h
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 014h, 03Bh, 0C3h, 0C6h, 044h, 024h, 024h, 018h, 074h, 009h
    db 08Bh, 0C8h, 0E8h, 05Ah, 0ACh, 095h, 0FFh, 0EBh, 002h, 033h, 0C0h, 068h, 0C0h, 0D7h, 000h, 000h
    db 0C6h, 044h, 024h, 028h, 014h, 089h, 086h, 0A0h, 030h, 000h, 000h, 0C7h, 086h, 0D0h, 02Fh, 000h
    db 000h, 0CDh, 0CCh, 0B3h, 042h, 0C7h, 086h, 0D4h, 02Fh, 000h, 000h, 000h, 000h, 08Ch, 042h, 089h
    db 09Eh, 0B0h, 030h, 000h, 000h, 0E8h, 076h, 021h, 01Bh, 000h, 083h, 0C4h, 004h, 089h, 044h, 024h
    db 014h, 03Bh, 0C3h, 0C6h, 044h, 024h, 024h, 019h, 074h, 009h, 08Bh, 0C8h, 0E8h, 0ABh, 09Fh, 093h
    db 0FFh, 0EBh, 002h, 033h, 0C0h, 06Ah, 02Ch, 0C6h, 044h, 024h, 028h, 014h, 089h, 086h, 0B0h, 030h
    db 000h, 000h, 089h, 09Eh, 0A4h, 030h, 000h, 000h, 0E8h, 043h, 021h, 01Bh, 000h, 083h, 0C4h, 004h
    db 089h, 044h, 024h, 014h, 03Bh, 0C3h, 0C6h, 044h, 024h, 024h, 01Ah, 074h, 009h, 08Bh, 0C8h, 0E8h
    db 0D2h, 025h, 095h, 0FFh, 0EBh, 002h, 033h, 0C0h, 06Ah, 00Ch, 0C6h, 044h, 024h, 028h, 014h, 089h
    db 086h, 0A4h, 030h, 000h, 000h, 0E8h, 016h, 021h, 01Bh, 000h, 083h, 0C4h, 004h, 089h, 044h, 024h
    db 014h, 03Bh, 0C3h, 0C6h, 044h, 024h, 024h, 01Bh, 074h, 009h, 08Bh, 0C8h, 0E8h, 0FDh, 00Fh, 094h
    db 0FFh, 0EBh, 002h, 033h, 0C0h, 06Ah, 058h, 0C6h, 044h, 024h, 028h, 014h, 089h, 086h, 0A8h, 030h
    db 000h, 000h, 089h, 09Eh, 0ACh, 030h, 000h, 000h, 0E8h, 0E3h, 020h, 01Bh, 000h, 083h, 0C4h, 004h
    db 089h, 044h, 024h, 014h, 03Bh, 0C3h, 0C6h, 044h, 024h, 024h, 01Ch, 074h, 009h, 08Bh, 0C8h, 0E8h
    db 007h, 0E6h, 094h, 0FFh, 0EBh, 002h, 033h, 0C0h, 068h, 010h, 001h, 000h, 000h, 0C6h, 044h, 024h
    db 028h, 014h, 089h, 086h, 0ACh, 030h, 000h, 000h, 089h, 09Eh, 0B4h, 030h, 000h, 000h, 0E8h, 0ADh
    db 020h, 01Bh, 000h, 083h, 0C4h, 004h, 089h, 044h, 024h, 014h, 03Bh, 0C3h, 0C6h, 044h, 024h, 024h
    db 01Dh, 074h, 009h, 08Bh, 0C8h, 0E8h, 0AFh, 0D8h, 096h, 0FFh, 0EBh, 002h, 033h, 0C0h, 06Ah, 050h
    db 0C6h, 044h, 024h, 028h, 014h, 089h, 086h, 0B4h, 030h, 000h, 000h, 089h, 09Eh, 0D0h, 000h, 000h
    db 000h, 089h, 09Eh, 0D4h, 000h, 000h, 000h, 089h, 09Eh, 0C4h, 02Fh, 000h, 000h, 089h, 09Eh, 0C8h
    db 02Fh, 000h, 000h, 089h, 09Eh, 0CCh, 02Fh, 000h, 000h, 089h, 09Eh, 0D8h, 02Fh, 000h, 000h, 089h
    db 09Eh, 0DCh, 02Fh, 000h, 000h, 089h, 09Eh, 0E0h, 02Fh, 000h, 000h, 0E8h, 050h, 020h, 01Bh, 000h
    db 083h, 0C4h, 004h, 089h, 044h, 024h, 014h, 03Bh, 0C3h, 0C6h, 044h, 024h, 024h, 01Eh, 074h, 009h
    db 08Bh, 0C8h, 0E8h, 0C4h, 0B0h, 097h, 0FFh, 0EBh, 002h, 033h, 0C0h, 089h, 086h, 0B8h, 030h, 000h
    db 000h, 0A1h, 0C8h, 0D5h, 02Eh, 001h, 038h, 098h, 0F5h, 00Ch, 000h, 000h, 0C6h, 044h, 024h, 024h
    db 014h, 074h, 03Ah, 06Ah, 050h, 0E8h, 016h, 020h, 01Bh, 000h, 083h, 0C4h, 004h, 089h, 044h, 024h
    db 014h, 03Bh, 0C3h, 0C6h, 044h, 024h, 024h, 01Fh, 074h, 014h, 08Bh, 0C8h, 0E8h, 04Ah, 0D8h, 096h
    db 0FFh, 0C6h, 044h, 024h, 024h, 014h, 089h, 086h, 0BCh, 030h, 000h, 000h, 0EBh, 015h, 033h, 0C0h
    db 0C6h, 044h, 024h, 024h, 014h, 089h, 086h, 0BCh, 030h, 000h, 000h, 0EBh, 006h, 089h, 09Eh, 0BCh
    db 030h, 000h, 000h, 06Ah, 00Eh, 068h, 0ECh, 0DBh, 011h, 001h, 08Dh, 08Eh, 084h, 030h, 000h, 000h
    db 089h, 03Dh, 08Ch, 005h, 034h, 001h, 0E8h, 0B5h, 07Dh, 01Bh, 000h, 06Ah, 00Eh, 068h, 0D8h, 0DBh
    db 011h, 001h, 08Bh, 0CDh, 0E8h, 0A7h, 07Dh, 01Bh, 000h, 06Ah, 00Eh, 068h, 0C4h, 0DBh, 011h, 001h
    db 08Dh, 08Eh, 088h, 030h, 000h, 000h, 0E8h, 095h, 07Dh, 01Bh, 000h, 06Ah, 00Eh, 068h, 0B0h, 0DBh
    db 011h, 001h, 08Dh, 08Eh, 08Ch, 030h, 000h, 000h, 0E8h, 083h, 07Dh, 01Bh, 000h, 0A1h, 0F0h, 018h
    db 02Fh, 001h, 03Bh, 0C3h, 075h, 004h, 033h, 0C0h, 0EBh, 00Ch, 08Bh, 048h, 004h, 03Bh, 0CBh, 074h
    db 005h, 0E8h, 005h, 023h, 093h, 0FFh, 08Bh, 048h, 010h, 089h, 08Eh, 01Ch, 030h, 000h, 000h, 0A1h
    db 0F0h, 018h, 02Fh, 001h, 03Bh, 0C3h, 074h, 00Eh, 08Bh, 048h, 004h, 03Bh, 0CBh, 074h, 005h, 0E8h
    db 0E7h, 022h, 093h, 0FFh, 08Bh, 0D8h, 08Bh, 053h, 00Ch, 08Bh, 04Ch, 024h, 01Ch, 05Fh, 089h, 096h
    db 018h, 030h, 000h, 000h, 0C6h, 086h, 0D0h, 030h, 000h, 000h, 001h, 08Bh, 0C6h, 05Eh, 05Dh, 05Bh
    db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h, 083h
??0BaseHeightMapRenderObjClass@@QAE@XZ ENDP
_TEXT ENDS
END
