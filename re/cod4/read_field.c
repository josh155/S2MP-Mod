int __cdecl MSG_ReadDeltaField(_DWORD *a1, int a2, int a3, int a4, const char **a5, int a6, char a7)
{
  const char *v7; // eax
  int v8; // ecx
  char v9; // si
  int v10; // edx
  int v11; // eax
  int result; // eax
  int v13; // ebx
  const char *v14; // ebx
  int v15; // ecx
  char v16; // bl
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  int v20; // ebx
  int v21; // esi
  int v22; // edx
  int v23; // ecx
  char v24; // si
  int v25; // ebx
  int v26; // ecx
  char v27; // si
  char v28; // al
  int v29; // ecx
  char v30; // al
  int v31; // ecx
  char v32; // al
  int v33; // edx
  char v34; // al
  int v35; // eax
  int v36; // edx
  int v37; // eax
  char v38; // bl
  int v39; // edx
  int v40; // ecx
  int v41; // esi
  char v42; // al
  int v43; // ecx
  char v44; // al
  int v45; // ecx
  char v46; // al
  int v47; // edx
  char v48; // al
  int v49; // eax
  int v50; // edx
  int v51; // eax
  char v52; // dl
  char v53; // si
  int v54; // edx
  int v55; // eax
  int v56; // esi
  int v57; // edx
  int v58; // eax
  int v59; // edx
  int v60; // eax
  int v61; // edx
  int v62; // eax
  char v63; // si
  int v64; // edx
  int v65; // eax
  int v66; // esi
  int v67; // edx
  int v68; // eax
  int v69; // ecx
  char v70; // si
  int v71; // ebx
  char v72; // al
  int v73; // ecx
  char v74; // al
  int v75; // ecx
  char v76; // al
  int v77; // edx
  char v78; // al
  float v79; // xmm0_4
  int v80; // edx
  int v81; // eax
  int v82; // edx
  int v83; // ecx
  char v84; // si
  int v85; // ebx
  int v86; // ecx
  char v87; // si
  char v88; // al
  int v89; // ecx
  char v90; // al
  int v91; // ecx
  char v92; // al
  int v93; // edx
  char v94; // al
  int v95; // eax
  int v96; // edx
  int v97; // eax
  int v98; // ebx
  char v99; // si
  int v100; // edx
  int v101; // eax
  int v102; // esi
  int v103; // ebx
  int v104; // edx
  int v105; // eax
  int v106; // ebx
  int v107; // edx
  int v108; // eax
  int v109; // ebx
  int v110; // edx
  int v111; // eax
  int v112; // ebx
  char v113; // si
  int v114; // edx
  int v115; // eax
  int v116; // edx
  int v117; // eax
  int v118; // edx
  int v119; // ebx
  char v120; // si
  int v121; // ebx
  int v122; // ebx
  char v123; // si
  int v124; // ebx
  char v125; // si
  int v126; // edx
  int v127; // eax
  int v128; // esi
  int v129; // edx
  int v130; // eax
  int v131; // ecx
  int v132; // edx
  int v133; // ecx
  char v134; // bl
  int v135; // ecx
  int v136; // esi
  char v137; // bl
  int v138; // edx
  int v139; // edx
  int v140; // edx
  int v141; // eax
  int v142; // ebx
  int v143; // esi
  int v144; // edx
  int v145; // edx
  int v146; // edx
  int v147; // eax
  char v148; // si
  int v149; // edx
  int v150; // edx
  int v151; // edx
  int v152; // eax
  int v153; // edx
  int v154; // edx
  int v155; // edx
  int v156; // eax
  int v157; // esi
  int v158; // ebx
  int v159; // edx
  int v160; // edx
  int v161; // edx
  int v162; // eax
  int v163; // ecx
  char v164; // si
  int v165; // ebx
  char v166; // al
  int v167; // ecx
  char v168; // al
  int v169; // ecx
  char v170; // al
  int v171; // edx
  char v172; // al
  int v173; // edx
  int v174; // eax
  char v175; // dl
  char v176; // si
  int v177; // edx
  int v178; // eax
  int v179; // esi
  int v180; // edx
  int v181; // eax
  int v182; // edx
  int v183; // eax
  int v184; // esi
  int v185; // edx
  int v186; // eax
  int v187; // edx
  int v188; // eax
  int v189; // ebx
  int v190; // edx
  int v191; // ecx
  int v192; // edx
  int v193; // eax
  int v194; // edx
  int v195; // eax
  int v196; // ebx
  int v197; // ecx
  int v198; // edx
  int v199; // esi
  int v200; // ecx
  int v201; // edx
  int v202; // eax
  char v203; // dl
  char v204; // bl
  int v205; // edx
  int v206; // edx
  int v207; // edx
  int v208; // eax
  int v209; // esi
  int v210; // edx
  int v211; // edx
  int v212; // edx
  int v213; // eax
  int v214; // esi
  char v215; // bl
  int v216; // edx
  int v217; // edx
  int v218; // edx
  int v219; // eax
  int v220; // esi
  char v221; // bl
  int v222; // edx
  int v223; // edx
  int v224; // edx
  int v225; // eax
  int v226; // esi
  char v227; // bl
  int v228; // edx
  int v229; // edx
  int v230; // edx
  int v231; // eax
  int v232; // esi
  char v233; // bl
  int v234; // edx
  int v235; // edx
  int v236; // edx
  int v237; // eax
  int v238; // ebx
  int v239; // esi
  int v240; // edx
  int v241; // edx
  int v242; // edx
  int v243; // eax
  int v244; // ebx
  int v245; // esi
  int v246; // edx
  int v247; // edx
  int v248; // edx
  int v249; // eax
  int v250; // eax
  int v251; // edx
  int v252; // edx
  int v253; // esi
  char v254; // bl
  int v255; // edx
  int v256; // edx
  int v257; // edx
  int v258; // eax
  int v259; // esi
  char v260; // bl
  int v261; // edx
  int v262; // edx
  int v263; // edx
  int v264; // eax
  int v265; // esi
  char v266; // bl
  int v267; // edx
  int v268; // edx
  int v269; // edx
  int v270; // eax
  int v271; // esi
  char v272; // bl
  int v273; // edx
  int v274; // edx
  int v275; // edx
  int v276; // eax
  int v277; // esi
  char v278; // bl
  int v279; // edx
  int v280; // edx
  int v281; // edx
  int v282; // eax
  int v283; // ebx
  int v284; // esi
  int v285; // edx
  int v286; // edx
  int v287; // edx
  int v288; // eax
  int v289; // ebx
  int v290; // esi
  int v291; // edx
  int v292; // edx
  int v293; // edx
  int v294; // eax
  int v295; // edx
  char v296; // bl
  int v297; // edx
  int v298; // ebx
  int v299; // eax
  char v300; // si
  int v301; // edx
  int v302; // edx
  int v303; // edx
  int v304; // edx
  char v305; // si
  int v306; // edx
  int v307; // ebx
  int v308; // eax
  char v309; // si
  int v310; // edx
  int v311; // edx
  int v312; // edx
  int v313; // ecx
  char v314; // si
  int v315; // ebx
  char v316; // al
  int v317; // edx
  char v318; // al
  float v319; // xmm0_4
  int v320; // ecx
  int v321; // eax
  int v322; // esi
  char v323; // bl
  int v324; // edx
  int v325; // edx
  int v326; // edx
  int v327; // eax
  int v328; // esi
  char v329; // bl
  int v330; // edx
  int v331; // edx
  int v332; // edx
  int v333; // eax
  int v334; // esi
  char v335; // bl
  int v336; // edx
  int v337; // edx
  int v338; // edx
  int v339; // eax
  int v340; // esi
  char v341; // bl
  int v342; // edx
  int v343; // edx
  int v344; // edx
  int v345; // eax
  int v346; // edx
  int v347; // edx
  int v348; // edx
  int v349; // eax
  int v350; // esi
  int v351; // ebx
  int v352; // edx
  int v353; // edx
  int v354; // edx
  int v355; // eax
  int v356; // ebx
  char v357; // si
  int v358; // edx
  int v359; // edx
  int v360; // edx
  int v361; // eax
  float v362; // xmm0_4
  int v363; // ecx
  char v364; // al
  int v365; // edx
  char v366; // al
  int v367; // ecx
  int v368; // eax
  int v369; // edx
  char v370; // bl
  int v371; // edx
  int v372; // edx
  int v373; // edx
  int v374; // eax
  int v375; // esi
  int v376; // edx
  int v377; // edx
  int v378; // edx
  int v379; // eax
  int v380; // esi
  char v381; // bl
  int v382; // edx
  int v383; // edx
  int v384; // edx
  int v385; // eax
  int v386; // esi
  char v387; // bl
  int v388; // edx
  int v389; // edx
  int v390; // edx
  int v391; // eax
  int v392; // edx
  int v393; // edx
  int v394; // edx
  int v395; // eax
  int v396; // esi
  int v397; // ebx
  int v398; // edx
  int v399; // edx
  int v400; // edx
  int v401; // eax
  int v402; // ebx
  char v403; // si
  int v404; // edx
  int v405; // edx
  int v406; // edx
  int v407; // eax
  float v408; // xmm0_4
  int v409; // edx
  int v410; // ebx
  int v411; // esi
  char v412; // bl
  int v413; // edx
  int v414; // edx
  int v415; // edx
  int v416; // eax
  int v417; // ebx
  int v418; // esi
  int v419; // edx
  int v420; // edx
  int v421; // edx
  int v422; // eax
  char v423; // si
  int v424; // edx
  int v425; // edx
  int v426; // edx
  int v427; // eax
  int v428; // esi
  int v429; // edx
  int v430; // edx
  int v431; // edx
  int v432; // eax
  int v433; // ebx
  int v434; // ecx
  int v435; // edx
  int v436; // edx
  int v437; // edx
  int v438; // eax
  float v439; // xmm0_4
  int v440; // edx
  int v441; // eax
  int v442; // ecx
  char v443; // bl
  int v444; // edx
  int v445; // eax
  int v446; // ebx
  char v447; // si
  int v448; // edx
  int v449; // edx
  int v450; // edx
  int v451; // edx
  int v452; // edx
  int v453; // eax
  char v454; // dl
  char v455; // bl
  int v456; // edx
  int v457; // esi
  char v458; // bl
  int v459; // edx
  int v460; // edx
  int v461; // edx
  int v462; // eax
  int v463; // ebx
  int v464; // esi
  int v465; // edx
  int v466; // edx
  int v467; // edx
  int v468; // eax
  char v469; // si
  int v470; // edx
  int v471; // edx
  int v472; // edx
  int v473; // eax
  int v474; // esi
  int v475; // edx
  int v476; // edx
  int v477; // edx
  int v478; // eax
  int v479; // ebx
  int v480; // ecx
  int v481; // edx
  int v482; // edx
  int v483; // edx
  int v484; // eax
  int v485; // edx
  int v486; // eax
  int v487; // ecx
  char v488; // dl
  char v489; // al
  int v490; // ecx
  int v491; // edx
  char v492; // dl
  char v493; // al
  int v494; // ecx
  int v495; // edx
  char v496; // dl
  char v497; // al
  int v498; // edx
  int v499; // [esp+2Ch] [ebp-13Ch]
  int v500; // [esp+2Ch] [ebp-13Ch]
  int v501; // [esp+2Ch] [ebp-13Ch]
  int v502; // [esp+2Ch] [ebp-13Ch]
  int v503; // [esp+2Ch] [ebp-13Ch]
  int v504; // [esp+2Ch] [ebp-13Ch]
  int v505; // [esp+2Ch] [ebp-13Ch]
  int v506; // [esp+2Ch] [ebp-13Ch]
  int v507; // [esp+2Ch] [ebp-13Ch]
  int v508; // [esp+2Ch] [ebp-13Ch]
  int v509; // [esp+2Ch] [ebp-13Ch]
  int v510; // [esp+2Ch] [ebp-13Ch]
  int v511; // [esp+2Ch] [ebp-13Ch]
  int v512; // [esp+2Ch] [ebp-13Ch]
  int v513; // [esp+2Ch] [ebp-13Ch]
  int v514; // [esp+2Ch] [ebp-13Ch]
  int v515; // [esp+2Ch] [ebp-13Ch]
  int v516; // [esp+2Ch] [ebp-13Ch]
  int v517; // [esp+2Ch] [ebp-13Ch]
  int v518; // [esp+2Ch] [ebp-13Ch]
  int v519; // [esp+2Ch] [ebp-13Ch]
  int v520; // [esp+2Ch] [ebp-13Ch]
  int v521; // [esp+2Ch] [ebp-13Ch]
  int v522; // [esp+2Ch] [ebp-13Ch]
  int v523; // [esp+2Ch] [ebp-13Ch]
  int v524; // [esp+2Ch] [ebp-13Ch]
  int v525; // [esp+2Ch] [ebp-13Ch]
  int v526; // [esp+2Ch] [ebp-13Ch]
  int v527; // [esp+2Ch] [ebp-13Ch]
  int v528; // [esp+2Ch] [ebp-13Ch]
  int v529; // [esp+2Ch] [ebp-13Ch]
  int v530; // [esp+2Ch] [ebp-13Ch]
  int v531; // [esp+2Ch] [ebp-13Ch]
  int v532; // [esp+2Ch] [ebp-13Ch]
  int v533; // [esp+38h] [ebp-130h]
  int v534; // [esp+38h] [ebp-130h]
  int v535; // [esp+38h] [ebp-130h]
  int v536; // [esp+38h] [ebp-130h]
  int v537; // [esp+38h] [ebp-130h]
  int v538; // [esp+38h] [ebp-130h]
  int v539; // [esp+38h] [ebp-130h]
  int v540; // [esp+38h] [ebp-130h]
  int v541; // [esp+38h] [ebp-130h]
  int v542; // [esp+38h] [ebp-130h]
  int v543; // [esp+38h] [ebp-130h]
  int v544; // [esp+38h] [ebp-130h]
  int v545; // [esp+38h] [ebp-130h]
  int v546; // [esp+38h] [ebp-130h]
  int v547; // [esp+38h] [ebp-130h]
  int v548; // [esp+38h] [ebp-130h]
  int v549; // [esp+38h] [ebp-130h]
  int v550; // [esp+38h] [ebp-130h]
  int *v551; // [esp+3Ch] [ebp-12Ch]
  int *v552; // [esp+40h] [ebp-128h]
  unsigned int v553; // [esp+44h] [ebp-124h]
  int v554; // [esp+48h] [ebp-120h]
  int v555; // [esp+48h] [ebp-120h]
  int v556; // [esp+4Ch] [ebp-11Ch]
  int v557; // [esp+50h] [ebp-118h]
  char v558; // [esp+5Ch] [ebp-10Ch]
  int v559; // [esp+64h] [ebp-104h]
  char v560; // [esp+68h] [ebp-100h]
  char v561; // [esp+70h] [ebp-F8h]
  float v562; // [esp+74h] [ebp-F4h]
  int v563; // [esp+78h] [ebp-F0h]
  int v564; // [esp+7Ch] [ebp-ECh]
  float v565; // [esp+80h] [ebp-E8h]
  int v566; // [esp+84h] [ebp-E4h]
  int v567; // [esp+88h] [ebp-E0h]
  int v568; // [esp+8Ch] [ebp-DCh]
  char v569; // [esp+90h] [ebp-D8h]
  char v570; // [esp+94h] [ebp-D4h]
  int v571; // [esp+98h] [ebp-D0h]
  int v572; // [esp+9Ch] [ebp-CCh]
  int v573; // [esp+A0h] [ebp-C8h]
  int v574; // [esp+A4h] [ebp-C4h]
  int v575; // [esp+A8h] [ebp-C0h]
  char v576; // [esp+ACh] [ebp-BCh]
  char v577; // [esp+B0h] [ebp-B8h]
  char v578; // [esp+B4h] [ebp-B4h]
  int v579; // [esp+B8h] [ebp-B0h]
  int v580; // [esp+BCh] [ebp-ACh]
  char v581; // [esp+C0h] [ebp-A8h]
  char v582; // [esp+C4h] [ebp-A4h]
  char v583; // [esp+C8h] [ebp-A0h]
  int v584; // [esp+CCh] [ebp-9Ch]
  char v585; // [esp+D0h] [ebp-98h]
  char v586; // [esp+D4h] [ebp-94h]
  int v587; // [esp+D8h] [ebp-90h]
  int v588; // [esp+DCh] [ebp-8Ch]
  char v589; // [esp+E0h] [ebp-88h]
  int v590; // [esp+E4h] [ebp-84h]
  int v591; // [esp+E8h] [ebp-80h]
  int v592; // [esp+ECh] [ebp-7Ch]
  int v593; // [esp+F0h] [ebp-78h]
  int v594; // [esp+F4h] [ebp-74h]
  char v595; // [esp+F8h] [ebp-70h]
  int v596; // [esp+FCh] [ebp-6Ch]
  int v597; // [esp+100h] [ebp-68h]
  int v598; // [esp+104h] [ebp-64h]
  int v599; // [esp+108h] [ebp-60h]
  char v600; // [esp+10Ch] [ebp-5Ch]
  int v601; // [esp+110h] [ebp-58h]
  int v602; // [esp+114h] [ebp-54h]
  int v603; // [esp+118h] [ebp-50h]
  int v604; // [esp+11Ch] [ebp-4Ch]
  int v605; // [esp+124h] [ebp-44h]
  int v606; // [esp+128h] [ebp-40h]
  int v607; // [esp+12Ch] [ebp-3Ch]
  int v608; // [esp+134h] [ebp-34h]
  int v609; // [esp+138h] [ebp-30h]
  int v610; // [esp+13Ch] [ebp-2Ch]
  int v611; // [esp+148h] [ebp-20h]
  int v612; // [esp+148h] [ebp-20h]
  int v613; // [esp+148h] [ebp-20h]
  int v614; // [esp+148h] [ebp-20h]
  int v615; // [esp+148h] [ebp-20h]
  __int16 v616; // [esp+148h] [ebp-20h]
  __int16 v617; // [esp+148h] [ebp-20h]
  int v618; // [esp+14Ch] [ebp-1Ch] BYREF

  v618 = 0; /*0x178e4f*/
  v7 = a5[1]; /*0x178e63*/
  if ( a7 ) /*0x178e5a*/
    v551 = &v618; /*0x178e69*/
  else
    v551 = (int *)&v7[a3]; /*0x17908b*/
  v552 = (int *)&v7[a4]; /*0x178e72*/
  if ( *((_BYTE *)a5 + 12) != 2 ) /*0x178e7f*/
  {
    v8 = a1[8]; /*0x178e85*/
    v9 = v8 & 7; /*0x178e8a*/
    if ( (v8 & 7) != 0 ) /*0x178e8d*/
    {
      v533 = a1[5]; /*0x178e92*/
    }
    else
    {
      v13 = a1[7]; /*0x178ee0*/
      v533 = a1[5]; /*0x178ee6*/
      if ( v13 >= a1[6] + v533 ) /*0x178ef3*/
      {
        *a1 = 1; /*0x178ef9*/
        goto LABEL_13; /*0x178ef9*/
      }
      a1[8] = 8 * v13; /*0x179217*/
      ++a1[7]; /*0x17921a*/
      v8 = 8 * v13; /*0x17921d*/
    }
    v10 = v8 >> 3; /*0x178e9a*/
    if ( v8 >> 3 < v533 ) /*0x178ea3*/
      v11 = *(unsigned __int8 *)(a1[2] + v10); /*0x179193*/
    else
      v11 = *(unsigned __int8 *)(a1[3] + v10 - v533); /*0x178eb2*/
    a1[8] = v8 + 1; /*0x178eb9*/
    if ( ((v11 >> v9) & 1) == 0 ) /*0x178ec2*/
    {
      result = *v551; /*0x178eca*/
      *v552 = *v551; /*0x178ed2*/
      return result; /*0x178ed2*/
    }
  }
LABEL_13:
  v14 = a5[2]; /*0x178f00*/
  if ( !v14 ) /*0x178f08*/
  {
    v22 = a1[8]; /*0x1790a0*/
    v23 = v22; /*0x1790a3*/
    v24 = v22 & 7; /*0x1790a7*/
    if ( (v22 & 7) != 0 ) /*0x1790aa*/
    {
      v535 = a1[5]; /*0x1791a3*/
    }
    else
    {
      v25 = a1[7]; /*0x1790b0*/
      v535 = a1[5]; /*0x1790b6*/
      if ( v25 >= a1[6] + v535 ) /*0x1790c1*/
      {
        *a1 = 1; /*0x1790c7*/
        goto LABEL_48; /*0x1790c7*/
      }
      a1[8] = 8 * v25; /*0x17975f*/
      ++a1[7]; /*0x179762*/
      v23 = 8 * v25; /*0x179765*/
    }
    v36 = v23 >> 3; /*0x1791ab*/
    if ( v23 >> 3 < v535 ) /*0x1791b4*/
      v37 = *(unsigned __int8 *)(a1[2] + v36); /*0x1795e3*/
    else
      v37 = *(unsigned __int8 *)(a1[3] + v36 - v535); /*0x1791c3*/
    v22 = v23 + 1; /*0x1791c7*/
    a1[8] = v23 + 1; /*0x1791ca*/
    if ( ((v37 >> v24) & 1) == 0 ) /*0x1791d3*/
    {
      v38 = v22 & 7; /*0x1791db*/
      if ( (v22 & 7) == 0 ) /*0x1791de*/
      {
        v39 = a1[7]; /*0x1791e4*/
        if ( v39 >= a1[6] + v535 ) /*0x1791f2*/
        {
          *a1 = 1; /*0x1791f8*/
          result = 0x80000000; /*0x1791fe*/
LABEL_140:
          *v552 = result; /*0x179745*/
          return result; /*0x179757*/
        }
        a1[8] = 8 * v39; /*0x179711*/
        ++a1[7]; /*0x179714*/
      }
      v80 = (int)a1[8] >> 3; /*0x17971c*/
      if ( v80 < v535 ) /*0x179725*/
        v81 = *(unsigned __int8 *)(a1[2] + v80); /*0x179aa7*/
      else
        v81 = *(unsigned __int8 *)(a1[3] + v80 - v535); /*0x179734*/
      ++a1[8]; /*0x17973b*/
      result = v81 >> v38 << 31; /*0x179742*/
      goto LABEL_140; /*0x179742*/
    }
    v25 = a1[7]; /*0x1795d0*/
LABEL_48:
    v26 = v22; /*0x1790cd*/
    v27 = v22 & 7; /*0x1790d1*/
    if ( (v22 & 7) == 0 ) /*0x1790d4*/
    {
      if ( v25 >= a1[6] + v535 ) /*0x1790e5*/
      {
        *a1 = 1; /*0x1790eb*/
        goto LABEL_51; /*0x1790eb*/
      }
      a1[8] = 8 * v25; /*0x1792b5*/
      ++a1[7]; /*0x1792b8*/
      v26 = 8 * v25; /*0x1792bb*/
      v25 = a1[7]; /*0x1792bd*/
    }
    v50 = v26 >> 3; /*0x1792c2*/
    if ( v26 >> 3 < v535 ) /*0x1792cb*/
      v51 = *(unsigned __int8 *)(a1[2] + v50); /*0x17976f*/
    else
      v51 = *(unsigned __int8 *)(a1[3] + v50 - v535); /*0x1792da*/
    v499 = v26 + 1; /*0x1792df*/
    v52 = v26 + 1; /*0x1792e5*/
    a1[8] = v26 + 1; /*0x1792e7*/
    if ( ((v51 >> v27) & 1) == 0 ) /*0x1792f0*/
    {
      v53 = v52 & 7; /*0x1792f8*/
      if ( (v52 & 7) == 0 ) /*0x1792fb*/
      {
        if ( v25 >= a1[6] + v535 ) /*0x179308*/
          goto LABEL_347; /*0x179308*/
        a1[8] = 8 * v25; /*0x179315*/
        ++a1[7]; /*0x179318*/
        v499 = 8 * v25; /*0x17931b*/
        v25 = a1[7]; /*0x179321*/
      }
      v54 = v499 >> 3; /*0x17932a*/
      if ( v499 >> 3 >= v535 ) /*0x179333*/
        v55 = *(unsigned __int8 *)(a1[3] + v54 - v535); /*0x179ab9*/
      else
        v55 = *(unsigned __int8 *)(a1[2] + v54); /*0x17933c*/
      v56 = (v55 >> v53) & 1; /*0x179346*/
      v500 = v499 + 1; /*0x179350*/
      a1[8] = v500; /*0x179358*/
      v576 = v500 & 7; /*0x17935e*/
      if ( (v500 & 7) == 0 ) /*0x179364*/
      {
        if ( v25 >= a1[6] + v535 ) /*0x179371*/
          goto LABEL_347; /*0x179371*/
        a1[8] = 8 * v25; /*0x17937e*/
        ++a1[7]; /*0x179381*/
        v500 = 8 * v25; /*0x179384*/
        v25 = a1[7]; /*0x17938a*/
      }
      v57 = v500 >> 3; /*0x179393*/
      if ( v500 >> 3 >= v535 ) /*0x17939c*/
        v58 = *(unsigned __int8 *)(a1[3] + v57 - v535); /*0x179d1b*/
      else
        v58 = *(unsigned __int8 *)(a1[2] + v57); /*0x1793a5*/
      v574 = 2 * ((v58 >> v576) & 1); /*0x1793b7*/
      v501 = v500 + 1; /*0x1793c4*/
      a1[8] = v501; /*0x1793cc*/
      v577 = v501 & 7; /*0x1793d2*/
      if ( (v501 & 7) == 0 ) /*0x1793d8*/
      {
        if ( v25 >= a1[6] + v535 ) /*0x1793e5*/
          goto LABEL_347; /*0x1793e5*/
        a1[8] = 8 * v25; /*0x1793f2*/
        ++a1[7]; /*0x1793f5*/
        v501 = 8 * v25; /*0x1793f8*/
        v25 = a1[7]; /*0x1793fe*/
      }
      v59 = v501 >> 3; /*0x179407*/
      if ( v501 >> 3 >= v535 ) /*0x179410*/
        v60 = *(unsigned __int8 *)(a1[3] + v59 - v535); /*0x179d2d*/
      else
        v60 = *(unsigned __int8 *)(a1[2] + v59); /*0x179419*/
      v575 = 4 * ((v60 >> v577) & 1); /*0x17942c*/
      v502 = v501 + 1; /*0x179439*/
      a1[8] = v502; /*0x179441*/
      v578 = v502 & 7; /*0x179447*/
      if ( (v502 & 7) == 0 ) /*0x17944d*/
      {
        if ( v25 >= a1[6] + v535 ) /*0x17945a*/
          goto LABEL_347; /*0x17945a*/
        a1[8] = 8 * v25; /*0x179467*/
        ++a1[7]; /*0x17946a*/
        v502 = 8 * v25; /*0x17946d*/
        v25 = a1[7]; /*0x179473*/
      }
      v61 = v502 >> 3; /*0x17947c*/
      if ( v502 >> 3 >= v535 ) /*0x179485*/
        v62 = *(unsigned __int8 *)(a1[3] + v61 - v535); /*0x179d47*/
      else
        v62 = *(unsigned __int8 *)(a1[2] + v61); /*0x17948e*/
      v573 = (8 * ((v62 >> v578) & 1)) | v575 | v574 | v56; /*0x1794b9*/
      v503 = v502 + 1; /*0x1794c6*/
      a1[8] = v503; /*0x1794cc*/
      v63 = v503 & 7; /*0x1794d1*/
      if ( (v503 & 7) == 0 ) /*0x1794d4*/
      {
        if ( v25 >= a1[6] + v535 ) /*0x1794e1*/
          goto LABEL_347; /*0x1794e1*/
        a1[8] = 8 * v25; /*0x1794ee*/
        ++a1[7]; /*0x1794f1*/
        v503 = 8 * v25; /*0x1794f4*/
        v25 = a1[7]; /*0x1794fa*/
      }
      v64 = v503 >> 3; /*0x179503*/
      if ( v503 >> 3 < v535 ) /*0x17950c*/
        v65 = *(unsigned __int8 *)(a1[2] + v64); /*0x179faf*/
      else
        v65 = *(unsigned __int8 *)(a1[3] + v64 - v535); /*0x17951b*/
      v66 = v573 | (16 * ((v65 >> v63) & 1)); /*0x17952b*/
      a1[8] = v503 + 1; /*0x179538*/
LABEL_110:
      if ( v25 >= a1[6] + v535 ) /*0x179546*/
      {
        *a1 = 1; /*0x179d02*/
        v68 = -32; /*0x179d08*/
      }
      else
      {
        if ( v25 < v535 ) /*0x179552*/
          v67 = *(unsigned __int8 *)(a1[2] + v25); /*0x179fef*/
        else
          v67 = *(unsigned __int8 *)(a1[3] + v25 - v535); /*0x179563*/
        a1[7] = v25 + 1; /*0x17956a*/
        v68 = 32 * v67; /*0x17956f*/
      }
      result = (((int)*(float *)v551 + 4096) ^ (v66 + v68)) - 4096; /*0x179586*/
LABEL_115:
      *(float *)v552 = (float)result; /*0x17958b*/
      if ( a6 ) /*0x17959e*/
        return Com_Printf(16, "%s:%i ", *a5, result); /*0x1795c0*/
      return result; /*0x1795c5*/
    }
LABEL_51:
    if ( v25 + 4 <= a1[6] + v535 ) /*0x179109*/
    {
      if ( v25 >= v535 ) /*0x179118*/
        v28 = *(_BYTE *)(a1[3] + v25 - v535); /*0x179b37*/
      else
        v28 = *(_BYTE *)(a1[2] + v25); /*0x179121*/
      LOBYTE(v611) = v28; /*0x179125*/
      v29 = v25 + 1; /*0x179127*/
      if ( v25 + 1 >= v535 ) /*0x179130*/
        v30 = *(_BYTE *)(a1[3] + v29 - v535); /*0x179fe3*/
      else
        v30 = *(_BYTE *)(a1[2] + v29); /*0x179139*/
      BYTE1(v611) = v30; /*0x17913d*/
      v31 = v25 + 2; /*0x179140*/
      if ( v25 + 2 >= v535 ) /*0x179147*/
        v32 = *(_BYTE *)(a1[3] + v31 - v535); /*0x179fcf*/
      else
        v32 = *(_BYTE *)(a1[2] + v31); /*0x179150*/
      BYTE2(v611) = v32; /*0x179154*/
      v33 = v25 + 3; /*0x179157*/
      if ( v25 + 3 < v535 ) /*0x179160*/
        v34 = *(_BYTE *)(a1[2] + v33); /*0x179fbb*/
      else
        v34 = *(_BYTE *)(a1[3] + v33 - v535); /*0x17916f*/
      HIBYTE(v611) = v34; /*0x179173*/
      a1[7] = v25 + 4; /*0x17917c*/
      v35 = v611; /*0x17917f*/
LABEL_133:
      *v552 = v35; /*0x1796bb*/
      result = *v551 ^ v35; /*0x1796c9*/
      *v552 = result; /*0x1796cb*/
      if ( a6 ) /*0x1796d2*/
      {
        v79 = *(float *)v552; /*0x1796d8*/
        return Com_Printf(16, "%s:%f ", *a5, v79); /*0x1796d8*/
      }
      return result; /*0x1796d2*/
    }
LABEL_132:
    *a1 = 1; /*0x1796b0*/
    v35 = -1; /*0x1796b6*/
    goto LABEL_133; /*0x1796b6*/
  }
  if ( v14 == (const char *)-89 ) /*0x178f11*/
  {
    v69 = a1[8]; /*0x1795f0*/
    v70 = v69 & 7; /*0x1795f5*/
    if ( (v69 & 7) != 0 ) /*0x1795f8*/
    {
      v535 = a1[5]; /*0x179883*/
    }
    else
    {
      v71 = a1[7]; /*0x1795fe*/
      v535 = a1[5]; /*0x179604*/
      if ( v71 >= a1[6] + v535 ) /*0x17960f*/
      {
        *a1 = 1; /*0x179615*/
        goto LABEL_122; /*0x179615*/
      }
      a1[8] = 8 * v71; /*0x179b88*/
      ++a1[7]; /*0x179b8b*/
      v69 = 8 * v71; /*0x179b8e*/
    }
    v96 = v69 >> 3; /*0x17988b*/
    if ( v69 >> 3 >= v535 ) /*0x179894*/
      v97 = *(unsigned __int8 *)(a1[3] + v96 - v535); /*0x179acb*/
    else
      v97 = *(unsigned __int8 *)(a1[2] + v96); /*0x17989d*/
    v98 = v69 + 1; /*0x1798a1*/
    a1[8] = v69 + 1; /*0x1798a4*/
    if ( ((v97 >> v70) & 1) != 0 ) /*0x1798ad*/
    {
      v71 = a1[7]; /*0x179d36*/
LABEL_122:
      if ( v71 + 4 <= a1[6] + v535 ) /*0x179633*/
      {
        if ( v71 >= v535 ) /*0x17963e*/
          v72 = *(_BYTE *)(a1[3] + v71 - v535); /*0x17a540*/
        else
          v72 = *(_BYTE *)(a1[2] + v71); /*0x179647*/
        LOBYTE(v613) = v72; /*0x17964b*/
        v73 = v71 + 1; /*0x17964d*/
        if ( v71 + 1 >= v535 ) /*0x179656*/
          v74 = *(_BYTE *)(a1[3] + v73 - v535); /*0x17a52c*/
        else
          v74 = *(_BYTE *)(a1[2] + v73); /*0x17965f*/
        BYTE1(v613) = v74; /*0x179663*/
        v75 = v71 + 2; /*0x179666*/
        if ( v71 + 2 >= v535 ) /*0x17966d*/
          v76 = *(_BYTE *)(a1[3] + v75 - v535); /*0x17a518*/
        else
          v76 = *(_BYTE *)(a1[2] + v75); /*0x179676*/
        BYTE2(v613) = v76; /*0x17967a*/
        v77 = v71 + 3; /*0x17967d*/
        if ( v71 + 3 < v535 ) /*0x179686*/
          v78 = *(_BYTE *)(a1[2] + v77); /*0x17a504*/
        else
          v78 = *(_BYTE *)(a1[3] + v77 - v535); /*0x179695*/
        HIBYTE(v613) = v78; /*0x179699*/
        a1[7] = v71 + 4; /*0x1796a2*/
        v35 = v613; /*0x1796a5*/
        goto LABEL_133; /*0x1796a8*/
      }
      goto LABEL_132; /*0x179633*/
    }
    v99 = v98 & 7; /*0x1798b5*/
    if ( (v98 & 7) == 0 ) /*0x1798b8*/
    {
      v25 = a1[7]; /*0x1798ba*/
      if ( v25 >= a1[6] + v535 ) /*0x1798c8*/
        goto LABEL_347; /*0x1798c8*/
      a1[8] = 8 * v25; /*0x1798d5*/
      ++a1[7]; /*0x1798d8*/
      v98 = 8 * v25; /*0x1798db*/
    }
    v100 = v98 >> 3; /*0x1798df*/
    if ( v98 >> 3 >= v535 ) /*0x1798e8*/
      v101 = *(unsigned __int8 *)(a1[3] + v100 - v535); /*0x17a3b5*/
    else
      v101 = *(unsigned __int8 *)(a1[2] + v100); /*0x1798f1*/
    v102 = (v101 >> v99) & 1; /*0x1798fb*/
    v103 = v98 + 1; /*0x1798fe*/
    a1[8] = v103; /*0x179901*/
    v581 = v103 & 7; /*0x179907*/
    if ( (v103 & 7) == 0 ) /*0x17990d*/
    {
      v25 = a1[7]; /*0x17990f*/
      if ( v25 >= a1[6] + v535 ) /*0x17991d*/
        goto LABEL_347; /*0x17991d*/
      a1[8] = 8 * v25; /*0x17992a*/
      ++a1[7]; /*0x17992d*/
      v103 = 8 * v25; /*0x179930*/
    }
    v104 = v103 >> 3; /*0x179934*/
    if ( v103 >> 3 >= v535 ) /*0x17993d*/
      v105 = *(unsigned __int8 *)(a1[3] + v104 - v535); /*0x17a480*/
    else
      v105 = *(unsigned __int8 *)(a1[2] + v104); /*0x179946*/
    v579 = 2 * ((v105 >> v581) & 1); /*0x179958*/
    v106 = v103 + 1; /*0x17995e*/
    a1[8] = v106; /*0x179961*/
    v582 = v106 & 7; /*0x179967*/
    if ( (v106 & 7) == 0 ) /*0x17996d*/
    {
      v25 = a1[7]; /*0x17996f*/
      if ( v25 >= a1[6] + v535 ) /*0x17997d*/
        goto LABEL_347; /*0x17997d*/
      a1[8] = 8 * v25; /*0x17998a*/
      ++a1[7]; /*0x17998d*/
      v106 = 8 * v25; /*0x179990*/
    }
    v107 = v106 >> 3; /*0x179994*/
    if ( v106 >> 3 >= v535 ) /*0x17999d*/
      v108 = *(unsigned __int8 *)(a1[3] + v107 - v535); /*0x17a4da*/
    else
      v108 = *(unsigned __int8 *)(a1[2] + v107); /*0x1799a6*/
    v580 = 4 * ((v108 >> v582) & 1); /*0x1799b9*/
    v109 = v106 + 1; /*0x1799bf*/
    a1[8] = v109; /*0x1799c2*/
    v583 = v109 & 7; /*0x1799c8*/
    if ( (v109 & 7) == 0 ) /*0x1799ce*/
    {
      v25 = a1[7]; /*0x1799d0*/
      if ( v25 >= a1[6] + v535 ) /*0x1799de*/
        goto LABEL_347; /*0x1799de*/
      a1[8] = 8 * v25; /*0x1799eb*/
      ++a1[7]; /*0x1799ee*/
      v109 = 8 * v25; /*0x1799f1*/
    }
    v110 = v109 >> 3; /*0x1799f5*/
    if ( v109 >> 3 >= v535 ) /*0x1799fe*/
      v111 = *(unsigned __int8 *)(a1[3] + v110 - v535); /*0x17a4ec*/
    else
      v111 = *(unsigned __int8 *)(a1[2] + v110); /*0x179a07*/
    v572 = (8 * ((v111 >> v583) & 1)) | v580 | v579 | v102; /*0x179a32*/
    v112 = v109 + 1; /*0x179a38*/
    a1[8] = v112; /*0x179a39*/
    v113 = v112 & 7; /*0x179a3e*/
    if ( (v112 & 7) != 0 ) /*0x179a41*/
      goto LABEL_188; /*0x179a41*/
    v25 = a1[7]; /*0x179a43*/
    if ( v25 < a1[6] + v535 ) /*0x179a51*/
    {
      a1[8] = 8 * v25; /*0x179a5e*/
      ++a1[7]; /*0x179a61*/
      v112 = 8 * v25; /*0x179a64*/
LABEL_188:
      v114 = v112 >> 3; /*0x179a66*/
      if ( v112 >> 3 < v535 ) /*0x179a71*/
        v115 = *(unsigned __int8 *)(a1[2] + v114); /*0x17a4f8*/
      else
        v115 = *(unsigned __int8 *)(a1[3] + v114 - v535); /*0x179a80*/
      v66 = v572 | (16 * ((v115 >> v113) & 1)); /*0x179a90*/
      a1[8] = v112 + 1; /*0x179a99*/
      v25 = a1[7]; /*0x179a9c*/
      goto LABEL_110; /*0x179a9f*/
    }
LABEL_347:
    *a1 = 1; /*0x17a55b*/
    v66 = -1; /*0x17a561*/
    goto LABEL_110; /*0x17a566*/
  }
  if ( v14 != (const char *)-88 ) /*0x178f1a*/
  {
    if ( v14 != (const char *)-99 ) /*0x178f23*/
    {
      if ( v14 != (const char *)-98 ) /*0x178f2c*/
      {
        if ( v14 != (const char *)-97 ) /*0x178f35*/
        {
          if ( v14 != (const char *)-96 ) /*0x178f3e*/
          {
            if ( v14 == (const char *)-94 || v14 == (const char *)-93 ) /*0x178f50*/
            {
              v189 = a1[7]; /*0x17a31d*/
              v190 = a1[5]; /*0x17a320*/
              if ( v189 >= a1[6] + v190 ) /*0x17a32a*/
              {
                *a1 = 1; /*0x17a8df*/
                v191 = -1; /*0x17a8e5*/
              }
              else
              {
                if ( v189 < v190 ) /*0x17a332*/
                  v191 = *(unsigned __int8 *)(a1[2] + v189); /*0x17accc*/
                else
                  v191 = *(unsigned __int8 *)(a1[3] + v189 - v190); /*0x17a33f*/
                a1[7] = v189 + 1; /*0x17a346*/
              }
              result = (int)v552; /*0x17a349*/
              *v552 = v191; /*0x17a34f*/
              return result; /*0x17a351*/
            }
            if ( v14 != (const char *)-95 ) /*0x178f59*/
            {
              if ( (unsigned int)(v14 + 92) > 1 ) /*0x178f65*/
              {
                if ( v14 != (const char *)-90 ) /*0x178f6e*/
                {
                  if ( v14 != (const char *)-100 ) /*0x178f77*/
                  {
                    if ( v14 != (const char *)-87 ) /*0x178f80*/
                    {
                      if ( v14 != (const char *)-86 ) /*0x178f89*/
                      {
                        if ( v14 != (const char *)-85 ) /*0x178f92*/
                        {
                          v15 = a1[8]; /*0x178f98*/
                          v16 = v15 & 7; /*0x178f9d*/
                          if ( (v15 & 7) != 0 ) /*0x178fa0*/
                          {
                            v534 = a1[5]; /*0x17a359*/
                          }
                          else
                          {
                            v17 = a1[7]; /*0x178fa6*/
                            v534 = a1[5]; /*0x178fac*/
                            if ( v17 >= a1[6] + v534 ) /*0x178fb9*/
                            {
                              *a1 = 1; /*0x178fbf*/
LABEL_32:
                              v554 = (int)a5[2]; /*0x178fc5*/
                              v553 = (unsigned int)v554 >> 31; /*0x178fd4*/
                              v18 = -v554; /*0x178fe0*/
                              if ( v554 >= 0 ) /*0x178fe4*/
                                v18 = (int)a5[2]; /*0x178fe4*/
                              v555 = v18; /*0x178feb*/
                              v556 = v18 & 7; /*0x178ff4*/
                              if ( (v18 & 7) != 0 ) /*0x178ffa*/
                              {
                                v557 = 0; /*0x17bbd3*/
                                v529 = 0; /*0x17bbdd*/
                                while ( 1 ) /*0x17bc2a*/
                                {
                                  v446 = a1[8]; /*0x17bc2a*/
                                  v447 = v446 & 7; /*0x17bc2f*/
                                  if ( (v446 & 7) == 0 ) /*0x17bc32*/
                                  {
                                    v448 = a1[7]; /*0x17bc34*/
                                    if ( v448 >= a1[6] + v534 ) /*0x17bc42*/
                                    {
                                      *a1 = 1; /*0x17c1a1*/
                                      v557 = -1; /*0x17c1a7*/
                                      goto LABEL_36; /*0x17c1b1*/
                                    }
                                    v449 = 8 * v448; /*0x17bc48*/
                                    a1[8] = v449; /*0x17bc4b*/
                                    ++a1[7]; /*0x17bc4e*/
                                    v446 = v449; /*0x17bc51*/
                                  }
                                  v450 = v446 >> 3; /*0x17bc55*/
                                  if ( v446 >> 3 >= v534 ) /*0x17bc5e*/
                                    v445 = *(unsigned __int8 *)(a1[3] + v450 - v534); /*0x17bbf2*/
                                  else
                                    v445 = *(unsigned __int8 *)(a1[2] + v450); /*0x17bc63*/
                                  v557 |= ((v445 >> v447) & 1) << v529; /*0x17bc06*/
                                  a1[8] = v446 + 1; /*0x17bc0f*/
                                  if ( ++v529 == v556 ) /*0x17bc24*/
                                    goto LABEL_36; /*0x17bc24*/
                                }
                              }
                              v557 = 0; /*0x179000*/
LABEL_36:
                              if ( v555 <= v556 ) /*0x179016*/
                                goto LABEL_634; /*0x179016*/
                              v19 = v556; /*0x17901c*/
                              do /*0x179052*/
                              {
                                v21 = a1[7]; /*0x179058*/
                                if ( v21 < a1[6] + v534 ) /*0x179066*/
                                {
                                  if ( v21 < v534 ) /*0x179026*/
                                    v20 = *(unsigned __int8 *)(a1[2] + v21); /*0x17b0a3*/
                                  else
                                    v20 = *(unsigned __int8 *)(a1[3] + v21 - v534); /*0x179037*/
                                  a1[7] = v21 + 1; /*0x17903e*/
                                }
                                else
                                {
                                  *a1 = 1; /*0x179068*/
                                  v20 = -1; /*0x17906e*/
                                }
                                v557 |= v20 << v19; /*0x179043*/
                                v19 += 8; /*0x179049*/
                              }
                              while ( v555 > v19 ); /*0x179052*/
                              v409 = -1; /*0x17b882*/
                              if ( v555 != 32 ) /*0x17b88e*/
LABEL_634:
                                v409 = (1 << v555) - 1; /*0x17b89e*/
                              v410 = v557 ^ *v551 & v409; /*0x17b8ab*/
                              if ( v553 && ((v410 >> (v555 - 1)) & 1) != 0 ) /*0x17b8c8*/
                                v410 |= ~v409; /*0x17b8cc*/
                              if ( a6 ) /*0x17b8d3*/
                                Com_Printf(16, "%s:%i ", *a5, *v552); /*0x17c08d*/
                              result = (int)v552; /*0x17b8d9*/
                              *v552 = v410; /*0x17b8df*/
                              return result; /*0x17b8e1*/
                            }
                            v451 = 8 * v17; /*0x17bd67*/
                            a1[8] = v451; /*0x17bd6a*/
                            ++a1[7]; /*0x17bd6d*/
                            v15 = v451; /*0x17bd70*/
                          }
                          v192 = v15 >> 3; /*0x17a361*/
                          if ( v15 >> 3 < v534 ) /*0x17a36a*/
                            v193 = *(unsigned __int8 *)(a1[2] + v192); /*0x17bbca*/
                          else
                            v193 = *(unsigned __int8 *)(a1[3] + v192 - v534); /*0x17a379*/
                          a1[8] = v15 + 1; /*0x17a380*/
                          if ( ((v193 >> v16) & 1) != 0 ) /*0x17a389*/
                            goto LABEL_32; /*0x17a389*/
LABEL_318:
                          result = (int)v552; /*0x17a38f*/
                          *v552 = 0; /*0x17a395*/
                          return result; /*0x17a39b*/
                        }
                        v442 = a1[8]; /*0x17bb60*/
                        v443 = v442 & 7; /*0x17bb65*/
                        if ( (v442 & 7) != 0 ) /*0x17bb68*/
                        {
                          v549 = a1[5]; /*0x17be06*/
                        }
                        else
                        {
                          v444 = a1[7]; /*0x17bb6e*/
                          v549 = a1[5]; /*0x17bb74*/
                          if ( v444 >= a1[6] + v549 ) /*0x17bb81*/
                          {
                            *a1 = 1; /*0x17bb87*/
LABEL_681:
                            *v552 = *v551; /*0x17bb8d*/
                            result = -(*((_BYTE *)v551 + 3) == 0); /*0x17bba1*/
                            *((_BYTE *)v552 + 3) = result; /*0x17bba3*/
                            return result; /*0x17bba6*/
                          }
                          v498 = 8 * v444; /*0x17c1ef*/
                          a1[8] = v498; /*0x17c1f2*/
                          ++a1[7]; /*0x17c1f5*/
                          v442 = v498; /*0x17c1f8*/
                        }
                        v452 = v442 >> 3; /*0x17be0e*/
                        if ( v442 >> 3 < v549 ) /*0x17be17*/
                          v453 = *(unsigned __int8 *)(a1[2] + v452); /*0x17c09a*/
                        else
                          v453 = *(unsigned __int8 *)(a1[3] + v452 - v549); /*0x17be26*/
                        v454 = v442 + 1; /*0x17be2a*/
                        a1[8] = v442 + 1; /*0x17be2d*/
                        if ( ((v453 >> v443) & 1) != 0 ) /*0x17be36*/
                          goto LABEL_681; /*0x17be36*/
                        v455 = v454 & 7; /*0x17be3e*/
                        if ( (v454 & 7) == 0 ) /*0x17be41*/
                        {
                          v456 = a1[7]; /*0x17be47*/
                          if ( v456 >= a1[6] + v549 ) /*0x17be55*/
                          {
                            *a1 = 1; /*0x17be5b*/
                            goto LABEL_724; /*0x17be5b*/
                          }
                          a1[8] = 8 * v456; /*0x17c0a6*/
                          ++a1[7]; /*0x17c0a9*/
                        }
                        v485 = (int)a1[8] >> 3; /*0x17c0b1*/
                        if ( v485 < v549 ) /*0x17c0ba*/
                          v486 = *(unsigned __int8 *)(a1[2] + v485); /*0x17c26a*/
                        else
                          v486 = *(unsigned __int8 *)(a1[3] + v485 - v549); /*0x17c0c9*/
                        ++a1[8]; /*0x17c0d0*/
                        if ( ((v486 >> v455) & 1) == 0 ) /*0x17c0d9*/
                        {
                          v487 = a1[7]; /*0x17c0df*/
                          if ( v487 >= a1[6] + v549 ) /*0x17c0ed*/
                          {
                            *a1 = 1; /*0x17c257*/
                            v489 = -1; /*0x17c25d*/
                          }
                          else
                          {
                            if ( v487 < v549 ) /*0x17c0f9*/
                              v488 = *(_BYTE *)(a1[2] + v487); /*0x17c2ae*/
                            else
                              v488 = *(_BYTE *)(a1[3] + v487 - v549); /*0x17c10a*/
                            a1[7] = v487 + 1; /*0x17c111*/
                            v489 = v488; /*0x17c114*/
                          }
                          *(_BYTE *)v552 = v489; /*0x17c11c*/
                          v490 = a1[7]; /*0x17c11e*/
                          v491 = a1[5]; /*0x17c121*/
                          if ( v490 >= a1[6] + v491 ) /*0x17c12b*/
                          {
                            *a1 = 1; /*0x17c247*/
                            v493 = -1; /*0x17c24d*/
                          }
                          else
                          {
                            if ( v490 < v491 ) /*0x17c133*/
                              v492 = *(_BYTE *)(a1[2] + v490); /*0x17c286*/
                            else
                              v492 = *(_BYTE *)(a1[3] + v490 - v491); /*0x17c142*/
                            a1[7] = v490 + 1; /*0x17c149*/
                            v493 = v492; /*0x17c14c*/
                          }
                          *((_BYTE *)v552 + 1) = v493; /*0x17c154*/
                          v494 = a1[7]; /*0x17c157*/
                          v495 = a1[5]; /*0x17c15a*/
                          if ( v494 >= a1[6] + v495 ) /*0x17c164*/
                          {
                            *a1 = 1; /*0x17c273*/
                            v497 = -1; /*0x17c279*/
                          }
                          else
                          {
                            if ( v494 < v495 ) /*0x17c16c*/
                              v496 = *(_BYTE *)(a1[2] + v494); /*0x17c2a2*/
                            else
                              v496 = *(_BYTE *)(a1[3] + v494 - v495); /*0x17c17b*/
                            a1[7] = v494 + 1; /*0x17c182*/
                            v497 = v496; /*0x17c185*/
                          }
                          *((_BYTE *)v552 + 2) = v497; /*0x17c18d*/
                        }
LABEL_724:
                        v457 = a1[8]; /*0x17be61*/
                        v458 = v457 & 7; /*0x17be66*/
                        if ( (v457 & 7) == 0 ) /*0x17be69*/
                        {
                          v459 = a1[7]; /*0x17be6b*/
                          if ( a1[5] + a1[6] <= v459 ) /*0x17be76*/
                            goto LABEL_786; /*0x17be76*/
                          v460 = 8 * v459; /*0x17be7c*/
                          a1[8] = v460; /*0x17be7f*/
                          ++a1[7]; /*0x17be82*/
                          v457 = v460; /*0x17be85*/
                        }
                        v461 = v457 >> 3; /*0x17be89*/
                        v550 = a1[5]; /*0x17be8f*/
                        if ( v550 <= v457 >> 3 ) /*0x17be97*/
                          v462 = *(unsigned __int8 *)(a1[3] + v461 - v550); /*0x17c23e*/
                        else
                          v462 = *(unsigned __int8 *)(a1[2] + v461); /*0x17bea0*/
                        v463 = (v462 >> v458) & 1; /*0x17beaa*/
                        v530 = v457 + 1; /*0x17beae*/
                        a1[8] = v457 + 1; /*0x17beb4*/
                        v464 = (v457 + 1) & 7; /*0x17beb7*/
                        if ( !v464 ) /*0x17beba*/
                        {
                          v465 = a1[7]; /*0x17bebc*/
                          if ( a1[5] + a1[6] <= v465 ) /*0x17bec7*/
                            goto LABEL_786; /*0x17bec7*/
                          v466 = 8 * v465; /*0x17becd*/
                          a1[8] = v466; /*0x17bed0*/
                          ++a1[7]; /*0x17bed3*/
                          v530 = v466; /*0x17bed6*/
                        }
                        v467 = v530 >> 3; /*0x17bee2*/
                        if ( v550 <= v530 >> 3 ) /*0x17beeb*/
                          v468 = *(unsigned __int8 *)(a1[3] + v467 - v550); /*0x17c22c*/
                        else
                          v468 = *(unsigned __int8 *)(a1[2] + v467); /*0x17bef4*/
                        v608 = 2 * ((v468 >> v464) & 1); /*0x17bf01*/
                        v531 = v530 + 1; /*0x17bf0b*/
                        a1[8] = v531; /*0x17bf11*/
                        v469 = v531 & 7; /*0x17bf16*/
                        if ( (v531 & 7) == 0 ) /*0x17bf19*/
                        {
                          v470 = a1[7]; /*0x17bf1b*/
                          if ( a1[5] + a1[6] <= v470 ) /*0x17bf26*/
                            goto LABEL_786; /*0x17bf26*/
                          v471 = 8 * v470; /*0x17bf2c*/
                          a1[8] = v471; /*0x17bf2f*/
                          ++a1[7]; /*0x17bf32*/
                          v531 = v471; /*0x17bf35*/
                        }
                        v472 = v531 >> 3; /*0x17bf41*/
                        if ( v550 <= v531 >> 3 ) /*0x17bf4a*/
                          v473 = *(unsigned __int8 *)(a1[3] + v472 - v550); /*0x17c21a*/
                        else
                          v473 = *(unsigned __int8 *)(a1[2] + v472); /*0x17bf53*/
                        v474 = 4 * ((v473 >> v469) & 1); /*0x17bf5e*/
                        v532 = v531 + 1; /*0x17bf6c*/
                        a1[8] = v532; /*0x17bf74*/
                        v570 = v532 & 7; /*0x17bf7a*/
                        if ( (v532 & 7) == 0 ) /*0x17bf80*/
                        {
                          v475 = a1[7]; /*0x17bf82*/
                          if ( a1[5] + a1[6] <= v475 ) /*0x17bf8d*/
                            goto LABEL_786; /*0x17bf8d*/
                          v476 = 8 * v475; /*0x17bf93*/
                          a1[8] = v476; /*0x17bf96*/
                          ++a1[7]; /*0x17bf99*/
                          v532 = v476; /*0x17bf9c*/
                        }
                        v477 = v532 >> 3; /*0x17bfa8*/
                        if ( v550 <= v532 >> 3 ) /*0x17bfb1*/
                          v478 = *(unsigned __int8 *)(a1[3] + v477 - v550); /*0x17c208*/
                        else
                          v478 = *(unsigned __int8 *)(a1[2] + v477); /*0x17bfba*/
                        v479 = (8 * ((v478 >> v570) & 1)) | v474 | v608 | v463; /*0x17bfd2*/
                        v480 = v532 + 1; /*0x17bfda*/
                        a1[8] = v532 + 1; /*0x17bfdb*/
                        if ( (((_BYTE)v532 + 1) & 7) != 0 ) /*0x17bfe3*/
                          goto LABEL_747; /*0x17bfe3*/
                        v481 = a1[7]; /*0x17bfe5*/
                        if ( v481 < a1[6] + v550 ) /*0x17bff3*/
                        {
                          v482 = 8 * v481; /*0x17bff9*/
                          a1[8] = v482; /*0x17bffc*/
                          ++a1[7]; /*0x17bfff*/
                          v480 = v482; /*0x17c002*/
LABEL_747:
                          v483 = v480 >> 3; /*0x17c004*/
                          if ( v480 >> 3 < v550 ) /*0x17c00f*/
                            v484 = *(unsigned __int8 *)(a1[2] + v483); /*0x17c198*/
                          else
                            v484 = *(unsigned __int8 *)(a1[3] + v483 - v550); /*0x17c01e*/
                          a1[8] = v480 + 1; /*0x17c025*/
                          result = 8 * ((16 * ((v484 >> ((v532 + 1) & 7)) & 1)) | v479); /*0x17c034*/
                          goto LABEL_750; /*0x17c034*/
                        }
LABEL_786:
                        *a1 = 1; /*0x17c28f*/
                        result = -8; /*0x17c295*/
LABEL_750:
                        *((_BYTE *)v552 + 3) = result; /*0x17c03b*/
                        return result; /*0x17c044*/
                      }
                      v411 = a1[8]; /*0x17b8e6*/
                      v412 = v411 & 7; /*0x17b8eb*/
                      if ( (v411 & 7) == 0 ) /*0x17b8ee*/
                      {
                        v413 = a1[7]; /*0x17b8f0*/
                        if ( a1[5] + a1[6] <= v413 ) /*0x17b8fb*/
                          goto LABEL_774; /*0x17b8fb*/
                        v414 = 8 * v413; /*0x17b901*/
                        a1[8] = v414; /*0x17b904*/
                        ++a1[7]; /*0x17b907*/
                        v411 = v414; /*0x17b90a*/
                      }
                      v415 = v411 >> 3; /*0x17b90e*/
                      v548 = a1[5]; /*0x17b914*/
                      if ( v548 <= v411 >> 3 ) /*0x17b91c*/
                        v416 = *(unsigned __int8 *)(a1[3] + v415 - v548); /*0x17bc84*/
                      else
                        v416 = *(unsigned __int8 *)(a1[2] + v415); /*0x17b925*/
                      v417 = (v416 >> v412) & 1; /*0x17b92f*/
                      v526 = v411 + 1; /*0x17b933*/
                      a1[8] = v411 + 1; /*0x17b939*/
                      v418 = (v411 + 1) & 7; /*0x17b93c*/
                      if ( !v418 ) /*0x17b93f*/
                      {
                        v419 = a1[7]; /*0x17b941*/
                        if ( a1[5] + a1[6] <= v419 ) /*0x17b94c*/
                          goto LABEL_774; /*0x17b94c*/
                        v420 = 8 * v419; /*0x17b952*/
                        a1[8] = v420; /*0x17b955*/
                        ++a1[7]; /*0x17b958*/
                        v526 = v420; /*0x17b95b*/
                      }
                      v421 = v526 >> 3; /*0x17b967*/
                      if ( v548 <= v526 >> 3 ) /*0x17b970*/
                        v422 = *(unsigned __int8 *)(a1[3] + v421 - v548); /*0x17bc72*/
                      else
                        v422 = *(unsigned __int8 *)(a1[2] + v421); /*0x17b979*/
                      v609 = 2 * ((v422 >> v418) & 1); /*0x17b986*/
                      v527 = v526 + 1; /*0x17b990*/
                      a1[8] = v527; /*0x17b996*/
                      v423 = v527 & 7; /*0x17b99b*/
                      if ( (v527 & 7) == 0 ) /*0x17b99e*/
                      {
                        v424 = a1[7]; /*0x17b9a0*/
                        if ( a1[5] + a1[6] <= v424 ) /*0x17b9ab*/
                          goto LABEL_774; /*0x17b9ab*/
                        v425 = 8 * v424; /*0x17b9b1*/
                        a1[8] = v425; /*0x17b9b4*/
                        ++a1[7]; /*0x17b9b7*/
                        v527 = v425; /*0x17b9ba*/
                      }
                      v426 = v527 >> 3; /*0x17b9c6*/
                      if ( v548 <= v527 >> 3 ) /*0x17b9cf*/
                        v427 = *(unsigned __int8 *)(a1[3] + v426 - v548); /*0x17bd4c*/
                      else
                        v427 = *(unsigned __int8 *)(a1[2] + v426); /*0x17b9d8*/
                      v428 = 4 * ((v427 >> v423) & 1); /*0x17b9e3*/
                      v528 = v527 + 1; /*0x17b9f1*/
                      a1[8] = v528; /*0x17b9f9*/
                      v569 = v528 & 7; /*0x17b9ff*/
                      if ( (v528 & 7) == 0 ) /*0x17ba05*/
                      {
                        v429 = a1[7]; /*0x17ba07*/
                        if ( a1[5] + a1[6] <= v429 ) /*0x17ba12*/
                          goto LABEL_774; /*0x17ba12*/
                        v430 = 8 * v429; /*0x17ba18*/
                        a1[8] = v430; /*0x17ba1b*/
                        ++a1[7]; /*0x17ba1e*/
                        v528 = v430; /*0x17ba21*/
                      }
                      v431 = v528 >> 3; /*0x17ba2d*/
                      if ( v548 <= v528 >> 3 ) /*0x17ba36*/
                        v432 = *(unsigned __int8 *)(a1[3] + v431 - v548); /*0x17bd3a*/
                      else
                        v432 = *(unsigned __int8 *)(a1[2] + v431); /*0x17ba3f*/
                      v433 = (8 * ((v432 >> v569) & 1)) | v428 | v609 | v417; /*0x17ba57*/
                      v434 = v528 + 1; /*0x17ba5f*/
                      a1[8] = v528 + 1; /*0x17ba60*/
                      if ( (((_BYTE)v528 + 1) & 7) != 0 ) /*0x17ba68*/
                        goto LABEL_664; /*0x17ba68*/
                      v435 = a1[7]; /*0x17ba6a*/
                      if ( v435 < a1[6] + v548 ) /*0x17ba78*/
                      {
                        v436 = 8 * v435; /*0x17ba7e*/
                        a1[8] = v436; /*0x17ba81*/
                        ++a1[7]; /*0x17ba84*/
                        v434 = v436; /*0x17ba87*/
LABEL_664:
                        v437 = v434 >> 3; /*0x17ba89*/
                        if ( v434 >> 3 < v548 ) /*0x17ba94*/
                          v438 = *(unsigned __int8 *)(a1[2] + v437); /*0x17bd10*/
                        else
                          v438 = *(unsigned __int8 *)(a1[3] + v437 - v548); /*0x17baa3*/
                        a1[8] = v434 + 1; /*0x17baaa*/
                        v439 = (float)((float)((16 * ((v438 >> ((v528 + 1) & 7)) & 1)) | v433) / 10.0) + 1.4; /*0x17bac5*/
                        goto LABEL_667; /*0x17bac5*/
                      }
LABEL_774:
                      *a1 = 1; /*0x17c1c9*/
                      v439 = 1.3; /*0x17c1cf*/
LABEL_667:
                      result = (int)v552; /*0x17bacd*/
                      *(float *)v552 = v439; /*0x17bad3*/
                      return result; /*0x17bad7*/
                    }
                    v363 = a1[7]; /*0x17b530*/
                    v547 = a1[5]; /*0x17b539*/
                    result = a1[6] + v547; /*0x17b53f*/
                    if ( v363 + 2 <= result ) /*0x17b544*/
                    {
                      if ( v363 >= v547 ) /*0x17b54f*/
                        v364 = *(_BYTE *)(a1[3] + v363 - v547); /*0x17c060*/
                      else
                        v364 = *(_BYTE *)(a1[2] + v363); /*0x17b558*/
                      LOBYTE(v617) = v364; /*0x17b55c*/
                      v365 = v363 + 1; /*0x17b55e*/
                      if ( v547 > v363 + 1 ) /*0x17b567*/
                        v366 = *(_BYTE *)(a1[2] + v365); /*0x17c04c*/
                      else
                        v366 = *(_BYTE *)(a1[3] + v365 - v547); /*0x17b576*/
                      HIBYTE(v617) = v366; /*0x17b57a*/
                      result = v617; /*0x17b57d*/
                      a1[7] = v363 + 2; /*0x17b581*/
                      v319 = (float)v617 * 0.0054931641; /*0x17b588*/
                      goto LABEL_532; /*0x17b590*/
                    }
LABEL_589:
                    *a1 = 1; /*0x17b595*/
                    v319 = -0.0054931641; /*0x17b59b*/
LABEL_532:
                    *(float *)v552 = v319; /*0x17b1b5*/
                    return result; /*0x17b1bf*/
                  }
                  v313 = a1[8]; /*0x17b12a*/
                  v314 = v313 & 7; /*0x17b12f*/
                  if ( (v313 & 7) != 0 ) /*0x17b132*/
                  {
                    v546 = a1[5]; /*0x17badf*/
                  }
                  else
                  {
                    v315 = a1[7]; /*0x17b138*/
                    v546 = a1[5]; /*0x17b13e*/
                    if ( v315 >= a1[6] + v546 ) /*0x17b14b*/
                    {
                      *a1 = 1; /*0x17b151*/
                      goto LABEL_526; /*0x17b151*/
                    }
                    a1[8] = 8 * v315; /*0x17bd00*/
                    ++a1[7]; /*0x17bd03*/
                    v313 = 8 * v315; /*0x17bd06*/
                  }
                  v440 = v313 >> 3; /*0x17bae7*/
                  if ( v313 >> 3 < v546 ) /*0x17baf0*/
                    v441 = *(unsigned __int8 *)(a1[2] + v440); /*0x17bb4a*/
                  else
                    v441 = *(unsigned __int8 *)(a1[3] + v440 - v546); /*0x17bafb*/
                  a1[8] = v313 + 1; /*0x17bb02*/
                  if ( ((v441 >> v314) & 1) == 0 ) /*0x17bb0b*/
                  {
                    result = (int)v552; /*0x17bb0d*/
                    *v552 = 0; /*0x17bb13*/
                    return result; /*0x17bb19*/
                  }
                  v315 = a1[7]; /*0x17bb3f*/
LABEL_526:
                  result = a1[6] + v546; /*0x17b157*/
                  if ( v315 + 2 <= result ) /*0x17b165*/
                  {
                    if ( v315 >= v546 ) /*0x17b174*/
                      v316 = *(_BYTE *)(a1[3] + v315 - v546); /*0x17bdfa*/
                    else
                      v316 = *(_BYTE *)(a1[2] + v315); /*0x17b17d*/
                    LOBYTE(v616) = v316; /*0x17b181*/
                    v317 = v315 + 1; /*0x17b183*/
                    if ( v546 > v315 + 1 ) /*0x17b18c*/
                      v318 = *(_BYTE *)(a1[2] + v317); /*0x17bde6*/
                    else
                      v318 = *(_BYTE *)(a1[3] + v317 - v546); /*0x17b19b*/
                    HIBYTE(v616) = v318; /*0x17b19f*/
                    result = v616; /*0x17b1a2*/
                    a1[7] = v315 + 2; /*0x17b1a6*/
                    v319 = (float)v616 * 0.0054931641; /*0x17b1ad*/
                    goto LABEL_532; /*0x17b1ad*/
                  }
                  goto LABEL_589; /*0x17b165*/
                }
                v565 = *(float *)v551; /*0x17ae97*/
                v295 = a1[8]; /*0x17ae9f*/
                v296 = v295 & 7; /*0x17aea4*/
                if ( (v295 & 7) != 0 ) /*0x17aea7*/
                {
                  v542 = a1[5]; /*0x17b287*/
                }
                else
                {
                  v297 = a1[7]; /*0x17aead*/
                  v542 = a1[5]; /*0x17aeb3*/
                  if ( v297 >= a1[6] + v542 ) /*0x17aebe*/
                  {
                    *a1 = 1; /*0x17aec4*/
LABEL_492:
                    v566 = (int)(float)(*(float *)(CL_GetMapCenter() + 8) + 0.5); /*0x17aeca*/
                    v567 = 0; /*0x17aee6*/
                    v298 = 0; /*0x17aef0*/
                    v543 = a1[5]; /*0x17aef5*/
                    while ( 1 ) /*0x17af32*/
                    {
                      v519 = a1[8]; /*0x17af32*/
                      v300 = v519 & 7; /*0x17af3a*/
                      if ( (v519 & 7) == 0 ) /*0x17af3d*/
                      {
                        v301 = a1[7]; /*0x17af3f*/
                        if ( v301 >= a1[6] + v543 ) /*0x17af4d*/
                        {
                          *a1 = 1; /*0x17b1c4*/
                          v567 = -1; /*0x17b1ca*/
LABEL_534:
                          v79 = (float)((((int)v565 - v566 + 0x8000) ^ v567) + v566 - 0x8000); /*0x17b1d4*/
LABEL_535:
                          *(float *)v552 = v79; /*0x17b204*/
                          result = a6; /*0x17b20e*/
                          if ( a6 ) /*0x17b213*/
                            return Com_Printf(16, "%s:%f ", *a5, v79); /*0x1796dc*/
                          return result; /*0x17970d*/
                        }
                        v302 = 8 * v301; /*0x17af53*/
                        a1[8] = v302; /*0x17af56*/
                        ++a1[7]; /*0x17af59*/
                        v519 = v302; /*0x17af5c*/
                      }
                      v303 = v519 >> 3; /*0x17af68*/
                      if ( v519 >> 3 >= v543 ) /*0x17af71*/
                        v299 = *(unsigned __int8 *)(a1[3] + v303 - v543); /*0x17af06*/
                      else
                        v299 = *(unsigned __int8 *)(a1[2] + v303); /*0x17af76*/
                      v567 |= ((v299 >> v300) & 1) << v298; /*0x17af15*/
                      a1[8] = v519 + 1; /*0x17af22*/
                      if ( ++v298 == 16 ) /*0x17af29*/
                        goto LABEL_534; /*0x17af29*/
                    }
                  }
                  v295 = 8 * v297; /*0x17bbab*/
                  a1[8] = v295; /*0x17bbae*/
                  ++a1[7]; /*0x17bbb1*/
                }
                v320 = v295 >> 3; /*0x17b28f*/
                if ( v295 >> 3 < v542 ) /*0x17b298*/
                  v321 = *(unsigned __int8 *)(a1[2] + v320); /*0x17b879*/
                else
                  v321 = *(unsigned __int8 *)(a1[3] + v320 - v542); /*0x17b2a7*/
                v322 = v295 + 1; /*0x17b2ab*/
                a1[8] = v295 + 1; /*0x17b2ae*/
                if ( ((v321 >> v296) & 1) != 0 ) /*0x17b2b7*/
                  goto LABEL_492; /*0x17b2b7*/
                v323 = v322 & 7; /*0x17b2bf*/
                if ( (v322 & 7) == 0 ) /*0x17b2c2*/
                {
                  v324 = a1[7]; /*0x17b2c4*/
                  if ( a1[5] + a1[6] <= v324 ) /*0x17b2cf*/
                    goto LABEL_773; /*0x17b2cf*/
                  v325 = 8 * v324; /*0x17b2d5*/
                  a1[8] = v325; /*0x17b2d8*/
                  ++a1[7]; /*0x17b2db*/
                  v322 = v325; /*0x17b2de*/
                }
                v326 = v322 >> 3; /*0x17b2e2*/
                if ( v542 <= v322 >> 3 ) /*0x17b2eb*/
                  v327 = *(unsigned __int8 *)(a1[3] + v326 - v542); /*0x17bccc*/
                else
                  v327 = *(unsigned __int8 *)(a1[2] + v326); /*0x17b2f4*/
                v568 = (v327 >> v323) & 1; /*0x17b2ff*/
                v328 = v322 + 1; /*0x17b305*/
                a1[8] = v328; /*0x17b306*/
                v329 = v328 & 7; /*0x17b30b*/
                if ( (v328 & 7) == 0 ) /*0x17b30e*/
                {
                  v330 = a1[7]; /*0x17b310*/
                  if ( a1[5] + a1[6] <= v330 ) /*0x17b31b*/
                    goto LABEL_773; /*0x17b31b*/
                  v331 = 8 * v330; /*0x17b321*/
                  a1[8] = v331; /*0x17b324*/
                  ++a1[7]; /*0x17b327*/
                  v328 = v331; /*0x17b32a*/
                }
                v332 = v328 >> 3; /*0x17b32e*/
                if ( v542 <= v328 >> 3 ) /*0x17b337*/
                  v333 = *(unsigned __int8 *)(a1[3] + v332 - v542); /*0x17bcba*/
                else
                  v333 = *(unsigned __int8 *)(a1[2] + v332); /*0x17b340*/
                v605 = 2 * ((v333 >> v329) & 1); /*0x17b34d*/
                v334 = v328 + 1; /*0x17b350*/
                a1[8] = v334; /*0x17b351*/
                v335 = v334 & 7; /*0x17b356*/
                if ( (v334 & 7) == 0 ) /*0x17b359*/
                {
                  v336 = a1[7]; /*0x17b35b*/
                  if ( v336 >= a1[6] + v542 ) /*0x17b369*/
                    goto LABEL_773; /*0x17b369*/
                  v337 = 8 * v336; /*0x17b36f*/
                  a1[8] = v337; /*0x17b372*/
                  ++a1[7]; /*0x17b375*/
                  v334 = v337; /*0x17b378*/
                }
                v338 = v334 >> 3; /*0x17b37c*/
                if ( v334 >> 3 >= v542 ) /*0x17b385*/
                  v339 = *(unsigned __int8 *)(a1[3] + v338 - v542); /*0x17bca8*/
                else
                  v339 = *(unsigned __int8 *)(a1[2] + v338); /*0x17b38e*/
                v606 = 4 * ((v339 >> v335) & 1); /*0x17b39c*/
                v340 = v334 + 1; /*0x17b39f*/
                a1[8] = v340; /*0x17b3a0*/
                v341 = v340 & 7; /*0x17b3a5*/
                if ( (v340 & 7) == 0 ) /*0x17b3a8*/
                {
                  v342 = a1[7]; /*0x17b3aa*/
                  if ( v342 >= a1[6] + v542 ) /*0x17b3b8*/
                    goto LABEL_773; /*0x17b3b8*/
                  v343 = 8 * v342; /*0x17b3be*/
                  a1[8] = v343; /*0x17b3c1*/
                  ++a1[7]; /*0x17b3c4*/
                  v340 = v343; /*0x17b3c7*/
                }
                v344 = v340 >> 3; /*0x17b3cb*/
                if ( v340 >> 3 >= v542 ) /*0x17b3d4*/
                  v345 = *(unsigned __int8 *)(a1[3] + v344 - v542); /*0x17bc96*/
                else
                  v345 = *(unsigned __int8 *)(a1[2] + v344); /*0x17b3dd*/
                v607 = 8 * ((v345 >> v341) & 1); /*0x17b3eb*/
                v521 = v340 + 1; /*0x17b3ef*/
                a1[8] = v340 + 1; /*0x17b3f5*/
                if ( (((_BYTE)v340 + 1) & 7) == 0 ) /*0x17b3fd*/
                {
                  v346 = a1[7]; /*0x17b3ff*/
                  if ( v346 >= a1[6] + v542 ) /*0x17b40d*/
                    goto LABEL_773; /*0x17b40d*/
                  v347 = 8 * v346; /*0x17b413*/
                  a1[8] = v347; /*0x17b416*/
                  ++a1[7]; /*0x17b419*/
                  v521 = v347; /*0x17b41c*/
                }
                v348 = v521 >> 3; /*0x17b428*/
                if ( v521 >> 3 >= v542 ) /*0x17b431*/
                  v349 = *(unsigned __int8 *)(a1[3] + v348 - v542); /*0x17bcf0*/
                else
                  v349 = *(unsigned __int8 *)(a1[2] + v348); /*0x17b43a*/
                v350 = 16 * ((v349 >> ((v340 + 1) & 7)) & 1); /*0x17b447*/
                v351 = v521 + 1; /*0x17b450*/
                a1[8] = v521 + 1; /*0x17b453*/
                if ( (((_BYTE)v521 + 1) & 7) == 0 ) /*0x17b45c*/
                {
                  v352 = a1[7]; /*0x17b45e*/
                  if ( v352 >= a1[6] + v542 ) /*0x17b46c*/
                    goto LABEL_773; /*0x17b46c*/
                  v353 = 8 * v352; /*0x17b472*/
                  a1[8] = v353; /*0x17b475*/
                  ++a1[7]; /*0x17b478*/
                  v351 = v353; /*0x17b47b*/
                }
                v354 = v351 >> 3; /*0x17b47f*/
                if ( v351 >> 3 >= v542 ) /*0x17b488*/
                  v355 = *(unsigned __int8 *)(a1[3] + v354 - v542); /*0x17bcde*/
                else
                  v355 = *(unsigned __int8 *)(a1[2] + v354); /*0x17b491*/
                v522 = (32 * ((v355 >> ((v521 + 1) & 7)) & 1)) | v350 | v607 | v606 | v605 | v568; /*0x17b4b8*/
                v356 = v351 + 1; /*0x17b4be*/
                a1[8] = v356; /*0x17b4bf*/
                v357 = v356 & 7; /*0x17b4c4*/
                if ( (v356 & 7) != 0 ) /*0x17b4c7*/
                  goto LABEL_579; /*0x17b4c7*/
                v358 = a1[7]; /*0x17b4c9*/
                if ( v358 < a1[6] + v542 ) /*0x17b4d7*/
                {
                  v359 = 8 * v358; /*0x17b4dd*/
                  a1[8] = v359; /*0x17b4e0*/
                  ++a1[7]; /*0x17b4e3*/
                  v356 = v359; /*0x17b4e6*/
LABEL_579:
                  v360 = v356 >> 3; /*0x17b4e8*/
                  if ( v356 >> 3 < v542 ) /*0x17b4f3*/
                    v361 = *(unsigned __int8 *)(a1[2] + v360); /*0x17bd1c*/
                  else
                    v361 = *(unsigned __int8 *)(a1[3] + v360 - v542); /*0x17b502*/
                  a1[8] = v356 + 1; /*0x17b509*/
                  v362 = (float)((v522 | (((v361 >> v357) & 1) << 6)) - 64); /*0x17b51f*/
                  goto LABEL_582; /*0x17b51f*/
                }
LABEL_773:
                *a1 = 1; /*0x17c1b6*/
                v362 = -65.0; /*0x17c1bc*/
LABEL_582:
                v79 = v362 + v565; /*0x17b523*/
                goto LABEL_535; /*0x17b52b*/
              }
              v562 = *(float *)v551; /*0x17af94*/
              v304 = a1[8]; /*0x17af9c*/
              v305 = v304 & 7; /*0x17afa1*/
              if ( (v304 & 7) != 0 ) /*0x17afa4*/
              {
                v544 = a1[5]; /*0x17b5ab*/
              }
              else
              {
                v306 = a1[7]; /*0x17afaa*/
                v544 = a1[5]; /*0x17afb0*/
                if ( v306 >= a1[6] + v544 ) /*0x17afbb*/
                {
                  *a1 = 1; /*0x17afc1*/
LABEL_504:
                  v563 = (int)(float)(*(float *)(CL_GetMapCenter() + 4 * (v14 + 92 != 0)) + 0.5); /*0x17afc7*/
                  v564 = 0; /*0x17afeb*/
                  v307 = 0; /*0x17aff5*/
                  v545 = a1[5]; /*0x17affa*/
                  while ( 1 ) /*0x17b037*/
                  {
                    v520 = a1[8]; /*0x17b037*/
                    v309 = v520 & 7; /*0x17b03f*/
                    if ( (v520 & 7) == 0 ) /*0x17b042*/
                    {
                      v310 = a1[7]; /*0x17b044*/
                      if ( v310 >= a1[6] + v545 ) /*0x17b052*/
                      {
                        *a1 = 1; /*0x17b21e*/
                        v564 = -1; /*0x17b224*/
LABEL_538:
                        v79 = (float)((((int)v562 - v563 + 0x8000) ^ v564) + v563 - 0x8000); /*0x17b22e*/
                        goto LABEL_535; /*0x17b25e*/
                      }
                      v311 = 8 * v310; /*0x17b058*/
                      a1[8] = v311; /*0x17b05b*/
                      ++a1[7]; /*0x17b05e*/
                      v520 = v311; /*0x17b061*/
                    }
                    v312 = v520 >> 3; /*0x17b06d*/
                    if ( v520 >> 3 >= v545 ) /*0x17b076*/
                      v308 = *(unsigned __int8 *)(a1[3] + v312 - v545); /*0x17b00b*/
                    else
                      v308 = *(unsigned __int8 *)(a1[2] + v312); /*0x17b07b*/
                    v564 |= ((v308 >> v309) & 1) << v307; /*0x17b01a*/
                    a1[8] = v520 + 1; /*0x17b027*/
                    if ( ++v307 == 16 ) /*0x17b02e*/
                      goto LABEL_538; /*0x17b02e*/
                  }
                }
                v304 = 8 * v306; /*0x17bbb9*/
                a1[8] = v304; /*0x17bbbc*/
                ++a1[7]; /*0x17bbbf*/
              }
              v367 = v304 >> 3; /*0x17b5b3*/
              if ( v304 >> 3 < v544 ) /*0x17b5bc*/
                v368 = *(unsigned __int8 *)(a1[2] + v367); /*0x17bb21*/
              else
                v368 = *(unsigned __int8 *)(a1[3] + v367 - v544); /*0x17b5cb*/
              v369 = v304 + 1; /*0x17b5cf*/
              v523 = v369; /*0x17b5d0*/
              a1[8] = v369; /*0x17b5d6*/
              if ( ((v368 >> v305) & 1) != 0 ) /*0x17b5df*/
                goto LABEL_504; /*0x17b5df*/
              v370 = v369 & 7; /*0x17b5e7*/
              if ( (v369 & 7) == 0 ) /*0x17b5ea*/
              {
                v371 = a1[7]; /*0x17b5ec*/
                if ( v371 >= a1[6] + v544 ) /*0x17b5fa*/
                  goto LABEL_775; /*0x17b5fa*/
                v372 = 8 * v371; /*0x17b600*/
                a1[8] = v372; /*0x17b603*/
                ++a1[7]; /*0x17b606*/
                v523 = v372; /*0x17b609*/
              }
              v373 = v523 >> 3; /*0x17b615*/
              if ( v523 >> 3 >= v544 ) /*0x17b61e*/
                v374 = *(unsigned __int8 *)(a1[3] + v373 - v544); /*0x17bdda*/
              else
                v374 = *(unsigned __int8 *)(a1[2] + v373); /*0x17b627*/
              v604 = (v374 >> v370) & 1; /*0x17b632*/
              v375 = v523 + 1; /*0x17b63b*/
              a1[8] = v523 + 1; /*0x17b63c*/
              if ( (((_BYTE)v523 + 1) & 7) == 0 ) /*0x17b644*/
              {
                v376 = a1[7]; /*0x17b646*/
                if ( v376 >= a1[6] + v544 ) /*0x17b654*/
                  goto LABEL_775; /*0x17b654*/
                v377 = 8 * v376; /*0x17b65a*/
                a1[8] = v377; /*0x17b65d*/
                ++a1[7]; /*0x17b660*/
                v375 = v377; /*0x17b663*/
              }
              v378 = v375 >> 3; /*0x17b667*/
              if ( v375 >> 3 >= v544 ) /*0x17b670*/
                v379 = *(unsigned __int8 *)(a1[3] + v378 - v544); /*0x17bdc8*/
              else
                v379 = *(unsigned __int8 *)(a1[2] + v378); /*0x17b679*/
              v601 = 2 * ((v379 >> ((v523 + 1) & 7)) & 1); /*0x17b686*/
              v380 = v375 + 1; /*0x17b689*/
              a1[8] = v380; /*0x17b68a*/
              v381 = v380 & 7; /*0x17b68f*/
              if ( (v380 & 7) == 0 ) /*0x17b692*/
              {
                v382 = a1[7]; /*0x17b694*/
                if ( v382 >= a1[6] + v544 ) /*0x17b6a2*/
                  goto LABEL_775; /*0x17b6a2*/
                v383 = 8 * v382; /*0x17b6a8*/
                a1[8] = v383; /*0x17b6ab*/
                ++a1[7]; /*0x17b6ae*/
                v380 = v383; /*0x17b6b1*/
              }
              v384 = v380 >> 3; /*0x17b6b5*/
              if ( v380 >> 3 >= v544 ) /*0x17b6be*/
                v385 = *(unsigned __int8 *)(a1[3] + v384 - v544); /*0x17bdb6*/
              else
                v385 = *(unsigned __int8 *)(a1[2] + v384); /*0x17b6c7*/
              v602 = 4 * ((v385 >> v381) & 1); /*0x17b6d5*/
              v386 = v380 + 1; /*0x17b6d8*/
              a1[8] = v386; /*0x17b6d9*/
              v387 = v386 & 7; /*0x17b6de*/
              if ( (v386 & 7) == 0 ) /*0x17b6e1*/
              {
                v388 = a1[7]; /*0x17b6e3*/
                if ( v388 >= a1[6] + v544 ) /*0x17b6f1*/
                  goto LABEL_775; /*0x17b6f1*/
                v389 = 8 * v388; /*0x17b6f7*/
                a1[8] = v389; /*0x17b6fa*/
                ++a1[7]; /*0x17b6fd*/
                v386 = v389; /*0x17b700*/
              }
              v390 = v386 >> 3; /*0x17b704*/
              if ( v386 >> 3 >= v544 ) /*0x17b70d*/
                v391 = *(unsigned __int8 *)(a1[3] + v390 - v544); /*0x17bda4*/
              else
                v391 = *(unsigned __int8 *)(a1[2] + v390); /*0x17b716*/
              v603 = 8 * ((v391 >> v387) & 1); /*0x17b724*/
              v524 = v386 + 1; /*0x17b728*/
              a1[8] = v386 + 1; /*0x17b72e*/
              if ( (((_BYTE)v386 + 1) & 7) == 0 ) /*0x17b736*/
              {
                v392 = a1[7]; /*0x17b738*/
                if ( v392 >= a1[6] + v544 ) /*0x17b746*/
                  goto LABEL_775; /*0x17b746*/
                v393 = 8 * v392; /*0x17b74c*/
                a1[8] = v393; /*0x17b74f*/
                ++a1[7]; /*0x17b752*/
                v524 = v393; /*0x17b755*/
              }
              v394 = v524 >> 3; /*0x17b761*/
              if ( v524 >> 3 >= v544 ) /*0x17b76a*/
                v395 = *(unsigned __int8 *)(a1[3] + v394 - v544); /*0x17bd92*/
              else
                v395 = *(unsigned __int8 *)(a1[2] + v394); /*0x17b773*/
              v396 = 16 * ((v395 >> ((v386 + 1) & 7)) & 1); /*0x17b780*/
              v397 = v524 + 1; /*0x17b789*/
              a1[8] = v524 + 1; /*0x17b78c*/
              if ( (((_BYTE)v524 + 1) & 7) == 0 ) /*0x17b795*/
              {
                v398 = a1[7]; /*0x17b797*/
                if ( v398 >= a1[6] + v544 ) /*0x17b7a5*/
                  goto LABEL_775; /*0x17b7a5*/
                v399 = 8 * v398; /*0x17b7ab*/
                a1[8] = v399; /*0x17b7ae*/
                ++a1[7]; /*0x17b7b1*/
                v397 = v399; /*0x17b7b4*/
              }
              v400 = v397 >> 3; /*0x17b7b8*/
              if ( v397 >> 3 >= v544 ) /*0x17b7c1*/
                v401 = *(unsigned __int8 *)(a1[3] + v400 - v544); /*0x17bd80*/
              else
                v401 = *(unsigned __int8 *)(a1[2] + v400); /*0x17b7ca*/
              v525 = (32 * ((v401 >> ((v524 + 1) & 7)) & 1)) | v396 | v603 | v602 | v601 | v604; /*0x17b7ee*/
              v402 = v397 + 1; /*0x17b7f4*/
              a1[8] = v402; /*0x17b7f5*/
              v403 = v402 & 7; /*0x17b7fa*/
              if ( (v402 & 7) != 0 ) /*0x17b7fd*/
                goto LABEL_627; /*0x17b7fd*/
              v404 = a1[7]; /*0x17b7ff*/
              if ( v404 < a1[6] + v544 ) /*0x17b80d*/
              {
                v405 = 8 * v404; /*0x17b813*/
                a1[8] = v405; /*0x17b816*/
                ++a1[7]; /*0x17b819*/
                v402 = v405; /*0x17b81c*/
LABEL_627:
                v406 = v402 >> 3; /*0x17b81e*/
                if ( v402 >> 3 < v544 ) /*0x17b829*/
                  v407 = *(unsigned __int8 *)(a1[2] + v406); /*0x17bd28*/
                else
                  v407 = *(unsigned __int8 *)(a1[3] + v406 - v544); /*0x17b838*/
                a1[8] = v402 + 1; /*0x17b83f*/
                v408 = (float)((v525 | (((v407 >> v403) & 1) << 6)) - 64); /*0x17b855*/
                goto LABEL_630; /*0x17b855*/
              }
LABEL_775:
              *a1 = 1; /*0x17c1dc*/
              v408 = -65.0; /*0x17c1e2*/
LABEL_630:
              v79 = v408 + v562; /*0x17b859*/
              goto LABEL_535; /*0x17b861*/
            }
            v253 = a1[8]; /*0x17a9ec*/
            v254 = v253 & 7; /*0x17a9f1*/
            if ( (v253 & 7) != 0 ) /*0x17a9f4*/
            {
              v541 = a1[5]; /*0x17af7f*/
            }
            else
            {
              v255 = a1[7]; /*0x17a9fa*/
              v541 = a1[5]; /*0x17aa00*/
              if ( v255 >= a1[6] + v541 ) /*0x17aa0d*/
                goto LABEL_677; /*0x17aa0d*/
              v256 = 8 * v255; /*0x17aa13*/
              a1[8] = v256; /*0x17aa16*/
              ++a1[7]; /*0x17aa19*/
              v253 = v256; /*0x17aa1c*/
            }
            v257 = v253 >> 3; /*0x17aa20*/
            if ( v253 >> 3 >= v541 ) /*0x17aa29*/
              v258 = *(unsigned __int8 *)(a1[3] + v257 - v541); /*0x17b097*/
            else
              v258 = *(unsigned __int8 *)(a1[2] + v257); /*0x17aa32*/
            v599 = (v258 >> v254) & 1; /*0x17aa3d*/
            v259 = v253 + 1; /*0x17aa40*/
            a1[8] = v259; /*0x17aa41*/
            v260 = v259 & 7; /*0x17aa46*/
            if ( (v259 & 7) == 0 ) /*0x17aa49*/
            {
              v261 = a1[7]; /*0x17aa4b*/
              if ( v261 >= a1[6] + v541 ) /*0x17aa59*/
                goto LABEL_677; /*0x17aa59*/
              v262 = 8 * v261; /*0x17aa5f*/
              a1[8] = v262; /*0x17aa62*/
              ++a1[7]; /*0x17aa65*/
              v259 = v262; /*0x17aa68*/
            }
            v263 = v259 >> 3; /*0x17aa6c*/
            if ( v259 >> 3 >= v541 ) /*0x17aa75*/
              v264 = *(unsigned __int8 *)(a1[3] + v263 - v541); /*0x17b0b5*/
            else
              v264 = *(unsigned __int8 *)(a1[2] + v263); /*0x17aa7e*/
            v596 = 2 * ((v264 >> v260) & 1); /*0x17aa8b*/
            v265 = v259 + 1; /*0x17aa8e*/
            a1[8] = v265; /*0x17aa8f*/
            v266 = v265 & 7; /*0x17aa94*/
            if ( (v265 & 7) == 0 ) /*0x17aa97*/
            {
              v267 = a1[7]; /*0x17aa99*/
              if ( v267 >= a1[6] + v541 ) /*0x17aaa7*/
                goto LABEL_677; /*0x17aaa7*/
              v268 = 8 * v267; /*0x17aaad*/
              a1[8] = v268; /*0x17aab0*/
              ++a1[7]; /*0x17aab3*/
              v265 = v268; /*0x17aab6*/
            }
            v269 = v265 >> 3; /*0x17aaba*/
            if ( v265 >> 3 >= v541 ) /*0x17aac3*/
              v270 = *(unsigned __int8 *)(a1[3] + v269 - v541); /*0x17b0c7*/
            else
              v270 = *(unsigned __int8 *)(a1[2] + v269); /*0x17aacc*/
            v597 = 4 * ((v270 >> v266) & 1); /*0x17aada*/
            v271 = v265 + 1; /*0x17aadd*/
            a1[8] = v271; /*0x17aade*/
            v272 = v271 & 7; /*0x17aae3*/
            if ( (v271 & 7) == 0 ) /*0x17aae6*/
            {
              v273 = a1[7]; /*0x17aae8*/
              if ( v273 >= a1[6] + v541 ) /*0x17aaf6*/
                goto LABEL_677; /*0x17aaf6*/
              v274 = 8 * v273; /*0x17aafc*/
              a1[8] = v274; /*0x17aaff*/
              ++a1[7]; /*0x17ab02*/
              v271 = v274; /*0x17ab05*/
            }
            v275 = v271 >> 3; /*0x17ab09*/
            if ( v271 >> 3 >= v541 ) /*0x17ab12*/
              v276 = *(unsigned __int8 *)(a1[3] + v275 - v541); /*0x17b0f7*/
            else
              v276 = *(unsigned __int8 *)(a1[2] + v275); /*0x17ab1b*/
            v598 = 8 * ((v276 >> v272) & 1); /*0x17ab29*/
            v277 = v271 + 1; /*0x17ab2c*/
            a1[8] = v277; /*0x17ab2d*/
            v278 = v277 & 7; /*0x17ab32*/
            if ( (v277 & 7) == 0 ) /*0x17ab35*/
            {
              v279 = a1[7]; /*0x17ab37*/
              if ( v279 >= a1[6] + v541 ) /*0x17ab45*/
                goto LABEL_677; /*0x17ab45*/
              v280 = 8 * v279; /*0x17ab4b*/
              a1[8] = v280; /*0x17ab4e*/
              ++a1[7]; /*0x17ab51*/
              v277 = v280; /*0x17ab54*/
            }
            v281 = v277 >> 3; /*0x17ab58*/
            if ( v277 >> 3 >= v541 ) /*0x17ab61*/
              v282 = *(unsigned __int8 *)(a1[3] + v281 - v541); /*0x17b0e5*/
            else
              v282 = *(unsigned __int8 *)(a1[2] + v281); /*0x17ab6a*/
            v283 = 16 * ((v282 >> v278) & 1); /*0x17ab77*/
            v284 = v277 + 1; /*0x17ab7a*/
            a1[8] = v284; /*0x17ab7d*/
            v600 = v284 & 7; /*0x17ab83*/
            if ( (v284 & 7) != 0 ) /*0x17ab86*/
              goto LABEL_446; /*0x17ab86*/
            v285 = a1[7]; /*0x17ab88*/
            if ( v285 < a1[6] + v541 ) /*0x17ab96*/
            {
              v286 = 8 * v285; /*0x17ab9c*/
              a1[8] = v286; /*0x17ab9f*/
              ++a1[7]; /*0x17aba2*/
              v284 = v286; /*0x17aba5*/
LABEL_446:
              v287 = v284 >> 3; /*0x17aba7*/
              if ( v284 >> 3 >= v541 ) /*0x17abb2*/
                v288 = *(unsigned __int8 *)(a1[3] + v287 - v541); /*0x17b109*/
              else
                v288 = *(unsigned __int8 *)(a1[2] + v287); /*0x17abbb*/
              v518 = (32 * ((v288 >> v600) & 1)) | v283 | v598 | v597 | v596 | v599; /*0x17abdf*/
              v289 = v284 + 1; /*0x17abe5*/
              a1[8] = v284 + 1; /*0x17abe8*/
              v290 = ((_BYTE)v284 + 1) & 7; /*0x17abed*/
              if ( v290 ) /*0x17abf0*/
                goto LABEL_451; /*0x17abf0*/
              v291 = a1[7]; /*0x17abf2*/
              if ( v291 < a1[6] + v541 ) /*0x17ac00*/
              {
                v292 = 8 * v291; /*0x17ac06*/
                a1[8] = v292; /*0x17ac09*/
                ++a1[7]; /*0x17ac0c*/
                v289 = v292; /*0x17ac0f*/
LABEL_451:
                v293 = v289 >> 3; /*0x17ac11*/
                if ( v289 >> 3 < v541 ) /*0x17ac1c*/
                  v294 = *(unsigned __int8 *)(a1[2] + v293); /*0x17b115*/
                else
                  v294 = *(unsigned __int8 *)(a1[3] + v293 - v541); /*0x17ac2b*/
                a1[8] = v289 + 1; /*0x17ac32*/
                result = 100 * (v518 | (((v294 >> v290) & 1) << 6)); /*0x17ac45*/
                goto LABEL_140; /*0x17ac48*/
              }
            }
LABEL_677:
            *a1 = 1; /*0x17bb50*/
            result = -100; /*0x17bb56*/
            goto LABEL_140; /*0x17bb5b*/
          }
          v118 = a1[8]; /*0x179b95*/
          v119 = v118; /*0x179b98*/
          v120 = v118 & 7; /*0x179b9c*/
          if ( (v118 & 7) != 0 ) /*0x179b9f*/
          {
            v538 = a1[5]; /*0x17a96e*/
          }
          else
          {
            v121 = a1[7]; /*0x179ba5*/
            v538 = a1[5]; /*0x179bab*/
            if ( v121 >= a1[6] + v538 ) /*0x179bb8*/
            {
              *a1 = 1; /*0x179bbe*/
              goto LABEL_207; /*0x179bbe*/
            }
            a1[8] = 8 * v121; /*0x17ad72*/
            ++a1[7]; /*0x17ad75*/
            v119 = 8 * v121; /*0x17ad78*/
          }
          v252 = v119 >> 3; /*0x17a976*/
          if ( v119 >> 3 < v538 ) /*0x17a97f*/
            v517 = *(unsigned __int8 *)(a1[2] + v252); /*0x17a9e4*/
          else
            v517 = *(unsigned __int8 *)(a1[3] + v252 - v538); /*0x17a98e*/
          v118 = v119 + 1; /*0x17a994*/
          a1[8] = v119 + 1; /*0x17a997*/
          result = 1022; /*0x17a9a2*/
          if ( ((v517 >> v120) & 1) != 0 ) /*0x17a9ae*/
            goto LABEL_140; /*0x17a9ae*/
LABEL_207:
          v122 = v118; /*0x179bc4*/
          v123 = v118 & 7; /*0x179bc8*/
          if ( (v118 & 7) == 0 ) /*0x179bcb*/
          {
            v124 = a1[7]; /*0x179bd1*/
            if ( v124 >= a1[6] + v538 ) /*0x179bdf*/
            {
              *a1 = 1; /*0x179be5*/
              goto LABEL_210; /*0x179be5*/
            }
            a1[8] = 8 * v124; /*0x17a8f6*/
            ++a1[7]; /*0x17a8f9*/
            v122 = 8 * v124; /*0x17a8fc*/
          }
          v251 = v122 >> 3; /*0x17a900*/
          if ( v122 >> 3 < v538 ) /*0x17a909*/
            v516 = *(unsigned __int8 *)(a1[2] + v251); /*0x17ace8*/
          else
            v516 = *(unsigned __int8 *)(a1[3] + v251 - v538); /*0x17a91c*/
          v118 = v122 + 1; /*0x17a922*/
          a1[8] = v122 + 1; /*0x17a925*/
          result = 0; /*0x17a930*/
          if ( ((v516 >> v123) & 1) != 0 ) /*0x17a939*/
            goto LABEL_140; /*0x17a939*/
          v124 = a1[7]; /*0x17a93f*/
LABEL_210:
          v504 = v118; /*0x179beb*/
          v125 = v118 & 7; /*0x179bf3*/
          if ( (v118 & 7) == 0 ) /*0x179bf6*/
          {
            if ( v124 >= a1[6] + v538 ) /*0x179c03*/
              goto LABEL_707; /*0x179c03*/
            v118 = 8 * v124; /*0x179c09*/
            a1[8] = 8 * v124; /*0x179c10*/
            ++a1[7]; /*0x179c13*/
            v504 = 8 * v124; /*0x179c16*/
            v124 = a1[7]; /*0x179c1c*/
          }
          v126 = v118 >> 3; /*0x179c1f*/
          if ( v126 >= v538 ) /*0x179c28*/
            v127 = *(unsigned __int8 *)(a1[3] + v126 - v538); /*0x17acae*/
          else
            v127 = *(unsigned __int8 *)(a1[2] + v126); /*0x179c31*/
          v128 = (v127 >> v125) & 1; /*0x179c3b*/
          v505 = v504 + 1; /*0x179c45*/
          a1[8] = v505; /*0x179c4d*/
          v561 = v505 & 7; /*0x179c53*/
          if ( (v505 & 7) != 0 ) /*0x179c59*/
            goto LABEL_218; /*0x179c59*/
          if ( v124 < a1[6] + v538 ) /*0x179c66*/
          {
            a1[8] = 8 * v124; /*0x179c73*/
            ++a1[7]; /*0x179c76*/
            v505 = 8 * v124; /*0x179c79*/
            v124 = a1[7]; /*0x179c7f*/
LABEL_218:
            v129 = v505 >> 3; /*0x179c82*/
            if ( v505 >> 3 < v538 ) /*0x179c91*/
              v130 = *(unsigned __int8 *)(a1[2] + v129); /*0x17acf6*/
            else
              v130 = *(unsigned __int8 *)(a1[3] + v129 - v538); /*0x179ca0*/
            v610 = v128 | (2 * ((v130 >> v561) & 1)); /*0x179cb4*/
            a1[8] = v505 + 1; /*0x179cbe*/
LABEL_221:
            if ( v124 >= a1[6] + v538 ) /*0x179ccc*/
            {
              *a1 = 1; /*0x17ac95*/
              v131 = -1; /*0x17ac9b*/
            }
            else
            {
              if ( v124 < v538 ) /*0x179cd8*/
                v131 = *(unsigned __int8 *)(a1[2] + v124); /*0x17b121*/
              else
                v131 = *(unsigned __int8 *)(a1[3] + v124 - v538); /*0x179ce9*/
              a1[7] = v124 + 1; /*0x179cf0*/
            }
            result = v610 | (4 * v131); /*0x179cfa*/
            goto LABEL_140; /*0x179cfd*/
          }
LABEL_707:
          *a1 = 1; /*0x17bd55*/
          v610 = -1; /*0x17bd5b*/
          goto LABEL_221; /*0x17bd62*/
        }
        v163 = a1[8]; /*0x179ff8*/
        v164 = v163 & 7; /*0x179ffd*/
        if ( (v163 & 7) != 0 ) /*0x17a000*/
        {
          v540 = a1[5]; /*0x17a5b0*/
        }
        else
        {
          v165 = a1[7]; /*0x17a006*/
          v540 = a1[5]; /*0x17a00c*/
          if ( v165 >= a1[6] + v540 ) /*0x17a019*/
          {
            *a1 = 1; /*0x17a01f*/
            goto LABEL_269; /*0x17a01f*/
          }
          a1[8] = 8 * v165; /*0x17ac54*/
          ++a1[7]; /*0x17ac57*/
          v163 = 8 * v165; /*0x17ac5a*/
        }
        v201 = v163 >> 3; /*0x17a5b8*/
        if ( v163 >> 3 < v540 ) /*0x17a5c1*/
          v202 = *(unsigned __int8 *)(a1[2] + v201); /*0x17a962*/
        else
          v202 = *(unsigned __int8 *)(a1[3] + v201 - v540); /*0x17a5d0*/
        v514 = v163 + 1; /*0x17a5d5*/
        v203 = v163 + 1; /*0x17a5db*/
        a1[8] = v163 + 1; /*0x17a5dd*/
        if ( ((v202 >> v164) & 1) != 0 ) /*0x17a5e6*/
        {
          v165 = a1[7]; /*0x17a957*/
LABEL_269:
          if ( v165 + 4 > a1[6] + v540 ) /*0x17a039*/
          {
            *a1 = 1; /*0x17a9cd*/
            result = -1; /*0x17a9d3*/
          }
          else
          {
            if ( v165 >= v540 ) /*0x17a048*/
              v166 = *(_BYTE *)(a1[3] + v165 - v540); /*0x17ade4*/
            else
              v166 = *(_BYTE *)(a1[2] + v165); /*0x17a051*/
            LOBYTE(v615) = v166; /*0x17a055*/
            v167 = v165 + 1; /*0x17a057*/
            if ( v165 + 1 >= v540 ) /*0x17a060*/
              v168 = *(_BYTE *)(a1[3] + v167 - v540); /*0x17ae84*/
            else
              v168 = *(_BYTE *)(a1[2] + v167); /*0x17a069*/
            BYTE1(v615) = v168; /*0x17a06d*/
            v169 = v165 + 2; /*0x17a070*/
            if ( v165 + 2 >= v540 ) /*0x17a077*/
              v170 = *(_BYTE *)(a1[3] + v169 - v540); /*0x17ae58*/
            else
              v170 = *(_BYTE *)(a1[2] + v169); /*0x17a080*/
            BYTE2(v615) = v170; /*0x17a084*/
            v171 = v165 + 3; /*0x17a087*/
            if ( v165 + 3 < v540 ) /*0x17a090*/
              v172 = *(_BYTE *)(a1[2] + v171); /*0x17ae64*/
            else
              v172 = *(_BYTE *)(a1[3] + v171 - v540); /*0x17a09f*/
            HIBYTE(v615) = v172; /*0x17a0a3*/
            a1[7] = v165 + 4; /*0x17a0ac*/
            result = v615; /*0x17a0af*/
          }
          goto LABEL_140; /*0x17a0b2*/
        }
        v204 = v203 & 7; /*0x17a5ee*/
        if ( (v203 & 7) == 0 ) /*0x17a5f1*/
        {
          v205 = a1[7]; /*0x17a5f3*/
          if ( v205 >= a1[6] + v540 ) /*0x17a601*/
            goto LABEL_631; /*0x17a601*/
          v206 = 8 * v205; /*0x17a607*/
          a1[8] = v206; /*0x17a60a*/
          ++a1[7]; /*0x17a60d*/
          v514 = v206; /*0x17a610*/
        }
        v207 = v514 >> 3; /*0x17a61c*/
        if ( v514 >> 3 >= v540 ) /*0x17a625*/
          v208 = *(unsigned __int8 *)(a1[3] + v207 - v540); /*0x17ad50*/
        else
          v208 = *(unsigned __int8 *)(a1[2] + v207); /*0x17a62e*/
        v594 = (v208 >> v204) & 1; /*0x17a639*/
        v209 = v514 + 1; /*0x17a642*/
        a1[8] = v514 + 1; /*0x17a643*/
        if ( (((_BYTE)v514 + 1) & 7) == 0 ) /*0x17a64b*/
        {
          v210 = a1[7]; /*0x17a64d*/
          if ( v210 >= a1[6] + v540 ) /*0x17a65b*/
            goto LABEL_631; /*0x17a65b*/
          v211 = 8 * v210; /*0x17a661*/
          a1[8] = v211; /*0x17a664*/
          ++a1[7]; /*0x17a667*/
          v209 = v211; /*0x17a66a*/
        }
        v212 = v209 >> 3; /*0x17a66e*/
        if ( v209 >> 3 >= v540 ) /*0x17a677*/
          v213 = *(unsigned __int8 *)(a1[3] + v212 - v540); /*0x17ad62*/
        else
          v213 = *(unsigned __int8 *)(a1[2] + v212); /*0x17a680*/
        v590 = 2 * ((v213 >> ((v514 + 1) & 7)) & 1); /*0x17a68d*/
        v214 = v209 + 1; /*0x17a693*/
        a1[8] = v214; /*0x17a694*/
        v215 = v214 & 7; /*0x17a699*/
        if ( (v214 & 7) == 0 ) /*0x17a69c*/
        {
          v216 = a1[7]; /*0x17a69e*/
          if ( v216 >= a1[6] + v540 ) /*0x17a6ac*/
            goto LABEL_631; /*0x17a6ac*/
          v217 = 8 * v216; /*0x17a6b2*/
          a1[8] = v217; /*0x17a6b5*/
          ++a1[7]; /*0x17a6b8*/
          v214 = v217; /*0x17a6bb*/
        }
        v218 = v214 >> 3; /*0x17a6bf*/
        if ( v214 >> 3 >= v540 ) /*0x17a6c8*/
          v219 = *(unsigned __int8 *)(a1[3] + v218 - v540); /*0x17ad88*/
        else
          v219 = *(unsigned __int8 *)(a1[2] + v218); /*0x17a6d1*/
        v591 = 4 * ((v219 >> v215) & 1); /*0x17a6df*/
        v220 = v214 + 1; /*0x17a6e2*/
        a1[8] = v220; /*0x17a6e3*/
        v221 = v220 & 7; /*0x17a6e8*/
        if ( (v220 & 7) == 0 ) /*0x17a6eb*/
        {
          v222 = a1[7]; /*0x17a6ed*/
          if ( v222 >= a1[6] + v540 ) /*0x17a6fb*/
            goto LABEL_631; /*0x17a6fb*/
          v223 = 8 * v222; /*0x17a701*/
          a1[8] = v223; /*0x17a704*/
          ++a1[7]; /*0x17a707*/
          v220 = v223; /*0x17a70a*/
        }
        v224 = v220 >> 3; /*0x17a70e*/
        if ( v220 >> 3 >= v540 ) /*0x17a717*/
          v225 = *(unsigned __int8 *)(a1[3] + v224 - v540); /*0x17ad9a*/
        else
          v225 = *(unsigned __int8 *)(a1[2] + v224); /*0x17a720*/
        v592 = 8 * ((v225 >> v221) & 1); /*0x17a72e*/
        v226 = v220 + 1; /*0x17a731*/
        a1[8] = v226; /*0x17a732*/
        v227 = v226 & 7; /*0x17a737*/
        if ( (v226 & 7) == 0 ) /*0x17a73a*/
        {
          v228 = a1[7]; /*0x17a73c*/
          if ( v228 >= a1[6] + v540 ) /*0x17a74a*/
            goto LABEL_631; /*0x17a74a*/
          v229 = 8 * v228; /*0x17a750*/
          a1[8] = v229; /*0x17a753*/
          ++a1[7]; /*0x17a756*/
          v226 = v229; /*0x17a759*/
        }
        v230 = v226 >> 3; /*0x17a75d*/
        if ( v226 >> 3 >= v540 ) /*0x17a766*/
          v231 = *(unsigned __int8 *)(a1[3] + v230 - v540); /*0x17adac*/
        else
          v231 = *(unsigned __int8 *)(a1[2] + v230); /*0x17a76f*/
        v593 = 16 * ((v231 >> v227) & 1); /*0x17a77d*/
        v232 = v226 + 1; /*0x17a780*/
        a1[8] = v232; /*0x17a781*/
        v233 = v232 & 7; /*0x17a786*/
        if ( (v232 & 7) == 0 ) /*0x17a789*/
        {
          v234 = a1[7]; /*0x17a78b*/
          if ( v234 >= a1[6] + v540 ) /*0x17a799*/
            goto LABEL_631; /*0x17a799*/
          v235 = 8 * v234; /*0x17a79f*/
          a1[8] = v235; /*0x17a7a2*/
          ++a1[7]; /*0x17a7a5*/
          v232 = v235; /*0x17a7a8*/
        }
        v236 = v232 >> 3; /*0x17a7ac*/
        if ( v232 >> 3 >= v540 ) /*0x17a7b5*/
          v237 = *(unsigned __int8 *)(a1[3] + v236 - v540); /*0x17adbe*/
        else
          v237 = *(unsigned __int8 *)(a1[2] + v236); /*0x17a7be*/
        v238 = 32 * ((v237 >> v233) & 1); /*0x17a7cb*/
        v239 = v232 + 1; /*0x17a7ce*/
        a1[8] = v239; /*0x17a7d1*/
        v595 = v239 & 7; /*0x17a7d7*/
        if ( (v239 & 7) == 0 ) /*0x17a7da*/
        {
          v240 = a1[7]; /*0x17a7dc*/
          if ( v240 >= a1[6] + v540 ) /*0x17a7ea*/
            goto LABEL_631; /*0x17a7ea*/
          v241 = 8 * v240; /*0x17a7f0*/
          a1[8] = v241; /*0x17a7f3*/
          ++a1[7]; /*0x17a7f6*/
          v239 = v241; /*0x17a7f9*/
        }
        v242 = v239 >> 3; /*0x17a7fd*/
        if ( v239 >> 3 >= v540 ) /*0x17a806*/
          v243 = *(unsigned __int8 *)(a1[3] + v242 - v540); /*0x17add0*/
        else
          v243 = *(unsigned __int8 *)(a1[2] + v242); /*0x17a80f*/
        v515 = (((v243 >> v595) & 1) << 6) | v238 | v593 | v592 | v591 | v590 | v594; /*0x17a83b*/
        v244 = v239 + 1; /*0x17a841*/
        a1[8] = v239 + 1; /*0x17a844*/
        v245 = ((_BYTE)v239 + 1) & 7; /*0x17a849*/
        if ( v245 ) /*0x17a84c*/
          goto LABEL_394; /*0x17a84c*/
        v246 = a1[7]; /*0x17a84e*/
        if ( v246 < a1[6] + v540 ) /*0x17a85c*/
        {
          v247 = 8 * v246; /*0x17a862*/
          a1[8] = v247; /*0x17a865*/
          ++a1[7]; /*0x17a868*/
          v244 = v247; /*0x17a86b*/
LABEL_394:
          v248 = v244 >> 3; /*0x17a86d*/
          if ( v244 >> 3 < v540 ) /*0x17a878*/
            v249 = *(unsigned __int8 *)(a1[2] + v248); /*0x17ae70*/
          else
            v249 = *(unsigned __int8 *)(a1[3] + v248 - v540); /*0x17a887*/
          v250 = v515 | (((v249 >> v245) & 1) << 7); /*0x17a895*/
          a1[8] = v244 + 1; /*0x17a89e*/
          goto LABEL_397; /*0x17a89e*/
        }
LABEL_631:
        *a1 = 1; /*0x17b866*/
        v250 = -1; /*0x17b86c*/
LABEL_397:
        result = a2 - v250; /*0x17a8a1*/
        goto LABEL_140; /*0x17a8a8*/
      }
      v559 = *v551; /*0x179d58*/
      v132 = a1[8]; /*0x179d5e*/
      v133 = v132; /*0x179d61*/
      v134 = v132 & 7; /*0x179d65*/
      if ( (v132 & 7) != 0 ) /*0x179d68*/
      {
        v539 = a1[5]; /*0x17a3c1*/
      }
      else
      {
        v135 = a1[7]; /*0x179d6e*/
        v539 = a1[5]; /*0x179d74*/
        if ( v135 >= a1[6] + v539 ) /*0x179d7f*/
        {
          *a1 = 1; /*0x179d85*/
          goto LABEL_234; /*0x179d85*/
        }
        a1[8] = 8 * v135; /*0x17a9c0*/
        ++a1[7]; /*0x17a9c3*/
        v133 = 8 * v135; /*0x17a9c6*/
      }
      v194 = v133 >> 3; /*0x17a3c9*/
      if ( v133 >> 3 < v539 ) /*0x17a3d2*/
        v195 = *(unsigned __int8 *)(a1[2] + v194); /*0x17a56e*/
      else
        v195 = *(unsigned __int8 *)(a1[3] + v194 - v539); /*0x17a3e1*/
      v132 = v133 + 1; /*0x17a3e5*/
      a1[8] = v133 + 1; /*0x17a3e8*/
      if ( ((v195 >> v134) & 1) != 0 ) /*0x17a3f1*/
      {
        v196 = a1[7]; /*0x17a3f7*/
        if ( v196 < a1[6] + v539 ) /*0x17a405*/
        {
          if ( v196 < v539 ) /*0x17ae2b*/
            v197 = *(unsigned __int8 *)(a1[2] + v196); /*0x17b26f*/
          else
            v197 = *(unsigned __int8 *)(a1[3] + v196 - v539); /*0x17ae3c*/
          a1[7] = ++v196; /*0x17ae43*/
        }
        else
        {
          *a1 = 1; /*0x17a40b*/
          v197 = -1; /*0x17a411*/
        }
        if ( v196 < a1[6] + v539 ) /*0x17a421*/
        {
          if ( v196 < v539 ) /*0x17ae03*/
            v198 = *(unsigned __int8 *)(a1[2] + v196); /*0x17b263*/
          else
            v198 = *(unsigned __int8 *)(a1[3] + v196 - v539); /*0x17ae14*/
          a1[7] = ++v196; /*0x17ae1b*/
        }
        else
        {
          *a1 = 1; /*0x17a427*/
          v198 = -1; /*0x17a42d*/
        }
        v199 = v197 | (v198 << 8); /*0x17a437*/
        if ( v196 >= a1[6] + v539 ) /*0x17a444*/
        {
          *a1 = 1; /*0x17aded*/
          v200 = -1; /*0x17adf3*/
        }
        else
        {
          if ( v196 < v539 ) /*0x17a450*/
            v200 = *(unsigned __int8 *)(a1[2] + v196); /*0x17b27b*/
          else
            v200 = *(unsigned __int8 *)(a1[3] + v196 - v539); /*0x17a461*/
          a1[7] = v196 + 1; /*0x17a468*/
        }
        result = v199 | (v200 << 16); /*0x17a470*/
        goto LABEL_140; /*0x17a472*/
      }
LABEL_234:
      v136 = v132; /*0x179d8b*/
      v137 = v132 & 7; /*0x179d8f*/
      if ( (v132 & 7) == 0 ) /*0x179d92*/
      {
        v138 = a1[7]; /*0x179d94*/
        if ( v138 >= a1[6] + v539 ) /*0x179da2*/
          goto LABEL_512; /*0x179da2*/
        v139 = 8 * v138; /*0x179da8*/
        a1[8] = v139; /*0x179dab*/
        ++a1[7]; /*0x179dae*/
        v136 = v139; /*0x179db1*/
      }
      v140 = v136 >> 3; /*0x179db5*/
      if ( v136 >> 3 >= v539 ) /*0x179dbe*/
        v141 = *(unsigned __int8 *)(a1[3] + v140 - v539); /*0x17a552*/
      else
        v141 = *(unsigned __int8 *)(a1[2] + v140); /*0x179dc7*/
      v142 = (v141 >> v137) & 1; /*0x179dd1*/
      v506 = v136 + 1; /*0x179dd5*/
      a1[8] = v136 + 1; /*0x179ddb*/
      v143 = (v136 + 1) & 7; /*0x179dde*/
      if ( !v143 ) /*0x179de1*/
      {
        v144 = a1[7]; /*0x179de3*/
        if ( v144 >= a1[6] + v539 ) /*0x179df1*/
          goto LABEL_512; /*0x179df1*/
        v145 = 8 * v144; /*0x179df7*/
        a1[8] = v145; /*0x179dfa*/
        ++a1[7]; /*0x179dfd*/
        v506 = v145; /*0x179e00*/
      }
      v146 = v506 >> 3; /*0x179e0c*/
      if ( v506 >> 3 >= v539 ) /*0x179e15*/
        v147 = *(unsigned __int8 *)(a1[3] + v146 - v539); /*0x17a580*/
      else
        v147 = *(unsigned __int8 *)(a1[2] + v146); /*0x179e1e*/
      v587 = 2 * ((v147 >> v143) & 1); /*0x179e2b*/
      v507 = v506 + 1; /*0x179e38*/
      a1[8] = v507; /*0x179e3e*/
      v148 = v507 & 7; /*0x179e43*/
      if ( (v507 & 7) == 0 ) /*0x179e46*/
      {
        v149 = a1[7]; /*0x179e48*/
        if ( v149 >= a1[6] + v539 ) /*0x179e56*/
          goto LABEL_512; /*0x179e56*/
        v150 = 8 * v149; /*0x179e5c*/
        a1[8] = v150; /*0x179e5f*/
        ++a1[7]; /*0x179e62*/
        v507 = v150; /*0x179e65*/
      }
      v151 = v507 >> 3; /*0x179e71*/
      if ( v507 >> 3 >= v539 ) /*0x179e7a*/
        v152 = *(unsigned __int8 *)(a1[3] + v151 - v539); /*0x17a592*/
      else
        v152 = *(unsigned __int8 *)(a1[2] + v151); /*0x179e83*/
      v588 = 4 * ((v152 >> v148) & 1); /*0x179e91*/
      v508 = v507 + 1; /*0x179e9e*/
      a1[8] = v508; /*0x179ea6*/
      v589 = v508 & 7; /*0x179eac*/
      if ( (v508 & 7) == 0 ) /*0x179eb2*/
      {
        v153 = a1[7]; /*0x179eb4*/
        if ( v153 >= a1[6] + v539 ) /*0x179ec2*/
          goto LABEL_512; /*0x179ec2*/
        v154 = 8 * v153; /*0x179ec8*/
        a1[8] = v154; /*0x179ecb*/
        ++a1[7]; /*0x179ece*/
        v508 = v154; /*0x179ed1*/
      }
      v155 = v508 >> 3; /*0x179edd*/
      if ( v508 >> 3 >= v539 ) /*0x179ee6*/
        v156 = *(unsigned __int8 *)(a1[3] + v155 - v539); /*0x17a5a4*/
      else
        v156 = *(unsigned __int8 *)(a1[2] + v155); /*0x179eef*/
      v157 = (8 * ((v156 >> v589) & 1)) | v588 | v142 | v587; /*0x179f10*/
      v158 = v508 + 1; /*0x179f18*/
      a1[8] = v508 + 1; /*0x179f1b*/
      v560 = (v508 + 1) & 7; /*0x179f21*/
      if ( v560 ) /*0x179f27*/
        goto LABEL_257; /*0x179f27*/
      v159 = a1[7]; /*0x179f29*/
      if ( v159 < a1[6] + v539 ) /*0x179f37*/
      {
        v160 = 8 * v159; /*0x179f3d*/
        a1[8] = v160; /*0x179f40*/
        ++a1[7]; /*0x179f43*/
        v158 = v160; /*0x179f46*/
LABEL_257:
        v161 = v158 >> 3; /*0x179f48*/
        if ( v158 >> 3 < v539 ) /*0x179f53*/
          v509 = *(unsigned __int8 *)(a1[2] + v161); /*0x17a8c8*/
        else
          v509 = *(unsigned __int8 *)(a1[3] + v161 - v539); /*0x179f66*/
        a1[8] = v158 + 1; /*0x179f6f*/
        v162 = 1 << (v157 | (16 * ((v509 >> v560) & 1))); /*0x179f9f*/
        goto LABEL_260; /*0x179f9f*/
      }
LABEL_512:
      *a1 = 1; /*0x17b081*/
      v162 = 0; /*0x17b087*/
LABEL_260:
      result = v559 ^ v162; /*0x179fa1*/
      goto LABEL_140; /*0x179fa7*/
    }
    v82 = a1[8]; /*0x179778*/
    v83 = v82; /*0x17977b*/
    v84 = v82 & 7; /*0x17977f*/
    if ( (v82 & 7) != 0 ) /*0x179782*/
    {
      v537 = a1[5]; /*0x179b43*/
    }
    else
    {
      v85 = a1[7]; /*0x179788*/
      v537 = a1[5]; /*0x17978e*/
      if ( v85 >= a1[6] + v537 ) /*0x17979b*/
      {
        *a1 = 1; /*0x1797a1*/
        goto LABEL_146; /*0x1797a1*/
      }
      a1[8] = 8 * v85; /*0x17a8b4*/
      ++a1[7]; /*0x17a8b7*/
      v83 = 8 * v85; /*0x17a8ba*/
    }
    v116 = v83 >> 3; /*0x179b4b*/
    if ( v83 >> 3 < v537 ) /*0x179b54*/
      v117 = *(unsigned __int8 *)(a1[2] + v116); /*0x17a3a3*/
    else
      v117 = *(unsigned __int8 *)(a1[3] + v116 - v537); /*0x179b63*/
    v82 = v83 + 1; /*0x179b67*/
    a1[8] = v83 + 1; /*0x179b6a*/
    if ( ((v117 >> v84) & 1) == 0 ) /*0x179b73*/
      goto LABEL_318; /*0x179b73*/
    v85 = a1[7]; /*0x179b79*/
LABEL_146:
    v86 = v82; /*0x1797a7*/
    v87 = v82 & 7; /*0x1797ab*/
    if ( (v82 & 7) == 0 ) /*0x1797ae*/
    {
      if ( v85 >= a1[6] + v537 ) /*0x1797bf*/
      {
        *a1 = 1; /*0x1797c5*/
LABEL_149:
        if ( v85 + 4 > a1[6] + v537 ) /*0x1797e3*/
        {
          *a1 = 1; /*0x17a947*/
          v95 = -1; /*0x17a94d*/
        }
        else
        {
          if ( v85 >= v537 ) /*0x1797f2*/
            v88 = *(_BYTE *)(a1[3] + v85 - v537); /*0x17ad3e*/
          else
            v88 = *(_BYTE *)(a1[2] + v85); /*0x1797fb*/
          LOBYTE(v614) = v88; /*0x1797ff*/
          v89 = v85 + 1; /*0x179801*/
          if ( v85 + 1 >= v537 ) /*0x17980a*/
            v90 = *(_BYTE *)(a1[3] + v89 - v537); /*0x17ad2a*/
          else
            v90 = *(_BYTE *)(a1[2] + v89); /*0x179813*/
          BYTE1(v614) = v90; /*0x179817*/
          v91 = v85 + 2; /*0x17981a*/
          if ( v85 + 2 >= v537 ) /*0x179821*/
            v92 = *(_BYTE *)(a1[3] + v91 - v537); /*0x17ad16*/
          else
            v92 = *(_BYTE *)(a1[2] + v91); /*0x17982a*/
          BYTE2(v614) = v92; /*0x17982e*/
          v93 = v85 + 3; /*0x179831*/
          if ( v85 + 3 < v537 ) /*0x17983a*/
            v94 = *(_BYTE *)(a1[2] + v93); /*0x17ad02*/
          else
            v94 = *(_BYTE *)(a1[3] + v93 - v537); /*0x179849*/
          HIBYTE(v614) = v94; /*0x17984d*/
          a1[7] = v85 + 4; /*0x179856*/
          v95 = v614; /*0x179859*/
        }
        *v552 = *v551 ^ v95; /*0x17986a*/
        result = a6; /*0x17986c*/
        if ( a6 ) /*0x179871*/
        {
          v79 = *(float *)v552; /*0x179877*/
          return Com_Printf(16, "%s:%f ", *a5, v79); /*0x17987b*/
        }
        return result; /*0x179871*/
      }
      a1[8] = 8 * v85; /*0x17a0be*/
      ++a1[7]; /*0x17a0c1*/
      v86 = 8 * v85; /*0x17a0c4*/
      v85 = a1[7]; /*0x17a0c6*/
    }
    v173 = v86 >> 3; /*0x17a0cb*/
    if ( v86 >> 3 < v537 ) /*0x17a0d4*/
      v174 = *(unsigned __int8 *)(a1[2] + v173); /*0x17a8d6*/
    else
      v174 = *(unsigned __int8 *)(a1[3] + v173 - v537); /*0x17a0e3*/
    v510 = v86 + 1; /*0x17a0e8*/
    v175 = v86 + 1; /*0x17a0ee*/
    a1[8] = v86 + 1; /*0x17a0f0*/
    if ( ((v174 >> v87) & 1) != 0 ) /*0x17a0f9*/
      goto LABEL_149; /*0x17a0f9*/
    v176 = v175 & 7; /*0x17a101*/
    if ( (v175 & 7) == 0 ) /*0x17a104*/
    {
      if ( v85 >= a1[6] + v537 ) /*0x17a111*/
        goto LABEL_674; /*0x17a111*/
      a1[8] = 8 * v85; /*0x17a11e*/
      ++a1[7]; /*0x17a121*/
      v510 = 8 * v85; /*0x17a124*/
      v85 = a1[7]; /*0x17a12a*/
    }
    v177 = v510 >> 3; /*0x17a133*/
    if ( v510 >> 3 >= v537 ) /*0x17a13c*/
      v178 = *(unsigned __int8 *)(a1[3] + v177 - v537); /*0x17ac7a*/
    else
      v178 = *(unsigned __int8 *)(a1[2] + v177); /*0x17a145*/
    v179 = (v178 >> v176) & 1; /*0x17a14f*/
    v511 = v510 + 1; /*0x17a159*/
    a1[8] = v511; /*0x17a161*/
    v585 = v511 & 7; /*0x17a167*/
    if ( (v511 & 7) == 0 ) /*0x17a16d*/
    {
      if ( v85 >= a1[6] + v537 ) /*0x17a17a*/
        goto LABEL_674; /*0x17a17a*/
      a1[8] = 8 * v85; /*0x17a187*/
      ++a1[7]; /*0x17a18a*/
      v511 = 8 * v85; /*0x17a18d*/
      v85 = a1[7]; /*0x17a193*/
    }
    v180 = v511 >> 3; /*0x17a19c*/
    if ( v511 >> 3 >= v537 ) /*0x17a1a5*/
      v181 = *(unsigned __int8 *)(a1[3] + v180 - v537); /*0x17ac8c*/
    else
      v181 = *(unsigned __int8 *)(a1[2] + v180); /*0x17a1ae*/
    v584 = 2 * ((v181 >> v585) & 1); /*0x17a1c0*/
    v512 = v511 + 1; /*0x17a1cd*/
    a1[8] = v512; /*0x17a1d5*/
    v586 = v512 & 7; /*0x17a1db*/
    if ( (v512 & 7) == 0 ) /*0x17a1e1*/
    {
      if ( v85 >= a1[6] + v537 ) /*0x17a1ee*/
        goto LABEL_674; /*0x17a1ee*/
      a1[8] = 8 * v85; /*0x17a1fb*/
      ++a1[7]; /*0x17a1fe*/
      v512 = 8 * v85; /*0x17a201*/
      v85 = a1[7]; /*0x17a207*/
    }
    v182 = v512 >> 3; /*0x17a210*/
    if ( v512 >> 3 >= v537 ) /*0x17a219*/
      v183 = *(unsigned __int8 *)(a1[3] + v182 - v537); /*0x17acc0*/
    else
      v183 = *(unsigned __int8 *)(a1[2] + v182); /*0x17a222*/
    v184 = (4 * ((v183 >> v586) & 1)) | v584 | v179; /*0x17a23b*/
    v513 = v512 + 1; /*0x17a244*/
    a1[8] = v513; /*0x17a24c*/
    v558 = v513 & 7; /*0x17a252*/
    if ( (v513 & 7) != 0 ) /*0x17a258*/
      goto LABEL_301; /*0x17a258*/
    if ( v85 < a1[6] + v537 ) /*0x17a265*/
    {
      a1[8] = 8 * v85; /*0x17a272*/
      ++a1[7]; /*0x17a275*/
      v513 = 8 * v85; /*0x17a278*/
      v85 = a1[7]; /*0x17a27e*/
LABEL_301:
      v185 = v513 >> 3; /*0x17a281*/
      if ( v513 >> 3 < v537 ) /*0x17a290*/
        v186 = *(unsigned __int8 *)(a1[2] + v185); /*0x17acd8*/
      else
        v186 = *(unsigned __int8 *)(a1[3] + v185 - v537); /*0x17a29f*/
      v571 = v184 | (8 * ((v186 >> v558) & 1)); /*0x17a2b4*/
      a1[8] = v513 + 1; /*0x17a2c1*/
LABEL_304:
      if ( v85 >= a1[6] + v537 ) /*0x17a2cf*/
      {
        *a1 = 1; /*0x17ac61*/
        v188 = -16; /*0x17ac67*/
      }
      else
      {
        if ( v85 < v537 ) /*0x17a2db*/
          v187 = *(unsigned __int8 *)(a1[2] + v85); /*0x17b0d3*/
        else
          v187 = *(unsigned __int8 *)(a1[3] + v85 - v537); /*0x17a2ec*/
        a1[7] = v85 + 1; /*0x17a2f3*/
        v188 = 16 * v187; /*0x17a2f8*/
      }
      result = (((int)*(float *)v551 + 2048) ^ (v571 + v188)) - 2048; /*0x17a313*/
      goto LABEL_115; /*0x17a318*/
    }
LABEL_674:
    *a1 = 1; /*0x17bb2a*/
    v571 = -1; /*0x17bb30*/
    goto LABEL_304; /*0x17bb3a*/
  }
  v40 = a1[7]; /*0x179224*/
  v41 = v40 + 4; /*0x179227*/
  v536 = a1[5]; /*0x17922d*/
  if ( v40 + 4 > a1[6] + v536 ) /*0x179238*/
  {
    *a1 = 1; /*0x179ad4*/
    v49 = -1; /*0x179ada*/
  }
  else
  {
    if ( v40 >= v536 ) /*0x179247*/
      v42 = *(_BYTE *)(a1[3] + v40 - v536); /*0x17a4c8*/
    else
      v42 = *(_BYTE *)(a1[2] + v40); /*0x179250*/
    LOBYTE(v612) = v42; /*0x179254*/
    v43 = v40 + 1; /*0x179256*/
    if ( v43 >= v536 ) /*0x17925d*/
      v44 = *(_BYTE *)(a1[3] + v43 - v536); /*0x17a4b4*/
    else
      v44 = *(_BYTE *)(a1[2] + v43); /*0x179266*/
    BYTE1(v612) = v44; /*0x17926a*/
    v45 = v43 + 1; /*0x17926d*/
    if ( v45 >= v536 ) /*0x179274*/
      v46 = *(_BYTE *)(a1[3] + v45 - v536); /*0x17a4a0*/
    else
      v46 = *(_BYTE *)(a1[2] + v45); /*0x17927d*/
    BYTE2(v612) = v46; /*0x179281*/
    v47 = v45 + 1; /*0x179284*/
    if ( v45 + 1 < v536 ) /*0x17928d*/
      v48 = *(_BYTE *)(a1[2] + v47); /*0x17a48c*/
    else
      v48 = *(_BYTE *)(a1[3] + v47 - v536); /*0x17929c*/
    HIBYTE(v612) = v48; /*0x1792a0*/
    a1[7] = v41; /*0x1792a3*/
    v49 = v612; /*0x1792a6*/
  }
  *v552 = v49; /*0x179ae5*/
  result = *v551 ^ v49; /*0x179aed*/
  *v552 = result; /*0x179aef*/
  if ( a6 ) /*0x179af6*/
  {
    v79 = *(float *)v552; /*0x179afc*/
    return Com_Printf(16, "%s:%f ", *a5, v79); /*0x179b22*/
  }
  return result; /*0x178ed4*/
}