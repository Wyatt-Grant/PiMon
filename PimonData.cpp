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
    { 11, "Psychosis", NONE, 0, 70, TARGET_OPPONENT, PHYSICAL_DAMAGE, BASIC_ATTACK, 100 },

    // status attacks
    { 10, "Hypnotize", NONE, 0, 70, TARGET_OPPONENT, NO_DAMAGE, SLEEP_ATTACK, 100 }, // sleep
    { 12, "Slow Roast", NONE, 0, 100, TARGET_OPPONENT, NO_DAMAGE, BURN_ATTACK, 100 }, // burned

    // special attacks
    { 13, "Fire Ball", FIRE, 100, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 14, "Fire Punch", FIRE, 125, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 15, "Solar Flare", FIRE, 150, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },

    { 16, "Wave", WATER, 110, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 17, "Hydro Blast", WATER, 130, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 18, "Hydro Cannon", WATER, 165, 90, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },

    { 19, "Earthquake", EARTH, 120, 80, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 20, "Meteor", EARTH, 140, 80, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 21, "Seismic Wave", EARTH, 190, 70, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },

    { 22, "Gust", AIR, 110, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 23, "Wind Slice", AIR, 130, 100, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
    { 24, "Tornado", AIR, 160, 90, TARGET_OPPONENT, SPECIAL_DAMAGE, BASIC_ATTACK, 100 },
};

pimon genericPimonData[] = {
    {1 , "Bursa",    FIRE,  40,45,50,55,60,65, {genericMoveData[0],  genericMoveData[5],   genericMoveData[13],  genericMoveData[14]}},
    {2 , "Volsaur",  FIRE,  60,65,70,75,80,85, {genericMoveData[0],  genericMoveData[5],   genericMoveData[13],  genericMoveData[14]}},
    {3 , "Cactine",  EARTH, 45,50,55,60,65,40, {genericMoveData[1],  genericMoveData[6],   genericMoveData[19],  genericMoveData[20]}},
    {4 , "Cacamos",  EARTH, 65,70,75,80,85,60, {genericMoveData[1],  genericMoveData[6],   genericMoveData[19],  genericMoveData[20]}},
    {5 , "Gali",     WATER, 50,55,60,65,40,45, {genericMoveData[2],  genericMoveData[7],   genericMoveData[16],  genericMoveData[17]}},
    {6 , "Galorus",  WATER, 70,75,80,85,60,65, {genericMoveData[2],  genericMoveData[7],   genericMoveData[16],  genericMoveData[17]}},
    {7 , "Henra",    AIR,   55,60,65,40,45,50, {genericMoveData[3],  genericMoveData[8],   genericMoveData[22],  genericMoveData[23]}},
    {8 , "Hawckos",  AIR,   75,80,85,60,65,70, {genericMoveData[3],  genericMoveData[8],   genericMoveData[22],  genericMoveData[23]}},
    {9 , "Bunflare", FIRE,  60,65,40,45,50,55, {genericMoveData[4],  genericMoveData[12],  genericMoveData[14],  genericMoveData[15]}},
    {10, "Grizchar", FIRE,  80,85,60,65,70,75, {genericMoveData[4],  genericMoveData[12],  genericMoveData[14],  genericMoveData[15]}},
    {11, "Trunit",   EARTH, 65,40,45,50,55,60, {genericMoveData[0],  genericMoveData[10],  genericMoveData[20],  genericMoveData[21]}},
    {12, "Elatruss", EARTH, 85,60,65,70,75,80, {genericMoveData[0],  genericMoveData[10],  genericMoveData[20],  genericMoveData[21]}},
    {13, "Hamil",    WATER, 55,60,65,40,45,50, {genericMoveData[1],  genericMoveData[11],  genericMoveData[17],  genericMoveData[18]}},
    {14, "Mouji",    WATER, 75,80,85,60,65,70, {genericMoveData[1],  genericMoveData[11],  genericMoveData[17],  genericMoveData[18]}},
    {15, "Songla",   AIR,   60,65,40,45,50,55, {genericMoveData[2],  genericMoveData[9],   genericMoveData[23],  genericMoveData[24]}},
    {16, "Aravia",   AIR,   80,85,60,65,70,75, {genericMoveData[2],  genericMoveData[9],   genericMoveData[23],  genericMoveData[24]}},
    {17, "Antel",    FIRE,  65,40,45,50,55,60, {genericMoveData[3],  genericMoveData[5],   genericMoveData[13],  genericMoveData[15]}},
    {18, "Punchant", FIRE,  85,60,65,70,75,80, {genericMoveData[3],  genericMoveData[5],   genericMoveData[13],  genericMoveData[15]}},
    {19, "Rocet",    EARTH, 40,45,50,55,60,65, {genericMoveData[4],  genericMoveData[6],   genericMoveData[19],  genericMoveData[21]}},
    {20, "Gravet",   EARTH, 60,65,70,75,80,85, {genericMoveData[4],  genericMoveData[6],   genericMoveData[19],  genericMoveData[21]}},
    {21, "Krabli",   WATER, 45,50,55,60,65,40, {genericMoveData[0],  genericMoveData[7],   genericMoveData[16],  genericMoveData[18]}},
    {22, "Sheladon", WATER, 65,70,75,80,85,60, {genericMoveData[0],  genericMoveData[7],   genericMoveData[16],  genericMoveData[18]}},
    {23, "Balloo",   AIR,   50,55,60,65,40,45, {genericMoveData[1],  genericMoveData[8],   genericMoveData[22],  genericMoveData[24]}},
    {24, "Blimfrog", AIR,   70,75,80,85,60,65, {genericMoveData[1],  genericMoveData[8],   genericMoveData[22],  genericMoveData[24]}}
};