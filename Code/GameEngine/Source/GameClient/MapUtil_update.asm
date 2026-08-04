.386
.model flat

; ?update@WaypointMap@@QAEXXZ
; Exact 366 retail bytes @ 0x00454EF0 (int3-delimited 0x454EEF/0x45505E, ret 0x45505D).
; Queue 0x00454EF0/361 and the old marker's 363 both underestimate; the real body
; ends at the `ret` 0x45505D (add esp,0x14; ret), 0x16E bytes.
; C++ blocked: ESP-relative SEH frame (handler 0x01023FB8, unwind state slot
; [esp+0x14]) wrapping AsciiString temporaries; the loop's format call is the
; AsciiString(AsciiString,...) by-value-overload shape (temp.set("Player_%d_Start")
; then format(&startingCamName, &temp, va_list i+1)) that needs BFME's 8-byte
; AsciiStringData + out-of-line set/format_va/releaseBuffer shim, which would
; invalidate the TU's other matched rows; out-of-line STLport map ops
; find@0x78BFE0 / operator[]@0x4C0D00 / _M_erase@0x477390; StaticNameKey lazy-key
; global @0x12A7A00 with out-of-line key()@0x490290 and keyToName@0x48FD30.
_TEXT SEGMENT
public ?update@WaypointMap@@QAEXXZ
?update@WaypointMap@@QAEXXZ PROC
    db 6Ah,0FFh,64h,0A1h,00h,00h,00h,00h,68h,0B8h,3Fh,02h,01h,50h,0A1h,88h
    db 15h,2Fh,01h,64h,89h,25h,00h,00h,00h,00h,83h,0ECh,08h,53h,55h,56h
    db 57h,33h,0FFh,3Bh,0C7h,8Bh,0D9h,75h,1Ah,0C7h,43h,0Ch,01h,00h,00h,00h
    db 8Bh,4Ch,24h,18h,64h,89h,0Dh,00h,00h,00h,00h,5Fh,5Eh,5Dh,5Bh,83h
    db 0C4h,14h,0C3h,39h,7Bh,04h,74h,1Fh,8Bh,03h,8Bh,48h,04h,51h,8Bh,0CBh
    db 0E8h,61h,0E4h,0BEh,0FFh,8Bh,03h,89h,40h,08h,8Bh,13h,89h,7Ah,04h,8Bh
    db 03h,89h,40h,0Ch,89h,7Bh,04h,0B9h,00h,7Ah,2Ah,01h,0E8h,0A3h,43h,0BBh
    db 0FFh,8Bh,0Dh,00h,0D6h,2Eh,01h,50h,8Dh,44h,24h,14h,50h,0E8h,08h,9Dh
    db 0BEh,0FFh,8Bh,2Dh,88h,15h,2Fh,01h,8Dh,4Ch,24h,10h,51h,8Bh,0CDh,89h
    db 7Ch,24h,24h,0E8h,27h,0BBh,0BBh,0FFh,8Bh,0F0h,3Bh,75h,00h,74h,1Fh,8Dh
    db 54h,24h,10h,52h,8Bh,0CBh,0E8h,0FCh,7Dh,0BBh,0FFh,83h,0C6h,14h,8Bh,0Eh
    db 89h,08h,8Bh,56h,04h,89h,50h,04h,8Bh,4Eh,08h,89h,48h,08h,8Dh,6Bh
    db 0Ch,89h,7Dh,00h,33h,0C0h,8Dh,70h,01h,56h,51h,89h,64h,24h,1Ch,8Bh
    db 0CCh,68h,0E4h,32h,08h,01h,0E8h,0F5h,3Bh,43h,00h,8Dh,54h,24h,18h,52h
    db 0E8h,1Bh,40h,43h,00h,8Bh,0Dh,88h,15h,2Fh,01h,83h,0C4h,0Ch,8Dh,44h
    db 24h,10h,50h,0E8h,0C7h,0BAh,0BBh,0FFh,8Bh,0Dh,88h,15h,2Fh,01h,8Bh,0F8h
    db 3Bh,39h,74h,2Dh,8Dh,54h,24h,10h,52h,8Bh,0CBh,0E8h,97h,7Dh,0BBh,0FFh
    db 83h,0C7h,14h,8Bh,0Fh,89h,08h,8Bh,57h,04h,89h,50h,04h,8Bh,4Fh,08h
    db 89h,48h,08h,8Bh,55h,00h,42h,8Bh,0C6h,83h,0F8h,08h,89h,55h,00h,7Ch
    db 95h,83h,7Dh,00h,01h,0C7h,44h,24h,14h,01h,00h,00h,00h,8Dh,44h,24h
    db 14h,7Ch,02h,8Bh,0C5h,8Bh,10h,8Dh,4Ch,24h,10h,89h,55h,00h,0C7h,44h
    db 24h,20h,0FFh,0FFh,0FFh,0FFh,0E8h,0F5h,28h,43h,00h,8Bh,4Ch,24h,18h,5Fh
    db 5Eh,5Dh,64h,89h,0Dh,00h,00h,00h,00h,5Bh,83h,0C4h,14h,0C3h
?update@WaypointMap@@QAEXXZ ENDP
_TEXT ENDS
END
