
#!/bin/bash

FILE_DAT="c-wire_v00.dat"  # Path to the data file
FILE_C="./codeC"           # Path to the compiled C executable
OUTPUT_FILE="filtered_data.csv"   # Output CSV file (results from C program)


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


#Check if help command is requested in the parameters entered. If yes, display_help fonction is called.
#Otherwise, do nothing.
for arg in "$@"; do
if [ "$arg" == "-h" ]; then
display_help
exit 0
fi
done


#Check for required parameters. If one or more are missing, an error message is displayed, 
#display_help fonction is called and an error code is returned.
if [[ -z "$1" || -z "$2" || -z "$3" ]]; then
  echo "Error : Missing parameters." >&2
  display_help
  exit 1
fi

#Check if the first parameter is the good path to the CSV file. Otherwise, an error message is displayed, 
#display_help fonction is called and an error code is returned.
if [[ ! -f "$1" || "$1" != *.csv ]]; then
echo "Error : The first parameter must be a valid path to an existing .csv file. " >&2
display_help
exit 1
fi


#Check if the second parameter is a type of station. Otherwise, an error message is displayed, 
#display_help fonction is called and an error code is returned.
if [[ "$2" != "hva" && "$2" != "hvb" && "$2" != "lv" ]]; then
echo "Error : The second parameter must be a type of station." >&2
display_help
exit 1
fi


#Check if the third parameter is a type of consumer. Otherwise, an error message is displayed, 
#display_help fonction is called and an error code is returned.
if [[ "$3" != "comp" && "$3" != "indiv" && "$3" != "all" ]]; then
echo "Error : The third parameter must be a type of consumer." >&2
display_help
exit 1
fi



#Check that the fourth parameter entered, which is the number of plant, if any, is valid.
#If not, an error message is displayed, display_help fonction is called and an error code is returned.
if [[ -n "$4"]]; then
if [[ "$4" != "1" && "$4" != "2" && "$4" != "3" && "$4" != "4" && "$4" != "5" ]]; then
echo "Error : The fourth parameter must be a valid power plant." >&2
display_help
exit 1
fi
fi





#Check the 4 prohibited combinations :
#1. If the first prohibited combination (hvb all) is entered by the user, an error message is displayed, 
#display_help fonction is called and an error code is returned.
if [[ "$2" == "hvb" && "$3" == "all" ]]; then
echo "Error : HV-B stations can not have all type of consumers." >&2
display_help
exit 1
fi


#2. If the second prohibited combination (hvb indiv) is entered by the user, an error message is displayed, 
#display_help fonction is called and an error code is returned.
if [[ "$2" == "hvb" && "$3" == "indiv" ]]; then
echo "Error : HV-B stations can not have individuals as consumers." >&2
display_help
exit 1
fi


#3. If the third prohibited combination (hva indiv) is entered by the user, an error message is displayed, 
#display_help fonction is called and an error code is returned.
if [[ "$2" == "hva"  && "$3" == "indiv" ]]; then
echo "Error : HV-A stations can not have individuals as consumers." >&2
display_help
exit 1
fi


#4. If the fourth prohibited combination (hva all) is entered by the user, an error message is displayed, 
#display_help fonction is called and an error code is returned.
if [[ "$2" == "hva" &&  "$3" == "all" ]]; then
echo "Error : HV-A stations can not have all type of consumers." >&2
display_help
exit 1
fi

./codeC

#Filter data based on user input and call the C program with the filtered data (5 possible combinations) :

#1. Companies linked to an HVB station (hvb comp) :
#Selection of the collones concerned in the CSV file.
#Extraction of these in the executable by replacing the "-"" with "0" to facilitate data manipulation.
if [[ "$2" == "hvb" ]] && [[ "$3" == "comp" ]]; then
  if [[ -n "$4" ]]; then
  awk -F';'  -v power_plant="$4" '$1 == power_plant && $2 != "-" && $3 == "-" && $4 == "-" && $5 != "-" && $6 == "-" && $7 == "-" && $8 != "-"' "c-wire_v00.dat" | cut -d';' -f1,2,5,8 | tr '-' '0' | ./codeC > "$OUTPUT_FILE"
  else 
  awk -F';'  '$1 != "-" && $2 != "-" && $3 == "-" && $4 == "-" && $5 != "-" && $6 == "-" && $7 == "-" && $8 != "-"' "c-wire_v00.dat" | cut -d';' -f1,2,5,8 | tr '-' '0' | ./codeC > "$OUTPUT_FILE"
