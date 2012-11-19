echo "Chance of existing edge:"
read chance 
echo "vertices elapsed_time edges deletemin insert update" > "experiment-$chance-all"
for ((i = 100; i <= 2000; i = i + 100 ))
do
  for ((j = 0; j < 10; j++))
  do
    echo "Execution $j to $i vertices"
    ./gen $i $chance > "test-$chance-$i.gr" 2> "test-$chance-$i.an.gr"
    echo "Graph created with $i vertices and $chance chance of existing edges between vertices." 
    from=$(awk '{print $3}' "test-$chance-$i.an.gr")
    to=$(awk '{print $5}' "test-$chance-$i.an.gr")
    echo "Calculation distance between $from and $to."
    ./dijkstra $from $to < "test-$chance-$i.gr" 2>> "run.tmp"
    rm "test-$chance-$i.gr"
    rm "test-$chance-$i.an.gr" 
  done
  vertices=$(awk '{x+=$1;next}END{print x/NR}' "run.tmp")
  elapsed_time=$(awk '{x+=$2;next}END{print x/NR}' "run.tmp")
  max_time=$(awk '{if (x<=$2) x=$2; next}END{print x}' "run.tmp")
  min_time=$(awk 'BEGIN{x=9999999999}{if (x>=$2) x=$2; next}END{print x}' "run.tmp")
  edges=$(awk '{x+=$3;next}END{print x/NR}' "run.tmp")
  deletemin=$(awk '{x+=$4;next}END{print x/NR}' "run.tmp")
  max_deletemin=$(awk '{if (x<=$4) x=$4; next}END{print x}' "run.tmp")
  min_deletemin=$(awk 'BEGIN{x=9999999999}{if (x>=$4) x=$4; next}END{print x}' "run.tmp")
  insert=$(awk '{x+=$5;next}END{print x/NR}' "run.tmp")
  max_insert=$(awk '{if (x<=$5) x=$5; next}END{print x}' "run.tmp")
  min_insert=$(awk 'BEGIN{x=9999999999}{if (x>=$5) x=$5; next}END{print x}' "run.tmp")
  update=$(awk '{x+=$6;next}END{print x/NR}' "run.tmp")
  max_update=$(awk '{if (x<=$6) x=$6; next}END{print x}' "run.tmp")
  min_update=$(awk 'BEGIN{x=9999999999}{if (x>=$6) x=$6; next}END{print x}' "run.tmp")
  cat run.tmp >> "experiment-$chance-all"
  rm run.tmp
  echo $vertices $max_time $elapsed_time $min_time >> "experiment-$chance-time"
  echo $vertices $max_deletemin $deletemin $min_deletemin >> "experiment-$chance-deletemin"
  echo $vertices $max_insert $insert $min_insert >> "experiment-$chance-insert"
  echo $edges $max_update $update $min_update >> "experiment-$chance-update"
done   
