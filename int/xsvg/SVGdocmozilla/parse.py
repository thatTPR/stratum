#  Parse Element and Attribte dirs as well as their respective .1 ext files and generate appropiatte c code"
#  Attribs
# // ValueType
# // DefaultValue 
# // Animatable: yes | no


import os
import shutil

# def check_strings_in_files(src_dir, target_dir, string_list):
#     # Ensure the target directory exists
#     os.makedirs(target_dir, exist_ok=True)

#     # Get all files in the source directory
#     for root, dirs, files in os.walk(src_dir):
#         for file_name in files:
#             file_path = os.path.join(root, file_name)
#             strings_found_in_file = []

#             try:
#                 # Open and read the file using utf-8-sig encoding (handles BOM in files)
#                 with open(file_path, 'r', encoding='utf-8-sig') as file:
#                     file_contents = file.read()

#                     # Check for each string in the string list
#                     for string in string_list:
#                         if string in file_contents:
#                             strings_found_in_file.append(string)

#                 # If we found any string, write them to a new file in the target directory
#                 if strings_found_in_file:
#                     target_file_path = os.path.join(target_dir, f"{file_name}")

#                     with open(target_file_path, 'w', encoding='utf-8') as output_file:
#                         output_file.write(f"Strings found in file: {file_path}\n")
#                         for string in strings_found_in_file:
#                             output_file.write(f"- {string}\n")
#                     print(f"Written matches for {file_name} to {target_file_path}")

#             except Exception as e:
#                 print(f"Could not process file {file_path}: {e}")
def check_strings_in_files(src_dir, target_file, string_list):
    # Open the output file for writing
    with open(target_file, 'w', encoding='utf-8') as output_file:
        # Get all files in the source directory
        for root, dirs, files in os.walk(src_dir):
            for file_name in files:
                file_path = os.path.join(root, file_name)
                strings_found_in_file = []

                try:
                    # Open and read the file using utf-8-sig encoding (handles BOM in files)
                    with open(file_path, 'r', encoding='utf-8-sig') as file:
                        file_contents = file.read()

                        # Check for each string in the string list
                        for string in string_list:
                            if string in file_contents:
                                strings_found_in_file.append(string)

                    # If we found any string, write to the output file
                    if strings_found_in_file:
                        output_file.write(f"Filename: {file_path}\n")
                        output_file.write(f"[{', '.join(strings_found_in_file)}]\n\n")

                except Exception as e:
                    output_file.write(f"Could not process file {file_path}: {e}\n\n")

    print(f"Results written to {target_file}")

# Example usage
src_dir_elem = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\Element'  # Directory to search for files (use \\ or raw string literals in Windows paths)
target_file_elem = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\elem.hpp'  # Directory to write results to (use \\ or raw string literals in Windows paths)
 

src_dir_attrib = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\Attribute'  # Directory to search for files (use \\ or raw string literals in Windows paths)
target_file_attrib = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\attrib.hpp'  # Directory to write results to (use \\ or raw string literals in Windows paths)
nevent = [ 'afterscriptexecute','animationcancel','animationend','animationiteration','animationstart','auxclick','beforeinput',
'beforematch','beforescriptexecute','beforexrselect','blur','click','compositionend','compositionstart',
'compositionupdate','contentvisibilityautostatechange','contextmenu','copy','cut','dblclick','DOMActivate','DOMMouseScroll',
'focus','focusin','focusout','fullscreenchange','fullscreenerror','gesturechange','gestureend','gesturestart',
'gotpointercapture','input','keydown','keypress','keyup','lostpointercapture','mousedown','mouseenter','mouseleave','mousemove',
'mouseout','mouseover','mouseup','mousewheel','MozMousePixelScroll','paste','pointercancel','pointerdown',
'pointerenter','pointerleave','pointermove','pointerout','pointerover','pointerrawupdate','pointerup','scroll',
'scrollend','scrollsnapchange','scrollsnapchanging','securitypolicyviolation','touchcancel','touchend','touchmove','touchstart',
'transitioncancel','transitionend','transitionrun','transitionstart','webkitmouseforcechanged','webkitmouseforcedown',
'webkitmouseforceup','webkitmouseforcewillbegin','wheel']  # List of strings to search for

