# menu
C++ terminal application for usage in bash files to ask the user 
to select between options.

## Return values
If nothing is selected the the return value is 0, if something 
is selected then the return value is bigger than 0.

### Usage
    Provide the available options in a double quoted parameters. 
    
 ```bash
declare exe="out/menu"

if [ ! -f "$exe" ]; then  echo "Error excutable does not exist"; exit 1; fi;


$exe  -lines "Option 1" "Option two"  "And some word in Icelandic, á íslensku"
case $? in

    0) echo "Nothing was selected" ;;

    *) echo "Option $? was selected"
;;
esac
 ```

