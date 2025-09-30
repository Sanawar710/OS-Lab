#2023331
read -p "Enter the number of terms for Fibonacci series: " n

a=0
b=1

echo "Fibonacci series up to $n terms:"
for (( i=0; i<n; i++ ))
do
    echo -n "$a "
    fn=$((a + b))
    a=$b
    b=$fn
done
