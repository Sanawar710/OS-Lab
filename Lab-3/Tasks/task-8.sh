#2023331
# Create directories if they don't exist
mkdir -p shelldir cdir jpgdir

# Move .sh files
mv *.sh shelldir/ 2>/dev/null

# Move .c files
mv *.c cdir/ 2>/dev/null

# Move .jpg files
mv *.jpg jpgdir/ 2>/dev/null

echo "Files moved based on their extensions."
