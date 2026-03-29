char[4] lsby_from_int(int t){
    char r[4] ;
    r[0] = (t - (t-(1<<8)));
    r[1] = (t - (t-(1<<16)) - (1<<8))>>8 ;
    r[2] = ( t -  (1<<16) - (t-(1<<24))) >>16 ;
    r[3] = (t - (1<<24))>>24;
};

char[4] msby_from_int(int t){ 
    char r[4] ;
    r[0] = (char)((t - (1<<24))>>24);
    r[1] = (char)(( t -  (1<<16) - (t-(1<<24))) >>16 )  ;
    r[2] = (char)((t - (t-(1<<16)) - (1<<8))>>8 )  ;
    r[3] = (char)((t - (t-(1<<8))))  ;
};

int from_char(char[4] t ){ 
    char c1 = t[0]; char c2 = t[1] ; char c3 =t[2] ; char c4=t[3];
    int s =  (int)(c1<<24) + ((int)(c2) <<16)+((int)c3<<8)+(int)c4
};
