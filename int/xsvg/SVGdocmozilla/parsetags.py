#  Parse Element and Attribte dirs as well as their respective .1 ext files and generate appropiatte c code"
#  Attribs
# // ValueType
# // DefaultValue 
# // Animatable: yes | no


import os
import shutil
# import xml.etree.ElementTree as ET
# import html.parser as htmlp

from bs4 import BeautifulSoup
        
class XMLp:
    def __init__(self, element):
        self.element = element
        
        # Initialize the member variables
        self.name = element.name  # Tag name (e.g., 'div', 'p')
        self.val = element.get_text(strip=True)  # Text content (without leading/trailing whitespace)
        # print(self.val)
        self.ats = element.attrs  # Attributes (as a dictionary)
        
        # Initialize the parent and children attributes
        self.par = element.parent if element.parent else None  # Parent element
        self.els = [XMLp(child) for child in element.children if isinstance(child, element.__class__)]  # Recursively parse children
    @classmethod
    def create(cls,na , _ats):
        element = ET.Element(na, _ats)
        return cls(element)
    def __iter__(self):
        self.pos = 0
        return self
    def __eq__(self, ob ):
        b_name = False
        b_at = True
        if self.name == ob.name :
            b_name = True
        if self.ats == ob.ats :
            b_at = True

    def soft_neq_name_ats(_ob,ob):
        b_name = True
        b_ats = True
        try:
            b_name =ob.name == _ob.name
            for k,v in ob.ats :
                    b_ats = _ob.ats[k] == v
        except Exception as e :
            print(f"softneqif: {e}")
        return (not b_name) and not b_ats

    def soft_neq_name_ats_dict(_ob, name, at_dict):
        b_name = True
        b_ats = True
        try:
            b_name = _ob.name == name
            for k,v in at_dict :
                b_ats= _ob.ats[k] == v
        except Exception as e :
            print(f"softneqif: {e}")
        return b_name and b_ats

    def get_val_rec_ex(element , *excl):
        for c in element.els:
            t = XMLp.get_val_rec_ex(c,excl)
            sneq  = False
            for s in excl:
                print(f"{type(s)}")
                if  XMLp.soft_neq_name_ats(c, s):
                    sneq = True
                    continue
            if sneq:
                if t:
                    print(f"{t}")
                    return (f"{c.val.strip() if c.val else ''}") + f"{t}"
                else :
                    return f"{c.val.strip() if c.val else ''}"
    def get_val_rec_ex_dict(element , name , dict):
        for c in element.els:
            t = XMLp.get_val_rec_ex_dict(c,name, dict)
            sneq  = False
            for s in dict:
                if  XMLp.soft_neq_name_ats_dict(c, name , dict ):
                    sneq = True
                    continue
            if sneq:
                if t:
                    print(f"{t}")
                    return (f"{c.val.strip() if c.val else ''}") + f"{t}"
                else :
                    return f"{c.val.strip() if c.val else ''}"

    @staticmethod
    def should_exclude(element, exclusions):
        """Check if an element should be excluded based on name and attributes."""
        if len(exclusions) == 0:
            return False
        for exclusion in exclusions:
            name_b = True
            attributes_b = True
            try:
                if isinstance(exclusion, dict):  # Ensure exclusions are dicts
                    name_b = exclusion.get("name") == element.name
                    attributes_b = all(element.ats.get(attr) == value for attr, value in exclusion.get("attributes", {}).items())
                if name_b and attributes_b:
                    return True
            except Exception as e : 
                print(f"Keynot found:{e}")
        return False
    
    def get_val_rec(element ):
        values = []
        # values.append(s)
        for c in element.els:
            t = XMLp.get_val_rec(c)
            if t:
                values.append( f"{c.val if c.val else ' '}" + ''.join(t)  )
            else :
                values.append( f"{c.val if c.val else ''}"  )
        return values 
    def get_values_rec_incl(element, should_incl ) :
        
        if ((should_incl(element) )   and (element.ats["visited"] != "visited")):
            element.ats["visited"] = "visited"
            values = []
            if element.val :
                values.append(element.val)

            v  = XMLp.get_val_rec(element)
            if v:
                values.append(''.join(v))
                print("values appended")
            # Recurse through child elements and collect their values
            for child in element.els:
                child_value = XMLp.get_values_rec_incl(child,should_incl)

                if child_value:
                    values.append(' '.join(child_value))

            return ''.join(values)
        return ''
    def get_values_rec_tree_incl(element,should_incl):
        values = []
        element.ats["visited"] = "v"
        if should_incl(element) :
            values.append(''.join( XMLp.get_values_rec_incl(element, should_incl)))
        else:
            for i in element.els :
                values.append( ''.join(XMLp.get_values_rec_tree_incl(i,should_incl)))
        return values
    def get_values_recursively(self, exclusions):
        """Recursively collect values (text) from element and its children, excluding certain elements."""
        # Skip this element if it matches any exclusion criteria
        if self.should_exclude(self, exclusions):
            return ''  # Skip this element

        # Collect the element's text if it has any
        values = []
        if self.val :
            values.append(self.val)

        # Recurse through child elements and collect their values
        for child in self.els:
            child_value = child.get_values_recursively(exclusions)
            if child_value:
                values.append(child_value)

        return ''.join(values)
    def from_str( str):
        try:
            xl = BeautifulSoup(str, "html.parser")
        except Exception as e:
            print(f"XMLp parsing error: {e}")
        return XMLp(x1)
    def __next__(self):
        if self.pos < len(self.els):
            result = self.els[self.pos]
            self.pos += 1
            return result
        else:
            raise StopIteration

    def __repr__(self):
        return f"XML(name={self.name}, val={self.val}, ats={self.ats}, els={self.els}) ;;;"


