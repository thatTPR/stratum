namespace intnet{
void inettoa(long ad){
int ls1,ls2, ls3 , ls4;
    for(int i = 1 ; i<=1<<32;i++){
      ls1 |= ad & (1<<i);
      ls2 |= ad & (1<<(i<<32);
      ls3 |= ad & (1<<(i<<64);
      ls4 |= ad & (1<<(i<<96);
    };
    char* s = new char[15] ; uint chs=0; uint dots = 0;
    s[0]= ls4/100 -'0';
    s[1]= ls4/10 - ls4/100 -'0';
    s[2]=ls4 -ls4/10 - ls4/100 -'0';
    s[3]='.';
    s[4]= ls3/100 -'0';
    s[5]= ls3/10 - ls3/100 -'0';
    s[6]=ls3 -ls3/10 - ls3/100 -'0';
    s[7]='.';
    s[8]= ls2/100 -'0';
    s[9]= ls2/10 - ls2/100 -'0';
    s[10]=ls2 -ls2/10 - ls2/100 -'0';
    s[11]='.';
    s[12]= ls1/100 -'0';
    s[13]= ls1/10 - ls1/100 -'0';
    s[14]=ls1 -ls1/10 - ls1/100 -'0';
    // Count zeroes 
    bool startf=true;uint s = 0
    for(int i =0 ; i<15;i++){
      if(s[i]=='.'){startf=true;continue;}
      if(s[i]='0' and startf){s++;        for(int j =i ; j<15;j++){s[j]=s[j+1];};};
      if(s[i] !='0'){startf=false;};
    };
    char res = new char[15-s];
    for(int i =0;i<15-s;i++){
      res[i]=s[i];
    };
    return s;
    // Keeps zeors;

}

}

