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
#include <exception>
#include <stdexcept>
std::vector<std::string> operator+(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs) {
    std::vector<std::string> result;

    // Add elements from the first vector (lhs)
    result.insert(result.end(), lhs.begin(), lhs.end());

    // Add elements from the second vector (rhs)
    result.insert(result.end(), rhs.begin(), rhs.end());

    return result;
};
using namespace std;
namespace fs = std::filesystem;

std::vector<std::string> erase_dups(std::vector<std::vector<std::string>> m)
{   
    std::vector<std::string> s ; 
    for(std::vector<std::string>& i : m ){
        for(std::string& it : i){
            s.push_back(it);
        };
    };
    for (size_t i = 0; i < s.size(); i++)
    {
        for (size_t t = i + 1; t < s.size();)
        {
            if (s[i] == s[t])
            {
                s.erase(s.begin() + t); // erase the duplicate at position t
            }
            else
            {
                ++t; // only increment if no erase, as erase shifts elements left
            }
        }
    };
    return s;
};
template <typename keysul, typename valuesul>
std::map<keysul, valuesul> make_map(std::vector<keysul> vec1, std::vector<valuesul> vec2)
{
    if (vec1.size() != vec2.size())
        throw std::invalid_argument("Keys and values vectors must be the same size.");
    else
    {
        std::map<keysul, valuesul> m;
        for (int i = 0; i < vec1.size(); i++)
        {
            m[vec1[i]] = vec2[i];
        };
        return m;
    };

};
std::vector<std::string> operator+(std::vector<std::string>& a, std::vector<std::string>& s){
    std::vector<std::string> val;
    for(auto& it : a){
        val.push_back(it);
    };
    for(auto& it : s){
        val.push_back(it);
    };

    return val;
};
// using make_str_map(std::string,) =  make_map<std::string,std::string>  ;
// Example usage
fs::path src_dir_elem = "C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\Element";      // Directory to search for files (use \\ or raw string literals in Windows paths)
fs::path target_file_elem = "C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\elem.hpp"; // Directory to write results to (use \\ or raw string literals in Windows paths)

fs::path src_dir_attrib = "C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\Attribute";      // Directory to search for files (use \\ or raw string literals in Windows paths)
fs::path target_file_attrib = "C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\attrib.hpp"; // Directory to write results to (use \\ or raw string literals in Windows paths)

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
const std::vector<std::string> elem_cat = {"Animation elements", "Basic shapes", "Container elements", "Descriptive elements", "Filter primitive elements", "Font elements", "Gradient elements", "Graphics elements", "Graphics referencing elements", "Light source elements", "Never-rendered elements", "Paint server elements", "Renderable elements", "Shape elements", "Structural elements", "Text content elements", "Text content child elements", "Uncategorized element"};
const std::vector<std::string> elem_all = erase_dups({Animation_elements, Basic_shapes , Container_elements , Descriptive_elements , Filter_primitive_elements , Font_elements , Gradient_elements , Graphics_elements , Graphics_referencing_elements , Light_source_elements , Never_rendered_elements , Paint_server_elements , Renderable_elements , Shape_elements , Structural_elements , Text_content_elements , Text_content_child_elements , Uncategorized_elements});
// const std::map<std::string,std::string> elem_cat_map =  make_map<std::string,std::vector<std::string>>(elem_cat , {Animation_elements,Basic_shapes,Container_elements,Descriptive_elements,Filter_primitive_elements,Font_elements,Gradient_elements,Graphics_elements,Graphics_referencing_elements,Light_source_elements,Never_rendered_elements,Paint_server_elements,Renderable_elements,Shape_elements,Structural_elements,Text_content_elements,Text_content_child_elements,Uncategorized_elements});