# Example usage
src_dir_elem = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\Element'  # Directory to search for files (use \\ or raw string literals in Windows paths)
target_file_elem = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\elem.hpp'  # Directory to write results to (use \\ or raw string literals in Windows paths)
 

src_dir_attrib = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\Attribute'  # Directory to search for files (use \\ or raw string literals in Windows paths)
target_file_attrib = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\attrib.hpp'  # Directory to write results to (use \\ or raw string literals in Windows paths)

# check_strings_in_files(src_dir_elem, target_file_elem_ev, event)
# check_strings_in_files(src_dir_elem, target_file_ev, event)

# in_last_two ['onabort','oncancel','oncanplay','oncanplay','oncanplaythrough','onchange','onchange','onclick','onclose','oncuechange','ondblclick','ondrag','ondrag','ondrag','ondrag','ondrag','ondrag','ondragend','ondragenter','ondragleave','ondragover','ondragstart','ondrop','ondurationchange','onemptied','onended','onerror','onerror','onfocus','onfocus','onfocus','oninput','oninvalid','onkeydown','onkeypress','onkeyup','onload','onload','onload','onload','onloadeddata','onloadedmetadata','onloadstart','onmousedown','onmouseenter','onmouseleave','onmousemove','onmouseout','onmouseover','onmouseup','onmousewheel','onpause','onplay','onplay','onplaying','onprogress','onratechange','onreset','onresize','onresize','onscroll','onscroll','onseeked','onseeking','onselect','onshow','onstalled','onsubmit','onsuspend','ontimeupdate','ontoggle','onvolumechange','onwaiting']
# Elements
Animation_elements = ['animate', 'animateMotion', 'animateTransform', 'mpath', 'set']
Basic_shapes = ['circle', 'ellipse', 'line', 'polygon', 'polyline', 'rect']
Container_elements = ['a', 'defs', 'g', 'marker', 'mask', 'missing-glyph', 'pattern', 'svg', 'switch', 'symbol']
Descriptive_elements = ['desc', 'metadata', 'title']
Filter_primitive_elements = ['feBlend', 'feColorMatrix', 'feComponentTransfer', 'feComposite', 'feConvolveMatrix', 'feDiffuseLighting', 'feDisplacementMap', 'feDropShadow', 'feFlood', 'feFuncA', 'feFuncB', 'feFuncG', 'feFuncR', 'feGaussianBlur', 'feImage', 'feMerge', 'feMergeNode', 'feMorphology', 'feOffset', 'feSpecularLighting', 'feTile', 'feTurbulence']
Font_elements = ['font', 'font-face', 'font-face-format', 'font-face-name', 'font-face-src', 'font-face-uri', 'hkern', 'vkern']
Gradient_elements = ['linearGradient', 'radialGradient', 'stop']
Graphics_elements = ['circle', 'ellipse', 'image', 'line', 'path', 'polygon', 'polyline', 'rect', 'text', 'use']
Graphics_referencing_elements = ['use']
Light_source_elements = ['feDistantLight', 'fePointLight', 'feSpotLight']
Never_rendered_elements = ['clipPath', 'defs', 'linearGradient', 'marker', 'mask', 'metadata', 'pattern', 'radialGradient', 'script', 'style', 'symbol', 'title']
Paint_server_elements = ['linearGradient', 'pattern', 'radialGradient']
Renderable_elements = ['a', 'circle', 'ellipse', 'foreignObject', 'g', 'image', 'line', 'path', 'polygon', 'polyline', 'rect', 'svg', 'switch', 'symbol', 'text', 'textPath', 'tspan', 'use']
Shape_elements = ['circle', 'ellipse', 'line', 'path', 'polygon', 'polyline', 'rect']
Structural_elements = ['defs', 'g', 'svg', 'symbol', 'use']
Text_content_elements = ['glyph', 'glyphRef', 'textPath', 'text', 'tref', 'tspan']
Text_content_child_elements = ['textPath', 'tref', 'tspan']
Uncategorized_elements = ['clipPath', 'cursor', 'filter', 'foreignObject', 'script', 'style', 'view']