# first_sec = [ 'blur','click','contextmenu','dblclick','focus','input','keydown','keypress','keyup','mousedown','mouseenter','mouseleave','mousemove','mouseout','mouseover','mouseup','mousewheel','scroll','wheel']
target_file_elem_ev = target_file_elem+'ev' 
# target_file_ev = target_file+'ev'
html_event = ['onabort', 'onautocomplete', 'onautocompleteerror', 'onblur', 'oncancel', 'oncanplay', 'oncanplaythrough', 
'onchange', 'onclick', 'onclose', 'oncontextmenu', 'oncuechange', 'ondblclick', 'ondrag', 'ondragend', 'ondragenter',
'ondragleave', 'ondragover', 'ondragstart', 'ondrop', 'ondurationchange', 'onemptied', 'onended', 'onerror', 'onfocus',
'oninput', 'oninvalid', 'onkeydown', 'onkeypress', 'onkeyup', 'onload', 'onloadeddata', 'onloadedmetadata', 'onloadstart',
'onmousedown', 'onmouseenter', 'onmouseleave', 'onmousemove', 'onmouseout', 'onmouseover',
'onmouseup', 'onmousewheel', 'onpause', 'onplay', 'onplaying', 'onprogress', 'onratechange', 'onreset', 'onresize',
'onscroll', 'onseeked', 'onseeking', 'onselect', 'onshow', 'onsort', 'onstalled', 
'onsubmit', 'onsuspend', 'ontimeupdate', 'ontoggle', 'onvolumechange', 'onwaiting']
#  html_event = ['onautocomplete', 'onautocompleteerror', 'onblur', 'oncontextmenu', 'onsort'] + in_last_two 

# first_last = ['click','dblclick','focus','focusin','focusout','input','keydown','keypress','keyup','mousedown','mouseenter','mouseleave','mousemove','mouseout','mouseover','mouseup','mousewheel','scroll','wheel' ]
svg_event_attr = ['onabort','onactivate','onbegin','oncancel','oncanplay','oncanplaythrough','onchange','onclick','onclose',
'oncuechange','ondblclick','ondrag','ondragend','ondragenter','ondragleave','ondragover','ondragstart','ondrop',
'ondurationchange','onemptied','onend','onended','onerror','onerror','onfocus','onfocusin','onfocusout','oninput',
'oninvalid','onkeydown','onkeypress','onkeyup','onload','onloadeddata','onloadedmetadata','onloadstart','onmousedown',
'onmouseenter','onmouseleave','onmousemove','onmouseout','onmouseover','onmouseup','onmousewheel','onpause','onplay','onplaying',
'onprogress','onratechange','onrepeat','onreset','onresize','onresize','onscroll','onscroll','onseeked','onseeking','onselect','onshow',
'onstalled','onsubmit','onsuspend','ontimeupdate','ontoggle','onunload','onvolumechange','onwaiting']
# svg_event_attr =  [ 'onactivate','onbegin','onend','onfocusin','onfocusout','onrepeat','onunload'] + in_last_two
# svg_event_attr = [ ]
# check_strings_in_files(src_dir_elem, target_file_elem_ev, event)
# check_strings_in_files(src_dir_elem, target_file_ev, event)

for i in nevent :
    for j  in svg_event_attr  :
        if i in j :
            print(f" {i }") 

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
elem_cat = ['Animation elements',
'Basic shapes',
'Container elements',
'Descriptive elements',
'Filter primitive elements',
'Font elements',
'Gradient elements',
'Graphics elements',
'Graphics referencing elements',
'Light source elements',
'Never-rendered elements',
'Paint server elements',
'Renderable elements',
'Shape elements',
'Structural elements',
'Text content elements',
'Text content child elements',
'Uncategorized element']

def check_tags_in_files(src_dir, target_file, res_dir):
    # Open the output file for writing
    with open(target_file, 'w', encoding='utf-8') as output_file:
        # Get all files in the source directory
        for root, dirs, files in os.walk(src_dir):
            for file_name in files:
                file_path = os.path.join(root, file_name)
                strings_found_in_file = []

                try:
                    # Open and read the file using utf-8-sig encoding (handles BOM in files)
                    with open(file_path, 'r', encoding='utf-8-sig') as file:
                        file_contents = file.read()

                        # Check for each string in the string list
                        for string in string_list:
                            if string in file_contents:
                                strings_found_in_file.append(string)

                    # If we found any string, write to the output file
                    if strings_found_in_file:
                        output_file.write(f"Filename: {file_path}\n")
                        output_file.write(f"[{', '.join(strings_found_in_file)}]\n\n")

                except Exception as e:
                    output_file.write(f"Could not process file {file_path}: {e}\n\n")

    print(f"Results written to {target_file}")

# def get_attrs_value(src_dir , target_file) :


_elem_attribs = target_file_elem + "attrs"
_elem_elems = target_file_elem + "elems"
_attrib_attribs = target_file_attrib + "attrs"
_attrib_elems = target_file_attrib + "elems"

# Get _ele
check_tags_in_files(src_dir_elem, _elem_attribs , src_dir_attrib)
