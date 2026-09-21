4ee63e  mov [rsp+arg_4948], rdi
4ee646  mov eax, 1F0h
4ee64b  cmp r12d, 0FFFFFFFFh
4ee64f  jle loc_4EE761
4ee655  nop word ptr [rax+rax+00000000h]
4ee660  mov r8d, r12d
4ee663  lea edi, [r13+1]
4ee667  sub r8d, r13d
4ee66a  mov edx, 4
4ee66f  mov rcx, r14
4ee672  call MSG_ReadNumFieldsSkipped; Basis: PS4 twin 0x726F60
4ee677  add r13d, eax
4ee67a  cmp edi, r13d
4ee67d  jge short loc_4EE6FD
4ee67f  mov r14, [rsp+arg_48]
4ee684  movzx r12d, [rsp+arg_39]
4ee68a  movsxd rax, edi
4ee68d  lea rsi, [r15+rax*8]
4ee691  movzx eax, [rsp+arg_38]
4ee696  lea rbx, [rsi+6]
4ee69a  nop word ptr [rax+rax+00h]
4ee6a0  test al, al
4ee6a2  jnz short loc_4EE6C4
4ee6a4  mov ecx, 1F0h
4ee6a9  test [rbx], cx
4ee6ac  jz short loc_4EE6C4
4ee6ae  movzx r8d, word ptr [rbx-6]
4ee6b3  mov rdx, rsi
4ee6b6  add r8, rbp
4ee6b9  movzx ecx, r12b
4ee6bd  call sub_4F0B90
4ee6c2  jmp short loc_4EE6DA
4ee6c4  test byte ptr [rbx], 2
4ee6c7  jnz short loc_4EE6DF
4ee6c9  mov r9d, edi
4ee6cc  mov r8, rbp
4ee6cf  mov rdx, r14
4ee6d2  mov rcx, r15
4ee6d5  call MSG_CopyFieldOver; Basis: copies one netfield from baseline to target
4ee6da  movzx eax, [rsp+arg_38]
4ee6df  inc edi
4ee6e1  add rsi, 8
4ee6e5  add rbx, 8
4ee6e9  cmp edi, r13d
4ee6ec  jl short loc_4EE6A0
4ee6ee  mov r14, [rsp+arg_58]
4ee6f3  mov r12d, [rsp+arg_54]
4ee6f8  mov rsi, [rsp+arg_48]
4ee6fd  cmp [rsp+arg_40], 0
4ee702  movsxd rax, r13d
4ee705  lea rcx, [r15+rax*8]
4ee709  jnz short loc_4EE715
4ee70b  test byte ptr [rcx+6], 4
4ee70f  jz short loc_4EE715
4ee711  mov al, 1
4ee713  jmp short loc_4EE717
4ee715  xor al, al
4ee717  cmp [rsp+arg_4970], 0
4ee71f  jz short loc_4EE729
4ee721  test al, al
4ee723  jz short loc_4EE729
4ee725  mov al, 1
4ee727  jmp short loc_4EE72B
4ee729  xor eax, eax
4ee72b  mov edx, [rsp+arg_44]
4ee72f  mov r9, rbp
4ee732  mov [rsp+arg_28], al
4ee736  mov r8, rsi
4ee739  mov dword ptr [rsp+arg_20], 0
4ee741  mov [rsp+arg_18], rcx
4ee746  mov rcx, r14
4ee749  call MSG_ReadDeltaField; Basis: PS4 twin 0x7273A0
4ee74e  cmp r13d, r12d
4ee751  jl loc_4EE660
4ee757  mov [rsp+arg_50], r13d
4ee75c  mov eax, 1F0h
4ee761  movsxd rsi, [rsp+arg_3C]
4ee766  lea edi, [r13+1]
4ee76a  movzx r12d, [rsp+arg_38]
4ee770  movsxd rbx, edi
4ee773  cmp rbx, rsi
4ee776  jge short loc_4EE7D4
4ee778  mov r14, [rsp+arg_48]
4ee77d  movzx r13d, [rsp+arg_39]
4ee783  test r12b, r12b
4ee786  jnz short loc_4EE7AA
4ee788  test [r15+rbx*8+6], ax
4ee78e  jz short loc_4EE7AA
4ee790  movzx r8d, word ptr [r15+rbx*8]
4ee795  movzx ecx, r13b
4ee799  movsxd rax, edi
4ee79c  add r8, rbp
4ee79f  lea rdx, [r15+rax*8]
4ee7a3  call sub_4F0B90
4ee7a8  jmp short loc_4EE7BB
4ee7aa  mov r9d, edi
4ee7ad  mov r8, rbp
4ee7b0  mov rdx, r14
4ee7b3  mov rcx, r15
4ee7b6  call MSG_CopyFieldOver; Basis: copies one netfield from baseline to target
4ee7bb  inc edi
4ee7bd  inc rbx
4ee7c0  mov eax, 1F0h
4ee7c5  cmp rbx, rsi
4ee7c8  jl short loc_4EE783
4ee7ca  mov r14, [rsp+arg_58]
4ee7cf  mov r13d, [rsp+arg_50]
4ee7d4  movsxd rbx, r13d
4ee7d7  test r13d, r13d
4ee7da  jle short loc_4EE81C
4ee7dc  mov r12, [rsp+arg_48]
4ee7e1  test byte ptr [r15+6], 2
4ee7e6  jz short loc_4EE80C
4ee7e8  mov edx, [rsp+arg_44]
4ee7ec  mov r9, rbp
4ee7ef  mov [rsp+arg_28], 0
4ee7f4  mov r8, r12
4ee7f7  mov dword ptr [rsp+arg_20], 0
4ee7ff  mov rcx, r14
4ee802  mov [rsp+arg_18], r15
4ee807  call MSG_ReadDeltaField; Basis: PS4 twin 0x7273A0
4ee80c  add r15, 8
4ee810  sub rbx, 1
4ee814  jnz short loc_4EE7E1
4ee816  movzx r12d, [rsp+arg_38]
4ee81c  cmp [rsp+arg_40], 0
4ee821  jz short loc_4EE896
4ee823  mov edx, [rbp+4Ch]
4ee826  mov r8, rbp
4ee829  mov rcx, cs:qword_2EC84F0
4ee830  call CL_GetPredictedPlayerInformationForServerTime
4ee835  mov r15, [rsp+arg_48]
4ee83a  test eax, eax
4ee83c  jnz short loc_4EE89B
4ee83e  mov eax, [r15+78h]
4ee842  mov [rbp+78h], eax
4ee845  mov eax, [r15+7Ch]
4ee849  mov [rbp+7Ch], eax
4ee84c  mov eax, [r15+80h]
4ee853  mov [rbp+80h], eax
4ee859  mov eax, [r15+84h]
4ee860  mov [rbp+84h], eax
4ee866  mov eax, [r15+88h]
4ee86d  mov [rbp+88h], eax
4ee873  mov eax, [r15+8Ch]
4ee87a  mov [rbp+8Ch], eax
4ee880  mov eax, [r15+74h]
4ee884  mov [rbp+74h], eax
4ee887  mov eax, [r15+0C8h]
4ee88e  mov [rbp+0C8h], eax
4ee894  jmp short loc_4EE89B
4ee896  mov r15, [rsp+arg_48]
4ee89b  mov r8d, [r14+28h]
4ee89f  and r8d, 7
4ee8a3  jnz short loc_4EE8D0
4ee8a5  mov eax, [r14+20h]
4ee8a9  add eax, [r14+1Ch]
4ee8ad  mov ecx, [r14+24h]
4ee8b1  cmp ecx, eax
4ee8b3  jl short loc_4EE8BE
4ee8b5  mov dword ptr [r14], 1
4ee8bc  jmp short loc_4EE910
4ee8be  lea eax, ds:0[rcx*8]
4ee8c5  mov [r14+28h], eax
4ee8c9  lea eax, [rcx+1]
4ee8cc  mov [r14+24h], eax
4ee8d0  mov r9d, [r14+28h]
4ee8d4  mov eax, r9d
4ee8d7  sar eax, 3
4ee8da  mov ecx, eax
4ee8dc  sub ecx, [r14+1Ch]
4ee8e0  js short loc_4EE8EF
4ee8e2  mov rax, [r14+10h]
4ee8e6  movsxd rcx, ecx
4ee8e9  movzx edx, byte ptr [rcx+rax]
4ee8ed  jmp short loc_4EE8FA
4ee8ef  movsxd rdx, eax
4ee8f2  mov rax, [r14+8]
4ee8f6  movzx edx, byte ptr [rdx+rax]
4ee8fa  lea eax, [r9+1]
4ee8fe  movzx ecx, r8b
4ee902  mov [r14+28h], eax
4ee906  movzx eax, dl
4ee909  shr eax, cl
4ee90b  and eax, 1
4ee90e  jz short loc_4EE970
4ee910  mov edx, 4
4ee915  mov rcx, r14
4ee918  call MSG_ReadBits; MSG_ReadBits
4ee91d  mov ebx, eax
4ee91f  test al, 1
4ee921  jz short loc_4EE931
4ee923  mov rcx, r14
4ee926  call MSG_ReadValue32_ByteCursor; CORRECTED from Com_Printf (call-graph propagation false positive; that
4ee92b  mov [rbp+15Ch], eax
4ee931  test bl, 2
4ee934  jz short loc_4EE944
4ee936  mov rcx, r14
4ee939  call MSG_ReadValue32_ByteCursor; CORRECTED from Com_Printf (call-graph propagation false positive; that
4ee93e  mov [rbp+160h], eax
4ee944  test bl, 4
4ee947  jz short loc_4EE957
4ee949  mov rcx, r14
4ee94c  call MSG_ReadValue32_ByteCursor; CORRECTED from Com_Printf (call-graph propagation false positive; that
4ee951  mov [rbp+164h], eax
4ee957  test bl, 8
4ee95a  jz short loc_4EE970
4ee95c  mov rcx, r14
4ee95f  call MSG_ReadByte; Basis: Arxan-obfuscated body; identified from use (deltaNum, snapFlags)
4ee964  mov [rbp+168h], eax
4ee96a  nop word ptr [rax+rax+00h]
4ee970  mov r8d, [r14+28h]
4ee974  and r8d, 7
4ee978  jnz short loc_4EE9A5
4ee97a  mov eax, [r14+20h]
4ee97e  add eax, [r14+1Ch]
4ee982  mov ecx, [r14+24h]
4ee986  cmp ecx, eax
4ee988  jl short loc_4EE993
4ee98a  mov dword ptr [r14], 1
4ee991  jmp short loc_4EE9E8
4ee993  lea eax, ds:0[rcx*8]
4ee99a  mov [r14+28h], eax
4ee99e  lea eax, [rcx+1]
4ee9a1  mov [r14+24h], eax
4ee9a5  mov r9d, [r14+28h]
4ee9a9  mov eax, r9d
4ee9ac  sar eax, 3
4ee9af  mov ecx, eax
4ee9b1  sub ecx, [r14+1Ch]
4ee9b5  js short loc_4EE9C4
4ee9b7  mov rax, [r14+10h]
4ee9bb  movsxd rcx, ecx
4ee9be  movzx edx, byte ptr [rcx+rax]
4ee9c2  jmp short loc_4EE9CF
4ee9c4  movsxd rdx, eax
4ee9c7  mov rax, [r14+8]
4ee9cb  movzx edx, byte ptr [rdx+rax]
4ee9cf  inc r9d
4ee9d2  movzx eax, dl
4ee9d5  movzx ecx, r8b
4ee9d9  mov [r14+28h], r9d
4ee9dd  shr eax, cl
4ee9df  and eax, 1
4ee9e2  jz loc_4EEAD7
4ee9e8  mov edx, 4
4ee9ed  mov rcx, r14
4ee9f0  call MSG_ReadBits; MSG_ReadBits
4ee9f5  movsxd rcx, eax
4ee9f8  mov edx, 1
4ee9fd  lea rdi, [rcx+rcx*2]
4eea01  mov rcx, r14
4eea04  call MSG_ReadBits; MSG_ReadBits
4eea09  mov edx, 1Bh
4eea0e  mov rcx, r14
4eea11  mov ebx, eax
4eea13  call MSG_ReadBits; MSG_ReadBits
4eea18  test ebx, ebx
4eea1a  mov [rbp+rdi*8+470h], eax
4eea21  lea rdi, [rdi+8Fh]
4eea28  setnz al
4eea2b  lea rbx, ds:0[rdi*8]
4eea33  mov [rbp+rdi*8-4], al
4eea37  add rbx, rbp
4eea3a  mov edi, 2
4eea3f  nop
4eea40  mov r8d, [r14+28h]
4eea44  and r8d, 7
4eea48  jnz short loc_4EEA75
4eea4a  mov eax, [r14+20h]
4eea4e  add eax, [r14+1Ch]
4eea52  mov ecx, [r14+24h]
4eea56  cmp ecx, eax
4eea58  jl short loc_4EEA63
4eea5a  mov dword ptr [r14], 1
4eea61  jmp short loc_4EEAB5
4eea63  lea eax, ds:0[rcx*8]
4eea6a  mov [r14+28h], eax
4eea6e  lea eax, [rcx+1]
4eea71  mov [r14+24h], eax
4eea75  mov r9d, [r14+28h]
4eea79  mov eax, r9d
4eea7c  sar eax, 3
4eea7f  mov ecx, eax
4eea81  sub ecx, [r14+1Ch]
4eea85  js short loc_4EEA94
4eea87  mov rax, [r14+10h]
4eea8b  movsxd rcx, ecx
4eea8e  movzx edx, byte ptr [rcx+rax]
4eea92  jmp short loc_4EEA9F
4eea94  movsxd rdx, eax
4eea97  mov rax, [r14+8]
4eea9b  movzx edx, byte ptr [rdx+rax]
4eea9f  lea eax, [r9+1]
4eeaa3  movzx ecx, r8b
4eeaa7  mov [r14+28h], eax
4eeaab  movzx eax, dl
4eeaae  shr eax, cl
4eeab0  and eax, 1
4eeab3  jz short loc_4EEAC4
4eeab5  mov edx, 8
4eeaba  mov rcx, r14
4eeabd  call MSG_ReadBits; MSG_ReadBits
4eeac2  mov [rbx], eax
4eeac4  add rbx, 4
4eeac8  sub rdi, 1
4eeacc  jnz loc_4EEA40
4eead2  jmp loc_4EE970
4eead7  and r9d, 7
4eeadb  jnz short loc_4EEB08
4eeadd  mov eax, [r14+20h]
4eeae1  add eax, [r14+1Ch]
4eeae5  mov ecx, [r14+24h]
4eeae9  cmp ecx, eax
4eeaeb  jl short loc_4EEAF6
4eeaed  mov dword ptr [r14], 1
4eeaf4  jmp short loc_4EEB4C
4eeaf6  lea eax, ds:0[rcx*8]
4eeafd  mov [r14+28h], eax
4eeb01  lea eax, [rcx+1]
4eeb04  mov [r14+24h], eax
4eeb08  mov r8d, [r14+28h]
4eeb0c  mov eax, r8d
4eeb0f  sar eax, 3
4eeb12  mov ecx, eax
4eeb14  sub ecx, [r14+1Ch]
4eeb18  js short loc_4EEB27
4eeb1a  mov rax, [r14+10h]
4eeb1e  movsxd rcx, ecx
4eeb21  movzx edx, byte ptr [rcx+rax]
4eeb25  jmp short loc_4EEB32
4eeb27  movsxd rdx, eax
4eeb2a  mov rax, [r14+8]
4eeb2e  movzx edx, byte ptr [rdx+rax]
4eeb32  lea eax, [r8+1]
4eeb36  movzx ecx, r9b
4eeb3a  mov [r14+28h], eax
4eeb3e  movzx eax, dl
4eeb41  shr eax, cl
4eeb43  and eax, 1
4eeb46  jz loc_4EF29A
4eeb4c  movzx r15d, [rsp+arg_39]
4eeb52  xor r13d, r13d
4eeb55  mov edi, r13d
4eeb58  mov esi, r13d
4eeb5b  nop dword ptr [rax+rax+00h]
4eeb60  mov r10d, [r14+28h]
4eeb64  and r10d, 7
4eeb68  jnz short loc_4EEB98
4eeb6a  mov ecx, [r14+20h]
4eeb6e  mov r8d, [r14+1Ch]
4eeb72  add ecx, r8d
4eeb75  mov edx, [r14+24h]
4eeb79  cmp edx, ecx
4eeb7b  jl short loc_4EEB86
4eeb7d  mov dword ptr [r14], 1
4eeb84  jmp short loc_4EEBDE
4eeb86  lea eax, ds:0[rdx*8]
4eeb8d  mov [r14+28h], eax
4eeb91  lea eax, [rdx+1]
4eeb94  mov [r14+24h], eax
4eeb98  mov r9d, [r14+28h]
4eeb9c  mov eax, r9d
4eeb9f  mov r8d, [r14+1Ch]
4eeba3  sar eax, 3
4eeba6  mov ecx, eax
4eeba8  sub ecx, r8d
4eebab  js short loc_4EEBBA
4eebad  mov rax, [r14+10h]
4eebb1  movsxd rcx, ecx
4eebb4  movzx edx, byte ptr [rcx+rax]
4eebb8  jmp short loc_4EEBC5
4eebba  movsxd rdx, eax
4eebbd  mov rax, [r14+8]
4eebc1  movzx edx, byte ptr [rdx+rax]
4eebc5  inc r9d
4eebc8  movzx eax, dl
4eebcb  movzx ecx, r10b
4eebcf  mov [r14+28h], r9d
4eebd3  shr eax, cl
4eebd5  and eax, 1
4eebd8  jz loc_4EF20C
4eebde  test r12b, r12b
4eebe1  jnz short loc_4EEC03
4eebe3  mov r9d, [r14+28h]
4eebe7  and r9d, 7
4eebeb  jnz short loc_4EEC42
4eebed  mov ecx, [r14+20h]
4eebf1  mov edx, [r14+24h]
4eebf5  add ecx, r8d
4eebf8  cmp edx, ecx
4eebfa  jl short loc_4EEC30
4eebfc  mov dword ptr [r14], 1
4eec03  mov r9d, [r14+28h]
4eec07  and r9d, 7
4eec0b  jnz loc_4EECB7
4eec11  mov ecx, [r14+20h]
4eec15  mov edx, [r14+24h]
4eec19  add ecx, r8d
4eec1c  cmp edx, ecx
4eec1e  jl loc_4EECA5
4eec24  mov dword ptr [r14], 1
4eec2b  jmp loc_4EECF6
4eec30  lea eax, ds:0[rdx*8]
4eec37  mov [r14+28h], eax
4eec3b  lea eax, [rdx+1]
4eec3e  mov [r14+24h], eax
4eec42  mov r10d, [r14+28h]
4eec46  mov eax, r10d
4eec49  sar eax, 3
4eec4c  mov ecx, eax
4eec4e  sub ecx, r8d
4eec51  js short loc_4EEC60
4eec53  mov rax, [r14+10h]
4eec57  movsxd rcx, ecx
4eec5a  movzx edx, byte ptr [rcx+rax]
4eec5e  jmp short loc_4EEC6B
4eec60  movsxd rdx, eax
4eec63  mov rax, [r14+8]
4eec67  movzx edx, byte ptr [rdx+rax]
4eec6b  lea eax, [r10+1]
4eec6f  movzx ecx, r9b
4eec73  mov [r14+28h], eax
4eec77  movzx eax, dl
4eec7a  shr eax, cl
4eec7c  and eax, 1
4eec7f  jnz short loc_4EEC03
4eec81  xor ecx, ecx
4eec83  movsxd rax, edi
4eec86  mov [rbp+rax*4+25Ch], ecx
4eec8d  add rax, rax
4eec90  mov [rbp+rax*8+298h], rcx
4eec98  mov [rbp+rax*8+2A0h], rcx
4eeca0  jmp loc_4EF285
4eeca5  lea eax, ds:0[rdx*8]
4eecac  mov [r14+28h], eax
4eecb0  lea eax, [rdx+1]
4eecb3  mov [r14+24h], eax
4eecb7  mov r10d, [r14+28h]
4eecbb  mov eax, r10d
4eecbe  sar eax, 3
4eecc1  mov ecx, eax
4eecc3  sub ecx, r8d
4eecc6  js short loc_4EECD5
4eecc8  mov rax, [r14+10h]
4eeccc  movsxd rcx, ecx
4eeccf  movzx edx, byte ptr [rcx+rax]
4eecd3  jmp short loc_4EECE0
4eecd5  movsxd rdx, eax
4eecd8  mov rax, [r14+8]
4eecdc  movzx edx, byte ptr [rdx+rax]
4eece0  lea eax, [r10+1]
4eece4  movzx ecx, r9b
4eece8  mov [r14+28h], eax
4eecec  movzx eax, dl
4eecef  shr eax, cl
4eecf1  and eax, 1
4eecf4  jz short loc_4EED0A
4eecf6  mov edx, 1Bh
4eecfb  mov rcx, r14
4eecfe  call MSG_ReadBits; MSG_ReadBits
4eed03  mov [rbp+rsi*4+25Ch], eax
4eed0a  mov r8d, [r14+28h]
4eed0e  and r8d, 7
4eed12  jnz short loc_4EED42
4eed14  mov eax, [r14+20h]
4eed18  add eax, [r14+1Ch]
4eed1c  mov ecx, [r14+24h]
4eed20  cmp ecx, eax
4eed22  jl short loc_4EED30
4eed24  mov dword ptr [r14], 1
4eed2b  or eax, 0FFFFFFFFh
4eed2e  jmp short loc_4EED80
4eed30  lea eax, ds:0[rcx*8]
4eed37  mov [r14+28h], eax
4eed3b  lea eax, [rcx+1]
4eed3e  mov [r14+24h], eax
4eed42  mov r9d, [r14+28h]
4eed46  mov eax, r9d
4eed49  sar eax, 3
4eed4c  mov ecx, eax
4eed4e  sub ecx, [r14+1Ch]
4eed52  js short loc_4EED61
4eed54  mov rax, [r14+10h]
4eed58  movsxd rcx, ecx
4eed5b  movzx edx, byte ptr [rcx+rax]
4eed5f  jmp short loc_4EED6C
4eed61  movsxd rdx, eax
4eed64  mov rax, [r14+8]
4eed68  movzx edx, byte ptr [rdx+rax]
4eed6c  lea eax, [r9+1]
4eed70  movzx ecx, r8b
4eed74  mov [r14+28h], eax
4eed78  movzx eax, dl
4eed7b  shr eax, cl
4eed7d  and eax, 1
4eed80  mov rbx, rsi
4eed83  add rbx, rbx
4eed86  test eax, eax
4eed88  setnle al
4eed8b  mov [rbp+rbx*8+298h], al
4eed92  mov r8d, [r14+28h]
4eed96  and r8d, 7
4eed9a  jnz short loc_4EEDCA
4eed9c  mov eax, [r14+20h]
4eeda0  add eax, [r14+1Ch]
4eeda4  mov ecx, [r14+24h]
4eeda8  cmp ecx, eax
4eedaa  jl short loc_4EEDB8
4eedac  mov dword ptr [r14], 1
4eedb3  or eax, 0FFFFFFFFh
4eedb6  jmp short loc_4EEE08
4eedb8  lea eax, ds:0[rcx*8]
4eedbf  mov [r14+28h], eax
4eedc3  lea eax, [rcx+1]
4eedc6  mov [r14+24h], eax
4eedca  mov r9d, [r14+28h]
4eedce  mov eax, r9d
4eedd1  sar eax, 3
4eedd4  mov ecx, eax
4eedd6  sub ecx, [r14+1Ch]
4eedda  js short loc_4EEDE9
4eeddc  mov rax, [r14+10h]
4eede0  movsxd rcx, ecx
4eede3  movzx edx, byte ptr [rcx+rax]
4eede7  jmp short loc_4EEDF4
4eede9  movsxd rdx, eax
4eedec  mov rax, [r14+8]
4eedf0  movzx edx, byte ptr [rdx+rax]
4eedf4  lea eax, [r9+1]
4eedf8  movzx ecx, r8b
4eedfc  mov [r14+28h], eax
4eee00  movzx eax, dl
4eee03  shr eax, cl
4eee05  and eax, 1
4eee08  test eax, eax
4eee0a  setnle al
4eee0d  mov [rbp+rbx*8+299h], al
4eee14  mov r8d, [r14+28h]
4eee18  and r8d, 7
4eee1c  jnz short loc_4EEE4C
4eee1e  mov eax, [r14+20h]
4eee22  add eax, [r14+1Ch]
4eee26  mov ecx, [r14+24h]
4eee2a  cmp ecx, eax
4eee2c  jl short loc_4EEE3A
4eee2e  mov dword ptr [r14], 1
4eee35  or eax, 0FFFFFFFFh
4eee38  jmp short loc_4EEE8A
4eee3a  lea eax, ds:0[rcx*8]
4eee41  mov [r14+28h], eax
4eee45  lea eax, [rcx+1]
4eee48  mov [r14+24h], eax
4eee4c  mov r9d, [r14+28h]
4eee50  mov eax, r9d
4eee53  sar eax, 3
4eee56  mov ecx, eax
4eee58  sub ecx, [r14+1Ch]
4eee5c  js short loc_4EEE6B
4eee5e  mov rax, [r14+10h]
4eee62  movsxd rcx, ecx
4eee65  movzx edx, byte ptr [rcx+rax]
4eee69  jmp short loc_4EEE76
4eee6b  movsxd rdx, eax
4eee6e  mov rax, [r14+8]
4eee72  movzx edx, byte ptr [rdx+rax]
4eee76  lea eax, [r9+1]
4eee7a  movzx ecx, r8b
4eee7e  mov [r14+28h], eax
4eee82  movzx eax, dl
4eee85  shr eax, cl
4eee87  and eax, 1
4eee8a  test eax, eax
4eee8c  setnle al
4eee8f  mov [rbp+rbx*8+29Ah], al
4eee96  test r12b, r12b
4eee99  jz loc_4EEFB1
4eee9f  mov r8d, [r14+28h]
4eeea3  and r8d, 7
4eeea7  jnz short loc_4EEED7
4eeea9  mov eax, [r14+20h]
4eeead  add eax, [r14+1Ch]
4eeeb1  mov ecx, [r14+24h]
4eeeb5  cmp ecx, eax
4eeeb7  jl short loc_4EEEC5
4eeeb9  mov dword ptr [r14], 1
4eeec0  or eax, 0FFFFFFFFh
4eeec3  jmp short loc_4EEF15
4eeec5  lea eax, ds:0[rcx*8]
4eeecc  mov [r14+28h], eax
4eeed0  lea eax, [rcx+1]
4eeed3  mov [r14+24h], eax
4eeed7  mov r9d, [r14+28h]
4eeedb  mov eax, r9d
4eeede  sar eax, 3
4eeee1  mov ecx, eax
4eeee3  sub ecx, [r14+1Ch]
4eeee7  js short loc_4EEEF6
4eeee9  mov rax, [r14+10h]
4eeeed  movsxd rcx, ecx
4eeef0  movzx edx, byte ptr [rcx+rax]
4eeef4  jmp short loc_4EEF01
4eeef6  movsxd rdx, eax
4eeef9  mov rax, [r14+8]
4eeefd  movzx edx, byte ptr [rdx+rax]
4eef01  lea eax, [r9+1]
4eef05  movzx ecx, r8b
4eef09  mov [r14+28h], eax
4eef0d  movzx eax, dl
4eef10  shr eax, cl
4eef12  and eax, 1
4eef15  test eax, eax
4eef17  setnle al
4eef1a  mov [rbp+rbx*8+29Bh], al
4eef21  mov r8d, [r14+28h]
4eef25  and r8d, 7
4eef29  jnz short loc_4EEF65
4eef2b  mov eax, [r14+20h]
4eef2f  add eax, [r14+1Ch]
4eef33  mov ecx, [r14+24h]
4eef37  cmp ecx, eax
4eef39  jl short loc_4EEF53
4eef3b  or eax, 0FFFFFFFFh
4eef3e  mov dword ptr [r14], 1
4eef45  test eax, eax
4eef47  setnle al
4eef4a  mov [rbp+rbx*8+29Ch], al
4eef51  jmp short loc_4EEFBA
4eef53  lea eax, ds:0[rcx*8]
4eef5a  mov [r14+28h], eax
4eef5e  lea eax, [rcx+1]
4eef61  mov [r14+24h], eax
4eef65  mov r9d, [r14+28h]
4eef69  mov eax, r9d
4eef6c  sar eax, 3
4eef6f  mov ecx, eax
4eef71  sub ecx, [r14+1Ch]
4eef75  js short loc_4EEF84
4eef77  mov rax, [r14+10h]
4eef7b  movsxd rcx, ecx
4eef7e  movzx edx, byte ptr [rcx+rax]
4eef82  jmp short loc_4EEF8F
4eef84  movsxd rdx, eax
4eef87  mov rax, [r14+8]
4eef8b  movzx edx, byte ptr [rdx+rax]
4eef8f  lea eax, [r9+1]
4eef93  movzx ecx, r8b
4eef97  mov [r14+28h], eax
4eef9b  movzx eax, dl
4eef9e  shr eax, cl
4eefa0  and eax, 1
4eefa3  test eax, eax
4eefa5  setnle al
4eefa8  mov [rbp+rbx*8+29Ch], al
4eefaf  jmp short loc_4EEFBA
4eefb1  mov [rbp+rbx*8+29Bh], r13w
4eefba  mov r8d, [r14+28h]
4eefbe  and r8d, 7
4eefc2  jnz short loc_4EEFF2
4eefc4  mov eax, [r14+20h]
4eefc8  add eax, [r14+1Ch]
4eefcc  mov ecx, [r14+24h]
4eefd0  cmp ecx, eax
4eefd2  jl short loc_4EEFE0
4eefd4  mov dword ptr [r14], 1
4eefdb  or eax, 0FFFFFFFFh
4eefde  jmp short loc_4EF030
4eefe0  lea eax, ds:0[rcx*8]
4eefe7  mov [r14+28h], eax
4eefeb  lea eax, [rcx+1]
4eefee  mov [r14+24h], eax
4eeff2  mov r9d, [r14+28h]
4eeff6  mov eax, r9d
4eeff9  sar eax, 3
4eeffc  mov ecx, eax
4eeffe  sub ecx, [r14+1Ch]
4ef002  js short loc_4EF011
4ef004  mov rax, [r14+10h]
4ef008  movsxd rcx, ecx
4ef00b  movzx edx, byte ptr [rcx+rax]
4ef00f  jmp short loc_4EF01C
4ef011  movsxd rdx, eax
4ef014  mov rax, [r14+8]
4ef018  movzx edx, byte ptr [rdx+rax]
4ef01c  lea eax, [r9+1]
4ef020  movzx ecx, r8b
4ef024  mov [r14+28h], eax
4ef028  movzx eax, dl
4ef02b  shr eax, cl
4ef02d  and eax, 1
4ef030  test eax, eax
4ef032  mov edx, 2
4ef037  mov rcx, r14
4ef03a  setnle al
4ef03d  mov [rbp+rbx*8+29Dh], al
4ef044  call MSG_ReadBits; MSG_ReadBits
4ef049  lea rcx, [rsi+2Ah]
4ef04d  add rcx, rcx
4ef050  mov [rbp+rcx*8+0], eax
4ef054  mov r9d, [r14+28h]
4ef058  and r9d, 7
4ef05c  jnz short loc_4EF08C
4ef05e  mov eax, [r14+20h]
4ef062  add eax, [r14+1Ch]
4ef066  mov ecx, [r14+24h]
4ef06a  cmp ecx, eax
4ef06c  jl short loc_4EF07A
4ef06e  mov dword ptr [r14], 1
4ef075  or eax, 0FFFFFFFFh
4ef078  jmp short loc_4EF0CA
4ef07a  lea eax, ds:0[rcx*8]
4ef081  mov [r14+28h], eax
4ef085  lea eax, [rcx+1]
4ef088  mov [r14+24h], eax
4ef08c  mov r8d, [r14+28h]
4ef090  mov eax, r8d
4ef093  sar eax, 3
4ef096  mov ecx, eax
4ef098  sub ecx, [r14+1Ch]
4ef09c  js short loc_4EF0AB
4ef09e  mov rax, [r14+10h]
4ef0a2  movsxd rcx, ecx
4ef0a5  movzx edx, byte ptr [rcx+rax]
4ef0a9  jmp short loc_4EF0B6
4ef0ab  movsxd rdx, eax
4ef0ae  mov rax, [r14+8]
4ef0b2  movzx edx, byte ptr [rdx+rax]
4ef0b6  lea eax, [r8+1]
4ef0ba  movzx ecx, r9b
4ef0be  mov [r14+28h], eax
4ef0c2  movzx eax, dl
4ef0c5  shr eax, cl
4ef0c7  and eax, 1
4ef0ca  test eax, eax
4ef0cc  setnle al
4ef0cf  mov [rbp+rbx*8+2A4h], al
4ef0d6  mov r8d, [r14+28h]
4ef0da  and r8d, 7
4ef0de  jnz short loc_4EF10E
4ef0e0  mov eax, [r14+20h]
4ef0e4  add eax, [r14+1Ch]
4ef0e8  mov ecx, [r14+24h]
4ef0ec  cmp ecx, eax
4ef0ee  jl short loc_4EF0FC
4ef0f0  mov dword ptr [r14], 1
4ef0f7  or eax, 0FFFFFFFFh
4ef0fa  jmp short loc_4EF14C
4ef0fc  lea eax, ds:0[rcx*8]
4ef103  mov [r14+28h], eax
4ef107  lea eax, [rcx+1]
4ef10a  mov [r14+24h], eax
4ef10e  mov r9d, [r14+28h]
4ef112  mov eax, r9d
4ef115  sar eax, 3
4ef118  mov ecx, eax
4ef11a  sub ecx, [r14+1Ch]
4ef11e  js short loc_4EF12D
4ef120  mov rax, [r14+10h]
4ef124  movsxd rcx, ecx
4ef127  movzx edx, byte ptr [rcx+rax]
4ef12b  jmp short loc_4EF138
4ef12d  movsxd rdx, eax
4ef130  mov rax, [r14+8]
4ef134  movzx edx, byte ptr [rdx+rax]
4ef138  lea eax, [r9+1]
4ef13c  movzx ecx, r8b
4ef140  mov [r14+28h], eax
4ef144  movzx eax, dl
4ef147  shr eax, cl
4ef149  and eax, 1
4ef14c  test eax, eax
4ef14e  setnle al
4ef151  mov [rbp+rbx*8+2A5h], al
4ef158  lea eax, [r15+1]
4ef15c  mov [rbp+rbx*8+2A6h], al
4ef163  mov r8d, [r14+28h]
4ef167  and r8d, 7
4ef16b  jnz short loc_4EF19B
4ef16d  mov eax, [r14+20h]
4ef171  add eax, [r14+1Ch]
4ef175  mov ecx, [r14+24h]
4ef179  cmp ecx, eax
4ef17b  jl short loc_4EF189
4ef17d  mov dword ptr [r14], 1
4ef184  or eax, 0FFFFFFFFh
4ef187  jmp short loc_4EF1D9
4ef189  lea eax, ds:0[rcx*8]
4ef190  mov [r14+28h], eax
4ef194  lea eax, [rcx+1]
4ef197  mov [r14+24h], eax
4ef19b  mov r9d, [r14+28h]
4ef19f  mov eax, r9d
4ef1a2  sar eax, 3
4ef1a5  mov ecx, eax
4ef1a7  sub ecx, [r14+1Ch]
4ef1ab  js short loc_4EF1BA
4ef1ad  mov rax, [r14+10h]
4ef1b1  movsxd rcx, ecx
4ef1b4  movzx edx, byte ptr [rcx+rax]
4ef1b8  jmp short loc_4EF1C5
4ef1ba  movsxd rdx, eax
4ef1bd  mov rax, [r14+8]
4ef1c1  movzx edx, byte ptr [rdx+rax]
4ef1c5  lea eax, [r9+1]
4ef1c9  movzx ecx, r8b
4ef1cd  mov [r14+28h], eax
4ef1d1  movzx eax, dl
4ef1d4  shr eax, cl
4ef1d6  and eax, 1
4ef1d9  test r12b, r12b
4ef1dc  jz short loc_4EF1FA
4ef1de  test eax, eax
4ef1e0  jnz loc_4EF285
4ef1e6  mov rcx, r14
4ef1e9  call MSG_ReadByte; Basis: Arxan-obfuscated body; identified from use (deltaNum, snapFlags)
4ef1ee  mov [rbp+rbx*8+2A6h], al
4ef1f5  jmp loc_4EF285
4ef1fa  test eax, eax
4ef1fc  jnz loc_4EF285
4ef202  mov [rbp+rbx*8+2A6h], r13b
4ef20a  jmp short loc_4EF285
4ef20c  test edi, edi
4ef20e  jle short loc_4EF285
4ef210  test dil, 3
4ef214  jnz short loc_4EF285
4ef216  and r9d, 7
4ef21a  jnz short loc_4EF246
4ef21c  mov ecx, [r14+20h]
4ef220  mov edx, [r14+24h]
4ef224  add ecx, r8d
4ef227  cmp edx, ecx
4ef229  jl short loc_4EF234
4ef22b  mov dword ptr [r14], 1
4ef232  jmp short loc_4EF285
4ef234  lea eax, ds:0[rdx*8]
4ef23b  mov [r14+28h], eax
4ef23f  lea eax, [rdx+1]
4ef242  mov [r14+24h], eax
4ef246  mov r10d, [r14+28h]
4ef24a  mov eax, r10d
4ef24d  sar eax, 3
4ef250  mov ecx, eax
4ef252  sub ecx, r8d
4ef255  js short loc_4EF264
4ef257  mov rax, [r14+10h]
4ef25b  movsxd rcx, ecx
4ef25e  movzx edx, byte ptr [rcx+rax]
4ef262  jmp short loc_4EF26F
4ef264  movsxd rdx, eax
4ef267  mov rax, [r14+8]
4ef26b  movzx edx, byte ptr [rdx+rax]
4ef26f  lea eax, [r10+1]
4ef273  movzx ecx, r9b
4ef277  mov [r14+28h], eax
4ef27b  movzx eax, dl
4ef27e  shr eax, cl
4ef280  and eax, 1
4ef283  jz short loc_4EF293
4ef285  inc edi
4ef287  inc rsi
4ef28a  cmp edi, 0Fh
4ef28d  jl loc_4EEB60
4ef293  mov r15, [rsp+arg_48]
4ef298  jmp short loc_4EF2A0
4ef29a  xor r13d, r13d
4ef29d  nop dword ptr [rax]
4ef2a0  mov r8d, [r14+28h]
4ef2a4  and r8d, 7
4ef2a8  jnz short loc_4EF2D5
4ef2aa  mov eax, [r14+20h]
4ef2ae  add eax, [r14+1Ch]
4ef2b2  mov ecx, [r14+24h]
4ef2b6  cmp ecx, eax
4ef2b8  jl short loc_4EF2C3
4ef2ba  mov dword ptr [r14], 1
4ef2c1  jmp short loc_4EF318
4ef2c3  lea eax, ds:0[rcx*8]
4ef2ca  mov [r14+28h], eax
4ef2ce  lea eax, [rcx+1]
4ef2d1  mov [r14+24h], eax
4ef2d5  mov r9d, [r14+28h]
4ef2d9  mov eax, r9d
4ef2dc  sar eax, 3
4ef2df  mov ecx, eax
4ef2e1  sub ecx, [r14+1Ch]
4ef2e5  js short loc_4EF2F4
4ef2e7  mov rax, [r14+10h]
4ef2eb  movsxd rcx, ecx
4ef2ee  movzx edx, byte ptr [rcx+rax]
4ef2f2  jmp short loc_4EF2FF
4ef2f4  movsxd rdx, eax
4ef2f7  mov rax, [r14+8]
4ef2fb  movzx edx, byte ptr [rdx+rax]
4ef2ff  inc r9d
4ef302  movzx eax, dl
4ef305  movzx ecx, r8b
4ef309  mov [r14+28h], r9d
4ef30d  shr eax, cl
4ef30f  and eax, 1
4ef312  jz loc_4EF487
4ef318  mov edx, 4
4ef31d  mov rcx, r14
4ef320  call MSG_ReadBits; MSG_ReadBits
4ef325  mov r8d, [r14+28h]
4ef329  movsxd rcx, eax
4ef32c  lea rbx, [rcx+rcx*2]
4ef330  and r8d, 7
4ef334  jnz short loc_4EF361
4ef336  mov eax, [r14+20h]
4ef33a  add eax, [r14+1Ch]
4ef33e  mov ecx, [r14+24h]
4ef342  cmp ecx, eax
4ef344  jl short loc_4EF34F
4ef346  mov dword ptr [r14], 1
4ef34d  jmp short loc_4EF3A1
4ef34f  lea eax, ds:0[rcx*8]
4ef356  mov [r14+28h], eax
4ef35a  lea eax, [rcx+1]
4ef35d  mov [r14+24h], eax
4ef361  mov r9d, [r14+28h]
4ef365  mov eax, r9d
4ef368  sar eax, 3
4ef36b  mov ecx, eax
4ef36d  sub ecx, [r14+1Ch]
4ef371  js short loc_4EF380
4ef373  mov rax, [r14+10h]
4ef377  movsxd rcx, ecx
4ef37a  movzx edx, byte ptr [rcx+rax]
4ef37e  jmp short loc_4EF38B
4ef380  movsxd rdx, eax
4ef383  mov rax, [r14+8]
4ef387  movzx edx, byte ptr [rdx+rax]
4ef38b  lea eax, [r9+1]
4ef38f  movzx ecx, r8b
4ef393  mov [r14+28h], eax
4ef397  movzx eax, dl
4ef39a  shr eax, cl
4ef39c  and eax, 1
4ef39f  jz short loc_4EF3CC
4ef3a1  mov edx, 1
4ef3a6  mov rcx, r14
4ef3a9  call MSG_ReadBits; MSG_ReadBits
4ef3ae  inc eax
4ef3b0  mov [rbp+rbx*4+3BCh], r13d
4ef3b8  mov [rbp+rbx*4+3C0h], al
4ef3bf  mov byte ptr [rbp+rbx*4+3C1h], 1
4ef3c7  jmp loc_4EF46E
4ef3cc  mov edx, 1Bh
4ef3d1  mov rcx, r14
4ef3d4  call MSG_ReadBits; MSG_ReadBits
4ef3d9  mov r8d, [r14+28h]
4ef3dd  mov r10d, eax
4ef3e0  and r8d, 7
4ef3e4  jnz short loc_4EF414
4ef3e6  mov ecx, [r14+20h]
4ef3ea  add ecx, [r14+1Ch]
4ef3ee  mov edx, [r14+24h]
4ef3f2  cmp edx, ecx
4ef3f4  jl short loc_4EF402
4ef3f6  mov dword ptr [r14], 1
4ef3fd  or eax, 0FFFFFFFFh
4ef400  jmp short loc_4EF452
4ef402  lea eax, ds:0[rdx*8]
4ef409  mov [r14+28h], eax
4ef40d  lea eax, [rdx+1]
4ef410  mov [r14+24h], eax
4ef414  mov r9d, [r14+28h]
4ef418  mov eax, r9d
4ef41b  sar eax, 3
4ef41e  mov ecx, eax
4ef420  sub ecx, [r14+1Ch]
4ef424  js short loc_4EF433
4ef426  mov rax, [r14+10h]
4ef42a  movsxd rcx, ecx
4ef42d  movzx edx, byte ptr [rcx+rax]
4ef431  jmp short loc_4EF43E
4ef433  movsxd rdx, eax
4ef436  mov rax, [r14+8]
4ef43a  movzx edx, byte ptr [rdx+rax]
4ef43e  lea eax, [r9+1]
4ef442  movzx ecx, r8b
4ef446  mov [r14+28h], eax
4ef44a  movzx eax, dl
4ef44d  shr eax, cl
4ef44f  and eax, 1
4ef452  test eax, eax
4ef454  mov [rbp+rbx*4+3BCh], r10d
4ef45c  mov byte ptr [rbp+rbx*4+3C0h], 0
4ef464  setnz al
4ef467  mov [rbp+rbx*4+3C1h], al
4ef46e  mov edx, 0Ah
4ef473  mov rcx, r14
4ef476  call MSG_ReadBits; MSG_ReadBits
4ef47b  mov [rbp+rbx*4+3C4h], eax
4ef482  jmp loc_4EF2A0
4ef487  and r9d, 7
4ef48b  jnz short loc_4EF4B8
4ef48d  mov eax, [r14+20h]
4ef491  add eax, [r14+1Ch]
4ef495  mov ecx, [r14+24h]
4ef499  cmp ecx, eax
4ef49b  jl short loc_4EF4A6
4ef49d  mov dword ptr [r14], 1
4ef4a4  jmp short loc_4EF4FC
4ef4a6  lea eax, ds:0[rcx*8]
4ef4ad  mov [r14+28h], eax
4ef4b1  lea eax, [rcx+1]
4ef4b4  mov [r14+24h], eax
4ef4b8  mov r8d, [r14+28h]
4ef4bc  mov eax, r8d
4ef4bf  sar eax, 3
4ef4c2  mov ecx, eax
4ef4c4  sub ecx, [r14+1Ch]
4ef4c8  js short loc_4EF4D7
4ef4ca  mov rax, [r14+10h]
4ef4ce  movsxd rcx, ecx
4ef4d1  movzx edx, byte ptr [rcx+rax]
4ef4d5  jmp short loc_4EF4E2
4ef4d7  movsxd rdx, eax
4ef4da  mov rax, [r14+8]
4ef4de  movzx edx, byte ptr [rdx+rax]
4ef4e2  lea eax, [r8+1]
4ef4e6  movzx ecx, r9b
4ef4ea  mov [r14+28h], eax
4ef4ee  movzx eax, dl
4ef4f1  shr eax, cl
4ef4f3  and eax, 1
4ef4f6  jz loc_4EF57A
4ef4fc  mov rax, cs:off_12D4BA8
4ef503  lea rdi, [rbp+1E64h]
4ef50a  mov ebp, [rsp+arg_44]
4ef50e  lea rbx, [r15+1E64h]
4ef515  mov r15, rdi
4ef518  mov esi, 24h ; '$'
4ef51d  sub r15, rbx
4ef520  mov r12d, [rax+48h]
4ef524  mov r13, [rax+40h]
4ef528  nop dword ptr [rax+rax+00000000h]
4ef530  mov edx, 3
4ef535  mov rcx, r14
4ef538  call MSG_ReadBits; MSG_ReadBits
4ef53d  mov [rsp+arg_30], 0
4ef542  lea r9, [r15+rbx]
4ef546  mov dword ptr [rsp+arg_28], 1
4ef54e  mov r8, rbx
4ef551  mov [rsp+arg_20], r13
4ef556  mov edx, ebp
4ef558  mov rcx, r14
4ef55b  mov dword ptr [rsp+arg_18], r12d
4ef560  mov [rdi], eax
4ef562  call sub_4EDAF0
4ef567  add rbx, 24h ; '$'
4ef56b  lea rdi, [rdi+24h]
4ef56f  sub rsi, 1
4ef573  jnz short loc_4EF530
4ef575  mov rbp, [rsp+arg_60]
4ef57a  mov r8d, [r14+28h]
4ef57e  and r8d, 7
4ef582  jnz short loc_4EF5AF
4ef584  mov eax, [r14+20h]
4ef588  add eax, [r14+1Ch]
4ef58c  mov ecx, [r14+24h]
4ef590  cmp ecx, eax
4ef592  jl short loc_4EF59D
4ef594  mov dword ptr [r14], 1
4ef59b  jmp short loc_4EF5EF
4ef59d  lea eax, ds:0[rcx*8]
4ef5a4  mov [r14+28h], eax
4ef5a8  lea eax, [rcx+1]
4ef5ab  mov [r14+24h], eax
4ef5af  mov r9d, [r14+28h]
4ef5b3  mov eax, r9d
4ef5b6  sar eax, 3
4ef5b9  mov ecx, eax
4ef5bb  sub ecx, [r14+1Ch]
4ef5bf  js short loc_4EF5CE
4ef5c1  mov rax, [r14+10h]
4ef5c5  movsxd rcx, ecx
4ef5c8  movzx edx, byte ptr [rcx+rax]
4ef5cc  jmp short loc_4EF5D9
4ef5ce  movsxd rdx, eax
4ef5d1  mov rax, [r14+8]
4ef5d5  movzx edx, byte ptr [rdx+rax]
4ef5d9  lea eax, [r9+1]
4ef5dd  movzx ecx, r8b
4ef5e1  mov [r14+28h], eax
4ef5e5  movzx eax, dl
4ef5e8  shr eax, cl
4ef5ea  and eax, 1
4ef5ed  jz short loc_4EF64A
4ef5ef  mov rbx, [rsp+arg_48]
4ef5f4  lea r9, [rbp+3A00h]
4ef5fb  mov edx, [rsp+arg_44]
4ef5ff  mov rcx, r14
4ef602  mov dword ptr [rsp+arg_20], 4
4ef60a  mov dword ptr [rsp+arg_18], 0Fh
4ef612  lea r8, [rbx+3A00h]
4ef619  call sub_4EDD10
4ef61e  mov edx, [rsp+arg_44]
4ef622  lea r9, [rbp+2380h]
4ef629  lea r8, [rbx+2380h]
4ef630  mov dword ptr [rsp+arg_20], 5
4ef638  mov rcx, r14
4ef63b  mov dword ptr [rsp+arg_18], 1Eh
4ef643  call sub_4EDD10
4ef648  jmp short loc_4EF64F
4ef64a  mov rbx, [rsp+arg_48]
4ef64f  call sub_5A47B0
4ef654  lea rsi, [rbp+4540h]
4ef65b  mov edi, eax
4ef65d  lea rbp, [rbx+4540h]
4ef664  call sub_5A47A0
4ef669  mov ebx, eax
4ef66b  call sub_5A4790
4ef670  mov edx, [rsp+arg_44]
4ef674  mov r8d, eax
4ef677  mov dword ptr [rsp+arg_28], edi
4ef67b  mov r9d, ebx
4ef67e  mov [rsp+arg_20], rsi
4ef683  mov rcx, r14
4ef686  mov [rsp+arg_18], rbp
4ef68b  call sub_4EE380
4ef690  mov rdi, [rsp+arg_4948]
4ef698  mov rcx, [rsp+arg_48F8]
4ef6a0  xor rcx, rsp; StackCookie
4ef6a3  call __security_check_cookie
4ef6a8  add rsp, 4910h
4ef6af  pop r15
4ef6b1  pop r14
4ef6b3  pop r13
4ef6b5  pop r12
4ef6b7  pop rsi
4ef6b8  pop rbp
4ef6b9  pop rbx
4ef6ba  retn
