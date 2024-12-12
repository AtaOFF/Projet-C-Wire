FILE_DAT="data_cwire.dat"
FILE_TEMP="filtered_data.dat" # temp file with filtered data
FILE_C="./code" # path to the compiled C executable
OUTPUT_FILE="result.txt" # file to show C program results (can be modified in the future to a graphic file)

#!/bin/bash

# Fonction d'aide pour expliquer les options du script principal
help_function() {
    echo -e "\n=== AIDE : Utilisation du script ==="
    echo -e "\nCommandes disponibles :"
    echo -e "  ./script.sh <type_station> <type_consommateur>"
    echo -e "\nParamètres :"
    echo -e "  <type_station> : Type de la station électrique. Les valeurs possibles sont :"
    echo -e "    - hvb : Haute tension B"
    echo -e "    - hva : Haute tension A"
    echo -e "    - lv  : Basse tension (Low Voltage)"
    echo -e "\n  <type_consommateur> : Type du consommateur. Les valeurs possibles sont :"
    echo -e "    - comp  : Consommateur commercial"
    echo -e "    - indiv : Consommateur individuel"
    echo -e "    - all   : Tous les types de consommateurs"
    echo -e "\nOptions spéciales :"
    echo -e "  -h : Affiche cette aide."

}

if [[ "$1" == "-h" ]]; then
  ./help.sh
  exit 0
fi

# Check files
if [ ! -f "$FILE_DAT" ]; then
    echo "Error : File $FILE_DAT does not exist or is not accessible"
    exit 1
fi

if [ ! -r "$FILE_C" ]; then
    echo "Error : File $FILE_C does not have read permissions"
    exit 1
fi

if [ ! -x "$FILE_C" ]; then
    echo "Error : File $FILE_C is not executable"
    exit 1
fi

A=$(date+%s.%N)

./code

if [[ "$1" == "hvb" ]] && [[ "$2" == "comp" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi

if [[ "$1" == "hvb" ]] && [[ "$2" == "indiv" ]]; then
  echo "Erreur : les stations HV-B ne peuvent pas avoir de particuliers comme consommateurs."
  ./help.sh
fi

if [[ "$1" == "hvb" ]] && [[ "$2" == "all" ]]; then
  echo "Erreur : les stations HV-B ne peuvent pas avoir tous les types de consommateurs."
  ./help.sh
fi

if [[ "$1" == "hva" ]] && [[ "$2" == "comp" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi

if [[ "$1" == "hva" ]] && [[ "$2" == "indiv" ]]; then
  echo "Erreur : les stations HV-A ne peuvent pas avoir de particuliers comme consommateurs."
  ./help.sh
fi

if [[ "$1" == "hva" ]] && [[ "$2" == "all" ]]; then
  echo "Erreur : les stations HV-A ne peuvent pas avoir tous les types de consommateurs."
  ./help.sh
fi

if [[ "$1" == "lv" ]] && [[ "$2" == "comp" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi

if [[ "$1" == "lv" ]] && [[ "$2" == "indiv" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi

if [[ "$1" == "lv" ]] && [[ "$2" == "all" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi


# Vérification des options
if [[ -z "$1" || -z "$2" || -z "$3" ]]; then
  echo "Erreur : il manque des paramètres."
  ./help.sh
  exit 1
fi

B=$(date +%s.%N)

echo"$B-$A" |bc