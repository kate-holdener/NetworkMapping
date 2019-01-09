#!/bin/bash

D=(1 0.5)
NV=(5 10 15 20 25 50)
NW=("1-5" "5-10")
EW=("1-5" "5-10")

for d in ${D[@]}; do
   for nodes in ${NV[@]}; do
      for nw in ${NW[@]}; do
        for ew in ${EW[@]}; do
           file_name=VN${nodes}_D${d}_NW${nw}_EW${ew}
           ../../GraphGenerator/build/src/graph_generator -density ${d} -nodes ${nodes} -edge_weight ${ew} -node_weight ${node_weight} > virtual/${file_name} 
        done
      done
   done
done
