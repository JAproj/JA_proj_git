;-------------------------------------------------------------------------

.386 
.MODEL FLAT, STDCALL
  
OPTION CASEMAP:NONE  

INCLUDE    \masm32\include\windows.inc   

.DATA

i DWORD ?
j DWORD ?

.CODE  

DllEntry PROC hInstDLL:HINSTANCE, reason:PTR DWORD, reserved1:DWORD  

    mov eax, TRUE
	ret  
DllEntry ENDP  

;-------------------------------------------------------------------------

MyFuncAsm proc tabSize: dword, table: ptr dword			;dane wejciowe

push esi								;rejestr �r�d�owy odk�adam na stos

	mov eax, dword ptr [table]			;adres pierwszego elementu tablicy do eax
	mov i, 0							;zerowanie zmiennej i

for1:
	mov ecx, tabSize					;rozmiar tablicy do ecx
	mov j, 0							;zerowanie zmiennej j
	cmp [i], ecx						;por�wnanie warto�ci i z tabSize
	jge koniec							;gdy i >= tabSize skok do etykiety koniec
	
	dec ecx								;tabSize = tabSize-1
	sub ecx, [i]						;w ecx tabSize-1-i
for2:
	cmp [j], ecx						;por�wnanie warto�ci j z tabSize-1-i
	jge zwiekszi						;gdy j >= tabSize-1-i skok do zwiekszi

iif1:	
	mov esi, [j]						;warto�� zmiennej j do esi 
	mov ebx, dword ptr [eax + esi*4]	;do ebx table[j]
	mov edx, dword ptr [eax + esi*4+4]	;do edx table[j+1]
	cmp ebx, edx						;por�wnaj table[j] z table[j+1]
	jge zamien							;gdy table[j] >= table[j+1] skok do zamien

zwiekszj:
	inc [j]								;zwi�ksz warto�� zmiennej j
	jmp for2							;skok bezwarunkowy do for2

zamien:
	mov dword ptr [eax + esi*4], edx	;table[j] = table[j+1]
	mov dword ptr [eax + esi*4+4], ebx	;table[j+1] = table[j]
	jmp zwiekszj						;skok bezwarunkowy do etykiety zwiekszj

zwiekszi:
	inc [i]								;zwi�ksz warto�� zmiennej i
	jmp for1							;skok bezwarunkowy do etykiety for1

koniec:
	mov eax, dword ptr [table]			;zwr�� tablic� przez akumulator 
 
pop esi									;pobieram ze stosu rejestr �r�d�owy
ret										;powr�t
MyFuncAsm endp  

;-------------------------------------------------------------------------

END DllEntry  

;-------------------------------------------------------------------------