#!/bin/bash

#Text Color commands
#
#Brief: Commands to change the color of a text
highlight=$(echo -en '\033[01;37m')
purpleColor=$(echo -en '\033[01;35m')
cyanColor=$(echo -en '\033[01;36m')
errorColor=$(echo -en '\033[01;31m')
successColor=$(echo -en '\033[01;32m')
norm=$(echo -en '\033[0m')

printHelp() {
    printf 'Usage: %s [OPTIONS]...\n' "$(basename "$0")"
    echo "  Bash test script to test the menu application"
    echo 
    echo "OPTIONS        Option description"
    echo "  -help        Prints this help page"
    echo
}

#Function: parseOption s()
#
#Brief: Checks if all options are correct and saves them to variables
#
#Arguments all bash options
parseOptions() {
    while (("$#")); do # While there are arguments still to be shifted

        if [[ "$1" != "--help" && "$1" != "-h" ]]; then
            echo "Invalid option:  ${errorColor}$1${norm}, get help by running command: $0 --help"
            exit 1
        fi
        if [[ "$1" == "--help" || "$1" == "-h" ]]; then
            printHelp
            exit
        fi
        
        shift
    done

}

parseOptions "$@"

declare exe="out/menu"

if [ ! -f "$exe" ]; then  echo "${errorColor}Error excutable does not exist${norm}"; exit 1; fi;

echo "Please use arrow keys to selecte between options:"
$exe   "Option 1" "Option two"  "And some word in Icelandic, Á íslensku"
case $? in

    0) echo "Nothing was selected" ;;

    *) echo "Option $? was selected"
;;
esac
