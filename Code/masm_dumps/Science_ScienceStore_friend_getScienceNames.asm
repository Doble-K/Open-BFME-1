.386
.model flat

; ?friend_getScienceNames@ScienceStore@@QBE?AV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@XZ
; Exact 259B @ 0x000E81F0; ghidra FUN_004e81f0 size 259 (queue 295 included trailing int3).
; Identity: m_sciences[this+8..+c] loop; getFinalOverride; m_science@+0xc; TheNameKeyGenerator@0x12ed600 keyToName;
; AsciiString copy@0x887B60; vector return (ret 4). Matches ZH friend_getScienceNames semantics.
; C++ shape drift (sub esp 0x1c vs 0x14 + AsciiString/STL codegen); MASM exact dump.
_TEXT SEGMENT
public ?friend_getScienceNames@ScienceStore@@QBE?AV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@XZ
?friend_getScienceNames@ScienceStore@@QBE?AV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@XZ PROC
    db 6Ah,0FFh,68h,1Ah,0B3h,0FFh,00h,64h,0A1h,00h,00h,00h,00h,50h,64h,89h
    db 25h,00h,00h,00h,00h,83h,0ECh,1Ch,53h,33h,0DBh,56h,89h,5Ch,24h,0Ch
    db 57h,8Bh,0F9h,89h,5Ch,24h,1Ch,89h,5Ch,24h,20h,89h,5Ch,24h,24h,8Bh
    db 77h,08h,3Bh,77h,0Ch,0C7h,44h,24h,30h,01h,00h,00h,00h,0Fh,84h,85h
    db 00h,00h,00h,8Bh,06h,8Bh,48h,04h,3Bh,0CBh,74h,05h,0E8h,7Ah,0A0h,0F1h
    db 0FFh,8Bh,40h,0Ch,8Bh,0Dh,00h,0D6h,2Eh,01h,50h,8Dh,44h,24h,10h,50h
    db 0E8h,25h,6Ah,0F5h,0FFh,8Bh,4Ch,24h,20h,3Bh,4Ch,24h,24h,0C6h,44h,24h
    db 30h,02h,74h,24h,89h,4Ch,24h,14h,89h,4Ch,24h,18h,3Bh,0CBh,0C6h,44h
    db 24h,30h,03h,74h,0Ah,50h,0E8h,0E5h,0F8h,79h,00h,8Bh,4Ch,24h,20h,83h
    db 0C1h,04h,89h,4Ch,24h,20h,0EBh,14h,6Ah,01h,6Ah,01h,8Dh,54h,24h,40h
    db 52h,50h,51h,8Dh,4Ch,24h,30h,0E8h,0DFh,0FFh,0F4h,0FFh,8Dh,4Ch,24h,0Ch
    db 0C6h,44h,24h,30h,01h,0E8h,96h,0F6h,79h,00h,8Bh,47h,0Ch,83h,0C6h,04h
    db 3Bh,0F0h,0Fh,85h,7Bh,0FFh,0FFh,0FFh,8Bh,74h,24h,38h,8Dh,44h,24h,1Ch
    db 50h,8Bh,0CEh,0E8h,0ACh,0D1h,0F2h,0FFh,8Dh,4Ch,24h,1Ch,0C7h,44h,24h,10h
    db 01h,00h,00h,00h,88h,5Ch,24h,30h,0E8h,0D5h,0E7h,0F3h,0FFh,8Bh,4Ch,24h
    db 28h,5Fh,8Bh,0C6h,5Eh,5Bh,64h,89h,0Dh,00h,00h,00h,00h,83h,0C4h,28h
    db 0C2h,04h,00h
?friend_getScienceNames@ScienceStore@@QBE?AV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@XZ ENDP
_TEXT ENDS
END
