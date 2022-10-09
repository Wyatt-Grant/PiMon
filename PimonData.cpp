move genericMoveData[] = {
    // basic attacks
    { 0, "Slam", NONE, 60, 90, TARGET_OPPONENT, PHYSICAL_DAMAGE, BASIC_ATTACK, 100 },
    { 1, "Scratch", NONE, 40, 100, TARGET_OPPONENT, PHYSICAL_DAMAGE, BASIC_ATTACK, 100 },
    { 2, "Bite", NONE, 50, 100, TARGET_OPPONENT, PHYSICAL_DAMAGE, BASIC_ATTACK, 100 },
    { 3, "Kick", NONE, 45, 100, TARGET_OPPONENT, PHYSICAL_DAMAGE, BASIC_ATTACK, 100 },
    { 4, "Slap", NONE, 30, 40, TARGET_OPPONENT, PHYSICAL_DAMAGE, BASIC_ATTACK, 100 },

    // strong attacks
    { 5, "Bullet Punch", NONE, 75, 90, TARGET_OPPONENT, PHYSICAL_DAMAGE, BASIC_ATTACK, 100 },
    { 6, "Iron Claw", NONE, 70, 50, TARGET_OPPONENT, PHYSICAL_DAMAGE, BASIC_ATTACK, 100 },
    { 7, "Tooth Blade", NONE, 80, 90, TARGET_OPPONENT, PHYSICAL_DAMAGE, BASIC_ATTACK, 100 },
    { 8, "Gravity Kick", NONE, 90, 80, TARGET_OPPONENT, PHYSICAL_DAMAGE, BASIC_ATTACK, 100 },
    { 9, "Quantum Shot", NONE, 80, 90, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },

    // status attacks
    { 10, "Hypnotize", NONE, 0, 70, TARGET_OPPONENT, NO_DAMAGE, SLEEP_ATTACK, 100 }, // sleep
    { 11, "Psychosis", NONE, 0, 70, TARGET_OPPONENT, NO_DAMAGE, CONFUSION_ATTACK, 100 }, // confusion
    { 12, "Slow Roast", NONE, 0, 100, TARGET_OPPONENT, NO_DAMAGE, BURN_ATTACK, 100 }, // burned

    // user stat attacks
    { 13, "Iron Skin", NONE, 60, 90, TARGET_USER, NO_DAMAGE, RAISE_USER_DEFENSE, 100 }, // defense
    { 14, "War Cry", NONE, 40, 100, TARGET_USER, NO_DAMAGE, RAISE_USER_ATTACK, 100 }, // attack
    { 15, "Sharp Mind", NONE, 50, 100, TARGET_USER, NO_DAMAGE, RAISE_USER_SP_ATTACK, 100 }, // sp atk
    { 16, "Calm Mind", NONE, 45, 100, TARGET_USER, NO_DAMAGE, RAISE_USER_SP_DEFENSE, 100 }, // sp def
    { 17, "Agility", NONE, 30, 100, TARGET_USER, NO_DAMAGE, RAISE_USER_SPEED, 100 }, // speed

    // enemy stat attacks
    { 18, "Corrosion", NONE, 60, 90, TARGET_OPPONENT, NO_DAMAGE, LOWER_ENEMY_SP_DEFENSE, 100 }, // defense
    { 19, "Erosion", NONE, 40, 100, TARGET_OPPONENT, NO_DAMAGE, LOWER_ENEMY_SP_ATTACK, 100 }, // attack
    { 20, "Scary Look", NONE, 50, 100, TARGET_OPPONENT, NO_DAMAGE, LOWER_ENEMY_DEFENSE, 100 }, // sp atk
    { 21, "Shriek", NONE, 45, 100, TARGET_OPPONENT, NO_DAMAGE, LOWER_ENEMY_ATTACK, 100 }, // sp def
    { 22, "Tar Ball", NONE, 30, 100, TARGET_OPPONENT, NO_DAMAGE, LOWER_ENEMY_SPEED, 100 }, // speed

    // special attacks
    { 23, "Fire Ball", FIRE, 100, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 24, "Fire Punch", FIRE, 125, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 25, "Solar Flare", FIRE, 150, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },

    { 26, "Wave", WATER, 110, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 27, "Hydro Blast", WATER, 130, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 28, "Hydro Cannon", WATER, 165, 90, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },

    { 29, "Earthquake", EARTH, 120, 80, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 30, "Meteor", EARTH, 140, 80, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 31, "Seismic Wave", EARTH, 190, 70, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },

    { 32, "Gust", AIR, 110, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 33, "Wind Slice", AIR, 130, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 34, "Tornado", AIR, 160, 90, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
};

pimon genericPimonData[] = {
    {1,"Bursa",FIRE,45,50,50,65,65,45,{     genericMoveData[0],     genericMoveData[5],     genericMoveData[18],     genericMoveData[23]}},
    {2,"Volsaur",FIRE,45,50,50,65,65,45,{   genericMoveData[0],     genericMoveData[5],     genericMoveData[18],     genericMoveData[23]}},
    {3,"Cactine",EARTH,45,50,50,65,65,45,{  genericMoveData[1],     genericMoveData[6],     genericMoveData[19],     genericMoveData[29]}},
    {4,"Cacamos",EARTH,45,50,50,65,65,45,{  genericMoveData[1],     genericMoveData[6],     genericMoveData[19],     genericMoveData[29]}},
    {5,"Gali",WATER,45,50,50,65,65,45,{     genericMoveData[2],     genericMoveData[7],     genericMoveData[20],     genericMoveData[26]}},
    {6,"Galorus",WATER,45,50,50,65,65,45,{  genericMoveData[2],     genericMoveData[7],     genericMoveData[20],     genericMoveData[26]}},
    {7,"Henra",AIR,45,50,50,65,65,45,{      genericMoveData[3],     genericMoveData[8],     genericMoveData[17],     genericMoveData[32]}},
    {8,"Hawckos",AIR,45,50,50,65,65,45,{    genericMoveData[3],     genericMoveData[8],     genericMoveData[17],     genericMoveData[32]}},
    {9,"Bunflare",FIRE,45,50,50,65,65,45,{  genericMoveData[4],     genericMoveData[12],     genericMoveData[21],     genericMoveData[25]}},
    {10,"Grizchar",FIRE,45,50,50,65,65,45,{ genericMoveData[4],     genericMoveData[12],     genericMoveData[21],     genericMoveData[25]}},
    {11,"Trunit",EARTH,45,50,50,65,65,45,{  genericMoveData[0],     genericMoveData[10],     genericMoveData[22],     genericMoveData[30]}},
    {12,"Elatruss",EARTH,45,50,50,65,65,45,{genericMoveData[0],     genericMoveData[10],     genericMoveData[22],     genericMoveData[30]}},
    {13,"Hamil",WATER,45,50,50,65,65,45,{   genericMoveData[1],     genericMoveData[11],     genericMoveData[5],     genericMoveData[27]}},
    {14,"Mouji",WATER,45,50,50,65,65,45,{   genericMoveData[1],     genericMoveData[11],     genericMoveData[5],     genericMoveData[27]}},
    {15,"Songla",AIR,45,50,50,65,65,45,{    genericMoveData[2],     genericMoveData[9],     genericMoveData[6],     genericMoveData[33]}},
    {16,"Aravia",AIR,45,50,50,65,65,45,{    genericMoveData[2],     genericMoveData[9],     genericMoveData[6],     genericMoveData[33]}},
    {17,"Antel",FIRE,45,50,50,65,65,45,{    genericMoveData[3],     genericMoveData[13],     genericMoveData[12],     genericMoveData[24]}},
    {18,"Punchant",FIRE,45,50,50,65,65,45,{ genericMoveData[3],     genericMoveData[13],     genericMoveData[12],     genericMoveData[24]}},
    {19,"Rocet",EARTH,45,50,50,65,65,45,{   genericMoveData[4],     genericMoveData[14],     genericMoveData[7],     genericMoveData[31]}},
    {20,"Gravet",EARTH,45,50,50,65,65,45,{  genericMoveData[4],     genericMoveData[14],     genericMoveData[7],     genericMoveData[31]}},
    {21,"Krabli",WATER,45,50,50,65,65,45,{  genericMoveData[0],     genericMoveData[15],     genericMoveData[8],     genericMoveData[28]}},
    {22,"Sheladon",WATER,45,50,50,65,65,45,{genericMoveData[0],     genericMoveData[15],     genericMoveData[8],     genericMoveData[28]}},
    {23,"Balloo",AIR,45,50,50,65,65,45,{    genericMoveData[1],     genericMoveData[16],     genericMoveData[9],     genericMoveData[34]}},
    {24,"Blimfrog",AIR,45,50,50,65,65,45,{  genericMoveData[1],     genericMoveData[16],     genericMoveData[9],     genericMoveData[34]}}
};