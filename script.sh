#!/bin/bash

output_file="all_c_files.txt"

# Vide le fichier de sortie
> "$output_file"

# Cherche récursivement tous les fichiers .c
find . -type f -name "*.c" | while read -r file; do
    echo "/* ======= fichier: $file ======= */" >> "$output_file"
    cat "$file" >> "$output_file"
    echo -e "\n" >> "$output_file"
done

echo "Tous les fichiers .c ont été concaténés dans $output_file"
