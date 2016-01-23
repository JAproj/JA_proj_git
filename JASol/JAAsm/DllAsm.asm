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

push esi								;rejestr Ÿród³owy odk³adam na stos

	mov eax, dword ptr [table]			;adres pierwszego elementu tablicy do eax
	mov i, 0							;zerowanie zmiennej i

for1:
	mov ecx, tabSize					;rozmiar tablicy do ecx
	mov j, 0							;zerowanie zmiennej j
	cmp [i], ecx						;porównanie wartoœci i z tabSize
	jge koniec							;gdy i >= tabSize skok do etykiety koniec
	
	dec ecx								;tabSize = tabSize-1
	sub ecx, [i]						;w ecx tabSize-1-i
for2:
	cmp [j], ecx						;porównanie wartoœci j z tabSize-1-i
	jge zwiekszi						;gdy j >= tabSize-1-i skok do zwiekszi

iif1:	
	mov esi, [j]						;wartoœæ zmiennej j do esi 
	mov ebx, dword ptr [eax + esi*4]	;do ebx table[j]
	mov edx, dword ptr [eax + esi*4+4]	;do edx table[j+1]
	cmp ebx, edx						;porównaj table[j] z table[j+1]
	jge zamien							;gdy table[j] >= table[j+1] skok do zamien

zwiekszj:
	inc [j]								;zwiêksz wartoœæ zmiennej j
	jmp for2							;skok bezwarunkowy do for2

zamien:
	mov dword ptr [eax + esi*4], edx	;table[j] = table[j+1]
	mov dword ptr [eax + esi*4+4], ebx	;table[j+1] = table[j]
	jmp zwiekszj						;skok bezwarunkowy do etykiety zwiekszj

zwiekszi:
	inc [i]								;zwiêksz wartoœæ zmiennej i
	jmp for1							;skok bezwarunkowy do etykiety for1

koniec:
	mov eax, dword ptr [table]			;zwróæ tablicê przez akumulator 
 
pop esi									;pobieram ze stosu rejestr Ÿród³owy
ret										;powrót
MyFuncAsm endp  

;-------------------------------------------------------------------------

END DllEntry  

;-------------------------------------------------------------------------