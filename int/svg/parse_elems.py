import os
import shutil

elems_cpp = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\svg_tags_elems.cpp'
vals = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\svg_values.cpp'
def parse_elems(target_file, src_file  ):
    with open(target_file ,'w', encoding= 'utf-8') as output_f:
        print('File opened')
        with open(src_file, 'r' , encoding = 'utf-8') as input_f:
            print('File opened')
            val_ts = []
            def_val = []
            for line in input_f:
                print(f"{line}")
                if 'attrs' in line :
                    print('attrs found')
                    ind = []
                    ind_s = 0
                    for index, char in enumerate(line):
                        if char == '{':
                            print("Opening brace '{' found")
                            ind.append([index, 0])  # Append a new pair [start_index, 0]
                            ind_s += 1
                        elif char == '}':
                            i = len(ind) - 1
                            while i >= 0:
                                # Ensure that ind[i] has two elements and the second element is 0
                                if len(ind[i]) == 2 and ind[i][1] == 0:
                                    ind[i][1] = index  # Set the end index
                                break
                            i -= 1                             
                    
                    for inds , tagp in enumerate(ind) :
                        if inds== 0 :
                            continue
                        print("{tagp[0]} , {tagp[1]}")
                        if not(( ind[inds-1][0] < ind[inds][0]  ) and (ind[inds-1][1]> ind[inds][1]) ):
                            if inds == (ind_s -1) : 
                                continue
                            attr = line[ind[inds-1][0] +1 : ind[inds-1][1] - 1]
                            attr = attr.split(",")
                            if len(attr) > 2:
                                def_val.append(attr[2])
                                print(attr[2])

                        else :
                            value_t = line[ind[inds-1][0] +1 : ind[inds-1][1] - 1]
                            value_t =  value_t.split(",")
                            value_t = [t.replace(' ', '') for t in value_t]
                            val_ts = val_ts+value_t
                            print(value_t)
          
           
            for valind,val in enumerate(val_ts) :
                for vi , vl in enumerate(val_ts):
                    if vi == valind :
                        continue
                    if vl == val :
                       val_ts[vi] = ''
            for valind,val in enumerate(def_val) :
                for vi , vl in enumerate(def_val):
                    if vi == valind :
                        continue
                    if vl == val :
                        def_val[vi] = ''
            output_f.write("valtypes:")
            output_f.write(f"[{', '.join(val_ts)}\n")
            output_f.write("defaults:")
            output_f.write(f"[{', '.join(def_val)}\n")
            
parse_elems(vals,elems_cpp)




