73fba0  push rbp; MSG_WriteDeltaField(SnapshotInfo_s*, msg_t*, int, unsigned char const*, unsigned char const*, NetField const*, int, bool, bool, int, int, bool, bool)
73fba1  mov rbp, rsp
73fba4  push r15
73fba6  push r14
73fba8  push r13
73fbaa  push r12
73fbac  push rbx
73fbad  sub rsp, 68h
73fbb1  mov rax, cs:COMMON
73fbb8  mov qword ptr [rbp+var_50], r8
73fbbc  mov dword ptr [rbp+var_70], edx
73fbbf  mov r15, rsi
73fbc2  mov r10, r9
73fbc5  mov r14, rdi
73fbc8  mov rax, [rax]
73fbcb  mov [rbp+var_30], rax
73fbcf  cmp dword ptr [r15+4], 0
73fbd4  jz short loc_73FC05
73fbd6  mov r12, rcx
73fbd9  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
73fbe0  lea rcx, aS_501; "%s"
73fbe7  lea r8, aMsgReadonly_1; "!msg->readOnly"
73fbee  mov esi, 78Bh
73fbf3  xor edx, edx
73fbf5  xor eax, eax
73fbf7  mov rbx, r10
73fbfa  call MyAssertHandler
73fbff  mov rcx, r12
73fc02  mov r10, rbx
73fc05  mov dl, [rbp+arg_10]
73fc08  movzx r12d, word ptr [r10+8]
73fc0d  test rcx, rcx
73fc10  jnz short loc_73FC4A
73fc12  mov r13, r12
73fc15  mov r12, rcx
73fc18  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
73fc1f  lea rcx, aS_501; "%s"
73fc26  lea r8, aFrom_4; "from"
73fc2d  mov esi, 78Fh
73fc32  xor edx, edx
73fc34  xor eax, eax
73fc36  mov rbx, r10
73fc39  call MyAssertHandler
73fc3e  mov dl, [rbp+arg_10]
73fc41  mov rcx, r12
73fc44  mov r12, r13
73fc47  mov r10, rbx
73fc4a  mov al, [rbp+arg_28]
73fc4d  lea rdi, [rcx+r12]
73fc51  mov [rbp+var_68], rcx
73fc55  test dl, dl
73fc57  mov rcx, rdi
73fc5a  jnz short loc_73FC67
73fc5c  lea rcx, [rbp+var_34]
73fc60  mov [rbp+var_34], 0
73fc67  mov rdx, qword ptr [rbp+var_50]
73fc6b  mov ebx, [rbp+arg_0]
73fc6e  mov qword ptr [rbp+var_60], rcx
73fc72  test al, al
73fc74  lea r8, [rdx+r12]
73fc78  jz loc_73FE6B
73fc7e  mov al, [rbp+arg_8]
73fc81  test al, al
73fc83  jnz short loc_73FCDF
73fc85  movsx eax, word ptr [r10+0Ah]
73fc8a  vmovdqu xmm0, xmmword ptr [rdi]
73fc8e  mov edx, 1
73fc93  vpcmpeqb xmm0, xmm0, xmmword ptr [r8]
73fc98  mov ecx, eax
73fc9a  neg ecx
73fc9c  test eax, eax
73fc9e  cmovns ecx, eax
73fca1  shl edx, cl
73fca3  dec edx
73fca5  vpmovmskb ecx, xmm0
73fca9  and ecx, edx
73fcab  cmp ecx, edx
73fcad  jnz short loc_73FCB6
73fcaf  xor ebx, ebx
73fcb1  jmp loc_7400F4
73fcb6  movsx edx, word ptr [r10+0Ch]
73fcbb  mov rsi, r8
73fcbe  mov ecx, eax
73fcc0  mov r13, r8
73fcc3  mov rbx, r10
73fcc6  call MSG_ValuesAreEqualPost
73fccb  mov r10, rbx
73fcce  mov ebx, [rbp+arg_0]
73fcd1  mov r8, r13
73fcd4  test al, al
73fcd6  jz short loc_73FCDF
73fcd8  xor ebx, ebx
73fcda  jmp loc_7400F4
73fcdf  mov [rbp+var_40], r15
73fce3  mov r15d, [rbp+arg_18]
73fce7  test byte ptr [r10+0Eh], 1
73fcec  jz short loc_73FD60
73fcee  mov edi, [r14+78h]
73fcf2  cmp edi, 14h
73fcf5  jg short loc_73FD07
73fcf7  mov rax, [rbp+var_68]
73fcfb  mov rcx, qword ptr [rbp+var_50]
73fcff  mov eax, [rax+4]
73fd02  cmp eax, [rcx+4]
73fd05  jnz short loc_73FD60
73fd07  mov al, [r14+1Ch]
73fd0b  test ebx, ebx
73fd0d  jnz short loc_73FD13
73fd0f  test al, al
73fd11  jnz short loc_73FD60
73fd13  mov [rbp+var_80], r14
73fd17  mov r14d, ebx
73fd1a  mov rbx, [r10]
73fd1d  movzx eax, al
73fd20  mov r13, r8
73fd23  mov [rbp+var_78], r10
73fd27  mov dword ptr [rbp+var_88], eax
73fd2d  call SV_GetEntityTypeString
73fd32  mov r8d, dword ptr [rbp+var_88]
73fd39  mov rdx, rbx
73fd3c  mov ebx, r14d
73fd3f  mov r14, [rbp+var_80]
73fd43  mov rcx, rax
73fd46  lea rsi, aFieldSChangedF_0; "Field %s changed for eType %s when we t"...
73fd4d  mov edi, 0Fh
73fd52  xor eax, eax
73fd54  call Com_PrintError
73fd59  mov r10, [rbp+var_78]
73fd5d  mov r8, r13
73fd60  mov r13d, [rbp+arg_20]
73fd64  sub ebx, r15d
73fd67  mov [rbp+var_80], r14
73fd6b  jg short loc_73FDA2
73fd6d  mov r15, r8
73fd70  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
73fd77  lea rcx, aSNumfieldsskip; "%s\n\t(numFieldsSkipped) = %i"
73fd7e  lea r8, aNumfieldsskipp; "(numFieldsSkipped > 0)"
73fd85  mov esi, 597h
73fd8a  mov edx, 0
73fd8f  xor eax, eax
73fd91  mov r9d, ebx
73fd94  mov r14, r10
73fd97  call MyAssertHandler
73fd9c  mov r10, r14
73fd9f  mov r8, r15
73fda2  cmp r13d, 1
73fda6  jnz short loc_73FDE3
73fda8  mov r15, [rbp+var_40]
73fdac  mov r13, r8
73fdaf  mov [rbp+var_78], r10
73fdb3  cmp ebx, 2
73fdb6  jl short loc_73FDCF
73fdb8  nop dword ptr [rax+rax+00000000h]
73fdc0  mov rdi, r15
73fdc3  call MSG_WriteBit0
73fdc8  dec ebx
73fdca  cmp ebx, 1
73fdcd  jg short loc_73FDC0
73fdcf  mov rdi, r15
73fdd2  call MSG_WriteBit1
73fdd7  mov r14, [rbp+var_80]
73fddb  mov r8, r13
73fdde  jmp loc_73FE64
73fde3  mov [rbp+var_78], r10
73fde7  mov [rbp+var_88], r8
73fdee  cmp ebx, 1
73fdf1  jnz short loc_73FE01
73fdf3  mov r15, [rbp+var_40]
73fdf7  mov rdi, r15
73fdfa  call MSG_WriteBit1
73fdff  jmp short loc_73FE59
73fe01  mov rdi, [rbp+var_40]
73fe05  call MSG_WriteBit0
73fe0a  mov r14d, 1
73fe10  mov cl, r13b
73fe13  lea r15d, [rbx-1]
73fe17  shl r14d, cl
73fe1a  cmp r14d, ebx
73fe1d  jle short loc_73FE25
73fe1f  mov rbx, [rbp+var_40]
73fe23  jmp short loc_73FE48
73fe25  mov rbx, [rbp+var_40]
73fe29  dec r14d
73fe2c  nop dword ptr [rax+00h]
73fe30  mov esi, 0FFFFFFFFh
73fe35  mov rdi, rbx
73fe38  mov edx, r13d
73fe3b  call MSG_WriteBits
73fe40  sub r15d, r14d
73fe43  cmp r15d, r14d
73fe46  jge short loc_73FE30
73fe48  mov rdi, rbx
73fe4b  mov esi, r15d
73fe4e  mov edx, r13d
73fe51  call MSG_WriteBits
73fe56  mov r15, rbx
73fe59  mov r14, [rbp+var_80]
73fe5d  mov r8, [rbp+var_88]
73fe64  mov r10, [rbp+var_78]
73fe68  mov ebx, [rbp+arg_0]
73fe6b  mov [rbp+var_40], r15
73fe6f  mov r15b, [r14+1Dh]
73fe73  test r15b, r15b
73fe76  jnz short loc_73FE89
73fe78  cmp byte ptr [r14+1Ch], 0
73fe7d  jnz short loc_73FE89
73fe7f  mov rcx, [r14+20h]
73fe83  movsxd rax, ebx
73fe86  inc dword ptr [rcx+rax*4]
73fe89  movsx r13d, word ptr [r10+0Ch]
73fe8e  mov rbx, r14
73fe91  lea eax, [r13+6Eh]; switch 44 cases
73fe95  cmp eax, 2Bh
73fe98  jbe short loc_73FF06
73fe9a  test r13d, r13d; jumptable 000000000073FF14 default case
73fe9d  jz loc_73FFEF; jumptable 000000000073FF14 case -108
73fea3  cmp r13d, 0FFFFFFCDh; jumptable 000000000073FF14 case -109
73fea7  jg short loc_73FEDE
73fea9  lea rdi, aMissedAMsgCase_0; "Missed a MSG_ case in MSG_WriteDeltaFie"...
73feb0  xor eax, eax
73feb2  mov esi, r13d
73feb5  mov r14, r8
73feb8  mov rbx, r10
73febb  call va
73fec0  mov rcx, rax
73fec3  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
73feca  mov esi, 952h
73fecf  xor edx, edx
73fed1  xor eax, eax
73fed3  call MyAssertHandler
73fed8  mov r10, rbx
73fedb  mov r8, r14
73fede  movsx ebx, word ptr [r10+0Ah]
73fee3  lea eax, [rbx+4]; switch 9 cases
73fee6  cmp eax, 8
73fee9  ja short def_73FEF9; jumptable 000000000073FEF9 default case, cases -3,0,3
73feeb  lea rcx, jpt_73FEF9
73fef2  movsxd rax, ds:(jpt_73FEF9 - 0FA0F24h)[rcx+rax*4]
73fef6  add rax, rcx
73fef9  jmp rax; switch jump
73fefb  mov eax, [r8]; jumptable 000000000073FEF9 cases -4,4
73fefe  mov r14, r10
73ff01  jmp loc_73FFA3
73ff06  lea rcx, jpt_73FF14
73ff0d  movsxd rax, ds:(jpt_73FF14 - 0FA0DC0h)[rcx+rax*4]
73ff11  add rax, rcx
73ff14  jmp rax; switch jump
73ff16  mov esi, [r8]; jumptable 000000000073FF14 cases -80,-78,-73,-71,-69,-68
73ff19  mov rdi, [rbp+var_40]
73ff1d  call MSG_WriteLong
73ff22  jmp loc_7400F2
73ff27  lea rdi, aDH1CodeSourceR_1285; jumptable 000000000073FEF9 default case, cases -3,0,3
73ff2e  lea rcx, aUnknownFieldSi_0; "unknown field size"
73ff35  mov esi, 209h
73ff3a  xor edx, edx
73ff3c  xor eax, eax
73ff3e  call MyAssertHandler
73ff43  jmp loc_7400E9
73ff48  mov edx, [r8]; jumptable 000000000073FF14 cases -97,-74,-72,-70
73ff4b  mov rdi, [rbp+var_40]
73ff4f  mov esi, dword ptr [rbp+var_70]
73ff52  call MSG_WriteDeltaTime
73ff57  jmp loc_7400F2
73ff5c  mov rax, qword ptr [rbp+var_60]; jumptable 000000000073FF14 cases -92,-91,-83,-82
73ff60  vmovss xmm0, dword ptr [r8]
73ff65  mov rcx, [rbp+var_40]
73ff69  lea rdx, [rbx+4]
73ff6d  mov rdi, rbx
73ff70  mov r8d, r13d
73ff73  vmovss xmm1, dword ptr [rax]
73ff77  call MSG_WriteOriginFloat
73ff7c  jmp loc_7400F2
73ff81  movsx eax, word ptr [r8]; jumptable 000000000073FEF9 case -2
73ff85  mov r14, r10
73ff88  jmp short loc_73FFA3
73ff8a  movsx eax, byte ptr [r8]; jumptable 000000000073FEF9 case -1
73ff8e  mov r14, r10
73ff91  jmp short loc_73FFA3
73ff93  movzx eax, byte ptr [r8]; jumptable 000000000073FEF9 case 1
73ff97  mov r14, r10
73ff9a  jmp short loc_73FFA3
73ff9c  movzx eax, word ptr [r8]; jumptable 000000000073FEF9 case 2
73ffa0  mov r14, r10
73ffa3  mov r12, r8
73ffa6  test eax, eax
73ffa8  jz loc_7400E9
73ffae  mov r15, [rbp+var_40]
73ffb2  mov rdi, r15
73ffb5  call MSG_WriteBit1
73ffba  mov r9, [r14]
73ffbd  mov rsi, qword ptr [rbp+var_60]
73ffc1  mov rdi, r15
73ffc4  mov rdx, r12
73ffc7  mov ecx, r13d
73ffca  mov r8d, ebx
73ffcd  call MSG_WriteValue
73ffd2  jmp loc_7400F2
73ffd7  mov rsi, [rbp+var_40]; jumptable 000000000073FF14 cases -106--104
73ffdb  mov rcx, qword ptr [rbp+var_60]
73ffdf  mov rdi, rbx
73ffe2  mov edx, r13d
73ffe5  call MSG_WriteMovingPlatformValidOrigin
73ffea  jmp loc_7400F2
73ffef  mov rdi, [rbp+var_40]; jumptable 000000000073FF14 case -108
73fff3  mov rsi, qword ptr [rbp+var_60]
73fff7  mov rdx, r8
73fffa  call MSG_WriteFloatCase
73ffff  jmp loc_7400F2
740004  mov rax, qword ptr [rbp+var_60]; jumptable 000000000073FF14 cases -90,-81
740008  vmovss xmm0, dword ptr [r8]
74000d  mov rdx, [rbp+var_40]
740011  lea rsi, [rbx+4]
740015  mov rdi, rbx
740018  vmovss xmm1, dword ptr [rax]
74001c  call MSG_WriteOriginZFloat
740021  jmp loc_7400F2
740026  mov rdi, [rbp+var_40]; jumptable 000000000073FF14 case -110
74002a  mov rsi, qword ptr [rbp+var_60]
74002e  mov rdx, r8
740031  call MSG_WriteHudData
740036  jmp loc_7400F2
74003b  mov rdi, [rbp+var_40]; jumptable 000000000073FF14 case -107
74003f  mov rsi, qword ptr [rbp+var_60]
740043  mov rdx, r8
740046  call MSG_WriteAnimData
74004b  jmp loc_7400F2
740050  movsxd rax, dword ptr [r8]; jumptable 000000000073FF14 case -103
740053  cmp rax, 31Fh
740059  jg loc_74094D
74005f  imul rbx, rax, 51EB851Fh
740066  mov rcx, rbx
740069  sar rbx, 24h
74006d  shr rcx, 3Fh
740071  add ebx, ecx
740073  imul ecx, ebx, 32h ; '2'
740076  jmp short loc_7400A1
740078  movsxd rax, dword ptr [r8]; jumptable 000000000073FF14 case -102
74007b  cmp rax, 0F9Fh
740081  jg loc_74094D
740087  imul rbx, rax, 10624DD3h
74008e  mov rcx, rbx
740091  sar rbx, 24h
740095  shr rcx, 3Fh
740099  add ebx, ecx
74009b  imul ecx, ebx, 0FAh
7400a1  cmp eax, ecx
7400a3  jnz loc_74094D
7400a9  mov r15, [rbp+var_40]
7400ad  mov rdi, r15
7400b0  call MSG_WriteBit0
7400b5  mov edx, 4
7400ba  mov rdi, r15
7400bd  mov esi, ebx
7400bf  call MSG_WriteBits
7400c4  jmp short loc_7400F2
7400c6  cmp word ptr [r8], 0; jumptable 000000000073FF14 case -101
7400cb  jz short loc_7400E9
7400cd  mov rbx, [rbp+var_40]
7400d1  mov r15, r8
7400d4  mov rdi, rbx
7400d7  call MSG_WriteBit1
7400dc  mov esi, [r15]
7400df  mov rdi, rbx
7400e2  call MSG_WriteShort
7400e7  jmp short loc_7400F2
7400e9  mov rdi, [rbp+var_40]
7400ed  call MSG_WriteBit0
7400f2  mov bl, 1
7400f4  mov rax, cs:COMMON
7400fb  mov rax, [rax]
7400fe  cmp rax, [rbp+var_30]
740102  jnz loc_7413AE
740108  mov al, bl
74010a  add rsp, 68h
74010e  pop rbx
74010f  pop r12
740111  pop r13
740113  pop r14
740115  pop r15
740117  pop rbp
740118  retn
740119  mov rax, qword ptr [rbp+var_60]; jumptable 000000000073FF14 case -100
74011d  vmovss xmm0, cs:dword_FA0C44
740125  vmovss xmm2, cs:dword_FA0C2C
74012d  vmovss xmm3, dword ptr [r8]
740132  vmulss xmm1, xmm0, dword ptr [rax]
740136  vaddss xmm1, xmm1, xmm2
74013a  vroundss xmm1, xmm0, xmm1, 1
740140  vmulss xmm0, xmm3, xmm0
740144  vaddss xmm0, xmm0, xmm2
740148  vcvttss2si eax, xmm1
74014c  vroundss xmm0, xmm0, xmm0, 1
740152  movsx esi, ax
740155  lea rax, g_commonAngleDeltas
74015c  vcvttss2si ecx, xmm0
740160  movsx edx, cx
740163  movsx ecx, word ptr [rax]
740166  mov r14d, edx
740169  sub r14d, esi
74016c  mov r13d, r14d
74016f  neg r13d
740172  cmovl r13d, r14d
740176  xor r12d, r12d
740179  cmp ecx, r13d
74017c  jz short loc_7401DC
74017e  movsx ecx, word ptr [rax+2]
740182  mov r12d, 1
740188  cmp ecx, r13d
74018b  jz short loc_7401DC
74018d  movsx ecx, word ptr [rax+4]
740191  mov r12d, 2
740197  cmp ecx, r13d
74019a  jz short loc_7401DC
74019c  movsx ecx, word ptr [rax+6]
7401a0  mov r12d, 3
7401a6  cmp ecx, r13d
7401a9  jz short loc_7401DC
7401ab  movsx ecx, word ptr [rax+8]
7401af  mov r12d, 4
7401b5  cmp ecx, r13d
7401b8  jz short loc_7401DC
7401ba  movsx ecx, word ptr [rax+0Ah]
7401be  mov r12d, 5
7401c4  cmp ecx, r13d
7401c7  jz short loc_7401DC
7401c9  movsx eax, word ptr [rax+0Ch]
7401cd  mov r12d, 6
7401d3  cmp eax, r13d
7401d6  jnz loc_7412C6
7401dc  mov rbx, [rbp+var_40]
7401e0  mov rdi, rbx
7401e3  call MSG_WriteBit1
7401e8  mov rdi, rbx
7401eb  test r14d, r14d
7401ee  js loc_740D7D
7401f4  call MSG_WriteBit0
7401f9  jmp loc_740D82
7401fe  mov rax, qword ptr [rbp+var_60]; jumptable 000000000073FF14 case -99
740202  vmovss xmm1, dword ptr [r8]
740207  vpxor xmm0, xmm0, xmm0
74020b  mov r13, r8
74020e  vcvttss2si r14d, dword ptr [rax]
740212  vmovd ebx, xmm1
740216  vucomiss xmm1, xmm0
74021a  jnz loc_740B51
740220  jp loc_740B51
740226  cmp ebx, 80000000h
74022c  jz loc_740B51
740232  mov rdi, [rbp+var_40]
740236  call MSG_WriteBit0
74023b  jmp loc_740D2F
740240  mov rax, qword ptr [rbp+var_60]; jumptable 000000000073FF14 case -98
740244  mov r13, [rbp+var_40]
740248  mov r14d, [r8]
74024b  mov ebx, [rax]
74024d  cmp dword ptr [r13+4], 0
740252  jz short loc_740277
740254  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
74025b  lea rcx, aS_501; "%s"
740262  lea r8, aMsgReadonly_1; "!msg->readOnly"
740269  mov esi, 349h
74026e  xor edx, edx
740270  xor eax, eax
740272  call MyAssertHandler
740277  xor ebx, r14d
74027a  mov r15d, ebx
74027d  and r15d, 1FFFFFFFh
740284  jz short loc_740295
740286  add ebx, 1FFFFFFFh
74028c  test ebx, r15d
74028f  jz loc_740D94
740295  mov rdi, r13
740298  call MSG_WriteBit1
74029d  mov edx, 1Dh
7402a2  jmp loc_740E12
7402a7  movsx eax, word ptr [r10+0Ah]; jumptable 000000000073FF14 case -96
7402ac  add eax, 4; switch 9 cases
7402af  cmp eax, 8
7402b2  ja def_7402C6; jumptable 00000000007402C6 default case, cases -3,0,3
7402b8  lea rcx, jpt_7402C6
7402bf  movsxd rax, ds:(jpt_7402C6 - 0FA0EB8h)[rcx+rax*4]
7402c3  add rax, rcx
7402c6  jmp rax; switch jump
7402c8  mov r15d, [r8]; jumptable 00000000007402C6 cases -4,4
7402cb  jmp loc_7409B5
7402d0  mov r12d, [r8]; jumptable 000000000073FF14 case -95
7402d3  test r15b, r15b
7402d6  jnz short loc_7402F1
7402d8  movsx edi, byte ptr [rbx]
7402db  lea rsi, aSendingIAsPlay; "Sending %i as playerstate timer value ("...
7402e2  mov ecx, 64h ; 'd'
7402e7  xor eax, eax
7402e9  mov edx, r12d
7402ec  call SV_LogSnapshotContent
7402f1  movsxd rax, r12d
7402f4  mov edx, 7
7402f9  imul rsi, rax, 51EB851Fh
740300  mov rax, rsi
740303  sar rsi, 25h
740307  shr rax, 3Fh
74030b  add esi, eax
74030d  jmp loc_74093F
740312  mov al, [rbp+arg_30]; jumptable 000000000073FF14 case -94
740315  mov r9d, 0FFFFFFFFh
74031b  test al, al
74031d  jz loc_741162
740323  mov rax, qword ptr [rbp+var_50]
740327  mov r15, r10
74032a  movsx eax, byte ptr [rax+0Eh]
74032e  cmp eax, 12h
740331  jl short loc_740356
740333  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
74033a  lea rcx, aS_501; "%s"
740341  lea r8, aEntitystateTTo; "((entityState_t*)to)->clientNum < MAX_C"...
740348  mov esi, 8F5h
74034d  xor edx, edx
74034f  xor eax, eax
740351  call MyAssertHandler
740356  mov rax, 7FFFFFFD4h
740360  add r12, rax
740363  shr r12, 3
740367  test r12d, r12d
74036a  js loc_741130
740370  cmp r12d, 4
740374  jl loc_741153
74037a  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
740381  lea rcx, aS_501; "%s"
740388  lea r8, aNetfieldindexM; "netfieldIndex < MAX_EVENTS"
74038f  mov esi, 8FBh
740394  jmp loc_74114A
740399  movsx eax, word ptr [r10+0Ah]; jumptable 000000000073FF14 case -93
74039e  add eax, 4; switch 9 cases
7403a1  cmp eax, 8
7403a4  ja def_7403B8; jumptable 00000000007403B8 default case, cases -3,0,3
7403aa  lea rcx, jpt_7403B8
7403b1  movsxd rax, ds:(jpt_7403B8 - 0FA0E94h)[rcx+rax*4]
7403b5  add rax, rcx
7403b8  jmp rax; switch jump
7403ba  mov r15d, [r8]; jumptable 00000000007403B8 cases -4,4
7403bd  jmp loc_740A50
7403c2  vmovss xmm0, dword ptr [r8]; jumptable 000000000073FF14 case -89
7403c7  vmovd eax, xmm0
7403cb  cmp eax, 80000000h
7403d0  jz loc_740971
7403d6  vcvttss2si ebx, xmm0
7403da  vcvtsi2ss xmm1, xmm0, ebx
7403de  vucomiss xmm1, xmm0
7403e2  jnz loc_740971
7403e8  jp loc_740971
7403ee  add ebx, 1000h
7403f4  cmp ebx, 1FFFh
7403fa  ja loc_740971
740400  mov rax, qword ptr [rbp+var_60]
740404  mov r12, [rbp+var_40]
740408  vcvttss2si r14d, dword ptr [rax]
74040c  mov rdi, r12
74040f  call MSG_WriteBit0
740414  add r14d, 1000h
74041b  mov edx, 5
740420  mov rdi, r12
740423  xor r14d, ebx
740426  mov esi, r14d
740429  call MSG_WriteBits
74042e  sar r14d, 5
740432  mov rdi, r12
740435  mov esi, r14d
740438  call MSG_WriteByte
74043d  jmp loc_7400F2
740442  mov rax, qword ptr [rbp+var_60]; jumptable 000000000073FF14 case -88
740446  mov esi, [rax]
740448  xor esi, [r8]
74044b  jmp loc_73FF19
740450  vmovss xmm0, dword ptr [r8]; jumptable 000000000073FF14 case -87
740455  mov rdi, [rbp+var_40]
740459  call MSG_WriteAngle16
74045e  jmp loc_7400F2
740463  vmovss xmm0, dword ptr [r8]; jumptable 000000000073FF14 case -86
740468  mov edx, 20h ; ' '
74046d  vmulss xmm1, xmm0, cs:dword_FA0C28
740475  vaddss xmm1, xmm1, cs:dword_FA0C2C
74047d  vroundss xmm1, xmm0, xmm1, 1
740483  vcvttss2si ebx, xmm1
740487  mov eax, ebx
740489  sar eax, 1Fh
74048c  mov ecx, eax
74048e  add eax, 6
740491  xor ecx, ebx
740493  lzcnt ecx, ecx
740497  sub edx, ecx
740499  cmp edx, eax
74049b  jbe short loc_7404B4
74049d  vmovd edx, xmm0
7404a1  lea rsi, aNotEnoughBitsW_0; "Not enough bits written for fontScale %"...
7404a8  mov edi, 0Fh
7404ad  xor eax, eax
7404af  call Com_PrintError
7404b4  mov rdi, [rbp+var_40]
7404b8  mov edx, 6
7404bd  mov esi, ebx
7404bf  call MSG_WriteBits
7404c4  jmp loc_7400F2
7404c9  mov rax, qword ptr [rbp+var_60]; jumptable 000000000073FF14 case -85
7404cd  mov al, [rax+3]
7404d0  test al, al
7404d2  jnz loc_740BD6
7404d8  mov r12, [rbp+var_40]
7404dc  movzx eax, byte ptr [r8+3]
7404e1  cmp eax, 0FFh
7404e6  jnz loc_740C0A
7404ec  jmp loc_740BEB
7404f1  mov esi, [r8]; jumptable 000000000073FF14 case -84
7404f4  mov edx, 0Dh
7404f9  jmp loc_74093F
7404fe  vmovss xmm0, cs:dword_FA0C30; jumptable 000000000073FF14 case -79
740506  vmovss xmm7, cs:dword_FA0C34
74050e  vmovss xmm3, cs:dword_FA0C38
740516  mov rax, qword ptr [rbp+var_60]
74051a  vxorps xmm6, xmm6, xmm6
74051e  vmulss xmm1, xmm0, dword ptr [r8]
740523  vroundss xmm2, xmm0, xmm1, 1
740529  vmulss xmm0, xmm0, dword ptr [rax]
74052d  vsubss xmm1, xmm1, xmm2
740531  vmulss xmm1, xmm1, xmm7
740535  vaddss xmm4, xmm1, xmm3
740539  vcmpless xmm5, xmm6, xmm4
74053e  vblendvps xmm1, xmm1, xmm4, xmm5
740544  vmovaps [rbp+var_50], xmm1
740549  vroundss xmm1, xmm0, xmm0, 1
74054f  vsubss xmm0, xmm0, xmm1
740553  vmulss xmm0, xmm0, xmm7
740557  vaddss xmm1, xmm0, xmm3
74055b  vcmpless xmm3, xmm6, xmm1
740560  vblendvps xmm1, xmm0, xmm1, xmm3
740566  vucomiss xmm1, xmm7
74056a  setbe al
74056d  vucomiss xmm6, xmm1
740571  setbe r14b
740575  and r14b, al
740578  jnz short loc_7405C3
74057a  vcvtss2sd xmm0, xmm1, xmm1
74057e  lea rdi, aOldfloatFIsnTN_0; "oldFloat %f isn't normalized\n"
740585  mov al, 1
740587  vmovaps [rbp+var_60], xmm1
74058c  call va
740591  mov r9, rax
740594  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
74059b  lea rcx, aSS_242; "%s\n\t%s"
7405a2  lea r8, aIsanglenormali_2; "IsAngleNormalized360( oldFloat )"
7405a9  mov esi, 66Bh
7405ae  mov edx, 0
7405b3  xor eax, eax
7405b5  call MyAssertHandler
7405ba  vmovaps xmm1, [rbp+var_60]
7405bf  vxorps xmm6, xmm6, xmm6
7405c3  vmovaps xmm0, [rbp+var_50]
7405c8  mov r13, rbx
7405cb  vucomiss xmm0, cs:dword_FA0C34
7405d3  setbe al
7405d6  vucomiss xmm6, xmm0
7405da  setbe cl
7405dd  and cl, al
7405df  mov byte ptr [rbp+var_68], cl
7405e2  jnz short loc_74062E
7405e4  vmovaps xmm0, [rbp+var_50]
7405e9  lea rdi, aFullfloatFIsnT; "fullFloat %f isn't normalized\n"
7405f0  mov al, 1
7405f2  vmovaps [rbp+var_60], xmm1
7405f7  vcvtss2sd xmm0, xmm0, xmm0
7405fb  call va
740600  mov r9, rax
740603  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
74060a  lea rcx, aSS_242; "%s\n\t%s"
740611  lea r8, aIsanglenormali_3; "IsAngleNormalized360( fullFloat )"
740618  mov esi, 66Ch
74061d  mov edx, 0
740622  xor eax, eax
740624  call MyAssertHandler
740629  vmovaps xmm1, [rbp+var_60]
74062e  test r14b, 1
740632  jnz short loc_74067C
740634  vcvtss2sd xmm0, xmm1, xmm1
740638  lea rdi, aAngletocompres_0; "AngleToCompressed called with a non nor"...
74063f  mov al, 1
740641  vmovaps [rbp+var_60], xmm1
740646  call va
74064b  mov rbx, rax
74064e  lea rdi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
740655  lea rcx, aSS_242; "%s\n\t%s"
74065c  lea r8, aIsanglenormali_4; "IsAngleNormalized360(x)"
740663  mov esi, 550h
740668  mov edx, 0
74066d  xor eax, eax
74066f  mov r9, rbx
740672  call MyAssertHandler
740677  vmovaps xmm1, [rbp+var_60]
74067c  vmulss xmm0, xmm1, cs:dword_FA0C3C
740684  vaddss xmm0, xmm0, cs:dword_FA0C2C
74068c  vroundss xmm0, xmm0, xmm0, 1
740692  vcvttss2si r12d, xmm0
740696  movsxd rbx, r12d
740699  movsx rax, r12w
74069d  cmp rbx, rax
7406a0  jz short loc_7406B6
7406a2  lea rsi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
7406a9  mov edx, 552h
7406ae  mov rdi, rbx
7406b1  call truncate_cast_assert_with_info
7406b6  movzx eax, bx
7406b9  cmp eax, 1000h
7406be  jb short loc_740703
7406c0  movsx esi, r12w
7406c4  lea rdi, aCompressedangl_1; "compressedAngle %d not within 0-%d rang"...
7406cb  mov edx, 0FFFh
7406d0  xor eax, eax
7406d2  call va
7406d7  mov rbx, rax
7406da  lea rdi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
7406e1  lea rcx, aSS_242; "%s\n\t%s"
7406e8  lea r8, aCompressedangl_2; "(compressedAngle >= 0.f) && (compressed"...
7406ef  mov esi, 556h
7406f4  mov edx, 0
7406f9  xor eax, eax
7406fb  mov r9, rbx
7406fe  call MyAssertHandler
740703  test byte ptr [rbp+var_68], 1
740707  jnz short loc_74074C
740709  vmovaps xmm0, [rbp+var_50]
74070e  lea rdi, aAngletocompres_0; "AngleToCompressed called with a non nor"...
740715  mov al, 1
740717  vcvtss2sd xmm0, xmm0, xmm0
74071b  call va
740720  mov rbx, rax
740723  lea rdi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
74072a  lea rcx, aSS_242; "%s\n\t%s"
740731  lea r8, aIsanglenormali_4; "IsAngleNormalized360(x)"
740738  mov esi, 550h
74073d  mov edx, 0
740742  xor eax, eax
740744  mov r9, rbx
740747  call MyAssertHandler
74074c  vmovaps xmm0, [rbp+var_50]
740751  vmulss xmm0, xmm0, cs:dword_FA0C3C
740759  vaddss xmm0, xmm0, cs:dword_FA0C2C
740761  vroundss xmm0, xmm0, xmm0, 1
740767  vcvttss2si ebx, xmm0
74076b  movsxd rax, ebx
74076e  movsx r14, bx
740772  mov [rbp+var_70], rax
740776  cmp rax, r14
740779  jz short loc_740790
74077b  mov rdi, [rbp+var_70]
74077f  lea rsi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
740786  mov edx, 552h
74078b  call truncate_cast_assert_with_info
740790  movzx eax, r14w
740794  movsx ebx, bx
740797  cmp eax, 1000h
74079c  jb short loc_7407E5
74079e  lea rdi, aCompressedangl_1; "compressedAngle %d not within 0-%d rang"...
7407a5  mov edx, 0FFFh
7407aa  xor eax, eax
7407ac  mov esi, ebx
7407ae  call va
7407b3  mov r10d, ebx
7407b6  mov rbx, rax
7407b9  lea rdi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
7407c0  lea rcx, aSS_242; "%s\n\t%s"
7407c7  lea r8, aCompressedangl_2; "(compressedAngle >= 0.f) && (compressed"...
7407ce  mov esi, 556h
7407d3  mov edx, 0
7407d8  xor eax, eax
7407da  mov r9, rbx
7407dd  mov ebx, r10d
7407e0  call MyAssertHandler
7407e5  movsx eax, r12w
7407e9  mov r12d, ebx
7407ec  mov dword ptr [rbp+var_60], ebx
7407ef  sub r12d, eax
7407f2  mov ebx, r12d
7407f5  neg ebx
7407f7  cmovl ebx, r12d
7407fb  test ebx, ebx
7407fd  jle loc_740CE6
740803  cmp ebx, 1000h
740809  jl short loc_740844
74080b  lea rdi, aAbsdiffD; "absdiff: %d\n"
740812  xor eax, eax
740814  mov esi, ebx
740816  call va
74081b  mov r9, rax
74081e  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
740825  lea rcx, aSS_242; "%s\n\t%s"
74082c  lea r8, aAbsdiffAngleDe; "absdiff < ANGLE_DELTA_MAXSIZE"
740833  mov esi, 67Dh
740838  mov edx, 0
74083d  xor eax, eax
74083f  call MyAssertHandler
740844  test r15b, r15b
740847  jnz short loc_740858
740849  cmp byte ptr [r13+1Ch], 0
74084e  jnz short loc_740858
740850  mov edi, r12d
740853  call SV_TrackNormalizedAngleDeltaBits
740858  mov r13, [rbp+var_40]
74085c  mov rdi, r13
74085f  call MSG_WriteBit1
740864  mov rdi, r13
740867  test r12d, r12d
74086a  js loc_740E22
740870  call MSG_WriteBit0
740875  jmp loc_740E27
74087a  movsx eax, word ptr [r10+0Ah]; jumptable 000000000073FF14 case -77
74087f  add eax, 4; switch 9 cases
740882  cmp eax, 8
740885  ja def_740899; jumptable 0000000000740899 default case, cases -3,0,3
74088b  lea rcx, jpt_740899
740892  movsxd rax, ds:(jpt_740899 - 0FA0E70h)[rcx+rax*4]
740896  add rax, rcx
740899  jmp rax; switch jump
74089b  mov ebx, [r8]; jumptable 0000000000740899 cases -4,4
74089e  jmp loc_740AB6
7408a3  mov rax, qword ptr [rbp+var_60]; jumptable 000000000073FF14 case -76
7408a7  mov r12d, [r8]
7408aa  mov r13, r10
7408ad  mov [rbp+var_88], r8
7408b4  sub r12d, [rax]
7408b7  test r15b, r15b
7408ba  jnz short loc_7408CA
7408bc  cmp byte ptr [rbx+1Ch], 0
7408c0  jnz short loc_7408CA
7408c2  mov edi, r12d
7408c5  call SV_TrackMovementDirDelta
7408ca  mov r15, [rbp+var_40]
7408ce  mov eax, r12d
7408d1  neg eax
7408d3  cmovl eax, r12d
7408d7  cmp eax, 7
7408da  mov rdi, r15
7408dd  jg loc_740C96
7408e3  call MSG_WriteBit1
7408e8  add r12d, 8
7408ec  mov edx, 4
7408f1  mov rdi, r15
7408f4  mov esi, r12d
7408f7  call MSG_WriteBits
7408fc  jmp loc_7400F2
740901  movsx edx, word ptr [r10+0Ah]; jumptable 000000000073FF14 case -75
740906  mov [rbp+var_78], r10
74090a  lea r12d, [rdx+4]; switch 9 cases
74090e  cmp r12d, 8
740912  ja def_740926; jumptable 0000000000740926 default case, cases -3,0,3
740918  lea rax, jpt_740926
74091f  movsxd rcx, ds:(jpt_740926 - 0FA0EDCh)[rax+r12*4]
740923  add rcx, rax
740926  jmp rcx; switch jump
740928  mov r13d, [r8]; jumptable 0000000000740926 cases -4,4
74092b  mov qword ptr [rbp+var_50], rdx
74092f  jmp loc_740B2B
740934  mov esi, [r8]; jumptable 000000000073FF14 case -67
740937  mov edx, 5
74093c  add esi, 0Ah
74093f  mov rdi, [rbp+var_40]
740943  call MSG_WriteBits
740948  jmp loc_7400F2
74094d  mov rbx, [rbp+var_40]
740951  mov r15, r8
740954  mov rdi, rbx
740957  call MSG_WriteBit1
74095c  mov esi, [r15]
74095f  mov edx, 10h
740964  mov rdi, rbx
740967  call MSG_WriteBits
74096c  jmp loc_7400F2
740971  mov rbx, [rbp+var_40]
740975  mov r15, r8
740978  mov rdi, rbx
74097b  call MSG_WriteBit1
740980  mov rax, qword ptr [rbp+var_60]
740984  mov rdi, rbx
740987  mov esi, [rax]
740989  xor esi, [r15]
74098c  call MSG_WriteLong
740991  jmp loc_7400F2
740996  lea rdi, aDH1CodeSourceR_1285; jumptable 00000000007402C6 default case, cases -3,0,3
74099d  lea rcx, aUnknownFieldSi_0; "unknown field size"
7409a4  mov esi, 209h
7409a9  xor edx, edx
7409ab  xor eax, eax
7409ad  xor r15d, r15d
7409b0  call MyAssertHandler
7409b5  mov rbx, [rbp+var_40]
7409b9  cmp dword ptr [rbx+4], 0
7409bd  jz short loc_7409E2
7409bf  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
7409c6  lea rcx, aS_501; "%s"
7409cd  lea r8, aMsgReadonly_1; "!msg->readOnly"
7409d4  mov esi, 36Ah
7409d9  xor edx, edx
7409db  xor eax, eax
7409dd  call MyAssertHandler
7409e2  cmp r15d, 7FEh
7409e9  jz short loc_740A24
7409eb  mov rdi, rbx
7409ee  call MSG_WriteBit0
7409f3  test r15d, r15d
7409f6  jz short loc_740A24
7409f8  mov rdi, rbx
7409fb  call MSG_WriteBit0
740a00  mov edx, 3
740a05  mov rdi, rbx
740a08  mov esi, r15d
740a0b  call MSG_WriteBits
740a10  sar r15d, 3
740a14  mov rdi, rbx
740a17  mov esi, r15d
740a1a  call MSG_WriteByte
740a1f  jmp loc_7400F2
740a24  mov rdi, rbx
740a27  call MSG_WriteBit1
740a2c  jmp loc_7400F2
740a31  lea rdi, aDH1CodeSourceR_1285; jumptable 00000000007403B8 default case, cases -3,0,3
740a38  lea rcx, aUnknownFieldSi_0; "unknown field size"
740a3f  mov esi, 209h
740a44  xor edx, edx
740a46  xor eax, eax
740a48  xor r15d, r15d
740a4b  call MyAssertHandler
740a50  mov rbx, [rbp+var_40]
740a54  cmp dword ptr [rbx+4], 0
740a58  jz short loc_740A7D
740a5a  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
740a61  lea rcx, aS_501; "%s"
740a68  lea r8, aMsgReadonly_1; "!msg->readOnly"
740a6f  mov esi, 3EBh
740a74  xor edx, edx
740a76  xor eax, eax
740a78  call MyAssertHandler
740a7d  mov edx, 1Fh
740a82  mov rdi, rbx
740a85  mov esi, r15d
740a88  call MSG_WriteBits
740a8d  jmp loc_7400F2
740a92  lea rdi, aDH1CodeSourceR_1285; jumptable 0000000000740899 default case, cases -3,0,3
740a99  lea rcx, aUnknownFieldSi_0; "unknown field size"
740aa0  mov esi, 209h
740aa5  xor edx, edx
740aa7  xor eax, eax
740aa9  xor ebx, ebx
740aab  mov r14, r10
740aae  call MyAssertHandler
740ab3  mov r10, r14
740ab6  mov eax, ebx
740ab8  mov r15, [rbp+var_40]
740abc  mov edx, 20h ; ' '
740ac1  sar eax, 1Fh
740ac4  mov ecx, eax
740ac6  add eax, 8
740ac9  xor ecx, ebx
740acb  lzcnt ecx, ecx
740acf  sub edx, ecx
740ad1  cmp edx, eax
740ad3  jbe short loc_740AF3
740ad5  mov rcx, [r10]
740ad8  lea rsi, aNotEnoughBitsW_1; "Not enough bits written: %d for %s (%d)"...
740adf  mov edi, 1
740ae4  mov r8d, 8
740aea  xor eax, eax
740aec  mov edx, ebx
740aee  call Com_PrintError
740af3  mov rdi, r15
740af6  mov esi, ebx
740af8  call MSG_WriteByte
740afd  jmp loc_7400F2
740b02  mov qword ptr [rbp+var_50], rdx; jumptable 0000000000740926 default case, cases -3,0,3
740b06  lea rdi, aDH1CodeSourceR_1285; "D:\\h1\\code_source\\Runtime\\qcommon/."...
740b0d  lea rcx, aUnknownFieldSi_0; "unknown field size"
740b14  mov esi, 209h
740b19  xor edx, edx
740b1b  xor eax, eax
740b1d  xor r13d, r13d
740b20  mov r14, r8
740b23  call MyAssertHandler
740b28  mov r8, r14
740b2b  cmp r12d, 8; switch 9 cases
740b2f  ja def_740B43; jumptable 0000000000740B43 default case, cases 1,4,7
740b35  lea rax, jpt_740B43
740b3c  movsxd rcx, ds:(jpt_740B43 - 0FA0F00h)[rax+r12*4]
740b40  add rcx, rax
740b43  jmp rcx; switch jump
740b45  mov rax, qword ptr [rbp+var_60]; jumptable 0000000000740B43 cases 0,8
740b49  mov r12d, [rax]
740b4c  jmp loc_74123D
740b51  mov r12, [rbp+var_40]
740b55  vmovss dword ptr [rbp+var_50], xmm1
740b5a  mov r15, rax
740b5d  mov rdi, r12
740b60  call MSG_WriteBit1
740b65  cmp ebx, 80000000h
740b6b  jz loc_740D18
740b71  vmovss xmm1, dword ptr [rbp+var_50]
740b76  vcvttss2si ebx, xmm1
740b7a  vcvtsi2ss xmm0, xmm0, ebx
740b7e  vucomiss xmm0, xmm1
740b82  jnz loc_740D18
740b88  jp loc_740D18
740b8e  add ebx, 800h
740b94  cmp ebx, 0FFFh
740b9a  ja loc_740D18
740ba0  mov rdi, r12
740ba3  call MSG_WriteBit0
740ba8  add r14d, 800h
740baf  mov edx, 4
740bb4  mov rdi, r12
740bb7  xor r14d, ebx
740bba  mov esi, r14d
740bbd  call MSG_WriteBits
740bc2  sar r14d, 4
740bc6  mov rdi, r12
740bc9  mov esi, r14d
740bcc  call MSG_WriteByte
740bd1  jmp loc_740D2F
740bd6  mov r12, [rbp+var_40]
740bda  movzx eax, al
740bdd  cmp eax, 0FFh
740be2  jnz short loc_740C0A
740be4  cmp byte ptr [r8+3], 0
740be9  jnz short loc_740C0A
740beb  mov rdi, qword ptr [rbp+var_60]
740bef  mov edx, 3
740bf4  mov rsi, r8
740bf7  mov rbx, r8
740bfa  call PLmemcmp
740bff  mov r8, rbx
740c02  test eax, eax
740c04  jz loc_74117E
740c0a  mov rdi, r12
740c0d  mov rbx, r8
740c10  call MSG_WriteBit0
740c15  mov rsi, qword ptr [rbp+var_60]
740c19  mov rdx, rbx
740c1c  movzx eax, byte ptr [rdx]
740c1f  lea r15, [rdx+1]
740c23  movzx ecx, byte ptr [rsi]
740c26  cmp ecx, eax
740c28  jnz short loc_740C4F
740c2a  movzx eax, byte ptr [rdx+1]
740c2e  movzx ecx, byte ptr [rsi+1]
740c32  cmp ecx, eax
740c34  jnz short loc_740C4F
740c36  movzx eax, byte ptr [rdx+2]
740c3a  movzx ecx, byte ptr [rsi+2]
740c3e  mov rbx, rdx
740c41  cmp ecx, eax
740c43  jnz short loc_740C52
740c45  mov rdi, r12
740c48  call MSG_WriteBit1
740c4d  jmp short loc_740C7D
740c4f  mov rbx, rdx
740c52  mov rdi, r12
740c55  call MSG_WriteBit0
740c5a  movzx esi, byte ptr [rbx]
740c5d  mov rdi, r12
740c60  call MSG_WriteByte
740c65  movzx esi, byte ptr [r15]
740c69  mov rdi, r12
740c6c  call MSG_WriteByte
740c71  movzx esi, byte ptr [rbx+2]
740c75  mov rdi, r12
740c78  call MSG_WriteByte
740c7d  movzx esi, byte ptr [rbx+3]
740c81  mov edx, 5
740c86  mov rdi, r12
740c89  shr esi, 3
740c8c  call MSG_WriteBits
740c91  jmp loc_7400F2
740c96  call MSG_WriteBit0
740c9b  mov r9, [r13+0]
740c9f  mov rsi, qword ptr [rbp+var_60]
740ca3  mov rdx, [rbp+var_88]
740caa  movsx r8d, word ptr [r13+0Ah]
740caf  mov ecx, 8
740cb4  mov rdi, r15
740cb7  jmp loc_73FFCD
740cbc  lea rdi, aDH1CodeSourceR_1285; jumptable 0000000000740B43 default case, cases 1,4,7
740cc3  lea rcx, aUnknownFieldSi_0; "unknown field size"
740cca  mov esi, 209h
740ccf  xor edx, edx
740cd1  xor eax, eax
740cd3  xor r12d, r12d
740cd6  mov r14, r8
740cd9  call MyAssertHandler
740cde  mov r8, r14
740ce1  jmp loc_74123D
740ce6  test r15b, r15b
740ce9  jnz short loc_740CF7
740ceb  cmp byte ptr [r13+1Ch], 0
740cf0  jnz short loc_740CF7
740cf2  call SV_TrackAngleNormalizedFullSend
740cf7  mov rbx, [rbp+var_40]
740cfb  mov rdi, rbx
740cfe  call MSG_WriteBit0
740d03  mov esi, dword ptr [rbp+var_60]
740d06  mov edx, 0Ch
740d0b  mov rdi, rbx
740d0e  call MSG_WriteBits
740d13  jmp loc_7400F2
740d18  mov rdi, r12
740d1b  call MSG_WriteBit1
740d20  mov esi, [r15]
740d23  mov rdi, r12
740d26  xor esi, [r13+0]
740d2a  call MSG_WriteLong
740d2f  vmovss xmm0, dword ptr [r13+0]
740d35  mov bl, 1
740d37  vaddss xmm0, xmm0, cs:dword_FA0C4C
740d3f  vcvttss2si rax, xmm0
740d44  cmp eax, 1000h
740d49  jb loc_7400F4
740d4f  vcvttss2si r8d, xmm0
740d53  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
740d5a  lea rcx, aFloatTofHudele_0; "*(float *)toF + HUDELEM_COORD_BIAS does"...
740d61  mov esi, 85Ah
740d66  mov edx, 0
740d6b  mov r9d, 1000h
740d71  xor eax, eax
740d73  call MyAssertHandler
740d78  jmp loc_7400F4
740d7d  call MSG_WriteBit1
740d82  mov edi, 7
740d87  call GetMinBitCountForNum
740d8c  mov rdi, rbx
740d8f  jmp loc_741276
740d94  mov eax, r15d
740d97  mov r14d, 1Fh
740d9d  lzcnt eax, eax
740da1  sub r14d, eax
740da4  cmp r14d, 1Dh
740da8  jb short loc_740DD3
740daa  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
740db1  lea rcx, aSChangedbitind; "%s\n\t(changedBitIndex) = %i"
740db8  lea r8, aChangedbitinde; "(changedBitIndex >= 0 && changedBitInde"...
740dbf  mov esi, 359h
740dc4  mov edx, 0
740dc9  xor eax, eax
740dcb  mov r9d, r14d
740dce  call MyAssertHandler
740dd3  mov eax, 1
740dd8  mov cl, r14b
740ddb  shl eax, cl
740ddd  cmp r15d, eax
740de0  jz short loc_740E05
740de2  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
740de9  lea rcx, aS_501; "%s"
740df0  lea r8, aOldflagsNewfla; "( ((oldFlags ^ newFlags) & MASK_EFLAGS)"...
740df7  mov esi, 35Ah
740dfc  xor edx, edx
740dfe  xor eax, eax
740e00  call MyAssertHandler
740e05  mov rdi, r13
740e08  call MSG_WriteBit0
740e0d  mov edx, 5
740e12  mov rdi, r13
740e15  mov esi, r14d
740e18  call MSG_WriteBits
740e1d  jmp loc_7400F2
740e22  call MSG_WriteBit1
740e27  mov edx, 0Ch
740e2c  mov rdi, r13
740e2f  mov esi, ebx
740e31  movzx r15d, r14w
740e35  call MSG_WriteBits
740e3a  cmp r15d, 1000h
740e41  jb short loc_740E80
740e43  mov esi, dword ptr [rbp+var_60]
740e46  lea rdi, aCompressedtoan_0; "CompressedToAngle called with out of ba"...
740e4d  xor eax, eax
740e4f  call va
740e54  mov rbx, rax
740e57  lea rdi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
740e5e  lea rcx, aSS_242; "%s\n\t%s"
740e65  lea r8, aX0XCompressedA_0; "(x >= 0) && (x <= COMPRESSED_ANGLE_RANG"...
740e6c  mov esi, 55Dh
740e71  mov edx, 0
740e76  xor eax, eax
740e78  mov r9, rbx
740e7b  call MyAssertHandler
740e80  mov r13, [rbp+var_70]
740e84  test byte ptr [rbp+var_68], 1
740e88  jnz short loc_740ECD
740e8a  vmovaps xmm0, [rbp+var_50]
740e8f  lea rdi, aAngletocompres_0; "AngleToCompressed called with a non nor"...
740e96  mov al, 1
740e98  vcvtss2sd xmm0, xmm0, xmm0
740e9c  call va
740ea1  mov rbx, rax
740ea4  lea rdi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
740eab  lea rcx, aSS_242; "%s\n\t%s"
740eb2  lea r8, aIsanglenormali_4; "IsAngleNormalized360(x)"
740eb9  mov esi, 550h
740ebe  mov edx, 0
740ec3  xor eax, eax
740ec5  mov r9, rbx
740ec8  call MyAssertHandler
740ecd  vxorps xmm0, xmm0, xmm0
740ed1  vcvtsi2ss xmm0, xmm0, r14d
740ed6  cmp r13, r14
740ed9  jz short loc_740EF9
740edb  lea rsi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
740ee2  mov edx, 552h
740ee7  mov rdi, r13
740eea  vmovss dword ptr [rbp+var_40], xmm0
740eef  call truncate_cast_assert_with_info
740ef4  vmovss xmm0, dword ptr [rbp+var_40]
740ef9  vmulss xmm0, xmm0, cs:dword_FA0C40
740f01  movzx eax, r14w
740f05  cmp eax, 1000h
740f0a  jb loc_740F98
740f10  mov ebx, dword ptr [rbp+var_60]
740f13  lea rdi, aCompressedangl_1; "compressedAngle %d not within 0-%d rang"...
740f1a  mov edx, 0FFFh
740f1f  xor eax, eax
740f21  vmovss dword ptr [rbp+var_40], xmm0
740f26  mov esi, ebx
740f28  call va
740f2d  mov rcx, rax
740f30  lea r15, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
740f37  lea r12, aSS_242; "%s\n\t%s"
740f3e  lea r8, aCompressedangl_2; "(compressedAngle >= 0.f) && (compressed"...
740f45  mov esi, 556h
740f4a  mov edx, 0
740f4f  xor eax, eax
740f51  mov r9, rcx
740f54  mov rdi, r15
740f57  mov rcx, r12
740f5a  call MyAssertHandler
740f5f  lea rdi, aCompressedtoan_0; "CompressedToAngle called with out of ba"...
740f66  xor eax, eax
740f68  mov esi, ebx
740f6a  call va
740f6f  mov rcx, rax
740f72  lea r8, aX0XCompressedA_0; "(x >= 0) && (x <= COMPRESSED_ANGLE_RANG"...
740f79  mov esi, 55Dh
740f7e  mov edx, 0
740f83  xor eax, eax
740f85  mov rdi, r15
740f88  mov r9, rcx
740f8b  mov rcx, r12
740f8e  call MyAssertHandler
740f93  vmovss xmm0, dword ptr [rbp+var_40]
740f98  mov bl, 1
740f9a  vucomiss xmm0, xmm0
740f9e  jnp loc_7400F4
740fa4  movzx eax, r14w
740fa8  vmovss dword ptr [rbp+var_40], xmm0
740fad  cmp eax, 1000h
740fb2  jb short loc_740FEE
740fb4  mov esi, dword ptr [rbp+var_60]
740fb7  lea rdi, aCompressedtoan_0; "CompressedToAngle called with out of ba"...
740fbe  xor eax, eax
740fc0  call va
740fc5  mov r9, rax
740fc8  lea rdi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
740fcf  lea rcx, aSS_242; "%s\n\t%s"
740fd6  lea r8, aX0XCompressedA_0; "(x >= 0) && (x <= COMPRESSED_ANGLE_RANG"...
740fdd  mov esi, 55Dh
740fe2  mov edx, 0
740fe7  xor eax, eax
740fe9  call MyAssertHandler
740fee  test byte ptr [rbp+var_68], 1
740ff2  jnz short loc_741034
740ff4  vmovaps xmm0, [rbp+var_50]
740ff9  lea rdi, aAngletocompres_0; "AngleToCompressed called with a non nor"...
741000  mov al, 1
741002  vcvtss2sd xmm0, xmm0, xmm0
741006  call va
74100b  mov r9, rax
74100e  lea rdi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
741015  lea rcx, aSS_242; "%s\n\t%s"
74101c  lea r8, aIsanglenormali_4; "IsAngleNormalized360(x)"
741023  mov esi, 550h
741028  mov edx, 0
74102d  xor eax, eax
74102f  call MyAssertHandler
741034  cmp r13, r14
741037  jz short loc_74104D
741039  lea rsi, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
741040  mov edx, 552h
741045  mov rdi, r13
741048  call truncate_cast_assert_with_info
74104d  vmovss xmm0, dword ptr [rbp+var_40]
741052  movzx eax, r14w
741056  cmp eax, 1000h
74105b  vcvtss2sd xmm0, xmm0, xmm0
74105f  jb loc_7410F0
741065  mov r14d, dword ptr [rbp+var_60]
741069  lea rdi, aCompressedangl_1; "compressedAngle %d not within 0-%d rang"...
741070  mov edx, 0FFFh
741075  xor eax, eax
741077  vmovsd [rbp+var_40], xmm0
74107c  mov esi, r14d
74107f  call va
741084  mov rcx, rax
741087  lea r15, aDH1CodeSourceR_1287; "D:\\h1\\code_source\\Runtime\\qcommon/."...
74108e  lea r12, aSS_242; "%s\n\t%s"
741095  lea r8, aCompressedangl_2; "(compressedAngle >= 0.f) && (compressed"...
74109c  mov esi, 556h
7410a1  mov edx, 0
7410a6  xor eax, eax
7410a8  mov r9, rcx
7410ab  mov rdi, r15
7410ae  mov rcx, r12
7410b1  call MyAssertHandler
7410b6  lea rdi, aCompressedtoan_0; "CompressedToAngle called with out of ba"...
7410bd  xor eax, eax
7410bf  mov esi, r14d
7410c2  call va
7410c7  mov rcx, rax
7410ca  lea r8, aX0XCompressedA_0; "(x >= 0) && (x <= COMPRESSED_ANGLE_RANG"...
7410d1  mov esi, 55Dh
7410d6  mov edx, 0
7410db  xor eax, eax
7410dd  mov rdi, r15
7410e0  mov r9, rcx
7410e3  mov rcx, r12
7410e6  call MyAssertHandler
7410eb  vmovsd xmm0, [rbp+var_40]
7410f0  lea rdi, aFF_2; "%f != %f"
7410f7  mov al, 2
7410f9  vmovapd xmm1, xmm0
7410fd  call va
741102  mov r9, rax
741105  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
74110c  lea rcx, aSS_242; "%s\n\t%s"
741113  lea r8, aCompressedtoan_1; "CompressedToAngle( newValAsShort ) == C"...
74111a  mov esi, 690h
74111f  mov edx, 0
741124  xor eax, eax
741126  call MyAssertHandler
74112b  jmp loc_7400F4
741130  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
741137  lea rcx, aS_501; "%s"
74113e  lea r8, aNetfieldindex0; "netfieldIndex >= 0"
741145  mov esi, 8FAh
74114a  xor edx, edx
74114c  xor eax, eax
74114e  call MyAssertHandler
741153  mov rax, qword ptr [rbp+var_50]
741157  movsx eax, byte ptr [rax+0Eh]
74115b  mov r10, r15
74115e  lea r9d, [r12+rax*4]
741162  mov rsi, [rbp+var_40]
741166  mov rdx, [rbp+var_68]
74116a  mov rcx, qword ptr [rbp+var_50]
74116e  mov rdi, rbx
741171  mov r8, r10
741174  call MSG_WriteEvent
741179  jmp loc_7400F2
74117e  mov rdi, r12
741181  call MSG_WriteBit1
741186  jmp loc_7400F2
74118b  movsx r15d, word ptr [r8]; jumptable 00000000007402C6 case -2
74118f  jmp loc_7409B5
741194  movsx r15d, byte ptr [r8]; jumptable 00000000007402C6 case -1
741198  jmp loc_7409B5
74119d  movzx r15d, byte ptr [r8]; jumptable 00000000007402C6 case 1
7411a1  jmp loc_7409B5
7411a6  movzx r15d, word ptr [r8]; jumptable 00000000007402C6 case 2
7411aa  jmp loc_7409B5
7411af  movsx r15d, word ptr [r8]; jumptable 00000000007403B8 case -2
7411b3  jmp loc_740A50
7411b8  movsx r15d, byte ptr [r8]; jumptable 00000000007403B8 case -1
7411bc  jmp loc_740A50
7411c1  movzx r15d, byte ptr [r8]; jumptable 00000000007403B8 case 1
7411c5  jmp loc_740A50
7411ca  movzx r15d, word ptr [r8]; jumptable 00000000007403B8 case 2
7411ce  jmp loc_740A50
7411d3  movsx ebx, word ptr [r8]; jumptable 0000000000740899 case -2
7411d7  jmp loc_740AB6
7411dc  movsx ebx, byte ptr [r8]; jumptable 0000000000740899 case -1
7411e0  jmp loc_740AB6
7411e5  movzx ebx, byte ptr [r8]; jumptable 0000000000740899 case 1
7411e9  jmp loc_740AB6
7411ee  movzx ebx, word ptr [r8]; jumptable 0000000000740899 case 2
7411f2  jmp loc_740AB6
7411f7  movsx r13d, word ptr [r8]; jumptable 0000000000740926 case -2
7411fb  mov qword ptr [rbp+var_50], rdx
7411ff  mov rax, qword ptr [rbp+var_60]; jumptable 0000000000740B43 case 2
741203  movsx r12d, word ptr [rax]
741207  jmp short loc_74123D
741209  movsx r13d, byte ptr [r8]; jumptable 0000000000740926 case -1
74120d  mov qword ptr [rbp+var_50], rdx
741211  mov rax, qword ptr [rbp+var_60]; jumptable 0000000000740B43 case 3
741215  movsx r12d, byte ptr [rax]
741219  jmp short loc_74123D
74121b  movzx r13d, byte ptr [r8]; jumptable 0000000000740926 case 1
74121f  mov qword ptr [rbp+var_50], rdx
741223  mov rax, qword ptr [rbp+var_60]; jumptable 0000000000740B43 case 5
741227  movzx r12d, byte ptr [rax]
74122b  jmp short loc_74123D
74122d  movzx r13d, word ptr [r8]; jumptable 0000000000740926 case 2
741231  mov qword ptr [rbp+var_50], rdx
741235  mov rax, qword ptr [rbp+var_60]; jumptable 0000000000740B43 case 6
741239  movzx r12d, word ptr [rax]
74123d  sub r13d, r12d
741240  lea r12d, [r13-1]
741244  cmp r12d, 0Fh
741248  ja short loc_741285
74124a  test r15b, r15b
74124d  jnz short loc_74125D
74124f  cmp byte ptr [rbx+1Ch], 0
741253  jnz short loc_74125D
741255  mov edi, r13d
741258  call SV_TrackEventSeqDeltaSend
74125d  mov r14, [rbp+var_40]
741261  mov rdi, r14
741264  call MSG_WriteBit1
741269  mov edi, 10h
74126e  call GetMinBitCountForNum
741273  mov rdi, r14
741276  mov esi, r12d
741279  mov edx, eax
74127b  call MSG_WriteBits
741280  jmp loc_7400F2
741285  mov r12, r8
741288  test r15b, r15b
74128b  jnz short loc_74129B
74128d  cmp byte ptr [rbx+1Ch], 0
741291  jnz short loc_74129B
741293  mov edi, r13d
741296  call SV_TrackEventSeqFullSend
74129b  mov rbx, [rbp+var_40]
74129f  mov rdi, rbx
7412a2  call MSG_WriteBit0
7412a7  mov rax, [rbp+var_78]
7412ab  mov rsi, qword ptr [rbp+var_60]
7412af  mov r8, qword ptr [rbp+var_50]
7412b3  mov ecx, 8
7412b8  mov rdi, rbx
7412bb  mov rdx, r12
7412be  mov r9, [rax]
7412c1  jmp loc_73FFCD
7412c6  mov rdi, [rbp+var_40]
7412ca  vmovss dword ptr [rbp+var_60], xmm3
7412cf  mov r12d, edx
7412d2  mov dword ptr [rbp+var_50], esi
7412d5  call MSG_WriteBit0
7412da  cmp r12d, dword ptr [rbp+var_50]
7412de  jz short loc_741315
7412e0  cmp r13d, 1000h
7412e7  jge short loc_741315
7412e9  test r15b, r15b
7412ec  jnz short loc_7412FC
7412ee  cmp byte ptr [rbx+1Ch], 0
7412f2  jnz short loc_7412FC
7412f4  mov edi, r14d
7412f7  call SV_TrackAngleDeltaBits
7412fc  mov rdi, [rbp+var_40]
741300  call MSG_WriteBit1
741305  test r14d, r14d
741308  js short loc_741343
74130a  mov rdi, [rbp+var_40]
74130e  call MSG_WriteBit0
741313  jmp short loc_74134C
741315  test r15b, r15b
741318  jnz short loc_741325
74131a  cmp byte ptr [rbx+1Ch], 0
74131e  jnz short loc_741325
741320  call SV_TrackAngleFullSend
741325  mov rbx, [rbp+var_40]
741329  mov rdi, rbx
74132c  call MSG_WriteBit0
741331  vmovss xmm0, dword ptr [rbp+var_60]
741336  mov rdi, rbx
741339  call MSG_WriteAngle16
74133e  jmp loc_7400F2
741343  mov rdi, [rbp+var_40]
741347  call MSG_WriteBit1
74134c  mov rdi, [rbp+var_40]
741350  mov edx, 0Ch
741355  mov esi, r13d
741358  call MSG_WriteBits
74135d  vcvtsi2ss xmm0, xmm0, r12d
741362  vmulss xmm0, xmm0, cs:dword_FA0C48
74136a  mov bl, 1
74136c  vucomiss xmm0, xmm0
741370  jnp loc_7400F4
741376  vcvtss2sd xmm0, xmm0, xmm0
74137a  lea rdi, aFF_2; "%f != %f"
741381  mov al, 2
741383  vmovapd xmm1, xmm0
741387  call va
74138c  mov r9, rax
74138f  lea rdi, aDH1CodeSourceR_1283; "D:\\h1\\code_source\\Runtime\\qcommon\\"...
741396  lea rcx, aSS_242; "%s\n\t%s"
74139d  lea r8, aShort2angleNew; "SHORT2ANGLE( newValAsShort ) == SHORT2A"...
7413a4  mov esi, 64Bh
7413a9  jmp loc_74111F
7413ae  call PL__stack_chk_fail
7413b3  nop
7413b4  nop word ptr [rax+rax+00000000h]
