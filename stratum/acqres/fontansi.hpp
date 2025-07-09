#include <int/ansicode.hpp>
#include <cstdint>
#include <glm/vec3.hpp>
enum flagSgr {
    bold=0x1,      //Bit 1
    italic=0x2,    //Bit 2
    underline=0x4, //Bit 3
    crossed=0x8,    //Bit 4
    conceal=0x10,  //Bit 5
    faint=0x11 // bit 5 and 1
};

typedef struct {
    uint8_t format;
    glm::uvec3 bg;
    glm::uvec3 fg;
}ansiFormat;
glm::vec3 ansi_rgb_0_15[16] = {
    {0, 0, 0}, {128, 0, 0}, {0, 128, 0}, {128, 128, 0},
    {0, 0, 128}, {128, 0, 128}, {0, 128, 128}, {192, 192, 192},
    {128, 128, 128}, {255, 0, 0}, {0, 255, 0}, {255, 255, 0},
    {0, 0, 255}, {255, 0, 255}, {0, 255, 255}, {255, 255, 255}
};


uint ansi_levels[6] = {0, 95, 135, 175, 215, 255};
glm::uvec3 ansi_256_to_rgb(uint8_t& code){
    if ((16 <= code)and( code <= 231)){
        code -= 16;
        r = code ;// 36;
        g = (code % 36); // 6;
        b = code % 6;
        return (ansi_levels[r], ansi_levels[g], ansi_levels[b])
    }
    else if(( 232 <= code)and(code <= 255)){
        uint gray = 8 + (code - 232) * 10;
        return {gray, gray, gray};
    }
    else return ansi_16_to_rgb(code)  ;// fallback
};
uint8_t rgb_to_ansi_256(glm::uvec3 v){
    # Convert grayscale
    if (v.r == v.g and(v.g ==v.b)){
        if (r < 8)return 16;
        if (r > 248)return 231;
        return 232 + (r - 8); };// 10

    auto closest = [&](uint8 x){
        int best = 0;
        int smallest_diff = abs(ansi_levels[0] - value);
        for (int i = 1; i < 6; ++i) {
            int diff = abs(ansi_levels[i] - value);
            if (diff < smallest_diff) {
                best = i;
                smallest_diff = diff;
            };
        }
        return best;
    };
    int r_idx = closest(r);
    int g_idx = closest(g);
    int b_idx = closest(b);
    return 16 + 36 * r_idx + 6 * g_idx + b_idx;};

    typedef struct {
std::string str;
ansiFormat* fs;
}formatStr;
formatStr ansiStrip(std::string s){
    formatStr fstr;
    ansiFormat formatCur;
    std::vector<ansiFormat> f;
    for(int i=0;i<s.size();i++){
        if(s[i]==0x98){
            switch(s[i+1]){
                case SG_reset :{};
                case SG_bold :{formatCur.format |= flagSgr::bold; i=+2; break;};
                case SG_faint :{formatCur.format |= flagSgr::faint;i+=2; break;};
                case SG_italic :{formatCur.format |= flagSgr::italic;i+=2; break;};
                case SG_underline :{formatCur.format |= flagSgr::underiline;i+=2; break;};
                case SG_conceal :{formatCur.format |= flagSgr::conceal;i+=2; break;};
                case SG_crossed :{formatCur.format |= flagSgr::crossed;i+=2; break;};
                case SG_bold_off :{formatCur.format ^= flagSgr::bold;i+=2; break;};
                case SG_normal_intensity :{formatCur.format ^= flagSgr::faint;i+=2; break;};
                case SG_italic_off :{formatCur.format ^= flagSgr::italic;i+=2; break;};
                case SG_underline_off :{formatCur.format ^= flagSgr::underline;i+=2; break;};
                default : {
                    if(s[i+1]==38){
                        if(s[i+3]==5){
                            formatCur.fg=ansi_256_to_rgbs(static_cast<uint>(s[i+5]));
                            i+=6;}
                        else if(s[i+3]==2){
                            formatCur.fg=glm::uvec3(static_cast<uint>(s[i+5]),static_cast<uint>(s[i+7]),static_cast<uint>(s[i+9]))
                            i+=9;
                        }
                    }
                    if(s[i+1]>=30 and s[i+1]<=37 ){
                        formatCur.fg= ansi_rgb_0_15[s[i+1]-30];
                        i+=2;
                    };
                    if(s[i+1]==48){
                        if(s[i+3]==5){
                            formatCur.bg=ansi_256_to_rgbs(static_cast<uint>(s[i+5]));
                            i+=6;}
                        else if(s[i+3]==2){
                            formatCur.bg=glm::uvec3(static_cast<uint>(s[i+5]),static_cast<uint>(s[i+7]),static_cast<uint>(s[i+9]))
                            i+=9;
                        }
                    }
                    if(s[i+1]>=40 and s[i+1]<=47 ){
                        formatCur.bg= ansi_rgb_0_15[s[i+1]-40];
                        i+=2;
                    };
                }
            }
        };
        else {fstr.s+=s[i];f.push_back(formatCur);};
        
    };
};