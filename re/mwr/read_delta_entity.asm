7246f0  push rbp; MSG_ReadDeltaEntity(msg_t*, int, entityState_s const*, entityState_s*, int, int, int)
7246f1  mov rbp, rsp
7246f4  push r15
7246f6  push r14
7246f8  push r13
7246fa  push r12
7246fc  push rbx
7246fd  sub rsp, 168h
724704  mov r14, cs:COMMON
72470b  mov rbx, rdx
72470e  mov r13d, r8d
724711  mov r12, rdi
724714  mov [rbp+var_138], rcx
72471b  mov [rbp+var_144], esi
724721  test rbx, rbx
724724  mov rax, [r14]
724727  mov [rbp+var_30], rax
72472b  jz short loc_72473C
72472d  test r9d, r9d
724730  jnz short loc_72473C
724732  xor esi, esi
724734  mov rdi, rbx
724737  call SV_ValidateEntityState
72473c  cmp r13d, 800h
724743  jb short loc_724768
724745  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
72474c  lea rcx, aS_490; "%s"
724753  lea r8, aNumber1uGentit; "number < (1u << GENTITYNUM_BITS)"
72475a  mov esi, 875h
72475f  xor edx, edx
724761  xor eax, eax
724763  call MyAssertHandler
724768  mov rdi, r12
72476b  call MSG_ReadBit
724770  cmp eax, 1
724773  jnz short loc_7247B6
724775  lea rax, unk_337E2E0
72477c  mov rax, [rax]
72477f  test rax, rax
724782  jz short loc_7247AC
724784  mov eax, [rax+18h]
724787  cmp eax, 1
72478a  jg short loc_724791
72478c  cmp eax, 0FFFFFFFFh
72478f  jnz short loc_7247AC
724791  mov edx, [r12+24h]
724796  lea rsi, a3i3iRemove; "%3i: #%-3i remove\n"
72479d  mov edi, 19h
7247a2  xor eax, eax
7247a4  mov ecx, r13d
7247a7  call Com_Printf
7247ac  mov ebx, 1
7247b1  jmp loc_724EFE
7247b6  mov rdi, r12
7247b9  call MSG_ReadBit
7247be  test eax, eax
7247c0  jz loc_7249AC
7247c6  lea r15, g_netFieldList
7247cd  mov rax, [r15]
7247d0  cmp dword ptr [rax+68h], 49h ; 'I'
7247d4  jb short loc_7247FC
7247d6  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
7247dd  lea rcx, aS_490; "%s"
7247e4  lea r8, aGNetfieldlistN; "g_netFieldList[NET_FIELD_TYPE_ENTITY_ST"...
7247eb  mov esi, 896h
7247f0  xor edx, edx
7247f2  xor eax, eax
7247f4  call MyAssertHandler
7247f9  mov rax, [r15]
7247fc  mov r15, [rax+60h]
724800  mov rdi, r12
724803  call MSG_ReadBit
724808  mov [rbp+var_15C], eax
72480e  mov eax, 48h ; 'H'
724813  mov esi, 20h ; ' '
724818  mov rdi, r12
72481b  lzcnt eax, eax
72481f  sub esi, eax
724821  call MSG_ReadBits
724826  mov ecx, eax
724828  cmp ecx, 48h ; 'H'
72482b  jge loc_7249C5
724831  lea rax, unk_337E2E0
724838  mov [rbp+var_140], rcx
72483f  mov rax, [rax]
724842  test rax, rax
724845  jz short loc_724873
724847  mov eax, [rax+18h]
72484a  cmp eax, 1
72484d  jg short loc_724854
72484f  cmp eax, 0FFFFFFFFh
724852  jnz short loc_724873
724854  mov edx, [r12+24h]
724859  mov rcx, [rbp+var_140]
724860  lea rsi, a3iLcD; "%3i: lc %d\n"
724867  mov edi, 19h
72486c  xor eax, eax
72486e  call Com_Printf
724873  mov rax, [rbp+var_138]
72487a  movzx edx, r13w
72487e  cmp edx, r13d
724881  mov [rax], r13w
724885  jz short loc_7248C1
724887  lea rdi, aValueDUnsigned; "value %d != *(unsigned short*)i %d"
72488e  xor eax, eax
724890  mov esi, r13d
724893  call va
724898  mov r9, rax
72489b  lea rdi, aDH1CodeSourceR_1270; "D:\\h1\\code_source\\Runtime\\qcommon/."...
7248a2  lea rcx, aSS_238; "%s\n\t%s"
7248a9  lea r8, aValueUnsignedS; "value == *(unsigned short*)i"
7248b0  mov esi, 229h
7248b5  mov edx, 0
7248ba  xor eax, eax
7248bc  call MyAssertHandler
7248c1  mov rdi, [r15]
7248c4  lea rsi, aEtype; "eType"
7248cb  call PLstrcmp
7248d0  test eax, eax
7248d2  jz short loc_7248F7
7248d4  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
7248db  lea rcx, aS_490; "%s"
7248e2  lea r8, aStrcmpEsfield0; "strcmp( esField[0].name, \"eType\" ) =="...
7248e9  mov esi, 8B0h
7248ee  xor edx, edx
7248f0  xor eax, eax
7248f2  call MyAssertHandler
7248f7  movzx eax, word ptr [r15+0Ch]
7248fc  mov [rbp+var_158], rbx
724903  cmp eax, 0FFB3h
724908  jz short loc_72492D
72490a  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
724911  lea rcx, aS_490; "%s"
724918  lea r8, aEsfield0BitsMs; "esField[0].bits == MSG_FIELD_ETYPE"
72491f  mov esi, 8B2h
724924  xor edx, edx
724926  xor eax, eax
724928  call MyAssertHandler
72492d  mov rax, [rbp+var_140]
724934  mov esi, 3
724939  mov rdi, r12
72493c  lea edx, [rax+1]
72493f  call MSG_ReadNumFieldsSkipped
724944  mov ebx, eax
724946  test ebx, ebx
724948  jg short loc_724973
72494a  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
724951  lea rcx, aSNextchangedI; "%s\n\t(nextChanged) = %i"
724958  lea r8, aNextchanged0; "(nextChanged > 0)"
72495f  mov esi, 8BCh
724964  mov edx, 0
724969  xor eax, eax
72496b  mov r9d, ebx
72496e  call MyAssertHandler
724973  dec ebx
724975  cmp ebx, 48h ; 'H'
724978  jl loc_724A40
72497e  mov rdi, r12
724981  call MSG_Discard
724986  lea rsi, aGotNextchanged; "Got nextChanged field of %i, but there "...
72498d  mov edi, 19h
724992  mov ecx, 48h ; 'H'
724997  xor eax, eax
724999  mov edx, ebx
72499b  call Com_PrintError
7249a0  mov r15, [rbp+var_138]
7249a7  jmp loc_724EF2
7249ac  mov r15, [rbp+var_138]
7249b3  mov edx, 100h
7249b8  mov rsi, rbx
7249bb  mov rdi, r15
7249be  call Com_Memcpy
7249c3  jmp short loc_724A30
7249c5  lea rdi, aLastchangedWas; "lastChanged was %i, totalFields is %i\n"
7249cc  mov edx, 48h ; 'H'
7249d1  xor eax, eax
7249d3  mov esi, ecx
7249d5  mov r15, rcx
7249d8  call va
7249dd  mov r9, rax
7249e0  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
7249e7  lea rcx, aSS_238; "%s\n\t%s"
7249ee  lea r8, aLastchangedTot; "lastChanged < totalFields"
7249f5  mov esi, 3E9h
7249fa  mov edx, 0
7249ff  xor eax, eax
724a01  call MyAssertHandler
724a06  mov rdi, r12
724a09  call MSG_Discard
724a0e  lea rsi, aGotLastchanged; "Got lastChanged field of %i, but there "...
724a15  mov edi, 19h
724a1a  mov ecx, 48h ; 'H'
724a1f  xor eax, eax
724a21  mov edx, r15d
724a24  call Com_PrintError
724a29  mov r15, [rbp+var_138]
724a30  xor ebx, ebx
724a32  test r15, r15
724a35  jnz loc_724EF2
724a3b  jmp loc_724EFE
724a40  mov [rbp+var_170], r15
724a47  mov r15d, [rbp+arg_0]
724a4b  mov [rbp+var_150], r12
724a52  mov [rbp+var_180], r13
724a59  test ebx, ebx
724a5b  jz short loc_724A8A
724a5d  mov [rbp+var_148], ebx
724a63  mov rbx, [rbp+var_138]
724a6a  mov rdi, [rbp+var_170]
724a71  mov rsi, [rbp+var_158]
724a78  xor ecx, ecx
724a7a  mov rdx, rbx
724a7d  call MSG_CopyFieldOver
724a82  mov r13d, 0FFFFFFFFh
724a88  jmp short loc_724AEE
724a8a  mov r14, [rbp+var_150]
724a91  mov rbx, [rbp+var_138]
724a98  mov esi, [rbp+var_144]
724a9e  mov rdx, [rbp+var_158]
724aa5  mov r8, [rbp+var_170]
724aac  xor r9d, r9d
724aaf  mov [rsp+190h+var_190], 0
724ab6  xor r13d, r13d
724ab9  mov rdi, r14
724abc  mov rcx, rbx
724abf  call MSG_ReadDeltaField
724ac4  mov rdx, [rbp+var_140]
724acb  test edx, edx
724acd  jle short loc_724AE4
724acf  mov esi, 3
724ad4  mov rdi, r14
724ad7  call MSG_ReadNumFieldsSkipped
724adc  mov [rbp+var_148], eax
724ae2  jmp short loc_724AEE
724ae4  mov [rbp+var_148], 0
724aee  mov r14b, [rbx+0Ch]
724af2  mov [rbp+var_138], rbx
724af9  movzx ebx, r14b
724afd  mov edi, ebx
724aff  call MSG_GetStateFieldListForEntityType
724b04  mov r12, [rax]
724b07  mov edx, [rax+8]
724b0a  test r15d, r15d
724b0d  jz loc_724BB8
724b13  mov rax, [rbp+var_158]
724b1a  mov r9, [rbp+var_140]
724b21  mov r10d, [rbp+var_148]
724b28  dec r14b; switch 6 cases
724b2b  lea r15, [rbp+var_130]
724b32  vmovups ymm0, ymmword ptr [rax+0E0h]
724b3a  vmovups [rbp+var_50], ymm0
724b3f  vmovups ymm0, ymmword ptr [rax+0C0h]
724b47  vmovups [rbp+var_70], ymm0
724b4c  vmovups ymm0, ymmword ptr [rax+0A0h]
724b54  vmovups [rbp+var_90], ymm0
724b5c  vmovups ymm0, ymmword ptr [rax+80h]
724b64  vmovups [rbp+var_B0], ymm0
724b6c  vmovups ymm0, ymmword ptr [rax]
724b70  vmovups ymm1, ymmword ptr [rax+20h]
724b75  vmovups ymm2, ymmword ptr [rax+40h]
724b7a  vmovups ymm3, ymmword ptr [rax+60h]
724b7f  movzx eax, r14b
724b83  cmp eax, 5
724b86  vmovups [rbp+var_D0], ymm3
724b8e  vmovups [rbp+var_F0], ymm2
724b96  vmovups [rbp+var_110], ymm1
724b9e  vmovups [rbp+var_130], ymm0
724ba6  jbe short loc_724BD4
724ba8  cmp ebx, 12h; jumptable 0000000000724BE4 default case
724bab  mov ebx, edx
724bad  jnz loc_724C92; jumptable 0000000000724BE4 cases 4,5
724bb3  jmp loc_724C4F; jumptable 0000000000724BE4 case 2
724bb8  mov r15, [rbp+var_158]
724bbf  mov r9, [rbp+var_140]
724bc6  mov r10d, [rbp+var_148]
724bcd  mov ebx, edx
724bcf  jmp loc_724C92; jumptable 0000000000724BE4 cases 4,5
724bd4  lea rcx, jpt_724BE4
724bdb  mov ebx, edx
724bdd  movsxd rax, ds:(jpt_724BE4 - 0F9B93Ch)[rcx+rax*4]
724be1  add rax, rcx
724be4  jmp rax; switch jump
724be6  mov rax, [rbp+var_180]; jumptable 0000000000724BE4 case 1
724bed  mov edi, eax
724bef  movsx rax, al
724bf3  cmp rdi, rax
724bf6  jz short loc_724C15
724bf8  lea rsi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
724bff  mov edx, 8EDh
724c04  mov r14, r9
724c07  mov r15d, r10d
724c0a  call truncate_cast_assert_with_info
724c0f  mov r10d, r15d
724c12  mov r9, r14
724c15  mov rax, [rbp+var_180]
724c1c  mov word ptr [rbp+var_130+6], 7FEh
724c25  mov byte ptr [rbp+var_130+0Dh], 7
724c2c  mov dword ptr [rbp+var_F0+1Ch], 3
724c36  mov dword ptr [rbp+var_B0], 1
724c40  lea r15, [rbp+var_130]
724c47  mov byte ptr [rbp+var_130+0Eh], al
724c4d  jmp short loc_724C92; jumptable 0000000000724BE4 cases 4,5
724c4f  mov word ptr [rbp+var_130+6], 7FEh; jumptable 0000000000724BE4 case 2
724c58  lea r15, [rbp+var_130]
724c5f  mov byte ptr [rbp+var_130+0Dh], 7
724c66  jmp short loc_724C92; jumptable 0000000000724BE4 cases 4,5
724c68  mov word ptr [rbp+var_130+6], 7FEh; jumptable 0000000000724BE4 case 3
724c71  lea r15, [rbp+var_130]
724c78  mov byte ptr [rbp+var_130+0Eh], 2Ah ; '*'
724c7f  jmp short loc_724C92; jumptable 0000000000724BE4 cases 4,5
724c81  lea r15, [rbp+var_130]; jumptable 0000000000724BE4 case 6
724c88  mov dword ptr [rbp+var_90+4], 7FFh
724c92  cmp r9d, ebx; jumptable 0000000000724BE4 cases 4,5
724c95  jge loc_724EBF
724c9b  mov r14, [rbp+var_138]
724ca2  mov rax, 1807E000001h
724cac  mov [rbp+var_184], ebx
724cb2  test r9d, r9d
724cb5  mov [rbp+var_178], rax
724cbc  jz loc_724F22
724cc2  cmp r13d, r9d
724cc5  jnz short loc_724CEF
724cc7  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
724cce  lea rcx, aLastchangedLcI; "lastChanged != lc\n\t%i, %i"
724cd5  mov esi, 90Bh
724cda  mov edx, 0
724cdf  xor eax, eax
724ce1  mov r8d, r9d
724ce4  mov ebx, r10d
724ce7  call MyAssertHandler
724cec  mov r10d, ebx
724cef  cmp [rbp+var_15C], 0
724cf6  mov rcx, 1FFFFFFFFFFh
724d00  mov rax, 1807E000001h
724d0a  setz byte ptr [rbp+var_158]
724d11  and rcx, rax
724d14  mov [rbp+var_168], rcx
724d1b  jmp short loc_724D4F
724d20  mov r9, [rbp+var_140]
724d27  mov esi, 924h
724d2c  mov edx, 0
724d31  xor eax, eax
724d33  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
724d3a  lea rcx, aNextchangedLcI; "nextChanged <= lc\n\t%i, %i"
724d41  mov r8d, r10d
724d44  mov ebx, r10d
724d47  call MyAssertHandler
724d4c  mov r10d, ebx
724d4f  mov ebx, r13d
724d52  mov r13d, r10d
724d55  inc ebx
724d57  cmp ebx, r13d
724d5a  jge short loc_724D77
724d5c  nop dword ptr [rax+00h]
724d60  mov rdi, r12
724d63  mov rsi, r15
724d66  mov rdx, r14
724d69  mov ecx, ebx
724d6b  call MSG_CopyFieldOver
724d70  inc ebx
724d72  cmp r13d, ebx
724d75  jnz short loc_724D60
724d77  movzx eax, byte ptr [r14+0Ch]
724d7c  movzx edx, byte ptr [r15+0Ch]
724d81  movsxd rcx, r13d
724d84  shl rcx, 4
724d88  lea r8, [r12+rcx]
724d8c  cmp edx, eax
724d8e  setnz al
724d91  mov dl, al
724d93  or dl, byte ptr [rbp+var_158]
724d99  jnz short loc_724DBA
724d9b  movsx ecx, word ptr [r12+rcx+0Ch]
724da1  add ecx, 6Ch ; 'l'
724da4  cmp ecx, 28h ; '('
724da7  ja short loc_724DB8
724da9  mov rax, [rbp+var_168]
724db0  shr rax, cl
724db3  and eax, 1
724db6  jmp short loc_724DBA
724db8  xor eax, eax
724dba  mov rbx, [rbp+var_150]
724dc1  mov esi, [rbp+var_144]
724dc7  movzx eax, al
724dca  xor r9d, r9d
724dcd  mov rdx, r15
724dd0  mov rcx, r14
724dd3  mov [rsp+190h+var_190], eax
724dd6  mov rdi, rbx
724dd9  call MSG_ReadDeltaField
724dde  mov r9, [rbp+var_140]
724de5  mov edx, r9d
724de8  sub edx, r13d
724deb  jle loc_724F1F
724df1  mov rdi, rbx
724df4  mov esi, 3
724df9  mov rbx, r9
724dfc  call MSG_ReadNumFieldsSkipped
724e01  mov rdx, rbx
724e04  mov ebx, eax
724e06  lea r10d, [rbx+r13]
724e0a  cmp edx, r10d
724e0d  jge short loc_724E5B
724e0f  xor eax, eax
724e11  lea rdi, aNextchangedIsI; "nextChanged is %i, lc is %i"
724e18  mov esi, r10d
724e1b  mov [rbp+var_148], r10d
724e22  call va
724e27  mov r9, rax
724e2a  mov esi, 922h
724e2f  xor edx, edx
724e31  xor eax, eax
724e33  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
724e3a  lea rcx, aSS_238; "%s\n\t%s"
724e41  lea r8, aLcNextchanged; "lc >= nextChanged"
724e48  call MyAssertHandler
724e4d  mov r10d, [rbp+var_148]
724e54  mov rdx, [rbp+var_140]
724e5b  test ebx, ebx
724e5d  jg short loc_724EB1
724e5f  xor eax, eax
724e61  lea rdi, aNextchangedIsI_0; "nextChanged is %i, lastChanged is %i"
724e68  mov esi, r10d
724e6b  mov edx, r13d
724e6e  mov [rbp+var_148], r10d
724e75  call va
724e7a  mov rbx, rax
724e7d  mov esi, 923h
724e82  xor edx, edx
724e84  xor eax, eax
724e86  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
724e8d  lea rcx, aSS_238; "%s\n\t%s"
724e94  lea r8, aNextchangedLas; "nextChanged > lastChanged"
724e9b  mov r9, rbx
724e9e  call MyAssertHandler
724ea3  mov r10d, [rbp+var_148]
724eaa  mov rdx, [rbp+var_140]
724eb1  cmp edx, r10d
724eb4  jge loc_724D4F
724eba  jmp loc_724D20
724ebf  lea rsi, aLastChangedFie; "Last changed field was %i, but there ar"...
724ec6  mov edi, 0Eh
724ecb  xor eax, eax
724ecd  mov edx, r9d
724ed0  mov ecx, ebx
724ed2  call Com_Printf
724ed7  mov rax, [rbp+var_150]
724ede  mov r14, cs:COMMON
724ee5  mov r15, [rbp+var_138]
724eec  mov dword ptr [rax], 1
724ef2  xor esi, esi
724ef4  mov rdi, r15
724ef7  xor ebx, ebx
724ef9  call SV_ValidateEntityState
724efe  mov rax, [r14]
724f01  cmp rax, [rbp+var_30]
724f05  jnz loc_725180
724f0b  mov eax, ebx
724f0d  add rsp, 168h
724f14  pop rbx
724f15  pop r12
724f17  pop r13
724f19  pop r14
724f1b  pop r15
724f1d  pop rbp
724f1e  retn
724f1f  mov r10d, r13d
724f22  cmp r10d, r9d
724f25  jz short loc_724F4F
724f27  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
724f2e  lea rcx, aNextchangedLcI_0; "nextChanged == lc\n\t%i, %i"
724f35  mov esi, 928h
724f3a  mov edx, 0
724f3f  xor eax, eax
724f41  mov r8d, r10d
724f44  mov ebx, r10d
724f47  call MyAssertHandler
724f4c  mov r10d, ebx
724f4f  test r10d, r10d
724f52  jle loc_724FF9
724f58  cmp [rbp+var_15C], 0
724f5f  mov rax, 1FFFFFFFFFFh
724f69  mov rbx, r12
724f6c  mov r14d, r10d
724f6f  setz byte ptr [rbp+var_140]
724f76  and [rbp+var_178], rax
724f7d  nop dword ptr [rax]
724f80  test byte ptr [rbx+0Eh], 2
724f84  jz short loc_724FF0
724f86  mov rax, [rbp+var_138]
724f8d  movzx ecx, byte ptr [r15+0Ch]
724f92  mov r13d, r10d
724f95  movzx eax, byte ptr [rax+0Ch]
724f99  cmp ecx, eax
724f9b  setnz al
724f9e  mov cl, al
724fa0  or cl, byte ptr [rbp+var_140]
724fa6  jnz short loc_724FC5
724fa8  movsx ecx, word ptr [rbx+0Ch]
724fac  add ecx, 6Ch ; 'l'
724faf  cmp ecx, 28h ; '('
724fb2  ja short loc_724FC3
724fb4  mov rax, [rbp+var_178]
724fbb  shr rax, cl
724fbe  and eax, 1
724fc1  jmp short loc_724FC5
724fc3  xor eax, eax
724fc5  mov rdi, [rbp+var_150]
724fcc  mov esi, [rbp+var_144]
724fd2  mov rcx, [rbp+var_138]
724fd9  movzx eax, al
724fdc  xor r9d, r9d
724fdf  mov rdx, r15
724fe2  mov r8, rbx
724fe5  mov [rsp+190h+var_190], eax
724fe8  call MSG_ReadDeltaField
724fed  mov r10d, r13d
724ff0  add rbx, 10h
724ff4  dec r14d
724ff7  jnz short loc_724F80
724ff9  test r10d, r10d
724ffc  jns short loc_725027
724ffe  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
725005  lea rcx, aS_490; "%s"
72500c  lea r8, aNextchanged0_0; "nextChanged >= 0"
725013  mov esi, 93Fh
725018  xor edx, edx
72501a  xor eax, eax
72501c  mov ebx, r10d
72501f  call MyAssertHandler
725024  mov r10d, ebx
725027  mov r14d, [rbp+var_184]
72502e  mov r13, [rbp+var_138]
725035  inc r10d
725038  cmp r10d, r14d
72503b  jge short loc_72505F
72503d  nop dword ptr [rax]
725040  mov rdi, r12
725043  mov rsi, r15
725046  mov rdx, r13
725049  mov ecx, r10d
72504c  mov ebx, r10d
72504f  call MSG_CopyFieldOver
725054  mov r10d, ebx
725057  inc r10d
72505a  cmp r14d, r10d
72505d  jnz short loc_725040
72505f  lea rax, unk_BA57FC0
725066  mov r14, cs:COMMON
72506d  mov r15, r13
725070  mov rax, [rax]
725073  cmp byte ptr [rax+18h], 0
725077  jz short loc_7250E8
725079  mov rcx, [rbp+var_170]
725080  movzx eax, word ptr [rcx+8]
725084  movsx ecx, word ptr [rcx+0Ah]
725088  add ecx, 4; switch 9 cases
72508b  cmp ecx, 8
72508e  ja short def_72509E; jumptable 000000000072509E default case, cases -3,0,3
725090  lea rdx, jpt_72509E
725097  movsxd rcx, ds:(jpt_72509E - 0F9B954h)[rdx+rcx*4]
72509b  add rcx, rdx
72509e  jmp rcx; switch jump
7250a0  mov ebx, [r15+rax]; jumptable 000000000072509E cases -4,4
7250a4  jmp short loc_7250C4
7250a6  lea rdi, aDH1CodeSourceR_1270; jumptable 000000000072509E default case, cases -3,0,3
7250ad  lea rcx, aUnknownFieldSi; "unknown field size"
7250b4  mov esi, 209h
7250b9  xor edx, edx
7250bb  xor eax, eax
7250bd  xor ebx, ebx
7250bf  call MyAssertHandler
7250c4  mov edi, ebx
7250c6  call BG_GetEntityTypeName
7250cb  mov rdx, [rbp+var_180]
7250d2  mov rcx, rax
7250d5  lea rsi, a3iChangedEntEt; "%3i: changed ent, eType %s\n"
7250dc  mov edi, 19h
7250e1  xor eax, eax
7250e3  call Com_Printf
7250e8  mov rdi, [r12]
7250ec  lea rsi, aEtype; "eType"
7250f3  call PLstrcmp
7250f8  test eax, eax
7250fa  jz short loc_72511F
7250fc  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
725103  lea rcx, aS_490; "%s"
72510a  lea r8, aStrcmpStatefie; "strcmp( stateFields[0].name, \"eType\" "...
725111  mov esi, 94Fh
725116  xor edx, edx
725118  xor eax, eax
72511a  call MyAssertHandler
72511f  movzx eax, word ptr [r12+0Ch]
725125  cmp eax, 0FFB3h
72512a  jz loc_724A30
725130  lea rdi, aDH1CodeSourceR_1269; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
725137  lea rcx, aS_490; "%s"
72513e  lea r8, aStatefields0Bi; "stateFields[0].bits == MSG_FIELD_ETYPE"
725145  mov esi, 951h
72514a  xor edx, edx
72514c  xor eax, eax
72514e  call MyAssertHandler
725153  jmp loc_724A30
725158  movsx ebx, word ptr [r15+rax]; jumptable 000000000072509E case -2
72515d  jmp loc_7250C4
725162  movsx ebx, byte ptr [r15+rax]; jumptable 000000000072509E case -1
725167  jmp loc_7250C4
72516c  movzx ebx, byte ptr [r15+rax]; jumptable 000000000072509E case 1
725171  jmp loc_7250C4
725176  movzx ebx, word ptr [r15+rax]; jumptable 000000000072509E case 2
72517b  jmp loc_7250C4
725180  call PL__stack_chk_fail
725185  nop
725186  nop word ptr [rax+rax+00000000h]
725190  push rbp; MSG_ReadDeltaArchivedEntity(msg_t*, int, archivedEntity_s const*, archivedEntity_s*, int)
725191  mov rbp, rsp
725194  push r15
725196  push r14
725198  push r13
72519a  push r12
72519c  push rbx
72519d  sub rsp, 38h
7251a1  lea rax, g_netFieldList
7251a8  mov rbx, rdx
7251ab  mov r15, rcx
7251ae  test rbx, rbx
7251b1  mov rax, [rax]
7251b4  mov r14d, [rax+8]
7251b8  mov r12, [rax]
7251bb  jz short loc_7251DB
7251bd  mov dword ptr [rbp+var_30+4], esi
7251c0  mov qword ptr [rbp+var_50+18h], rdi
7251c4  xor esi, esi
7251c6  mov rdi, rbx
7251c9  mov r13d, r8d
7251cc  call SV_ValidateEntityState
7251d1  mov rdi, qword ptr [rbp+var_50+18h]
7251d5  mov esi, dword ptr [rbp+var_30+4]
7251d8  mov r8d, r13d
7251db  mov rdx, rbx
7251de  mov rcx, r15
7251e1  mov r9d, r14d
7251e4  mov [rsp+1F8h+var_1E8], r12
7251e9  mov [rsp+1F8h+var_1D8], 1
7251f1  mov [rsp+1F8h+var_1E0], 3
7251f9  mov [rsp+1F8h+var_1F0], 2
725201  mov [rsp+1F8h+var_1F8], 0Bh
725208  call MSG_ReadDeltaStruct
72520d  mov ebx, eax
72520f  test r15, r15
725212  jz short loc_725222
725214  test ebx, ebx
725216  jnz short loc_725222
725218  xor esi, esi
72521a  mov rdi, r15
72521d  call SV_ValidateEntityState
725222  mov eax, ebx
725224  add rsp, 38h
725228  pop rbx
725229  pop r12
72522b  pop r13
72522d  pop r14
72522f  pop r15
725231  pop rbp
725232  retn
