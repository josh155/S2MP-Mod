4ee380  mov [rsp+arg_18], rbx
4ee385  push rsi
4ee386  push r12
4ee388  push r13
4ee38a  push r14
4ee38c  push r15
4ee38e  sub rsp, 30h
4ee392  mov r14, [rsp+58h+arg_20]
4ee39a  mov r12d, edx
4ee39d  mov r15, [rsp+58h+arg_28]
4ee3a5  mov rbx, rcx
4ee3a8  mov esi, r8d
4ee3ab  mov rdx, r14
4ee3ae  mov r8d, r8d
4ee3b1  mov rcx, r15
4ee3b4  shl r8, 3
4ee3b8  mov r13d, r9d
4ee3bb  call sub_59F870
4ee3c0  mov rcx, rbx
4ee3c3  call MSG_ReadBit; CORRECTED from MSG_ReadShort (a false positive of the same-game call-graph
4ee3c8  test eax, eax
4ee3ca  jz loc_4EE4C1
4ee3d0  mov [rsp+58h+arg_0], rbp
4ee3d5  mov ebp, [rsp+58h+arg_30]
4ee3dc  mov [rsp+58h+arg_8], rdi
4ee3e1  mov edx, r13d
4ee3e4  mov rcx, rbx
4ee3e7  call MSG_ReadBits; MSG_ReadBits
4ee3ec  mov edi, eax
4ee3ee  mov rcx, rbx
4ee3f1  cmp eax, esi
4ee3f3  jnb loc_4EE4B2
4ee3f9  lea rdx, [r15+rdi*8]
4ee3fd  mov [rsp+58h+var_30], ebp
4ee401  mov [rsp+58h+var_38], rdx
4ee406  lea r9, [r14+rdi*8]
4ee40a  mov r8d, edi
4ee40d  mov edx, r12d
4ee410  call sub_4EE120
4ee415  mov r8d, [rbx+28h]
4ee419  and r8d, 7
4ee41d  jnz short loc_4EE444
4ee41f  mov eax, [rbx+20h]
4ee422  add eax, [rbx+1Ch]
4ee425  mov ecx, [rbx+24h]
4ee428  cmp ecx, eax
4ee42a  jl short loc_4EE434
4ee42c  mov dword ptr [rbx], 1
4ee432  jmp short loc_4EE482
4ee434  lea eax, ds:0[rcx*8]
4ee43b  mov [rbx+28h], eax
4ee43e  lea eax, [rcx+1]
4ee441  mov [rbx+24h], eax
4ee444  mov r9d, [rbx+28h]
4ee448  mov eax, r9d
4ee44b  sar eax, 3
4ee44e  mov ecx, eax
4ee450  sub ecx, [rbx+1Ch]
4ee453  js short loc_4EE462
4ee455  mov rax, [rbx+10h]
4ee459  movsxd rcx, ecx
4ee45c  movzx edx, byte ptr [rcx+rax]
4ee460  jmp short loc_4EE46D
4ee462  movsxd rdx, eax
4ee465  mov rax, [rbx+8]
4ee469  movzx edx, byte ptr [rdx+rax]
4ee46d  lea eax, [r9+1]
4ee471  movzx ecx, r8b
4ee475  mov [rbx+28h], eax
4ee478  movzx eax, dl
4ee47b  shr eax, cl
4ee47d  and eax, 1
4ee480  jz short loc_4EE49D
4ee482  inc edi
4ee484  cmp edi, esi
4ee486  jnb short loc_4EE4AF
4ee488  lea rcx, [r15+rdi*8]
4ee48c  mov [rsp+58h+var_30], ebp
4ee490  mov [rsp+58h+var_38], rcx
4ee495  mov rcx, rbx
4ee498  jmp loc_4EE406
4ee49d  mov rcx, rbx
4ee4a0  call MSG_ReadBit; CORRECTED from MSG_ReadShort (a false positive of the same-game call-graph
4ee4a5  test eax, eax
4ee4a7  jnz loc_4EE3E1
4ee4ad  jmp short loc_4EE4B7
4ee4af  mov rcx, rbx
4ee4b2  call MSG_Discard; Basis: PS4 twin MSG_Discard; called on overflow paths
4ee4b7  mov rbp, [rsp+58h+arg_0]
4ee4bc  mov rdi, [rsp+58h+arg_8]
4ee4c1  mov rbx, [rsp+58h+arg_18]
4ee4c6  add rsp, 30h
4ee4ca  pop r15
4ee4cc  pop r14
4ee4ce  pop r13
4ee4d0  pop r12
4ee4d2  pop rsi
4ee4d3  retn