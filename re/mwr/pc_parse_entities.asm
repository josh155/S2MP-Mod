341d30  push rbx
341d32  push rbp
341d33  push rsi
341d34  push rdi
341d35  push r12
341d37  push r13
341d39  push r14
341d3b  push r15
341d3d  sub rsp, 2F8h
341d44  mov rax, cs:qword_12F8CB0
341d4b  xor rax, rsp
341d4e  mov [rsp+338h+var_58], rax
341d56  mov eax, [rcx+4AE8h]
341d5c  mov r13, rdx
341d5f  mov r15, [rsp+338h+arg_20]
341d67  mov rbp, rcx
341d6a  mov [rsp+338h+var_304], r8d
341d6f  lea rcx, [rsp+338h+var_1F8]
341d77  xor ebx, ebx
341d79  xor edx, edx
341d7b  mov r8d, 194h
341d81  mov [rsp+338h+var_300], rbx
341d86  mov [r15+4A58h], eax
341d8d  mov r14, r9
341d90  mov [r15+4A50h], ebx
341d97  call sub_826080
341d9c  mov [rsp+338h+var_308], ebx
341da0  lea rax, [rsp+338h+var_1F8]
341da8  mov [r15+4A30h], rax
341daf  mov r12d, ebx
341db2  lea r8, unk_2F7D1EC
341db9  mov esi, ebx
341dbb  test r14, r14
341dbe  jnz short loc_341DC7
341dc0  mov edi, 1869Fh
341dc5  jmp short loc_341E05
341dc7  cmp [r14+4A50h], ebx
341dce  jg short loc_341DD7
341dd0  mov edi, 1869Fh
341dd5  jmp short loc_341E05
341dd7  test byte ptr [r14+4A38h], 8
341ddf  jz short loc_341DE6
341de1  mov rbx, r8
341de4  jmp short loc_341E02
341de6  mov eax, [r14+4A58h]
341ded  cdq
341dee  idiv dword ptr [rbp+8F8Ch]
341df4  movsxd rbx, edx
341df7  shl rbx, 8
341dfb  add rbx, [rbp+8FA8h]
341e02  movsx edi, word ptr [rbx]
341e05  cmp [r13+0], esi
341e09  jnz loc_342102
341e0f  nop
341e10  mov edx, 0Bh
341e15  mov rcx, r13
341e18  call MSG_ReadEntityIndex; Basis: PS4 twin 0x724540
341e1d  cmp dword ptr [r13+0], 0
341e22  movsx r12d, ax
341e26  jnz loc_3420F6
341e2c  mov eax, 7FFh
341e31  cmp r12d, eax
341e34  jz loc_3420F6
341e3a  mov eax, [r13+1Ch]
341e3e  cmp [r13+24h], eax
341e42  jle short loc_341E55
341e44  lea rdx, unk_8FE5A8
341e4b  mov ecx, 1
341e50  call sub_159860
341e55  cmp edi, r12d
341e58  jge loc_341F4C
341e5e  xchg ax, ax
341e60  cmp dword ptr [r13+0], 0
341e65  jnz loc_341F49
341e6b  mov eax, [rbp+4AE8h]
341e71  mov ecx, 2
341e76  cdq
341e77  idiv dword ptr [rbp+8F8Ch]
341e7d  mov rax, rbx
341e80  movsxd rdx, edx
341e83  shl rdx, 8
341e87  add rdx, [rbp+8FA8h]
341e8e  xchg ax, ax
341e90  lea rdx, [rdx+80h]
341e97  movups xmm0, xmmword ptr [rax]
341e9a  lea rax, [rax+80h]
341ea1  movups xmmword ptr [rdx-80h], xmm0
341ea5  movups xmm1, xmmword ptr [rax-70h]
341ea9  movups xmmword ptr [rdx-70h], xmm1
341ead  movups xmm0, xmmword ptr [rax-60h]
341eb1  movups xmmword ptr [rdx-60h], xmm0
341eb5  movups xmm1, xmmword ptr [rax-50h]
341eb9  movups xmmword ptr [rdx-50h], xmm1
341ebd  movups xmm0, xmmword ptr [rax-40h]
341ec1  movups xmmword ptr [rdx-40h], xmm0
341ec5  movups xmm1, xmmword ptr [rax-30h]
341ec9  movups xmmword ptr [rdx-30h], xmm1
341ecd  movups xmm0, xmmword ptr [rax-20h]
341ed1  movups xmmword ptr [rdx-20h], xmm0
341ed5  movups xmm1, xmmword ptr [rax-10h]
341ed9  movups xmmword ptr [rdx-10h], xmm1
341edd  sub rcx, 1
341ee1  jnz short loc_341E90
341ee3  inc dword ptr [rbp+4AE8h]
341ee9  inc esi
341eeb  inc dword ptr [r15+4A50h]
341ef2  cmp esi, [r14+4A50h]
341ef9  jl short loc_341F02
341efb  mov edi, 1869Fh
341f00  jmp short loc_341F40
341f02  test byte ptr [r14+4A38h], 8
341f0a  jz short loc_341F1F
341f0c  movsxd rbx, esi
341f0f  lea rax, unk_2F7D1EC
341f16  shl rbx, 8
341f1a  add rbx, rax
341f1d  jmp short loc_341F3D
341f1f  mov eax, [r14+4A58h]
341f26  add eax, esi
341f28  cdq
341f29  idiv dword ptr [rbp+8F8Ch]
341f2f  movsxd rbx, edx
341f32  shl rbx, 8
341f36  add rbx, [rbp+8FA8h]
341f3d  movsx edi, word ptr [rbx]
341f40  cmp edi, r12d
341f43  jl loc_341E60
341f49  cmp edi, r12d
341f4c  jnz short loc_341FC9
341f4e  mov r8d, [rsp+338h+var_304]
341f53  mov r9, r15
341f56  mov [rsp+338h+var_310], rbx
341f5b  mov rdx, r13
341f5e  mov rcx, rbp
341f61  mov [rsp+338h+var_318], r12d
341f66  call sub_3407C0
341f6b  inc esi
341f6d  cmp esi, [r14+4A50h]
341f74  jl short loc_341F80
341f76  mov edi, 1869Fh
341f7b  jmp loc_3420DC
341f80  test byte ptr [r14+4A38h], 8
341f88  jz short loc_341FA3
341f8a  movsxd rbx, esi
341f8d  lea rax, unk_2F7D1EC
341f94  shl rbx, 8
341f98  add rbx, rax
341f9b  movsx edi, word ptr [rbx]
341f9e  jmp loc_3420DC
341fa3  mov eax, [r14+4A58h]
341faa  add eax, esi
341fac  cdq
341fad  idiv dword ptr [rbp+8F8Ch]
341fb3  movsxd rbx, edx
341fb6  shl rbx, 8
341fba  add rbx, [rbp+8FA8h]
341fc1  movsx edi, word ptr [rbx]
341fc4  jmp loc_3420DC
341fc9  movsxd r8, cs:dword_10B2D44
341fd0  lea rcx, [rsp+338h+var_2F8]
341fd5  xor edx, edx
341fd7  call sub_826080
341fdc  lea rdx, qword_9276C8
341fe3  lea rcx, [rsp+338h+var_298]
341feb  call sub_5B0CF0
341ff0  test byte ptr [r15+4A38h], 10h
341ff8  mov eax, 7FFh
341ffd  mov [rsp+338h+var_2F6], ax
342002  jz loc_3420A4
342008  call sub_2B0940
34200d  mov rcx, [rsp+338h+var_300]
342012  cmp ecx, eax
342014  jnb short loc_34207A
342016  call sub_2B0950
34201b  lea rcx, [rsp+338h+var_2F8]
342020  mov edx, 2
342025  lea rcx, [rcx+80h]
34202c  movups xmm0, xmmword ptr [rax]
34202f  lea rax, [rax+80h]
342036  movups xmmword ptr [rcx-80h], xmm0
34203a  movups xmm1, xmmword ptr [rax-70h]
34203e  movups xmmword ptr [rcx-70h], xmm1
342042  movups xmm0, xmmword ptr [rax-60h]
342046  movups xmmword ptr [rcx-60h], xmm0
34204a  movups xmm1, xmmword ptr [rax-50h]
34204e  movups xmmword ptr [rcx-50h], xmm1
342052  movups xmm0, xmmword ptr [rax-40h]
342056  movups xmmword ptr [rcx-40h], xmm0
34205a  movups xmm1, xmmword ptr [rax-30h]
34205e  movups xmmword ptr [rcx-30h], xmm1
342062  movups xmm0, xmmword ptr [rax-20h]
342066  movups xmmword ptr [rcx-20h], xmm0
34206a  movups xmm1, xmmword ptr [rax-10h]
34206e  movups xmmword ptr [rcx-10h], xmm1
342072  sub rdx, 1
342076  jnz short loc_342025
342078  jmp short loc_3420A0
34207a  xor edx, edx
34207c  lea rcx, [rsp+338h+var_2F8]
342081  mov r8d, 100h
342087  call sub_826080
34208c  lea rdx, qword_9276C8
342093  lea rcx, [rsp+338h+var_298]
34209b  call sub_5B0CF0
3420a0  inc dword ptr [rsp+338h+var_300]
3420a4  mov r8d, [rsp+338h+var_304]
3420a9  lea rax, [rsp+338h+var_2F8]
3420ae  mov [rsp+338h+var_310], rax
3420b3  mov r9, r15
3420b6  mov rdx, r13
3420b9  mov [rsp+338h+var_318], r12d
3420be  mov rcx, rbp
3420c1  mov [rsp+338h+var_2F8], r12w
3420c7  mov byte ptr [r15+4A28h], 1
3420cf  call sub_3407C0
3420d4  mov byte ptr [r15+4A28h], 0
3420dc  mov r12d, [rsp+338h+var_308]
3420e1  inc r12d
3420e4  cmp dword ptr [r13+0], 0
3420e9  mov [rsp+338h+var_308], r12d
3420ee  jz loc_341E10
3420f4  jmp short loc_3420FB
3420f6  mov r12d, [rsp+338h+var_308]
3420fb  lea r8, unk_2F7D1EC
342102  cmp edi, 1869Fh
342108  jz loc_3421F0
34210e  xchg ax, ax
342110  cmp dword ptr [r13+0], 0
342115  jnz loc_3421F0
34211b  mov eax, [rbp+4AE8h]
342121  cdq
342122  idiv dword ptr [rbp+8F8Ch]
342128  mov eax, 2
34212d  movsxd rdx, edx
342130  shl rdx, 8
342134  add rdx, [rbp+8FA8h]
34213b  nop dword ptr [rax+rax+00h]
342140  lea rdx, [rdx+80h]
342147  movups xmm0, xmmword ptr [rbx]
34214a  lea rbx, [rbx+80h]
342151  movups xmmword ptr [rdx-80h], xmm0
342155  movups xmm1, xmmword ptr [rbx-70h]
342159  movups xmmword ptr [rdx-70h], xmm1
34215d  movups xmm0, xmmword ptr [rbx-60h]
342161  movups xmmword ptr [rdx-60h], xmm0
342165  movups xmm1, xmmword ptr [rbx-50h]
342169  movups xmmword ptr [rdx-50h], xmm1
34216d  movups xmm0, xmmword ptr [rbx-40h]
342171  movups xmmword ptr [rdx-40h], xmm0
342175  movups xmm1, xmmword ptr [rbx-30h]
342179  movups xmmword ptr [rdx-30h], xmm1
34217d  movups xmm0, xmmword ptr [rbx-20h]
342181  movups xmmword ptr [rdx-20h], xmm0
342185  movups xmm1, xmmword ptr [rbx-10h]
342189  movups xmmword ptr [rdx-10h], xmm1
34218d  sub rax, 1
342191  jnz short loc_342140
342193  inc dword ptr [rbp+4AE8h]
342199  inc esi
34219b  inc dword ptr [r15+4A50h]
3421a2  cmp esi, [r14+4A50h]
3421a9  jge short loc_3421F0
3421ab  test byte ptr [r14+4A38h], 8
3421b3  jz short loc_3421C1
3421b5  movsxd rbx, esi
3421b8  shl rbx, 8
3421bc  add rbx, r8
3421bf  jmp short loc_3421DF
3421c1  mov eax, [r14+4A58h]
3421c8  add eax, esi
3421ca  cdq
3421cb  idiv dword ptr [rbp+8F8Ch]
3421d1  movsxd rbx, edx
3421d4  shl rbx, 8
3421d8  add rbx, [rbp+8FA8h]
3421df  movsx r9d, word ptr [rbx]
3421e3  cmp r9d, 1869Fh
3421ea  jnz loc_342110
3421f0  mov r9, [r15+4A30h]
3421f7  cmp dword ptr [r9], 0
3421fb  jle short loc_34220B
3421fd  mov r8, r15
342200  mov rdx, r14
342203  mov rcx, rbp
342206  call sub_343030
34220b  mov eax, r12d
34220e  mov rcx, [rsp+338h+var_58]
342216  xor rcx, rsp; StackCookie
342219  call __security_check_cookie
34221e  add rsp, 2F8h
342225  pop r15
342227  pop r14
342229  pop r13
34222b  pop r12
34222d  pop rdi
34222e  pop rsi
34222f  pop rbp
342230  pop rbx
342231  retn