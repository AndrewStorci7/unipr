#!/bin/bash

sanitize_str() {
    local input_str="$1"

    local sanitized_str
    sanitized_str=$(echo "$input_str" | sed 's/[0-9]//g; s/-/ /g')
    echo "$sanitized_str"
}

main() {

    read -p "Inserisci il nome della cartella: " folder_name

    if [[ -z "$folder_name" ]]; then
        echo "Errore: il nome della cartella non può essere vuoto."
        exit 1
    fi

    if mkdir -p "$folder_name"; then
        echo "Cartella '$folder_name' creata con successo."
    else
        echo "Errore nella creazione della cartella."
        exit 1
    fi

    readme_path="$folder_name/README.md"
    title=$(sanitize_str "$folder_name")

    if echo -e "# $title" > "$readme_path"; then
        echo "File '$readme_path' creato con successo."
    else
        echo "Errore nella creazione del file README.md."
        exit 1
    fi
}

main
