#2023331
echo "Enter a number:"
read num

# Check if the number is less than 2
if [ "$num" -lt 2 ]; then
    echo "$num is not a prime number."
    exit 0
fi

# 2 is prime
if [ "$num" -eq 2 ]; then
    echo "$num is a prime number."
    exit 0
fi

# Check divisibility from 2 to sqrt(num)
i=2
while [ $((i * i)) -le "$num" ]; do
    if [ $((num % i)) -eq 0 ]; then
        echo "$num is not a prime number."
        exit 0
    fi
    i=$((i + 1))
done

echo "$num is a prime number."