# Attrs
elem_cat = ['Animation elements','Basic shapes','Container elements','Descriptive elements','Filter primitive elements','Font elements','Gradient elements','Graphics elements','Graphics referencing elements','Light source elements','Never-rendered elements','Paint server elements','Renderable elements','Shape elements','Structural elements','Text content elements','Text content child elements','Uncategorized element']
elem_all = Animation_elements+Basic_shapes+Container_elements+Descriptive_elements+Filter_primitive_elements+Font_elements+Gradient_elements+Graphics_elements+Graphics_referencing_elements+Light_source_elements+Never_rendered_elements+Paint_server_elements+Renderable_elements+Shape_elements+Structural_elements+Text_content_elements+Text_content_child_elements+Uncategorized_elements
elem_cat_map =  dict(zip(elem_cat , [Animation_elements,Basic_shapes,Container_elements,Descriptive_elements,Filter_primitive_elements,Font_elements,Gradient_elements,Graphics_elements,Graphics_referencing_elements,Light_source_elements,Never_rendered_elements,Paint_server_elements,Renderable_elements,Shape_elements,Structural_elements,Text_content_elements,Text_content_child_elements,Uncategorized_elements]))

Core_attributes = ['id','class','style','lang','tabindex','xml:lang','xml:space']
Conditional_processing_attributes = ['requiredExtensions','requiredFeatures','systemLanguage']
Generic_attributes = Core_attributes + Conditional_processing_attributes
XLink_attributes =['xlink:href','xlink:type','xlink:role','xlink:arcrole','xlink:title','xlink:show','xlink:actuate']
    # Note: All SVG presentation attributes can be used as CSS properties.
