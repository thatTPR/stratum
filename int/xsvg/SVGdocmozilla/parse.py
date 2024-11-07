#  Parse Element and Attribte dirs as well as their respective .1 ext files and generate appropiatte c code"
#  Attribs
# // ValueType
# // DefaultValue 
# // Animatable: yes | no


events= [ 'afterscriptexecute','animationcancel','animationend','animationiteration','animationstart','auxclick','beforeinput',
'beforematch','beforescriptexecute','beforexrselect','blur','click','compositionend','compositionstart',
'compositionupdate','contentvisibilityautostatechange','contextmenu','copy','cut','dblclick','DOMActivate','DOMMouseScroll',
'focus','focusin','focusout','fullscreenchange','fullscreenerror','gesturechange','gestureend','gesturestart',
'gotpointercapture','input','keydown','keypress','keyup','lostpointercapture','mousedown','mouseenter','mouseleave','mousemove',
'mouseout','mouseover','mouseup','mousewheel','MozMousePixelScroll','paste','pointercancel','pointerdown',
'pointerenter','pointerleave','pointermove','pointerout','pointerover','pointerrawupdate','pointerup','scroll',
'scrollend','scrollsnapchange','scrollsnapchanging','securitypolicyviolation','touchcancel','touchend','touchmove','touchstart',
'transitioncancel','transitionend','transitionrun','transitionstart','webkitmouseforcechanged','webkitmouseforcedown',
'webkitmouseforceup','webkitmouseforcewillbegin','wheel']


# To find all occurrences of a specific string in all files within a directory using Python, you can use the os module to walk through the directory and the open() function to read each file. Here’s a Python script that demonstrates this process:

# Python Script to Search for String References in Files
# python
# Copy code

# target_dir = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\attrib'
# def find_string_in_files(directory, search_string):
#     # Walk through all files in the given directory
#     for root, dirs, files in os.walk(directory):
#         for file in files:
#             # Only open files with specific extensions (optional, e.g., .txt, .py)
#             file_path = os.path.join(root, file)
#             try:
#                 with open(file_path, 'r', encoding='utf-8') as f:
#                     # Read file line by line
#                     for line_num, line in enumerate(f, start=1):
#                         flag = 0
#                         if search_string in line:
#                             # flag = flag + 1
#                             # if flag < 2 :
#                             with open( os.path.join(target_dir, file), 'a') as f :
#                                 f.write(f"\n{search_string} on line {line_num}: {line}\n")
#                         else:
#                             break
#             except Exception as e:
#                 print(f"Could not open {file_path}: {e}")

# Example Usage
# directory = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\Attribute'  # Specify the directory to search in
# def create_files(directory):
#     for root, dirs, files in os.walk(directory):
#         for file in files:
#             file_path = os.path.join(target_dir, file)
            
            
# create_files(directory) 
    
# for search_string in  events: 
#     find_string_in_files(directory, search_string)


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
 

src_dir = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\Attribute'  # Directory to search for files (use \\ or raw string literals in Windows paths)
target_file = 'C:\\Users\\Alexandru.Popp\\src\\xavirtg\\int\\xsvg\\SVGdocmozilla\\attrib.hpp'  # Directory to write results to (use \\ or raw string literals in Windows paths)
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
target_file_ev = target_file+'ev'
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