#ifndef ACQRES_VALUES_HPP
#define ACQRES_VALUES_HPP
int isdigit(int __ch) {
  return (__ch >= '0' && __ch <= '9');
}
 int32_t num(std::string& line, uint& ind){
            bool neg=false;
            int32_t num=0;if(line[i-1]=='-'){neg=true;}
            for(;isdigit(line[ind]);ind++){
                num*=10;num+=line[ind]-0;
            };
            if(neg){num=-num;}
            return num;
        } ; 
float val(std::string& line,uint& ind){int n;float pt;
    n=num(line,i);pt=n;
    if(line[i] == '.'){i++;n=num(line,i);
                        float fr = n;
                        while(fr>1){fr/=10;}
                        pt=pt+fr;
    }
    return pt;
}

#endif