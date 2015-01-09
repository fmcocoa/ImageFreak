#
# Fix this warning: libpng warning: iCCP: known incorrect sRGB profile
#

for i in $(find . -type f -name "*.png")
do
    gm convert $i -strip $i
done
