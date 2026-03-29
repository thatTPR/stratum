$files = Get-ChildItem "./shaders"
foreach ($file in $files) {

    $n = $file.fullName+ ".spv"
    glslc $file.fullName -o $n
} 