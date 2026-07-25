.386
.model flat

; ?updateContextPurchaseScience@ControlBar@@IAEXXZ
; Retail @ 0x0049CAE0 size 139 (masm-dump boundary fix: old row claimed
; 0x49CAE3/136, which starts 3 bytes into the PRECEDING function's
; `mov eax,[ThePlayerList]` instruction - proven via build.read_target_bytes;
; true start is 0x49CAE0, that same mov's opcode byte)
_TEXT SEGMENT
public ?updateContextPurchaseScience@ControlBar@@IAEXXZ
?updateContextPurchaseScience@ControlBar@@IAEXXZ PROC
    db 0A1h, 48h, 0D7h, 2Eh, 01h, 83h, 0ECh, 08h, 53h, 56h, 8Bh, 70h, 0Ch, 57h, 8Bh, 0F9h
    db 8Bh, 0Dh, 40h, 1Bh, 2Fh, 01h, 8Bh, 19h, 8Bh, 0Dh, 00h, 0D6h, 2Eh, 01h, 68h, 10h
    db 0B8h, 0Fh, 01h, 0E8h, 0CFh, 0E2h, 0B9h, 0FFh, 8Bh, 57h, 38h, 8Bh, 0Dh, 40h, 1Bh, 2Fh
    db 01h, 50h, 52h, 0FFh, 93h, 0DCh, 00h, 00h, 00h, 8Bh, 0F8h, 85h, 0FFh, 74h, 45h, 0D9h
    db 86h, 5Ch, 02h, 00h, 00h, 83h, 0ECh, 08h, 0DDh, 1Ch, 24h, 0FFh, 15h, 0B8h, 93h, 35h
    db 01h, 0D9h, 5Ch, 24h, 14h, 83h, 0C4h, 08h, 0D9h, 44h, 24h, 0Ch, 0DBh, 5Ch, 24h, 10h
    db 8Bh, 8Eh, 6Ch, 02h, 00h, 00h, 8Bh, 44h, 24h, 10h, 8Bh, 0B6h, 68h, 02h, 00h, 00h
    db 2Bh, 0C1h, 6Bh, 0C0h, 64h, 99h, 2Bh, 0F1h, 0F7h, 0FEh, 50h, 57h, 0E8h, 19h, 50h, 0B8h
    db 0FFh, 83h, 0C4h, 08h, 5Fh, 5Eh, 5Bh, 83h, 0C4h, 08h, 0C3h
?updateContextPurchaseScience@ControlBar@@IAEXXZ ENDP
_TEXT ENDS
END
