.386
.model flat

; ?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z
; Exact 363 retail bytes @ 0x0043AF60 (ghidra FUN_0083af60; queue size 402 was int3 pad)
; Identity: prologue push ebx/ebp; m_pendingPlaceType@+0x534, m_pendingPlaceSourceObjectID@+0x538
; m_mouseMode@+0x824, m_mouseModeCursor@+0x828, m_placeIcon[0]@+0x53c; ret 8
; Neighbors: beginAreaSelectHint@0x43AC30, setGUICommand@0x43ADE0; next ghidra 0x43B150
; Layout vs ZH: pending place fields compact near +0x534 (ZH m_pendingPlaceType@+0x1740)
_TEXT SEGMENT
public ?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z
?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z PROC
    db 053h,055h,08Bh,06Ch,024h,00Ch,056h,057h,033h,0FFh,03Bh,0EFh,08Bh,0F1h,074h,008h
    db 08Bh,006h,0FFh,090h,01Ch,001h,000h,000h,039h,0BEh,034h,005h,000h,000h,074h,010h
    db 03Bh,0EFh,074h,00Ch,08Bh,016h,057h,057h,08Bh,0CEh,0FFh,092h,0C0h,000h,000h,000h
    db 08Bh,044h,024h,018h,033h,0DBh,03Bh,0C7h,089h,0AEh,034h,005h,000h,000h,089h,0BEh
    db 038h,005h,000h,000h,074h,013h,08Bh,098h,0FCh,000h,000h,000h,03Bh,0DFh,074h,009h
    db 08Bh,043h,074h,089h,086h,038h,005h,000h,000h,08Bh,00Dh,05Ch,04Ch,02Fh,001h,03Bh
    db 0CFh,00Fh,084h,0FDh,000h,000h,000h,03Bh,0EFh,00Fh,084h,0AEh,000h,000h,000h,0C7h
    db 086h,024h,008h,000h,000h,001h,000h,000h,000h,0BFh,004h,000h,000h,000h,089h,0BEh
    db 028h,008h,000h,000h,08Bh,00Dh,05Ch,04Ch,02Fh,001h,08Bh,011h,0FFh,052h,03Ch,08Bh
    db 00Dh,05Ch,04Ch,02Fh,001h,085h,0C9h,074h,015h,08Bh,001h,057h,0FFh,050h,038h,083h
    db 0BEh,024h,008h,000h,000h,002h,075h,006h,089h,0BEh,028h,008h,000h,000h,08Bh,00Dh
    db 0D8h,0F1h,02Eh,001h,06Ah,0FFh,06Ah,008h,055h,0E8h,018h,013h,0BFh,0FFh,085h,0DBh
    db 08Bh,0F8h,074h,032h,08Bh,00Dh,0C8h,0D5h,02Eh,001h,083h,0B9h,018h,002h,000h,000h
    db 004h,08Bh,0CBh,075h,00Eh,0E8h,0EAh,057h,0BEh,0FFh,08Bh,090h,0C8h,001h,000h,000h
    db 052h,0EBh,00Ch,0E8h,0DCh,057h,0BEh,0FFh,08Bh,080h,0C4h,001h,000h,000h,050h,08Bh
    db 0CFh,0E8h,0B3h,0DBh,0BEh,0FFh,08Bh,08Dh,0B0h,003h,000h,000h,051h,08Bh,0CFh,0E8h
    db 041h,0E9h,0BFh,0FFh,0C7h,087h,0B0h,000h,000h,000h,066h,066h,0E6h,03Eh,08Bh,096h
    db 03Ch,005h,000h,000h,089h,03Ah,05Fh,05Eh,05Dh,05Bh,0C2h,008h,000h,083h,0BEh,024h
    db 008h,000h,000h,001h,075h,016h,089h,0BEh,024h,008h,000h,000h,0C7h,086h,028h,008h
    db 000h,000h,002h,000h,000h,000h,08Bh,00Dh,05Ch,04Ch,02Fh,001h,08Bh,001h,0FFh,050h
    db 040h,08Bh,00Dh,05Ch,04Ch,02Fh,001h,03Bh,0CFh,074h,007h,08Bh,011h,06Ah,002h,0FFh
    db 052h,038h,08Bh,006h,057h,08Bh,0CEh,0FFh,090h,0CCh,000h,000h,000h,08Bh,0CEh,0E8h
    db 077h,03Bh,0BEh,0FFh,05Fh,05Eh,05Dh,05Bh,0C2h,008h,000h
?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z ENDP
_TEXT ENDS
END