Presentation_attributes= ['alignment-baseline','baseline-shift','clip','clip-path','clip-rule','color','color-interpolation','color-interpolation-filters','color-rendering','cursor','d','direction','display','dominant-baseline','fill','fill-opacity','fill-rule','filter','flood-color','flood-opacity','font-family','font-size','font-size-adjust','font-stretch','font-style','font-variant','font-weight','glyph-orientation-horizontal','glyph-orientation-vertical','image-rendering','letter-spacing','lighting-color','marker-end','marker-mid','marker-start','mask','opacity','overflow','pointer-events','shape-rendering','stop-color','stop-opacity','stroke','stroke-dasharray','stroke-dashoffset','stroke-linecap','stroke-linejoin','stroke-miterlimit','stroke-opacity','stroke-width','text-anchor','text-decoration','text-rendering','transform','transform-origin','unicode-bidi','vector-effect','visibility','word-spacing','writing-mode']
Filter_primitive_attributes = ['height','result','width','x','y']
Transfer_function_attributes = ['type','tableValues','slope','intercept','amplitude','exponent','offset']
Filters_attributes = Filter_primitive_attributes + Transfer_function_attributes
Animation_target_element_attributes =['href']
Animation_attribute_target_attributes = ['attributeType', 'attributeName']
Animation_timing_attributes = ['begin','dur','end','min','max','restart','repeatCount','repeatDur','fill' ]
Animation_value_attributes = ['calcMode', 'values', 'keyTimes', 'keySplines', 'from', 'to', 'by', 'autoReverse', 'accelerate', 'decelerate']
Animation_addition_attributes = ['additive', 'accumulate']
Animation_attributes = Animation_target_element_attributes+Animation_attribute_target_attributes+Animation_timing_attributes+Animation_value_attributes+Animation_addition_attributes

attr_cat = ['Core attributes','Conditional processing attributes','XLink attributes','Presentation attributes','Filter primitive attributes','Transfer function attributes','Animation attributes','Animation target element attributes','Animation attribute target attributes','Animation timing attributes','Animation value attributes','Animation addition attributes']
attr_cat_cat = ['Generic_attributes','Filters_attributes', 'Animation_attributes']

attr_cat_map = dict(zip(attr_cat, [Core_attributes,Conditional_processing_attributes,Generic_attributes,XLink_attributes,Presentation_attributes,Filter_primitive_attributes,Transfer_function_attributes,Filters_attributes,Animation_target_element_attributes,Animation_attribute_target_attributes,Animation_timing_attributes,Animation_value_attributes,Animation_addition_attributes]))
attr_all = Generic_attributes + XLink_attributes + Presentation_attributes + Filters_attributes + Animation_attributes


#     print(f"Results written to {target_file}")
# import re
# def remove_consecutive_duplicates(input_str, delimiters=r'">|;|:| '):
    # (\b\w+\b)([">|;:\s]+)(?=\1\b) $2



# def strip_tags(str):
#     between = str
#     between = between.replace('<code>', '')  # Fix: re-assign to 'between'
#     between = between.replace('</code>', '')  # Fix: re-assign to 'between'
#     between = between.replace('<strong>', '')  # Fix: re-assign to 'between'
#     between = between.replace('</strong>', '')  # Fix: re-assign to 'between'
#     between = between.replace('<em>', '')  # Fix: re-assign to 'between'
#     between = between.replace('</em>', '')  # Fix: re-assign to 'between'
#     between = between.replace('<a href="/en-US/docs/Web/SVG/Content_type#', '')
#     between = between.replace('<a href=\\"/en-US/docs/Web/SVG/Content_type#', '')  # Fix: re-assign to 'between'
#     between = between.replace('<ahref="/en_US/docs/Web/SVG/Attribute/', '')
#     between = between.replace('&lt;', '')
#     between = between.replace('&gt;', '')
#     between = between.replace('</a>' , '')


