
FILE_DAT="c-wire_v00.dat"
FILE_C="./codeC" # path to the compiled C executable
OUTPUT_FILE="result.txt" # file to show C program results (can be modified in the future to a graphic file)

#!/bin/bash

# Function: Display help
display_help() {
    echo "Usage: ./c-wire.sh [ARG] [OPTION]"
    echo "Arguments:"
    echo "  ARG[0] Path to the CSV file containing the data *required*"
    echo "  ARG[1] Station type (HVB, HVA, LV) *required*"
    echo "  ARG[2] Consumer type: comp (business), indiv (individual), all (all) *required*"
    echo "  ARG[3] Number of power plant *optional*"
    echo "Options:"
    echo "  -h        Display this help and ignore all other parameters *optional*"
    echo ""
    echo "Restrictions:"
    echo "  The following combinations are forbidden:"
    echo "  - hvb all, hva all, hvb indiv, hva indiv"
    echo ""
}

#Start timer 
A=$(date +%s.%N)


#Check if help command is requested. If yes, display_help is called. Otherwise, do nothing.
for arg in "$@"; do
if [ "$arg" == "-h" ]; then
display_help
exit 0
fi
done


#Check required parameters
if [[ -z "$1" || -z "$2" || -z "$3" ]]; then
  echo "Error : Missing parameters." >&2
  display_help
  exit 1
fi

#Check if the first parameter is the good path to the CSV file.
if [[ ! -f "$1" || "$1" != *.csv ]]; then
echo "Error : The first parameter must be a valid path to an existing .csv file. " >&2
display_help
exit 1
fi


#Check if the second parameter is a type of station.
if [[ "$2" != "hva" && "$2" != "hvb" && "$2" != "lv" ]]; then
echo "Error : The second parameter must be a type of station." >&2
display_help
exit 1
fi


#Check if the third parameter is a type of consumer.
if [[ "$3" != "comp" && "$3" != "indiv" && "$3" != "all" ]]; then
echo "Error : The third parameter must be a type of consumer." >&2
display_help
exit 1
fi


#Check the 4 prohibited combinations
if [[ "$2" == "hvb" && "$3" == "all" ]]; then
echo "Error : HV-B stations can not have all type of consumers." >&2
display_help
exit 1
fi

if [[ "$2" == "hvb" && "$3" == "indiv" ]]; then
echo "Error : HV-B stations can not have individuals as consumers." >&2
display_help
exit 1
fi

if [[ "$2" == "hva"  && "$3" == "indiv" ]]; then
echo "Error : HV-A stations can not have individuals as consumers." >&2
display_help
exit 1
fi

if [[ "$2" == "hva" &&  "$3" == "all" ]]; then
echo "Error : HV-A stations can not have all type of consumers." >&2
display_help
exit 1
fi


# verify files
if [ ! -f "$FILE_DAT" ]; then
    echo "Error : File $FILE_DAT does not exist or is not accessible." >&2
    exit 1
fi

if [ ! -r "$FILE_C" ]; then
    echo "Error : File $FILE_C does not have read permissions." >&2
    exit 1
fi

if [ ! -x "$FILE_C" ]; then
    echo "Error : File $FILE_C is not executable." >&2
    exit 1
fi

#filtering
if [[ "$1" == "hvb" ]] && [[ "$2" == "comp" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
fi



if [[ "$1" == "hva" ]] && [[ "$2" == "comp" ]]; then
  awk -F';' '$2 != "-" && $4 == "-" && $7 == "-" || $2 != "-" && $3 == "-" && $4 == "-" && $5 == "-" && $6 == "-"' "cwire.dat" | cut -d';' -f2,5,7,8 | tr '-' '0' | ./projet
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



B=$(date +%s.%N)
diff=$(echo "$B - $A" | bc)
echo "Elapsed time : $diff seconds"

./codeC