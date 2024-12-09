FILE_DAT="data_cwire.dat"
FILE_TEMP="filtered_data.dat" # temp file with filtered data
FILE_C="./code" # path to the compiled C executable
OUTPUT_FILE="result.txt" # file to show C program results (can be modified in the future to a graphic file)

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

./code
