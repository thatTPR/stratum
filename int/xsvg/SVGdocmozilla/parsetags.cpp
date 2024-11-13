// //  Parse Element and Attribte dirs as well as their respective .1 ext files and generate appropiatte c code"
// //  Attribs
// // // ValueType
// // // DefaultValue 
// // // Animatable: yes | no

#include <iostream>
#include <filesystem>
#include <fstream>
#include "../../sformats/xml.hpp"
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <exception>
#include <stdexcept>
using namespace std;
namespace fs = std::filesystem
class XMLn{
    public:
    string name ;
    string val
    std::vector<XMLn> els;
    std::map<string,string> atrs;
    XMLn par ; 

    XMLn(XMLn element){
        // this->element = element
        
        // Initialize the member variables
        this->name = element.name  // Tag name (e.g., 'div', 'p')
        this->val = element.get_text(strip=true)  // Text content (without leading/trailing whitespace)
        // print(this->val)
        this->ats = element.attrs  // Attributes (as a dictionary)
        
        // Initialize the parent and children attributes
        this->par = element.parent if element.parent else None  // Parent element
        this->els = [](){ for (const auto child : element.children) this->els+= XMLn(child)}  // Recursively parse children
        return this
    };
    XMLn(std::string _name , std::map<std::string> _ats ,std::string _val): name(_name) , ats(_ats) , val(_val){};
    XMLn(std::string& s_){
        return xml_parse(s_);
    };
    bool operator==(XMLn& ob_, XMLn& ob ){
        if ((ob_.name == ob.name) and (ob_.val == ob.val )and (ob_.ats == ob.ats)) return true;
        return false 
    };
    void soft_neq_name_ats(XMLn _ob, XMLn ob){
        b_name = true
        b_ats = true
        try:
            b_name =ob.name == _ob.name
            for (const auto std::pair<std::string,std::string >& t : ob.ats  ){
                    b_ats = _ob.ats[k] == t.
        }
        catch (std::excpetion& e)  :
            std::cout<<"softneq excpetion:"<<e<<std::endl;
        return ((not b_name) and (not b_ats))
    };
    void soft_neq_name_ats_dict(_ob, name, at_dict){
        bool b_name = true
        bool b_ats = true
        try{
            b_name = _ob.name == name
            for (const auto k,v : at_dict  )
                b_ats= _ob.ats[k] == v
        }
        catch(const std::exception& e)
        {
            std::cerr << softneqif<<e.what() << '\n';
        }
        return b_name and b_ats
    };
    void get_val_rec_ex(XMLn element , bool(excl*)(XMLn)){
        for (c : element.els){
            std::string t = XMLn.get_val_rec_ex(c,excl)
            bool sneq  = false
            for (const auto s : excl ){
                print(f"{type(s)}")
                if ( XMLn.soft_neq_name_ats(c, s)) {
                    sneq = true
                    continue
                };
            };
            if (sneq){
                if (t){
                    std::cout<<t ;
                    return c.val?c.val:'' + t ;
                };
                else return c.val?c.val:''

            };
        };

    };
    void get_val_rec_ex_dict(XMLn& element , std::string& name , std::map<std::string, std::string>& dict):
        for (const auto c : element->els ){
            std::string t = c.get_val_rec_ex_dict(c,name, dict)
            bool sneq  = false
            for (const auto s : dict ){
                if  XMLn.soft_neq_name_ats_dict(c, name , dict ):
                    sneq = true
                    continue
            };
            if (sneq){
                if t{
                    std::cout<<t;
                    return c.val?c.val:'' + t;
                };
                else return c.val?c.val:'' + t;
             };
    };
    // void should_exclude(XMLn element,std::map<std::string,std::string> exclusions){
    //     //Check if an element should be excluded based on name and attributes.//
    //     if (exclusions.size == 0)
    //         return false
    //     for (auto const exclusion : exclusions){
    //         name_b = true
    //         attributes_b = true
    //         try:
    //             if isinstance(exclusion, dict):  // Ensure exclusions are dicts
    //                 name_b = exclusion.get("name") == element.name
    //                 attributes_b = all(element.ats.get(attr) == value for attr, value in exclusion.get("attributes", {}).items())
    //             if name_b and attributes_b:
    //                 return true
    //         except Exception as e : 
    //             print(f"Keynot found:{e}");};
    //     return false
    // }
    std::string get_val_rec( XMLn& element){
        std::vector<std::string> vec ;  
        // values.append(s)
        for (const auto c : element.els ){
            t = c.get_val_rec(c)
            if (t) {values+=return c.val?c.val:'' + t;}
            else values+=return c.val?c.val:'' + t;
        return values 
    };
    std::string get_values_rec_incl(XMLn& element, std::function<bool(XMLn&)> should_incl){
        
        if ((should_incl(element) )   and (element.ats["visited"] != "visited")){
            element.ats["visited"] = "visited"
            std::string values="";
            if(element.val){
                values+=element.val;
            };
            std::string v  = element.get_val_rec(element)
            if (v){
                values+=" " +v;
                std::cout<<"values appended";
            };
            // Recurse through child elements and collect their values
            for (const auto child : element.els ){
                std::string child_value = child.get_values_rec_incl(&child,should_incl);
                if (child_value){values+=child_value;}
            };
            return values
        };
        return ''
    };
    void get_values_rec_tree_incl(XMLn& element,std::function<bool(XMLn&)> should_incl){
        std::string values ="";
        element.ats["visited"] = "v";
        if (should_incl(element)){
            values+= " "+ this->get_values_rec_incl(element, should_incl);
        }
        else{
            for (const auto i : element.els  )
                values+=i.get_values_rec_tree_incl(i,should_incl);
            };
        return values
    };
    // void get_values_recursively(exclusions):
    //     // //Recursively collect values (text) from element and its children, excluding certain elements.//
    //     // Skip this element if it matches any exclusion criteria
    //     if (this->should_exclude(exclusions))
    //         return ''  // Skip this element

    //     // Collect the element's text if it has any
    //     std::string values;
    //     if (this->val) 
    //         values.append(this->val)

    //     // Recurse through child elements and collect their values
    //     for (const auto child : this->els ){
    //         child_value = child.get_values_recursively(exclusions)
    //         if child_value:
    //             values.append(child_value)
    //     };
    //     return values
    // };
    
    XMLn from_str(std::string& str){
        try{
            XMLn xl = XMLParse(str)
        }
        catch(const std::exception& e) {
            std::err<< XMLn parsing error: << e << std::endl;
        };
        return XMLn(x1)
    };
    XMLn& operator++(int){
        result = this->els[this->pos]
        this->pos += 1
        return result
        
    };
    XMLn& find(std::string& name){
        for (XMLn& el : this->els){
            if (el.name==name) return el;
        };
    };
    friend std::ostream& operator<<(std::ostream& os, const XMLn& n){
        os<< std::string( "name"+ this->name + "val="+this->val, "ats="+[this->ats](std::map<std::string,std::string> &n){std::string sum = "" ; for (const auto& s : n) sum+= s; return s}, ",els="+ [this->els](XMLn[]& n){ std::string sum="" ;for (const auto& s : n) sum+=s.repr(s); return sum}   ;;;
        return os ;
    };
};


void erase_dups(std::vector<std::string>& s){for (int i=0; i < s.size() ;  i++) {for(  int t = i+1 ; t<s.size();t++) if (s[i] == s[t]) s.erase(t); };   };
#define ERROR_MAP_CREATE_VECTORS_NOT_SAME_SIZE
template <typename T, typename Ts>
std::map<T,Ts> make_map(std::vector<T> ks, std::vector<Ts> vs){if (ks.size() != ts.size()) throw std::invalid_argument("Keys and values vectors must be the same size."); 
else { std::map<T,Ts> m;
    for(int i =0 ; i<ks.size() ; i++){ m[ks[i]] = vs[i]; }; };};
// Example usage
std::string src_dir_elem = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\Element'  // Directory to search for files (use \\ or raw string literals in Windows paths)
std::string target_file_elem = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\elem.hpp'  // Directory to write results to (use \\ or raw string literals in Windows paths)
 

std::string src_dir_attrib = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\Attribute'  // Directory to search for files (use \\ or raw string literals in Windows paths)
std::string target_file_attrib = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\attrib.hpp'  // Directory to write results to (use \\ or raw string literals in Windows paths)

// check_strings_in_files(src_dir_elem, target_file_elem_ev, event)
// check_strings_in_files(src_dir_elem, target_file_ev, event)

// in_last_two ['onabort','oncancel','oncanplay','oncanplay','oncanplaythrough','onchange','onchange','onclick','onclose','oncuechange','ondblclick','ondrag','ondrag','ondrag','ondrag','ondrag','ondrag','ondragend','ondragenter','ondragleave','ondragover','ondragstart','ondrop','ondurationchange','onemptied','onended','onerror','onerror','onfocus','onfocus','onfocus','oninput','oninvalid','onkeydown','onkeypress','onkeyup','onload','onload','onload','onload','onloadeddata','onloadedmetadata','onloadstart','onmousedown','onmouseenter','onmouseleave','onmousemove','onmouseout','onmouseover','onmouseup','onmousewheel','onpause','onplay','onplay','onplaying','onprogress','onratechange','onreset','onresize','onresize','onscroll','onscroll','onseeked','onseeking','onselect','onshow','onstalled','onsubmit','onsuspend','ontimeupdate','ontoggle','onvolumechange','onwaiting']
// Elements
const std::vector<std::string> Animation_elements = {"animate", "animateMotion", "animateTransform", "mpath", "set"};
const std::vector<std::string> Basic_shapes = {"circle", "ellipse", "line", "polygon", "polyline", "rect"};
const std::vector<std::string> Container_elements = {"a", "defs", "g", "marker", "mask", "missing-glyph", "pattern", "svg", "switch", "symbol"};
const std::vector<std::string> Descriptive_elements = {"desc", "metadata", "title"};
const std::vector<std::string> Filter_primitive_elements = {"feBlend", "feColorMatrix", "feComponentTransfer", "feComposite", "feConvolveMatrix", "feDiffuseLighting", "feDisplacementMap", "feDropShadow", "feFlood", "feFuncA", "feFuncB", "feFuncG", "feFuncR", "feGaussianBlur", "feImage", "feMerge", "feMergeNode", "feMorphology", "feOffset", "feSpecularLighting", "feTile", "feTurbulence"};
const std::vector<std::string> Font_elements = {"font", "font-face", "font-face-format", "font-face-name", "font-face-src", "font-face-uri", "hkern", "vkern"};
const std::vector<std::string> Gradient_elements = {"linearGradient", "radialGradient", "stop"};
const std::vector<std::string> Graphics_elements = {"circle", "ellipse", "image", "line", "path", "polygon", "polyline", "rect", "text", "use"};
const std::vector<std::string> Graphics_referencing_elements = {"use"};
const std::vector<std::string> Light_source_elements = {"feDistantLight", "fePointLight", "feSpotLight"};
const std::vector<std::string> Never_rendered_elements = {"clipPath", "defs", "linearGradient", "marker", "mask", "metadata", "pattern", "radialGradient", "script", "style", "symbol", "title"};
const std::vector<std::string> Paint_server_elements = {"linearGradient", "pattern", "radialGradient"};
const std::vector<std::string> Renderable_elements = {"a", "circle", "ellipse", "foreignObject", "g", "image", "line", "path", "polygon", "polyline", "rect", "svg", "switch", "symbol", "text", "textPath", "tspan", "use"};
const std::vector<std::string> Shape_elements = {"circle", "ellipse", "line", "path", "polygon", "polyline", "rect"};
const std::vector<std::string> Structural_elements = {"defs", "g", "svg", "symbol", "use"};
const std::vector<std::string> Text_content_elements = {"glyph", "glyphRef", "textPath", "text", "tref", "tspan"};
const std::vector<std::string> Text_content_child_elements = {"textPath", "tref", "tspan"};
const std::vector<std::string> Uncategorized_elements = {"clipPath", "cursor", "filter", "foreignObject", "script", "style", "view"};
const std::vector<std::string> elem_cat = {"Animation elements","Basic shapes","Container elements","Descriptive elements","Filter primitive elements","Font elements","Gradient elements","Graphics elements","Graphics referencing elements","Light source elements","Never-rendered elements","Paint server elements","Renderable elements","Shape elements","Structural elements","Text content elements","Text content child elements","Uncategorized element"};
const std::vector<std::string> elem_all = erase_dups( Animation_elements+Basic_shapes+Container_elements+Descriptive_elements+Filter_primitive_elements+Font_elements+Gradient_elements+Graphics_elements+Graphics_referencing_elements+Light_source_elements+Never_rendered_elements+Paint_server_elements+Renderable_elements+Shape_elements+Structural_elements+Text_content_elements+Text_content_child_elements+Uncategorized_elements );
const std::map<std::string,std::string> elem_cat_map =  make_map<std::string,std::vector<std::string>>(elem_cat , {Animation_elements,Basic_shapes,Container_elements,Descriptive_elements,Filter_primitive_elements,Font_elements,Gradient_elements,Graphics_elements,Graphics_referencing_elements,Light_source_elements,Never_rendered_elements,Paint_server_elements,Renderable_elements,Shape_elements,Structural_elements,Text_content_elements,Text_content_child_elements,Uncategorized_elements};);

// Attrs
const std::vector<std::string> Core_attributes = {"id","class","style","lang","tabindex","xml:lang","xml:space"]
const std::vector<std::string> Conditional_processing_attributes = {"requiredExtensions","requiredFeatures","systemLanguage"]
const std::vector<std::string> Generic_attributes = Core_attributes + Conditional_processing_attributes
const std::vector<std::string> XLink_attributes ={"xlink:href","xlink:type","xlink:role","xlink:arcrole","xlink:title","xlink:show","xlink:actuate"]
    // Note: All SVG presentation attributes can be used as CSS properties.
const std::vector<std::string> Presentation_attributes= {"alignment-baseline","baseline-shift","clip","clip-path","clip-rule","color","color-interpolation","color-interpolation-filters","color-rendering","cursor","d","direction","display","dominant-baseline","fill","fill-opacity","fill-rule","filter","flood-color","flood-opacity","font-family","font-size","font-size-adjust","font-stretch","font-style","font-variant","font-weight","glyph-orientation-horizontal","glyph-orientation-vertical","image-rendering","letter-spacing","lighting-color","marker-end","marker-mid","marker-start","mask","opacity","overflow","pointer-events","shape-rendering","stop-color","stop-opacity","stroke","stroke-dasharray","stroke-dashoffset","stroke-linecap","stroke-linejoin","stroke-miterlimit","stroke-opacity","stroke-width","text-anchor","text-decoration","text-rendering","transform","transform-origin","unicode-bidi","vector-effect","visibility","word-spacing","writing-mode"]
const std::vector<std::string> Filter_primitive_attributes = {"height","result","width","x","y"]
const std::vector<std::string> Transfer_function_attributes = {"type","tableValues","slope","intercept","amplitude","exponent","offset"]
const std::vector<std::string> Filters_attributes = Filter_primitive_attributes + Transfer_function_attributes
const std::vector<std::string> Animation_target_element_attributes ={"href"]
const std::vector<std::string> Animation_attribute_target_attributes = {"attributeType", "attributeName"]
const std::vector<std::string> Animation_timing_attributes = {"begin","dur","end","min","max","restart","repeatCount","repeatDur","fill" ]
const std::vector<std::string> Animation_value_attributes = {"calcMode", "values", "keyTimes", "keySplines", "from", "to", "by", "autoReverse", "accelerate", "decelerate"]
const std::vector<std::string> Animation_addition_attributes = {"additive", "accumulate"]
const std::vector<std::string> Animation_attributes = Animation_target_element_attributes+Animation_attribute_target_attributes+Animation_timing_attributes+Animation_value_attributes+Animation_addition_attributes

const std::vector<std::string> attr_cat = {"Core attributes","Conditional processing attributes","XLink attributes","Presentation attributes","Filter primitive attributes","Transfer function attributes","Animation attributes","Animation target element attributes","Animation attribute target attributes","Animation timing attributes","Animation value attributes","Animation addition attributes"]
const std::vector<std::string> attr_cat_cat = {"Generic_attributes","Filters_attributes", "Animation_attributes"]

const std::map<std::string,std::string> attr_cat_map = make_map<std::string,std::string>(attr_cat, {Core_attributes,Conditional_processing_attributes,Generic_attributes,XLink_attributes,Presentation_attributes,Filter_primitive_attributes,Transfer_function_attributes,Filters_attributes,Animation_target_element_attributes,Animation_attribute_target_attributes,Animation_timing_attributes,Animation_value_attributes,Animation_addition_attributes}))
const std::vector<std::string > attr_all = erase_dups(Generic_attributes + XLink_attributes + Presentation_attributes + Filters_attributes + Animation_attributes);


//     print(f"Results written to {target_file}")
// import re
// void remove_consecutive_duplicates(input_str, delimiters=r'">|;|:| '):
    // (\b\w+\b)([">|;:\s]+)(?=\1\b) $2



// void strip_tags(str):
//     between = str
//     between = between.replace('<code>', '')  // Fix: re-assign to 'between'
//     between = between.replace('</code>', '')  // Fix: re-assign to 'between'
//     between = between.replace('<strong>', '')  // Fix: re-assign to 'between'
//     between = between.replace('</strong>', '')  // Fix: re-assign to 'between'
//     between = between.replace('<em>', '')  // Fix: re-assign to 'between'
//     between = between.replace('</em>', '')  // Fix: re-assign to 'between'
//     between = between.replace('<a href="/en-US/docs/Web/SVG/Content_type//', '')
//     between = between.replace('<a href=\\"/en-US/docs/Web/SVG/Content_type//', '')  // Fix: re-assign to 'between'
//     between = between.replace('<ahref="/en_US/docs/Web/SVG/Attribute/', '')
//     between = between.replace('&lt;', '')
//     between = between.replace('&gt;', '')
//     between = between.replace('</a>' , '')


//     return between
// void proc_value(line, start, end):
//     start_pos = line.find(start)
//     end_pos = line.find(end, start_pos)
//     between_strings = line[start_pos + len(start):end_pos].strip()
//     between_strings = strip_tags(between_strings)
//     return between_strings
void check_elem_elem_and_attrs_with_values( string elem_dir,string target_file ,vector<string> elems,vector<string> attrs ,vector<string> elem_cats){
    vector<string> tag_elem = [&](){vector<string> tel={}; for (const auto& item : elems) tel+="&lt;" + item + "&gt;"; return tel};
    vector<string> tag_attr =  [&](){vector<string> tat={}; for (const auto& item : attrs) tel+="&lt;" + item + "&gt;"; return tat;};
    
    std::ofstream out(target_file);
        for (const auto file : fs::directory_iterator(elem_dir) ){
             if (file.is_directory()) {continue;} 
            else if (file.is_regular_file()) {std::cout << "File: " << entry.path().filename() << std::endl;}
            else {std::cout << "Other: " << entry.path().filename() << std::endl;continue;};
            string strings_found_in_file = {};
                try{
                    std::ifstream elem_file(file);
                        for (const auto line : elem_file ){
                            if 'id="attributes"' in line :
                                strings_found_in_file.append("attribs:{")
                                bod_end = false
                                while not bod_end:
                                    for (const auto tattr : attrs ){
                                        // (f"href=\"/en-US/docs/Web/SVG/Attribute/{tattr}\"><code>{tattr}</code>" in line or 
                                        // f"<code>{tattr}</code>" in line or f"<strong>{tattr}</strong>" in line 
                                        s = '\"'
                                        s = '<code>' + tattr + '</code>'
                                        b= false 
                                        ind = 0
                                        for (const auto char : line ){ //if  s in line
                                            if ind == len(s) - 1 :
                                                b = true
                                                break
                                            if char == s[ind] :
                                                ind+=1
                                            else : 
                                                ind = 0
                                        if b:
                                            // print(f"{tattr}")
                                            // Process value types and other attributes
                                            // print(f"at_{tattr}:")
                                            strings_found_in_file.append(f"&at_{tattr}::Vals::")
                                            
                                            for (const auto line : elem_file ){
                                                // if '</dd>' in line:
                                                //     break  // Exit loop when '</dd>' is found
                                                if 'Value type' in line:
                                                    between_strings = proc_value(line, 'Value type', '</p>')
                                                    
                                                    // print(f"{between_strings};")
                                                    strings_found_in_file.append(f"Valuetype: {between_strings}; :: ")
                                                    // print(f"Value{line}")
                                                    // print(f"{between_strings}")
                                                    break;
                                                
                                                // if 'Default value' in line:
                                                    // between_strings = proc_value(line, 'Default value', ';')
                                                    // print(f"Default{line}")
                                                    // print(f"{between_strings}")
                                                    // print(f"Default:{between_strings};")
                                                    // strings_found_in_file.append(f"Default:{between_strings};")
                                                // if 'Animatable' in line:
                                                    // between_strings = proc_value(line, 'Animatable', '</strong>')
                                                    // print(f"Animatable{line}")
                                                    // print(f"{between_strings}")
                                                    // print(f"Animatable:{between_strings};")
                                                    // strings_found_in_file.append(f"Animatable:{between_strings};;")
                                    if '</div></section>' in line:
                                        print("Found Attrib list end ---------------------------------")
                        
                                        bod_end = true
                        };
                        elem_file.seek(0)
                        for (const auto line : elem_file ){
                            if 'Permitted content' in line:
                                strings_found_in_file.append('elems:{')
                                tbody_end = false 
                                
                                for (const auto line : elem_file ){
                                    for (const auto el_cat : elem_cats ){
                                        if el_cat in line:
                                            print(f"el_{el_cat}")
                                            strings_found_in_file.append(f"&el_{el_cat}, ")
                                    
                                    for (const auto tag_el : tag_elem ){
                                        if tag_el in line:
                                            out = tag_el.replace('&lt;','')
                                            out = out.replace('&gt;','')
                                            print(f"el_{out}")
                                            strings_found_in_file.append(f"&el_{out}, ")
                                    
                                    if '</tbody>' in line:
                                        tbody_end = true
                                        strings_found_in_file.append('}')
                                    if tbody_end:
                                        break  // End the inner loop if tbody_end is true
                        ]   
                        strings_found_in_file.append('\n')             
                    if strings_found_in_file:

                        print(f"Filename: {file_path}\n")
                        print(f"[{', '.join(strings_found_in_file)}]\n\n")
                        // output_file.write(f"Filename: {file_path}\n")
                        // output_file.write(f"[{', '.join(strings_found_in_file)}]\n\n")
                }
                catch (std::exception& e){
                    print(f"Could not process file {file_path}: {e}\n\n")
                    // output_file.write(f"Could not process file {file_path}: {e}\n\n")
                }
        }
};

void check_attrs_elem_with_values(string attr_dir, string target_file,vector<string> elems ,vector<string> attrs  ){
    // Open the output file for writing
    // Get all el
    std::ofstream out(target_file);
        for (const auto file : fs::directory_iterator(elem_dir) ){
             if (file.is_directory()) {continue;} 
            else if (file.is_regular_file()) {std::cout << "File: " << entry.path().filename() << std::endl;}
            else {std::cout << "Other: " << entry.path().filename() << std::endl;continue;};
            string strings_found_in_file = {};
                try{
                    std::ifstream attr_file(file);
                        for (const auto line : elem_file ){
        // Get all files in the source directory
                        bool arti = false
                        string lines = {};
                        std::string line ;
                        while(attr_file.getline( line){  // Loop until end of file
                            // Check for each string in the tag_elem list
                            size_t pos
                            if (pos = line.find("<article")){
                                std::cout<<file_name <<";\n";
                                arti = true;
                                // print(f"found article: {line[t:]}\n")
                                lines += line.substr(pos,line.size()-pos);
                                continue
                            };
                            if (pos = line.find("</article")){
                                // print(f"found close article:{line[:t+len('</article>')]}\n")
                                lines += line.substr(0,pos+sizeof("</article>"));
                                arti= false
                                break      ;
                            };
                            if (arti == true){
                                lines+=line;
                            };
                        };
                        s +=lines;
                        cout<<s.substr(0,40)<<"\n"<< s.substr(s.length()-40,s.length());                        
                        // print(s)
                        XMLn xl(s) ;
                        XMLn article= xl.find("article");
                        std::vector<XMLn&> elems ; 
                        std::string vals;
                        // elems=XMLn.get_values_rec(child , [](XMLn& e): { return (("elements" or "example" or"code-example" in e.ats.values()) or (e.name ==  "p")) ) };
                        try {                                                              // ( any("/en-US/docs/Web/SVG/Element/" in s for s in e.ats.values()) or and (e.name =="a") )  ( e.ats.get("class")=="table-container") and (e.name =="figure"))   ((e.ats.get("class")=="properties") and (e.name =="table") )   
                            vals=XMLn.get_values_rec_tree_incl(xl , [](std::XMLn& e){(return e.ats["class"]=="properties") } // Make lambda list
//                         elems=XMLn.get_values_rec_incl(xl , lambda e:  ( ("/en-US/docs/Web/SVG/Element/" in s for s in e.ats.values()) or (e.val ==  "Value" or "Default Value" or "Animatable")) )
                        }
                        catch( std::exception e) {
                            print(f"exception:{e}")
                        //for (const auto child : xl.els  ){
                        //    print("Entered children")
                        //    try{  //"aria-labelledby":"elements","aria-labelledby":"example"
                        //            void condition(e):
                        //                return (("elements" or"example"or"code-example" in e.ats.values()) or (e.name ==  "p"))
                        //            // elems=XMLn.get_values_rec(child , lambda e: (("elements" or "example" or"code-example" in e.ats.values()) or (e.name ==  "p")) )
                        //            // elems+=child.val
                        //            print(elems)
                        //    }  
                        /// catch( std::exception e) {std::err<<e }
 

                        }

                         out<<"Filename:"<< file<<"\n";
                        cout<<"Filename:"<< file<<"\n";
                         out<<vals<<"\n";
                        cout<<vals<<"\n";

                except Exception as e:
                    print(f"{file_name}: {e}\n\n")
                    // output_file.write(f"{file_name}: {e}\n\n")

        print(f"Results written to {target_file}")
};
// void get_attrs_value(src_dir , target_file) :
string _elem_attribs = target_file_elem + "attrs";
string _elem_elems = target_file_elem + "elems";
string _attrib_attribs = target_file_attrib + "attrs";
string _attrib_elems = target_file_attrib + "elems";


int main(){
    // dir_file_no(src_dir_elem)
    // check_strings_in_files(src_dir_elem, _elem_attribs, attr_cat + attr_cat_cat+ [ '&lt;'+item+'&gt;' for item in attr_all]  )
    // check_attrs_elem_with_values(src_dir_attrib, src_dir_elem, _attrib_elems , elem_all , attr_all)

    // void check_attrs_elem_with_values(attr_dir, elem_dir, target_file, elems , attrs  ):
    // void check_elem_elem_and_attrs_with_values( elem_dir, target_file , elems, attrs , elem_cats):

    // check_elem_elem_and_attrs_with_values(src_dir_elem, _elem_elems , elem_all , attr_all , elem_cat )
    check_attrs_elem_with_values(src_dir_attrib,_attrib_elems, elem_all , attr_all)

};