// Attrs
const std::vector<std::string> Core_attributes = {"id", "class", "style", "lang", "tabindex", "xml:lang", "xml:space"};
const std::vector<std::string> Conditional_processing_attributes = {"requiredExtensions", "requiredFeatures", "systemLanguage"};
const std::vector<std::string> Generic_attributes = erase_dups({Core_attributes , Conditional_processing_attributes});
const std::vector<std::string> XLink_attributes = {"xlink:href", "xlink:type", "xlink:role", "xlink:arcrole", "xlink:title", "xlink:show", "xlink:actuate"};
// Note: All SVG presentation attributes can be used as CSS properties.
const std::vector<std::string> Presentation_attributes = {"alignment-baseline", "baseline-shift", "clip", "clip-path", "clip-rule", "color", "color-interpolation", "color-interpolation-filters", "color-rendering", "cursor", "d", "direction", "display", "dominant-baseline", "fill", "fill-opacity", "fill-rule", "filter", "flood-color", "flood-opacity", "font-family", "font-size", "font-size-adjust", "font-stretch", "font-style", "font-variant", "font-weight", "glyph-orientation-horizontal", "glyph-orientation-vertical", "image-rendering", "letter-spacing", "lighting-color", "marker-end", "marker-mid", "marker-start", "mask", "opacity", "overflow", "pointer-events", "shape-rendering", "stop-color", "stop-opacity", "stroke", "stroke-dasharray", "stroke-dashoffset", "stroke-linecap", "stroke-linejoin", "stroke-miterlimit", "stroke-opacity", "stroke-width", "text-anchor", "text-decoration", "text-rendering", "transform", "transform-origin", "unicode-bidi", "vector-effect", "visibility", "word-spacing", "writing-mode"};
const std::vector<std::string> Filter_primitive_attributes = {"height","result","width","x","y"};
const std::vector<std::string> Transfer_function_attributes = {"type","tableValues","slope","intercept","amplitude","exponent","offset"};
const std::vector<std::string> Filters_attributes = erase_dups({Filter_primitive_attributes , Transfer_function_attributes});
const std::vector<std::string> Animation_target_element_attributes = {"href"};
const std::vector<std::string> Animation_attribute_target_attributes = {"attributeType", "attributeName"};
const std::vector<std::string> Animation_timing_attributes = {"begin", "dur", "end", "min", "max", "restart", "repeatCount", "repeatDur", "fill"};
const std::vector<std::string> Animation_value_attributes = {"calcMode", "values", "keyTimes", "keySplines", "from", "to", "by", "autoReverse", "accelerate", "decelerate"};
const std::vector<std::string> Animation_addition_attributes = {"additive", "accumulate"};
const std::vector<std::string> Animation_attributes = erase_dups({Animation_target_element_attributes , Animation_attribute_target_attributes , Animation_timing_attributes , Animation_value_attributes , Animation_addition_attributes});

const std::vector<std::string> attr_cat = {"Core attributes", "Conditional processing attributes", "XLink attributes", "Presentation attributes", "Filter primitive attributes", "Transfer function attributes", "Animation attributes", "Animation target element attributes", "Animation attribute target attributes", "Animation timing attributes", "Animation value attributes", "Animation addition attributes"};
const std::vector<std::string> attr_cat_cat = {"Generic_attributes", "Filters_attributes", "Animation_attributes"};

// const std::map<std::string,std::string> attr_cat_map = make_map<std::string,std::string>(attr_cat, {Core_attributes,Conditional_processing_attributes,Generic_attributes,XLink_attributes,Presentation_attributes,Filter_primitive_attributes,Transfer_function_attributes,Filters_attributes,Animation_target_element_attributes,Animation_attribute_target_attributes,Animation_timing_attributes,Animation_value_attributes,Animation_addition_attributes}));
const std::vector<std::string> attr_all = erase_dups({Generic_attributes ,XLink_attributes , Presentation_attributes , Filters_attributes , Animation_attributes});

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
void check_elem_elem_and_attrs_with_values(fs::path elem_dir, fs::path target_file, vector<string> elems, vector<string> attrs, vector<string> elem_cats)
{
    // vector<string> tag_elem = [&]()
    // {vector<string> tel={}; for (const auto& item : elems) tel+="&lt;" + item + "&gt;"; return tel };
    // vector<string> tag_attr = [&]()
    // {vector<string> tat={}; for (const auto& item : attrs) tel+="&lt;" + item + "&gt;"; return tat; };

    std::ofstream fout(target_file);
    for (const auto file : fs::directory_iterator(elem_dir))
    {
        if (file.is_directory())
        {
            continue;
        }
        else if (file.is_regular_file())
        {
            std::cout << "File: " << file.path().filename() << std::endl;
        }
        else
        {
            std::cout << "Other: " << file.path().filename() << std::endl;
            continue;
        };
        std::ifstream elem_file(file.path());

        string strings_found_in_file = "";
        try
        {
            if (strings_found_in_file.length() > 10){
                        std::cout<<"Filename: "<<file<<"\n";
                        std::cout<<strings_found_in_file<<std::endl;
                        fout<<"Filename: "<<file<<"\n";
                        fout<<strings_found_in_file<<std::endl;
            }
        }
        catch (std::exception &e)
        {
            std::cout << "Could not process file" << e.what() << "\n\n";
            // output_file.write(f"Could not process file {file_path}: {e}\n\n")
        }
    }
};