#     return between
# def proc_value(line, start, end):
#     start_pos = line.find(start)
#     end_pos = line.find(end, start_pos)
#     between_strings = line[start_pos + len(start):end_pos].strip()
#     between_strings = strip_tags(between_strings)
#     return between_strings
def check_elem_elem_and_attrs_with_values( elem_dir, target_file , elems, attrs , elem_cats):
    tag_elem = ['&lt;' + item + '&gt;' for item in elems]
    tag_attr =  ['&lt;' + item + '&gt;' for item in attrs]
    with open(target_file ,'w', encoding= 'utf-8') as output_file:
        for root, dirs, files in os.walk(elem_dir):
            for file_name in files:
                file_path = os.path.join(root,file_name)
                strings_found_in_file = []
                try:
                    with open(file_path, 'r', encoding='utf-8') as elem_file:
                        # Look for specific content in the file
                        for line in elem_file:
                            if 'id="attributes"' in line :
                                strings_found_in_file.append("attribs:{")
                                bod_end = False
                                while not bod_end:
                                    for tattr in attrs:
                                        # (f"href=\"/en-US/docs/Web/SVG/Attribute/{tattr}\"><code>{tattr}</code>" in line or 
                                        # f"<code>{tattr}</code>" in line or f"<strong>{tattr}</strong>" in line 
                                        s = '\"'
                                        s = '<code>' + tattr + '</code>'
                                        b= False 
                                        ind = 0
                                        for char in line: #if  s in line
                                            if ind == len(s) - 1 :
                                                b = True
                                                break
                                            if char == s[ind] :
                                                ind+=1
                                            else : 
                                                ind = 0
                                        if b:
                                            # print(f"{tattr}")
                                            # Process value types and other attributes
                                            # print(f"at_{tattr}:")
                                            strings_found_in_file.append(f"&at_{tattr}::Vals::")
                                            
                                            for line in elem_file:
                                                # if '</dd>' in line:
                                                #     break  # Exit loop when '</dd>' is found
                                                if 'Value type' in line:
                                                    between_strings = proc_value(line, 'Value type', '</p>')
                                                    
                                                    # print(f"{between_strings};")
                                                    strings_found_in_file.append(f"Valuetype: {between_strings}; :: ")
                                                    # print(f"Value{line}")
                                                    # print(f"{between_strings}")
                                                    break;
                                                
                                                # if 'Default value' in line:
                                                    # between_strings = proc_value(line, 'Default value', ';')
                                                    # print(f"Default{line}")
                                                    # print(f"{between_strings}")
                                                    # print(f"Default:{between_strings};")
                                                    # strings_found_in_file.append(f"Default:{between_strings};")
                                                # if 'Animatable' in line:
                                                    # between_strings = proc_value(line, 'Animatable', '</strong>')
                                                    # print(f"Animatable{line}")
                                                    # print(f"{between_strings}")
                                                    # print(f"Animatable:{between_strings};")
                                                    # strings_found_in_file.append(f"Animatable:{between_strings};;")
                                    if '</div></section>' in line:
                                        print("Found Attrib list end ---------------------------------")
                                        bod_end = True
                        elem_file.seek(0)
                        for line in elem_file:
                            if 'Permitted content' in line:
                                strings_found_in_file.append('elems:{')
                                tbody_end = False 
                                
                                for line in elem_file:
                                    for el_cat in elem_cats:
                                        if el_cat in line:
                                            print(f"el_{el_cat}")
                                            strings_found_in_file.append(f"&el_{el_cat}, ")
                                    
                                    for tag_el in tag_elem:
                                        if tag_el in line:
                                            out = tag_el.replace('&lt;','')
                                            out = out.replace('&gt;','')
                                            print(f"el_{out}")
                                            strings_found_in_file.append(f"&el_{out}, ")
                                    
                                    if '</tbody>' in line:
                                        tbody_end = True
                                        strings_found_in_file.append('}')
                                    if tbody_end:
                                        break  # End the inner loop if tbody_end is True
                             
                        strings_found_in_file.append('\n')             
                    if strings_found_in_file:

                        print(f"Filename: {file_path}\n")
                        print(f"[{', '.join(strings_found_in_file)}]\n\n")
                        # output_file.write(f"Filename: {file_path}\n")
                        # output_file.write(f"[{', '.join(strings_found_in_file)}]\n\n")

                except Exception as e:
                    print(f"Could not process file {file_path}: {e}\n\n")
                    # output_file.write(f"Could not process file {file_path}: {e}\n\n")

def strip_tags(str):
    tag_open = 0
    s = ''
    for ind, c in enumerate(str):
        if c =='<':
            c = c+","
            tag_open+=1
        if c == '>' :
            tag_open -=1
            c = c+","
            continue
        if  tag_open == 0 :
            s = s + c
        
    s = s.replace(f"\n" , '')
    s = s.replace(f"Deprecated", '')
    return s