fi
fi


#2. Companies linked to an HVA station (hva comp) :
#Selection of the collones concerned in the CSV file.
#Extraction of these in the executable by replacing the "-"" with "0" to facilitate data manipulation.
if [[ "$2" == "hva" ]] && [[ "$3" == "comp" ]]; then
  if [[ -n "$4" ]]; then
  awk -F';'  -v power_plant="$4" '$1 == power_plant && $2 == "-" && $3 != "-" && $4 == "-" && $5 != "-" && $6 == "-" && $7 == "-" && $8 != "-"' "c-wire_v00.dat" | cut -d';' -f1,3,5,8 | tr '-' '0' | ./codeC > "$OUTPUT_FILE"
  else 
  awk -F';'  '$1 != "-" && $2 == "-" && $3 != "-" && $4 == "-" && $5 != "-" && $6 == "-" && $7 == "-" && $8 != "-"' "c-wire_v00.dat" | cut -d';' -f1,3,5,8 | tr '-' '0' | ./codeC > "$OUTPUT_FILE"
fi
fi

#3. Companies linkes to a LV station (lv comp) :
#Selection of the collones concerned in the CSV file.
#Extraction of these in the executable by replacing the "-"" with "0" to facilitate data manipulation.
if [[ "$2" == "lv" ]] && [[ "$3" == "comp" ]]; then
  if [[ -n "$4" ]]; then
  awk -F';'  -v power_plant="$4" '$1 == power_plant && $2 == "-" && $3 == "-" && $4 != "-" && $5 != "-" && $6 == "-" && $7 == "-" && $8 != "-"' "c-wire_v00.dat" | cut -d';' -f1,4,5,8 | tr '-' '0' | ./codeC > "$OUTPUT_FILE"
  else
  awk -F';'  '$1 != "-" && $2 == "-" && $3 == "-" && $4 != "-" && $5 != "-" && $6 == "-" && $7 == "-" && $8 != "-"' "c-wire_v00.dat" | cut -d';' -f1,4,5,8 | tr '-' '0' | ./codeC > "$OUTPUT_FILE"
fi
fi

#4. Individuals linked to a LV station (lv indiv) :
#Selection of the collones concerned in the CSV file.
#Extraction of these in the executable by replacing the "-"" with "0" to facilitate data manipulation.
if [[ "$2" == "lv" ]] && [[ "$3" == "indiv" ]]; then
  if [[ -n "$4" ]]; then
  awk -F';' -v power_plant="$4" '$1 == power_plant && $2 == "-" && $3 == "-" && $4 != "-" && $5 == "-" && $6 != "-" && $7 == "-" && $8 != "-"' "cwire.dat" | cut -d';' -f1,4,6,8 | tr '-' '0' | ./codeC > "$OUTPUT_FILE"
  else
  awk -F';' '$1 != "-" && $2 == "-" && $3 == "-" && $4 != "-" && $5 == "-" && $6 != "-" && $7 == "-" && $8 != "-"' "cwire.dat" | cut -d';' -f1,4,6,8 | tr '-' '0' | ./codeC > "$OUTPUT_FILE"
fi
fi

#5. Individuals and companies linked to a LV station (lv all) :
#Selection of the collones concerned in the CSV file.
#Extraction of these in the executable by replacing the "-"" with "0" to facilitate data manipulation.
if [[ "$2" == "lv" ]] && [[ "$3" == "all" ]]; then
  if [[ -n "$4" ]]; then
  awk -F';' -v power_plant="$4" '$1 == power_plant && $2 == "-" && $3 == "-" && $4 != "-" && $5 != "-" && $6 != "-" && $7 == "-" && $8 != "-"' "cwire.dat" | cut -d';' -f1,4,5,6,8 | tr '-' '0' | ./codeC > "$OUTPUT_FILE"
  else
  awk -F';' '$1 != "-" && $2 == "-" && $3 == "-" && $4 != "-" && $5 != "-" && $6 != "-" && $7 == "-" && $8 != "-"' "cwire.dat" | cut -d';' -f1,4,5,6,8 | tr '-' '0' | ./codeC > "$OUTPUT_FILE"
fi




#Display elapsed time
B=$(date +%s.%N)
diff=$(echo "$B - $A" | bc)
echo "Elapsed time : $diff seconds"




Check files
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



