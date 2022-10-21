#!/bin/bash
file_name="scan.mac"
run_name="../Output/2D_Test/2DTest"
min_x=-1900
min_y=-1900
max_x=1900
max_y=1900
step_x=50
step_y=50

for(( i = $min_x; i <= $max_x; i+= $step_x))
do
  for(( j = $min_y; j <= $max_y; j+= $step_y ))
  do
    echo "pos att $i $j"
    sed -i "2 c\/run/fname ${run_name}" $file_name
    sed -i "3 c\/run/fxpos ${i}" $file_name
    sed -i "4 c\/run/fypos ${j}" $file_name
    sed -i "5 c\/gun/position ${i} ${j} 0 um" $file_name
    ./sim $file_name
  done
done

echo All done