void check_attrs_elem_with_values(fs::path attr_dir, fs::path target_file, vector<string> elems, vector<string> attrs)
{
    // Open the output file for writing
    // Get all el
    std::cout<<attr_dir<<" ";
    std::cout<<"Accessing target file\n"<<target_file<<std::endl;
    std::ofstream out(target_file);
    for (const auto file : fs::directory_iterator(attr_dir))
    {
        if (file.is_directory()){continue;}
        else if (file.is_regular_file())
        {
            std::cout << "File: " << file.path().filename() << std::endl;
        }
        else
        {
            std::cout << "Other: " << file.path().filename() << std::endl;
            continue;
        };
        string strings_found_in_file = {};
        std::ifstream attr_file(file.path());
        if(!attr_file){
            std::cerr<< "error opening file";
        }
        try
        {
            std::string lines ;
            std::string line;
            bool arti = false; 
            while(std::getline(attr_file, line)){  // Loop until end of file
                // Check for each string in the tag_elem list
                size_t pos = line.find("<article");
                if (pos !=std::string::npos)
                {
                    arti = true;
                    // print(f"found article: {line[t:]}\n")
                    lines += line.substr(pos, line.size() - pos);
                    continue;
                };
                pos = line.find("</article");
                if (pos != std::string::npos)
                {
                    lines += line.substr(0, pos + sizeof("</article>")-1);
                    arti = false; break;
                };
                if (arti == true)
                {
                    lines += line;
                };
            };
            // cout<<lines.substr(0,40)<<" ... "<<lines.substr(lines.length()-40,lines.length());// Print lines start and line end                 
            // Get all files in the source directory
            // print(s)

            xml::xml_parse parser(xml::xml) ;
            xml::xmln xl =parser.from_str(lines);
            std::cout<<xl.name<<" ";
            std::cout<<std::endl<<xl<<xl.els.front().name;
            // std::cout<<xl.els.front().name << " \n";
            std::vector<xml::xmln*> article= xl.bfs_all([](xml::xmln* n){return n->name=="article";});
            
            std::vector<xml::xmln> elems ; 
            std::string vals;
            try {                                                              
                xml::xmln* elem;
                for (int i=0;i<article.size();i++)
                {// ( at_exists = false ;for(const auto pair : e.atrs){if("/en-US/docs/Web/SVG/Element/" == pair.second){at_exists =true ; break;};  return( at_exists and (e.name =="a") }  { return ((e.ats["class"]=="table-container") and (e.name =="figure")) ;}  {return (e.ats["class"]=="properties") and (e.name =="table"); }
                    elem = article[i];
                    std::cout<<elem->name<<":";
                    auto condition = [](xml::xmln* e) -> bool { return (e->ats["class"] == "properties") ;};
                    std::vector<xml::xmln*> s= elem->bfs_all(condition );
                    std::vector<xml::xmln*> vec ; 
                    // std::vector<xml::xmln*> s= elem->bfs_all( "" , make_map<std::string,std::string>({"class"},{"properties"} ));
                    xml::xmln* t;
                    for(int it =0;it<s.size();it++){t = (s[it]);

                        std::vector<xml::xmln*> res =t->dfs_all() ;
                        vec.insert(vec.end(), res.begin(), res.end());
                    };
                }
                // elems=XMLn.get_values_rec(child , [](XMLn& e): { return (("elements" or "example" or"code-example" in e.ats.values()) or (e.name ==  "p")) ) };
                

                //                         elems=XMLn.get_values_rec_incl(xl , lambda e:  ( ("/en-US/docs/Web/SVG/Element/" in s for s in e.ats.values()) or (e.val ==  "Value" or "Default Value" or "Animatable")) )
            }
            catch( std::exception& e) {
                std::cout << "exception:{" << e.what() << std::endl;
                // for (const auto child : xl.els  ){
                //     print("Entered children")
                //     try{  //"aria-labelledby":"elements","aria-labelledby":"example"
                //             void condition(e):
                //                 return (("elements" or"example"or"code-example" in e.ats.values()) or (e.name ==  "p"))
                //             // elems=XMLn.get_values_rec(child , lambda e: (("elements" or "example" or"code-example" in e.ats.values()) or (e.name ==  "p")) )
                //             // elems+=child.val
                //             print(elems)
                //     }
                /// catch( std::exception e) {std::cout<<e }
            }
            // out<<"Filename:"<< file.path().filename()<<"\n";
            std::cout<<"Filename:"<< file.path().filename()<<"\n";
            // out<<vals<<"\n";
            std::cout<<vals<<"\n";
        }
        catch (std::exception& e)
        {
            std::cout << file << ": " << e.what() << "\n\n";
            // output_file.write(f"{file_name}: {e}\n\n")
        };
    };
    std::cout << "Results written to " << target_file;
};
// void get_attrs_value(src_dir , target_file) :

int main(int argc, char **argv)
{

    // bool elems, atrs;
    // for (int i = 0; i < argc; i++)
    // {
    //     if (argv[i] == "elems"){
    //         elems = true;
    //         std::cout<<"Printing elems";
    //     }
    //     if (argv[i] == "atrs")
    //         atrs = true;
    //                     std::cout<<"Printing atrs";
    // };
    // dir_file_no(src_dir_elem)
    // check_strings_in_files(src_dir_elem, _elem_attribs, attr_cat + attr_cat_cat+ [ '&lt;'+item+'&gt;' for item in attr_all]  )
    // check_attrs_elem_with_values(src_dir_attrib, src_dir_elem, _attrib_elems , elem_all , attr_all)

    // void check_attrs_elem_with_values(attr_dir, elem_dir, target_file, elems , attrs  ):
    // void check_elem_elem_and_attrs_with_values( elem_dir, target_file , elems, attrs , elem_cats):

    // check_elem_elem_and_attrs_with_values(src_dir_elem, _elem_elems , elem_all , attr_all , elem_cat )
        check_attrs_elem_with_values(src_dir_attrib, target_file_attrib, elem_all, attr_all);
    
    
};
