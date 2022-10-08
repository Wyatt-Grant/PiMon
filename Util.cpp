namespace picosystem {
    voice_t piano = voice(20, 200, 50, 50);
    int16_t notes[] = { 0, 262, 277, 294, 311, 330, 349, 370, 391, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951 };

    // ez music - play music on the piezo buzzer using rtttl formatted songs. more: https://en.wikipedia.org/wiki/Ring_Tone_Text_Transfer_Language
    void play_rtttl(std::string song) {
        char char_array[song.length() + 1];
        strcpy(char_array, song.c_str());
        char *p = char_array;
        unsigned char default_dur = 4;
        unsigned char default_oct = 6;
        int bpm = 63;
        int num;
        long wholenote;
        long duration;
        unsigned char note;
        unsigned char scale;

        while(*p != ':') {
            p++;
        }
        p++;
        if(*p == 'd') {
            p++;
            p++;
            num = 0;
            while(isdigit(*p))
            {
            num = (num * 10) + (*p++ - '0');
            }
            if(num > 0) default_dur = num;
            p++;
        }
        if(*p == 'o') {
            p++; p++;
            num = *p++ - '0';
            if(num >= 3 && num <=7) {
                default_oct = num;
            }
            p++;
        }

        if(*p == 'b') {
            p++; p++;
            num = 0;
            while(isdigit(*p))
            {
            num = (num * 10) + (*p++ - '0');
            }
            bpm = num;
            p++;
        }

        wholenote = (60 * 1000L / bpm) * 4;

        while(*p) {
            if (changeSong || menuOpen) {
                changeSong = false;
                break;
            }

            num = 0;
            while(isdigit(*p)) {
                num = (num * 10) + (*p++ - '0');
            }

            if(num) duration = wholenote / num;
            else duration = wholenote / default_dur;

            note = 0;

            switch(*p) {
                case 'c':
                    note = 1;
                    break;
                case 'd':
                    note = 3;
                    break;
                case 'e':
                    note = 5;
                    break;
                case 'f':
                    note = 6;
                    break;
                case 'g':
                    note = 8;
                    break;
                case 'a':
                    note = 10;
                    break;
                case 'b':
                    note = 12;
                    break;
                case 'p':
                default:
                    note = 0;
            }

            p++;

            if(*p == '#') {
                note++;
                p++;
            }
            if(*p == '.') {
                duration += duration/2;
                p++;
            }
            if (isdigit(*p)) {
                scale = *p - '0';
                p++;
            } else {
                scale = default_oct;
            }
            if(*p == ',') {
                p++;
            }

            if (note) {
                play(piano, notes[(scale - 4) * 12 + note], duration * 0.9, volume);
                sleep(duration);
            } else {
                sleep(duration);
            }
        }
    }

    /**
     * play error sound
     * 
     * @return void
     */
    voice_t errorSound = voice(100,0,60,0,0,0,0,0,60);
    void playError() {
        play(errorSound, 300, 400, 100);
    }

    /**
     * play music helper
     * 
     * @return void
     */
    void playMusic() {
        while(1) {
            std::string route_song = "route_song:d=8,o=7,b=240:2p.,d6,e6,4f#6,4f#6,4f#6,d6,e6,4f#6,4f#6,4f#6,d6,e6,4f#6,4f#6,g6,4g6,f#6,2e6,4p,c#6,d6,4e6,4e6,4e6,c#6,d6,4e6,4e6,4e6,c#6,d6,4e6,4e6,f#6,e6,e6,f#6,2d6,4p,d6,e6,4f#6,4f#6,4f#6,d6,e6,4f#6,4f#6,4f#6,d6,e6,4f#6,4f#6,4g.6,f#6,2e6,4p,c#6,d6,4e6,4g6,4f#6,4e6,4d6,4c#6,4b5,4c#6,2b6,2e6,2f#6,2p,2d5,2c#5,2b4,2a4,2d5,2a4,2b4,2a4,2c#5,2a4,2b4,2c5,2c#5,2a4,2d5,4p,d6,e6,4f#6,4f#6,4f#6,d6,e6,4f#6,4f#6,4f#6,d6,e6,4f#6,4f#6,g6,4g6,f#6,2e6,4p,c#6,d6,4e6,4e6,4e6,c#6,d6,4e6,4e6,4e6,c#6,d6,4e6,4e6,f#6,e6,e6,f#6,2d6,4p,d6,e6,4f#6,4f#6,4f#6,d6,e6,4f#6,4f#6,4f#6,d6,e6,4f#6,4f#6,4g.6,f#6,2e6,4p,c#6,d6,4e6,4g6,4f#6,4e6,4d6,4c#6,4b5,4c#6,2b6,2e6,2f#6,2p,2d5,2c#5,2b4,2a4,2d5,2a4,2b4,2a4,2c#5,2a4,2b4,2c5,2c#5,2a4,2d5,4p,d6,e6,4f#6,4f#6,4f#6,d6,e6,4f#6,4f#6,4f#6,d6,e6,4f#6,4f#6,4g.6,f#6,2e6,4p,c#6,d6,4e6,4g6,4f#6,4e6,4d6,4c#6,4b5,4c#6,2b6,2e6,4f#6,4a5,2d6";
            std::string battle_song = "battle_song:d=8,o=7,b=185:16c6,16b5,16a#5,16a5,16a#5,16a5,16g#5,16g5,16g#5,16g5,16f#5,16f5,16f#5,16f5,16e5,16d#5,16e5,16d#5,16d5,16c#5,16d5,16c#5,16c5,16b4,16c5,16b4,16a#4,16a4,16a#4,16b4,16c5,16c#5,4g5,p,4a#4,p,4d5,4c5,4c#5,4d5,4p,4d#5,p,4a#4,p,4d#5,4c5,4d5,2d#5,4d6,p,4a#5,p,4d6,4c6,4c#6,4d6,4p,4d#6,p,4a#5,p,4d#6,4c6,4d6,2d#6,4d.5,4b.4,4b4,4f.5,4e.5,4c5,2g#5,16a#5,16a5,16g#5,16g5,16g#5,16a5,16a#5,16b5,2c6,16b5,16a#5,16a5,16g#5,16a5,16a#5,16b5,16c6,4d.5,4b.4,4b4,4f.5,4e.5,4d5,2e5,2d5,2c5,2f5,4d#.5,4c.5,4c5,4f#.5,4f.5,4c#5,2a5,16b5,16a#5,16a5,16g#5,16a5,16a#5,16b5,16c6,2c#6,16c6,16b5,16a#5,16a5,16a#5,16b5,16c6,16c#6,4d#.5,4c.5,4c5,4f#.5,4f.5,4c#5,2f5,2d#5,2c#5,2f#5,4e.5,4d.5,4e5,4f.5,4e.5,4c5,2f5,2c5,4e.5,4d.5,4f5,1g5,2d6,2g6,1g6,1d6,4c5,4d5,4c5,4b4,1c5,4d5,4e5,4d5,4f#5,1g5,4d.5,4b.4,4b4,4f.5,4e.5,4c5,2g#5,16a#5,16a5,16g#5,16g5,16g#5,16a5,16a#5,16b5,2c6,16b5,16a#5,16a5,16g#5,16a5,16a#5,16b5,16c6,4d.5,4b.4,4b4,4f.5,4e.5,4d5,2e5,2d5,2c5,2f5,4d#.5,4c.5,4c5,4f#.5,4f.5,4c#5,2a5,16b5,16a#5,16a5,16g#5,16a5,16a#5,16b5,16c6,2c#6,16c6,16b5,16a#5,16a5,16a#5,16b5,16c6,16c#6,4d#.5,4c.5,4c5,4f#.5,4f.5,4c#5,2f5,2d#5,2c#5,2f#5,4e.5,4d.5,4e5,4f.5,4e.5,4c5,2f5,2c5,4e.5,4d.5,4f5,1g5,2d6,2g6,1g6,1d6,4c5,4d5,4c5,4b4,1c5,4d5,4e5,4d5,4f#5,1g5";
            std::string title_song = "title_song:d=8,o=7,b=120:4d.5,b4,4b4,4d5,2c.5,4d#5,4d.5,g4,4g4,4d5,4d#.5,p,4g#.5,p,16g4,p,16a4,2b4,4g4,16c5,p,16d5,2e5,4c5,16b4,p,16c5,2b4,4a4,16a4,p,16b4,4c.5,4e5,f#5,16g6,3d5,b4,4d5,4b4,4c.5,4f.5,4c5,4d.5,16d#5,16e5,4f.5,16e5,16d#5,2d5,6c5,6b4,6c5,4d.5,b4,4d5,4b4,c5,4d5,e5,6e5,6e5,6c5,2b4,6f5,6e5,6c5,2d5,p,b4,c5,d5,4d.5,b4,4d5,4b4,4c.5,4f.5,4c5,4d.5,16d#5,16e5,4f.5,16e5,16d#5,2d5,6c5,6b4,6c5,4d.5,b4,4d.5,g5,6a5,6g5,6f5,4f5,4e5,4d.5,f5,g5,4d5,g5,g4,b4,d5,g5,f5,a5,c6,f6,4d.6,4c.6,4a#5,16f5,16e5,16d5,16e5,4f5,4d6,4f6,4e.6,g5,6a5,6g5,6f5,2g5,4c6,4c#6,16d6,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,6c6,6c6,6c#6,16d6,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,6c6,6c6,6c#6,16d6,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,16d4,16p,16d4,16a3,6e5,6e5,6c5,1d5,p,1c5,p,1b4,p,2c5,2b4,2d5,2b4,2c5,2f5,2a5,4g.5,16g5,16f#5,2f5,2e5,1d.5,2p,16g4,p.,16g4,3p,16g4,16g4,16g4,p.,16g4,p.,16g4,p.,16a4,48p,16a4,48p,16a4,48p,16a4,48p,16a4,48p,16f#4,48p,16g4,p.,16g3";
            std::string town1_song = "town1_song:d=8,o=7,b=120:4e6,4c6,4d6,4b5,c6,b5,a5,b5,4g.5,16g5,16g#5,4a5,4c6,a5,a6,g6,f6,e6,f6,g6,e6,2d6,e6,g5,c6,g5,p,d6,g5,b5,g5,p,c6,p,b5,p,a5,p,b5,p,g5,b4,p,4p,16g5,16p,16g#5,16p,a5,c5,c6,c5,p,a5,p,a6,p,g6,p,f6,p,g6,p,a6,p,b6,p,c,2d,4c.,4p.";
        
            if (time() > 1500) {
                switch (MainScene) {
                    case TITLE_SCREEN:
                    case LOAD_GAME:
                        play_rtttl(title_song);
                        break;
                    case NEW_GAME:
                        break;
                    case OVERWORLD:
                        play_rtttl(town1_song);
                        break;
                    case BATTLE:
                        play_rtttl(battle_song);
                        break;
                }
            }
        }
    }

    void startBattle() {
        changeSong = true;
        MainScene = BATTLE;
        transitionCounter = 0;
        transitionDone = false;
        sleep(300);
    }

    bool battleTransitionDone() {
        if (transitionDone) {
            return true;
        }

        pen(0,0,0);
        int8_t index, i, k = 0, l = 0, m = 15, n = 15;
        transitionCounter++;
        while (k < m && l < n) {
            if (index >= transitionCounter) {
                sleep(50);
                return false;
            }
            for (i = l; i < n; ++i) frect(k*8,i*8,8,8);
            k++;
            for (i = k; i < m; ++i) frect(i*8,(n-1)*8,8,8);
            n--;
            if (k < m) {
                for (i = n - 1; i >= l; --i) {
                frect((m-1)*8,i*8,8,8);
                }
                m--;
            }
            if (l < n) {
                for (i = m - 1; i >= k; --i) {
                    frect(i*8,l*8,8,8);
                }
                l++;
            }
            index++;
        }

        frect(0,0,120,120);
        sleep(150);
        transitionDone = true;
        return true;
    }
}