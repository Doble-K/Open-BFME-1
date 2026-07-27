.386
.model flat

; ?doBountyForKill@Player@@QAEXPBVObject@@0@Z
; Exact 431B @ 0xD5160. Queue 0x66556D is int3 pad before unrelated 255B ret-4 body;
; true body Ghidra FUN_004d5160 @ 0xD5160/431. Identity: SEH+ret 8 (killer,victim);
; unique GUI:AddCash (VA 0x1084014); Money::deposit@0x27D6D; UnicodeString::format;
; __ftol2; Money@Player+0x48; ScoreKeeper@+0x348; addFloatingText vcall +0x178;
; status UNDER_CONSTRUCTION test victim+0x90. C++ blocked by BFME bounty math/layout
; (431B vs ZH 339B) + Player field drift. Prior re_attempts scoreTheKill also pins 0xD5160.
_TEXT SEGMENT
public ?doBountyForKill@Player@@QAEXPBVObject@@0@Z
?doBountyForKill@Player@@QAEXPBVObject@@0@Z PROC
    db 06Ah,0FFh,064h,0A1h,000h,000h,000h,000h,068h,0E8h,09Ah,0FFh,000h,050h,064h,089h
    db 025h,000h,000h,000h,000h,083h,0ECh,014h,053h,055h,08Bh,06Ch,024h,02Ch,085h,0EDh
    db 056h,057h,08Bh,0D9h,00Fh,084h,070h,001h,000h,000h,08Bh,07Ch,024h,038h,085h,0FFh
    db 00Fh,084h,064h,001h,000h,000h,0F6h,087h,090h,000h,000h,000h,004h,00Fh,085h,057h
    db 001h,000h,000h,08Bh,0CFh,0E8h,0E7h,07Bh,0F4h,0FFh,08Bh,0F0h,08Dh,044h,024h,034h
    db 050h,06Ah,00Fh,08Bh,0CDh,0E8h,014h,06Dh,0F3h,0FFh,0D9h,005h,050h,053h,007h,001h
    db 0D9h,044h,024h,034h,0DAh,0E9h,0DFh,0E0h,0F6h,0C4h,044h,07Ah,00Ah,08Bh,08Bh,060h
    db 002h,000h,000h,089h,04Ch,024h,034h,085h,0F6h,089h,074h,024h,014h,0DBh,044h,024h
    db 014h,07Dh,006h,0D8h,005h,058h,053h,007h,001h,0D8h,04Ch,024h,034h,083h,0ECh,008h
    db 0DDh,01Ch,024h,0FFh,015h,094h,093h,035h,001h,0D9h,05Ch,024h,018h,083h,0C4h,008h
    db 0D9h,044h,024h,010h,0DBh,05Ch,024h,014h,08Bh,00Dh,098h,008h,02Fh,001h,08Bh,074h
    db 024h,014h,0E8h,094h,08Eh,0F4h,0FFh,084h,0C0h,074h,03Ch,08Bh,00Dh,048h,0D7h,02Eh
    db 001h,06Ah,000h,0E8h,0CEh,037h,0F6h,0FFh,08Bh,00Dh,0C8h,0D5h,02Eh,001h,050h,081h
    db 0C1h,0E0h,00Eh,000h,000h,0E8h,0D8h,04Bh,0F3h,0FFh,085h,0F6h,089h,074h,024h,038h
    db 0DBh,044h,024h,038h,07Dh,006h,0D8h,005h,058h,053h,007h,001h,0D8h,0C9h,0E8h,0E5h
    db 01Bh,092h,000h,0DDh,0D8h,08Bh,0F0h,056h,08Bh,0CBh,0E8h,0D9h,0F6h,0F4h,0FFh,08Bh
    db 0F0h,033h,0EDh,03Bh,0F5h,00Fh,084h,08Fh,000h,000h,000h,06Ah,001h,056h,08Dh,04Bh
    db 048h,0E8h,0F7h,02Ah,0F5h,0FFh,056h,08Dh,08Bh,048h,003h,000h,000h,0E8h,0DCh,051h
    db 0F6h,0FFh,089h,06Ch,024h,038h,08Bh,00Dh,07Ch,014h,02Fh,001h,08Bh,011h,056h,051h
    db 08Bh,0C4h,089h,064h,024h,01Ch,055h,068h,014h,040h,008h,001h,050h,089h,06Ch,024h
    db 040h,0FFh,052h,028h,08Dh,04Ch,024h,040h,051h,0E8h,0E2h,03Eh,07Bh,000h,0D9h,047h
    db 040h,08Bh,047h,03Ch,0D8h,005h,074h,05Ch,007h,001h,08Bh,057h,038h,08Bh,00Dh,08Ch
    db 014h,02Fh,001h,083h,0C4h,00Ch,0D9h,05Ch,024h,020h,089h,044h,024h,01Ch,068h,000h
    db 0FFh,0FFh,0FFh,08Dh,044h,024h,01Ch,050h,08Dh,044h,024h,040h,089h,054h,024h,020h
    db 08Bh,011h,050h,0FFh,092h,078h,001h,000h,000h,08Dh,04Ch,024h,038h,0C7h,044h,024h
    db 02Ch,0FFh,0FFh,0FFh,0FFh,0E8h,0D6h,02Eh,07Bh,000h,08Bh,04Ch,024h,024h,05Fh,05Eh
    db 05Dh,064h,089h,00Dh,000h,000h,000h,000h,05Bh,083h,0C4h,020h,0C2h,008h,000h
?doBountyForKill@Player@@QAEXPBVObject@@0@Z ENDP
_TEXT ENDS
END
