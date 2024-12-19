#!/bin/bash

help() {
    cat << EOF
Usage : $0 <path> <station> <consumption>
Description :
This script.

For its good fonctionment, this script verify the validity of the 3 arguments :
    1. First argument : valid path to a file
    2. Second argument : valid type of station
    3. Third argument : valid type of consumption

Required arguments :
    <path> : valid absolute path to a file
    <station> : allowed values ("hvb", "hva", "lv")
    <consumption> : allowed values ("company", "individual", "all")

    If the combination of station and consumption is invalid (hvb-individual, hvb-all, hva-individual and hva-all), the script shows "Error : impossible request"

Options :
    -h, --help Show this help
EOF
}

timer() {
    start_time=$(date +%s)  # Capture the start time
    "$@"  # Execute the command passed as argument
    end_time=$(date +%s)  # Capture the end time
    elapsed_time=$((end_time - start_time))  # Calculate elapsed time
    echo "Execution time: $elapsed_time seconds"
}

# Gérer l'option help
if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    help
    exit 0
fi

if [ $# -ne 3 ]; then # If the number of arguments is incorrect
    echo "Usage : $0 <path> <station> <consumption>"
    help # Return "help" function
    exit 1
fi

path=$1 # First argument
station=$2 # Second argument
consumption=$3 # Third argument

if [ ! -f "$path" ]; then # If the path is incorrect
    echo "Error : $path is incorrect"
    help # Return "help" function
    exit 2
fi

if [[ "$station" != "hvb" && "$station" != "hva" && "$station" != "lv" ]]; then
    echo "Error : $station the station's type is incorrect"
    help
    exit 3
fi

if [[ "$consumption" != "company" && "$consumption" != "individual" && "$consumption" != "all" ]]; then
    echo "Error : $consumption the consumption's type is incorrect"
    help
    exit 4
fi

exec="codeC/MNH_CWire"
if [[ ! -f "$exec" ]]; then
    echo "Error : $exec doesn't exist. Compiling..."
    cd codeC
    make clean
    make all
    cd ..

    if [[ ! -f "$exec" ]]; then
        echo "Error : $exec hasn't been compiled."
        exit 5
    fi
fi

tmp="tmp"
if [[ ! -d "$tmp" ]]; then
    echo "Error : $tmp doesn't exist. Creation of the directory"
    mkdir tmp
else
    rm -f $tmp
fi

case "$station-$consumption" in
    "hvb-company")
        awk -F";" '($2 != "-" && $5 != "-") || ($2 != "-" && $7 != "-") {print $2 ";" $7 ";" $8}' input/c-wire_v00.dat > tmp/hvbCtmp.csv
        tmp_file="tmp/hvbCtmp.csv"
        final_file="tests/hvb_comp.csv"
        ;; #hvb company

    "hva-company")
        awk -F";" '($3 != "-" && $5 != "-") || ($3 != "-" && $7 != "-") {print $3 ";" $7 ";" $8}' input/c-wire_v00.dat > tmp/hvaCtmp.csv
        tmp_file="tmp/hvaCtmp.csv"
        final_file="tests/hva_comp.csv"
        ;; #hva company

    "lv-company")
        awk -F";" '($4 != "-" && $5 != "-") || ($4 != "-" && $7 != "-") {print $4 ";" $7 ";" $8}' input/c-wire_v00.dat > tmp/lvCtmp.csv
        tmp_file="tmp/lvCtmp.csv"
        final_file="tests/lv_comp.csv"
        ;; #lv company

    "lv-individual")
        awk -F";" '($4 != "-" && $6 != "-") || ($4 != "-" && $7 != "-") {print $4 ";" $7 ";" $8}' input/c-wire_v00.dat > tmp/lvItmp.csv
        tmp_file="tmp/lvItmp.csv"
        final_file="tests/lv_indiv.csv"
        ;; #lv indiv

    "lv-all")
        awk -F";" '($4 != "-" && $5 != "-") || ($4 != "-" && $6 != "-") || ($4 != "-" && $7 != "-") {print $3 ";" $7 ";" $8}' input/c-wire_v00.dat > tmp/lvAtmp.csv
        tmp_file="tmp/lvAtmp.csv"
        tmpminmax_file="tmp/lv_all.csv"

        final_file="tests/lv_all_minmax.csv" #on crée un fichier additionnel en plus qui va stocker les 10 min et 10 max, minmax_file est une variable qui contient le chemin complet du nv fichier
        echo "Nom;Capacite;Consommation;Difference" > "$final_file" #en-tête

        awk -F";" 'NR > 1 { #awk divise chaque ligne en champs $1 $2 $3 grace au séparateur -F";" NR > 1 pour éviter la première ligne (en-tête)
            capacite = $2; 
            consommation = $3;
            difference = capacite - consommation;
            print $0 ";" difference; #On ajoute à la fin de la ligne $0 une nouvelle colonne contenant la différence calculée
        }' "$tmpminmax_file" | sort -t';' -k4,4n | { #on trie les données selon la 4ᵉ colonne (la colonne difference) : les lignes sont triées dans l'ordre croissant de la différence
            head -n 10 >> "$final_file" #on ajoute les 10 lv max
            tail -n 10 >> "$final_file" #on ajoute les 10 lv min
        }

        echo "File $final_file has been successfully generated."
        if [[ -f "$final_file" ]]; then #si le fichier a bien été créé
            echo "Created directory"
        else
            echo "Error: $final_file was not generated properly."
            exit 7
        fi
        ;;

    *)
        echo "Error : impossible request"
        help 
        exit 6
esac

# Création ou réinitialisation du fichier final
if [[ ! -f "$final_file" ]]; then
    chmod +w "$final_file"
    echo "Station; Capacity; Consumption" > "$final_file"  # Créer le fichier avec l'entête
    echo "Created CSV file with headers: $final_file"

else 
    chmod +w "$final_file"
    echo "Station; Capacity; Consumption" > "$final_file"
fi

./codeC/MNH_CWire "$tmp_file" "$final_file"

sort -t ';' -k 2,2 "$final_file"
