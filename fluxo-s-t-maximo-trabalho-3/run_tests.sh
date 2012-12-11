echo "type:"
read type
echo "dim1:"
read dim1
echo "dim2:"
read dim2
echo "range:"
read range
echo "vertices edges iter_count elapsed_time" > "experiment-$dim1-$dim2-$range-all"
for ((i = 1; i <= 10; i++))
do
  for ((j = 0; j < 10; j++))
  do
    echo "Execution $j"
    d1=$(echo "$dim1 * $i / 10" | bc)
    echo $d1
    d2=$(echo "$dim1 * $i / 10" | bc)
    echo $d2
    ./gengraph $type $d1 $d2 $range "test-$type-$dim1-$dim2-$range.gr"
    ./ford-fulkerson < "test-$type-$dim1-$dim2-$range.gr" 2>> "run.tmp"
    rm "test-$type-$dim1-$dim2-$range.gr"
  done
  limU=$(awk '{x+=$1;next}END{print x/NR}' "run.tmp")
  total_edges=$(awk '{x+=$2;next}END{print x/NR}' "run.tmp")
  count_iter=$(awk '{x+=$3;next}END{print x/NR}' "run.tmp")
  elapsed_time=$(awk '{x+=$4;next}END{print x/NR}' "run.tmp")
  max_count_iter=$(awk '{if (x<=$3) x=$3; next}END{print x}' "run.tmp")
  min_count_iter=$(awk 'BEGIN{x=9999999999}{if (x>=$3) x=$3; next}END{print x}' "run.tmp")
  max_time=$(awk '{if (x<=$4) x=$4; next}END{print x}' "run.tmp")
  min_time=$(awk 'BEGIN{x=9999999999}{if (x>=$4) x=$4; next}END{print x}' "run.tmp")
  cat run.tmp >> "experiment-$dim1-$dim2-$range-all"
  rm run.tmp
  echo $total_edges $min_time $elapsed_time $max_time >> "experiment-$dim1-$dim2-$range-time"
  echo $total_edges $min_count_iter $count_iter $max_count_iter $limU >> "experiment-$dim1-$dim2-$range-iter"
done   