def check_attrs_elem_with_values(attr_dir, target_file, elems , attrs  ):
    # Open the output file for writing
    # Get all el
    with open(target_file, 'w', encoding='utf-8-sig') as output_file:
        # Get all files in the source directory
        for root, dirs, files in os.walk(attr_dir):
            for file_name in files:
                file_path = os.path.join(root, file_name)
                strings_found_in_file = []
                try:
                    # Open and read the file using utf-8-sig encoding (handles BOM in files)
                    with open(file_path, 'r', encoding='utf-8-sig') as attr_file:
                        arti = False
                        lines = []
                        t = -1
                        for line in attr_file:  # Loop until end of file
                            # Check for each string in the tag_elem list
                            if '<article' in line:
                                print(f"{file_name}")
                                arti = True
                                t = line.find('<article')
                                # print(f"found article: {line[t:]}\n")
                                lines += line[t:]
                                
                                continue
                            if '</article' in line:
                                t = line.find('</article')
                                # print(f"found close article:{line[:t+len('</article>')]}\n")
                                lines += line[:t+len('</article>')]
                               
                                arti= False
                                break      
                            if arti == True:
                                lines+=line
                                # print(line)
                        s = ''.join(lines).strip()
                        print(f"{s[:40]} {s[-40:]}")                        
                        # print(s)
                        soup = BeautifulSoup(s, "html.parser")
                        xl = XMLp(soup.find("article"))
                        elems = []
                        # elems=XMLp.get_values_rec(child , lambda e: (("elements" or "example" or"code-example" in e.ats.values()) or (e.name ==  "p")) )
                        try :                                                               # ( any("/en-US/docs/Web/SVG/Element/" in s for s in e.ats.values()) or and (e.name =="a") )  ( e.ats.get("class")=="table-container") and (e.name =="figure"))   ((e.ats.get("class")=="properties") and (e.name =="table") )   
                            elems=XMLp.get_values_rec_tree_incl(xl , lambda e:  (  ((e.ats.get("class")=="properties") )  ) ) # Make lambda list
#                         elems=XMLp.get_values_rec_incl(xl , lambda e:  ( ("/en-US/docs/Web/SVG/Element/" in s for s in e.ats.values()) or (e.val ==  "Value" or "Default Value" or "Animatable")) )
                        except Exception as e :
                            print(f"exception:{e}")
                        #for child in xl.els :
                        #    print("Entered children")
                        #    try:  #"aria-labelledby":"elements","aria-labelledby":"example"
                        #            def condition(e):
                        #                return (("elements" or"example"or"code-example" in e.ats.values()) or (e.name ==  "p"))
                        #            # elems=XMLp.get_values_rec(child , lambda e: (("elements" or "example" or"code-example" in e.ats.values()) or (e.name ==  "p")) )
                        #            # elems+=child.val
                        #            print(elems)
                        #    except Exception as e: 

                        output_file.write(f"Filename: {file_name}\n")
                        print(f"Filename: {file_name}\n")
                        output_file.write(f"[{''.join(elems)}]\n")
                        print(f"[{''.join(elems)}]\n")

                except Exception as e:
                    print(f"{file_name}: {e}\n\n")
                    # output_file.write(f"{file_name}: {e}\n\n")

        print(f"Results written to {target_file}")

# def get_attrs_value(src_dir , target_file) :
_elem_attribs = target_file_elem + "attrs"
_elem_elems = target_file_elem + "elems"
_attrib_attribs = target_file_attrib + "attrs"
_attrib_elems = target_file_attrib + "elems"

def dir_file_no(dir):
    for root, dirs, files in os.walk(dir):
        s = 0 
        for file in files :
            s+=1
        print(s)
# dir_file_no(src_dir_elem)
# check_strings_in_files(src_dir_elem, _elem_attribs, attr_cat + attr_cat_cat+ [ '&lt;'+item+'&gt;' for item in attr_all]  )
# check_attrs_elem_with_values(src_dir_attrib, src_dir_elem, _attrib_elems , elem_all , attr_all)

# def check_attrs_elem_with_values(attr_dir, elem_dir, target_file, elems , attrs  ):
# def check_elem_elem_and_attrs_with_values( elem_dir, target_file , elems, attrs , elem_cats):

# check_elem_elem_and_attrs_with_values(src_dir_elem, _elem_elems , elem_all , attr_all , elem_cat )
check_attrs_elem_with_values(src_dir_attrib,_attrib_elems, elem_all , attr_all)


