.386
.model flat

; ?update@AIPanicState@@UAE?AW4StateReturnType@@XZ
; Exact 399B @ 0x0017B840. Drift queue 0x0077B0E1 is mid-body noise (target
; byte 0x00; not a prologue). True body = AIPanicState vtbl 0x109A988 slot6
; (thunk 0x149CA -> 0x17B840; ghidra FUN_0057b840 size 399). Slot4=onEnter@
; 0x17B680 already matched; slot6 prologue matches C++ update shape (sub esp,8
; push ebx/ebp/esi/edi). Logic: AIInternalMoveToState::update + KINDOF_CAN_BE_REPULSED
; timer/repulsor fail + waypoint success path (getNextWaypoint/GameLogicRandomValue/
; computeGoal/computePath). C++ blocked by State/Object/layout offsets. MASM exact.
_TEXT SEGMENT
public ?update@AIPanicState@@UAE?AW4StateReturnType@@XZ
?update@AIPanicState@@UAE?AW4StateReturnType@@XZ PROC
    db 083h,0ECh,008h,053h,055h,056h,057h,08Bh,0F1h,0E8h,0A8h,0D0h,0ECh,0FFh,08Bh,07Eh
    db 01Ch,08Bh,05Fh,010h,08Bh,0E8h,08Bh,043h,004h,085h,0C0h,074h,00Ch,08Bh,048h,004h
    db 085h,0C9h,074h,005h,0E8h,052h,06Ah,0E8h,0FFh,08Bh,088h,0CCh,000h,000h,000h,0F6h
    db 0C5h,020h,074h,036h,0FFh,04Eh,070h,079h,031h,08Bh,046h,06Ch,089h,046h,070h,08Bh
    db 07Fh,010h,08Bh,0CBh,0E8h,0C2h,092h,0E9h,0FFh,051h,08Bh,00Dh,014h,0F2h,02Eh,001h
    db 0D9h,01Ch,024h,057h,0E8h,01Bh,005h,0EBh,0FFh,085h,0C0h,074h,00Dh,05Fh,05Eh,05Dh
    db 0B8h,0FEh,0FFh,0FFh,0FFh,05Bh,083h,0C4h,008h,0C3h,083h,0FDh,0FFh,00Fh,085h,012h
    db 001h,000h,000h,08Bh,04Eh,01Ch,08Bh,051h,010h,08Bh,0BAh,004h,002h,000h,000h,08Bh
    db 0CEh,0E8h,058h,0F2h,0E8h,0FFh,085h,0C0h,089h,046h,060h,075h,015h,08Bh,046h,064h
    db 050h,08Bh,0CFh,0E8h,077h,019h,0EBh,0FFh,05Fh,05Eh,00Bh,0C5h,05Dh,05Bh,083h,0C4h
    db 008h,0C3h,08Bh,0BFh,0CCh,001h,000h,000h,085h,0FFh,00Fh,084h,0A5h,000h,000h,000h
    db 08Bh,047h,004h,085h,0C0h,074h,00Ch,08Bh,048h,004h,085h,0C9h,074h,005h,0E8h,0B8h
    db 069h,0E8h,0FFh,0D9h,080h,0ECh,000h,000h,000h,0D8h,01Dh,050h,053h,007h,001h,0DFh
    db 0E0h,0F6h,0C4h,041h,075h,07Fh,08Bh,0CFh,0E8h,0A0h,075h,0E9h,0FFh,0D8h,005h,03Ch
    db 053h,007h,001h,083h,0ECh,008h,0DDh,01Ch,024h,0FFh,015h,0B8h,093h,035h,001h,0D9h
    db 05Ch,024h,018h,083h,0C4h,008h,0D9h,044h,024h,010h,0DBh,05Ch,024h,014h,08Bh,05Ch
    db 024h,014h,083h,0FBh,001h,07Dh,005h,0BBh,001h,000h,000h,000h,068h,088h,026h,000h
    db 000h,068h,09Ch,076h,009h,001h,08Bh,0FBh,0F7h,0DFh,053h,057h,0E8h,04Dh,062h,0E8h
    db 0FFh,08Dh,00Ch,080h,068h,089h,026h,000h,000h,0D1h,0E1h,089h,04Ch,024h,028h,0DBh
    db 044h,024h,028h,068h,09Ch,076h,009h,001h,053h,057h,0D9h,05Eh,050h,0E8h,02Ch,062h
    db 0E8h,0FFh,08Dh,014h,080h,083h,0C4h,020h,0D1h,0E2h,089h,054h,024h,014h,0DBh,044h
    db 024h,014h,0D9h,05Eh,054h,06Ah,000h,08Bh,0CEh,0E8h,023h,0E4h,0E9h,0FFh,0A0h,039h
    db 002h,02Fh,001h,084h,0C0h,074h,017h,0A1h,0FCh,0D4h,02Eh,001h,085h,0C0h,074h,00Eh
    db 068h,088h,0A0h,009h,001h,050h,0E8h,0BFh,0E7h,0EBh,0FFh,083h,0C4h,008h,08Bh,006h
    db 08Bh,0CEh,0FFh,050h,044h,05Fh,05Eh,05Dh,033h,0C0h,05Bh,083h,0C4h,008h,0C3h
?update@AIPanicState@@UAE?AW4StateReturnType@@XZ ENDP
_TEXT ENDS
END
