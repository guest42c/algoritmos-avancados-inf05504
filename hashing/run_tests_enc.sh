echo "n(7919):"
read n
echo "m:"
read m
echo "inserts lookups table_size elapsed_time_inserts elapsed_time_lookups" > "experiment-enc-$n-$m-all"
for ((i = $n/10; i <= $n; i += $n/10 ))
do
  for ((j = 0; j < 10; j++))
  do
    echo "Execution $j"
    ./gen $i $m > "test-$i-$m.gr"
    ./hash_enc < "test-$i-$m.gr" 2>> "run.tmp"
    rm "test-$i-$m.gr"
  done
  occupancy=$(echo "scale=1; $i/$n" | bc)
  inserts=$(awk '{x+=$4;next}END{print x/NR}' "run.tmp")
  lookups=$(awk '{x+=$5;next}END{print x/NR}' "run.tmp")
  max_inserts=$(awk '{if (x<=$4) x=$4; next}END{print x}' "run.tmp")
  min_inserts=$(awk 'BEGIN{x=9999999999}{if (x>=$4) x=$4; next}END{print x}' "run.tmp")
  max_lookups=$(awk '{if (x<=$5) x=$5; next}END{print x}' "run.tmp")
  min_lookups=$(awk 'BEGIN{x=9999999999}{if (x>=$5) x=$5; next}END{print x}' "run.tmp")
  cat run.tmp >> "experiment-enc-$n-$m-all"
  rm run.tmp
  echo $occupancy $min_inserts $inserts $max_inserts >> "experiment-enc-$n-$m-inserts"
  echo $occupancy $min_lookups $lookups $max_lookups >> "experiment-enc-$n-$m-lookups"
done   
