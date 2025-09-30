#2023331
echo "Enter 5 numbers:"
read -p "Number 1: " n1
read -p "Number 2: " n2
read -p "Number 3: " n3
read -p "Number 4: " n4
read -p "Number 5: " n5

# Initialize max and min
max=$n1
min=$n1

# Check max
for num in $n2 $n3 $n4 $n5
do
    if (( num > max )); then
        max=$num
    fi
    if (( num < min )); then
        min=$num
    fi
done

echo "Maximum number is: $max"
echo "Minimum number is: $min"
