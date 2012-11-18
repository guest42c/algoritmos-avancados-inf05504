echo "Chance of existing edge:"
read chance 
for ((i = 100; i <= 3000; i = i + 100 ))
do
  echo "nodes\telapsed_time\tedges\tdeletemin\tinsert\tupdate" > "running-time-$chance-all"
  for ((j = 0; j < 10; j++))
  do
    ./gen $i $chance > "test-$chance-$i.gr" 2> "test-$chance-$i.an.gr"
    echo "Graph with $i nodes and $chance chance of existing edges between nodes created..." 
    from=$(awk '{print $3}' "test-$chance-$i.an.gr")
    to=$(awk '{print $5}' "test-$chance-$i.an.gr")
    ./dijkstra $from $to < "test-$chance-$i.gr" 2>> "run.tmp"
    rm "test-$chance-$i.gr"
    rm "test-$chance-$i.an.gr" 
  done
  nodes=$(awk '{x+=$1;next}END{print x/NR}' "run.tmp")
  elapsed_time=$(awk '{x+=$2;next}END{print x/NR}' "run.tmp")
  edges=$(awk '{x+=$3;next}END{print x/NR}' "run.tmp")
  deletemin=$(awk '{x+=$4;next}END{print x/NR}' "run.tmp")
  insert=$(awk '{x+=$5;next}END{print x/NR}' "run.tmp")
  update=$(awk '{x+=$6;next}END{print x/NR}' "run.tmp")
  cat "run.tmp" >> "running-time-$chance-all"
  rm "run.tmp"
  echo $nodes $elapsed_time $edges $deletemin $insert $update >> "running-time-$chance"
done   
