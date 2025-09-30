#2023331
read -p "Enter a number to find its factorial: " num

fact=1

if (( num < 0 )); then
    echo "Factorial is not defined for negative numbers."
    exit 1
fi

for (( i=1; i<=num; i++ ))
do
    fact=$((fact * i))
done

echo "Factorial of $num is: $fact"
