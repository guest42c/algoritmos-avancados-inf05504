echo "Chance of existing edge:"
read chance 
for ((i = 100; i <= 3000; i = i + 100 ))
do
  ./gen $i $chance > "test-$chance-$i.gr" 2> "test-$chance-$i.an.gr" 
  from=$(awk '{print $3}' "test-$chance-$i.an.gr")
  to=$(awk '{print $5}' "test-$chance-$i.an.gr")
  ./dijkstra $from $to < "test-$chance-$i.gr" 2>> "running-time-$chance"
  rm "test-$chance-$i.gr"
  rm "test-$chance-$i.an.gr" 
done   
