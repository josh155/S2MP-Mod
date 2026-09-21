4ef6c0  push rbx
4ef6c2  push r12
4ef6c4  push r13
4ef6c6  sub rsp, 210h
4ef6cd  mov rax, cs:qword_12F8CB0
4ef6d4  xor rax, rsp
4ef6d7  mov [rsp+228h+var_48], rax
4ef6df  mov [rsp+228h+var_208], r9
4ef6e4  mov r12, r9
4ef6e7  mov r13, r8
4ef6ea  mov rbx, rcx
4ef6ed  test r8, r8
4ef6f0  jnz short loc_4EF709
4ef6f2  xor edx, edx
4ef6f4  lea rcx, [rsp+228h+var_1E8]
4ef6f9  mov r8d, 194h
4ef6ff  lea r13, [rsp+228h+var_1E8]
4ef704  call sub_59F7E0
4ef709  mov rcx, rbx
4ef70c  call MSG_ReadBit; CORRECTED from MSG_ReadShort (a false positive of the same-game call-graph
4ef711  test eax, eax
4ef713  jnz loc_4EF7A5
4ef719  mov eax, 3
4ef71e  xchg ax, ax
4ef720  lea r12, [r12+80h]
4ef728  movups xmm0, xmmword ptr [r13+0]
4ef72d  lea r13, [r13+80h]
4ef734  movups xmmword ptr [r12-80h], xmm0
4ef73a  movups xmm1, xmmword ptr [r13-70h]
4ef73f  movups xmmword ptr [r12-70h], xmm1
4ef745  movups xmm0, xmmword ptr [r13-60h]
4ef74a  movups xmmword ptr [r12-60h], xmm0
4ef750  movups xmm1, xmmword ptr [r13-50h]
4ef755  movups xmmword ptr [r12-50h], xmm1
4ef75b  movups xmm0, xmmword ptr [r13-40h]
4ef760  movups xmmword ptr [r12-40h], xmm0
4ef766  movups xmm1, xmmword ptr [r13-30h]
4ef76b  movups xmmword ptr [r12-30h], xmm1
4ef771  movups xmm0, xmmword ptr [r13-20h]
4ef776  movups xmmword ptr [r12-20h], xmm0
4ef77c  movups xmm1, xmmword ptr [r13-10h]
4ef781  movups xmmword ptr [r12-10h], xmm1
4ef787  sub rax, 1
4ef78b  jnz short loc_4EF720
4ef78d  movups xmm0, xmmword ptr [r13+0]
4ef792  movups xmmword ptr [r12], xmm0
4ef797  mov eax, [r13+10h]
4ef79b  mov [r12+10h], eax
4ef7a0  jmp loc_4EFFBC
4ef7a5  mov [rsp+228h+arg_8], rbp
4ef7ad  mov [rsp+228h+var_20], rsi
4ef7b5  mov [rsp+228h+var_28], rdi
4ef7bd  mov [rsp+228h+var_30], r14
4ef7c5  mov r14, r12
4ef7c8  mov [rsp+228h+var_38], r15
4ef7d0  mov r15, r13
4ef7d3  sub r15, r12
4ef7d6  mov [rsp+228h+var_1F8], r15
4ef7db  mov r15d, 2
4ef7e1  mov r12, [rsp+228h+var_1F8]
4ef7e6  nop word ptr [rax+rax+00000000h]
4ef7f0  mov ebp, [r12+r14]
4ef7f4  mov rcx, rbx
4ef7f7  call MSG_ReadBit; CORRECTED from MSG_ReadShort (a false positive of the same-game call-graph
4ef7fc  test eax, eax
4ef7fe  jz short loc_4EF81F
4ef800  xor esi, esi
4ef802  xor edi, edi
4ef804  mov rcx, rbx
4ef807  call MSG_ReadByte; Basis: Arxan-obfuscated body; identified from use (deltaNum, snapFlags)
4ef80c  mov ecx, edi
4ef80e  add edi, 8
4ef811  shl eax, cl
4ef813  or esi, eax
4ef815  cmp edi, 10h
4ef818  jl short loc_4EF804
4ef81a  movzx ebp, bp
4ef81d  xor ebp, esi
4ef81f  mov [r14], ebp
4ef822  add r14, 4
4ef826  sub r15, 1
4ef82a  jnz short loc_4EF7F0
4ef82c  mov r12, [rsp+228h+var_208]
4ef831  xor eax, eax
4ef833  mov [rsp+228h+var_200], rax
4ef838  nop dword ptr [rax+rax+00000000h]
4ef840  mov r9d, [rbx+28h]
4ef844  lea rax, [rax+rax*8]
4ef848  lea r14, ds:0[rax*2]
4ef850  add r14, r13
4ef853  lea r15, [r12+rax*2]
4ef857  and r9d, 7
4ef85b  jnz short loc_4EF8AF
4ef85d  mov ecx, [rbx+20h]
4ef860  mov r8d, [rbx+1Ch]
4ef864  add ecx, r8d
4ef867  mov edx, [rbx+24h]
4ef86a  cmp edx, ecx
4ef86c  jl short loc_4EF89F
4ef86e  mov dword ptr [rbx], 1
4ef874  mov r9d, [rbx+28h]
4ef878  movzx edi, byte ptr [r14+8]
4ef87d  and r9d, 7
4ef881  jnz loc_4EF91A
4ef887  mov ecx, [rbx+20h]
4ef88a  mov edx, [rbx+24h]
4ef88d  add ecx, r8d
4ef890  cmp edx, ecx
4ef892  jl short loc_4EF90A
4ef894  mov dword ptr [rbx], 1
4ef89a  jmp loc_4EF958
4ef89f  lea eax, ds:0[rdx*8]
4ef8a6  mov [rbx+28h], eax
4ef8a9  lea eax, [rdx+1]
4ef8ac  mov [rbx+24h], eax
4ef8af  mov r10d, [rbx+28h]
4ef8b3  mov eax, r10d
4ef8b6  mov r8d, [rbx+1Ch]
4ef8ba  sar eax, 3
4ef8bd  mov ecx, eax
4ef8bf  sub ecx, r8d
4ef8c2  js short loc_4EF8D1
4ef8c4  mov rax, [rbx+10h]
4ef8c8  movsxd rcx, ecx
4ef8cb  movzx edx, byte ptr [rcx+rax]
4ef8cf  jmp short loc_4EF8DC
4ef8d1  movsxd rdx, eax
4ef8d4  mov rax, [rbx+8]
4ef8d8  movzx edx, byte ptr [rdx+rax]
4ef8dc  lea eax, [r10+1]
4ef8e0  movzx ecx, r9b
4ef8e4  mov [rbx+28h], eax
4ef8e7  movzx eax, dl
4ef8ea  shr eax, cl
4ef8ec  and eax, 1
4ef8ef  jnz short loc_4EF874
4ef8f1  movups xmm0, xmmword ptr [r14+8]
4ef8f6  movups xmmword ptr [r15+8], xmm0
4ef8fb  movzx eax, word ptr [r14+18h]
4ef900  mov [r15+18h], ax
4ef905  jmp loc_4EFE0B
4ef90a  lea eax, ds:0[rdx*8]
4ef911  mov [rbx+28h], eax
4ef914  lea eax, [rdx+1]
4ef917  mov [rbx+24h], eax
4ef91a  mov r10d, [rbx+28h]
4ef91e  mov eax, r10d
4ef921  sar eax, 3
4ef924  mov ecx, eax
4ef926  sub ecx, r8d
4ef929  js short loc_4EF938
4ef92b  mov rax, [rbx+10h]
4ef92f  movsxd rcx, ecx
4ef932  movzx edx, byte ptr [rcx+rax]
4ef936  jmp short loc_4EF943
4ef938  movsxd rdx, eax
4ef93b  mov rax, [rbx+8]
4ef93f  movzx edx, byte ptr [rdx+rax]
4ef943  lea eax, [r10+1]
4ef947  movzx ecx, r9b
4ef94b  mov [rbx+28h], eax
4ef94e  movzx eax, dl
4ef951  shr eax, cl
4ef953  and eax, 1
4ef956  jz short loc_4EF96A
4ef958  mov edx, 5
4ef95d  mov rcx, rbx
4ef960  call MSG_ReadBits; MSG_ReadBits
4ef965  and edi, 1Fh
4ef968  xor edi, eax
4ef96a  mov [r15+8], dil
4ef96e  mov r8d, [rbx+28h]
4ef972  movzx esi, word ptr [r14+0Eh]
4ef977  and r8d, 7
4ef97b  jnz short loc_4EF9A2
4ef97d  mov eax, [rbx+20h]
4ef980  add eax, [rbx+1Ch]
4ef983  mov ecx, [rbx+24h]
4ef986  cmp ecx, eax
4ef988  jl short loc_4EF992
4ef98a  mov dword ptr [rbx], 1
4ef990  jmp short loc_4EF9E0
4ef992  lea eax, ds:0[rcx*8]
4ef999  mov [rbx+28h], eax
4ef99c  lea eax, [rcx+1]
4ef99f  mov [rbx+24h], eax
4ef9a2  mov r9d, [rbx+28h]
4ef9a6  mov eax, r9d
4ef9a9  sar eax, 3
4ef9ac  mov ecx, eax
4ef9ae  sub ecx, [rbx+1Ch]
4ef9b1  js short loc_4EF9C0
4ef9b3  mov rax, [rbx+10h]
4ef9b7  movsxd rcx, ecx
4ef9ba  movzx edx, byte ptr [rcx+rax]
4ef9be  jmp short loc_4EF9CB
4ef9c0  movsxd rdx, eax
4ef9c3  mov rax, [rbx+8]
4ef9c7  movzx edx, byte ptr [rdx+rax]
4ef9cb  lea eax, [r9+1]
4ef9cf  movzx ecx, r8b
4ef9d3  mov [rbx+28h], eax
4ef9d6  movzx eax, dl
4ef9d9  shr eax, cl
4ef9db  and eax, 1
4ef9de  jz short loc_4EFA04
4ef9e0  mov edx, 2
4ef9e5  mov rcx, rbx
4ef9e8  call MSG_ReadBits; MSG_ReadBits
4ef9ed  mov rcx, rbx
4ef9f0  mov edi, eax
4ef9f2  call MSG_ReadByte; Basis: Arxan-obfuscated body; identified from use (deltaNum, snapFlags)
4ef9f7  shl eax, 2
4ef9fa  and esi, 3FFh
4efa00  or edi, eax
4efa02  xor esi, edi
4efa04  mov [r15+0Eh], si
4efa09  mov r8d, [rbx+28h]
4efa0d  movzx ebp, word ptr [r14+0Ah]
4efa12  and r8d, 7
4efa16  jnz short loc_4EFA3D
4efa18  mov eax, [rbx+20h]
4efa1b  add eax, [rbx+1Ch]
4efa1e  mov ecx, [rbx+24h]
4efa21  cmp ecx, eax
4efa23  jl short loc_4EFA2D
4efa25  mov dword ptr [rbx], 1
4efa2b  jmp short loc_4EFA7B
4efa2d  lea eax, ds:0[rcx*8]
4efa34  mov [rbx+28h], eax
4efa37  lea eax, [rcx+1]
4efa3a  mov [rbx+24h], eax
4efa3d  mov r9d, [rbx+28h]
4efa41  mov eax, r9d
4efa44  sar eax, 3
4efa47  mov ecx, eax
4efa49  sub ecx, [rbx+1Ch]
4efa4c  js short loc_4EFA5B
4efa4e  mov rax, [rbx+10h]
4efa52  movsxd rcx, ecx
4efa55  movzx edx, byte ptr [rcx+rax]
4efa59  jmp short loc_4EFA66
4efa5b  movsxd rdx, eax
4efa5e  mov rax, [rbx+8]
4efa62  movzx edx, byte ptr [rdx+rax]
4efa66  lea eax, [r9+1]
4efa6a  movzx ecx, r8b
4efa6e  mov [rbx+28h], eax
4efa71  movzx eax, dl
4efa74  shr eax, cl
4efa76  and eax, 1
4efa79  jz short loc_4EFA98
4efa7b  xor esi, esi
4efa7d  xor edi, edi
4efa7f  nop
4efa80  mov rcx, rbx
4efa83  call MSG_ReadByte; Basis: Arxan-obfuscated body; identified from use (deltaNum, snapFlags)
4efa88  mov ecx, edi
4efa8a  add edi, 8
4efa8d  shl eax, cl
4efa8f  or esi, eax
4efa91  cmp edi, 10h
4efa94  jl short loc_4EFA80
4efa96  xor ebp, esi
4efa98  mov [r15+0Ah], bp
4efa9d  mov r8d, [rbx+28h]
4efaa1  movzx ebp, word ptr [r14+0Ch]
4efaa6  and r8d, 7
4efaaa  jnz short loc_4EFAD1
4efaac  mov eax, [rbx+20h]
4efaaf  add eax, [rbx+1Ch]
4efab2  mov ecx, [rbx+24h]
4efab5  cmp ecx, eax
4efab7  jl short loc_4EFAC1
4efab9  mov dword ptr [rbx], 1
4efabf  jmp short loc_4EFB0F
4efac1  lea eax, ds:0[rcx*8]
4efac8  mov [rbx+28h], eax
4efacb  lea eax, [rcx+1]
4eface  mov [rbx+24h], eax
4efad1  mov r9d, [rbx+28h]
4efad5  mov eax, r9d
4efad8  sar eax, 3
4efadb  mov ecx, eax
4efadd  sub ecx, [rbx+1Ch]
4efae0  js short loc_4EFAEF
4efae2  mov rax, [rbx+10h]
4efae6  movsxd rcx, ecx
4efae9  movzx edx, byte ptr [rcx+rax]
4efaed  jmp short loc_4EFAFA
4efaef  movsxd rdx, eax
4efaf2  mov rax, [rbx+8]
4efaf6  movzx edx, byte ptr [rdx+rax]
4efafa  lea eax, [r9+1]
4efafe  movzx ecx, r8b
4efb02  mov [rbx+28h], eax
4efb05  movzx eax, dl
4efb08  shr eax, cl
4efb0a  and eax, 1
4efb0d  jz short loc_4EFB2B
4efb0f  xor esi, esi
4efb11  xor edi, edi
4efb13  mov rcx, rbx
4efb16  call MSG_ReadByte; Basis: Arxan-obfuscated body; identified from use (deltaNum, snapFlags)
4efb1b  mov ecx, edi
4efb1d  add edi, 8
4efb20  shl eax, cl
4efb22  or esi, eax
4efb24  cmp edi, 10h
4efb27  jl short loc_4EFB13
4efb29  xor ebp, esi
4efb2b  mov [r15+0Ch], bp
4efb30  mov r8d, [rbx+28h]
4efb34  movzx esi, word ptr [r14+10h]
4efb39  and r8d, 7
4efb3d  jnz short loc_4EFB64
4efb3f  mov eax, [rbx+20h]
4efb42  add eax, [rbx+1Ch]
4efb45  mov ecx, [rbx+24h]
4efb48  cmp ecx, eax
4efb4a  jl short loc_4EFB54
4efb4c  mov dword ptr [rbx], 1
4efb52  jmp short loc_4EFBA2
4efb54  lea eax, ds:0[rcx*8]
4efb5b  mov [rbx+28h], eax
4efb5e  lea eax, [rcx+1]
4efb61  mov [rbx+24h], eax
4efb64  mov r9d, [rbx+28h]
4efb68  mov eax, r9d
4efb6b  sar eax, 3
4efb6e  mov ecx, eax
4efb70  sub ecx, [rbx+1Ch]
4efb73  js short loc_4EFB82
4efb75  mov rax, [rbx+10h]
4efb79  movsxd rcx, ecx
4efb7c  movzx edx, byte ptr [rcx+rax]
4efb80  jmp short loc_4EFB8D
4efb82  movsxd rdx, eax
4efb85  mov rax, [rbx+8]
4efb89  movzx edx, byte ptr [rdx+rax]
4efb8d  lea eax, [r9+1]
4efb91  movzx ecx, r8b
4efb95  mov [rbx+28h], eax
4efb98  movzx eax, dl
4efb9b  shr eax, cl
4efb9d  and eax, 1
4efba0  jz short loc_4EFBC6
4efba2  mov edx, 2
4efba7  mov rcx, rbx
4efbaa  call MSG_ReadBits; MSG_ReadBits
4efbaf  mov rcx, rbx
4efbb2  mov edi, eax
4efbb4  call MSG_ReadByte; Basis: Arxan-obfuscated body; identified from use (deltaNum, snapFlags)
4efbb9  shl eax, 2
4efbbc  and esi, 3FFh
4efbc2  or edi, eax
4efbc4  xor esi, edi
4efbc6  mov [r15+10h], si
4efbcb  mov r8d, [rbx+28h]
4efbcf  movzx ebp, word ptr [r14+12h]
4efbd4  and r8d, 7
4efbd8  jnz short loc_4EFBFF
4efbda  mov eax, [rbx+20h]
4efbdd  add eax, [rbx+1Ch]
4efbe0  mov ecx, [rbx+24h]
4efbe3  cmp ecx, eax
4efbe5  jl short loc_4EFBEF
4efbe7  mov dword ptr [rbx], 1
4efbed  jmp short loc_4EFC3D
4efbef  lea eax, ds:0[rcx*8]
4efbf6  mov [rbx+28h], eax
4efbf9  lea eax, [rcx+1]
4efbfc  mov [rbx+24h], eax
4efbff  mov r9d, [rbx+28h]
4efc03  mov eax, r9d
4efc06  sar eax, 3
4efc09  mov ecx, eax
4efc0b  sub ecx, [rbx+1Ch]
4efc0e  js short loc_4EFC1D
4efc10  mov rax, [rbx+10h]
4efc14  movsxd rcx, ecx
4efc17  movzx edx, byte ptr [rcx+rax]
4efc1b  jmp short loc_4EFC28
4efc1d  movsxd rdx, eax
4efc20  mov rax, [rbx+8]
4efc24  movzx edx, byte ptr [rdx+rax]
4efc28  lea eax, [r9+1]
4efc2c  movzx ecx, r8b
4efc30  mov [rbx+28h], eax
4efc33  movzx eax, dl
4efc36  shr eax, cl
4efc38  and eax, 1
4efc3b  jz short loc_4EFC59
4efc3d  xor esi, esi
4efc3f  xor edi, edi
4efc41  mov rcx, rbx
4efc44  call MSG_ReadByte; Basis: Arxan-obfuscated body; identified from use (deltaNum, snapFlags)
4efc49  mov ecx, edi
4efc4b  add edi, 8
4efc4e  shl eax, cl
4efc50  or esi, eax
4efc52  cmp edi, 10h
4efc55  jl short loc_4EFC41
4efc57  xor ebp, esi
4efc59  mov [r15+12h], bp
4efc5e  mov r8d, [rbx+28h]
4efc62  movzx esi, word ptr [r14+14h]
4efc67  and r8d, 7
4efc6b  jnz short loc_4EFC92
4efc6d  mov eax, [rbx+20h]
4efc70  add eax, [rbx+1Ch]
4efc73  mov ecx, [rbx+24h]
4efc76  cmp ecx, eax
4efc78  jl short loc_4EFC82
4efc7a  mov dword ptr [rbx], 1
4efc80  jmp short loc_4EFCD0
4efc82  lea eax, ds:0[rcx*8]
4efc89  mov [rbx+28h], eax
4efc8c  lea eax, [rcx+1]
4efc8f  mov [rbx+24h], eax
4efc92  mov r9d, [rbx+28h]
4efc96  mov eax, r9d
4efc99  sar eax, 3
4efc9c  mov ecx, eax
4efc9e  sub ecx, [rbx+1Ch]
4efca1  js short loc_4EFCB0
4efca3  mov rax, [rbx+10h]
4efca7  movsxd rcx, ecx
4efcaa  movzx edx, byte ptr [rcx+rax]
4efcae  jmp short loc_4EFCBB
4efcb0  movsxd rdx, eax
4efcb3  mov rax, [rbx+8]
4efcb7  movzx edx, byte ptr [rdx+rax]
4efcbb  lea eax, [r9+1]
4efcbf  movzx ecx, r8b
4efcc3  mov [rbx+28h], eax
4efcc6  movzx eax, dl
4efcc9  shr eax, cl
4efccb  and eax, 1
4efcce  jz short loc_4EFCF4
4efcd0  mov edx, 2
4efcd5  mov rcx, rbx
4efcd8  call MSG_ReadBits; MSG_ReadBits
4efcdd  mov rcx, rbx
4efce0  mov edi, eax
4efce2  call MSG_ReadByte; Basis: Arxan-obfuscated body; identified from use (deltaNum, snapFlags)
4efce7  shl eax, 2
4efcea  and esi, 3FFh
4efcf0  or edi, eax
4efcf2  xor esi, edi
4efcf4  mov [r15+14h], si
4efcf9  mov r8d, [rbx+28h]
4efcfd  movzx edi, word ptr [r14+16h]
4efd02  and r8d, 7
4efd06  jnz short loc_4EFD2D
4efd08  mov eax, [rbx+20h]
4efd0b  add eax, [rbx+1Ch]
4efd0e  mov ecx, [rbx+24h]
4efd11  cmp ecx, eax
4efd13  jl short loc_4EFD1D
4efd15  mov dword ptr [rbx], 1
4efd1b  jmp short loc_4EFD6B
4efd1d  lea eax, ds:0[rcx*8]
4efd24  mov [rbx+28h], eax
4efd27  lea eax, [rcx+1]
4efd2a  mov [rbx+24h], eax
4efd2d  mov r9d, [rbx+28h]
4efd31  mov eax, r9d
4efd34  sar eax, 3
4efd37  mov ecx, eax
4efd39  sub ecx, [rbx+1Ch]
4efd3c  js short loc_4EFD4B
4efd3e  mov rax, [rbx+10h]
4efd42  movsxd rcx, ecx
4efd45  movzx edx, byte ptr [rcx+rax]
4efd49  jmp short loc_4EFD56
4efd4b  movsxd rdx, eax
4efd4e  mov rax, [rbx+8]
4efd52  movzx edx, byte ptr [rdx+rax]
4efd56  lea eax, [r9+1]
4efd5a  movzx ecx, r8b
4efd5e  mov [rbx+28h], eax
4efd61  movzx eax, dl
4efd64  shr eax, cl
4efd66  and eax, 1
4efd69  jz short loc_4EFD7D
4efd6b  mov edx, 6
4efd70  mov rcx, rbx
4efd73  call MSG_ReadBits; MSG_ReadBits
4efd78  and edi, 3Fh
4efd7b  xor edi, eax
4efd7d  mov [r15+16h], di
4efd82  mov r8d, [rbx+28h]
4efd86  movzx edi, word ptr [r14+18h]
4efd8b  and r8d, 7
4efd8f  jnz short loc_4EFDB6
4efd91  mov eax, [rbx+20h]
4efd94  add eax, [rbx+1Ch]
4efd97  mov ecx, [rbx+24h]
4efd9a  cmp ecx, eax
4efd9c  jl short loc_4EFDA6
4efd9e  mov dword ptr [rbx], 1
4efda4  jmp short loc_4EFDF4
4efda6  lea eax, ds:0[rcx*8]
4efdad  mov [rbx+28h], eax
4efdb0  lea eax, [rcx+1]
4efdb3  mov [rbx+24h], eax
4efdb6  mov r9d, [rbx+28h]
4efdba  mov eax, r9d
4efdbd  sar eax, 3
4efdc0  mov ecx, eax
4efdc2  sub ecx, [rbx+1Ch]
4efdc5  js short loc_4EFDD4
4efdc7  mov rax, [rbx+10h]
4efdcb  movsxd rcx, ecx
4efdce  movzx edx, byte ptr [rcx+rax]
4efdd2  jmp short loc_4EFDDF
4efdd4  movsxd rdx, eax
4efdd7  mov rax, [rbx+8]
4efddb  movzx edx, byte ptr [rdx+rax]
4efddf  lea eax, [r9+1]
4efde3  movzx ecx, r8b
4efde7  mov [rbx+28h], eax
4efdea  movzx eax, dl
4efded  shr eax, cl
4efdef  and eax, 1
4efdf2  jz short loc_4EFE06
4efdf4  mov edx, 5
4efdf9  mov rcx, rbx
4efdfc  call MSG_ReadBits; MSG_ReadBits
4efe01  and edi, 1Fh
4efe04  xor edi, eax
4efe06  mov [r15+18h], di
4efe0b  mov rax, [rsp+228h+var_200]
4efe10  inc rax
4efe13  mov [rsp+228h+var_200], rax
4efe18  cmp rax, 12h
4efe1c  jl loc_4EF840
4efe22  mov r8d, [rbx+28h]
4efe26  mov r14, [rsp+228h+var_30]
4efe2e  and r8d, 7
4efe32  jnz short loc_4EFE59
4efe34  mov eax, [rbx+20h]
4efe37  add eax, [rbx+1Ch]
4efe3a  mov ecx, [rbx+24h]
4efe3d  cmp ecx, eax
4efe3f  jl short loc_4EFE49
4efe41  mov dword ptr [rbx], 1
4efe47  jmp short loc_4EFE9B
4efe49  lea eax, ds:0[rcx*8]
4efe50  mov [rbx+28h], eax
4efe53  lea eax, [rcx+1]
4efe56  mov [rbx+24h], eax
4efe59  mov r9d, [rbx+28h]
4efe5d  mov eax, r9d
4efe60  sar eax, 3
4efe63  mov ecx, eax
4efe65  sub ecx, [rbx+1Ch]
4efe68  js short loc_4EFE77
4efe6a  mov rax, [rbx+10h]
4efe6e  movsxd rcx, ecx
4efe71  movzx edx, byte ptr [rcx+rax]
4efe75  jmp short loc_4EFE82
4efe77  movsxd rdx, eax
4efe7a  mov rax, [rbx+8]
4efe7e  movzx edx, byte ptr [rdx+rax]
4efe82  lea eax, [r9+1]
4efe86  movzx ecx, r8b
4efe8a  mov [rbx+28h], eax
4efe8d  movzx eax, dl
4efe90  shr eax, cl
4efe92  and eax, 1
4efe95  jz loc_4EFF45
4efe9b  mov r15, [rsp+228h+var_1F8]
4efea0  lea rsi, [r12+14Ch]
4efea8  mov ebp, 12h
4efead  nop dword ptr [rax]
4efeb0  mov r8d, [rbx+28h]
4efeb4  mov edi, [rsi+r15]
4efeb8  and r8d, 7
4efebc  jnz short loc_4EFEE3
4efebe  mov eax, [rbx+20h]
4efec1  add eax, [rbx+1Ch]
4efec4  mov ecx, [rbx+24h]
4efec7  cmp ecx, eax
4efec9  jl short loc_4EFED3
4efecb  mov dword ptr [rbx], 1
4efed1  jmp short loc_4EFF21
4efed3  lea eax, ds:0[rcx*8]
4efeda  mov [rbx+28h], eax
4efedd  lea eax, [rcx+1]
4efee0  mov [rbx+24h], eax
4efee3  mov r9d, [rbx+28h]
4efee7  mov eax, r9d
4efeea  sar eax, 3
4efeed  mov ecx, eax
4efeef  sub ecx, [rbx+1Ch]
4efef2  js short loc_4EFF01
4efef4  mov rax, [rbx+10h]
4efef8  movsxd rcx, ecx
4efefb  movzx edx, byte ptr [rcx+rax]
4efeff  jmp short loc_4EFF0C
4eff01  movsxd rdx, eax
4eff04  mov rax, [rbx+8]
4eff08  movzx edx, byte ptr [rdx+rax]
4eff0c  lea eax, [r9+1]
4eff10  movzx ecx, r8b
4eff14  mov [rbx+28h], eax
4eff17  movzx eax, dl
4eff1a  shr eax, cl
4eff1c  and eax, 1
4eff1f  jz short loc_4EFF33
4eff21  mov edx, 2
4eff26  mov rcx, rbx
4eff29  call MSG_ReadBits; MSG_ReadBits
4eff2e  and edi, 3
4eff31  xor edi, eax
4eff33  mov [rsi], edi
4eff35  add rsi, 4
4eff39  sub rbp, 1
4eff3d  jnz loc_4EFEB0
4eff43  jmp short loc_4EFF9C
4eff45  movups xmm0, xmmword ptr [r13+14Ch]
4eff4d  movups xmmword ptr [r12+14Ch], xmm0
4eff56  movups xmm1, xmmword ptr [r13+15Ch]
4eff5e  movups xmmword ptr [r12+15Ch], xmm1
4eff67  movups xmm0, xmmword ptr [r13+16Ch]
4eff6f  movups xmmword ptr [r12+16Ch], xmm0
4eff78  movups xmm1, xmmword ptr [r13+17Ch]
4eff80  movups xmmword ptr [r12+17Ch], xmm1
4eff89  movsd xmm0, qword ptr [r13+18Ch]
4eff92  movsd qword ptr [r12+18Ch], xmm0
4eff9c  mov rdi, [rsp+228h+var_28]
4effa4  mov rsi, [rsp+228h+var_20]
4effac  mov rbp, [rsp+228h+arg_8]
4effb4  mov r15, [rsp+228h+var_38]
4effbc  mov rcx, [rsp+228h+var_48]
4effc4  xor rcx, rsp; StackCookie
4effc7  call __security_check_cookie
4effcc  add rsp, 210h
4effd3  pop r13
4effd5  pop r12
4effd7  pop rbx
4effd8  retn