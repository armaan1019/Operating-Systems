# Name: Armaan Sharma
# Date: March 31, 2026
# Title: Lab1 – Shell Programming
# Description: This program computes the perimeter and areas for a circle.

echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "armaansharma" ] 
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
exit 1
fi

perimeter() {
    radius=$1
    result=$(echo "2 * 3.14159 * $radius" | bc)
    echo "The perimeter is: $result"
}

area() {
    radius=$1
    result=$(echo "3.14159 * $radius * $radius" | bc)
    echo "The area is: $result"
}

response="Yes"
while [ $response != "No" ]
    do
        echo "Enter radius of circle: "
        read radius
        while [ "$(echo "$radius <= 0" | bc)" -eq 1 ]
            do
                echo "Enter another radius. Must be positive: "
                read radius
        done
        perimeter $radius
        area $radius
        echo "Would you like to repeat for another circle [Yes/No]?"
        read response
done

