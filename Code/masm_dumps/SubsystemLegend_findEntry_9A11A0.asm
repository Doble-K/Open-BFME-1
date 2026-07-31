.386
.model flat
; ?findEntry@SubsystemLegend@@QAEPAUSubsystemLegendEntry@@VAsciiString@@@Z
; Exact 264B @ 0x009A11A0. Byte dump, not source: the C++ body lives in
; Code/GameEngine/Source/Common/System/SubsystemLegend.cpp and is correct to
; 262 of these 264 bytes -- MSVC 7.1 reloads the spilled `this` into ecx at
; 0x009A123C where retail used eax. See that file and docs/lessons.md.
_TEXT SEGMENT
public ?findEntry@SubsystemLegend@@QAEPAUSubsystemLegendEntry@@VAsciiString@@@Z
?findEntry@SubsystemLegend@@QAEPAUSubsystemLegendEntry@@VAsciiString@@@Z PROC
    db 6Ah, 0FFh, 68h, 50h, 00h, 06h, 01h, 64h, 0A1h, 00h, 00h, 00h, 00h, 50h, 64h, 89h
    db 25h, 00h, 00h, 00h, 00h, 83h, 0ECh, 08h, 53h, 55h, 56h, 57h, 89h, 4Ch, 24h, 14h
    db 8Bh, 41h, 08h, 8Bh, 28h, 3Bh, 0E8h, 0C7h, 44h, 24h, 20h, 00h, 00h, 00h, 00h, 74h
    db 76h, 8Dh, 45h, 08h, 50h, 8Dh, 4Ch, 24h, 14h, 0E8h, 82h, 69h, 0EEh, 0FFh, 8Bh, 44h
    db 24h, 28h, 85h, 0C0h, 74h, 09h, 0Fh, 0B7h, 58h, 04h, 8Dh, 78h, 08h, 0EBh, 07h, 33h
    db 0DBh, 0BFh, 8Bh, 38h, 07h, 01h, 8Bh, 44h, 24h, 10h, 85h, 0C0h, 74h, 09h, 0Fh, 0B7h
    db 50h, 04h, 8Dh, 70h, 08h, 0EBh, 07h, 33h, 0D2h, 0BEh, 8Bh, 38h, 07h, 01h, 3Bh, 0D3h
    db 8Bh, 0CAh, 7Ch, 02h, 8Bh, 0CBh, 33h, 0C0h, 0F3h, 0A6h, 74h, 05h, 1Bh, 0C0h, 83h, 0D8h
    db 0FFh, 85h, 0C0h, 75h, 08h, 2Bh, 0D3h, 8Bh, 0C2h, 85h, 0C0h, 74h, 42h, 8Dh, 4Ch, 24h
    db 10h, 0C6h, 44h, 24h, 20h, 00h, 0E8h, 05h, 67h, 0EEh, 0FFh, 8Bh, 44h, 24h, 14h, 8Bh
    db 6Dh, 00h, 3Bh, 68h, 08h, 75h, 8Ah, 8Dh, 4Ch, 24h, 28h, 0C7h, 44h, 24h, 20h, 0FFh
    db 0FFh, 0FFh, 0FFh, 0E8h, 0E8h, 66h, 0EEh, 0FFh, 5Fh, 5Eh, 5Dh, 33h, 0C0h, 5Bh, 8Bh, 4Ch
    db 24h, 08h, 64h, 89h, 0Dh, 00h, 00h, 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h, 8Dh
    db 4Ch, 24h, 10h, 8Dh, 75h, 08h, 0C6h, 44h, 24h, 20h, 00h, 0E8h, 0C0h, 66h, 0EEh, 0FFh
    db 8Dh, 4Ch, 24h, 28h, 0C7h, 44h, 24h, 20h, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 0AFh, 66h, 0EEh
    db 0FFh, 8Bh, 4Ch, 24h, 18h, 5Fh, 8Bh, 0C6h, 5Eh, 5Dh, 5Bh, 64h, 89h, 0Dh, 00h, 00h
    db 00h, 00h, 83h, 0C4h, 14h, 0C2h, 04h, 00h
?findEntry@SubsystemLegend@@QAEPAUSubsystemLegendEntry@@VAsciiString@@@Z ENDP
_TEXT ENDS
END
