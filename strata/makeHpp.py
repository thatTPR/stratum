import os
import re

def extract_declarations(content):
    # Use regular expressions to match includes and function/method declarations
    include_pattern = re.compile(r'#include\s*["<].*?[">]')
    declaration_pattern = re.compile(r'\b(?:class|struct|namespace)?\s*\w+\s*[\*\&]?\s*\([^)]*\)\s*;?')

    # Extract includes and declarations
    includes = re.findall(include_pattern, content)
    declarations = re.findall(declaration_pattern, content)

    return includes, declarations

def generate_hpp_file(input_file, output_file):
    try:
        with open(input_file, 'r') as cpp_file:
            cpp_content = cpp_file.read()

        # Extract includes and declarations
        includes, declarations = extract_declarations(cpp_content)

        # Change the file extension from .cpp to .hpp
        output_file = os.path.splitext(output_file)[0] + '.hpp'

        with open(output_file, 'w') as hpp_file:
            # Write extracted includes to the new .hpp file
            hpp_file.write('\n'.join(includes))
            hpp_file.write('\n\n')

            # Write extracted declarations to the new .hpp file
            hpp_file.write('\n'.join(declarations))

        print(f'Successfully generated {output_file}')
    except Exception as e:
        print(f'Error: {e}')

def generate_hpp_files_in_directory(input_directory):
    for root, dirs, files in os.walk(input_directory):
        for file in files:
            if file.endswith('.cpp'):
                input_file_path = os.path.join(root, file)
                output_file_path = os.path.join(root, os.path.splitext(file)[0] + '.hpp')
                generate_hpp_file(input_file_path, output_file_path)


# Example usage
generate_hpp_files_in_directory('.')