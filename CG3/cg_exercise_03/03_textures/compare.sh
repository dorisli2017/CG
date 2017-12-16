for i in assignment_references/*; do
  compare -compose src $i assignment_images/$(basename $i) diff/$(basename     $i)
done
