import os

def replace_in_file(file_path, search_string, replacement_string):
    """
    Replace all occurrences of search_string with replacement_string in a given file.
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()

        # Replace occurrences
        updated_content = content.replace(search_string, replacement_string)

        # Write the updated content back to the file
        with open(file_path, 'w', encoding='utf-8') as file:
            file.write(updated_content)

        print(f"Updated: {file_path}")

    except Exception as e:
        print(f"Failed to process {file_path}: {e}")


def replace_in_directory(directory_path, search_string, replacement_string, file_extensions=None):
    """
    Replace occurrences of search_string with replacement_string in all files
    under directory_path. Only process files with specified extensions if provided.
    """
    for root, _, files in os.walk(directory_path):
        for file_name in files:
            # Check file extension if specified
            if file_extensions is None or any(file_name.endswith(ext) for ext in file_extensions):
                file_path = os.path.join(root, file_name)
                replace_in_file(file_path, search_string, replacement_string)


replace_in_directory("C:\Users\Alxandru.Popp\src\strata\strata" , "STRATA",)