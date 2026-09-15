int __cdecl CG_RegisterWeapon(int a1, int a2)
{
  int result; // eax
  const char **WeaponDef; // edi
  _DWORD *v4; // esi
  int WeaponViewModelXAnim; // eax
  int i; // esi
  const char *v7; // ebx
  const char *v8; // eax
  int v9; // edx
  int String; // eax
  int v11; // eax
  int v12; // [esp+2Ch] [ebp-3Ch]
  const char *v13; // [esp+3Ch] [ebp-2Ch] BYREF
  __int16 v14; // [esp+40h] [ebp-28h]
  char v15; // [esp+42h] [ebp-26h]
  const char *v16; // [esp+44h] [ebp-24h]
  __int16 v17; // [esp+48h] [ebp-20h]
  char v18; // [esp+4Ah] [ebp-1Eh]
  unsigned __int8 v19[25]; // [esp+4Fh] [ebp-19h] BYREF

  result = a2; /*0x77cd9*/
  removeMeWhenMPStopsCrashingInHere = a2; /*0x77cdc*/
  if ( a2 )
  {
    WeaponDef = (const char **)BG_GetWeaponDef(a2); /*0x77cf8*/
    v4 = (_DWORD *)((char *)&cg_weaponsArray + 68 * a2); /*0x77d0f*/
    result = v4[12]; /*0x77d12*/
    if ( !result )
    {
      SCR_UpdateLoadScreen(); /*0x77d19*/
      memset(v4, 0, 0x44u); /*0x77d31*/
      v4[12] = 1; /*0x77d36*/
      v4[13] = (char *)&bg_itemlist + 4 * a2; /*0x77d45*/
      v4[10] = -1; /*0x77d48*/
      if ( WeaponDef[3] && WeaponDef[19] )
      {
        v14 = 0; /*0x77d65*/
        v17 = word_17656E6; /*0x77d77*/
        v15 = 0; /*0x77d7b*/
        v18 = 0; /*0x77d7f*/
        v13 = WeaponDef[19]; /*0x77d86*/
        v16 = WeaponDef[3]; /*0x77d8c*/
        WeaponViewModelXAnim = CG_CreateWeaponViewModelXAnim(); /*0x77d91*/
        v4[11] = WeaponViewModelXAnim; /*0x77d96*/
        v12 = Com_ClientDObjCreate(&v13, 2, WeaponViewModelXAnim, a2 + 1024); /*0x77dc4*/
        *v4 = v12; /*0x77dc7*/
        v4[1] = WeaponDef[19]; /*0x77dcc*/
        *((_BYTE *)v4 + 20) = 0; /*0x77dcf*/
        XAnimClearTreeGoalWeights(v4[11], 0, 0); /*0x77de9*/
        XAnimSetGoalWeight(v12, 0, 1065353216, 0, 1065353216, 0, 1, 0); /*0x77e29*/
        XAnimSetGoalWeight(v12, 1, 1065353216, 0, 1065353216, 0, 1, 0); /*0x77e64*/
        if ( *WeaponDef[52] ) /*0x77e6f*/
        {
          XAnimSetGoalWeight(v12, 32, 1065353216, 0, 0, 0, 1, 0); /*0x7816a*/
          XAnimSetTime(v4[11], 32, 1065353216); /*0x78181*/
        }
        for ( i = 0; i != 8; ++i )
        {
          if ( !*((_WORD *)WeaponDef + i + 108) ) /*0x77eb9*/
            break; /*0x77ec2*/
          v19[0] = -2; /*0x77ec4*/
          if ( DObjGetBoneIndex(v12, *((unsigned __int16 *)WeaponDef + i + 108), v19) )
          {
            *((_DWORD *)&cg_weaponsArray + 17 * a2 + (v19[0] >> 5) + 6) |= 0x80000000 >> (v19[0] & 0x1F); /*0x77eaf*/
          }
          else
          {
            v7 = *WeaponDef; /*0x77eea*/
            v8 = (const char *)SL_ConvertToString(*((unsigned __int16 *)WeaponDef + i + 108)); /*0x77ef7*/
            Com_PrintError(14, "CG_RegisterWeapon: No such bone tag (%s) for weapon (%s)\n", v8, v7);
          }
        }
        DObjSetHidePartBits(v12, (char *)&cg_weaponsArray + 68 * a2 + 24); /*0x77f40*/
        DObjUpdateClientInfo(*((_DWORD *)&cg_weaponsArray + 17 * a2), 1028443341, 0); /*0x77f61*/
      }
      v9 = (int)WeaponDef[195]; /*0x77f66*/
      if ( v9 ) /*0x77f6e*/
        cgMedia[a2 + 13] = v9; /*0x77f7c*/
      else
        cgMedia[a2 + 13] = 0; /*0x78063*/
      String = SEH_StringEd_GetString(WeaponDef[1]); /*0x77f86*/
      *((_DWORD *)&cg_weaponsArray + 17 * a2 + 14) = String; /*0x77f9d*/
      if ( !String )
      {
        if ( *(_BYTE *)(loc_warnings + 12) )
        {
          if ( *(_BYTE *)(loc_warningsAsErrors + 12) )
            Com_Error(7, "Weapon %s: Could not translate display name \"%s\"", (char)*WeaponDef);
          else
            Com_PrintWarning(
              17,
              "WARNING: Weapon %s: Could not translate display name \"%s\"\n",
              *WeaponDef,
              WeaponDef[1]);
        }
        *((_DWORD *)&cg_weaponsArray + 17 * a2 + 14) = WeaponDef[1]; /*0x78127*/
      }
      v11 = SEH_StringEd_GetString(WeaponDef[53]); /*0x77fb2*/
      *((_DWORD *)&cg_weaponsArray + 17 * a2 + 15) = v11; /*0x77fc9*/
      if ( !v11 )
      {
        if ( *(_BYTE *)(loc_warnings + 12) )
        {
          if ( *(_BYTE *)(loc_warningsAsErrors + 12) )
            Com_Error(7, "Weapon %s: Could not translate mode name \"%s\"", (char)*WeaponDef);
          else
            Com_PrintWarning(
              17,
              "WARNING: Weapon %s: Could not translate mode name \"%s\"\n",
              *WeaponDef,
              WeaponDef[53]);
        }
        *((_DWORD *)&cg_weaponsArray + 17 * a2 + 15) = WeaponDef[53]; /*0x780ca*/
      }
      result = SEH_StringEd_GetString(WeaponDef[2]); /*0x77fdb*/
      *((_DWORD *)&cg_weaponsArray + 17 * a2 + 16) = result; /*0x77ff2*/
      if ( !result )
      {
        if ( *(_BYTE *)(loc_warnings + 12) )
        {
          if ( *(_BYTE *)(loc_warningsAsErrors + 12) )
            Com_Error(7, "Weapon %s: Could not translate AI overlay description \"%s\"", (char)*WeaponDef);
          else
            Com_PrintWarning(
              17,
              "WARNING: Weapon %s: Could not translate AI overlay description \"%s\"\n",
              *WeaponDef,
              WeaponDef[2]);
        }
        result = (int)WeaponDef[2]; /*0x78049*/
        *((_DWORD *)&cg_weaponsArray + 17 * a2 + 16) = result; /*0x78052*/
      }
    }
  }
  return result; /*0x77ce5*/
}